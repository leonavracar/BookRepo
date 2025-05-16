# Book Repository CLI Application

A simple C++ command-line interface (CLI) application to manage a repository of books and authors. This project demonstrates object-oriented design principles including dynamic memory management, reference tracking, and role-based access control via the State pattern.

## Features

- Add, display, and delete books with one or multiple authors
- Automatically manages author reference counts and deletes unused authors
- Save and load book repositories to and from text files
- Role-based command access (`Admin` vs `Customer`)
- Efficient search using `unordered_map`
- Function pointer-based command dispatch system
- Book key generation to avoid duplicates

## Technologies

- C++17
- Standard Library (`<vector>`, `<unordered_map>`, `<map>`, `<fstream>`, etc.)
- No external libraries, no smart pointers

## How to Use

- **Build**: Ensure you have `g++` installed (supporting C++17). Then compile using ``make`` from the project folder.
- **Run**: To run use ``./app``. You will be prompted to pick a role. Use ``help`` to view all commands.
