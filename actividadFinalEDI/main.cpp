#include <iostream>
#include <string.h>
#include <Provinces.h>
#include <Parties.h>
#include <Towns.h>
#include "IDatabaseHandler.h"
#include "SqliteDatabaseHandler.h"


using namespace std;

int main()
{
    IDatabaseHandler* dbh = new SqliteDatabaseHandler();
    dbh->prepareQuery("CREATE TABLE IF NOT EXISTS provinces (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL, name VARCHAR(45) UNIQUE NOT NULL, uuid VARCHAR(45), code VARCHAR(45))");
    dbh->execute();
    dbh->prepareQuery("CREATE TABLE IF NOT EXISTS parties (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL, idProvinces INTEGER REFERENCES provinces(id) MATCH SIMPLE, uuid VARCHAR(45), name VARCHAR(45) UNIQUE NOT NULL, code VARCHAR(45));");
    dbh->execute();
    dbh->prepareQuery("CREATE TABLE IF NOT EXISTS towns (id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE NOT NULL, idParties INTEGER REFERENCES parties(id) MATCH SIMPLE, uuid VARCHAR(45), name VARCHAR(45) UNIQUE NOT NULL, postalCode VARCHAR(45));");
    dbh->execute();
/*
    dbh->prepareQuery("INSERT INTO provinces(name) VALUES(?)");
    dbh->addParameter(1, "Buenos Aires");
    dbh->execute();
*/
    Provinces *p = new Provinces("Buenos Aires", dbh);
/*
    dbh->prepareQuery("INSERT INTO parties(name,idProvinces) VALUES(?,?)");
    dbh->addParameter(1, "General Pueyrredón");
    dbh->addParameter(2, "1");
    dbh->execute();
*/
    Parties *pa = new Parties("General Pueyrredon", "1", dbh);
/*
    dbh->prepareQuery("INSERT INTO towns(name,idParties) VALUES(?,?)");
    dbh->addParameter(1, "Mar del Plata");
    dbh->addParameter(2, "1");
    dbh->execute();
*/
    Towns *t = new Towns("Mar del Plata","1", dbh);

    return 0;
}
