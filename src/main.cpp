#include <iostream>
#include <memory>
#include "authenticationController.h"
#include "movieController.h"
#include "movieView.h"
#include "engine.h"

int main()
{
    UserController *userController = new UserController();

    userController->createUser("Mo2", "pass1234", 30);
    // std::unique_ptr<Authentication> auth = std::make_unique<CmdAuthentication>();
    // while (!auth->isAuthenticated())
    // {
    //     auth->authenticate();
    // }

    // // Assuming that authentication is successful and a user object is returned
    // UserController userController;
    // std::unique_ptr<User> user = userController.getUser(1); // Assuming 1 is the authenticated user's ID

    // // Recommendation Engine Configuration
    // MovieController movieController;
    // std::map<int, Movie> allMovies;
    // if (movieController.GetAllMovies(allMovies))
    // {
    //     // Create the Recommendation Strategy
    //     UserBasedCollaborativeFiltering ucfStrategy(user->getRatings(), allMovies);
    //     RecommendationEngine recommendationEngine(&ucfStrategy);

    //     // Get Recommendations
    //     std::vector<Movie> recommendations = recommendationEngine.recommend(*user, 5); // Assuming you want 5 recommendations

    //     // Display Recommendations
    //     for (Movie &movie : recommendations)
    //     {
    //         movie.printAttributes();
    //     }
    // }
    // else
    // {
    //     std::cout << "Failed to fetch all movies\n";
    // }

    return 0;
}
