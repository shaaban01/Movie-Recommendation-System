#include "db.h"
#include <iostream>

DB *DB::instance = nullptr;

DB::DB() {
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306/MRS", "root", "2003!!2003@@");
}

DB *DB::getInstance() {
    if (instance == nullptr) {
        instance = new DB();
    }
    return instance;
}

sql::Connection *DB::getConnection() {
    return con;
}

sql::ResultSet* DB::executeQuery(const std::string& query) {
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res = stmt->executeQuery(query);
    delete stmt;
    return res;
}

int DB::executeUpdate(const std::string& update) {
    sql::Statement *stmt = con->createStatement();
    int count = stmt->executeUpdate(update);
    delete stmt;
    return count;
}
