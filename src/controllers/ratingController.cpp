#include "ratingController.h"

RatingController::RatingController()
{
    db = DB::getInstance();
}

bool RatingController::createRating(int userID, std::string movieID, float rating)
{
    if (!(movieController->storeMovie(movieID)))
    {
        std::cout << "ERROR: Cannot Save movie " << movieID << std::endl;
        return false;
    }

    std::stringstream ss;
    ss << "INSERT INTO UserMovies(UserID, MovieID, UserRating) VALUES (" << userID << ", " << movieID << ", " << rating << ")";
    int count = db->executeUpdate(ss.str());

    if (count > 0)
    {
        // Fetch the user and the movie from the database
        std::unique_ptr<User> user = userController->getUser(userID);
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
            userController->updateUser(user);
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

bool RatingController::updateRating(int userID, std::string movieID, float newRating)
{
    // Fetch the old rating from the database
    float oldRating = getRating(userID, movieID);

    // Update the rating in the database
    std::stringstream ss;
    ss << "UPDATE UserMovies SET UserRating = " << newRating << " WHERE UserID = " << userID << " AND MovieID = " << movieID;
    int count = db->executeUpdate(ss.str());

    if (count > 0)
    {
        // Fetch the user and the movie from the database
        std::unique_ptr<User> user = userController->getUser(userID);
        Movie *movie;
        movieController->fetchMovieById(movieID, *movie);

        // Update the user's genre preferences
        for (int genre : movie->genre_ids)
        {
            user->genre_preferences[genre] -= oldRating;
            user->genre_preferences[genre] += newRating;
        }

        // Update the user's language preferences
        user->language_preferences[movie->original_language] -= oldRating;
        user->language_preferences[movie->original_language] += newRating;

        // Update the user in the database
        userController->updateUser(user);
    }

    return count > 0;
}

bool RatingController::deleteRating(int userID, std::string movieID)
{
    // Fetch the old rating from the database
    float oldRating = getRating(userID, movieID);

    // Delete the rating from the database
    std::stringstream ss;
    ss << "DELETE FROM UserMovies WHERE UserID = " << userID << " AND MovieID = " << movieID;
    int count = db->executeUpdate(ss.str());

    if (count > 0)
    {
        // Fetch the user and the movie from the database
        std::unique_ptr<User> user = userController->getUser(userID);
        Movie *movie;
        movieController->fetchMovieById(movieID, *movie);

        // Update the user's genre preferences
        for (int genre : movie->genre_ids)
        {
            user->genre_preferences[genre] -= oldRating;
        }

        // Update the user's language preferences
        user->language_preferences[movie->original_language] -= oldRating;

        // Update the user in the database
        userController->updateUser(user);
    }

    return count > 0;
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

bool RatingController::createRatingQML(int userID, const QString &movieID, float rating)
{
    return createRating(userID, movieID.toStdString(), rating);
}

bool RatingController::updateRatingQML(int userID, const QString &movieID, float newRating)
{
    return updateRating(userID, movieID.toStdString(), newRating);
}

bool RatingController::deleteRatingQML(int userID, const QString &movieID)
{
    return deleteRating(userID, movieID.toStdString());
}

float RatingController::getRatingQML(int userID, const QString &movieID) const
{
    return getRating(userID, movieID.toStdString());
}