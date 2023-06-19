#include "movieApiController.h"
#include "movie.h"

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

bool FetchMoviesByTitle(std::string movieName, std::vector<Movie> &movies)
{
    std::string apiKey = std::getenv("API_KEY_TMDB"); // Fetch the API key from the environment variables
    std::string url = "https://api.themoviedb.org/3/search/movie?api_key=" + apiKey + "&query=" + movieName + "&language=en-US&page=1";
    return FetchMovies(url, movies);
}

bool FetchPopularMovies(std::vector<Movie> &movies)
{
    std::string apiKey = std::getenv("API_KEY_TMDB"); // Fetch the API key from the environment variables
    std::string url = "https://api.themoviedb.org/3/movie/popular?api_key=" + apiKey + "&language=en-US&page=1";
    return FetchMovies(url, movies);
}
