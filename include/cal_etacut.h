#ifndef ETA_YCUT
#define ETA_YCUT
#include<iostream>
#include<sstream>
#include<string>
#include<cmath>
#include<fstream>
using namespace std;

int eta_etacut(double qgp_energy,double qgp_pz,double energy_list[],double pz_list[],double eta_left,double y_step,int lattice_number,double accept_error);

int cal_etacut_with_output(double qgp_energy,double qgp_pz,double energy_list[],double pz_list[],double eta_left,double y_step,int lattice_number,ofstream &eta_cut_output_file,double accept_error);

int sample_by_sample_eta_cal(string oscar_path,double eta_left,double eta_right,double y_step,double qgp_energy,double qgp_pz,double accept_error);

int all_sample_eta_cal(string oscar_path,double eta_left,double eta_right,double y_step,double qgp_energy,double qgp_pz,double accept_error);

#endif
