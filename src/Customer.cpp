#include "../include/Customer.h"
#include <iostream>
#include <iomanip>
#include <limits>
using namespace std;

// ─── Constructor ────────────────────────────────────────────────────────────
Customer::Customer(Database& database) : db(database) {}

// ─── Helper: print a divider line ───────────────────────────────────────────
static void divider(int width = 80) {
    std::cout << "  " << std::string(width, '-') << std::endl;
}

// ─── Add Customer ───────────────────────────────────────────────────────────
void Customer::addCustomer() {
    std::string name, phone, city, email;

    std::cout << "\n";
    divider();
    std::cout << "  ADD NEW CUSTOMER\n";
    divider();

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "  Name  : ";
    std::getline(std::cin, name);
    std::cout << "  Phone : ";
    std::getline(std::cin, phone);
    std::cout << "  City  : ";
    std::getline(std::cin, city);
    std::cout << "  Email : ";
    std::getline(std::cin, email);

    if (name.empty()) {
        std::cout << "\n  [ERROR] Customer name cannot be empty.\n";
        return;
    }

    std::string sql = "INSERT INTO customer (name, phone, city, email) VALUES ('"
                      + Database::escapeSql(name) + "', '"
                      + Database::escapeSql(phone) + "', '"
                      + Database::escapeSql(city) + "', '"
                      + Database::escapeSql(email) + "');";

    if (db.executeUpdate(sql)) {
        int id = db.lastInsertId();
        std::cout << "\n  [SUCCESS] Customer added with ID: " << id << "\n";
    } else {
        std::cout << "\n  [ERROR] Failed to add customer.\n";
    }
}

// ─── Delete Customer ────────────────────────────────────────────────────────
void Customer::deleteCustomer() {
    int id;
    std::cout << "\n";
    divider();
    std::cout << "  DELETE CUSTOMER\n";
    divider();

    std::cout << "  Enter Customer ID: ";
    std::cin >> id;

    if (!customerExists(id)) {
        std::cout << "  [ERROR] Customer with ID " << id << " not found.\n";
        return;
    }

    std::string sql = "DELETE FROM customer WHERE id = " + std::to_string(id) + ";";

    if (db.executeUpdate(sql)) {
        std::cout << "  [SUCCESS] Customer deleted.\n";
    } else {
        std::cout << "  [ERROR] Failed to delete customer.\n";
    }
}

// ─── Update Customer ────────────────────────────────────────────────────────
void Customer::updateCustomer() {
    int id;
    std::cout << "\n";
    divider();
    std::cout << "  UPDATE CUSTOMER\n";
    divider();

    std::cout << "  Enter Customer ID: ";
    std::cin >> id;

    if (!customerExists(id)) {
        std::cout << "  [ERROR] Customer with ID " << id << " not found.\n";
        return;
    }

    // Fetch current data
    std::string query = "SELECT name, phone, city, email FROM customer WHERE id = " + std::to_string(id) + ";";
    auto rows = db.executeQuery(query);

    if (rows.empty()) return;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string name, phone, city, email;

    std::cout << "\n  Current Name  : " << rows[0][0] << "\n";
    std::cout << "  New Name  (Enter to keep): ";
    std::getline(std::cin, name);
    if (name.empty()) name = rows[0][0];

    std::cout << "  Current Phone : " << rows[0][1] << "\n";
    std::cout << "  New Phone (Enter to keep): ";
    std::getline(std::cin, phone);
    if (phone.empty()) phone = rows[0][1];

    std::cout << "  Current City  : " << rows[0][2] << "\n";
    std::cout << "  New City  (Enter to keep): ";
    std::getline(std::cin, city);
    if (city.empty()) city = rows[0][2];

    std::cout << "  Current Email : " << rows[0][3] << "\n";
    std::cout << "  New Email (Enter to keep): ";
    std::getline(std::cin, email);
    if (email.empty()) email = rows[0][3];

    std::string sql = "UPDATE customer SET name='" + Database::escapeSql(name)
                    + "', phone='" + Database::escapeSql(phone)
                    + "', city='" + Database::escapeSql(city)
                    + "', email='" + Database::escapeSql(email)
                    + "' WHERE id=" + std::to_string(id) + ";";

    if (db.executeUpdate(sql)) {
        std::cout << "\n  [SUCCESS] Customer updated.\n";
    } else {
        std::cout << "\n  [ERROR] Failed to update customer.\n";
    }
}

// ─── Display All Customers ──────────────────────────────────────────────────
void Customer::viewCustomers(){
    std::cout << "\n";
    divider();
    std::cout << "  ALL CUSTOMERS\n";
    divider();

    auto rows = db.executeQuery("SELECT id, name, phone, city, email FROM customer ORDER BY id;");

    if (rows.empty()) {
        std::cout << "  No customers found.\n";
        return;
    }

    std::cout << "  " << std::left
              << std::setw(6)  << "ID"
              << std::setw(22) << "Name"
              << std::setw(16) << "Phone"
              << std::setw(16) << "City"
              << std::setw(24) << "Email" << "\n";
    divider();

    for (const auto& row : rows) {
        std::cout << "  " << std::left
                  << std::setw(6)  << row[0]
                  << std::setw(22) << row[1]
                  << std::setw(16) << row[2]
                  << std::setw(16) << row[3]
                  << std::setw(24) << row[4] << "\n";
    }
    divider();
    std::cout << "  Total: " << rows.size() << " customer(s)\n";
}

// ─── Search Customer ────────────────────────────────────────────────────────
void Customer::searchCustomer() {
    std::string keyword;
    std::cout << "\n";
    divider();
    std::cout << "  SEARCH CUSTOMER\n";
    divider();

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << "  Enter name or phone: ";
    std::getline(std::cin, keyword);

    std::string safeKey = Database::escapeSql(keyword);
    std::string sql = "SELECT id, name, phone, city, email FROM customer "
                      "WHERE name LIKE '%" + safeKey + "%' OR phone LIKE '%" + safeKey + "%';";

    auto rows = db.executeQuery(sql);

    if (rows.empty()) {
        std::cout << "  No customers found matching '" << keyword << "'.\n";
        return;
    }

    std::cout << "\n  " << std::left
              << std::setw(6)  << "ID"
              << std::setw(22) << "Name"
              << std::setw(16) << "Phone"
              << std::setw(16) << "City"
              << std::setw(24) << "Email" << "\n";
    divider();

    for (const auto& row : rows) {
        std::cout << "  " << std::left
                  << std::setw(6)  << row[0]
                  << std::setw(22) << row[1]
                  << std::setw(16) << row[2]
                  << std::setw(16) << row[3]
                  << std::setw(24) << row[4] << "\n";
    }
    std::cout << "  Found: " << rows.size() << " result(s)\n";
}

// ─── Exists ─────────────────────────────────────────────────────────────────
bool Customer::customerExists(int id) {
    std::string sql = "SELECT id, name FROM customer WHERE id = " + std::to_string(id) + ";";
    auto rows = db.executeQuery(sql);
    if (!rows.empty()) {
        std::cout << "  Customer: " << rows[0][1] << " (ID: " << rows[0][0] << ")\n";
        return true;
    }
    return false;
}
