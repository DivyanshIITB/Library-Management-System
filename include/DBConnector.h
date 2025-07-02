#ifndef DBCONNECTOR_H
#define DBCONNECTOR_H

#include <string>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

class DBConnector {
private:
    sql::mysql::MySQL_Driver* driver;
    sql::Connection* con;

public:
    DBConnector();
    ~DBConnector();

    void connect(const std::string& user, const std::string& password, const std::string& db);
    void disconnect();
    void logTransaction(int userId, int bookId, const std::string& action);
    bool checkAvailability(int bookId);
    void setAvailability(int bookId, bool status);
    bool bookExists(int bookId);
    void viewAllTransactions();
    bool getUserById(int id, std::string& name, std::string& email, std::string& role);


    // Book Queries
    void insertBook(int id, const std::string& title, const std::string& author);
    void deleteBook(int id);
    void updateBook(int id, const std::string& title, const std::string& author);
    void getBook(int id);
};

#endif // DBCONNECTOR_H
