#ifndef DB_H
#define DB_H

#include <mysql_driver.h>
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <string>
#include <iostream>

class DB
{
private:
    static DB *instance;
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

    DB();
    DB(const DB &) = delete;
    DB &operator=(const DB &) = delete;

    sql::Connection *getConnection();

public:
    static DB *getInstance();
    sql::ResultSet *executeQuery(const std::string &query);
    int executeUpdate(const std::string &update);
    int getLastInsertId();
};

#endif // DB_H