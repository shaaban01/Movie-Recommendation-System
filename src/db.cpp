#include <chrono>
#include "db.h"

DB *DB::instance = nullptr;

DB::DB()
{
    static const auto start = std::chrono::steady_clock::now();

    driver = sql::mysql::get_mysql_driver_instance();

    // Azure SQL database connection parameters
    static const std::string server = "movie-recommendation-system.mysql.database.azure.com";
    static const int port = 3306; // Default port for Azure SQL database
    static const std::string username = "MRSAdmin";
    static const std::string password = std::getenv("MRSDB_PASSWORD");
    static const std::string database = "mrsdb";

    // Connection URL
    static const std::string url = "tcp://" + server + ":" + std::to_string(port);

    // Create connection
    con = driver->connect(url, username, password);

    // Select the database
    con->setSchema(database);

    static const auto end = std::chrono::steady_clock::now();
    static const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    std::cout << "Connection created in " << duration << " milliseconds." << std::endl;
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

sql::PreparedStatement *DB::prepareStatement(const std::string &query)
{
    return con->prepareStatement(query);
}
