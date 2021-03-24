#include"../include/line.h"

void particle_line::particle_information(string oneline)
{
    stringstream stem_oneline;
    stem_oneline.clear();
    stem_oneline.str(oneline);
    double tem_variable;
    for(int i = 0;i<11;i++)
    {
        stem_oneline >> tem_variable;
        if(i == 2)px = tem_variable;
        if(i == 3)py = tem_variable;
        if(i == 4)pz = tem_variable;
        if(i == 5){energy = tem_variable;
        y = 0.5*log((energy+pz)/(energy-pz));
        absp = sqrt(px*px+py*py+pz*pz);
        eta = 0.5*log((absp+pz)/(absp-pz));
        }
    }
}


void title_line::title_information(string oneline)
{
    stringstream stem_oneline;
    stem_oneline.clear();
    stem_oneline.str(oneline);
    int mid_variable;
    for(int i=1;i<=2;i++)
    {
        stem_oneline >> mid_variable;
        if(i==1) sample_order = mid_variable;
        if(i==2) particle_number = mid_variable;
    }   
} 
