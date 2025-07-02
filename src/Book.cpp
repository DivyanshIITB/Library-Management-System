#include "../include/Book.h"
#include "../include/DBConnector.h"
#include<iostream>
using namespace std;

Book::Book(int id, const string& title, const string& author) 
    : bookId(id), title(title), author(author), isAvailable(true) {}

void Book::displayInfo() const {
    std::cout << "Book ID: " << bookId << ", Title: " << title << ", Author: " << author
              << ", Available: " << (isAvailable ? "Yes" : "No") << std::endl;
}

bool Book::getAvailability() const{
    return isAvailable;
}

void Book::markIssued(){
    isAvailable = false;
}

void Book::markReturned(){
    isAvailable = true;
}

// getters
int Book::getBookId() const{
    return bookId;
}

string Book::getTitle() const{
    return title;
}

string Book::getAuthor() const{
    return author;
}

// setter
void Book::setAvailability(bool status){
    isAvailable = status;
}

// 🔽 DB-integrated static methods
void Book::addBook(DBConnector& db, int id, const string& title, const string& author) {
    db.insertBook(id, title, author);
}

void Book::removeBook(DBConnector& db, int id) {
    db.deleteBook(id);
}

void Book::updateBook(DBConnector& db, int id, const string& title, const string& author) {
    db.updateBook(id, title, author);
}

void Book::viewBook(DBConnector& db, int id) {
    db.getBook(id);
}

