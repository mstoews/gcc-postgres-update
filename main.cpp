#include <iostream>
#include <fstream>
#include <pqxx/pqxx>
#include <getopt.h>
#include <crow.h>

#include "./tables/glaccounts.h"
#include "./tables/gltypes.h"


using namespace std;
using namespace pqxx;


class NobleLogHandler : public crow::ILogHandler
{
public:
    void log(std::string message, crow::LogLevel /*level*/) override
    {
        std::cerr << "Log => " << message;
    }
};

struct JWTMiddleWare
{
    std::string message;

    JWTMiddleWare() : message("foo")
    {
    }

    void setMessage(const std::string &newMsg)
    {
        message = newMsg;
    }

    struct context
    {
    };

    void before_handle(crow::request & /*req*/, crow::response & /*res*/, context & /*ctx*/)
    {
        CROW_LOG_DEBUG << " - MESSAGE: " << message;
    }

    void after_handle(crow::request & /*req*/, crow::response & /*res*/, context & /*ctx*/)
    {
        // no-op
    }
};

int main(int argc, char *argv[])
{
    const int PORT = 43022;
    option longopts[] = {
        {"filename", optional_argument, NULL, 't'},
        {"connection", optional_argument, NULL, 'c'},
        {0}};

    crow::App<JWTMiddleWare> app;

    app.get_middleware<JWTMiddleWare>().setMessage("hello");

    app.loglevel(crow::LogLevel::Info);

    CROW_ROUTE(app, "/")
        .name("hello")([]
                       { return "<h1>Application Server</h1>"; });

    CROW_ROUTE(app, "/about")
    ([]()
     { return "<h1>Nobleledger Accounting<h1><h2>Application Server</h2>"; });

    CROW_ROUTE(app, "/types")
    ([]()
     { 
        GLTypes types;
        const int r = types.updateAndTruncate();
        const string s = to_string(r);
        return "<h1>Application Server</h1><h2>Loaded " + s + " general ledger accounts.<h2>"; });

    CROW_ROUTE(app, "/accounts")
    ([]()
     { 
        GLAccounts types;
        const int r = types.updateAndTruncate();
        const string s = to_string(r);
        return "<h1>Application Server</h1><h2>Loaded " + s + " account types.<h2>"; });
    

    // a request to /path should be forwarded to /path/
    CROW_ROUTE(app, "/path/")
    ([]()
     { return "Trailing slash test case.."; });

    
    
    // simple json response
    CROW_ROUTE(app, "/json")
    ([]
     {
                crow::json::wvalue x({{"message", "Hello, World!"}});
                x["message2"] = "Hello, World.. Again!";
                return x; });

    CROW_ROUTE(app, "/json-initializer-list-constructor")
    ([]
     { return crow::json::wvalue({
           {"first", "Hello world!"},                     /* stores a char const* hence a json::type::String */
           {"second", std::string("How are you today?")}, /* stores a std::string hence a json::type::String. */
           {"third", std::int64_t(1025)},                 /* stores a 64-bit int hence a std::int64_t. */
           {"fourth", std::uint64_t(54)},                 /* stores a 64-bit unsigned int hence a std::uint64_t. */
           {"fifth", 54},                                 /* stores an int (as 54 is an int literal) hence a std::int64_t. */
           {"sixth", 54u},                                /* stores an unsigned int (as 54u is a unsigned int literal) hence a std::uint64_t. */
           {"seventh", 2.f},                              /* stores a float (as 2.f is a float literal) hence a double. */
           {"eighth", 2.8989},                            /* stores a double (as 2. is a double literal) hence a double. */
           {"ninth", nullptr},                            /* stores a std::nullptr hence json::type::Null . */
           {"tenth", true}                                /* stores a bool hence json::type::True . */
       }); });

    // json list response
    CROW_ROUTE(app, "/json_list")
    ([]
     {
                crow::json::wvalue x(crow::json::wvalue::list({1, 2, 3}));
                return x; });

    // To see it in action enter {ip}:18080/hello/{integer_between -2^32 and 100} and you should receive
    // {integer_between -2^31 and 100} bottles of beer!
    CROW_ROUTE(app, "/hello/<int>")
    ([](int count)
     {
                if (count > 100)
                    return crow::response(400);
                std::ostringstream os;
                os << count << " bottles of beer!";
                return crow::response(os.str()); });

    app.port(PORT).multithreaded().run_async();

    // while (1)
    // {
    //     const int opt = getopt_long(argc, argv, "atc::", longopts, 0);

    //     if (opt == -1)
    //     {
    //         break;
    //     }

    //     switch (opt)
    //     {
    //     case 'a':
    //     {
    //         Transaction accounts;
    //         string table = "gl_accounts";
    //         accounts.trunctateTable(table);
    //         accounts.insertTableFromCSV(table);
    //         break;
    //     }
    //     case 't':
    //     {
    //         GLTypes types;
    //         string table = "gl_account_type";
    //         types.trunctateTypes(table);
    //         types.insertTypesFromCSV(table);
    //         break;
    //     }
    //     case 'c':
    //     {
    //         GLTypes types;
    //         types.updateAndTruncate();
    //         Transaction accounts;
    //         accounts.updateAndTruncate();
    //         break;
    //     }
    //     }
    // }
}
