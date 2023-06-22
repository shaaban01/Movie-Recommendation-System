#include "ratingController.h"
#include <sstream>

RatingController::RatingController()
{
    db = DB::getInstance();
}

bool RatingController::createRating(int userID, int movieID, float rating)
{
    std::stringstream ss;
    ss << "INSERT INTO UserMovies(UserID, MovieID, UserRating) VALUES (" << userID << ", " << movieID << ", " << rating << ")";
    int count = db->executeUpdate(ss.str());
    return count > 0;
}

bool RatingController::updateRating(int userID, int movieID, float newRating)
{
    std::stringstream ss;
    ss << "UPDATE UserMovies SET UserRating = " << newRating << " WHERE UserID = " << userID << " AND MovieID = " << movieID;
    int count = db->executeUpdate(ss.str());
    return count > 0;
}

bool RatingController::deleteRating(int userID, int movieID)
{
    std::stringstream ss;
    ss << "DELETE FROM UserMovies WHERE UserID = " << userID << " AND MovieID = " << movieID;
    int count = db->executeUpdate(ss.str());
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