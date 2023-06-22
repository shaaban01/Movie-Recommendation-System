
#ifndef DB_H
#define DB_H
#include "db.h"
#endif
#include "user.h"
#include <memory>

class UserController
{
private:
    DB *db;
    bool authenticated = false;

public:
    UserController();

    // User operations
    std::unique_ptr<User> getUser(int userId);
    bool createUser(const std::string &username, const std::string &password, int age);
    bool deleteUser(int userId);
    bool updateUser(User &user);

    // Authentication operations
    void registerUser(const std::string &username, const std::string &password, int age);
    bool loginUser(const std::string &username, const std::string &password);
    bool isAuthenticated();
};
