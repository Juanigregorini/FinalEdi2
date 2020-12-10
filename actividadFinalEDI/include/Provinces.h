#ifndef PROVINCES_H
#define PROVINCES_H
#include <SqliteDatabaseHandler.h>

using namespace std;

class Provinces
{
    private:
        int id;
        string uuid,name,code;

    public:
        Provinces(string name, IDatabaseHandler* dbh){
                dbh->prepareQuery("INSERT INTO provinces(name) VALUES(?)");
                dbh->addParameter(1, name);
                dbh->execute();
        }
        virtual ~Provinces() {}
        int getId(){
            return this->id;
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

#endif // PROVINCES_H
