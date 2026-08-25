#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "Database.h"


class Customer
{
private:
    Database& db;   // Shared database connection

public:
    // Constructor
    Customer(Database& database);

    // Customer operations
    void addCustomer();
    void updateCustomer();
    void deleteCustomer();

    // View & search
    void viewCustomers();
    void searchCustomer();

    // Utility
    bool customerExists(int customerId);
};

#endif // CUSTOMER_H