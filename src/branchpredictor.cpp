//
// Created by Jason on 11/16/2019.
//

#include "branchpredictor.h"
#include <iostream>
#include <cmath>
#include <iomanip>

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

    gshare_global_history = 0;

    counter_min = 1;
    counter_max = 2;
    gshare_global_add = 0;

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
    bimodal_length = (1 << m2_bits);

    bimodal_array = new int[bimodal_length];
    initialize_bimodal_array();
}
void BranchPredictor::gshare_setter(int m1, int n, char *file) {
    m1_bits = m1;
    n_bits = n;
    trace_file = file;
    gshare_global_add = (1 << (n_bits - 1));
    gshare_length = (1 << m1_bits);

    gshare_array = new int[gshare_length];
    initialize_gshare_array();
}
void BranchPredictor::hybrid_setter(int k, int m1, int n, int m2, char *file) {
    k_bits = k;
    m1_bits = m1;
    n_bits = n;
    m2_bits = m2;
    trace_file = file;

    bimodal_length = (1 << m2_bits);
    gshare_global_add = (1 << (n_bits - 1));
    gshare_length = (1 << m1_bits);
    chooser_length = (1 << k_bits);

    bimodal_array = new int[bimodal_length];
    gshare_array = new int[gshare_length];
    chooser_array = new int[chooser_length];

    initialize_bimodal_array();
    initialize_gshare_array();
    initialize_chooser_array();
}
void BranchPredictor::route_setter(char route) {
    real_path = route;
}
//Setter methods, instead of constructor due to the way that C++ initializes objects

//Initialize Arrays
void BranchPredictor::initialize_bimodal_array(void) {
    for (int i = 0; i < bimodal_length; i++) {
        bimodal_array[i] = 2;
    }
}
void BranchPredictor::initialize_gshare_array(void) {
    for (int i = 0; i < gshare_length; i++) {
        gshare_array[i] = 2;
    }
}
void BranchPredictor::initialize_chooser_array(void) {
    for (int i = 0; i < chooser_length; i++) {
        chooser_array[i] = 1;
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
    int gshare_table_index = get_gshare_table_index(value);
    char gshare_predicted_path = gshare_prediction(gshare_table_index);
    verify_prediction(gshare_predicted_path);
    gshare_table_update(gshare_table_index);
    gshare_global_update();
}
void BranchPredictor::hybrid(long value) {
    int bimodal_table_index = get_bimodal_table_index(value);
    char bimodal_predicted_path = bimodal_prediction(bimodal_table_index);

    int gshare_table_index = get_gshare_table_index(value);
    char gshare_predicted_path = gshare_prediction(gshare_table_index);

    int chooser_table_index = get_chooser_table_index(value);
    char chooser_predicted_path = chooser_prediction(chooser_table_index);
    if (chooser_predicted_path == 'b') {
        verify_prediction(bimodal_predicted_path);
        bimodal_table_update(bimodal_table_index);
    } else {
        verify_prediction(gshare_predicted_path);
        gshare_table_update(gshare_table_index);
    }
    gshare_global_update();

    chooser_table_update(bimodal_predicted_path, gshare_predicted_path, chooser_table_index);
}
//Delegator Methods for each mode

//manipulate passed in value
int BranchPredictor::get_bimodal_table_index(long initial_value) {
    return ((1 << m2_bits) - 1) & (initial_value >> offset_bits);
}
int BranchPredictor::get_gshare_table_index(long initial_value) {
    int pc_m_plus1 = ((1 << m1_bits) - 1) & (initial_value >> offset_bits);
    int most_significant_index = (gshare_global_history ^ (pc_m_plus1 >> (m1_bits - n_bits))) << (m1_bits - n_bits);
    int least_significant_index = ((1 << (m1_bits - n_bits)) - 1) & pc_m_plus1;
    return (most_significant_index | least_significant_index);
}
int BranchPredictor::get_chooser_table_index(long initial_value) {
    return ((1 << k_bits) - 1) & (initial_value >> offset_bits);
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
char BranchPredictor::gshare_prediction(int gshare_table_index) {
    int counter = gshare_array[gshare_table_index];
    if (counter >= 2) {
        return 't';
    } else {
        return 'n';
    }
}
char BranchPredictor::chooser_prediction(int chooser_table_index) {
    int counter = chooser_array[chooser_table_index];
    if (counter >= 2) {
        return 'g';
    } else {
        return 'b';
    }
}
void BranchPredictor::verify_prediction(char prediction) {
    total_predictions++;
    if (prediction != real_path) {
        total_mispredictions++;
    }
}
//prediction associated methods

//update table methods
void BranchPredictor::bimodal_table_update(int bimodal_table_index) {
    int counter = bimodal_array[bimodal_table_index];
    if (real_path == 't') {
        if (counter >= counter_max) {
            bimodal_array[bimodal_table_index] = 3;
        } else {
            bimodal_array[bimodal_table_index]++;
        }
    } else {
        if (counter <= counter_min) {
            bimodal_array[bimodal_table_index] = 0;
        } else {
            bimodal_array[bimodal_table_index]--;
        }
    }
}
void BranchPredictor::gshare_table_update(int gshare_table_index) {
    int counter = gshare_array[gshare_table_index];
    if (real_path == 't') {
        if (counter >= counter_max) {
            gshare_array[gshare_table_index] = 3;
        } else {
            gshare_array[gshare_table_index]++;
        }
    } else {
        if (counter <= counter_min) {
            gshare_array[gshare_table_index] = 0;
        } else {
            gshare_array[gshare_table_index]--;
        }
    }
}
void BranchPredictor::gshare_global_update() {
    gshare_global_history >>= 1;
    if (real_path == 't') {
        gshare_global_history += gshare_global_add;
    }
}
void BranchPredictor::chooser_table_update(char bimodal_predicted_path, char gshare_predicted_path, int chooser_table_index) {
    int counter = chooser_array[chooser_table_index];

    if (bimodal_predicted_path != real_path && gshare_predicted_path == real_path) {
        if (counter >= counter_max) {
            chooser_array[chooser_table_index] = 3;
        } else {
            chooser_array[chooser_table_index]++;
        }
    } else if (bimodal_predicted_path == real_path && gshare_predicted_path != real_path) {
        if (counter <= counter_min) {
            chooser_array[chooser_table_index] = 0;
        } else {
            chooser_array[chooser_table_index]--;
        }
    }
}
//update table methods

//Print Statements
void BranchPredictor::print_result(int result, char *exe_command, char *mode, int btb_size, int btb_assoc) {

    //rounds misprediction rate to 2 decimals
    double temp = ((double) total_mispredictions / (double) total_predictions) * 10000;
    temp = lround(temp);
    misprediction_rate = temp / 100;
    //misprediction_rate = (double) (lround(((total_mispredictions / total_predictions) * 100)));

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
    cout << setprecision(2) << fixed << " " << "misprediction rate: " << misprediction_rate << "%" << endl;
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