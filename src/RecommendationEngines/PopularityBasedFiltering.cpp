#include "engine.h"

std::vector<Movie> PopularityBasedStrategy::recommend(const User &user, int num_recommendations)
{
    return PopularityBasedStrategy::recommend(num_recommendations);
}

std::vector<Movie> PopularityBasedStrategy::recommend(int num_recommendations)
{
    std::vector<Movie> popularMovies;

    if (!movieController.fetchPopularMovies(popularMovies))
    {
        std::cerr << "Failed to fetch popular movies." << std::endl;
        return std::vector<Movie>(); // Return an empty vector on failure
    }

    if (popularMovies.size() > num_recommendations)
    {
        popularMovies.resize(num_recommendations); // Trim to the required number of recommendations
    }

    return popularMovies;
}
