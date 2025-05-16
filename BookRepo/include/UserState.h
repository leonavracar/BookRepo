#pragma once
#include "BookRepo.h"
#include "User.h"

// UserState is the base class in the state design pattern
// AdminState, CustomerState -> derived from UserState
// All functions are delegated from User to the UserState of that User object

class UserState {
    public:
        virtual bool canAddDelete() const = 0;
        virtual std::string getRoleName() const = 0;
        virtual ~UserState() = default;

};

class AdminState : public UserState{
    public:
        bool canAddDelete() const override;
        std::string getRoleName() const override;
};

class CustomerState : public UserState {
        public:
            bool canAddDelete() const override;
            std::string getRoleName() const override;
};