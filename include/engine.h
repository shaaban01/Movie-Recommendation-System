#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include <map>
#include "movie.h"
#include "user.h"
#include "movieController.h"

// Abstract class that forms the base for all recommendation strategies.
class RecommendationStrategy
{
public:
    // Pure virtual function to provide recommendations based on a user and a number of recommendations.
    virtual std::vector<Movie> recommend(const User &user, int num_recommendations) = 0;
};

// Recommendation strategy based on user collaborative filtering.
// Recommendations are based on the similarity between users.
class UserBasedCollaborativeFiltering : public RecommendationStrategy
{
private:
    std::map<int, User> users;                   // Collection of users
    std::map<int, std::map<int, float>> ratings; // User-Item matrix for ratings
    std::map<int, Movie> movies;                 // Collection of movies

    // Compute the similarity between two users.
    float computeSimilarity(const User &user1, const User &user2);

    // Get a vector of users who are similar to the provided user.
    std::vector<int> getSimilarUsers(const User &user);

    // Predict the rating of a movie by a user.
    float predictRating(const User &user, const Movie &movie);

public:
    // Constructor that initializes user collection, ratings, and movie collection.
    UserBasedCollaborativeFiltering(std::map<int, User> &users, std::map<int, std::map<int, float>> &ratings, std::map<int, Movie> &movies)
        : users(users), ratings(ratings), movies(movies) {}

    // Provide movie recommendations for the given user.
    std::vector<Movie> recommend(const User &user, int num_recommendations) override;
};

// Recommendation strategy based on content filtering.
// Recommendations are based on the similarity between a user preferences and a movie.
class ContentBasedFiltering : public RecommendationStrategy
{
private:
    std::map<int, User> users;   // Collection of users
    std::map<int, Movie> movies; // Collection of movies

    // Calculate the similarity between a user and a movie.
    float calculateSimilarity(const User &user, const Movie &movie);

public:
    // Constructor that initializes user collection and movie collection.
    ContentBasedFiltering(std::map<int, User> &users, std::map<int, Movie> &movies)
        : users(users), movies(movies) {}

    // Provide movie recommendations for the given user.
    std::vector<Movie> recommend(const User &user, int num_recommendations) override;
};

// Recommendation strategy based on movie popularity.
class PopularityBasedStrategy : public RecommendationStrategy
{
private:
    MovieController movieController;
    std::vector<Movie> recommend(int num_recommendations);

public:
    // Constructor that initializes the MovieController.
    PopularityBasedStrategy(MovieController movieController) : movieController(movieController) {}

    // Provide movie recommendations for the given user.
    std::vector<Movie> recommend(const User &user, int num_recommendations) override;
};

// Recommendation engine that utilizes a recommendation strategy to provide movie recommendations.
class RecommendationEngine
{
private:
    RecommendationStrategy *strategy; // Pointer to the strategy being used.

public:
    // Constructor that initializes the recommendation strategy.
    RecommendationEngine(RecommendationStrategy *strategy) : strategy(strategy) {}

    // Setter for the recommendation strategy.
    void setStrategy(RecommendationStrategy *strategy) { this->strategy = strategy; }

    // Provides movie recommendations using the current strategy.
    std::vector<Movie> recommend(const User &user, int num_recommendations)
    {
        return strategy->recommend(user, num_recommendations);
    }
};

#endif // ENGINE_H
