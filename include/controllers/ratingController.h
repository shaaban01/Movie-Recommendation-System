#ifndef RATING_CONTROLLER_H
#define RATING_CONTROLLER_H

#include <string>
#include <map>
#include <sstream>
#include <memory>
#include <QObject>
#include <QVariant>

#include "db.h"
#include "movieController.h"
#include "userController.h"
#include "movie.h"
#include "user.h"

class UserController;

class RatingController : public QObject
{
    Q_OBJECT
private:
    DB *db;
    std::unique_ptr<MovieController> movieController;
    std::unique_ptr<UserController> userController;

public:
    RatingController();

    // Create a new rating for a movie by a user.
    // If the rating already exists, it will be updated.
    bool addRating(int userID, std::string movieID, float rating);

    // Get a rating.
    float getRating(int userID, std::string movieID) const;

    // Get all ratings of a specific user.
    std::map<int, float> getAllRatings(int userID) const;

public slots:
    Q_INVOKABLE bool addRatingQML(int userID, const QString &movieID, float rating);
    Q_INVOKABLE float getRatingQML(int userID, const QString &movieID) const;
    Q_INVOKABLE QVariantList getAllRatingsQML(int userID) const;
};

#endif // RATING_CONTROLLER_H
