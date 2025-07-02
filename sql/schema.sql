CREATE DATABASE IF NOT EXISTS librarydb;
USE librarydb;

CREATE TABLE IF NOT EXISTS Users (
    user_id INT PRIMARY KEY,
    name VARCHAR(100),
    email VARCHAR(100),
    role ENUM('student', 'librarian') NOT NULL
);

CREATE TABLE IF NOT EXISTS Books (
    id INT PRIMARY KEY,
    title VARCHAR(255),
    author VARCHAR(255),
    available BOOLEAN DEFAULT TRUE
);

DROP TABLE IF EXISTS Transactions;

CREATE TABLE Transactions (
    id INT AUTO_INCREMENT PRIMARY KEY,
    user_id INT,
    book_id INT,
    action ENUM('ISSUE', 'RETURN'),
    timestamp DATETIME DEFAULT CURRENT_TIMESTAMP
);