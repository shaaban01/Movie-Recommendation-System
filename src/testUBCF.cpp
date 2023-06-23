#include "movie.h"
#include "user.h"
#include "engine.h"

int main()
{
    // Initialize users and ratings. Normally this would be done by reading from a file or a database.
    std::map<int, User> users;
    std::map<int, std::map<int, float>> ratings;
    std::map<int, Movie> movies;

    // This is just dummy data
    users[1] = User(1, "user1", "password1", 30);
    users[2] = User(2, "user2", "password2", 25);
    users[3] = User(2, "user3", "password3", 25);
    Movie movie1 = Movie();
    movie1.id = 1;
    movie1.title = "movie1";
    Movie movie2 = Movie();
    movie2.id = 2;
    movie2.title = "movie2";
    Movie movie3 = Movie();
    movie3.id = 3;
    movie3.title = "movie3";

    movies[1] = movie1;
    movies[2] = movie2;
    movies[3] = movie3;

    ratings[1][1] = 5.0;
    ratings[1][2] = 1.0;
    ratings[1][3] = 4.0;
    ratings[2][1] = 2.0;
    ratings[2][2] = 2.0;
    ratings[2][3] = 4.0;
    ratings[3][1] = 5.0;

    // Create UserBasedCollaborativeFiltering object
    UserBasedCollaborativeFiltering ubcf(users, ratings, movies);

    // Get recommendation for user1
    User user = users[3];
    std::vector<Movie> recommendations = ubcf.recommend(user, 2);

    // Print out recommended movies
    for (const Movie &movie : recommendations)
    {
        std::cout << "Recommended movie: " << movie.title << std::endl;
    }

    return 0;
}
