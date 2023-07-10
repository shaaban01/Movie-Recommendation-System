#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include <memory>
#include <QObject>
#include "db.h"
#include "user.h"

class User;

class UserController : public QObject
{
    Q_OBJECT
private:
    DB *db;
    bool authenticated = false;

public:
    explicit UserController(QObject *parent = nullptr);
    ~UserController() override;
    // User operations
    std::unique_ptr<User> getUser(int userId);

    // will return the user id if successful, -1 otherwise
    int createUser(const std::string &username, const std::string &password, int age);
    bool deleteUser(int userId);
    bool updateUser(std::unique_ptr<User> &user);

    // Authentication operations:

    // will return the user id if successful, -1 otherwise
    void registerUser(const std::string &username, const std::string &password, int age);

    // will return the user id if successful, -1 otherwise
    int loginUser(const std::string &username, const std::string &password) ;

    bool isAuthenticated();

    // QML invokable methods
    Q_INVOKABLE int loginUser(const QString &username, const QString &password);
    Q_INVOKABLE int registerUser(const QString &username, const QString &password, int age);

signals:
    void loginSuccessful();
    void loginFailed();
    void registrationSuccessful();
    void registrationFailed();
};

#endif // USER_CONTROLLER_H
