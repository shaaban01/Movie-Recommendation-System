#include "user.h"

User::User(int id, std::string username, std::string password, int age)
    : id(id), username(username), password(password), age(age) {}

int User::getId() const { return id; }
std::string User::getUsername() const { return username; }
std::string User::getPassword() const { return password; }
int User::getAge() const { return age; }

void User::setId(int id) { this->id = id; }
void User::setUsername(std::string username) { this->username = username; }
void User::setPassword(std::string password) { this->password = password; }
void User::setAge(int age) { this->age = age; }

std::map<int, float> User::getRatings()
{
    return ratingController.getAllRatings(id);
}