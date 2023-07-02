#include "movieController.h"
#include "movie.h"
#include "db.h"
#include "sstream"

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
bool MovieController::FetchMovieById(const std::string MovieId, Movie &movie)
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

bool MovieController::FetchMoviesByTitle(std::string movieName, std::vector<Movie> &movies)
{
    std::string apiKey = std::getenv("API_KEY_TMDB"); // Fetch the API key from the environment variables
    std::string url = "https://api.themoviedb.org/3/search/movie?api_key=" + apiKey + "&query=" + movieName + "&language=en-US&page=1";
    return FetchMovies(url, movies);
}

bool MovieController::FetchPopularMovies(std::vector<Movie> &movies)
{
    std::string apiKey = std::getenv("API_KEY_TMDB");
    std::string url = "https://api.themoviedb.org/3/movie/popular?api_key=" + apiKey + "&language=en-US&page=1";
    return FetchMovies(url, movies);
}

bool StoreMovieGenres(std::vector<int> &genres, int movieId)
{
    for (int &genreId : genres)
    {
        // Check if genre exists
        std::stringstream ss_check;
        ss_check << "SELECT * FROM MovieGenres WHERE MovieId = '" << movieId << "' AND GenreId = '" << genreId << "'";
        sql::ResultSet *result = DB::getInstance()->executeQuery(ss_check.str());

        if (!result->next())
        { // If genre does not exist, insert it
            std::stringstream ss_insert;
            ss_insert << "INSERT INTO MovieGenres (MovieId, GenreId) VALUES ('" << movieId << "', '" << genreId << "')";
            int count = DB::getInstance()->executeUpdate(ss_insert.str());
            if (count == 0)
            {
                std::cerr << "Failed to store genre data." << std::endl;
                return false;
            }
        }
        delete result;
    }
    return true;
}

bool MovieController::StoreMovie(const std::string movieId)
{
    // Fetch the movie data.
    Movie movie;
    if (!FetchMovieById(movieId, movie))
    {
        std::cerr << "Failed to fetch movie data." << std::endl;
        return false;
    }

    // Check if movie exists
    std::stringstream ss_check;
    ss_check << "SELECT * FROM Movies WHERE Id = '" << movie.id << "'";
    sql::ResultSet *result = DB::getInstance()->executeQuery(ss_check.str());

    if (!result->next())
    { // If movie does not exist, insert it
        // Prepare SQL statement for Movies table.
        std::stringstream ss_insert;
        ss_insert << "INSERT INTO Movies (Id, Title, original_title, original_language, Overview, release_date, "
                  << "Adult, Popularity, Video, vote_average, vote_count, backdrop_path, poster_path) "
                  << "VALUES ('" << movie.id << "', '" << movie.title << "', '" << movie.original_title << "', '"
                  << movie.original_language << "', '" << movie.overview << "', '" << movie.release_date << "', '"
                  << (movie.adult ? 1 : 0) << "', '" << movie.popularity << "', '" << (movie.video ? 1 : 0) << "', '"
                  << movie.vote_average << "', '" << movie.vote_count << "', '" << movie.backdrop_path << "', '"
                  << movie.poster_path << "')";

        // Execute SQL statement for Movies table.
        int count = DB::getInstance()->executeUpdate(ss_insert.str());
        if (count == 0)
        {
            std::cerr << "Failed to store movie data." << std::endl;
            return false;
        }

        // Store the movie genres data.
        StoreMovieGenres(movie.genre_ids, movie.id);
    }
    delete result;

    return true;
}

bool MovieController::GetAllMovies(std::map<int, Movie> &movies)
{
    std::stringstream ss;
    ss << "SELECT * FROM Movies";
    sql::ResultSet *result = DB::getInstance()->executeQuery(ss.str());

    while (result->next())
    {
        Movie movie;
        movie.id = result->getInt("Id");
        movie.title = result->getString("Title");
        movie.original_title = result->getString("original_title");
        movie.original_language = result->getString("original_language");
        movie.overview = result->getString("Overview");
        movie.release_date = result->getString("release_date");
        movie.adult = result->getBoolean("Adult");
        movie.popularity = result->getDouble("Popularity");
        movie.video = result->getBoolean("Video");
        movie.vote_average = result->getDouble("vote_average");
        movie.vote_count = result->getInt("vote_count");
        movie.backdrop_path = result->getString("backdrop_path");
        movie.poster_path = result->getString("poster_path");

        movies.insert(std::pair<int, Movie>(movie.id, movie));
    }
    delete result;
    return true;
}