#include <mysql_driver.h>
#include <mysql_connection.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <string>

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

    void registerUser(const std::string &firstName, const std::string &lastName, const std::string &email, const std::string &password, bool &isAuthenticated);
    void loginUser(const std::string &email, const std::string &password, bool &isAuthenticated);
};
