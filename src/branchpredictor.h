//
// Created by Jason on 11/16/2019.
//

#ifndef PROJECT_BRANCHPREDICTOR_H
#define PROJECT_BRANCHPREDICTOR_H


class BranchPredictor {
private:
    //methods============================
    void initialize_bimodal_array(void);
    int get_bimodal_table_index(long initial_value);

    char bimodal_prediction(int bimodal_table_index);
    void verify_prediction(char prediction);
    void bimodal_table_update(int bimodal_table_index);

    void print_predictions(void);
    void print_bimodal_contents(void);
    void print_gshare_contents(void);
    void print_chooser_contents(void);

    //variables==========================
    char real_path;

    int offset_bits;

    char *trace_file;
    int m2_bits;
    int m1_bits;
    int n_bits;
    int k_bits;

    int bimodal_min;
    int bimodal_max;

    int *bimodal_array;
    int *gshare_array;
    int *chooser_array;

    int bimodal_length;
    int gshare_length;
    int chooser_length;

    int total_predictions;
    int total_mispredictions;
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
