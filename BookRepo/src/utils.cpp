#include "utils.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
/**
*@brief 
* Helper functions used in Menu.cpp
*/
std::string toLower(const std::string& i_string) {
    std::string out = i_string;
    std::transform(out.begin(), out.end(), out.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return out;
}

int readInt(const std::string& yearPrompt) {
    int o_year;
    while (true) {
        std::cout << yearPrompt;
        std::string yearInput;
        std::getline(std::cin, yearInput);
        std::istringstream iss(yearInput);
        if (iss >> o_year) 
            return o_year;
        std::cout << "Invalid number, try again. \n";
    }
}

std::vector<std::string> splitCommaSeparated(const std::string& i_authors) {
    std::vector<std::string> o_authors;
    std::istringstream iss(i_authors);
    std::string singleAuthor;
    while (std::getline(iss, singleAuthor, ',')){
        o_authors.push_back(singleAuthor);
    }
    return o_authors;
}

void printAvailableGenres() {
    std::cout << "Available genres: fiction, non-fiction, article, sci-fi, fantasy, textbook, history, biology, computer_science, politics\n";
}

std::string collapseSpaces(const std::string& input) {
    std::ostringstream oss;
    bool inSpace = false;
    for (char c : input) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            if (!inSpace) {
                oss << ' ';
                inSpace = true;
            }
        } else {
            oss << c;
            inSpace = false;
        }
    }
    return oss.str(); // optionally trim again
}

