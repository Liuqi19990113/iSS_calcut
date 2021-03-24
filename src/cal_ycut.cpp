#include"../include/cal_ycut.h"
#include"../include/line.h"

int cal_ycut(double qgp_energy,double qgp_pz,double energy_list[],double pz_list[],double y_left,double y_step,int lattice_number,double accept_error)
{
    for(int left_lattice = 0;left_lattice < lattice_number-1;left_lattice++)
            {   
                double this_y_cut_lb = 0, this_y_cut_rb = 0;
                double energy_sum = 0, pz_sum = 0;
                int count = 0;
                double delta_energy = 100;
                double delta_pz = 100;
                energy_sum = energy_list[left_lattice];
                pz_sum = pz_list[left_lattice];
                if(left_lattice == (lattice_number - 2)) cout << "Not found ycut of this one" << endl;
                if (energy_sum == 0){continue;}   //skip zero energy lattice
                for(int right_lattice = left_lattice+1;right_lattice < lattice_number;right_lattice++)
                    {energy_sum += energy_list[right_lattice];
                    pz_sum += pz_list[right_lattice];
                    delta_energy = abs((energy_sum-qgp_energy)/qgp_energy);
                    delta_pz = abs((pz_sum-qgp_pz)/qgp_pz);
                    if (delta_energy < accept_error && delta_pz < accept_error)
                    {
                        this_y_cut_lb = y_left + y_step*left_lattice;
                        this_y_cut_rb = y_left + y_step*right_lattice; 
                        count = 1;
                        cout << "successfully get the cut " << " y_lb " << this_y_cut_lb
                        << "  y_rb " << this_y_cut_rb << endl; 
                        break;
                    }
                    else
                    {
                        if(count == 0)continue;
                    }
                    }
                if (this_y_cut_lb != 0)break;
            }
}



int sample_by_sample_cal(string oscar_path,double y_left,double y_right,double y_step,double qgp_energy,double qgp_pz,double accept_error)
{
    int lattice_number = (y_right-y_left)/y_step;
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
            double energy_list[lattice_number]={0};
            double pz_list[lattice_number]={0};
            title_line this_title;
            this_title.title_information(stem_line);
            cout << this_title.sample_order << " th" << " sample result" << endl;
            for(int k = 1;k<= this_title.particle_number;k++)
            {
                getline(oscar_file,stem_line);
                particle_line thisline;
                thisline.particle_information(stem_line);
                int this_y_order = (thisline.y - y_left)/y_step;
                energy_list[this_y_order] += thisline.energy;
                pz_list[this_y_order] += thisline.pz;
            }
        cal_ycut(qgp_energy,qgp_pz,energy_list,pz_list,y_left,y_step,lattice_number,accept_error);
        }
    oscar_file.close();
    cout << "closed OSCAR.DAT" << endl;
    }
    else
    {
        cout << "failed to open OSCAR.DAT" << endl;
    }
}


int all_sample_cal(string oscar_path,double y_left,double y_right,double y_step,double qgp_energy,double qgp_pz ,double accept_error)
{
    int lattice_number = (y_right-y_left)/y_step;
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
        double energy_list[lattice_number] = {0};
        double pz_list[lattice_number] = {0};
        int final_order;
        while(true)
        {
            stem_line.clear();
            getline(oscar_file,stem_line);
            if(stem_line == "")
            {
                cout <<"finish sorted" << endl;
                break;
            }
            title_line this_title;
            this_title.title_information(stem_line);
            cout << "sorting the rapidity of " << this_title.sample_order << "th sample result" << endl;
            final_order = this_title.sample_order;
            for(int k = 1;k<= this_title.particle_number;k++)
            {
                getline(oscar_file,stem_line);
                particle_line thisline;
                thisline.particle_information(stem_line);
                int this_y_order = (thisline.y - y_left)/y_step;
                energy_list[this_y_order] += thisline.energy;
                pz_list[this_y_order] += thisline.pz;
            }
        }
        oscar_file.close();
        cout << "closed the OSCAR.DAT" << endl;
        for(int i = 0; i<lattice_number; i++)
        {
            energy_list[i] = energy_list[i]/final_order;
            pz_list[i] = pz_list[i]/final_order;
        }
    cal_ycut(qgp_energy,qgp_pz,energy_list,pz_list,y_left,y_step,lattice_number,accept_error);
    }
    else
    {
        cout << "failed to open OSCAR.DAT" << endl;
    }
} 