#include "../include/Transaction.h"
#include "../include/DBConnector.h"
#include <iostream>

Transaction::Transaction(int txnId, int userId, int bookId, const std::string& type, const std::string& timestamp)
    : transactionId(txnId), userId(userId), bookId(bookId), type(type), timestamp(timestamp) {}

void Transaction::printTransaction() const {
    std::cout << "[" << timestamp << "] "
              << "Txn ID: " << transactionId << ", "
              << "User: " << userId << ", Book: " << bookId
              << ", Type: " << type << std::endl;
}

void Transaction::log(DBConnector& db, int userId, int bookId, const std::string& action) {
    db.logTransaction(userId, bookId, action);
}

int Transaction::getTransactionId() const { return transactionId; }
int Transaction::getUserId() const { return userId; }
int Transaction::getBookId() const { return bookId; }
std::string Transaction::getType() const { return type; }
std::string Transaction::getTimestamp() const { return timestamp; }
