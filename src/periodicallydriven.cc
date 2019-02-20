/*
############################ COPYRIGHT NOTICE ##################################

Code written by G. Sinuco, February 2019.

Permission is granted for anyone to copy, use, modify, or distribute the
accompanying programs and documents for any purpose, provided this copyright
notice is retained and prominently displayed
 
The programs and documents are distributed without any warranty, express or
implied.

These programs were written for research purposes only, and are meant to
demonstrate and reproduce the main results obtained in the paper.

All use of these programs is entirely at the user's own risk.

################################################################################
*/

#include <iostream>
#include <vector>
#include <complex>

//Transverse-field Ising model in 1d
class FloquetSystem{

  //number of energy levels
  const int D_bare_;

  //value of the driving strengh and frequency
  const double Rabi_;
  const double omega_;

  //bare energy spectrum
  const std::vector<double> E_;
  
  //option to use periodic boundary conditions
  const bool pbc_;

  
  //pre-computed quantities
  std::vector<std::complex<double> > mel_;
  std::vector<std::vector<int> > flipsh_;

public:

  Floquet(int D_bare,std::vector<double> E, double Rabi,double omega,bool pbc=true):D_bare_(D_bare),E_(E),Rabi_(Rabi),omega_(omega),pbc_(pbc){
    Init();
  }

  void Init(){
   
    E_.resize(D_bare);
      
    mel_.resize(D_bare_+1,0.);
    flipsh_.resize(D_bare_+1);

    for(int i=0;i<D_bare_;i++){
        E_[i] = E[i];
    }
    for(int i=0;i<nspins_;i++){
      mel_[i+1]=-hfield_;
      flipsh_[i+1]=std::vector<int>(1,i);
    }
    std::cout<<"# Using the Floquet model with omega = "<<omega_<<std::endl;
  }

  //Finds the non-zero matrix elements of the hamiltonian
  //on the given state
  //i.e. all the state' such that <state'|H|state> = mel(state') \neq 0
  //state' is encoded as the sequence of spin flips to be performed on state
  void FindConn(const std::vector<int> & state,std::vector<std::vector<int> > & flipsh,std::vector<std::complex<double> > & mel){

    mel.resize(nspins_+1);
    flipsh.resize(nspins_+1);

    //assigning pre-computed matrix elements and spin flips
    mel=mel_;
    flipsh=flipsh_;

    //computing interaction part Sz*Sz
    mel[0]=0.;

    for(int i=0;i<(nspins_-1);i++){
      mel[0]-=double(state[i]*state[i+1]);
    }

    if(pbc_){
      mel[0]-=double(state[nspins_-1]*state[0]);
    }

  }

  int MinFlips()const{
    return 1;
  }

};
