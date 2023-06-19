#ifndef USER_H
#define USER_H

#include <string>

class User
{
private:
    int id;
    std::string username;
    std::string password;
    int age;

public:
    User(int id, std::string username, std::string password, int age);

    // Getters
    int getId();
    std::string getUsername();
    std::string getPassword();
    int getAge();

    // Setters
    void setId(int id);
    void setUsername(std::string username);
    void setPassword(std::string password);
    void setAge(int age);
};

#endif // USER_H
