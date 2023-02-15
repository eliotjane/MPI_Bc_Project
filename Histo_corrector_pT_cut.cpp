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

void Histo_corrector_pT_cut(){

TFile* original_file = new TFile();

original_file = TFile().Open("c_multiplicity_cats_ratio_noCR_pT_cut.root");
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
h_DPS_noCR->GetXaxis()->SetTitle("N_{VELO}/N_{noBias PYTHIA}^{2.0<#eta<4.5}");
h_DPS_noCR->GetYaxis()->SetTitle("#scale[0.6]{#frac{d#sigma(B_{c}^{+})}{dN}}/#scale[0.6]{#frac{d#sigma(B^{+})}{dN}}");

//h_DPS_noCR->SetAxisRange(0, 80, "X");
//h_DPS_noCR->SetAxisRange(0, 0.5, "Y");

//h_DPS_noCR->GetXaxis()->SetTicks("+");
//h_DPS_noCR->GetXaxis()->SetRangeUser(0., 80.);


//h_DPS_noCR->GetXaxis() 


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
	
	//Attempt to change x axis values
	//int n = 16;
	//double xbins[16] = {}
	
	
	
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
	corrected_value = X_content * Velo_efficency_MC_greater_than_50;
	
	cout << "Corrected value greater: " << corrected_value << "\n";
	
	h_DPS_noCR->SetBinContent(i, corrected_value);
	
	
		}
		

// from Matt's Anna-Note https://twiki.cern.ch/twiki/pub/LHCbPhysics/BHadronsHighMult13TeVpp/AnalysisNote_Bc_Bs_mult_13TeV_v0.pdf

}

//create second histogram
TH1D * h1 = (TH1D*)original_file->Get("h_multiplicity_cats_pythia_SPS_ratio_noCR");

TAxis *yaxis_1 = h1->GetYaxis();

TAxis *xaxis_1 = h1->GetXaxis();

TH1F *h_SPS_noCR = (TH1F*)h1->Clone("h_SPS_noCR");

//set axis titles
h_SPS_noCR->GetXaxis()->SetTitle("N_{VELO}/N_{noBias PYTHIA}^{2.0<#eta<4.5}");
h_SPS_noCR->GetYaxis()->SetTitle("#scale[0.6]{#frac{d#sigma(B_{c}^{+})}{dN}}/#scale[0.6]{#frac{d#sigma(B^{+})}{dN}}");

for (int i = 0; i <= 16; ++i) {
	
	double Xcenter_1 = h1->GetXaxis()->GetBinCenter(i);
	
	double X_content_1 = h1->GetBinContent(i);	

	double Velo_efficency_MC_greater_than_50, Velo_efficency_MC_less_than_50, corrected_value_1;
	
	//here we should add an if loop for bin values less than 50
	if (Xcenter_1 <= 50) {

	Velo_efficency_MC_less_than_50 = 0.988;
	
	corrected_value_1 = X_content_1 * Velo_efficency_MC_less_than_50;
	
	h_SPS_noCR->SetBinContent(i, corrected_value_1);
	
		} 
	else {

	Velo_efficency_MC_greater_than_50 = 0.987;
	
	corrected_value_1 = X_content_1 * Velo_efficency_MC_greater_than_50;
		
	h_SPS_noCR->SetBinContent(i, corrected_value_1);
		}
}

//Add the colour reconnection models (DPS)

TH1D * h3 = (TH1D*)original_file->Get("h_multiplicity_cats_pythia_DPS_ratio_wiCR");

TAxis *yaxis_3 = h3->GetYaxis();
TAxis *xaxis_3 = h3->GetXaxis();

TH1F *h_DPS_wiCR = (TH1F*)h3->Clone("h_DPS_wiCR");

//set axis titles
h_DPS_wiCR->GetXaxis()->SetTitle("N_{VELO}/N_{noBias PYTHIA}^{2.0<#eta<4.5}");
h_DPS_wiCR->GetYaxis()->SetTitle("#scale[0.6]{#frac{d#sigma(B_{c}^{+})}{dN}}/#scale[0.6]{#frac{d#sigma(B^{+})}{dN}}");

for (int i = 0; i <= 16; ++i) {
	
	double Xcenter_1 = h3->GetXaxis()->GetBinCenter(i);
	
	double X_content_1 = h3->GetBinContent(i);	

	double Velo_efficency_MC_greater_than_50, Velo_efficency_MC_less_than_50, corrected_value_1;
	
	//here we should add an if loop for bin values less than 50
	if (Xcenter_1 <= 50) {

	Velo_efficency_MC_less_than_50 = 0.988;
	
	corrected_value_1 = X_content_1 * Velo_efficency_MC_less_than_50;
	
	h_DPS_wiCR->SetBinContent(i, corrected_value_1);
	
		} 
	else {

	Velo_efficency_MC_greater_than_50 = 0.987;
	
	corrected_value_1 = X_content_1 * Velo_efficency_MC_greater_than_50;
		
	h_DPS_wiCR->SetBinContent(i, corrected_value_1);
		}
}


//Add the colour reconnection models (DPS)

TH1D * h4 = (TH1D*)original_file->Get("h_multiplicity_cats_pythia_SPS_ratio_wiCR");

TAxis *yaxis_4 = h4->GetYaxis();
TAxis *xaxis_4 = h4->GetXaxis();

TH1F *h_SPS_wiCR = (TH1F*)h4->Clone("h_DPS_wiCR");

//set axis titles
h_SPS_wiCR->GetXaxis()->SetTitle("N_{VELO}/N_{noBias PYTHIA}^{2.0<#eta<4.5}");
h_SPS_wiCR->GetYaxis()->SetTitle("#scale[0.6]{#frac{d#sigma(B_{c}^{+})}{dN}}/#scale[0.6]{#frac{d#sigma(B^{+})}{dN}}");

for (int i = 0; i <= 16; ++i) {
	
	double Xcenter_1 = h4->GetXaxis()->GetBinCenter(i);
	
	double X_content_1 = h4->GetBinContent(i);	

	double Velo_efficency_MC_greater_than_50, Velo_efficency_MC_less_than_50, corrected_value_1;
	
	//here we should add an if loop for bin values less than 50
	if (Xcenter_1 <= 50) {

	Velo_efficency_MC_less_than_50 = 0.988;
	
	corrected_value_1 = X_content_1 * Velo_efficency_MC_less_than_50;
	
	h_SPS_wiCR->SetBinContent(i, corrected_value_1);
	
		} 
	else {

	Velo_efficency_MC_greater_than_50 = 0.987;
	
	corrected_value_1 = X_content_1 * Velo_efficency_MC_greater_than_50;
		
	h_SPS_wiCR->SetBinContent(i, corrected_value_1);
		}
}


//THIS FUNCTION WILL BE USEFUL FOR BRANCHING FRACTION
//h_DPS_noCR->Scale(1/n_tracks_noBias);

//add text



//Create branching fraction histogram
//double branching_fraction_ratio, u_sys, u_stat;

double branching_fraction_ratio [16] = {0.0980867, 0.0980867, 
0.0980867, 0.0980867, 
0.0980867, 0.0980867, 
0.0980867, 0.0980867, 
0.0980867, 0.0980867, 
0.0980867, 0.0980867, 
0.0980867, 0.0980867, 
0.0980867, 0.0980867};

double u_stat [16] = {0.0137286, 0.0137286, 
0.0137286, 0.0137286, 
0.0137286, 0.0137286, 
0.0137286, 0.0137286, 
0.0137286, 0.0137286, 
0.0137286, 0.0137286, 
0.0137286, 0.0137286, 
0.0137286, 0.0137286};

double u_sys [16] = {0.0104736, 0.0104736, 
0.0104736, 0.0104736, 
0.0104736, 0.0104736, 
0.0104736, 0.0104736, 
0.0104736, 0.0104736,
0.0104736, 0.0104736, 
0.0104736, 0.0104736, 
0.0104736, 0.0104736};

//int n = 16;

//TH1F* h_branching = new TH1F("h_branching", "h_branching", n, 0.0, 80);

//Fill histogram
//for (int i = 1; i <= 16; ++i) {
//	h_branching->SetBinContent(i, branching_fraction_ratio[i]);
//	h_branching->SetBinError(i, u_stat[i]);
//}
//h_branching->Draw();

//from https://root-forum.cern.ch/t/histogram-th1d-with-two-error-bars-systematic-and-statistical-uncertainty/46079 


//TH1F * h3 = new TH1F("h3", "h3", n, 0.0, 80);
//TH1F * histJustUsedForDrawing = (TH1F*)h3->Clone("h_branching");

//create a systtematic histogram
//for (int i = 0; i <= 16; ++i) {
//	histJustUsedForDrawing->SetBinContent(i, branching_fraction_ratio[i]);
//	histJustUsedForDrawing->SetBinError(i, u_sys[i]);
//}


//Apply the branching fraction 

//multiply hisgorams to create new
//TH1F h_branch_stat = (*h_DPS_noCR)*(*h_branching);

//change name
//h_branch_stat.SetTitle("h_branch_stat");


//clone in modified hisogram
//TH1F * h_DPS_noCR_branch_stat = (TH1F*)h_branch_stat.Clone("dummy");

//show
//h_DPS_noCR_branch_sys->Print();
//h_DPS_noCR_branch_stat->Draw();

//h_DPS_noCR_branch_sys.Draw();

//h_DPS_noCR_branch_sys.Draw();


//h_DPS_noCR_branch_stat.Draw("Same");

//no bias numbers for CR and non-CR
//From Tom via Slack 1/2/23

double n_tracks_noBias, n_tracks_noBias_CR; //multiplicity_over_noBias;

//int n = 17;

n_tracks_noBias = 12.74;
n_tracks_noBias_CR = 13.16;

//(^from data triggered on the clock with no requirement that a PV is formed). 

//Scale to no bias tracks
h_DPS_noCR->GetXaxis()->SetLimits(0, 80/n_tracks_noBias);
h_SPS_noCR->GetXaxis()->SetLimits(0, 80/n_tracks_noBias);

h_DPS_wiCR->GetXaxis()->SetLimits(0, 80/n_tracks_noBias_CR);
h_SPS_wiCR->GetXaxis()->SetLimits(0, 80/n_tracks_noBias_CR);

//remove percentage scaling on y-axis

h_DPS_noCR->Scale(0.01);
h_SPS_noCR->Scale(0.01);

h_DPS_wiCR->Scale(0.01);
h_SPS_wiCR->Scale(0.01);


//h_DPS_noCR->Sumw2(0);
//h_SPS_noCR->Sumw2(0);

//h_DPS_wiCR->Sumw2(0);
//h_SPS_wiCR->Sumw2(0);


//h->


//Create new canvas
auto mycanvas = new TCanvas();

h_SPS_noCR->GetYaxis()->SetRangeUser(0, 0.005);

h_SPS_noCR->GetXaxis()->CenterTitle("True");
h_SPS_noCR->GetYaxis()->CenterTitle("True");
h_SPS_noCR->GetYaxis()->SetTitleOffset(2.3); 

//h_DPS_noCR->Draw();

h_SPS_noCR->Draw("Same");

//h_SPS_wiCR->Draw("Same");
//h_DPS_wiCR->Draw("Same");

auto legend = new TLegend(.9,.75,.65,.9);
legend->SetHeader("0 < p_{T} < 20","C");
//legend->AddEntry(h_DPS_noCR,"DPS Default","PE");
legend->AddEntry(h_SPS_noCR,"SPS Default","PE");
//legend->AddEntry(h_DPS_wiCR,"DPS QCD-CR","PE");
//legend->AddEntry(h_SPS_wiCR,"SPS QCD-CR","PE");
//->EditEntryAttLine();
//legend->gStyle()->SetLegendBorderSize(1);

legend->Draw();


}


