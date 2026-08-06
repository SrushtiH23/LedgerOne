#include <iostream>
#include "../include/Database.h"
#include "../include/Customer.h"
#include "../include/Product.h"
#include "../include/Transaction.h"
#include "../include/Report.h"
#include "../include/Menu.h"

// ...

int main()
{
    std::cout << "Program started\n";

    Database db;

    std::cout << "Connecting...\n";

    if (!db.connect("database/ledgerone.db"))
    {
        std::cout << "Failed to connect to database.\n";
        return 1;
    }

    std::cout << "Connected\n";

    db.initTables();

    std::cout << "Tables initialized\n";

    Customer customer(db);
    Product product(db);
    Transaction transaction(db);
    Report report(db);

    std::cout << "Objects created\n";

    Menu menu(customer, product, transaction, report);

    std::cout << "Opening menu...\n";

    menu.mainMenu();

    std::cout << "Program ended\n";

    db.disconnect();

    return 0;
}