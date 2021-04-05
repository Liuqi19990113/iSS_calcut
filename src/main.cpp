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

int main()
{
    string urqmd_path("../urqmd/urqmd_result19"); //path of urqmd_result19
    string oscar_path("../iSS/OSCAR.DAT");   //path of OSCAR.DAT
    parameter para;
    para.get_para("./parameter.txt");

    if (para.qgp_option == 0)
    {
        cout << "please input qgp energy/Gev: ";
        cin >> para.qgp_energy;
        cout << "please input qgp pz/Gev: ";
        cin >> para.qgp_pz;
    }
    if (para.qgp_option == 1)
    {
    double *qgp_energy_pz_array = urqmd_qgp_function(urqmd_path);               
    para.qgp_energy = qgp_energy_pz_array[0],para.qgp_pz = qgp_energy_pz_array[1];
    }       



    if (para.eta_or_y_option == 1)
    {
    cout << "********************y cut lattice method without output file*************************"<<endl; 
    sample_by_sample_cal(oscar_path,para.y_left,para.y_right,para.y_step,para.qgp_energy,para.qgp_pz,para.accept_error);  //cal ycut result by result  
    all_sample_cal(oscar_path,para.y_left,para.y_right,para.y_step,para.qgp_energy,para.qgp_pz,para.accept_error);  // cal ycut of all results
    }   
    if (para.eta_or_y_option == 0)
    {
    if(access("./results_of_cal",0) != -1)
    {
        system("rm -rf  ./results_of_cal");
        system("mkdir ./results_of_cal");
        //system("mkdir ./results_of_cal/ep_spectrum");
    }
    else 
    {
        system("mkdir ./results_of_cal");
        //system("mkdir ./results_of_cal/ep_spectrum");
    }
    cout << "********************eta cut lattice method with output file*************************"<<endl;
    sample_by_sample_eta_cal(oscar_path,para.eta_left,para.eta_right,para.y_step,para.qgp_energy,para.qgp_pz,para.accept_error);
    output_function("./results_of_cal/eta cut result of each sample.txt",oscar_path,"./results_of_cal/iSS result after cut.txt");
    //all_sample_eta_cal(oscar_path,para.eta_left,para.eta_right,para.y_step,para.qgp_energy,para.qgp_pz,para.accept_error);
    }
    if  (para.eta_or_y_option == 3)
    {cout << "*******************eta cut particle method without output file************************"<<endl;
    if(access("./results_of_cal",0) != -1)
    {
        system("rm -rf  ./results_of_cal");
        system("mkdir ./results_of_cal");
        //system("mkdir ./results_of_cal/ep_spectrum");
    }
    else 
    {
        system("mkdir ./results_of_cal");
        //system("mkdir ./results_of_cal/ep_spectrum");
    }
    sample_eta_particle_by_particle(para.qgp_energy,para.qgp_pz,para.accept_error,oscar_path);
    output_function("./results_of_cal/eta cut result of each sample.txt",oscar_path,"./results_of_cal/iSS result after cut.txt");
    }
}    