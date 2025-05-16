#pragma once
#include <string>
#include <vector>
#include "Book.h"
#include "Author.h"
#include <unordered_map>
#include <unordered_set>
#include <cctype>
#include <algorithm>
#include <iomanip>
/**
*@brief 
* BookRepo manages creation, deletion and garbage collection of books and authors.
* BookRepo has member variables vectors of pointers of all authors, books.
* BookRepo has member variables unordered maps of author full name + author pointer, authorID + author pointer.
* Only BookRepo can create new books and authors.
* Authors can only be created when a book is created. An author exists as long as there is at least 1 book by them in the system (RefCount != 0).
* Deleting a book means deleting its authors only if the above condition is true.
*/

class BookRepo {
    private:
        std::string m_repoName;
        std::vector<Book*> m_repoBooks;
        std::vector <Author*> m_repoAuthors;
        
        // For cheaper iteration over authors -> unordered maps/sets
        // Full name of author (lowercase with trailing spaces removed) -> Author pointer
        std::unordered_map<std::string, Author*> m_authorLookup;
        // Author ID -> Author pointer
        std::unordered_map<unsigned int, Author*> m_authorIDLookup;

        // For book lookup, we will create a unique identifier w title, AuthorID using helper function
        std::unordered_set<std::string> m_bookKeys; // Will look like "Title_2-5-4"

    public:
        // c'tor
        BookRepo(const std::string& i_repoName);
        // d'tor
        virtual ~BookRepo();
        // delete default c'tor, copy c'tor , assignment operator
        BookRepo() = delete;
        BookRepo(const BookRepo& i_bookRepo) = delete;
        BookRepo& operator=(const BookRepo& i_other) = delete;

        // getters
        const std::string& getRepoName() const;
        Book* bookPointerByID(int i_bookID) const;

        // setter
        void setReponame(const std::string& i_repoName);

        // Display
        void displayAll() const;
        void displayAllAuthors() const;
        
    // Main Methods
        /* newBook -> creates a new book in the BookRepo if the book doesn't exist
        - Takes title, year, {author1, author2}, Genre::undefined
        - Existence of a book is checked using an unordered set of keys, m_bookKeys
        - Existence of an author is checked using an unordered map of author keys, m_authorLookup
        * deleteBookByID -> deletes the book object and deletes associated authors (if their counter = 0)
        * saveToFile -> saves books as "The Hobbit;Fantasy;1937;J.R.R. Tolkien"
        * loadFromFile -> loads from same format, creates new objects
        */ 
        Book* newBook(const std::string& i_title, int i_year, const std::vector<std::string>& i_authorsFullNames, Genre genre = Genre::undefined);
        bool deleteBookByID(int i_bookID);
        void saveToFile(const std::string& filePath);
        void loadFromFile(const std::string& filePath);


    // Helper methods
    private:
        // Methods for authors
        // splitName -> turns "First Last" into {"First", "Last"}
        std::pair<std::string, std::string> splitName(const std::string& i_authorFullName);
        std::string makeAuthorKey( const std::pair<std::string, std::string>& i_authorSplitName);
        
        // Author* AuthorExists -> search unordered_map return Author* if key exists, if not return nullptr
        Author* authorExists(const std::string& i_authorKey );
        // Author* NewAuthor (takes output of splitName and makes new author) -> pointer to new author
        Author* newAuthor(const std::pair<std::string, std::string>& i_authorSplitName);
        void deleteAuthorZeroCount(Author* p_author);
        
        //Methods for books
        // trim -> trims trailing and leading whitespaces
        std::string trim(const std::string& i_string);
        // creates a book key with title (lowercase) and sorted authorID's separated with _
        std::string makeBookKey(const std::string& i_title, const std::vector<Author*>& i_authors);
};