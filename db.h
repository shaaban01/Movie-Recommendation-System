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
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

    sql::Connection *getConnection();

public:
    void registerUser(const std::string &firstName, const std::string &lastName, const std::string &email, const std::string &password);
    void loginUser(const std::string &email, const std::string &password);
};
