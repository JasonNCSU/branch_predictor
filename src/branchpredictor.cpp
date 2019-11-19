//
// Created by Jason on 11/16/2019.
//

#include "branchpredictor.h"
#include <iostream>
#include <cmath>

using namespace std;

//Default constructor
BranchPredictor::BranchPredictor(void) {
    //set all values to 0 if it complains
    m2_bits = 0;
    n_bits = 0;
    m1_bits = 0;
    k_bits = 0;
    trace_file = nullptr;
    real_path = ' ';

    bimodal_array = nullptr;
    gshare_array = nullptr;
    chooser_array = nullptr;

    total_predictions = 0;
    total_mispredictions = 0;
    misprediction_rate = 0;

    bimodal_length = 0;
    gshare_length = 0;
    chooser_length = 0;
}

//Setter methods, instead of constructor due to the way that C++ initializes objects
void BranchPredictor::bimodal_setter(int m2, char *file) {
    m2_bits = m2;
    trace_file = file;

    bimodal_array = new int[m2_bits];
}
void BranchPredictor::gshare_setter(int m1, int n, char *file) {
    m1_bits = m1;
    n_bits = n;
    trace_file = file;

    gshare_array = new int[m1_bits];
}
void BranchPredictor::hybrid_setter(int k, int m1, int n, int m2, char *file) {
    k_bits = k;
    m1_bits = m1;
    n_bits = n;
    m2_bits = m2;
    trace_file = file;

    bimodal_array = new int[m2_bits];
    gshare_array = new int[m1_bits];
    chooser_array = new int[k_bits];
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

//print statements
void BranchPredictor::print_result(int result, char *exe_command, char *mode, int btb_size, int btb_assoc) {

    //rounds misprediction rate to 2 decimals
    misprediction_rate = (double) (lround(((total_mispredictions / total_predictions) * 100))) / 100;

    cout << "COMMAND" << endl;
    //bimodal
    if (result == 0) {
        cout << exe_command << " " << mode << " " << m2_bits << " " << btb_size << " " << btb_assoc << " " << trace_file << endl;
        BranchPredictor::print_predictions();
        BranchPredictor::print_bimodal_contents();
    }
    //gshare
    else if (result == 5) {
        cout << exe_command << " " << mode << " " << m1_bits << " " << n_bits << " " << btb_size << " " << btb_assoc << " " << trace_file << endl;
        BranchPredictor::print_predictions();
        BranchPredictor::print_gshare_contents();
    }
    //hybrid
    else {
        cout << exe_command << " " << mode << " " << k_bits << " " << m1_bits << " " << n_bits << " " << m2_bits << " " << btb_size << " " << btb_assoc << " " << trace_file << endl;
        BranchPredictor::print_predictions();
        BranchPredictor::print_chooser_contents();
        BranchPredictor::print_gshare_contents();
        BranchPredictor::print_bimodal_contents();
    }
}

void BranchPredictor::print_predictions(void) {
    cout << "OUTPUT" << endl;
    cout << " " << "number of predictions: " << total_predictions << endl;
    cout << " " << "number of mispredictions: " << total_mispredictions << endl;
    cout << " " << "misprediction rate: " << misprediction_rate << endl;
}

void BranchPredictor::print_bimodal_contents(void) {
    cout << "FINAL BIMODAL CONTENTS" << endl;
    for (int i = 0; i < bimodal_length; i++) {
        cout << i << " " << bimodal_array[i] << endl;
    }
}

void BranchPredictor::print_gshare_contents(void) {
    cout << "FINAL GSHARE CONTENTS" << endl;
    for (int i = 0; i < gshare_length; i++) {
        cout << i << " " << gshare_array[i] << endl;
    }
}

void BranchPredictor::print_chooser_contents(void) {
    cout << "FINAL CHOOSER CONTENTS" << endl;
    for (int i = 0; i < chooser_length; i++) {
        cout << i << " " << chooser_array[i] << endl;
    }
}