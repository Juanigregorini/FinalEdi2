#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "IDatabaseHandler.h"
#include "SqliteDatabaseHandler.h"

typedef std::unordered_map< std::string, std::string > Row;
typedef std::vector< Row > Table;
int main()
{
    IDatabaseHandler* dbh = new SqliteDatabaseHandler();

    dbh->prepareQuery("CREATE TABLE IF NOT EXISTS Users (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT)");
    dbh->execute();

    dbh->prepareQuery("INSERT INTO Users(name) VALUES(?)");
    dbh->addParameter(1, "Juan");
    dbh->execute();

    dbh->prepareQuery("INSERT INTO Users(name) VALUES(?)");
    dbh->addParameter(1, "Pedro");
    dbh->execute();

    //ROW DATA:
    dbh->prepareQuery("SELECT * FROM Users WHERE id=?1");
    dbh->addParameter(1, "1");
    Row row = dbh->fetch();

    std::cout << "ROW DATA 1" << std::endl;
    std::cout << "id: " << row["id"] << std::endl;
    std::cout << "name: " << row["name"] << std::endl << std::endl;

    dbh->prepareQuery("SELECT * FROM Users WHERE id=?1");
    dbh->addParameter(1, "2");
    row = dbh->fetch();

    std::cout << "ROW DATA 2" << std::endl;
    std::cout << "id: " << row["id"] << std::endl;
    std::cout << "name: " << row["name"] << std::endl << std::endl;

    //TABLE DATA:
    dbh->prepareQuery("SELECT * FROM Users");
    Table table = dbh->fetchAll();

    std::cout << "Table DATA row 1:" << std::endl;
    std::cout << "id: " << table[0]["id"] << std::endl;
    std::cout << "name: " << table[0]["name"] << std::endl << std::endl;

    std::cout << "Table DATA row 2:" << std::endl;
    std::cout << "id: " << table[1]["id"] << std::endl;
    std::cout << "name: " << table[1]["name"] << std::endl;

    delete dbh;
    return 0;
}
