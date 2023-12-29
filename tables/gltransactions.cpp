#include "gltransactions.h"

int GLJournalTransactions::insertTransactionsFromCSV () {
    connection c{"postgresql://mst:1628@localhost/nobleledger"};
    work txn{c};

    ifstream glaccounts;
    glaccounts.open("./data/gl_transaction.csv");

    string insert = "INSERT INTO gl_journal_header (journal_id, description, booked, booked_date,booked_user, create_date, create_user)  VALUES (";
    
    string journal_id;
    string journal_sub_id;
    string account;
    string child_account;
    string description;
    string debit;
    string credit;
    char sqlBuffer[1000];
        
    string line;
    while (getline(glaccounts, line))
    {
        stringstream ss(line);
        getline(ss, journal_id, ',');
        getline(ss, journal_sub_id, ',');
        getline(ss, account, ',');
        getline(ss, child_account, ',');
        getline(ss, description, ',');
        getline(ss, debit, ',');
        getline(ss, credit, ',');

        sprintf(sqlBuffer, "%s '%s','%s',%s,'%s','%s','%s',%s",
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
    return r.size();
}
  
void GLJournalTransactions::trunctateTransaction () {
    pqxx::connection c{"postgresql://mst:1628@localhost/nobleledger"};
    pqxx::work txn{c};
    txn.exec("TRUNCATE TABLE gl_distribution;");
    txn.commit();
}

int GLJournalTransactions::truncateAndUpdate() {
    trunctateTransaction();
    return insertTransactionsFromCSV();
}
