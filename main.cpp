#include <iostream>
#include <fstream>
#include <pqxx/pqxx>
#include <getopt.h>
#include "glaccounts.h"

using namespace std;
using namespace pqxx;

int main(int argc, char *argv[]) {
     option longopts[] = {
        {"filename", optional_argument, NULL, 't'}, 
        {"connection", optional_argument, NULL, 'c'}, {0}
     };

        while (1) {
        const int opt = getopt_long(argc, argv, "tc::", longopts, 0);

        if (opt == -1) {
            break;
        }

        switch (opt) {
            case 't': {
                    Transaction t;
                    string table = "gl_accounts";
                    t.trunctateTable(table);
                    break;
            }
            case 'c':
                break;
        }
    }

    Transaction t;
    string table = "gl_accounts";    
    t.insertTableFromCSV(table);
}


