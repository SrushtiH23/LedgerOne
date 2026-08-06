#include "../include/Menu.h"

#include <iostream>

namespace
{
    void divider(int width = 60)
    {
        std::cout << std::string(width, '=') << "\n";
    }
}

// Constructor
Menu::Menu(Customer& customer,
           Product& product,
           Transaction& transaction,
           Report& report)
    : customer(customer),
      product(product),
      transaction(transaction),
      report(report)
{
}
void Menu::customerMenu()
{
    int choice;

    do
    {
        std::cout << "\n";
        divider();

        std::cout << "CUSTOMER MENU\n";

        divider();

        std::cout << "1. Add Customer\n";
        std::cout << "2. View Customers\n";
        std::cout << "3. Search Customer\n";
        std::cout << "4. Update Customer\n";
        std::cout << "5. Delete Customer\n";
        std::cout << "0. Back\n";

        divider();

        std::cout << "Enter Choice: ";
        std::cin >> choice;

        switch(choice)
        {
            case 1:
                customer.addCustomer();
                break;

            case 2:
                customer.viewCustomers();
                break;

            case 3:
                customer.searchCustomer();
                break;

            case 4:
                customer.updateCustomer();
                break;

            case 5:
                customer.deleteCustomer();
                break;

            case 0:
                break;

            default:
                std::cout << "\nInvalid Choice.\n";
        }

    } while(choice != 0);
}
void Menu::productMenu()
{
    int choice;

    do
    {
        std::cout << "\n";
        divider();

        std::cout << "PRODUCT MENU\n";

        divider();

        std::cout << "1. Add Product\n";
        std::cout << "2. View Products\n";
        std::cout << "3. Search Product\n";
        std::cout << "4. Update Product\n";
        std::cout << "5. Delete Product\n";
        std::cout << "0. Back\n";

        divider();

        std::cout << "Enter Choice: ";
        std::cin >> choice;

        switch(choice)
        {
            case 1:
                product.addProduct();
                break;

            case 2:
                product.viewProducts();
                break;

            case 3:
                product.searchProduct();
                break;

            case 4:
                product.updateProduct();
                break;

            case 5:
                product.deleteProduct();
                break;

            case 0:
                break;

            default:
                std::cout << "\nInvalid Choice.\n";
        }

    } while(choice != 0);
}
void Menu::transactionMenu()
{
    int choice;

    do
    {
        std::cout << "\n";
        divider();

        std::cout << "TRANSACTION MENU\n";

        divider();

        std::cout << "1. New Sale\n";
        std::cout << "2. New Purchase\n";
        std::cout << "0. Back\n";

        divider();

        std::cout << "Enter Choice: ";
        std::cin >> choice;

        switch(choice)
        {
            case 1:
                transaction.makeSale();
                break;

            case 2:
                transaction.makePurchase();
                break;

            case 0:
                break;

            default:
                std::cout << "\nInvalid Choice.\n";
        }

    } while(choice != 0);
}
// ─── Report Menu ───────────────────────────────────────────────────────────
void Menu::reportMenu()
{
    report.showReportMenu();
}
void Menu::mainMenu()
{
    int choice;

    do
    {
        std::cout << "\n";
        divider();

        std::cout << "          LEDGERONE MINI ERP\n";

        divider();

        std::cout << "1. Customer Management\n";
        std::cout << "2. Product Management\n";
        std::cout << "3. Transactions\n";
        std::cout << "4. Reports\n";
        std::cout << "0. Exit\n";

        divider();

        std::cout << "Enter Choice: ";
        std::cin >> choice;

        switch(choice)
        {
            case 1:
                customerMenu();
                break;

            case 2:
                productMenu();
                break;

            case 3:
                transactionMenu();
                break;

            case 4:
                reportMenu();
                break;

            case 0:
                std::cout << "\nThank you for using LedgerOne.\n";
                break;

            default:
                std::cout << "\nInvalid Choice.\n";
        }

    } while(choice != 0);
}
