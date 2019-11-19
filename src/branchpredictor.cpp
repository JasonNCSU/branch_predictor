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
void BranchPredictor::route_setter(char route) {
    real_path = route;
}
//Setter methods, instead of constructor due to the way that C++ initializes objects

//Delegator Methods for each mode
void BranchPredictor::bimodal(long value) {
    //TODO bimodal branch prediction
}
void BranchPredictor::gshare(long value) {
    //TODO bimodal branch prediction
}
void BranchPredictor::hybrid(long value) {
    //TODO bimodal branch prediction
}
//Delegator Methods for each mode

void BranchPredictor::verify_prediction(char prediction) {
    total_predictions++;
    if (prediction != real_path) {
        total_mispredictions++;
    }
}

void BranchPredictor::print_result(int result, char *exe_command, char *mode, int btb_size, int btb_assoc) {

    //rounds misprediction rate to 2 decimals
    misprediction_rate = total_mispredictions / total_predictions;
    misprediction_rate = (int) (misprediction_rate * 100 + 0.5);
    misprediction_rate = misprediction_rate / 100;

    //bimodal
    if (result == 0) {
        
    }
    //gshare
    else if (result == 5) {

    }
    //hybrid
    else {

    }
}