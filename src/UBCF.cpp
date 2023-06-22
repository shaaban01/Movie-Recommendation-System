#include <algorithm>
#include <cmath>
#include "engine.h"
#include "user.h"

float UserBasedCollaborativeFiltering::computeSimilarity(const User &user1, const User &user2)
{
    std::map<int, float> ratings1 = ratings[user1.getId()];
    std::map<int, float> ratings2 = ratings[user2.getId()];

    float dotProduct = 0.0, norm1 = 0.0, norm2 = 0.0;
    for (auto &kv : ratings1)
    {
        dotProduct += kv.second * ratings2[kv.first];
        norm1 += kv.second * kv.second;
    }

    for (auto &kv : ratings2)
    {
        norm2 += kv.second * kv.second;
    }

    return dotProduct / (sqrt(norm1) * sqrt(norm2));
}

std::vector<int> UserBasedCollaborativeFiltering::getSimilarUsers(const User &user)
{
    std::vector<std::pair<int, float>> similarities;
    for (auto &kv : users)
    {
        if (kv.first == user.getId())
            continue;
        similarities.push_back({kv.first, computeSimilarity(user, kv.second)});
    }

    std::sort(similarities.begin(), similarities.end(), [](std::pair<int, float> a, std::pair<int, float> b)
              { return a.second > b.second; });

    std::vector<int> similarUserIds;
    for (auto &kv : similarities)
    {
        similarUserIds.push_back(kv.first);
    }

    return similarUserIds;
}

float UserBasedCollaborativeFiltering::predictRating(const User &user, const Movie &movie)
{
    std::vector<int> similarUsers = getSimilarUsers(user);
    float weightedSum = 0.0, sumSimilarities = 0.0;

    for (int userId : similarUsers)
    {
        float sim = computeSimilarity(user, users[userId]);
        weightedSum += sim * ratings[userId][movie.id];
        sumSimilarities += sim;
    }

    return weightedSum / sumSimilarities;
}

std::vector<Movie> UserBasedCollaborativeFiltering::recommend(const User &user, int num_recommendations)
{
    std::vector<std::pair<int, float>> predictedRatings;
    for (auto &kv : movies)
    {
        predictedRatings.push_back({kv.first, predictRating(user, kv.second)});
    }

    std::sort(predictedRatings.begin(), predictedRatings.end(), [](std::pair<int, float> a, std::pair<int, float> b)
              { return a.second > b.second; });

    std::vector<Movie> recommendations;
    for (int i = 0; i < num_recommendations && i < predictedRatings.size(); i++)
    {
        recommendations.push_back(movies[predictedRatings[i].first]);
    }

    return recommendations;
}
