# LedgerOne - Mini ERP System

LedgerOne is a terminal-based Enterprise Resource Planning (ERP) system developed in **C++** using **SQLite3** for persistent data storage. It provides core business management features such as customer management, product inventory, sales and purchase transactions, and reporting.

## Features

### Customer Management

- Add customer
- View customers
- Search customer
- Update customer
- Delete customer

### Product Management

- Add product
- View products
- Search product
- Update product
- Delete product

### Transactions

- Create new sales
- Create new purchases
- Automatically update product stock
- Store transaction records in the database
- Use database transactions to maintain data consistency

### Reports

- Today's Sales
- Monthly Sales
- Today's Purchases
- Inventory Report
- Low Stock Report
- Customer Report
- Profit Report
- Sales by Date Range

## Tech Stack

- **Language:** C++17
- **Database:** SQLite3
- **Build System:** CMake
- **Compiler:** GCC (MSYS2 UCRT64)
- **IDE:** Visual Studio Code

## Project Structure

```text
LedgerOne/
│── include/            # Header files
│── src/                # Source files
│── database/           # SQLite database
│── thirdparty/sqlite/  # SQLite source
│── CMakeLists.txt
│── README.md
│── .gitignore
```

## Build Instructions

### Prerequisites

Make sure the following are installed:

- GCC (MSYS2 UCRT64)
- CMake

SQLite3 is included with the project under:

```text
thirdparty/sqlite/
```

### Clone the Repository

```bash
git clone https://github.com/SrushtiH23/LedgerOne.git
cd LedgerOne
```

### Configure

```bash
mkdir build
cd build

cmake .. -G "MinGW Makefiles" \
-DCMAKE_C_COMPILER=C:/msys64/ucrt64/bin/gcc.exe \
-DCMAKE_CXX_COMPILER=C:/msys64/ucrt64/bin/g++.exe
```

### Build

```bash
cmake --build .
```

### Run

From the `build` directory:

```bash
./LedgerOne.exe
```

## Transaction Handling

Sales and purchases use SQLite database transactions to maintain data consistency.

For example, when creating a sale:

1. Product availability is checked.
2. A database transaction is started.
3. Product stock is reduced.
4. The transaction record is saved.
5. Changes are committed.

If any operation fails before completion, the transaction is rolled back to prevent partial updates.

The purchase workflow follows a similar process for updating stock, buying price, and transaction records.

## Future Improvements

- Invoice generation
- Company settings
- GST support
- PDF invoice export
- User authentication
- Dashboard analytics
- Backup and restore
- CSV export
- Barcode support
- Supplier management

## Learning Outcomes

This project helped me understand:

- Object-Oriented Programming
- Modular C++ project architecture
- Header and source file separation
- CMake build system
- SQLite database integration
- CRUD operations
- SQL queries
- Database transactions
- Commit and rollback
- Inventory management
- Menu-driven application design
- Input validation

## Author

**Srushti Hosamani**

GitHub: https://github.com/SrushtiH23
