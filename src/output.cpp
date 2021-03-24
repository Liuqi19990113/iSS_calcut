#include"../include/output.h"
#include"../include/line.h"

void output_function(string ycut_path, string oscar_path, string output_path)
{
    ifstream ycut_file;
    ycut_file.open(ycut_path,ios::in);
    ifstream oscar_file;
    oscar_file.open(oscar_path,ios::in);
    ofstream output_file;
    output_file.open(output_path,ios::out);
    string stem_ycut_line, stem_oscar_line;
    output_file << "OSC1997A" <<endl;
    output_file << "final_id_p_x" << endl;
    output_file << " 3DHydro       1.1  (197,    79)+(197,    79)  eqsp  0.1000E+03         1" <<endl;
    if(ycut_file && oscar_file)
    {
        cout << "successfully open the file" << endl;
        for(int i = 1; i <= 3; i++)
        {
            getline(oscar_file,stem_oscar_line);
            stem_oscar_line.clear();
        }
        int sample_with_cut_order = 0;
        while(true)
        {
            getline(ycut_file,stem_ycut_line);
            if(stem_ycut_line == "")break;
            getline(ycut_file,stem_ycut_line);
            if(stem_ycut_line.find("successfully") == -1)
            {
                title_line this_title;
                getline(oscar_file,stem_oscar_line);
                this_title.title_information(stem_oscar_line);
                for (int i = 1; i <= this_title.particle_number; i++)
                {
                    getline(oscar_file,stem_oscar_line);
                }
            }

            else
            {
                sample_with_cut_order += 1;
                stringstream sstem_ycut_line;
                string tem_line;
                double cut_left,cut_right;
                sstem_ycut_line.str(stem_ycut_line);
                for(int i = 1; i <= 8; i++)
                {
                    if (i == 6) sstem_ycut_line >> cut_left;
                    else if (i == 8) sstem_ycut_line >> cut_right;
                    else sstem_ycut_line >> tem_line;
                }
                vector<string>particle_with_cut;
                title_line this_title;
                getline(oscar_file,stem_oscar_line);
                this_title.title_information(stem_oscar_line);
                for (int i = 1; i <= this_title.particle_number; i++)
                {
                    getline(oscar_file,stem_oscar_line);
                    particle_line this_particle;
                    this_particle.particle_information(stem_oscar_line);
                    if (this_particle.eta >= cut_left && this_particle.eta <= cut_right)particle_with_cut.push_back(stem_oscar_line);            
                }
                output_file << right << setw(10) << sample_with_cut_order << right << setw(12)<< particle_with_cut.size() << right << setw(10) << "0" << right << setw(10) << "0" << endl;
                for(int i = 0;i<= particle_with_cut.size()-1;i++)
                {
                    stringstream output_line; 
                    output_line.str(particle_with_cut[i]);
                    string final_out_line;
                    output_line >> final_out_line;
                    final_out_line.clear();
                    output_file << right << setw(10) << i+1;
                    output_line >> final_out_line;
                    output_file << right << setw(12) << final_out_line;
                    
                    for(int j = 2;j <= 10; j++)
                    {
                     final_out_line.clear();
                        output_line >> final_out_line;
                        if(j != 10)output_file << right << setw(26) << final_out_line ;
                        else output_file << right << setw(26) << final_out_line << endl;
                    }
                }
                particle_with_cut.clear();
            }

        }
        ycut_file.close();
        oscar_file.close();
        output_file.close();
        cout << "finished to combine output file" << endl;
        cout << "there are " << sample_with_cut_order << " sample result in output file" << endl;

    }

    else
    {
        cout << "Cant open the file" << endl;
    }
}