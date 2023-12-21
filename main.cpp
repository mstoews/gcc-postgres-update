#include <iostream>
#include <fstream>
#include <pqxx/pqxx>
#include "glaccounts.h"

using namespace std;
using namespace pqxx;

int main(int, char *argv[])
{
    // pqxx::connection c{"postgresql://mst:1628@localhost/nobleledger"};
    Transaction t;
    string table = "gl_accounts";
    t.trunctateTable(table);
    t.insertTableFromCSV(table);
}


