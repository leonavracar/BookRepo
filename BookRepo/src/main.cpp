
#include "BookRepo.h"
#include <iostream>
#include "Menu.h"
#include "User.h"
#include "RoleSelector.h"

int main() {
    BookRepo repo("Test Repo");
    User user = selectUser();

    // Add some test books directly
    repo.newBook("The Giver", 1993, {"Lois Lowry"}, Genre::fantasy);
    repo.newBook("1984", 1949, {"George Orwell"}, Genre::fiction);
    repo.newBook("The Hobbit", 1937, {"J.R.R. Tolkien"}, Genre::fantasy);
    repo.newBook("Brief History of Time", 1988, {"Stephen Hawking"}, Genre::non_fiction);


    runInteractiveMenu(repo, user);
    
    
    return 0;
}
