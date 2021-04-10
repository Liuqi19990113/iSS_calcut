#ifndef PARA_READ
#define PARA_READ

#include<iostream>
#include<sstream>
#include<string>
#include<fstream>
using namespace std;

class parameter
{
    public:
        double qgp_option;
        double eta_or_y_option;
        double qgp_energy;
        double qgp_pz;
        double y_left;
        double y_right;
        double eta_left;
        double eta_right;
        double y_step;
        double accept_error;
        int debug_option;
        string urqmd_path;
        string oscar_path;
        void get_para(string parameter_path);
};








#endif
