#pragma once
#include <string>
#include "utils.h"

/**
*@brief 
* Genre is an enum class that is used as a book attribute.
*/

enum class Genre {


undefined,
article,
fiction,
non_fiction,
sci_fi, 
fantasy,
textbook,
history,
biology,
computer_science,
politics,

};

// Turn Genre object (internally an integer) into a string, used for printing
std::string genreToString(Genre genre);
// Turn a string into a Genre object
Genre parseGenre(const std::string& input);