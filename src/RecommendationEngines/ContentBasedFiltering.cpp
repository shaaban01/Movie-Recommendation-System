#include "engine.h"
#include <iostream>

using GenrePreferences = std::map<int, float>;
using LanguagePreferences = std::map<std::string, float>;
using MovieCollection = std::map<int, Movie>;
using MovieScorePair = std::pair<int, float>;

// Calculates the similarity between a user and a movie based on genre and language preferences
float ContentBasedFiltering::calculateSimilarity(const User &user, const Movie &movie)
{
    float similarityScore = 0.0;

    // Calculate the score for genres
    for (const auto &genre : movie.genre_ids)
    {
        if (user.genre_preferences.find(genre) != user.genre_preferences.end())
        {
            similarityScore += user.genre_preferences.at(genre);
        }
    }

    // Calculate the score for language
    if (user.language_preferences.find(movie.original_language) != user.language_preferences.end())
    {
        similarityScore += user.language_preferences.at(movie.original_language);
    }

    return similarityScore;
}

// Returns a vector of movie recommendations for the given user based on content-based filtering
std::vector<Movie> ContentBasedFiltering::recommend(const User &user, int num_recommendations)
{
    // Initialize vector for movie similarity scores
    std::vector<MovieScorePair> movieScores;

    // Calculate similarity score for each movie and store it in the vector
    for (const auto &kv : movies)
    {
        movieScores.push_back({kv.first, calculateSimilarity(user, kv.second)});
    }

    // Sort the vector in descending order of similarity score
    std::sort(movieScores.begin(), movieScores.end(),
              [](const MovieScorePair &a, const MovieScorePair &b)
              { return a.second > b.second; });

    // Extract the top-rated movies
    std::vector<Movie> recommendations;
    for (int i = 0; i < num_recommendations && i < static_cast<int>(movieScores.size()); i++)
    {
        recommendations.push_back(movies[movieScores[i].first]);
    }

    std::cout << "Content-based filtering recommendations for user :" << std::endl;
    for (const auto &movie : recommendations)
    {
        std::cout << movie.title << std::endl;
    }

    return recommendations;
}
