#include <iostream>
#include "db.h"
#include "authUI.h"

int main() {
    int choice;

    do {
        showMenu();
        std::cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2: {
                loginUser();
                break;
            }
            case 3:
                std::cout << "Goodbye!\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != 3);

    return 0;
}
