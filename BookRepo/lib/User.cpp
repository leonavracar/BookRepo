#include "UserState.h"
#include "User.h"
#include <string>
#include <iostream>


User::User(UserState* i_state) : state(i_state) {}

std::string User::getRoleName() const {
    return state->getRoleName();  // delegate
}

bool User::canAddDelete() const {
    return state->canAddDelete();
}


