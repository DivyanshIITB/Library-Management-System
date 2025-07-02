#ifndef USER_H
#define USER_H

#include <string>

class User {
protected:
    int userId;
    std::string name;
    std::string email;

public:
    User(int id, const std::string& name, const std::string& email);
    virtual ~User();
    virtual void showMenu() = 0;  // pure virtual

    // Getters
    int getUserId() const;
    std::string getName() const;
    std::string getEmail() const;

    // Setters
    void setName(const std::string& name);
    void setEmail(const std::string& email);

    // Virtual Methods
    virtual void getDetails() const = 0; // pure virtual function (polymorphism)
};

#endif // USER_H
