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

void Histo_corrector(){

TFile* original_file = new TFile();

original_file = TFile().Open("c_multiplicity_cats_ratio_noCR.root");
original_file->ls();

//THIS WORKS!!

TH1D * h2 = (TH1D*)original_file->Get("h_multiplicity_cats_pythia_DPS_ratio_noCR");
//h2->Draw();

TAxis *yaxis = h2->GetYaxis();
yaxis->Print();

//get x-axis (this returns the label)
TAxis *xaxis = h2->GetXaxis();
xaxis->Print();

//Double_t Xcenter = h2->GetXaxis()->GetBinCenter(1);
//cout << "X-center = " << Xcenter << endl;

//This gets the cental bin value from the x-axis


TH1F *h_DPS_noCR = (TH1F*)h2->Clone("h_DPS_noCR");

//TH1D *h_DPS_noCR = new TH1D();

//set axis titles
h_DPS_noCR->GetXaxis()->SetTitle("N_{VELO}^{2.0<#eta<4.5}");
h_DPS_noCR->GetYaxis()->SetTitle("#scale[0.6]{#frac{d#sigma(B_{c}^{+})}{dN}}/#scale[0.6]{#frac{d#sigma(B^{+})}{dN}} (%)");

//h_DPS_noCR->SetAxisRange(0, 80, "X");
//h_DPS_noCR->SetAxisRange(0, 0.5, "Y");

//h_DPS_noCR->GetXaxis()->SetTicks("+");
//h_DPS_noCR->GetXaxis()->SetRangeUser(0., 80.);



//Int_t bin = h_DPS_noCR->GetBin(1;4);

//cout << "The first Bin: " << bin << "\n";

for (int i = 0; i <= 16; ++i) {
	//choose the central value of the x-bin
	
	//cout << "Outer: " << i << "\n";
	
	double Xcenter = h2->GetXaxis()->GetBinCenter(i);
	
	//double X_content = h2->GetBinContent(Xcenter);
	
	
	double X_content = h2->GetBinContent(i);
	
	//it goes through 16 times but it doesn't replace the values every time
	cout <<  Xcenter << "\n";
	
	cout <<  X_content << "\n";
	
	
	double Velo_efficency_MC_greater_than_50, Velo_efficency_MC_less_than_50, corrected_value;
	
	//here we should add an if loop for bin values less than 50
	if (Xcenter <= 50) {
	//cout << "less than 50 tracks" << "";
	
	//intialise number
	
		

	//from Figure 25 in VELO paper for run1 and run2. Accessible DOI: 10.1088/1748-0221/9/09/P09007
	//for tracks fewer than 50
	
	Velo_efficency_MC_less_than_50 = 0.988;
	//Velo_efficency_MC_less_than_50 = 0.;
	//multiply values
	
	corrected_value = X_content * Velo_efficency_MC_less_than_50;
	
	//cout << "Corrected value lesser: " << corrected_value << "\n";
	
	
	
	h_DPS_noCR->SetBinContent(i, corrected_value);
	
	//mylist.push_back (corrected_value);
	
	//looks good!
	//cout <<  corrected_value << "";
	
		} 
	else {

	//from Figure 25 in VELO paper for run1 and run2. Accessible DOI: 10.1088/1748-0221/9/09/P09007
	//for tracks greater than 50
	
	Velo_efficency_MC_greater_than_50 = 0.987;
	//Velo_efficency_MC_greater_than_50 = 0.;
	
	
	//multiply values
	
	corrected_value = X_content * Velo_efficency_MC_greater_than_50;
	
	cout << "Corrected value greater: " << corrected_value << "\n";
	
	h_DPS_noCR->SetBinContent(i, corrected_value);
	
	//mylist.push_back (modified_value);
	
		//cout <<  X_content << " ";
		//cout <<  corrected_value << " ";
	
		}
}

//return 0;


h_DPS_noCR->Draw();

//Now we make the new histograms






//TH1F *h1 = new TH1F("h1", "h1 title", 100, 0, 4.4);/
//h1->Draw();
//hist->Browse(hist);

//auto* values = hist->Get("fN");

//hist->Dump();



}
