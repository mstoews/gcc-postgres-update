#include <iostream>
#include <fstream>
#include <pqxx/pqxx>

using namespace std;
using namespace pqxx;

class GLTypes {
    public:
        void trunctateTypes(string table);
        void insertTypesFromCSV(string table);
        void updateAndTruncate();
    
};   

