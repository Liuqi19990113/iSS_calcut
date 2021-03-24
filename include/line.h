#ifndef LINE_H
#define LINE_H
#include<iostream>
#include<string>
#include<sstream>
#include<cmath>
using namespace std;

class particle_line
{
public:
    double energy, pz, y ,px ,py, eta, absp;
    void particle_information(string one_line);
};


class title_line
{
public:
    int sample_order,particle_number;
    void title_information(string oneline);
};


#endif
