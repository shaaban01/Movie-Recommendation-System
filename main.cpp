#include <iostream>
#include "authentication.h"
#include "movieFetch.h"
#include "viewMovies.h"

int main()
{

    Authentication *auth = new CmdAuthentication();
    while (!auth->isAuthenticated())
    {
        auth->authenticate();
    }
    

    std::string movieName = "Fight";
    std::vector<Movie> movies;
    FetchMovieData(movieName, movies);

    ViewMovies *viewer = new CmdViewMovies(movies);
    viewer->Display();


    delete auth;
    delete viewer;
    return 0;
}
