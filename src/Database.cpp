#include "../include/Database.h"
#include <iostream>
#include <cstdio>

#ifdef _WIN32
  #include <direct.h>
  #define MKDIR(dir) _mkdir(dir)
#else
  #include <sys/stat.h>
  #define MKDIR(dir) mkdir(dir, 0755)
#endif

using namespace std;

// ─── Callback used by executeQuery ──────────────────────────────────────────
static int queryCallback(void* data, int argc, char** argv, char** colNames) {
    (void)colNames;
    auto* rows = static_cast<vector<vector<string>>*>(data);
    vector<string> row;
    for (int i = 0; i < argc; i++) {
        row.push_back(argv[i] ? argv[i] : "NULL");
    }
    rows->push_back(row);
    return 0;
}

// ─── Constructor / Destructor ───────────────────────────────────────────────
Database::Database() : db(nullptr), connected(false) {}

Database::~Database() {
    disconnect();
}

// ─── Connect ────────────────────────────────────────────────────────────────
bool Database::connect(const string& dbPath) {
    // Create the database directory if it doesn't exist
    string dir = dbPath.substr(0, dbPath.find_last_of("/\\"));
    if (!dir.empty()) {
        MKDIR(dir.c_str());
    }

    int rc = sqlite3_open(dbPath.c_str(), &db);
    if (rc != SQLITE_OK) {
        cerr << "  [ERROR] Cannot open database: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    connected = true;

    // Enable foreign keys
    executeUpdate("PRAGMA foreign_keys = ON;");

    return true;
}

// ─── Disconnect ─────────────────────────────────────────────────────────────
void Database::disconnect() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
        connected = false;
    }
}

// ─── Is Connected ───────────────────────────────────────────────────────────
bool Database::isConnected() const {
    return connected;
}

// ─── Execute UPDATE / INSERT / DELETE ───────────────────────────────────────
bool Database::executeUpdate(const string& sql) {
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), nullptr, nullptr, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "  [SQL ERROR] " << errMsg << endl;
        sqlite3_free(errMsg);
        return false;
    }
    return true;
}

// ─── Execute SELECT ─────────────────────────────────────────────────────────
vector<vector<string>> Database::executeQuery(const string& sql) {
    vector<vector<string>> results;
    char* errMsg = nullptr;
    int rc = sqlite3_exec(db, sql.c_str(), queryCallback, &results, &errMsg);
    if (rc != SQLITE_OK) {
        cerr << "  [SQL ERROR] " << errMsg << endl;
        sqlite3_free(errMsg);
    }
    return results;
}

// ─── Escape SQL ─────────────────────────────────────────────────────────────
string Database::escapeSql(const string& input) {
    string res;
    res.reserve(input.size());
    for (char c : input) {
        if (c == '\'') {
            res += "''";
        } else {
            res += c;
        }
    }
    return res;
}

// ─── Last Insert ID ────────────────────────────────────────────────────────
int Database::lastInsertId() {
    return static_cast<int>(sqlite3_last_insert_rowid(db));
}

// ─── Get Handle ─────────────────────────────────────────────────────────────
sqlite3* Database::getHandle() {
    return db;
}

// ─── Initialize Tables ─────────────────────────────────────────────────────
void Database::initTables() {

    // Customer table
    executeUpdate(
        "CREATE TABLE IF NOT EXISTS customer ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "phone TEXT,"
        "city TEXT,"
        "email TEXT"
        ");"
    );

    // Product table
    executeUpdate(
        "CREATE TABLE IF NOT EXISTS product ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "name TEXT NOT NULL,"
        "price REAL NOT NULL DEFAULT 0,"
        "buying_price REAL DEFAULT 0,"
        "stock INTEGER NOT NULL DEFAULT 0,"
        "gst_percent REAL DEFAULT 0"
        ");"
    );

    // Transaction table
    executeUpdate(
        "CREATE TABLE IF NOT EXISTS transactions ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "customer_id INTEGER,"
        "product_id INTEGER,"
        "quantity INTEGER NOT NULL,"
        "amount REAL NOT NULL,"
        "type TEXT NOT NULL,"
        "date TEXT DEFAULT (datetime('now','localtime')),"
        "FOREIGN KEY(customer_id) REFERENCES customer(id),"
        "FOREIGN KEY(product_id) REFERENCES product(id)"
        ");"
    );
}

    