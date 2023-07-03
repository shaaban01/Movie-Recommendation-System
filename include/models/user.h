#ifndef USER_H
#define USER_H

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "ratingController.h"

class RatingController;
class User
{
private:
    int id;
    std::string username;
    std::string password;
    int age;
    RatingController *ratingController;

public:
    User() : id(0), username(""), password(""), age(0) {}
    User(int id, std::string username, std::string password, int age);

    // Getters
    int getId() const;
    std::string getUsername() const;
    std::string getPassword() const;
    int getAge() const;

    // Setters
    void setId(int id);
    void setUsername(std::string username);
    void setPassword(std::string password);
    void setAge(int age);

    // For User-Based Collaborative Filtering
    std::map<int, float> getRatings(); // Use the RatingController to get ratings

    // For Content-Based Filtering
    std::map<int, float> genre_preferences;
    std::map<std::string, float> language_preferences;
};

#endif // USER_H
