#include"../include/line.h"
#include"../include/urqmd_read.h"
#include"../include/cal_particle_by_particle.h"

int cal_eta_particle_by_particle(double qgp_energy,double qgp_pz, double accept_error,map<double,double>eta_energy_map,map<double,double>eta_pz_map,vector<double>eta_list)
{
    for(int left_particle_order = 0;left_particle_order < eta_list.size()-1;left_particle_order++)
        {   
            double this_eta_cut_lb = 0, this_eta_cut_rb = 0;
            double energy_sum = 0, pz_sum = 0;
            int count = 0;
            double delta_energy = 100;
            double delta_pz = 100;
            energy_sum = eta_energy_map[eta_list[left_particle_order]];
            pz_sum = eta_pz_map[eta_list[left_particle_order]];
            if(left_particle_order == (eta_list.size() - 2)) cout << "Not found etacut of this one" << endl;
            if (energy_sum == 0){continue;}   //skip zero energy lattice
            for(int right_particle_order = left_particle_order+1;right_particle_order < eta_list.size();right_particle_order++)
                {energy_sum += eta_energy_map[eta_list[right_particle_order]];
                pz_sum += eta_pz_map[eta_list[right_particle_order]];
                delta_energy = abs((energy_sum-qgp_energy)/qgp_energy);
                delta_pz = abs((pz_sum-qgp_pz)/qgp_pz);
                if (delta_energy < accept_error && delta_pz < accept_error)
                {
                    this_eta_cut_lb = eta_list[left_particle_order];
                    this_eta_cut_rb = eta_list[right_particle_order]; 
                    count = 1;
                    cout << "successfully get the cut " << " eta_lb " << this_eta_cut_lb
                    << "  eta_rb " << this_eta_cut_rb << endl; 
                    break;
                }
                else
                {
                    if(count == 0)continue;
                }
                }
                if (this_eta_cut_lb != 0)break;
        }

}




int sample_eta_particle_by_particle(double qgp_energy,double qgp_pz, double accept_error, string oscar_path)
{
    ifstream oscar_file;
    oscar_file.open(oscar_path);
    if(oscar_file)
    {
        cout << "successfully open the OSCAR.DAT" << endl;
        string stem_line;
        //remove the head text
        for(int i=1;i<=3;i++)
        {
            getline(oscar_file,stem_line);
            stem_line.clear();
        }
        while(true)
        {
            getline(oscar_file,stem_line);
            if(stem_line == "")
            {
                cout << "finish sorted" <<endl;
                break;
            }
            title_line this_title;
            this_title.title_information(stem_line);
            cout << this_title.sample_order << " th" << " sample result" << endl;
            cout << "There are "<<this_title.particle_number <<" particles in this result." << endl;
            map<double,double>eta_energy_map;
            map<double,double>eta_pz_map;
            vector<double>eta_list;
            for(int k = 1;k<= this_title.particle_number;k++)
            {
                getline(oscar_file,stem_line);
                particle_line thisline;
                thisline.particle_information(stem_line);
                eta_energy_map[thisline.eta] = thisline.energy;
                eta_pz_map[thisline.eta] = thisline.pz;
                eta_list.push_back(thisline.eta);
            }
            sort(eta_list.begin(),eta_list.end());
            cout << "the map size is " << eta_pz_map.size() << endl;
            cal_eta_particle_by_particle(qgp_energy,qgp_pz,accept_error,eta_energy_map,eta_pz_map,eta_list);
        }
        oscar_file.close();

    }





}