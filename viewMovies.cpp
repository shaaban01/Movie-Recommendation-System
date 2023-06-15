#include <iostream>
#include "viewMovies.h"

void CmdViewMovies::Display()
{
    for (const auto& movie : movies_)
    {
        std::cout << "Movie title: " << movie.title << '\n';
        std::cout << "Release date: " << movie.release_date << '\n';
        std::cout << "Overview: " << movie.overview << "\n\n";
    }
}
