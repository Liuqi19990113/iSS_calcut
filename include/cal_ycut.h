#ifndef CAL_YCUT
#define CAL_YCUT
#include<iostream>
#include<sstream>
#include<string>
#include<cmath>
#include<fstream>
using namespace std;

int cal_ycut(double qgp_energy,double qgp_pz,double energy_list[],double pz_list[],double y_left,double y_step,int lattice_number,double accept_error);

int sample_by_sample_cal(string oscar_path,double y_left,double y_right,double y_step,double qgp_energy,double qgp_pz,double accept_error);

int all_sample_cal(string oscar_path,double y_left,double y_right,double y_step,double qgp_energy,double qgp_pz,double accept_error);

#endif
