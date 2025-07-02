#include "../include/User.h"
#include<iostream>
using namespace std;

User::User(int id, const string& name, const string& email)
    : userId(id), name(name), email(email) {}

User::~User() {}  // Needed if base class has virtual destructor

// getters
int User::getUserId() const{
    return userId;
}

string User::getEmail() const{
    return email;
}

string User::getName() const{
    return name;
}

// setters
void User::setName(const string& newName){ name = newName; }
void User::setEmail(const string& newEmail){ email = newEmail; }

