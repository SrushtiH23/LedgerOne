cmake_minimum_required(VERSION 3.16)

project(LedgerOne)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(LedgerOne
    src/main.cpp
    src/Database.cpp
    src/Customer.cpp
    src/Product.cpp
    src/Transaction.cpp
    src/Report.cpp
    src/Menu.cpp
    thirdparty/sqlite/sqlite3.c
)

target_include_directories(LedgerOne PRIVATE
    include
    thirdparty/sqlite
)