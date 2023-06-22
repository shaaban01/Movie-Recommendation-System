#ifndef MOVIE_FETCH_H
#define MOVIE_FETCH_H

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <curl/curl.h>
#include "nlohmann/json.hpp"
#include "movie.h"

class MovieController
{

public:
    // Fetches movie data from the TMDB API and stores the data in the provided vector of Movies.
    // Returns true if the fetch was successful, false otherwise.
    bool FetchMoviesByTitle(std::string movieName, std::vector<Movie> &movies);

    // Fetches the popular movies from the TMDB API and stores the data in the provided vector of Movies.
    // Returns true if the fetch was successful, false otherwise.
    bool FetchPopularMovies(std::vector<Movie> &movies);

    // Fetches the movie with the given ID from the TMDB API
    // Returns true if the fetch was successful, false otherwise.
    bool FetchMovieById(const std::string MovieId, Movie &movie);

    // store the specific movie in the database
    // Returns true if the store was successful, false otherwise.
    bool StoreMovie(const std::string MovieId);

    // retrieve all the movies from the database
    // Returns true if the retrieve was successful, false otherwise.
    bool GetAllMovies(std::map<std::string, Movie> &movies);

};
#endif /* MOVIE_FETCH_H */
