#include <iostream>
#include "authentication.h"
#include "movieApiController.h"
#include "viewMovies.h"

int main()
{

    Authentication *auth = new CmdAuthentication();
    while (!auth->isAuthenticated())
    {
        auth->authenticate();
    }
    

    std::vector<Movie> movies;
    FetchPopularMovies(movies);

    ViewMovies *viewer = new CmdViewMovies(movies);
    viewer->Display();


    delete auth;
    delete viewer;
    return 0;
}
