#pragma once
#include "BookRepo.h"
#include "Genre.h"
#include "utils.h"
#include <iostream>
#include <map>
#include <string>
#include "User.h"
/**
*@brief 
* Command Line Interface for User Input:
* addBook -> prompts user field by field for title, year, authors (comma-separated), genre (validated from enum list)
* displayBooks -> prints all books in BookRepo
* deleteBook <BookID> -> deletes a book object and the author (if its refCount = 0)
* runInteractiveMenu -> UI 
* load, save -> load from file, save to file
* help -> prints all commands
*/

void addBook(BookRepo& i_repo);
void deleteBook(BookRepo& i_repo);
void displayBooks(BookRepo& i_repo);
void displayAuthors(BookRepo& i_repo);

void runInteractiveMenu(BookRepo& i_repo, const User& i_user);

void load(BookRepo& i_repo);
void save(BookRepo& i_repo);

void help(BookRepo& i_repo);