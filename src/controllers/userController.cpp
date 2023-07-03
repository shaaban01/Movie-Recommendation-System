#include "userController.h"
#include <sstream>

UserController::UserController()
{
    db = DB::getInstance();
}

std::unique_ptr<User> UserController::getUser(int userId)
{
    std::stringstream query;
    query << "SELECT * FROM Users WHERE UserID=" << userId;

    sql::ResultSet *res = db->executeQuery(query.str());

    if (res->next())
    {
        return std::make_unique<User>(res->getInt("UserID"), res->getString("UserName"), res->getString("Password"), res->getInt("Age"));
    }

    return nullptr;
}

bool UserController::createUser(const std::string &username, const std::string &password, int age)
{
    std::stringstream query;
    query << "INSERT INTO Users(UserName, Password, Age) VALUES('" << username << "','" << password << "'," << age << ")";

    int rowsAffected = db->executeUpdate(query.str());

    return rowsAffected > 0;
}

bool UserController::deleteUser(int userId)
{
    std::stringstream query;
    query << "DELETE FROM Users WHERE UserID=" << userId;

    int rowsAffected = db->executeUpdate(query.str());

    return rowsAffected > 0;
}

bool UserController::updateUser(std::unique_ptr<User> &user)
{
    std::stringstream query;
    query << "UPDATE Users SET UserName='" << user->getUsername() << "', Password='" << user->getPassword() << "', Age=" << user->getAge() << " WHERE UserID=" << user->getId();

    int rowsAffected = db->executeUpdate(query.str());

    return rowsAffected > 0;
}

void UserController::registerUser(const std::string &username, const std::string &password, int age)
{
    if (createUser(username, password, age))
    {
        std::cout << "Registration successful!\n";
        authenticated = true;
    }
    else
    {
        std::cout << "Registration failed!\n";
    }
}

bool UserController::loginUser(const std::string &username, const std::string &password)
{
    std::stringstream query;
    query << "SELECT * FROM Users WHERE UserName='" << username << "' AND Password='" << password << "'";

    sql::ResultSet *res = db->executeQuery(query.str());

    if (res->next())
    {
        std::cout << "Login successful!\n";
        authenticated = true;
        return true;
    }
    else
    {
        std::cout << "Login failed!\n";
        return false;
    }
}

bool UserController::isAuthenticated()
{
    return authenticated;
}