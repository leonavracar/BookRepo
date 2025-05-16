#include "Genre.h"
#include "utils.h"
#include <algorithm>


// Used to display Genres in their string format
std::string genreToString(Genre genre) {
    switch (genre) {
        case Genre::undefined:         return "Undefined";
        case Genre::article:           return "Article";
        case Genre::fiction:           return "Fiction";
        case Genre::non_fiction:       return "Non-fiction";
        case Genre::sci_fi:            return "Sci-Fi";
        case Genre::fantasy:           return "Fantasy";
        case Genre::textbook:          return "Textbook";
        case Genre::history:           return "History";
        case Genre::biology:           return "Biology";
        case Genre::computer_science:  return "CompSci";
        case Genre::politics:          return "Politics";
        default:                       return "Unknown";
    }
}

// Creation of new books is more flexible for the user, genre input is case-insensitive
// and doesn't have to be an exact match (e.g. both compsci and computer_science are valid)

Genre parseGenre(const std::string& input) {
    std::string lower = toLower(input);

    if (lower == "article")           return Genre::article;
    if (lower == "fiction")           return Genre::fiction;
    if (lower == "non-fiction" || lower == "non_fiction") return Genre::non_fiction;
    if (lower == "sci-fi" || lower == "scifi") return Genre::sci_fi;
    if (lower == "fantasy")           return Genre::fantasy;
    if (lower == "textbook")          return Genre::textbook;
    if (lower == "history")           return Genre::history;
    if (lower == "biology")           return Genre::biology;
    if (lower == "computer_science" || lower == "compsci" || lower == "comp_sci") return Genre::computer_science;
    if (lower == "politics")          return Genre::politics;

    return Genre::undefined;
}

