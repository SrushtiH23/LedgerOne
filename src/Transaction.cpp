#include "../include/Transaction.h"

#include <iostream>
#include <limits>

// Constructor
Transaction::Transaction(Database& database)
    : db(database)
{
}

// Helper function
namespace
{
    void divider(int width = 80)
    {
        std::cout << "  " << std::string(width, '-') << std::endl;
    }
}
// Update product stock
bool Transaction::updateStock(int productId, int quantityChange)
{
    std::string sql =
        "UPDATE product SET stock = stock + ("
        + std::to_string(quantityChange)
        + ") WHERE id = "
        + std::to_string(productId)
        + ";";

    return db.executeUpdate(sql);
}
// Save transaction into database
int Transaction::saveTransaction(
    int customerId,
    int supplierId,
    int productId,
    int quantity,
    double unitPrice,
    double gstAmount,
    double discount,
    double total,
    const std::string& transactionType)
{
    (void)supplierId;
    (void)unitPrice;
    (void)gstAmount;
    (void)discount;

    std::string customerValue =
        customerId == 0 ? "NULL" : std::to_string(customerId);

    std::string sql =
        "INSERT INTO transactions "
        "(customer_id, product_id, quantity, amount, type) "
        "VALUES ("
        + customerValue
        + ", "
        + std::to_string(productId)
        + ", "
        + std::to_string(quantity)
        + ", "
        + std::to_string(total)
        + ", '"
        + transactionType
        + "');";

    if (db.executeUpdate(sql))
        return db.lastInsertId();

    return -1;
}
// ─── Make Sale ──────────────────────────────────────────────────────────────
void Transaction::makeSale()
{
    int customerId;
    int productId;
    int quantity;

    std::cout << "\n";
    divider();
    std::cout << "  NEW SALE\n";
    divider();

    // Customer ID
    std::cout << "  Customer ID : ";
    std::cin >> customerId;

    auto customer = db.executeQuery(
        "SELECT name FROM customer WHERE id = "
        + std::to_string(customerId) + ";"
    );

    if (customer.empty())
    {
        std::cout << "\n  [ERROR] Customer not found.\n";
        return;
    }

    // Product ID
    std::cout << "  Product ID  : ";
    std::cin >> productId;

    auto product = db.executeQuery(
        "SELECT name, price, stock FROM product WHERE id = "
        + std::to_string(productId) + ";"
    );

    if (product.empty())
    {
        std::cout << "\n  [ERROR] Product not found.\n";
        return;
    }

    std::string productName = product[0][0];
    double price = std::stod(product[0][1]);
    int stock = std::stoi(product[0][2]);

    std::cout << "  Product : " << productName << "\n";
    std::cout << "  Price   : " << price << "\n";
    std::cout << "  Stock   : " << stock << "\n\n";

    std::cout << "  Quantity : ";
    std::cin >> quantity;

    if(quantity <= 0)
    {
        std::cout << "\n  [ERROR] Invalid quantity.\n";
        return;
    }

    if(quantity > stock)
    {
        std::cout << "\n  [ERROR] Insufficient stock.\n";
        return;
    }

    double total = quantity * price;

    // Start database transaction
    if (!db.beginTransaction())
    {
        std::cout << "\n  [ERROR] Failed to start database transaction.\n";
        return;
    }

    // Reduce stock
    if (!updateStock(productId, -quantity))
    {
        db.rollbackTransaction();

        std::cout << "\n  [ERROR] Failed to update stock.\n";
        return;
    }

    // Save transaction
    int transactionId = saveTransaction(
        customerId,
        0,
        productId,
        quantity,
        price,
        0,
        0,
        total,
        "SALE"
    );

    if (transactionId < 0)
    {
        db.rollbackTransaction();

        std::cout << "\n  [ERROR] Failed to save transaction.\n";
        return;
    }

    // Commit all changes
    if (!db.commitTransaction())
    {
        std::cout << "\n  [ERROR] Failed to commit transaction.\n";
        return;
    }
    divider();

    std::cout << "  Sale Successful\n";
    std::cout << "  Transaction ID : " << transactionId << "\n";
    std::cout << "  Customer       : " << customer[0][0] << "\n";
    std::cout << "  Product        : " << productName << "\n";
    std::cout << "  Quantity       : " << quantity << "\n";
    std::cout << "  Total Amount   : " << total << "\n";

    divider();
}
// ─── Make Purchase ──────────────────────────────────────────────────────────
void Transaction::makePurchase()
{
    int productId;
    int quantity;
    double buyingPrice;

    std::cout << "\n";
    divider();
    std::cout << "  NEW PURCHASE\n";
    divider();

    // Product ID
    std::cout << "  Product ID : ";
    std::cin >> productId;

    auto product = db.executeQuery(
        "SELECT name, stock FROM product WHERE id = "
        + std::to_string(productId) + ";"
    );

    if(product.empty())
    {
        std::cout << "\n  [ERROR] Product not found.\n";
        return;
    }

    std::string productName = product[0][0];
    int currentStock = std::stoi(product[0][1]);

    std::cout << "  Product       : " << productName << "\n";
    std::cout << "  Current Stock : " << currentStock << "\n\n";

    std::cout << "  Quantity      : ";
    std::cin >> quantity;

    std::cout << "  Buying Price  : ";
    std::cin >> buyingPrice;

    if(quantity <= 0 || buyingPrice < 0)
    {
        std::cout << "\n  [ERROR] Invalid input.\n";
        return;
    }

    double total = quantity * buyingPrice;
      

    // Start database transaction
    if (!db.beginTransaction())
    {
        std::cout << "\n  [ERROR] Failed to start database transaction.\n";
        return;
    }

    // Increase stock
    if (!updateStock(productId, quantity))
    {
        db.rollbackTransaction();

        std::cout << "\n  [ERROR] Failed to update stock.\n";
        return;
    }

    // Update buying price
    bool priceUpdated = db.executeUpdate(
        "UPDATE product SET buying_price = "
        + std::to_string(buyingPrice)
        + " WHERE id = "
        + std::to_string(productId)
        + ";"
    );

    if (!priceUpdated)
    {
        db.rollbackTransaction();

        std::cout << "\n  [ERROR] Failed to update buying price.\n";
        return;
    }

    // Save transaction
    int transactionId = saveTransaction(
        0,
        0,
        productId,
        quantity,
        buyingPrice,
        0,
        0,
        total,
        "PURCHASE"
    );

    if (transactionId < 0)
    {
        db.rollbackTransaction();

        std::cout << "\n  [ERROR] Failed to save purchase.\n";
        return;
    }

    // Commit all changes
    if (!db.commitTransaction())
    {
        std::cout << "\n  [ERROR] Failed to commit transaction.\n";
        return;
    }

    

    divider();

    std::cout << "  Purchase Successful\n";
    std::cout << "  Transaction ID : " << transactionId << "\n";
    std::cout << "  Product        : " << productName << "\n";
    std::cout << "  Quantity       : " << quantity << "\n";
    std::cout << "  Total Cost     : " << total << "\n";
    std::cout << "  New Stock      : " << currentStock + quantity << "\n";

    divider();
}