//
// Created by Jason on 11/16/2019.
//

#ifndef PROJECT_BRANCHPREDICTOR_H
#define PROJECT_BRANCHPREDICTOR_H


class BranchPredictor {
private:
    //methods

    //variables


public:
    //constructors
    BranchPredictor(void);
    BranchPredictor(int m2_bits, char *trace_file);
    BranchPredictor(int m1_bits, int n_bits, char *trace_file);
    BranchPredictor(int k_bits, int m1_bits, int n_bits, int m2_bits, char *trace_file);

    //other public methods

};


#endif //PROJECT_BRANCHPREDICTOR_H
