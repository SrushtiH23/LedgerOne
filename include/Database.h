#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>
#include "sqlite3.h"

class Database
{
private:
    sqlite3* db;      // SQLite database connection
    bool connected;   // Connection status

public:
    Database();
    ~Database();

    // Connection management
    bool connect(const std::string& dbPath);
    void disconnect();
    bool isConnected() const;

    // SQL execution
    bool executeUpdate(const std::string& sql);
    std::vector<std::vector<std::string>> executeQuery(const std::string& sql);

    // Utility functions
    int lastInsertId();
    sqlite3* getHandle();

    static std::string escapeSql(const std::string& input);

    // Create application tables
    void initTables();
};

#endif