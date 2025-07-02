#include "../include/Librarian.h"
#include "../include/Book.h"
#include "../include/Transaction.h"
#include <iostream>

Librarian::Librarian(int id, const std::string& name, const std::string& email, const std::string& empId)
    : User(id, name, email), employeeId(empId) {}

void Librarian::getDetails() const {
    std::cout << "Librarian: " << name << " (Emp ID: " << employeeId << "), Email: " << email << std::endl;
}

std::string Librarian::getEmployeeId() const { return employeeId; }
void Librarian::setEmployeeId(const std::string& empId) { employeeId = empId; }

void Librarian::showMenu() {
    DBConnector db;
    db.connect("root", "librarysql1365", "librarydb");

    int choice, bookId;
    string title, author;

    do {
        cout << "\n--- Librarian Menu ---\n";
        cout << "1. Add Book\n2. View Book\n3. Update Book\n4. Delete Book\n5. View Transactions\n0. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Book ID, Title, Author: ";
                cin >> bookId;
                cin.ignore();
                getline(cin, title);
                getline(cin, author);
                Book::addBook(db, bookId, title, author);
                break;

            case 2:
                cout << "Enter Book ID: ";
                cin >> bookId;
                Book::viewBook(db, bookId);
                break;

            case 3:
                cout << "Enter Book ID to update: ";
                cin >> bookId;
                    
                if (!db.bookExists(bookId)) {
                    cout << "Book not found in the database. Cannot update.\n";
                } else {
                    cin.ignore();
                    cout << "Enter new title: ";
                    getline(cin, title);
                    cout << "Enter new author: ";
                    getline(cin, author);
                
                    Book::updateBook(db, bookId, title, author);
                    cout << "Book updated successfully.\n";
                }
                break;


            case 4:
                cout << "Enter Book ID to delete: ";
                cin >> bookId;

                if (!db.bookExists(bookId)) {
                    cout << "Book not found in the database. Cannot delete.\n";
                } else {
                    Book::removeBook(db, bookId);
                    cout << "Book deleted successfully.\n";
                }
                break;

            case 5:
                db.viewAllTransactions();
                break;
        }
    } while (choice != 0);

    db.disconnect();
}