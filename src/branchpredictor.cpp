//
// Created by Jason on 11/16/2019.
//

#include "branchpredictor.h"
#include <iostream>
#include <cmath>

using namespace std;

//Default Constructor
BranchPredictor::BranchPredictor(void) {
    //set all values to 0 if it complains
    offset_bits = 2;

    m2_bits = 0;
    n_bits = 0;
    m1_bits = 0;
    k_bits = 0;
    trace_file = nullptr;
    real_path = ' ';

    bimodal_array = nullptr;
    gshare_array = nullptr;
    chooser_array = nullptr;

    bimodal_min = 1;
    bimodal_max = 2;

    total_predictions = 0;
    total_mispredictions = 0;
    misprediction_rate = 0;

    bimodal_length = 0;
    gshare_length = 0;
    chooser_length = 0;
}
//Default Constructor

//Setter methods, instead of constructor due to the way that C++ initializes objects
void BranchPredictor::bimodal_setter(int m2, char *file) {
    m2_bits = m2;
    trace_file = file;

    bimodal_array = new int[m2_bits];
    initialize_bimodal_array();
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

//Initialize Arrays
void BranchPredictor::initialize_bimodal_array(void) {
    for (int i = 0; i < m2_bits; i++) {
        bimodal_array[i] = 2;
    }
}
//Initialize Arrays

//Delegator Methods for each mode
void BranchPredictor::bimodal(long value) {
    int bimodal_table_index = get_bimodal_table_index(value);
    char bimodal_predicted_path = bimodal_prediction(bimodal_table_index);
    verify_prediction(bimodal_predicted_path);
    bimodal_table_update(bimodal_table_index);
}
void BranchPredictor::gshare(long value) {
    //TODO gshare branch prediction
}
void BranchPredictor::hybrid(long value) {
    //TODO hybrid branch prediction
}
//Delegator Methods for each mode

//manipulate passed in value
int BranchPredictor::get_bimodal_table_index(long initial_value) {
    return ((1 << m2_bits+1) - 1) & (initial_value >> offset_bits);
}
//manipulate passed in value

//prediction associated methods
char BranchPredictor::bimodal_prediction(int bimodal_table_index) {
    int counter = bimodal_array[bimodal_table_index];
    if (counter >= 2) {
        return 't';
    } else {
        return 'n';
    }
}
void BranchPredictor::verify_prediction(char prediction) {
    total_predictions++;
    if (prediction != real_path) {
        total_mispredictions++;
    }
}
void BranchPredictor::bimodal_table_update(int bimodal_table_index) {
    int counter = bimodal_array[bimodal_table_index];
    if (real_path == 't') {
        if (counter >= bimodal_max) {
            bimodal_array[bimodal_table_index] = 3;
        } else {
            bimodal_array[bimodal_table_index]++;
        }
    } else {
        if (counter <= bimodal_min) {
            bimodal_array[bimodal_table_index] = 0;
        } else {
            bimodal_array[bimodal_table_index]--;
        }
    }
}
//prediction associated methods

//Print Statements
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
//Print Statements