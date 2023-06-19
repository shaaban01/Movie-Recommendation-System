#include <iostream>
#include <memory>
#include "authentication.h"
#include "movieApiController.h"
#include "viewMovies.h"

int main()
{
    // std::unique_ptr<Authentication> auth = std::make_unique<CmdAuthentication>();
    // while (!auth->isAuthenticated())
    // {
    //     auth->authenticate();
    // }

    std::vector<Movie> movies;
    FetchPopularMovies(movies);

    std::unique_ptr<ViewMovies> viewer = std::make_unique<CmdViewMovies>(movies);
    viewer->Display();

    return 0;
}
