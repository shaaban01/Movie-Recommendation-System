#include "ratingController.h"

RatingController::RatingController()
{
    db = DB::getInstance();
}

bool RatingController::addRating(int userID, std::string movieID, float rating)
{
    UserController userController;

    // Check if the rating already exists
    float oldRating = getRating(userID, movieID);
    if (oldRating > 0)
    {
        // Update the rating in the database
        std::stringstream ss;
        ss << "UPDATE UserMovies SET UserRating = " << rating << " WHERE UserID = " << userID << " AND MovieID = '" << movieID << "'";
        int count = db->executeUpdate(ss.str());

        if (count > 0)
        {
            // Fetch the user and the movie from the database
            std::unique_ptr<User> user = userController.getUser(userID);
            Movie *movie;
            movieController->fetchMovieById(movieID, *movie);

            // Update the user's genre preferences
            for (int genre : movie->genre_ids)
            {
                user->genre_preferences[genre] -= oldRating;
                user->genre_preferences[genre] += rating;
            }

            // Update the user's language preferences
            user->language_preferences[movie->original_language] -= oldRating;
            user->language_preferences[movie->original_language] += rating;

            // Update the user in the database
            userController.updateUser(user);
        }

        return count > 0;
    }
    else
    {
        // Create a new rating
        if (!(movieController->storeMovie(movieID)))
        {
            std::cout << "ERROR: Cannot Save movie " << movieID << std::endl;
            return false;
        }

        std::stringstream ss;
        ss << "INSERT INTO UserMovies(UserID, MovieID, UserRating) VALUES (" << userID << ", '" << movieID << "', " << rating << ")";
        int count = db->executeUpdate(ss.str());
        if (count > 0)
        {
            // Fetch the user and the movie from the database
            std::unique_ptr<User> user = userController.getUser(userID);
            Movie *movie = new Movie;
            if (user != nullptr && movieController->fetchMovieById(movieID, *movie))
            {
                // Update the user's genre preferences
                for (int genre : movie->genre_ids)
                {
                    user->genre_preferences[genre] += rating;
                }

                // Update the user's language preferences
                user->language_preferences[movie->original_language] += rating;

                // Update the user in the database
                userController.updateUser(user);
            }
            else
            {
                std::cout << "ERROR: Failed to fetch user or movie data." << std::endl;
                delete movie;
                return false;
            }

            delete movie;
            return true;
        }
        else
        {
            std::cout << "ERROR: Cannot Save rating " << movieID << std::endl;
            return false;
        }
    }
}

float RatingController::getRating(int userID, std::string movieID) const
{
    std::stringstream ss;
    ss << "SELECT UserRating FROM UserMovies WHERE UserID = " << userID << " AND MovieID = " << movieID;
    sql::ResultSet *res = db->executeQuery(ss.str());
    float rating = 0.0;
    if (res->next())
    {
        rating = res->getDouble("UserRating");
    }
    delete res;
    return rating;
}

std::map<int, float> RatingController::getAllRatings(int userID) const
{
    std::stringstream ss;
    ss << "SELECT MovieID, UserRating FROM UserMovies WHERE UserID = " << userID;
    sql::ResultSet *res = db->executeQuery(ss.str());

    std::map<int, float> ratings;
    while (res->next())
    {
        std::string movieID = res->getString("MovieID");
        float rating = res->getDouble("UserRating");
        int movieId = std::stoi(movieID);
        ratings[movieId] = rating;
    }
    delete res;
    return ratings;
}

bool RatingController::addRatingQML(int userID, const QString &movieID, float rating)
{
    return addRating(userID, movieID.toStdString(), rating);
}

float RatingController::getRatingQML(int userID, const QString &movieID) const
{
    return getRating(userID, movieID.toStdString());
}

QVariantList RatingController::getAllRatingsQML(int userID) const
{
    std::map<int, float> ratings = getAllRatings(userID);
    QVariantList variantList;
    MovieController *movieController;
    Movie movie;
    for (auto const &rating : ratings)
    {
        movieController->fetchMovieById(std::to_string(rating.first), movie);
        QVariantMap movieMap;
        movieMap["movieID"] = QString::number(movie.id);
        movieMap["url"] = QString::fromStdString(movie.poster_path);
        movieMap["title"] = QString::fromStdString(movie.title);
        movieMap["rating"] = ratings[movie.id];
        variantList.append(movieMap);
    }

    return variantList;
}