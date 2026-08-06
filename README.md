# LedgerOne - Mini ERP System

LedgerOne is a terminal-based Enterprise Resource Planning (ERP) system developed in **C++** using **SQLite3** for persistent data storage. It provides core business management features such as customer management, product inventory, transactions, and reporting.

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
- Sales management
- Purchase management

### Reports
- Today's Sales
- Monthly Sales
- Today's Purchases
- Inventory Report
- Customer Report
- Profit Report

## Tech Stack

- **Language:** C++17
- **Database:** SQLite3
- **Build System:** CMake
- **Compiler:** GCC (MSYS2 UCRT64)
- **IDE:** Visual Studio Code

## Project Structure

```
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

- GCC (MSYS2 UCRT64)
- CMake
- SQLite3 (included)

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

```bash
./LedgerOne.exe
```



## Future Improvements

- Invoice generation
- Company settings
- GST support
- PDF invoice export
- User authentication
- Dashboard analytics
- Backup & restore
- CSV export
- Barcode support

## Learning Outcomes

This project helped me understand:

- Object-Oriented Programming
- Modular C++ project architecture
- CMake build system
- SQLite database integration
- File organization
- CRUD operations
- Menu-driven application design

## Author

**Srushti Hosamani**

GitHub: https://github.com/SrushtiH23
