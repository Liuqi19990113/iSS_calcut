#include"../include/urqmd_read.h"
using namespace std;

double *urqmd_qgp_function(string urqmd_path)
{
    double *array = new double[2];
    ifstream urqmd_file;
    urqmd_file.open(urqmd_path,ios::in); //open urqmd_result19
    if (urqmd_file)
    {
        cout << "successfully open the file" << endl;
        string line;
        stringstream this_line;
        //clear the head text
        for(int i=1;i<=4;i++)
        {
            getline(urqmd_file,line);
            line.clear();
        }
    
        double qgp_energy = 0, qgp_pz = 0;
        double tem_variable, this_pz = 0, this_energy = 0;
        while(!urqmd_file.eof())                  // read each line and get energy pz of QGP
       {    
            this_line.clear();
            getline(urqmd_file,line);
            if(line.length()==0)break;
            this_line.str(line);
            for(int j=0;j<11;j++)
            {
                this_line >> tem_variable;
                if(j == 4) this_pz = tem_variable;
                else if(j == 5) this_energy = tem_variable;
                else if((j == 10) && (tem_variable > 0.1))
                {
                    qgp_energy = qgp_energy + this_energy;
                    qgp_pz = qgp_pz + this_pz;
                }
            } 
        }
        urqmd_file.close();
        cout << "successfully closed urqmd_result19 file" << endl;
    array[0] = qgp_energy; array[1] = qgp_pz;
    cout << "the energy of qgp is " << qgp_energy << " Gev" << endl;
    cout << "the pz of qgp is " << qgp_pz << " Gev" << endl;
    }
    else
    {
        cout << "failed to open the urqmd file";
    }
    return array;
}

