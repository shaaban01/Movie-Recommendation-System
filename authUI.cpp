#include <iostream>
#include <string>
#include "db.h"

using namespace std;



void showMenu() {
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
}

void registerUser() {
    string firstName, lastName, email, password;
    cout << "Enter your first name: ";
    cin >> firstName;
    cout << "Enter your last name: ";
    cin >> lastName;
    cout << "Enter your email: ";
    cin >> email;
    cout << "Enter your password: ";
    cin >> password;

    registerUser(firstName, lastName, email, password); 
}

void loginUser() {
    string email, password;
    cout << "Enter your email: ";
    cin >> email;
    cout << "Enter your password: ";
    cin >> password;
    loginUser(email, password);
}
