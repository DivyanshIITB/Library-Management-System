#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include "User.h"
#include "DBConnector.h"

class Librarian : public User {
private:
    std::string employeeId;

public:
    Librarian(int id, const std::string& name, const std::string& email, const std::string& empId);

    void getDetails() const override;
    void showMenu() override;

    // Getters/Setters
    std::string getEmployeeId() const;
    void setEmployeeId(const std::string& empId);
};

#endif // LIBRARIAN_H
