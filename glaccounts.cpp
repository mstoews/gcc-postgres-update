#include "glaccounts.h"

void Transaction::insertTableFromCSV (string table ) {
    pqxx::connection c{"postgresql://mst:1628@localhost/nobleledger"};
    pqxx::work txn{c};

    ifstream glaccounts;
    glaccounts.open("./data/gl_accounts.csv");
    
    string insert = "INSERT INTO gl_accounts (account,child, parent_account, type, sub_type, description, balance, comments, create_date, create_user,update_date, update_user)  VALUES (";

    string line;
    while (getline(glaccounts, line))
    {
        stringstream ss(line);
        string account;
        string child;
        string parent_account;
        string type;
        string sub_type;
        string description;
        string balance;
        string comments;
        string create_date;
        string create_user;
        string update_date;
        string update_user;

        getline(ss, account, ',');
        getline(ss, child, ',');
        getline(ss, parent_account, ',');
        getline(ss, type, ',');
        getline(ss, sub_type, ',');
        getline(ss, description, ',');
        getline(ss, balance, ',');
        getline(ss, comments, ',');
        getline(ss, create_date, ',');
        getline(ss, create_user, ',');
        getline(ss, update_date, ',');
        getline(ss, update_user, ',');

        // account, child, parent_account, type, sub_type, description, balance, comments, create_date, create_user,update_date, update_user

        char sqlBuffer[1000];
        string sql;
        
        sprintf(sqlBuffer, "%s '%s','%s',%s,'%s','%s','%s',%s,'%s','%s','%s','%s','%s'%s",
                insert.c_str(),
                account.c_str(),
                child.c_str(),
                parent_account.c_str(),
                type.c_str(),
                sub_type.c_str(),
                description.c_str(), 
                balance.c_str(), 
                comments.c_str(), 
                create_date.c_str(), 
                create_user.c_str(), 
                update_date.c_str(), 
                update_user.c_str(), 
                ");");

        string buffer(sqlBuffer);
        txn.exec(buffer);
    }

    result r = txn.exec("SELECT account, child, parent_account from gl_accounts;");
    cout << "Truncated and inserted " << r.size() << " general ledger accounts.\n";
    txn.commit();
}
  
void Transaction::trunctateTable (string table ) {
    pqxx::connection c{"postgresql://mst:1628@localhost/nobleledger"};
    pqxx::work txn{c};
    txn.exec("TRUNCATE TABLE gl_accounts;");
    txn.commit();
}
