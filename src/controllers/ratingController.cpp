#include "ratingController.h"

RatingController::RatingController()
{
    db = DB::getInstance();
}

bool RatingController::createRating(int userID, int movieID, float rating)
{
    if (!(StoreMovie(movieID)))
        std::cout << "ERROR: Cannot Save movie " << movieID << std::endl;

    std::stringstream ss;
    ss << "INSERT INTO UserMovies(UserID, MovieID, UserRating) VALUES (" << userID << ", " << movieID << ", " << rating << ")";
    int count = db->executeUpdate(ss.str());

    if (count > 0)
    {
        // Fetch the user and the movie from the database
        User user = fetchUserById(userID);
        Movie movie = fetchMovieById(movieID);

        // Update the user's genre preferences
        for (int genre : movie.genre_ids)
        {
            user.genre_preferences[genre] += rating;
        }

        // Update the user's language preferences
        user.language_preferences[movie.original_language] += rating;

        // Update the user in the database
        updateUser(user);
    }

    return count > 0;
}

bool RatingController::updateRating(int userID, int movieID, float newRating)
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
        User user = fetchUserById(userID);
        Movie movie = fetchMovieById(movieID);

        // Update the user's genre preferences
        for (int genre : movie.genre_ids)
        {
            user.genre_preferences[genre] -= oldRating;
            user.genre_preferences[genre] += newRating;
        }

        // Update the user's language preferences
        user.language_preferences[movie.original_language] -= oldRating;
        user.language_preferences[movie.original_language] += newRating;

        // Update the user in the database
        updateUser(user);
    }

    return count > 0;
}

bool RatingController::deleteRating(int userID, int movieID)
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
        User user = fetchUserById(userID);
        Movie movie = fetchMovieById(movieID);

        // Update the user's genre preferences
        for (int genre : movie.genre_ids)
        {
            user.genre_preferences[genre] -= oldRating;
        }

        // Update the user's language preferences
        user.language_preferences[movie.original_language] -= oldRating;

        // Update the user in the database
        updateUser(user);
    }

    return count > 0;
}

float RatingController::getRating(int userID, int movieID)
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

std::map<int, float> RatingController::getAllRatings(int userID)
{
    std::stringstream ss;
    ss << "SELECT MovieID, UserRating FROM UserMovies WHERE UserID = " << userID;
    sql::ResultSet *res = db->executeQuery(ss.str());

    std::map<int, float> ratings;
    while (res->next())
    {
        int movieID = res->getInt("MovieID");
        float rating = res->getDouble("UserRating");
        ratings[movieID] = rating;
    }
    delete res;
    return ratings;
}