#include "user.h"

User::User(int id, std::string username, std::string password, int age)
    : id(id), username(username), password(password), age(age) {}

int User::getId() { return id; }
std::string User::getUsername() { return username; }
std::string User::getPassword() { return password; }
int User::getAge() { return age; }

void User::setId(int id) { this->id = id; }
void User::setUsername(std::string username) { this->username = username; }
void User::setPassword(std::string password) { this->password = password; }
void User::setAge(int age) { this->age = age; }
