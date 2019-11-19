//
// Created by Jason on 11/16/2019.
//

#ifndef PROJECT_BRANCHPREDICTOR_H
#define PROJECT_BRANCHPREDICTOR_H


class BranchPredictor {
private:
    //methods============================

    //variables==========================
    char *trace_file;
    int m2_bits;
    int m1_bits;
    int n_bits;
    int k_bits;

    char real_path;

public:
    //constructors=======================
    BranchPredictor(void);

    //other public methods===============
    void bimodal_setter(int m2_bits, char *trace_file);
    void gshare_setter(int m1_bits, int n_bits, char *trace_file);
    void hybrid_setter(int k_bits, int m1_bits, int n_bits, int m2_bits, char *trace_file);
    void route_setter(char route);

    void bimodal(long value);
    void gshare(long value);
    void hybrid(long value);
};


#endif //PROJECT_BRANCHPREDICTOR_H
