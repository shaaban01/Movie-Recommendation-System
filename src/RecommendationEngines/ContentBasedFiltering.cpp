#include "engine.h"

float ContentBasedFiltering::calculateSimilarity(const User &user, const Movie &movie)
{
    float score = 0.0;

    // Calculate the score for genre
    for (auto genre : movie.genre_ids)
    {
        if (user.genre_preferences.find(genre) != user.genre_preferences.end())
        {
            score += user.genre_preferences[genre];
        }
    }

    // Calculate the score for language
    if (user.language_preferences.find(movie.original_language) != user.language_preferences.end())
    {
        score += user.language_preferences[movie.original_language];
    }

    return score;
}

std::vector<Movie> ContentBasedFiltering::recommend(const User &user, int num_recommendations)
{
    std::vector<std::pair<int, float>> movieScores;

    // Calculate similarity score for each movie
    for (auto &kv : movies)
    {
        movieScores.push_back({kv.first, calculateSimilarity(user, kv.second)});
    }

    // Sort movies based on the score
    std::sort(movieScores.begin(), movieScores.end(), [](std::pair<int, float> a, std::pair<int, float> b)
              { return a.second > b.second; });

    // Return the top num_recommendations movies
    std::vector<Movie> recommendations;
    for (int i = 0; i < num_recommendations && i < movieScores.size(); i++)
    {
        recommendations.push_back(movies[movieScores[i].first]);
    }

    return recommendations;
}
