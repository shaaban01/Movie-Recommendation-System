#ifndef ENGINE_H
#define ENGINE_H

#include <vector>
#include "movie.h"
#include "user.h"
#include "movieController.h"

// The abstract RecommendationStrategy class
class RecommendationStrategy
{
public:
    virtual std::vector<Movie> recommend(const User &user, int num_recommendations) = 0;
};

class UserBasedCollaborativeFiltering : public RecommendationStrategy
{
private:
    std::map<int, User> users;                   // Users collection
    std::map<int, std::map<int, float>> ratings; // User-Item matr ix
    std::map<int, Movie> movies;                 // Movies collection
    float computeSimilarity(const User &user1, const User &user2);
    std::vector<int> getSimilarUsers(const User &user);
    float predictRating(const User &user, const Movie &movie);

public:
    UserBasedCollaborativeFiltering(std::map<int, User> &users, std::map<int, std::map<int, float>> &ratings, std::map<int, Movie> &movies)
        : users(users), ratings(ratings), movies(movies) {}

    std::vector<Movie> recommend(const User &user, int num_recommendations) override;
};

// TODO: Implement ContentBasedStrategy
// class ContentBasedStrategy : public RecommendationStrategy
// {
// public:
//     std::vector<Movie> recommend(const User &user, int num_recommendations) override;
// };

class PopularityBasedStrategy : public RecommendationStrategy
{
private:
    MovieController movieController;
    std::vector<Movie> recommend(int num_recommendations);

public:
    PopularityBasedStrategy(MovieController movieController) : movieController(movieController) {}
    std::vector<Movie> recommend(const User &user, int num_recommendations) override;
    
};

class RecommendationEngine
{
private:
    RecommendationStrategy *strategy;

public:
    RecommendationEngine(RecommendationStrategy *strategy) : strategy(strategy) {}
    void setStrategy(RecommendationStrategy *strategy) { this->strategy = strategy; }
    std::vector<Movie> recommend(const User &user, int num_recommendations)
    {
        return strategy->recommend(user, num_recommendations);
    }
};

#endif // ENGINE_H
