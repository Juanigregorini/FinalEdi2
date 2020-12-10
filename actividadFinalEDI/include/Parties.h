#ifndef PARTIES_H
#define PARTIES_H
#include <SqliteDatabaseHandler.h>

class Parties
{
    private:
        int id;
        string uuid,name,code,idProvinces;

    public:
        Parties(string name, string idProvinces, IDatabaseHandler* dbh){
            dbh->prepareQuery("INSERT INTO parties(name,idProvinces) VALUES(?,?)");
            dbh->addParameter(1, name);
            dbh->addParameter(2, idProvinces);
            dbh->execute();
        }
        virtual ~Parties() {}
        int getId(){
            return this->id;
        }
        string getIdProvicens(){
            return this->idProvinces;
        }
        string getUuid(){
            return this->uuid;
        }
        string getName (){
            return this->name;
        }
        string getCode (){
            return this->code;
        }
        void setId(int id){
            this->id = id;
        }
        void setIdProvinces(string idProvinces){
            this->idProvinces = idProvinces;
        }
        void setUuid(string uuid){
            this->uuid = uuid;
        }
        void setName(string name){
            this->name = name;
        }
        void setCode(string code){
            this->code = code;
        }
};

#endif // PARTIES_H
