#pragma once
#include <string>
#include <vector>
#include <chrono>
#include <thread>

/**
*@brief 
* Helper functions used in Menu.cpp
*/

std::string toLower(const std::string& i_string);
int readInt(const std::string& i_strYear);
std::vector<std::string> splitCommaSeparated(const std::string& i_authors);
void printAvailableGenres();

std::string collapseSpaces(const std::string& input);

// Little timer for 1 second
inline void wait(int ms = 1000) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}