#include "BookRepo.h"
#include "Genre.h"
#include "utils.h"
#include <iostream>
#include <map>
#include <string>
#include "Book.h"
#include "User.h"
#include "UserState.h"
#include <fstream>
#include <sstream>

static const User* g_currentUser = nullptr;

void addBook(BookRepo& i_repo) {
    std::string i_title;
    std::cout << "Enter book title: " << std::endl;
    std::getline(std::cin >> std::ws, i_title);

    int i_year = readInt("Enter year of publishing: ");

    std::vector<std::string> i_authors;
    std::string str_authors;
    std::cout << "Enter full author name(s) (comma separated): " << std::endl;
    std::getline(std::cin >> std::ws, str_authors);
    i_authors = splitCommaSeparated(str_authors);
    
    printAvailableGenres();
    std::string str_genre;
    std::cout << "Enter genre: " << std::endl;
    std::getline(std::cin >> std::ws, str_genre);
    Genre i_genre = parseGenre(str_genre);

    Book* addedBook = i_repo.newBook(i_title, i_year, i_authors, i_genre);
        if (addedBook)
        std::cout << "Book added successfully.\n";
    else
        std::cout << "Book already exists or an error occurred.\n";
}

void deleteBook(BookRepo& i_repo) 
{   std::string i_bookID;
    std::cout << "Enter bookID of the book to be deleted: " << std::endl;

    std::cin >> i_bookID;
    
    int int_bookID = std::stoi(i_bookID);
    Book* p_book = i_repo.bookPointerByID(int_bookID);

    if (!p_book) {std::cout << "Book with ID " << int_bookID << " not found.\n"; return;}

    std::cout << "Deleting: " << '\n';
    p_book->display();
    std::cout <<'\n' << "Do you wish to proceed? (y/n)? \n";
    char confirm;
    std::cin >> confirm;

    if (confirm == 'y' || confirm == 'Y') {
    bool success = i_repo.deleteBookByID(int_bookID);
    std::cout << (success ? "Book deleted.\n" : "Deletion failed.\n");
    } else {
    std::cout << "Deletion cancelled.\n";
    }
}

void displayBooks(BookRepo& i_repo) {i_repo.displayAll();}

void displayAuthors(BookRepo& i_repo) {i_repo.displayAllAuthors();}

void load(BookRepo& i_repo) 
{
    std::cout << "Enter file path to load from: " << std::endl;
    std::string input;
    std::cin >> input;
    i_repo.loadFromFile(input);
}

void save(BookRepo& i_repo) 
{
    std::cout << "Enter file path to save the data into: " << std::endl;
    std::string input;
    std::cin >> input;
    i_repo.saveToFile(input);
}

void help(BookRepo& i_repo) {
    std::cout << "Commands available:\n";
    std::cout << "  help              - Show this help menu\n";
    std::cout << "  display           - Display all books\n";
    std::cout << "  display_authors   - Show all authors and their book count\n";
    std::cout << "  quit              - Exit the program\n";

    if (g_currentUser && g_currentUser->canAddDelete()) {
        std::cout << "  add_book          - Add a new book\n";
        std::cout << "  delete_book       - Delete a book by ID\n";
        std::cout << "  save              - Save repo to file\n";
        std::cout << "  load              - Load repo from file\n";
    }

    std::cout << '\n';
    (void)i_repo;
}


typedef void (*operationFunctionPointerType) (BookRepo& i_repo);

void runInteractiveMenu(BookRepo& i_repo, const User& i_user) 
{   
    std::map<std::string, operationFunctionPointerType>  mapCommands;
    g_currentUser = &i_user;
    mapCommands["add_book"] = &addBook;
    mapCommands["display"] = &displayBooks;
    mapCommands["display_authors"] = &displayAuthors;
    mapCommands["delete_book"] = &deleteBook;
    mapCommands["save"] = &save;
    mapCommands["load"] = &load;
    mapCommands["help"] = &help;

    std::cout << "Welcome to the Book Repository!" << std::endl;
    wait();
    std::cout << "Logged in as: " << i_user.getRoleName() << '\n';
    wait();
    std::cout << "Type a command (help to list commands):\n ";
    std::string input;
    while (std::cin >> input && input != "quit") 
    {
        if (mapCommands.count(input) == 0) 
        {
            std::cout << "Invalid input!" << std::endl;
            continue;
        }
        if ((input == "add_book" || input == "delete_book" || input == "load" || input == "save") && !i_user.canAddDelete()) {
            std::cout << "Access denied: Only Admins can perform this action.\n";
            continue;
        }
        
        mapCommands[input](i_repo);
        std::cout << "Ready for next input..." << std::endl;

    }

    std::cout << "Bye" << std::endl;
}


