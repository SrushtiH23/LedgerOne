#include "../include/Report.h"

#include <iostream>
#include <iomanip>

Report::Report(Database& database)
    : db(database)
{
}

namespace
{
    void divider(int width = 80)
    {
        std::cout << "  " << std::string(width, '-') << std::endl;
    }
}
void Report::printTable(
    const std::vector<std::string>& headers,
    const std::vector<std::vector<std::string>>& rows)
{
    divider();

    for(const auto& header : headers)
    {
        std::cout << std::left << std::setw(18) << header;
    }

    std::cout << "\n";

    divider();

    for(const auto& row : rows)
    {
        for(const auto& value : row)
        {
            std::cout << std::left << std::setw(18) << value;
        }

        std::cout << "\n";
    }

    divider();
}
void Report::todaysSales()
{
    auto rows = db.executeQuery(
        "SELECT id, customer_id, product_id, quantity, amount "
        "FROM transactions "
        "WHERE type='SALE' "
        "AND date(date)=date('now','localtime');"
    );

    std::cout << "\nTODAY'S SALES\n";

    if(rows.empty())
    {
        std::cout << "No sales found.\n";
        return;
    }

    printTable(
        {"ID","Customer","Product","Qty","Amount"},
        rows
    );
}
void Report::todaysPurchases()
{
    auto rows = db.executeQuery(
        "SELECT id, product_id, quantity, amount "
        "FROM transactions "
        "WHERE type='PURCHASE' "
        "AND date(date)=date('now','localtime');"
    );

    std::cout << "\nTODAY'S PURCHASES\n";

    if(rows.empty())
    {
        std::cout << "No purchases found.\n";
        return;
    }

    printTable(
        {"ID","Product","Qty","Amount"},
        rows
    );
}
// ─── Monthly Sales ──────────────────────────────────────────────────────────
void Report::monthlySales()
{
    auto rows = db.executeQuery(
        "SELECT id, customer_id, product_id, quantity, amount "
        "FROM transactions "
        "WHERE type='SALE' "
        "AND strftime('%Y-%m', date)=strftime('%Y-%m','now','localtime');"
    );

    std::cout << "\nMONTHLY SALES\n";

    if(rows.empty())
    {
        std::cout << "No sales found.\n";
        return;
    }

    printTable(
        {"ID","Customer","Product","Qty","Amount"},
        rows
    );
}
// ─── Inventory Report ───────────────────────────────────────────────────────
void Report::inventoryReport()
{
    auto rows = db.executeQuery(
        "SELECT id, name, stock, buying_price, price "
        "FROM product "
        "ORDER BY id;"
    );

    std::cout << "\nINVENTORY REPORT\n";

    if(rows.empty())
    {
        std::cout << "No products found.\n";
        return;
    }

    printTable(
        {"ID","Product","Stock","Buy","Sell"},
        rows
    );
}
// ─── Low Stock Report ───────────────────────────────────────────────────────
void Report::lowStockReport()
{
    const int LOW_STOCK_THRESHOLD = 5;

    auto rows = db.executeQuery(
        "SELECT id, name, stock "
        "FROM product "
        "WHERE stock <= " + std::to_string(LOW_STOCK_THRESHOLD) + " "
        "ORDER BY stock ASC;"
    );

    std::cout << "\nLOW STOCK REPORT\n";

    if (rows.empty())
    {
        std::cout << "All products have sufficient stock.\n";
        return;
    }

    printTable(
        {"ID", "Product", "Stock"},
        rows
    );
}
// ─── Customer Report ────────────────────────────────────────────────────────
void Report::customerReport()
{
    auto rows = db.executeQuery(
        "SELECT id, name, phone, city "
        "FROM customer "
        "ORDER BY id;"
    );

    std::cout << "\nCUSTOMER REPORT\n";

    if(rows.empty())
    {
        std::cout << "No customers found.\n";
        return;
    }

    printTable(
        {"ID","Name","Phone","City"},
        rows
    );
}
// ─── Profit Report ──────────────────────────────────────────────────────────
void Report::profitReport()
{
    auto rows = db.executeQuery(
        "SELECT "
        "SUM((p.price - p.buying_price) * t.quantity) "
        "FROM transactions t "
        "JOIN product p ON t.product_id = p.id "
        "WHERE t.type='SALE';"
    );

    std::cout << "\nPROFIT REPORT\n";
    divider();

    if(rows.empty() || rows[0][0] == "NULL")
    {
        std::cout << "Total Profit : 0\n";
    }
    else
    {
        std::cout << "Total Profit : " << rows[0][0] << "\n";
    }

    divider();
}
void Report::salesByDateRange()
{
    std::string startDate;
    std::string endDate;

    std::cout << "\nSALES BY DATE RANGE\n";
    divider();

    std::cout << "Enter start date (YYYY-MM-DD): ";
    std::cin >> startDate;

    std::cout << "Enter end date (YYYY-MM-DD): ";
    std::cin >> endDate;

    auto rows = db.executeQuery(
        "SELECT id, customer_id, product_id, quantity, amount, date "
        "FROM transactions "
        "WHERE type = 'SALE' "
        "AND date(date) BETWEEN '"
        + startDate + "' AND '"
        + endDate + "' "
        "ORDER BY date;"
    );

    if (rows.empty())
    {
        std::cout << "\nNo sales found in this date range.\n";
        return;
    }

    printTable(
        {"ID", "Customer", "Product", "Qty", "Amount", "Date"},
        rows
    );
}
// ─── Report Menu ────────────────────────────────────────────────────────────
void Report::showReportMenu()
{
    int choice;

    do
    {
        std::cout << "\n";
        divider();

        std::cout << "           REPORT MENU\n";

        divider();

        std::cout << "1. Today's Sales\n";
        std::cout << "2. Monthly Sales\n";
        std::cout << "3. Today's Purchases\n";
        std::cout << "4. Inventory Report\n";
        std::cout << "5. Low Stock Report\n";
        std::cout << "6. Customer Report\n";
        std::cout << "7. Profit Report\n";
        std::cout << "8. Sales By Date Range\n";
        std::cout << "0. Back\n";

        divider();

        std::cout << "Enter Choice : ";
        std::cin >> choice;

        switch(choice)
        {
            switch(choice)
            {
                case 1: todaysSales(); break;
                case 2: monthlySales(); break;
                case 3: todaysPurchases(); break;
                case 4: inventoryReport(); break;
                case 5: lowStockReport(); break;
                case 6: customerReport(); break;
                case 7: profitReport(); break;
                case 8:salesByDateRange();break;

                case 0: break;

                default:
                    std::cout << "\nInvalid Choice.\n";
            }
        }

    } while(choice != 0);
}