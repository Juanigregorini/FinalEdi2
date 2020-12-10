#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <sqlite3.h> // require sqlite3 install on GNU/LINUX

#include <IDatabaseHandler.h>

typedef std::unordered_map< std::string, std::string > Row; 
typedef std::vector< Row > Table; 

class SqliteDatabaseHandler : public IDatabaseHandler
{
    private:
        sqlite3* pDB;
        sqlite3_stmt* stmt;
        bool errorStatus;
        Row row;
        Table table;
        std::string columnName;
        std::string columnValue;
        int columnCount;

    public:
        SqliteDatabaseHandler()
        {
            errorStatus = false;
            std::string path = "./test.db";

            int iReturn = sqlite3_open(path.c_str(), &pDB);
            if (iReturn != SQLITE_OK) 
            {  
                errorStatus = true;
                std::cerr << "Error open DB " << sqlite3_errmsg(pDB) << std::endl; 
                exit(-1);
            }
            stmt = nullptr;
        }
        
        ~SqliteDatabaseHandler()
        {
            sqlite3_finalize(stmt);
            sqlite3_close(pDB);
        }
        
        bool getErrorStatus()
        { 
            return this->errorStatus; 
        } 

        void prepareQuery( std::string query )
        {
            int iReturn = sqlite3_prepare_v2(pDB, query.c_str(), query.size() + 1, &stmt, 0);
            if (iReturn != SQLITE_OK) { errorStatus = true; sqlite3_close(pDB); exit(-1); }
        }

        void addParameter( int index, std::string value )
        {
            int iReturn = sqlite3_bind_text(stmt, index, value.c_str(), value.size(), 0);
            if (iReturn != SQLITE_OK) { errorStatus = true; exit(-1); }
        }

        void execute()
        {
            //sqlite3_reset(stmt);
            //sqlite3_clear_bindings(stmt);
            sqlite3_step(stmt);
        }

        Row fetch()
        {
            row.clear();
            sqlite3_step(stmt);
            columnCount = sqlite3_column_count(stmt);
            for( int i = 0; i < columnCount; i++ )
            {
                columnName = std::string( (char *)sqlite3_column_name(stmt, i) );
                columnValue = std::string( (char *)sqlite3_column_text( stmt, i ) );
                row[columnName] = columnValue;           
            }   
            return row; 
        }

        Table fetchAll()
        {
            table.clear();
            row.clear();
            columnCount = sqlite3_column_count(stmt);
            while(sqlite3_step(stmt)==SQLITE_ROW)
            {
                row.clear();
                for( int i = 0; i < columnCount; i++ )
                {
                    columnName = std::string( (char *)sqlite3_column_name(stmt, i) );
                    columnValue = std::string( (char *)sqlite3_column_text( stmt, i ) );
                    row[columnName] = columnValue;
                } 
                table.push_back(row);
            }

            return table;
        }
};

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