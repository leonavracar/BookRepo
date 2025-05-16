#include "RoleSelector.h"
#include <iostream>

// Static role instances
static AdminState admin;
static CustomerState customer;

User selectUser() {
    std::string role;

    while (true) {
        std::cout << "Enter role (admin/customer): ";
        std::cin >> role;

        if (role == "admin") {
            return User(&admin);
        } else if (role == "customer") {
            return User(&customer);
        } else {
            std::cout << "Invalid role. Please try again.\n";
        }
    }
}
