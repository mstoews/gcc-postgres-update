#include <iostream>
#include <fstream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

class GLJournalTransactions {
    public:
        void trunctateTransaction(string table);
        void insertTransactionsFromCSV(string table);
        void truncateAndUpdate();    
};   

