//
// Created by Iason Katsaros on 11/16/2019.
// Student ID: 200089673
//

#include "branchpredictor.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv) {
    //Takes in original specs
    //argv[0] is the program name, so we start with 1 as our inputs
    //strtol(arg, nullptr, 10) gets the argument as an int
    //char *varible_name = arg gets the argument as a char array
    char *trace_file;
    char *mode;
    char *exe_command;

    int m2_bits;
    int btb_size; //ignored since extra credit
    int btb_assoc; //ignored since extra credit

    int m1_bits;
    int n_bits;

    int k_bits;

    exe_command = argv[0];
    mode = argv[1];
    BranchPredictor branch_predict;

    int result = strcmp(mode, "bimodal");
    //bimodal
    if (result == 0) {
        m2_bits = strtol(argv[2], nullptr, 10);
        btb_size = strtol(argv[3], nullptr, 10);
        btb_assoc = strtol(argv[4], nullptr, 10);
        trace_file = argv[5];

        branch_predict.bimodal_setter(m2_bits, trace_file);
    }
    //gshare
    else if (result == 5) {
        m1_bits = strtol(argv[2], nullptr, 10);
        n_bits = strtol(argv[3], nullptr, 10);
        btb_size = strtol(argv[4], nullptr, 10);
        btb_assoc = strtol(argv[5], nullptr, 10);
        trace_file = argv[6];

        branch_predict.gshare_setter(m1_bits, n_bits, trace_file);
    }
    //hybrid
    else {
        k_bits = strtol(argv[2], nullptr, 10);
        m1_bits = strtol(argv[3], nullptr, 10);
        n_bits = strtol(argv[4], nullptr, 10);
        m2_bits = strtol(argv[5], nullptr, 10);
        btb_size = strtol(argv[6], nullptr, 10);
        btb_assoc = strtol(argv[7], nullptr, 10);
        trace_file = argv[8];

        branch_predict.hybrid_setter(k_bits, m1_bits, n_bits, m2_bits, trace_file);
    }

    //Reads in trace file
    string data_segment;
    long value;
    char real_route;

    ifstream input(trace_file);
    while (getline(input, data_segment)) {
        real_route = data_segment.at(7);
        value = strtol(data_segment.substr(0, 5).c_str(), nullptr, 10);

        //sets the branch taken/not-taken value
        branch_predict.route_setter(real_route);
        //bimodal
        if (result == 0) {
            branch_predict.bimodal(value);
        }
        //gshare
        else if (result == 5) {
            branch_predict.gshare(value);
        }
        //hybrid
        else {
            branch_predict.hybrid(value);
        }
    }

    branch_predict.print_result(result, exe_command, mode, btb_size, btb_assoc);

    //Signals the end of the program
    return 0;
}
