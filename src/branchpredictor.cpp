//
// Created by Jason on 11/16/2019.
//

#include "branchpredictor.h"

using namespace std;

//Default constructor, this shouldn't run...
BranchPredictor::BranchPredictor(void) {
    //set all values to 0 if it complains
}

//Bimodal constructor
BranchPredictor::BranchPredictor(int m2_bits, char *trace_file) {

}

//Gshare constructor
BranchPredictor::BranchPredictor(int m1_bits, int n_bits, char *trace_file) {

}

//Hybrid constructor
BranchPredictor::BranchPredictor(int k_bits, int m1_bits, int n_bits, int m2_bits, char *trace_file) {

}
