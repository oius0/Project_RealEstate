#ifndef DATABASE_H
#define DATABASE_H

#include <sqlite3.h>
#include <string>

class Database {
public:
    Database(const std::string& db_name);
    ~Database();

    bool execute_query(const std::string& query);
    bool create_table();
    bool insert_property(const std::string& name, double price);
    void get_properties();

private:
    sqlite3* db;
};

#endif // DATABASE_H
