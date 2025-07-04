#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <string>

class DBConnector;

class Transaction {
private:
    int transactionId;
    int userId;
    int bookId;
    std::string type;        // "ISSUE" or "RETURN"
    std::string timestamp;

public:
    Transaction(int txnId, int userId, int bookId, const std::string& type, const std::string& timestamp);

    static void log(DBConnector& db, int userId, int bookId, const std::string& action);

    // Display
    void printTransaction() const;

    // Getters
    int getTransactionId() const;
    int getUserId() const;
    int getBookId() const;
    std::string getType() const;
    std::string getTimestamp() const;
};

#endif // TRANSACTION_H
