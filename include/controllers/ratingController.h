#ifndef RATING_CONTROLLER_H
#define RATING_CONTROLLER_H

#include <string>
#include <map>
#include <sstream>
#include <memory>

#include "db.h"
#include "movieController.h"
#include "userController.h"
#include "movie.h"
#include "user.h"

class UserController;

class RatingController
{
private:
    DB *db;
    std::unique_ptr<MovieController> movieController;
    std::unique_ptr<UserController> userController;

public:
    RatingController();

    // Create a new rating.
    bool createRating(int userID, std::string movieID, float rating);

    // Update an existing rating.
    bool updateRating(int userID, std::string movieID, float newRating);

    // Delete a rating.
    bool deleteRating(int userID, std::string movieID);

    // Get a rating.
    float getRating(int userID, std::string movieID) const;

    // Get all ratings of a specific user.
    std::map<int, float> getAllRatings(int userID) const;
};

#endif // RATING_CONTROLLER_H
