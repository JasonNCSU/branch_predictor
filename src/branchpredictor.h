//
// Created by Jason on 11/16/2019.
//

#ifndef PROJECT_BRANCHPREDICTOR_H
#define PROJECT_BRANCHPREDICTOR_H


class BranchPredictor {
private:
    //methods============================
    void verify_prediction(char prediction);

    //variables==========================
    char real_path;

    char *trace_file;
    int m2_bits;
    int m1_bits;
    int n_bits;
    int k_bits;

    double total_predictions;
    double total_mispredictions;
    double misprediction_rate;

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

    void print_result(int result, char *exe_command, char *mode, int btb_size, int btb_assoc);
};


#endif //PROJECT_BRANCHPREDICTOR_H
