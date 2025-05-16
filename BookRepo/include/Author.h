#pragma once
#include <string>
#include <vector>

/**
*@brief 
* - The Author class manages author information (first name, last name, unique ID). 
* - It provides constructors, destructors, getters/setters for first/last name, getter for ID.
* - Display function for an author object.
* - Reference count (how many books author has written in repo) + static variable s_nextAuthorID.
* - Reference count is used in BookRepo to delete authors when their ref count = 0.
*/


class Author {
    private:
        std::string m_firstName;
        std::string m_lastName;

        int m_authorID; // uniqueID
        static int s_nextAuthorID; // static variable for auto incrementing
        
        int m_refCount = 0; // counts number of books (refs) the author is in, use to dlt author if = 0

    public:
        // c'tor
        Author(const std::string& i_firstName, const std::string& i_lastName);
        // d'tor
        virtual ~Author();

        // delete default c'tor, copy c'tor , assignment operator
        Author() = delete;
        Author(const Author& i_other) = delete;
        Author &operator=(const Author& i_other) = delete; 

        // getters
        const std::string& getFirstAuName() const;
        const std::string& getLastAuName() const;
        // getter for full name, constructs new string
        std::string getFullName() const;
        int getAuID() const;
        
        // setters
        void setFirstAuName(const std::string& i_firstName);
        void setLastAuName(const std::string& i_lastName);

        // Display
        void display() const;

        // Reference count getter and safe increment/decrement
        int getRefCount() const;
        void incrementRefCount();
        void decrementRefCount();
        

};