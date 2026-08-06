#ifndef REPORT_H
#define REPORT_H

#include "Database.h"
#include <string>
#include <vector>

class Report
{
private:
    Database& db;
    

    // Utility function to display reports in tabular format
    void printTable(const std::vector<std::string>& headers,
                    const std::vector<std::vector<std::string>>& rows);

public:
    // Constructor
    Report(Database& database);

    // Sales Reports
    void todaysSales();
    void monthlySales();

    // Purchase Reports
    void todaysPurchases();

    // Inventory Reports
    void inventoryReport();
    void lowStockReport();

    // Business Reports
    void profitReport();
    void customerReport();
    void supplierReport();
    void gstReport();

    // Analytics
    void topSellingProducts(int limit = 5);

    // Custom Reports
    void salesByDateRange();

    // Report Menu
    void showReportMenu();
};

#endif // REPORT_H