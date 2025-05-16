#include "BookRepo.h"
#include "User.h"
#include "UserState.h"

bool AdminState::canAddDelete() const  {return true;}
std::string AdminState::getRoleName() const {return "Admin";}

bool CustomerState::canAddDelete() const  {return false;}
std::string CustomerState::getRoleName() const {return "Customer";}


