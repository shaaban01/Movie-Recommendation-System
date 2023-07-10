#include "userController.h"
#include <sstream>

UserController::UserController(QObject *parent) : QObject(parent)
{
    db = DB::getInstance();
}

UserController::~UserController()
{
    // nothing to clean up
}

int UserController::getUserId()
{
    return currentUserId;
}

void UserController::setUserId(int userId)
{
    currentUserId = userId;
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

int UserController::createUser(const std::string &username, const std::string &password, int age)
{
    std::stringstream query;
    query << "INSERT INTO Users(UserName, Password, Age) VALUES('" << username << "','" << password << "'," << age << ")";

    int rowsAffected = db->executeUpdate(query.str());

    if (rowsAffected > 0)
    {

        setUserId(db->getLastInsertId());
        return getUserId();
    }
    else
    {
        // Return -1 to indicate failure
        return -1;
    }
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

bool UserController::isAuthenticated()
{
    return authenticated;
}

int UserController::loginUser(const std::string &username, const std::string &password)
{
    std::stringstream query;
    query << "SELECT * FROM Users WHERE UserName='" << username << "' AND Password='" << password << "'";

    sql::ResultSet *res = db->executeQuery(query.str());

    if (res->next())
    {
        std::cout << "Login successful!\n";
        authenticated = true;

        // Return the user ID of the logged-in user
        setUserId(res->getInt("UserID"));
        return getUserId();
    }
    else
    {
        std::cout << "Login failed!\n";
        emit loginFailed();

        // Return -1 to indicate failure
        return -1;
    }
}

int UserController::loginUser(const QString &username, const QString &password)
{
    int userId = loginUser(username.toStdString(), password.toStdString());

    if (userId != -1)
    {
        emit loginSuccessful();
    }
    else
    {
        emit loginFailed();
    }

    return userId;
}

int UserController::registerUser(const QString &username, const QString &password, int age)
{
    int userId = createUser(username.toStdString(), password.toStdString(), age);
    if (userId != -1)
    {
        emit registrationSuccessful();
    }
    else
    {
        emit registrationFailed();
    }
    return userId;
}