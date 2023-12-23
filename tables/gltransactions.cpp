#include "gltransactions.h"

void GLJournalTransactions::insertTransactionsFromCSV (string table ) {
    connection c{"postgresql://mst:1628@localhost/nobleledger"};
    work txn{c};

    ifstream glaccounts;
    glaccounts.open("./data/gl_transaction.csv");
    
    // 1,1,1000,Accounts Receivable - Rev Received,Operating,2000 ,0 
    // journal_id  integer not null    
    // description varchar(40),
    // booked      boolean,
    // booked_date date,
    // booked_user varchar(20),
    // create_date date,
    // create_user varchar(20)

    string insert = "INSERT INTO gl_accounts (journal_id, description, booked, booked_date,booked_user, create_date, create_user)  VALUES (";

    string line;
    while (getline(glaccounts, line))
    {
        stringstream ss(line);
        string journal_id;
        string journal_sub_id;
        string account;
        string child_account;
        string description;
        string debit;
        string credit;
        
        // account, child, parent_account, type, sub_type, description, balance, comments, create_date, create_user,update_date, update_user

        char sqlBuffer[1000];
        string sql;
        
        sprintf(sqlBuffer, "%s '%s','%s',%s,'%s','%s','%s',%s,'%s','%s','%s','%s','%s'%s",
                insert.c_str(),
                journal_id.c_str(),
                account.c_str(),
                child_account.c_str(),
                description.c_str(),
                debit.c_str(),
                credit.c_str(),
                ");");
                
        string buffer(sqlBuffer);
        txn.exec(buffer);
    }

    result r = txn.exec("SELECT account, child, parent_account from gl_accounts;");
    cout << "Truncated and inserted " << r.size() << " general ledger accounts.\n";
    txn.commit();
}
  
void GLJournalTransactions::trunctateTransaction (string table ) {
    pqxx::connection c{"postgresql://mst:1628@localhost/nobleledger"};
    pqxx::work txn{c};
    txn.exec("TRUNCATE TABLE gl_;");
    txn.commit();
}

void GLJournalTransactions::truncateAndUpdate() {
    trunctateTransaction("gl_accounts");
    insertTransactionsFromCSV("gl_accounts");
}
