#pragma once
#include "User.h"
#include "UserState.h" 
#include <string>
#include <iostream>

// User is the context in a state design pattern
// Its state is saved in the state attribute

class UserState; // forward declaration

class User {
    private:
        UserState* state;
    public:
        User(UserState* i_state);

        std::string getRoleName() const;
        bool canAddDelete() const;
    };