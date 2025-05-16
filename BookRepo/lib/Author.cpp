#include "Author.h"
#include <string>
#include <vector>
#include <iostream>

// c'tor
Author::Author(const std::string& i_firstName, const std::string& i_lastName) 
    : m_firstName(i_firstName), 
    m_lastName(i_lastName), 
    m_authorID(s_nextAuthorID++)
{}

// d'tor 
Author::~Author() {};

int Author::s_nextAuthorID = 1;  // start value 1

// getters
const std::string& Author::getFirstAuName() const { return m_firstName; }
const std::string& Author::getLastAuName() const {return m_lastName; }
std::string Author::getFullName() const {return m_firstName + ' ' + m_lastName;};
int Author::getAuID() const {return m_authorID;}

// setters
void Author::setFirstAuName(const std::string& i_firstName) { m_firstName = i_firstName; }
void Author::setLastAuName(const std::string& i_lastName) {m_lastName = i_lastName; }

// Display
void Author::display() const {
    std::cout << " Author has first name " << m_firstName << " and last name " << m_lastName << " with ID " << m_authorID << std::endl;
}

// Reference count getter and safe increment/decrement
int Author::getRefCount() const { return m_refCount;}
void Author::incrementRefCount() {++m_refCount; }
void Author::decrementRefCount() {--m_refCount; }

