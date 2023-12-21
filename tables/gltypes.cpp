#include "gltypes.h"

void GLTypes::insertTypesFromCSV (string table ) {
    pqxx::connection c{"postgresql://mst:1628@localhost/nobleledger"};
    pqxx::work txn{c};

    ifstream gltypes;
    gltypes.open("./data/gl_types.csv");
    
    string insert = "insert into gl_account_type (type, description, create_date, create_user, update_date, update_user) values (";

    string line;
    while (getline(gltypes, line))
    {
        stringstream ss(line);
        string account_type;
        string description;
        string create_date;
        string create_user;
        string update_date;
        string update_user;

        getline(ss, account_type, ',');
        getline(ss, description, ',');
        getline(ss, create_date, ',');
        getline(ss, create_user, ',');
        getline(ss, update_date, ',');
        getline(ss, update_user, ',');

        // insert into gl_account_type (type, description, create_date, create_user, update_date, update_user) values ();

        char sqlBuffer[1000];
        string sql;
        //                   1  2    3   4    5    6    7  8    
        sprintf(sqlBuffer, "%s '%s','%s','%s','%s','%s','%s'%s",
                insert.c_str(),
                account_type.c_str(),                
                description.c_str(), 
                create_date.c_str(), 
                create_user.c_str(), 
                update_date.c_str(), 
                update_user.c_str(), 
                ");");

        string buffer(sqlBuffer);
        txn.exec(buffer);
    }

    result r = txn.exec("SELECT type from gl_account_type;");
    cout << "Truncated and inserted " << r.size() << " account types.\n";
    txn.commit();
}
  
void GLTypes::trunctateTypes (string table ) {
    pqxx::connection c{"postgresql://mst:1628@localhost/nobleledger"};
    pqxx::work txn{c};
    txn.exec("TRUNCATE TABLE gl_account_type;");
    txn.commit();
}

void GLTypes::updateAndTruncate() {
    trunctateTypes("gl_account_type");
    insertTypesFromCSV("gl_account_type");
}
