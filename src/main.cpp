#include <iostream>
#include <memory>
#include "authenticationController.h"
#include "movieApiController.h"
#include "ratingController.h"
#include "viewMovies.h"

int main()
{
    // std::unique_ptr<Authentication> auth = std::make_unique<CmdAuthentication>();
    // while (!auth->isAuthenticated())
    // {
    //     auth->authenticate();
    // }

    // std::vector<Movie> movies;
    // Movie movie;
    // std::unique_ptr<MovieApiController> movieController = std::make_unique<MovieApiController>();
    // movieController->FetchMoviesByTitle("The Matrix", movies);
    // movieController->FetchMovieById("508602", movie);
    // movie.printAttributes();
    // movieController->StoreMovie("508602");
    // std::unique_ptr<ViewMovies> viewer = std::make_unique<CmdViewMovies>(movies);
    // viewer->Display();
    std::unique_ptr<RatingController> ratingController = std::make_unique<RatingController>();
    if (ratingController->createRating(1, 508602, 8.5))
    {
        std::cout << "Rating created successfully\n";
    }
    else
    {
        std::cout << "Rating creation failed\n";
    }

    std::map<int, float> ratings = ratingController->getAllRatings(1);

    for (const auto &elem : ratings)
    {
        std::cout << elem.first << " " << elem.second << "\n";
    }
    return 0;
}