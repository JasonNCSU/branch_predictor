//
// Created by Jason on 11/16/2019.
//

#include "branchpredictor.h"

using namespace std;

//Default constructor
BranchPredictor::BranchPredictor(void) {
    //set all values to 0 if it complains
}

//Setter methods, instead of constructor due to the way that C++ initializes objects
void BranchPredictor::bimodal_setter(int m2, char *file) {
    m2_bits = m2;
    trace_file = file;
}
void BranchPredictor::gshare_setter(int m1, int n, char *file) {
    m1_bits = m1;
    n_bits = n;
    trace_file = file;
}
void BranchPredictor::hybrid_setter(int k, int m1, int n, int m2, char *file) {
    k_bits = k;
    m1_bits = m1;
    n_bits = n;
    m2_bits = m2;
    trace_file = file;
}
//Setter methods, instead of constructor due to the way that C++ initializes objects

//Delegator Methods for each mode
void BranchPredictor::bimodal(char route, long value) {
    //TODO bimodal branch prediction
}
void BranchPredictor::gshare(char route, long value) {
    //TODO gshare branch prediction
}
void BranchPredictor::hybrid(char route, long value) {
    //TODO hybrid branch prediction
}
//Delegator Methods for each mode