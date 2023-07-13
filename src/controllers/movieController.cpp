#include "movieController.h"
#include "movie.h"
#include "db.h"
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <sstream>

size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *userp)
{
    userp->append((char *)contents, size * nmemb);
    return size * nmemb;
}

bool fetchMovies(std::string url, std::vector<Movie> &movies)
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
bool MovieController::fetchMovieById(const std::string MovieId, Movie &movie)
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

bool MovieController::fetchMoviesByTitle(std::string movieName, std::vector<Movie> &movies)
{
    std::string encodedMovieName = urlEncode(movieName);
    std::string apiKey = std::getenv("API_KEY_TMDB"); // Fetch the API key from the environment variables
    std::string url = "https://api.themoviedb.org/3/search/movie?api_key=" + apiKey + "&query=" + encodedMovieName + "&language=en-US&page=1";
    return fetchMovies(url, movies);
}

bool MovieController::fetchPopularMovies(std::vector<Movie> &movies)
{
    std::string apiKey = std::getenv("API_KEY_TMDB");
    std::string url = "https://api.themoviedb.org/3/movie/popular?api_key=" + apiKey + "&language=en-US&page=1";
    return fetchMovies(url, movies);
}

bool storeMovieGenres(std::vector<int> &genres, int movieId)
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

bool MovieController::storeMovie(const std::string movieId)
{
    // Fetch the movie data.
    Movie movie;
    if (!fetchMovieById(movieId, movie))
    {
        std::cerr << "Failed to fetch movie data." << std::endl;
        return false;
    }

    // Check if movie exists
    std::stringstream ss_check;
    ss_check << "SELECT * FROM Movies WHERE Id = ?";
    sql::PreparedStatement *checkStatement = DB::getInstance()->prepareStatement(ss_check.str());
    checkStatement->setString(1, std::to_string(movie.id));
    sql::ResultSet *result = checkStatement->executeQuery();

    if (!result->next())
    { // If movie does not exist, insert it
        // Prepare SQL statement for Movies table.
        std::stringstream ss_insert;
        ss_insert << "INSERT INTO Movies (Id, Title, original_title, original_language, Overview, release_date, "
                  << "Adult, Popularity, Video, vote_average, vote_count, backdrop_path, poster_path) "
                  << "VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";

        sql::PreparedStatement *insertStatement = DB::getInstance()->prepareStatement(ss_insert.str());
        insertStatement->setString(1, std::to_string(movie.id));
        insertStatement->setString(2, movie.title);
        insertStatement->setString(3, movie.original_title);
        insertStatement->setString(4, movie.original_language);
        insertStatement->setString(5, movie.overview);
        insertStatement->setString(6, movie.release_date);
        insertStatement->setBoolean(7, movie.adult);
        insertStatement->setDouble(8, movie.popularity);
        insertStatement->setBoolean(9, movie.video);
        insertStatement->setDouble(10, movie.vote_average);
        insertStatement->setInt(11, movie.vote_count);
        insertStatement->setString(12, movie.backdrop_path);
        insertStatement->setString(13, movie.poster_path);

        // Execute SQL statement for Movies table.
        int count = insertStatement->executeUpdate();
        if (count == 0)
        {
            std::cerr << "Failed to store movie data." << std::endl;
            delete insertStatement;
            delete checkStatement;
            delete result;
            return false;
        }

        delete insertStatement;
        delete checkStatement;

        // Store the movie genres data.
        storeMovieGenres(movie.genre_ids, movie.id);
    }
    delete checkStatement;
    delete result;

    return true;
}

bool MovieController::getAllMovies(std::map<int, Movie> &movies)
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

QVariantList MovieController::fetchMoviesByTitleQML(const QString &movieName)
{
    std::vector<Movie> movies;
    if (!fetchMoviesByTitle(movieName.toStdString(), movies))
    {
        return QVariantList();
    }
    QVariantList qMovies;
    for (Movie &movie : movies)
    {
        QVariantMap movieMap;
        movieMap["movieID"] = QString::number(movie.id);
        movieMap["url"] = QString::fromStdString(movie.poster_path);
        movieMap["title"] = QString::fromStdString(movie.title);
        qMovies.append(movieMap);
    }
    return qMovies;
}

std::string MovieController::urlEncode(const std::string& str)
{
    std::ostringstream escaped;
    escaped.fill('0');
    escaped << std::hex;

    for (char c : str) {
        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
        } else {
            escaped << '%' << std::setw(2) << std::int32_t(static_cast<unsigned char>(c));
        }
    }

    return escaped.str();
}