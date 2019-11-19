//
// Created by Iason Katsaros on 11/16/2019.
// Student ID: 200089673
//

#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv) {
    //Takes in original specs
    //argv[0] is the program name, so we start with 1 as our inputs
    //strtol(arg, nullptr, 10) gets the argument as an int
    //char *varible_name = arg gets the argument as a char array
    int variable_name = strtol(argv[1], nullptr, 10);
    char *trace_file = argv[8];

    //Reads in trace file
    string data_segment;
    ifstream input(trace_file);
    while (getline(input, data_segment)) {
        //do stuff with each input

    }

    //Signals the end of the program
    return 0;
}
