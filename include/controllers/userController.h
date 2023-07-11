#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include "db.h"
#include "user.h"
#include <memory>
#include <QObject>

class User;

class UserController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int currentUserId READ getCurrentUserId WRITE setCurrentUserId NOTIFY currentUserIdChanged)
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
    bool registerUser(const std::string &username, const std::string &password, int age);
    bool loginUser(const std::string &username, const std::string &password);
    bool isAuthenticated();

signals:
    void currentUserIdChanged(int value);

public slots:
    int getCurrentUserId() const;
    void setCurrentUserId(int value);

    Q_INVOKABLE bool registerUserQML(const QString &username, const QString &password, int age);
    Q_INVOKABLE bool loginUserQML(const QString &username, const QString &password);
};

#endif // USER_CONTROLLER_H