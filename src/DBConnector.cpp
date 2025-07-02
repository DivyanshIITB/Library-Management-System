#include "DBConnector.h"
#include <iostream>
using namespace std;

DBConnector::DBConnector() {
    driver = nullptr;
    con = nullptr;
}

DBConnector::~DBConnector() {
    disconnect();
}

void DBConnector::connect(const std::string& user, const std::string& password, const std::string& db) {
    try {
        driver = sql::mysql::get_mysql_driver_instance();
        con = driver->connect("tcp://127.0.0.1:3306", user, password);
        con->setSchema(db);
    } catch (sql::SQLException& e) {
        std::cerr << "Connection error: " << e.what() << std::endl;
    }
}

void DBConnector::disconnect() {
    if (con) {
        delete con;
        con = nullptr;
        }
}

void DBConnector::insertBook(int id, const std::string& title, const std::string& author) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "INSERT INTO Books (id, title, author, available) VALUES (?, ?, ?, ?)");
        pstmt->setInt(1, id);
        pstmt->setString(2, title);
        pstmt->setString(3, author);
        pstmt->setBoolean(4, true);
        pstmt->execute();
        delete pstmt;
        std::cout << "Book inserted successfully.\n";
    } catch (sql::SQLException& e) {
        std::cerr << "Insert error: " << e.what() << std::endl;
    }
}

void DBConnector::deleteBook(int id) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("DELETE FROM Books WHERE id = ?");
        pstmt->setInt(1, id);
        pstmt->execute();
        delete pstmt;
    } catch (sql::SQLException& e) {
        std::cerr << "Delete error: " << e.what() << std::endl;
    }
}

void DBConnector::updateBook(int id, const std::string& title, const std::string& author) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement(
            "UPDATE Books SET title = ?, author = ? WHERE id = ?");
        pstmt->setString(1, title);
        pstmt->setString(2, author);
        pstmt->setInt(3, id);
        pstmt->execute();
        delete pstmt;
    } catch (sql::SQLException& e) {
        std::cerr << "Update error: " << e.what() << std::endl;
    }
}

void DBConnector::logTransaction(int userId, int bookId, const std::string& action) {
    sql::PreparedStatement* pstmt = con->prepareStatement(
        "INSERT INTO Transactions(user_id, book_id, action) VALUES (?, ?, ?)");
    pstmt->setInt(1, userId);
    pstmt->setInt(2, bookId);
    pstmt->setString(3, action);
    pstmt->execute();
    delete pstmt;
}

void DBConnector::viewAllTransactions() {
    sql::Statement* stmt = con->createStatement();
    sql::ResultSet* res = stmt->executeQuery(
        "SELECT * FROM Transactions ORDER BY timestamp DESC"
    );

    cout << "\n--- Transaction Logs ---\n";
    while (res->next()) {
        cout << "ID: " << res->getInt("id")
             << " | User ID: " << res->getInt("user_id")
             << " | Book ID: " << res->getInt("book_id")
             << " | Action: " << res->getString("action")
             << " | Time: " << res->getString("timestamp") << endl;
    }

    delete res;
    delete stmt;
}

bool DBConnector::bookExists(int bookId) {
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT id FROM Books WHERE id = ?");
    pstmt->setInt(1, bookId);
    sql::ResultSet* res = pstmt->executeQuery();
    bool exists = res->next();
    delete res;
    delete pstmt;
    return exists;
}

void DBConnector::getBook(int id) {
    try {
        sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM Books WHERE id = ?");
        pstmt->setInt(1, id);
        sql::ResultSet* res = pstmt->executeQuery();

        if (res->next()) {
            std::cout << "ID: " << res->getInt("id") << "\n";
            std::cout << "Title: " << res->getString("title") << "\n";
            std::cout << "Author: " << res->getString("author") << "\n";
            std::cout << "Available: " << (res->getBoolean("available") ? "Yes" : "No") << "\n";
        } else {
            std::cout << "Book not found.\n";
        }

        delete res;
        delete pstmt;
    } catch (sql::SQLException& e) {
        std::cerr << "Fetch error: " << e.what() << std::endl;
    }
}

bool DBConnector::checkAvailability(int bookId) {
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT available FROM Books WHERE id = ?");
    pstmt->setInt(1, bookId);
    sql::ResultSet* res = pstmt->executeQuery();
    bool available = false;
    if (res->next()) {
        available = res->getBoolean("available");
    }
    delete res;
    delete pstmt;
    return available;
}

void DBConnector::setAvailability(int bookId, bool status) {
    sql::PreparedStatement* pstmt = con->prepareStatement("UPDATE Books SET available = ? WHERE id = ?");
    pstmt->setBoolean(1, status);
    pstmt->setInt(2, bookId);
    pstmt->executeUpdate();
    delete pstmt;
}

bool DBConnector::getUserById(int id, std::string& name, std::string& email, std::string& role) {
    sql::PreparedStatement* pstmt = con->prepareStatement("SELECT * FROM Users WHERE id = ?");
    pstmt->setInt(1, id);
    sql::ResultSet* res = pstmt->executeQuery();

    bool found = false;
    if (res->next()) {
        name = res->getString("name");
        email = res->getString("email");
        role = res->getString("role");
        found = true;
    }

    delete res;
    delete pstmt;
    return found;
}
