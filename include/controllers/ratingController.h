#include <string>
#include <map>
#include <sstream>

#ifndef DB_H
#define DB_H
#include "db.h"
#endif
#include "movieController.h"
#include "movie.h"
#include "user.h"
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
    float getRating(int userID, int movieID) const;

    // Get all ratings of a specific user.
    std::map<int, float> getAllRatings(int userID) const;
};
