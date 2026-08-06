#ifndef PRODUCT_H
#define PRODUCT_H

#include "Database.h"
#include <string>

class Product
{
private:
    Database& db;   // Shared database connection

public:
    // Constructor
    Product(Database& database);

    // Product operations
    void addProduct();
    void updateProduct();
    void deleteProduct();

    // View & search
    void viewProducts();
    void searchProduct();

    // Utility
    bool productExists(int productId);

    // Product information
    double getSellingPrice(int productId);
    double getBuyingPrice(int productId);
    int getStock(int productId);
    std::string getProductName(int productId);
    double getGstPercentage(int productId);
};

#endif // PRODUCT_H