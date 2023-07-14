#include "userController.h"
#include <sstream>
#include <iostream>

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
    currentUserId = db->getLastInsertId();
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

    // Update genre preferences
    for (const auto &genrePref : user->genre_preferences)
    {
        std::stringstream genreQuery;
        genreQuery << "INSERT INTO UserGenrePreferences (UserID, GenreID, PreferenceScore) VALUES (" << user->getId() << ", " << genrePref.first << ", " << genrePref.second << ") ";
        genreQuery << "ON DUPLICATE KEY UPDATE PreferenceScore=" << genrePref.second;

        db->executeUpdate(genreQuery.str());
    }

    // Update language preferences
    for (const auto &langPref : user->language_preferences)
    {
        std::stringstream langQuery;
        langQuery << "INSERT INTO UserLanguagePreferences (UserID, Language, PreferenceScore) VALUES (" << user->getId() << ", '" << langPref.first << "', " << langPref.second << ") ";
        langQuery << "ON DUPLICATE KEY UPDATE PreferenceScore=" << langPref.second;

        db->executeUpdate(langQuery.str());
    }

    return rowsAffected > 0;
}

bool UserController::registerUser(const std::string &username, const std::string &password, int age)
{
    if (createUser(username, password, age))
    {
        std::cout << "Registration successful!\n";
        authenticated = true;
        return true;
    }
    else
    {
        std::cout << "Registration failed!\n";
        return false;
    }
}

bool UserController::loginUser(const std::string &username, const std::string &password)
{
    std::cout << "Logging in...\n";

    std::stringstream query;
    query << "SELECT * FROM Users WHERE UserName='" << username << "' AND Password='" << password << "'";

    sql::ResultSet *res = db->executeQuery(query.str());

    if (res->next())
    {
        std::cout << "Login successful!\n";
        authenticated = true;

        currentUserId = res->getInt("UserID");
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

int UserController::getCurrentUserId() const
{
    return currentUserId;
}

void UserController::setCurrentUserId(int value)
{
    currentUserId = value;
    emit currentUserIdChanged(value);
}

bool UserController::registerUserQML(const QString &username, const QString &password, int age)
{
    return registerUser(username.toStdString(), password.toStdString(), age);
}

bool UserController::loginUserQML(const QString &username, const QString &password)
{
    return loginUser(username.toStdString(), password.toStdString());
}

User UserController::getUserQML(int userId)
{
    return *getUser(userId);
}

std::map<int, User> UserController::getAllUsers()
{
    std::map<int, User> users;

    std::stringstream query;
    query << "SELECT * FROM Users";

    sql::ResultSet *res = db->executeQuery(query.str());

    while (res->next())
    {
        users[res->getInt("UserID")] = User(res->getInt("UserID"), res->getString("UserName"), res->getString("Password"), res->getInt("Age"));
    }

    return users;
}