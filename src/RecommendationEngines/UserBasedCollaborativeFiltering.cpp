#include <algorithm>
#include <cmath>
#include "engine.h"
#include "user.h"

using RatingsForUser = std::map<int, float>;
using AllUserRatings = std::map<int, RatingsForUser>;
using AllUsers = std::map<int, User>;
using AllMovies = std::map<int, Movie>;
using UserIdSimilarityPair = std::pair<int, float>;

// Computes the cosine similarity between two users based on their ratings
float UserBasedCollaborativeFiltering::computeSimilarity(const User &user1, const User &user2)
{
    // Get the ratings of both users
    const RatingsForUser &ratings1 = ratings[user1.getId()];
    const RatingsForUser &ratings2 = ratings[user2.getId()];

    // Initialize variables for similarity calculation
    float dotProduct = 0.0, norm1 = 0.0, norm2 = 0.0;

    // Compute dot product and first norm
    for (const auto &kv : ratings1)
    {
        dotProduct += kv.second * ratings2.at(kv.first);
        norm1 += kv.second * kv.second;
    }

    // Compute second norm
    for (const auto &kv : ratings2)
    {
        norm2 += kv.second * kv.second;
    }

    // Return cosine similarity
    return dotProduct / (sqrt(norm1) * sqrt(norm2));
}

// Returns a vector of user IDs, sorted by their similarity to the given user
std::vector<int> UserBasedCollaborativeFiltering::getSimilarUsers(const User &user)
{
    // Initialize similarity vector
    std::vector<UserIdSimilarityPair> similarities;

    // Calculate similarity for each user and store it in the vector
    for (const auto &kv : users)
    {
        if (kv.first == user.getId())
            continue;
        similarities.push_back({kv.first, computeSimilarity(user, kv.second)});
    }

    // Sort the vector in descending order of similarity
    std::sort(similarities.begin(), similarities.end(),
              [](const UserIdSimilarityPair &a, const UserIdSimilarityPair &b)
              { return a.second > b.second; });

    // Extract the sorted user IDs
    std::vector<int> similarUserIds;
    for (const auto &kv : similarities)
    {
        similarUserIds.push_back(kv.first);
    }

    return similarUserIds;
}

// Predicts the rating that the given user would give the given movie
float UserBasedCollaborativeFiltering::predictRating(const User &user, const Movie &movie)
{
    // Get the similar users
    const std::vector<int> &similarUsers = getSimilarUsers(user);

    // Initialize sum variables
    float weightedSum = 0.0, sumSimilarities = 0.0;

    // Compute weighted sum and sum of similarities
    for (const int &userId : similarUsers)
    {
        const float sim = computeSimilarity(user, users[userId]);
        weightedSum += sim * ratings[userId][movie.id];
        sumSimilarities += sim;
    }

    // Return predicted rating
    return weightedSum / sumSimilarities;
}

// Recommends movies to the given user based on user-based collaborative filtering
std::vector<Movie> UserBasedCollaborativeFiltering::recommend(const User &user, const int num_recommendations)
{
    // Initialize vector for predicted ratings
    std::vector<UserIdSimilarityPair> predictedRatings;

    // Predict rating for each movie and store it in the vector
    for (const auto &kv : movies)
    {
        predictedRatings.push_back({kv.first, predictRating(user, kv.second)});
    }

    // Sort the vector in descending order of predicted rating
    std::sort(predictedRatings.begin(), predictedRatings.end(),
              [](const UserIdSimilarityPair &a, const UserIdSimilarityPair &b)
              { return a.second > b.second; });

    // Extract the top-rated movies
    std::vector<Movie> recommendations;
    for (int i = 0; i < num_recommendations && i < static_cast<int>(predictedRatings.size()); i++)
    {
        recommendations.push_back(movies[predictedRatings[i].first]);
    }

    std::cout << "User-based collaborative filtering recommendations for user:" << std::endl;
    for (const Movie &movie : recommendations)
    {
        std::cout << movie.title << std::endl;
    }

    return recommendations;
}
