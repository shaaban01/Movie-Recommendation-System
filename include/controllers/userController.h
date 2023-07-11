#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include "db.h"
#include "user.h"
#include <memory>

class User;

class UserController
{
private:
    DB *db;
    bool authenticated = false;

public:
    int currentUserId = -1;

    UserController();
    // User operations
    std::unique_ptr<User> getUser(int userId);
    bool createUser(const std::string &username, const std::string &password, int age);
    bool deleteUser(int userId);
    bool updateUser(std::unique_ptr<User> &user);

    // Authentication operations
    void registerUser(const std::string &username, const std::string &password, int age);
    bool loginUser(const std::string &username, const std::string &password);
    bool isAuthenticated();
};

#endif // USER_CONTROLLER_H