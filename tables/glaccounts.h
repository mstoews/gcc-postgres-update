#include <iostream>
#include <fstream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

class Transaction {
    public:
        void trunctateTable(string table);
        void insertTableFromCSV(string table);
        void updateAndTruncate();
    
};   

