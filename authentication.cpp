#include <iostream>
#include <string>

#include "authentication.h"

using namespace std;

void CmdAuthentication::showMenu()
{
    std::cout << "1. Register\n";
    std::cout << "2. Login\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice: ";
}

void CmdAuthentication::registerUser()
{
    string firstName, lastName, email, password;
    cout << "Enter your first name: ";
    cin >> firstName;
    cout << "Enter your last name: ";
    cin >> lastName;
    cout << "Enter your email: ";
    cin >> email;
    cout << "Enter your password: ";
    cin >> password;

    db.registerUser(firstName, lastName, email, password, authenicated);
}

void CmdAuthentication::loginUser()
{
    string email, password;

    cout << "Enter your email: ";
    cin >> email;
    cout << "Enter your password: ";
    cin >> password;
    db.loginUser(email, password, authenicated);
}

void CmdAuthentication::authenticate()
{
    int choice;

    showMenu();
    std::cin >> choice;

    switch (choice)
    {
    case 1:
        registerUser();
        break;
    case 2:
        loginUser();
        break;
    case 3:
        std::cout << "Goodbye!\n";
        return;
    default:
        std::cout << "Invalid choice. Please try again.\n";
        break;
    }
}

bool CmdAuthentication::isAuthenticated()
{
    return authenicated;
}