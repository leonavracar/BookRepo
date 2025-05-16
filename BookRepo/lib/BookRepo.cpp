#include "Book.h"
#include "Genre.h"
#include "Author.h"
#include "BookRepo.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <unordered_map>
#include <fstream>


BookRepo::BookRepo(const std::string& i_repoName) : m_repoName(i_repoName) {}

BookRepo::~BookRepo() {
    for (Book* book : m_repoBooks) delete book;
    for (Author* author : m_repoAuthors) delete author;
}

// Helper methods
std::pair<std::string, std::string> BookRepo::splitName(const std::string& i_authorFullName) {
    std::istringstream iss(trim(i_authorFullName)); 
    std::string first, last;
    iss >> first >> last;
    return {first, last};
}



std::string BookRepo::makeAuthorKey(const std::pair<std::string, std::string>& i_authorSplitName ) {
    std::string o_authorKey;
    o_authorKey = toLower(i_authorSplitName.first) + '_' + toLower(i_authorSplitName.second);
    return o_authorKey; // output is first_last
}

// Search author using authorKey in unordered_map return its pointer if exists, if not return nullptr
Author* BookRepo::authorExists(const std::string& i_authorKey) {
    if (m_authorLookup.count(i_authorKey)) {
        return m_authorLookup.at(i_authorKey);
    }
    return nullptr;
}

// Takes output of splitName and creates Author object 
// Note: Adding the new author to the BookRepo member variables and making a key is handled in newBook, not here
Author* BookRepo::newAuthor(const std::pair<std::string, std::string>& i_authorSplitName) {
    Author* author = new Author(i_authorSplitName.first, i_authorSplitName.second);
    return author;
}

std::string BookRepo::trim(const std::string& i_string) {
    const char* white_space = " \t\v\r\n";
    std::size_t start = i_string.find_first_not_of(white_space);
    std::size_t end = i_string.find_last_not_of(white_space);
    return start == end ? std::string() : i_string.substr(start, end - start +1);
}


std::string BookRepo::makeBookKey(const std::string& i_title, const std::vector<Author*>& i_authors) {
    // trim and lowerspace the title
    std::string trimmed = trim(i_title); 
    std::string lowered = toLower(trimmed);

    std::string o_bookKey;

    // add _ between words
    bool inSpace = false;
    for (char c : lowered) {
        if (c == ' ' || c == '\t') {
            if (!inSpace) {
                o_bookKey+= '_';
                inSpace = true;
            }
        } else {
                o_bookKey += c;
                inSpace = false;
            }
        }

    // sort authorIDs
    std::vector<int> auIDs;
    for (const auto& iter : i_authors) {
        auIDs.push_back(iter->getAuID());
    }
    std::sort(auIDs.begin(), auIDs.end());

    // add sorted authorIDs to the key
    for (int num : auIDs) {
        o_bookKey += '_' + std::to_string(num);
    }
    
    return o_bookKey;
}

Book* BookRepo::newBook(const std::string& i_title, int i_year, const std::vector<std::string>& i_authorsFullNames, Genre genre) {
    // For storing the final list of pointers for this book
    std::vector<Author*> bookAuthors;

    // === Step 1: Process author names ===
    for (std::string authorName : i_authorsFullNames) {
        // a) Normalize input and make key
        auto authorSplitNames = splitName(authorName); // returns {first, last}
        std::string authorKey = makeAuthorKey(authorSplitNames); // e.g. jane_austen
        // b) Check if author exists
        Author* p_author = authorExists(authorKey);
        // c) If not found, create new author and add to repo
        if (!p_author) {
            p_author = newAuthor(authorSplitNames); // allocates new Author
            m_repoAuthors.push_back(p_author); // store pointer
            m_authorLookup[authorKey] = p_author; // name key-> pointer
            m_authorIDLookup[p_author->getAuID()] = p_author; // ID key -> pointer
        }
        bookAuthors.push_back(p_author); // add to book's author list
    }

    // === Step 2: Create unique book key and check for duplicates ===
    std::string bookKey = makeBookKey(i_title, bookAuthors); 
    if  (m_bookKeys.count(bookKey)) {
        std::cerr << "Error: A book titled |" << i_title <<"| already exsis in the repo. \n";
        return nullptr;
    }

    // === Step 3: Create and store new Book ===
    std::string cleanedTitle = collapseSpaces(i_title);
    Book* newBook = new Book(cleanedTitle, i_year, bookAuthors, genre);
    m_repoBooks.push_back(newBook);
    m_bookKeys.insert(bookKey);

    // === Step 4: Update ref count for each author ===
    for (Author* p_author : bookAuthors) {
        p_author->incrementRefCount();
    }
    return newBook;

}

Book* BookRepo::bookPointerByID(int i_bookID) const {
    for (Book* p_book : m_repoBooks) {
        if (p_book->getBookID() == i_bookID) {
            return p_book;
        } 
    }
    return nullptr;
}

void BookRepo::deleteAuthorZeroCount(Author* p_author) {
    if (p_author->getRefCount() == 0) {
        // == Remove pointer from m_repoAuthors == 
        m_repoAuthors.erase(std::remove(m_repoAuthors.begin(), m_repoAuthors.end(), p_author),
        m_repoAuthors.end());
        // == Remove key from m_authorLookup == 
        std::string authorKey = makeAuthorKey({p_author->getFirstAuName(), p_author->getLastAuName()});
        m_authorLookup.erase(authorKey);
        // == Remove ID from m_authorIDLookup ==
        m_authorIDLookup.erase(p_author->getAuID());
        // == Delete pointer ==
        delete p_author;
    }
    return;
}

bool BookRepo::deleteBookByID(int i_bookID) {
    auto p_book = bookPointerByID(i_bookID);

    if (!p_book) {return false;}

    // == Decrement ref counts & clean up authors ==
    for (Author* p_author : p_book->getAuthorsPointers()) {
        p_author->decrementRefCount();
        deleteAuthorZeroCount(p_author);
    }

    // == Remove pointer from m_repoBooks ==
    m_repoBooks.erase(
        std::remove(m_repoBooks.begin(), m_repoBooks.end(), p_book),
        m_repoBooks.end()
    );

    // == Rebuild book key to remove it from m_bookKeys ==
    std::string bookKey = makeBookKey(p_book->getTitle(), p_book->getAuthorsPointers());
    m_bookKeys.erase(bookKey);

    // == Delete book object ==
    delete p_book;

    return true;
}

void BookRepo::displayAll() const {
    std::cout << std::left
              << std::setw(10) << "Book ID"
              << std::setw(30) << "Title"
              << std::setw(6)  << "Year"
              << std::setw(12) << "Genre"
              << "Authors" << std::endl;

    for (Book* p_book : m_repoBooks) {
        std::cout << std::left
                  << std::setw(10) << p_book->getBookID()
                  << std::setw(30) << p_book->getTitle()
                  << std::setw(6)  << p_book->getYear()
                  << std::setw(12) << genreToString(p_book->getGenre());

        // Print authors (inline, separated by commas)
        const auto& authors = p_book->getAuthorsPointers();
        for (size_t i = 0; i < authors.size(); ++i) {
            std::cout << authors[i]->getFirstAuName() << " " << authors[i]->getLastAuName();
            if (i != authors.size() - 1)
                std::cout << ", ";
        }

        std::cout << std::endl;
    }
}

void BookRepo::displayAllAuthors() const 
{
    std::cout << std::left
              << std::setw(25) << "Author"
              << "Books Written\n";

    for (Author* author : m_repoAuthors) {
        std::string fullName = author->getFirstAuName() + " " + author->getLastAuName();
        std::cout << std::left
                  << std::setw(25) << fullName
                  << author->getRefCount() << '\n';
    }
}


// Loading/Saving to file
    // saving: out << year << ";" << genreToString(book->getGenre()) << ";" << title << ";" << author1 << ";" << author2 << ...
    // loading: Genre genre = parseGenre(tokens[1]);
    // format: title;genre;year;author1;author2

    void BookRepo::saveToFile(const std::string& filePath) 
    {
        std::ofstream outFile(filePath);
        if (!outFile) {std::cerr << "Failed to open file for writing.\n"; return;}
        for (Book* book: m_repoBooks) 
        {
            outFile << book->getTitle() << ';' << genreToString(book->getGenre()) << ';' << book->getYear() << ';';
            const auto authors = book->getAuthorsPointers();
            for(size_t i = 0; i < authors.size(); ++i) 
            {
                outFile << authors[i]->getFullName();
                if (i < authors.size()-1) {outFile << ';';} // semicolon not added after last author name
            }
            outFile << '\n';
        }
    }
    void BookRepo::loadFromFile(const std::string& filePath) 
    {
        std::ifstream inFile(filePath);
        if (!inFile) {std::cerr << "Failed to open file for loading.\n"; return;}

        std::string line;
        while(getline(inFile, line))
        {
            std::stringstream lineStream(line);
            std::string item;
            int fieldIndex = 0;
            std::string title, str_genre, str_year;
            std::vector<std::string> authors;

            while(getline(lineStream, item, ';')) 
            {
                switch (fieldIndex) 
                {
                    case 0:
                        title = item;
                        break;
                    case 1:
                        str_genre = item;
                        break;
                    case 2:
                        str_year = item;
                        break;
                    default:
                        authors.push_back(item);
                        break;
                }
                fieldIndex++;
            }
            newBook(title, std::stoi(str_year), authors, parseGenre(str_genre));
        }
        std::cout << "File loaded successfully!" << std::endl;
    }


