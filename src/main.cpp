#include "DBConnector.h"
#include "Book.h"
#include "Student.h"
#include "Librarian.h"

int main() {
    DBConnector db;
    db.connect("root", "librarysql1365", "librarydb");

    int userId;
    std::string name, email, role;

    cout << "Enter your User ID: ";
    cin >> userId;

    if (db.getUserById(userId, name, email, role)) {
        cout << "Welcome, " << name << " (" << role << ")\n";

        if (role == "STUDENT") {
            // Dummy roll number for now
            Student s(userId, name, email, "TEMP1234");
            s.showMenu();
        } else if (role == "LIBRARIAN") {
            Librarian l(userId, name, email, "123");
            l.showMenu();
        }
    } else {
        cout << "No user found with that ID.\n";
    }

    return 0;
}
