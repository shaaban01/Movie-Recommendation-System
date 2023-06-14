#ifndef DB_H
#define DB_H

#include <string>

// Function prototypes
void registerUser(const std::string& firstName, const std::string& lastName, const std::string& email, const std::string& password);
void loginUser(const std::string& email, const std::string& password);

#endif  // DB_H
