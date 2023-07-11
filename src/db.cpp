#include "db.h"

DB *DB::instance = nullptr;

DB::DB()
{
    driver = sql::mysql::get_mysql_driver_instance();

    // Azure SQL database connection parameters
    std::string server = "movie-recommendation-system.mysql.database.azure.com";
    int port = 3306; // Default port for Azure SQL database
    std::string username = "MRSAdmin";
    std::string password = std::getenv("MRSDB_PASSWORD");
    std::string database = "mrsdb";

    // Connection URL
    std::string url = "tcp://" + server + ":" + std::to_string(port);

    // Create connection
    con = driver->connect(url, username, password);

    // Select the database
    con->setSchema(database);
}

DB *DB::getInstance()
{
    if (instance == nullptr)
    {
        instance = new DB();
    }
    return instance;
}

sql::Connection *DB::getConnection()
{
    return con;
}

sql::ResultSet *DB::executeQuery(const std::string &query)
{
    sql::Statement *stmt = con->createStatement();
    sql::ResultSet *res = stmt->executeQuery(query);
    delete stmt;
    return res;
}

int DB::executeUpdate(const std::string &update)
{
    sql::Statement *stmt = con->createStatement();
    int count = stmt->executeUpdate(update);
    delete stmt;
    return count;
}

int DB::getLastInsertId()
{
    sql::Statement *stmt = con->createStatement();
    std::string query = "SELECT LAST_INSERT_ID()";
    sql::ResultSet *res = stmt->executeQuery(query);
    res->next();
    int id = res->getInt(1);
    delete stmt;
    return id;
}