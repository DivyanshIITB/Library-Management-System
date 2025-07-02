#include "../include/Student.h"
#include "../include/Book.h"
#include "../include/Transaction.h"
#include <iostream>
#include <algorithm>

Student::Student(int id, const std::string& name, const std::string& email, const std::string& roll)
    : User(id, name, email), rollNumber(roll) {}

void Student::getDetails() const {
    std::cout << "Student: " << name << " (" << rollNumber << "), Email: " << email << std::endl;
}

void Student::borrowBook(int bookId) {
    borrowedBookIds.push_back(bookId);
}

void Student::returnBook(int bookId) {
    borrowedBookIds.erase(std::remove(borrowedBookIds.begin(), borrowedBookIds.end(), bookId), borrowedBookIds.end());
}

const std::vector<int>& Student::getBorrowedBooks() const {
    return borrowedBookIds;
}

std::string Student::getRollNumber() const {
    return rollNumber;
}

void Student::setRollNumber(const std::string& roll) {
    rollNumber = roll;
}

void Student::showMenu() {
    DBConnector db;
    db.connect("root", "librarysql1365", "librarydb");

    int choice, bookId;
    string title, author;

    do {
        cout << "\n--- Student Menu ---\n";
        cout << "1. View Book\n2. Issue Book\n3. Return Book\n0. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Book ID: ";
                cin >> bookId;
                Book::viewBook(db, bookId);
                break;

            case 2:
                cout << "Enter Book ID to issue: ";
                cin >> bookId;
                if (db.checkAvailability(bookId)) {
                    db.setAvailability(bookId, false);  // mark as issued
                    Transaction::log(db, userId, bookId, "ISSUE");
                    cout << "Book issued successfully.\n";
                } else {
                    cout << "Book is already issued or not found.\n";
                }
                break;

            case 3: // Return Book
                cout << "Enter Book ID to return: ";
                cin >> bookId;

                if (!db.bookExists(bookId)) {
                    cout << "Book does not exist in the database.\n";
                    break;
                }
            
                if (db.checkAvailability(bookId)) {
                    cout << "This book was not issued.\n";
                } else {
                    db.setAvailability(bookId, true); // mark as returned
                    Transaction::log(db, userId, bookId, "RETURN");
                    cout << "Book returned successfully.\n";
                }
                break;
        }
    } while (choice != 0);
    db.disconnect();
}
