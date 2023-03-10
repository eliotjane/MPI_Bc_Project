//digest file written 20/10/2022

//#include <cstdlib>
//#include <iostream>
//#include <map>
//#include <math.h>
//#include <string>

//#include "TChain.h"
//#include "TFile.h"
//#include "TTree.h"
//#include "TString.h"
//#include "TObjString.h"
//#include "TSystem.h"
//#include "TROOT.h"


namespace ewalton {}
using namespace ewalton;

//TString dir = "/eos/user/m/mwalton/DLL_Data/reporcessed_nominal/MPI_data_MC/2018_MC_*.root";

//DECLARE_COMPONENT( Background_digestion )

//DECLARE_COMPONENT( Histo_corrector )

void Machine_Learning_Evaluation_Plots(){

TFile* original_file = new TFile();

original_file = TFile().Open("TMVA_Bc2JpsiPi_BDTG_MC_.root");

//Check the BDT file is loaded
//original_file->ls();

TObject* dataset_BDT = original_file->Get("dataset");

//Check dataset is loaded
dataset_BDT->ls();

//I am confused how to go on from here

//input_variables = TFile().Open("InputVariables_Id;1");

//input_variables->ls();

//Now is manipulation of a TObject

//TH1D * h2 = (TH1D*)original_file->Get("h_multiplicity_cats_pythia_DPS_ratio_noCR");

//TObject* CorrelationMatrixSignal = new TObject();

//CorrelationMatrixSignal = dataset_BDT->Clone("CorrelationMatrixS");

//CorrelationMatrixSignal->Draw();

//CorrelationMatrixSignal->Draw();

}
