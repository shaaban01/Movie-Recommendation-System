#include <iostream>
#include <string>

#include "authenticationController.h"

using namespace std;

CmdAuthentication::CmdAuthentication()
{
    userController = new UserController();
    authenicated = false;
}

void CmdAuthentication::showMenu()
{
    std::cout << "1. Register\n";
    std::cout << "2. Login\n";
    std::cout << "3. Exit\n";
    std::cout << "Enter your choice: ";
}

void CmdAuthentication::registerUser()
{
    string userName, password;
    int age;
    cout << "Enter your userName: ";
    cin >> userName;
    cout << "Enter your password: ";
    cin >> password;
    cout << "Enter your age: ";
    cin >> age;

    userController->registerUser(userName, password, age);
    authenicated = userController->isAuthenticated();
}

void CmdAuthentication::loginUser()
{
    string username, password;

    cout << "Enter your username: ";
    cin >> username;
    cout << "Enter your password: ";
    cin >> password;
    userController->loginUser(username, password);
    authenicated = userController->isAuthenticated();
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