#include <string>
#include <map>

#ifndef DB_H
#define DB_H
#include "db.h"
#endif

class RatingController
{
private:
    DB *db;

public:
    RatingController();

    // Create a new rating.
    bool createRating(int userID, int movieID, float rating);

    // Update an existing rating.
    bool updateRating(int userID, int movieID, float newRating);

    // Delete a rating.
    bool deleteRating(int userID, int movieID);

    // Get a rating.
    float getRating(int userID, int movieID);

    // Get all ratings of a specific user.
    std::map<int, float> getAllRatings(int userID);
};
