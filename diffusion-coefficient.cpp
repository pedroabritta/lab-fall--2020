//Author: Pedro Abritta
//University of South Florida
//Professor: Dr Robert Hoy 

//This program gets the rmsd values for each frame during the simulation and fits it to a liner function msd(t) = a + 6Dt where D is the natural log of the diffusion coefficient 
//It does so for all phis 
//Path to msd file can be changed and will be indicated in the program 
//Loop for the phis is created with the arguments entered when running the program 
//New file format is
//      phi             ln(diff)
// MUST RUN PROGRAM IN THE DIRECTORY WITH ALL THE PHI DIRECTORIES TOGETHER - FROM SAME NUMBER OF ATOMS/TEMPERATURE


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

//---------------------------go to line function------------------------------------
fstream& gotoline(fstream& file, unsigned int line){
        file.seekg(ios::beg);
        for(int i = 0; i < line - 1; i++){
                file.ignore(numeric_limits<streamsize>::max(),'\n');
        }
        return file;
}

//----------------------------------------------------------------------------------

//-------------Main function-------------------------------------------------------
//Takes 4 arguments
//      Total number of atoms N
//      Highest phi pH
//      Lowest phi pL
//
int main(int argc, char* argv[]){
        int N = atoi(argv[1]);
        double pH = atof(argv[2]);
        double pL = atof(argv[3]);
        double dphi = atof(argv[4]);
        double logaux = 0.0;
        double aux = 0.0;
        double phi = pL;
        int i = 0;
        int frame;


        ofstream afs;
        afs.open("diffvsphi.dat");
        if (!afs.is_open()){
              cout << "Failed to output first file" << endl;
              exit(1);
        }
        afs << "#Data entry: phi  ln(rmsd)" << endl;
        afs.close();

        // CHECKING IF ARGUMENTS WERE ENTERED CORRECTLY
        if (pL >=pH || dphi >= pL || dphi>=pH ){
                cout << "Arguments were entered incorrectly; order is: N, phiHigh, phiLow, dphi." << endl;
                exit(1);
        }


        // LOOPING THROUGH DIRECTORIES AND OPENING DIFFUSION FILES
        while (phi<=pH && i<=1){
                ostringstream strsN;
                strsN<< N;
                string Nst= strsN.str();
                ostringstream strsphi;
                strsphi<< phi;
                string Pst = strsphi.str();
                string filename = Nst+"_"+Pst+"/equil_log/diffusion.duringequilrun"; // THIS IS WHERE PATH MAY BE ALTERED TO SUIT DIRECTORIES ON YOUR SIMULATION
                //FILE WAS PUT INSIDE /equil_log/ DURING THE SIMULATIONS - DIRECTORIES ARE SET AS N_phi/equil_log/file - (i.e. 32000_0.54/equil_log/diffusion.duringequilrun)


                // OPENING OUTPUT FILE AND CHECKING IT OPENED
                ofstream ofs;
                ofs.open("log_rmsd_"+Pst+".dat");
                if (!ofs.is_open()){
                     cout << "Failed to output first file" << endl;
                     exit(1);
                }

                // OPENING INPUT FILE AND CHECKING IT OPENED 
                fstream ifs;
                ifs.open((filename).c_str());
                if (!ifs.is_open()){
                        cout << "Failed to open input file" << endl;
                        exit(1);
                }


                //RMSD BY FRAME FILE HAS 1443 LINES - WE WANT THE DIFF COEFF FOR THE LAST 1/3 OF FRAMES => WE GO TO LINE 962 AND LOOP FROM THERE
                for (int line = 962; line <=1443; line++){
                        gotoline(ifs, line);
                        ifs >> frame >> aux; //IFS RETURNS ALL ELEMENTS IN LINE N => WE CAN ACCESS ALL TERMS IN ORDER THEY APPEAR
                        logaux = log(aux);
                        ofs << logaux << endl;
                }
        ifs.close();    // CLOSE DIFFUSION.DURINGEQUILRUN FILE

        //run python fitting plot 
        system(("python3 fitted.py "+Pst).c_str());
        phi=phi+dphi; //LOOP THROUGH NEXT PHI 
        if (phi>=pH){
                phi=pH;
                ++i;
            }
        }
        return 0;
}
