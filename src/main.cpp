#include <iostream>
//#include "cxxopts.hpp"
#include "test.h"
#include "drivemodbus.h"

using namespace std;

void parse_args(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    try {
        parse_args(argc, argv);
        Test test;
    }
    catch (exception& e) {
        cerr << "Error. " << e.what() << endl;
        return 1;
    }
    catch (...) {
        cerr << "Unknown error" << endl;
        return 1;
    }

    cout << flush;

    return 0;
}

void parse_args(int argc, char *argv[]) {
    (void)argc;
    (void)argv;
}
