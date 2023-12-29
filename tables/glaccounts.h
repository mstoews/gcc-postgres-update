#include <iostream>
#include <fstream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

class GLAccounts {
    public:
        void trunctateTable();
        int insertTableFromCSV();
        int updateAndTruncate();
    
};   

