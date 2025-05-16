#pragma once
#include <string>
#include <vector>
#include "Author.h"
#include "Genre.h"

/**
*@brief 
* The Book class manages book information (title, year, genre, ID) and its authors saved as a vector of Author pointers.
* - 
*/

class Book {
    private:
        std::string m_title;
        int m_year;
        std::vector<Author*> m_authors;
        Genre m_genre;

        int m_bookID;
        static int s_nextBookID;



    public:
        // c'tor for creating books (bookID is auto-incremented)
        Book(const std::string& i_title, int i_year, const std::vector<Author*>& i_authors, Genre i_genre = Genre::undefined);

        // d'tor
        virtual ~Book();
    
        // delete default c'tor, copy c'tor , assignment operator
        Book() = delete;
        Book(const Book& i_book) = delete;
        Book &operator=(const Book& i_other) = delete;

        // Getters: title and year getters
        const std::string& getTitle() const;
        int getYear() const;

        // Author pointer vector list getter
        const std::vector<Author*>& getAuthorsPointers() const;

        // Genre and ID getters
        Genre getGenre() const;
        int getBookID() const;

        // Setters for title, year, genre, authors
        void setBookTitle(const std::string& i_title);
        void setBookYear(int i_year);
        void setGenre(Genre i_genre);
        // NOTE: No setter for authors, authors are only created when a book is created

        void display() const; 
        
        // Private helper methods
    private:
        // Gets author's full name and ID, is used in the display() Books
        std::string getAuthorList() const;


};