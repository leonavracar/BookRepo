#include "Book.h"
#include "Genre.h"
#include "Author.h"
#include <iostream>
#include <string>
#include <vector>

// c'tor
Book::Book(const std::string& i_title, int i_year, const std::vector<Author*>& i_authors, Genre i_genre)
: m_title(i_title), m_year(i_year), m_authors(i_authors), m_genre(i_genre),  m_bookID(s_nextBookID++) {}

// d'tor
Book::~Book() {};
// Static book ID
int Book::s_nextBookID = 1;

// Getters for title and year
const std::string& Book::getTitle() const {return m_title;}
int Book::getYear() const {return m_year;}

// Author pointer vector list getter
const std::vector<Author*>& Book::getAuthorsPointers() const {return m_authors;};

// Genre and ID getters
Genre Book::getGenre() const {return m_genre;}
int Book::getBookID() const { return m_bookID;}

// Setters for title, year, genre
void Book::setBookTitle(const std::string& i_title) { m_title = i_title;}
void Book::setBookYear(int i_year) {m_year = i_year;}
void Book::setGenre(Genre i_genre) {m_genre = i_genre;}

// Methods

// Display method
void Book::display() const {
    std::cout << "Book titled \"" << m_title << "\", written in year " << m_year 
    << " by author(s) " << this->getAuthorList() << "." << std::endl;
}

// Private helper methods
    // Gets a string of author full names, is used in the display() Books
    // Iterates over m_authors (list of author pointers), derefs them, uses getFullName to get names.
    std::string Book::getAuthorList() const {
        std::string au = "";
        for (size_t i = 0; i < m_authors.size(); ++i) {
            au.append(m_authors[i]->getFirstAuName() + " " + m_authors[i]->getLastAuName());
            if (i != m_authors.size() -1) {
                au.append(", ");
            }
        }
        return au;
    }
