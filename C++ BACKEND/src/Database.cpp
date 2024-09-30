#include "Database.h"
#include <iostream>

Database::Database(const std::string& db_name) {
    if (sqlite3_open(db_name.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        db = nullptr;
    }
}

Database::~Database() {
    if (db) {
        sqlite3_close(db);
    }
}

bool Database::execute_query(const std::string& query) {
    char* err_msg = nullptr;
    if (sqlite3_exec(db, query.c_str(), nullptr, nullptr, &err_msg) != SQLITE_OK) {
        std::cerr << "SQL error: " << err_msg << std::endl;
        sqlite3_free(err_msg);
        return false;
    }
    return true;
}

bool Database::create_table() {
    std::string query = "CREATE TABLE IF NOT EXISTS properties ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "price REAL NOT NULL);";
    return execute_query(query);
}

bool Database::insert_property(const std::string& name, double price) {
    std::string query = "INSERT INTO properties (name, price) VALUES ('" + name + "', " + std::to_string(price) + ");";
    return execute_query(query);
}

void Database::get_properties() {
    std::string query = "SELECT * FROM properties;";
    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* name = sqlite3_column_text(stmt, 1);
        double price = sqlite3_column_double(stmt, 2);

        std::cout << "ID: " << id << ", Name: " << name << ", Price: " << price << std::endl;
    }

    sqlite3_finalize(stmt);
}
