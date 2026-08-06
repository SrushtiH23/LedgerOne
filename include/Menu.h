#ifndef MENU_H
#define MENU_H

#include "Customer.h"
#include "Product.h"
#include "Transaction.h"
#include "Report.h"

class Menu
{
private:
    Customer& customer;
    Product& product;
    Transaction& transaction;
    Report& report;

    // Sub-menus
    void customerMenu();
    void productMenu();
    void transactionMenu();
    void reportMenu();

public:
    // Constructor
    Menu(Customer& customer,
         Product& product,
         Transaction& transaction,
         Report& report);

    // Main application menu
    void mainMenu();
};

#endif // MENU_H