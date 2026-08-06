#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Database.h"
#include <string>

class Transaction
{
private:
    Database& db;
    

    // Internal helper functions
    bool updateStock(int productId, int quantityChange);
    int saveTransaction(int customerId,
                        int supplierId,
                        int productId,
                        int quantity,
                        double unitPrice,
                        double gstAmount,
                        double discount,
                        double total,
                        const std::string& transactionType);

public:
    // Constructor
    Transaction(Database& database);

    // Business operations
    void makeSale();
    void makePurchase();
};

#endif // TRANSACTION_H