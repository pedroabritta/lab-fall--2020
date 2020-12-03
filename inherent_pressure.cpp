//Author: Pedro Abritta
//University of South Florida
//Professor: Dr Robert Hoy

//This program reads data from the log.lammps file and calculates the Inherent Structure pressure for several different packing densities of bidisperse systems
//one can adjust it by changing the suffixes and frame numbers to suit one's own simulation

#include <fstream>
#include <limits>
#include <iostream>
#include <ostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>
#include <math.h>
#include <string.h>
#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sstream>

using namespace std;

int main(){

//------------------------var declaration ---------------------------------
float trash[5];
float aux, press=0;
string line, file;
int counter = 0, a;
FILE *fp;
float suffixes[23];
string Dir;
int i = 0;
float aux2;
ofstream ofs;
ofs.open("ispressure.dat");

while (i<23){
        suffixes[i] = 0.54 + i*0.009;
        i++;
}
for (int i=0; i<=22; i++)
{
        cout<<suffixes[i]<<endl;
}
//--------loop thorugh directories -----------------------------------------
for(int i = 0; i<=22;i++){
        aux2 = suffixes[i];
        ostringstream strsaux2;
        strsaux2 << aux2;
        string Dir = strsaux2.str();
//------------loop thorugh min logs ------------------------------------------
for (int log = 135000;log<=360000;log = log + 15000){
        ostringstream strslog;
        strslog << log;
        string LOG = strslog.str();
        fp=fopen(("32000_"+Dir+"/min_log"+LOG+"/log.lammps").c_str(), "r");
        if (fp == NULL){
        cout << "Failure to open file" << endl;
        exit(-1);
        }
            while (counter < 33){
                if ((a = fgetc(fp))=='\n'){
                counter++;      }
                if (counter == 32){
                   fscanf(fp, "%f %f %f %f %f %f", &trash[0], &trash[1], &trash[2], &trash[3], &aux, &trash[4]);
                        }
                }
        counter = 0;
        press = aux/25 + press;
        cout << log << aux << endl;
        fclose(fp);
}
ofs<<Dir<<"\t"<<press<<"\n";
press = 0;
}
ofs.close();
 return 0;
}
