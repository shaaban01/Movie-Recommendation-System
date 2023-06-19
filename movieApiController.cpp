#include "movieApiController.h"
#include "movie.h"

std::string const apiKey = "2cce7924b7bbfab015d3af73e7ea9bba";

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp)
{
    userp->append((char *)contents, size * nmemb);
    return size * nmemb;
}

bool FetchMoviesByTitle(std::string movieName, std::vector<Movie> &movies)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        std::string url = "https://api.themoviedb.org/3/search/movie?api_key=" + apiKey + "&query=" + movieName + "&language=en-US&page=1";
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

bool FetchPopularMovies(std::vector<Movie> &movies)
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl)
    {
        std::string url = "https://api.themoviedb.org/3/movie/popular?api_key=" + apiKey + "&language=en-US&page=1";
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


