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

    int m2_bits;
    int btb_size; //ignored since extra credit
    int btb_assoc; //ignored since extra credit

    int m1_bits;
    int n_bits;

    int k_bits;

    mode = argv[1];

    int result = strcmp(mode, "bimodal");
    if (result == 0) {
        m2_bits = strtol(argv[2], nullptr, 10);
        btb_size = strtol(argv[3], nullptr, 10);
        btb_assoc = strtol(argv[4], nullptr, 10);
        trace_file = argv[5];

        BranchPredictor branch_predict(m2_bits, trace_file);
    } else if (result == 5) {
        m1_bits = strtol(argv[2], nullptr, 10);
        n_bits = strtol(argv[3], nullptr, 10);
        btb_size = strtol(argv[4], nullptr, 10);
        btb_assoc = strtol(argv[5], nullptr, 10);
        trace_file = argv[6];

        BranchPredictor branch_predict(m1_bits, n_bits, trace_file);
    } else {
        k_bits = strtol(argv[2], nullptr, 10);
        m1_bits = strtol(argv[3], nullptr, 10);
        n_bits = strtol(argv[4], nullptr, 10);
        m2_bits = strtol(argv[5], nullptr, 10);
        btb_size = strtol(argv[6], nullptr, 10);
        btb_assoc = strtol(argv[7], nullptr, 10);
        trace_file = argv[8];

        BranchPredictor branch_predict(k_bits, m1_bits, n_bits, m2_bits, trace_file);
    }

    //Reads in trace file
    string data_segment;
    ifstream input(trace_file);
    while (getline(input, data_segment)) {
        //do stuff with each input
        if (strcmp(mode, "bimodal") == 0) {

        } else if (strcmp(mode, "gshare") == 0) {

        } else {

        }
    }

    //Signals the end of the program
    return 0;
}
