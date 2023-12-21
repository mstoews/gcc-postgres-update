#include <iostream>
#include <fstream>
#include <pqxx/pqxx>
#include <getopt.h>

#include "./tables/glaccounts.h"
#include "./tables/gltypes.h"

using namespace std;
using namespace pqxx;

int main(int argc, char *argv[]) {
     option longopts[] = {
        {"filename", optional_argument, NULL, 't'}, 
        {"connection", optional_argument, NULL, 'c'}, {0}
     };

        while (1) {
        const int opt = getopt_long(argc, argv, "atc::", longopts, 0);

        if (opt == -1) {
            break;
        }

        switch (opt) {
            case 'a': {
                    Transaction accounts;
                    string table = "gl_accounts";
                    accounts.trunctateTable(table);
                    accounts.insertTableFromCSV(table);
                    break;
            }
            case 't': {
                    GLTypes types;
                    string table = "gl_account_type";
                    types.trunctateTypes(table);
                    types.insertTypesFromCSV(table);
                    break;
            }
            case 'c':
                break;
        }
    }
}


