#include "../include/Product.h"

#include <iostream>
#include <iomanip>
#include <limits>

// Constructor
Product::Product(Database& database)
    : db(database)
{
}

// Helper function to print a divider
namespace
{
    void divider(int width = 80)
    {
        std::cout << "  " << std::string(width, '-') << std::endl;
    }
}
// ─── Add Product ────────────────────────────────────────────────────────────
void Product::addProduct()
{
    std::string name;
    double buyingPrice, sellingPrice, gstPercent;
    int stock;

    std::cout << "\n";
    divider();
    std::cout << "  ADD NEW PRODUCT\n";
    divider();

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "  Product Name  : ";
    std::getline(std::cin, name);

    if (name.empty())
    {
        std::cout << "\n  [ERROR] Product name cannot be empty.\n";
        return;
    }

    // Check if product already exists
    auto rows = db.executeQuery(
        "SELECT id FROM product WHERE LOWER(name)=LOWER('"
        + Database::escapeSql(name) + "');"
    );

    if (!rows.empty())
    {
        std::cout << "\n  [ERROR] Product already exists.\n";
        return;
    }

    std::cout << "  Buying Price : ";
    std::cin >> buyingPrice;

    std::cout << "  Selling Price: ";
    std::cin >> sellingPrice;

    std::cout << "  GST (%)      : ";
    std::cin >> gstPercent;

    std::cout << "  Stock        : ";
    std::cin >> stock;

    if (buyingPrice < 0 || sellingPrice < 0 || gstPercent < 0 || stock < 0)
    {
        std::cout << "\n  [ERROR] Values cannot be negative.\n";
        return;
    }

    std::string sql =
        "INSERT INTO product "
        "(name, price, buying_price, gst_percent, stock) "
        "VALUES ('"
        + Database::escapeSql(name) + "', "
        + std::to_string(sellingPrice) + ", "
        + std::to_string(buyingPrice) + ", "
        + std::to_string(gstPercent) + ", "
        + std::to_string(stock) + ");";

    if (db.executeUpdate(sql))
    {
        std::cout << "\n  [SUCCESS] Product added successfully.\n";
    }
    else
    {
        std::cout << "\n  [ERROR] Failed to add product.\n";
    }
}
// ─── Delete Product ─────────────────────────────────────────────────────────
void Product::deleteProduct()
{
    int productId;

    std::cout << "\n";
    divider();
    std::cout << "  DELETE PRODUCT\n";
    divider();

    std::cout << "  Enter Product ID: ";
    std::cin >> productId;

    if (!productExists(productId))
    {
        std::cout << "\n  [ERROR] Product not found.\n";
        return;
    }

    std::string sql =
        "DELETE FROM product WHERE id = "
        + std::to_string(productId) + ";";

    if (db.executeUpdate(sql))
    {
        std::cout << "\n  [SUCCESS] Product deleted successfully.\n";
    }
    else
    {
        std::cout << "\n  [ERROR] Failed to delete product.\n";
    }
}

bool Product::productExists(int productId)
{
    std::string sql =
        "SELECT id, name FROM product WHERE id = "
        + std::to_string(productId) + ";";

    auto rows = db.executeQuery(sql);

    if(rows.empty())
        return false;

    return true;
}
void Product::viewProducts()
{
    std::cout << "\n";
    divider();

    std::cout << "  PRODUCT LIST\n";

    divider();

    auto rows = db.executeQuery(
        "SELECT id,name,price,buying_price,gst_percent,stock "
        "FROM product ORDER BY id;"
    );

    if(rows.empty())
    {
        std::cout << "No products found.\n";
        return;
    }

    std::cout
        << std::left
        << std::setw(5)  << "ID"
        << std::setw(25) << "Name"
        << std::setw(12) << "Sell"
        << std::setw(12) << "Buy"
        << std::setw(8)  << "GST"
        << std::setw(8)  << "Stock"
        << "\n";

    divider();

    for(const auto& row : rows)
    {
        std::cout
            << std::left
            << std::setw(5)  << row[0]
            << std::setw(25) << row[1]
            << std::setw(12) << row[2]
            << std::setw(12) << row[3]
            << std::setw(8)  << row[4]
            << std::setw(8)  << row[5]
            << "\n";
    }

    divider();
}
void Product::searchProduct()
{
    std::string keyword;

    std::cout << "\n";
    divider();

    std::cout << "SEARCH PRODUCT\n";

    divider();

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter product name : ";

    std::getline(std::cin, keyword);

    auto rows = db.executeQuery(

        "SELECT id,name,price,stock "
        "FROM product WHERE name LIKE '%"
        + Database::escapeSql(keyword)
        + "%';"
    );

    if(rows.empty())
    {
        std::cout << "\nProduct not found.\n";
        return;
    }

    std::cout
        << std::left
        << std::setw(5)  << "ID"
        << std::setw(25) << "Name"
        << std::setw(12) << "Price"
        << std::setw(8)  << "Stock"
        << "\n";

    divider();

    for(const auto& row : rows)
    {
        std::cout
            << std::left
            << std::setw(5)  << row[0]
            << std::setw(25) << row[1]
            << std::setw(12) << row[2]
            << std::setw(8)  << row[3]
            << "\n";
    }

    divider();
}
// ─── Update Product ─────────────────────────────────────────────────────────
void Product::updateProduct()
{
    int productId;

    std::cout << "\n";
    divider();
    std::cout << "  UPDATE PRODUCT\n";
    divider();

    std::cout << "Enter Product ID : ";
    std::cin >> productId;

    if(!productExists(productId))
    {
        std::cout << "\nProduct not found.\n";
        return;
    }

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::string name;
    double sellingPrice;
    double buyingPrice;
    double gst;
    int stock;

    std::cout << "New Name          : ";
    std::getline(std::cin, name);

    std::cout << "Selling Price     : ";
    std::cin >> sellingPrice;

    std::cout << "Buying Price      : ";
    std::cin >> buyingPrice;

    std::cout << "GST (%)           : ";
    std::cin >> gst;

    std::cout << "Stock             : ";
    std::cin >> stock;

    std::string sql =
        "UPDATE product SET "
        "name='" + Database::escapeSql(name)
        + "', price=" + std::to_string(sellingPrice)
        + ", buying_price=" + std::to_string(buyingPrice)
        + ", gst_percent=" + std::to_string(gst)
        + ", stock=" + std::to_string(stock)
        + " WHERE id=" + std::to_string(productId) + ";";

    if(db.executeUpdate(sql))
        std::cout << "\nProduct updated successfully.\n";
    else
        std::cout << "\nFailed to update product.\n";
}
double Product::getSellingPrice(int productId)
{
    auto rows = db.executeQuery(
        "SELECT price FROM product WHERE id="
        + std::to_string(productId) + ";");

    if(rows.empty())
        return -1;

    return std::stod(rows[0][0]);
}
double Product::getBuyingPrice(int productId)
{
    auto rows = db.executeQuery(
        "SELECT buying_price FROM product WHERE id="
        + std::to_string(productId) + ";");

    if(rows.empty())
        return -1;

    return std::stod(rows[0][0]);
}
int Product::getStock(int productId)
{
    auto rows = db.executeQuery(
        "SELECT stock FROM product WHERE id="
        + std::to_string(productId) + ";");

    if(rows.empty())
        return -1;

    return std::stoi(rows[0][0]);
}
std::string Product::getProductName(int productId)
{
    auto rows = db.executeQuery(
        "SELECT name FROM product WHERE id="
        + std::to_string(productId) + ";");

    if(rows.empty())
        return "";

    return rows[0][0];
}
double Product::getGstPercentage(int productId)
{
    auto rows = db.executeQuery(
        "SELECT gst_percent FROM product WHERE id="
        + std::to_string(productId) + ";");

    if(rows.empty())
        return 0;

    return std::stod(rows[0][0]);
}