#ifndef CAL_PARTICLEBYPARICLE
#define CAL_PARTICLEBYPARICLE
#include<string>
#include<map>
#include<algorithm>
#include<vector>
using namespace std;

int sample_eta_particle_by_particle(double qgp_energy,double qgp_pz, double accept_error, string oscar_path,int debug_in);
int cal_eta_particle_by_particle(double qgp_energy,double qgp_pz, double accept_error,map<double,double>eta_energy_map,map<double,double>eta_pz_map,vector<double>eta_list,ofstream &eta_cut_output_file,int debug_in);;




#endif
