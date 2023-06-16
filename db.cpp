#include "db.h"

using namespace std;

sql::Connection *DB::getConnection()
{
    driver = sql::mysql::get_mysql_driver_instance();
    con = driver->connect("tcp://127.0.0.1:3306", "root", "2003!!2003@@");
    return con;
}

void DB::registerUser(const string &firstName, const string &lastName, const string &email, const std::string &password, bool &isAuthenticated)
{
    sql::Connection *con = getConnection();

    try
    {
        sql::Statement *stmt = con->createStatement();
        stmt->execute("INSERT INTO MRS.users (firstname, lastname, email, password) VALUES ('" + firstName + "', '" + lastName + "', '" + email + "', '" + password + "')");
        delete stmt;
        cout << "Registration successful!\n";
        isAuthenticated = true;
    }
    catch (sql::SQLException &e)
    {
        cout << "ERROR!!\n";
    }

    delete con;
}

void DB::loginUser(const std::string &email, const std::string &password, bool &isAuthenticated)
{
    sql::Connection *con = getConnection();

    try
    {
        sql::Statement *stmt = con->createStatement();
        sql::ResultSet *res = stmt->executeQuery("SELECT * FROM MRS.users WHERE email='" + email + "'");

        if (res->next())
        {
            std::string storedPassword = res->getString("password");
            if (password == storedPassword)
            {
                cout << "Login successful!" << endl;
                isAuthenticated = true;
            }
            else
            {
                cout << "Incorrect password. Please try again." << endl;
            }
        }
        else
        {
            cout << "Email does not exist. Please try again." << endl;
        }

        delete res;
        delete stmt;
    }
    catch (sql::SQLException &e)
    {
        cout << "ERROR!!!\n";
    }

    delete con;
}
