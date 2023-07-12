#ifndef MOVIE_H
#define MOVIE_H

#include <string>
#include <vector>
#include <iostream>
#include "nlohmann/json.hpp"

class Movie
{

public:
    Movie();
    Movie(const nlohmann::json &movieJson);

    bool adult;
    std::string backdrop_path;
    std::vector<int> genre_ids;
    int id;
    std::string original_language;
    std::string original_title;
    std::string overview;
    double popularity;
    std::string poster_path;
    std::string release_date;
    std::string title;
    bool video;
    double vote_average;
    int vote_count;

    void printAttributes() const;
};

#endif /* MOVIE_H */
