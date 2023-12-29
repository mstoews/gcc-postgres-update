#include <iostream>
#include <fstream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

class GLJournalTransactions {
    public:
        void trunctateTransaction();
        int insertTransactionsFromCSV();
        int truncateAndUpdate();    
};   

