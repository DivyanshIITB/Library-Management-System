#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "DBConnector.h"
#include <vector>

class Student : public User {
private:
    std::string rollNumber;
    std::vector<int> borrowedBookIds;

public:
    Student(int id, const std::string& name, const std::string& email, const std::string& roll);

    void getDetails() const override;
    void showMenu() override;

    // Borrow management
    void borrowBook(int bookId);
    void returnBook(int bookId);
    const std::vector<int>& getBorrowedBooks() const;

    // Getters/Setters
    std::string getRollNumber() const;
    void setRollNumber(const std::string& roll);
};

#endif // STUDENT_H
