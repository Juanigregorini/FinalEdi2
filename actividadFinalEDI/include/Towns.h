#ifndef TOWNS_H
#define TOWNS_H
#include <SqliteDatabaseHandler.h>

class Towns
{
    private:
        int id;
        string uuid,name,postalCode,idParties;
    public:
        Towns(string name, string idParties, IDatabaseHandler* dbh){
            dbh->prepareQuery("INSERT INTO towns(name,idParties) VALUES(?,?)");
            dbh->addParameter(1, name);
            dbh->addParameter(2, idParties);
            dbh->execute();
        }
        virtual ~Towns() {}
        int getId(){
            return this->id;
        }
        string getIdParties(){
            return this->idParties;
        }
        string getUuid(){
            return this->uuid;
        }
        string getName (){
            return this->name;
        }
        string getPostalCode (){
            return this->postalCode;
        }
        void setId(int id){
            this->id = id;
        }
        void setIdParties(string id){
            this->idParties = id;
        }
        void setUuid(string uuid){
            this->uuid = uuid;
        }
        void setName(string name){
            this->name = name;
        }
        void setPostalCode(string postalCode){
            this->postalCode = postalCode;
        }

};

#endif // TOWNS_H
