#include "movieApiController.h"
#include "movie.h"
#ifndef DB_H
#define DB_H
#include "db.h"
#include "sstream"
#endif

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp)
{
    userp->append((char *)contents, size * nmemb);
    return size * nmemb;
}

bool FetchMovies(std::string url, std::vector<Movie> &movies)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return false;
        }
        else
        {
            nlohmann::json jsonResponse = nlohmann::json::parse(readBuffer);

            for (auto &movieJson : jsonResponse["results"])
            {
                movies.push_back(Movie(movieJson));
            }
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return true;
}
bool MovieApiController::FetchMovieById(const std::string MovieId, Movie &movie)
{

    std::string apiKey = std::getenv("API_KEY_TMDB"); // Fetch the API key from the environment variables
    std::string url = "https://api.themoviedb.org/3/movie/" + MovieId + "?api_key=" + apiKey + "&language=en-US&page=1";

    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return false;
        }
        else
        {
            nlohmann::json jsonResponse = nlohmann::json::parse(readBuffer);
            movie = Movie(jsonResponse);
        }
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return true;
}

bool MovieApiController::FetchMoviesByTitle(std::string movieName, std::vector<Movie> &movies)
{
    std::string apiKey = std::getenv("API_KEY_TMDB"); // Fetch the API key from the environment variables
    std::string url = "https://api.themoviedb.org/3/search/movie?api_key=" + apiKey + "&query=" + movieName + "&language=en-US&page=1";
    return FetchMovies(url, movies);
}

bool MovieApiController::FetchPopularMovies(std::vector<Movie> &movies)
{
    std::string apiKey = std::getenv("API_KEY_TMDB"); // Fetch the API key from the environment variables
    std::string url = "https://api.themoviedb.org/3/movie/popular?api_key=" + apiKey + "&language=en-US&page=1";
    return FetchMovies(url, movies);
}

bool MovieApiController::StoreMovie(const std::string movieId)
{
    // Fetch the movie data.
    Movie movie;
    if (!FetchMovieById(movieId, movie))
    {
        std::cerr << "Failed to fetch movie data." << std::endl;
        return false;
    }

    // Prepare SQL statement for Movies table.
    std::stringstream ss;
    ss << "INSERT INTO Movies (Id, Title, original_title, original_language, Overview, release_date, "
       << "Adult, Popularity, Video, vote_average, vote_count, backdrop_path, poster_path) "
       << "VALUES ('" << movie.id << "', '" << movie.title << "', '" << movie.original_title << "', '"
       << movie.original_language << "', '" << movie.overview << "', '" << movie.release_date << "', '"
       << (movie.adult ? 1 : 0) << "', '" << movie.popularity << "', '" << (movie.video ? 1 : 0) << "', '"
       << movie.vote_average << "', '" << movie.vote_count << "', '" << movie.backdrop_path << "', '"
       << movie.poster_path << "')";

    // Execute SQL statement for Movies table.
    int count = DB::getInstance()->executeUpdate(ss.str());
    if (count == 0)
    {
        std::cerr << "Failed to store movie data." << std::endl;
        return false;
    }

    // Insert each genre id into the MovieGenres table.
    for (int genre_id : movie.genre_ids)
    {
        std::stringstream ss2;
        ss2 << "INSERT INTO MovieGenres (MovieId, GenreId) VALUES ('" << movieId << "', '" << genre_id << "')";
        count = DB::getInstance()->executeUpdate(ss2.str());
        if (count == 0)
        {
            std::cerr << "Failed to store genre data for movie." << std::endl;
            return false;
        }
    }

    return true;
}
