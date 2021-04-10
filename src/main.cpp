#pragma GCC optimize(3)
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<cmath>
#include<cstdlib>
#include<unistd.h>
#include"../include/line.h"
#include"../include/cal_ycut.h"
#include"../include/urqmd_read.h"
#include"../include/para_read.h"
#include"../include/cal_etacut.h"
#include"../include/output.h"
#include"../include/cal_particle_by_particle.h"
using namespace std;

int main(int argc, char **argv)
{
    parameter para;
    para.get_para("./calcut_parameter.txt");
    string urqmd_path = para.urqmd_path;
    string oscar_path = para.oscar_path;

    if (para.qgp_option == 0)
    {
        stringstream QgpEnergy, QgpPz;
        QgpEnergy.clear();
        QgpPz.clear();
        QgpEnergy  << argv[1];
        QgpPz << argv[2];
        QgpEnergy >> para.qgp_energy;
        QgpPz >> para.qgp_pz; 
        if(para.debug_option == 1)
        {cout << "The qgp energy is " << para.qgp_energy << " Gev" << endl;
         cout << "The qgp pz is " << para.qgp_pz << " Gev" << endl;}
    }
    if (para.qgp_option == 1)
    {
    double *qgp_energy_pz_array = urqmd_qgp_function(urqmd_path,para.debug_option);               
    para.qgp_energy = qgp_energy_pz_array[0],para.qgp_pz = qgp_energy_pz_array[1];
    }       



    if (para.eta_or_y_option == 1)
    {
    cout << "***************y cut lattice method without output file***************"<<endl; 
    sample_by_sample_cal(oscar_path,para.y_left,para.y_right,para.y_step,para.qgp_energy,para.qgp_pz,para.accept_error);  //cal ycut result by result  
    //all_sample_cal(oscar_path,para.y_left,para.y_right,para.y_step,para.qgp_energy,para.qgp_pz,para.accept_error);  // cal ycut of all results
    }   
    if (para.eta_or_y_option == 0)
    {
    cout << "***************eta cut lattice method with output file***************"<<endl;
    sample_by_sample_eta_cal(oscar_path,para.eta_left,para.eta_right,para.y_step,para.qgp_energy,para.qgp_pz,para.accept_error,para.debug_option);
    output_function("./results_of_cal/etacut_result_of_each_sample.txt",oscar_path,"./results_of_cal/iSS_result_after_cut.txt",para.debug_option);
    //all_sample_eta_cal(oscar_path,para.eta_left,para.eta_right,para.y_step,para.qgp_energy,para.qgp_pz,para.accept_error);
    }
    if  (para.eta_or_y_option == 3)
    {cout << "**************eta cut particle method with output file***************"<<endl;
    sample_eta_particle_by_particle(para.qgp_energy,para.qgp_pz,para.accept_error,oscar_path,para.debug_option);
    output_function("./results_of_cal/etacut_result_of_each_sample.txt",oscar_path,"./results_of_cal/iSS_result_after_cut_txt",para.debug_option);
    }
}    