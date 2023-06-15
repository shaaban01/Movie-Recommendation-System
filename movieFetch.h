#ifndef MOVIE_FETCH_H
#define MOVIE_FETCH_H

#include <iostream>
#include <string>
#include <curl/curl.h>
#include "nlohmann/json.hpp"
#include "movie.h"

// Fetches movie data from the TMDB API and stores the data in the provided vector of Movies.
// Returns true if the fetch was successful, false otherwise.
bool FetchMovieData(std::string movieName, std::vector<Movie> &movies);

#endif /* MOVIE_FETCH_H */
