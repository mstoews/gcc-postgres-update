#include <iostream>
#include <fstream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

class GLJournalTransactions {
    public:
        int bookTransaction(int transaction_id);
        void trunctateTransaction();
        int insertTransactionsFromCSV();
        int truncateAndUpdate();    
};   

