#ifndef BOOK_H          // Include Guards
#define BOOK_H

#include<string>
using namespace std;

// Forward declaration to avoid circular include
class DBConnector;

class Book{
private:
    int bookId;
    string title;
    string author;
    bool isAvailable;

public:
    Book(int id, const string& title, const string& author);

    void displayInfo() const;
    bool getAvailability() const;
    void markIssued();
    void markReturned();

    // getters
    int getBookId() const;
    string getTitle() const;
    string getAuthor() const;

    // setter
    void setAvailability(bool status);

// 🔽 DB-related methods (static)
    static void addBook(DBConnector& db, int id, const string& title, const string& author);
    static void removeBook(DBConnector& db, int id);
    static void updateBook(DBConnector& db, int id, const string& title, const string& author);
    static void viewBook(DBConnector& db, int id);    
};

#endif //BOOK_H