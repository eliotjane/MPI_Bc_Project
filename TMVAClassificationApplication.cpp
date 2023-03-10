
// 27/2/2023
// Eliot Walton TMVA Classification Application
// For Bc multiplicity analysis

/**********************************************************************************
 * Project   : TMVA - a Root-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Exectuable: TMVAClassificationApplication                                      *
 *                                                                                *
 * This macro provides a simple example on how to use the trained classifiers     *
 * within an analysis module                                                      *
 **********************************************************************************/

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <math.h>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include <TChain.h>
#include "TStopwatch.h"

#include "../inc//TMVA/Tools.h"
#include "../inc/TMVA/Reader.h"
#include "../inc/TMVA/MethodCuts.h"

//#include "TMVAGui.C"


using namespace std;
using namespace TMVA;

void TMVAClassificationApplication(TString decay = "Signal", TString dataType = "Data", TString myMethod = "BDTG", TString trainedOn = "MC" ) 
{   
#ifdef __CINT__
   gROOT->ProcessLine( ".O0" ); // turn off optimization in CINT
#endif

   //---------------------------------------------------------------
   std::cout << "==> Start TMVAClassificationApplication" << std::endl;

   TString outFileName = "../";

   TChain* theTree = new TChain("DecayTree");
   if(decay == "Signal" && dataType == "Data"){ 	  
	theTree->Add("./BDT5/TMVA_Bc2JpsiPi_BDTG_MC_.root");
   // theTree->Add("../root_files/PreSelection/DVntuple_Bc_Data_2012_MagUp.root");
	outFileName += "signal_BDTG.root";
   } else {
	cout << "Unknown filename, CRASHING." << endl;
	throw "ERROR";
   }

   // Ouput tree
   TFile *hFile = new TFile(outFileName,"RECREATE");
   TTree* tree = theTree->CloneTree(0);

   // This loads the library
   TMVA::Tools::Instance();

   // --- Create the Reader object
   TMVA::Reader *reader = new TMVA::Reader( "Color:!Silent" );    

   // Create a set of variables and declare them to the reader

//   	 dataloader->AddVariable( "B_P","B_P","", 'F' );
//	 dataloader->AddVariable( "B_PE","B_PE","", 'F' );
//	 dataloader->AddVariable( "B_PT","B_PT","", 'F' );
//	 dataloader->AddVariable( "B_PX","B_PX","", 'F' );
//	 dataloader->AddVariable( "B_PY","B_PY","", 'F' );
//	 dataloader->AddVariable( "B_PZ","B_PZ","", 'F' );

	 //dataloader->AddVariable( "Jpsi_PT","Jpsi_PT","", 'F' );
	 //dataloader->AddVariable( "mum_PT","mum_PT","", 'F' );
	 //dataloader->AddVariable( "mup_PT","mup_PT","", 'F' );
	 //dataloader->AddVariable( "pi_PT","pi_PT","", 'F' );

	 //goodness of fit variables & IP
	 //dataloader->AddVariable( "mup_IP_OWNPV","B_IP_OWNPV","", 'F' );
	 //dataloader->AddVariable( "B_IPCHI2_OWNPV","B_IPCHI2_OWNPV","", 'F' );

	 //dataloader->AddVariable( "Jpsi_IPCHI2_OWNPV","Jpsi_IPCHI2_OWNPV","", 'F' );
	 //dataloader->AddVariable( "Jpsi_IP_OWNPV","Jpsi_IP_OWNPV","", 'F' );

	 //dataloader->AddVariable( "mup_IPCHI2_OWNPV","mup_IPCHI2_OWNPV","", 'F' );
	 //dataloader->AddVariable( "mum_IPCHI2_OWNPV","mum_IPCHI2_OWNPV","", 'F' );
	// dataloader->AddVariable( "mum_IP_OWNPV","mum_IP_OWNPV","", 'F' );
///dataloader->AddVariable( "mup_IP_OWNPV","mup_IP_OWNPV","", 'F' );

	// dataloader->AddVariable( "pi_IPCHI2_OWNPV","pi_IPCHI2_OWNPV","", 'F' );
	// dataloader->AddVariable( "pi_IP_OWNPV","pi_IP_OWNPV","", 'F' );

	//Spectator variables

	//Tom's recomenadation (23/2/23)
	 //dataloader->AddSpectator("B_M" );
	 //dataloader->AddSpectator("B_MM" );
//////////////////////////////////////

	 //dataloader->AddSpectator("PVNDOF" );

	
//	 dataloader->AddSpectator( "B_RecPV_NextPV" );
	// dataloader->AddSpectator( "B_RecPV_NextPV_nTracks" );

	 //dataloader->AddSpectator( "B_RecPV_nTracks" );
	 //dataloader->AddSpectator( "B_RecPV_nTracks_Forwards" );
	 //dataloader->AddSpectator( "B_RecPV_nTracks_Backwards" );

	 //Refit
	// dataloader->AddSpectator( "B_RecPV_ReFit_nTracks" );
	// dataloader->AddSpectator( "B_RecPV_ReFit_nTracks_Backwards" );
	// dataloader->AddSpectator( "B_RecPV_ReFit_nTracks_Forwards" );

	 //Location of the B

	// dataloader->AddSpectator( "PVNTRACKS" );
	// dataloader->AddSpectator( "PVNDOF" );

   Float_t r_B_P;
   Float_t r_B_PE;   
   Float_t r_B_PT;
   Float_t r_B_PX;
   Float_t r_B_PY;    
   Float_t r_B_PZ;

   Float_t r_B_IPCHI2_OWNPV;
   Float_t r_Jpsi_IPCHI2_OWNPV;
   Float_t r_mup_IPCHI2_OWNPV;
   Float_t r_mum_IPCHI2_OWNPV;
   Float_t r_pi_IPCHI2_OWNPV;

   Float_t r_Jpsi_PT;
   Float_t r_mup_PT;
   Float_t r_mum_PT;
   Float_t r_pi_PT;

   //These were spectators
	
	Float_t r_B_RecPV_NextPV;
	Float_t r_B_RecPV_NextPV_nTracks;

   Float_t r_B_RecPV_nTracks;
   Float_t r_B_RecPV_nTracks_Forwards;
   Float_t r_B_RecPV_nTracks_Backwards;

   Float_t r_B_RecPV_ReFit_nTracks;
   Float_t r_B_RecPV_ReFit_nTracks_Backwards;
   Float_t r_B_RecPV_ReFit_nTracks_Forwards;
   
   Float_t r_B_M;
   Float_t r_B_MM;


   Float_t r_nVeloTracks;
   Float_t r_nTracks;
   Float_t r_nPV;
   Float_t r_PVNDOF;
   Float_t r_PVNTRACKS;
    Float_t r_BDTG;

   reader->AddVariable( "B_cplus_IPCHI2_OWNPV := sqrt(B_cplus_IPCHI2_OWNPV)",&r_B_cplus_IPCHI2_OWNPV);
   reader->AddVariable( "muplus_IPCHI2_OWNPV := sqrt(muplus_IPCHI2_OWNPV)",&r_muplus_IPCHI2_OWNPV );
   reader->AddVariable( "muminus_IPCHI2_OWNPV:=sqrt(muminus_IPCHI2_OWNPV)",&r_muminus_IPCHI2_OWNPV );
   reader->AddVariable( "J_psi_1S_IPCHI2_OWNPV:=sqrt(J_psi_1S_IPCHI2_OWNPV)",&r_J_psi_1S_IPCHI2_OWNPV);
   reader->AddVariable( "piplus_IPCHI2_OWNPV:=sqrt(piplus_IPCHI2_OWNPV)",&r_piplus_IPCHI2_OWNPV);
   reader->AddVariable( "muplus_PT",&r_muplus_PT);
   reader->AddVariable( "muminus_PT",&r_muminus_PT);
   reader->AddVariable( "J_psi_1S_PT",&r_J_psi_1S_PT);
   reader->AddVariable( "piplus_PT",&r_piplus_PT);
   reader->AddVariable( "B_cplus_LOKI_DTF_CTAU", &r_B_cplus_LOKI_DTF_CTAU);
   reader->AddVariable( "B_cplus_LOKI_DTF_VCHI2NDOF", &r_B_cplus_LOKI_DTF_VCHI2NDOF);
    reader->AddVariable( "BDTG",&r_BDTG);

   reader->AddSpectator( "nVeloTracks", &r_nVeloTracks );
   reader->AddSpectator( "nTracks", &r_nTracks );
   reader->AddSpectator( "nPVs", &r_nPVs );
   reader->AddSpectator( "B_cplus_M" , &r_B_cplus_M);



   // --- Book the MVA methods

   TString dir    = "dataset/weights/";
   TString weightFile = dir + "TMVAClassification" +TString("_")+trainedOn+TString("__")+myMethod+ ".weights.xml" ;
	reader->BookMVA( myMethod, weightFile ); 

   Double_t B_cplus_IPCHI2_OWNPV;
   Double_t muplus_IPCHI2_OWNPV;
   Double_t muminus_IPCHI2_OWNPV;
   Double_t J_psi_1S_IPCHI2_OWNPV;
   Double_t piplus_IPCHI2_OWNPV;
   Double_t muplus_PT;
   Double_t muminus_PT;
   Double_t piplus_PT;
   Double_t J_psi_1S_PT;
   Double_t B_cplus_LOKI_DTF_CTAU;
   Double_t B_cplus_LOKI_DTF_VCHI2NDOF;
    Double_t BDTG;
    
   theTree->SetBranchAddress( "B_cplus_IPCHI2_OWNPV",&B_cplus_IPCHI2_OWNPV);
   theTree->SetBranchAddress( "muplus_IPCHI2_OWNPV",&muplus_IPCHI2_OWNPV);
   theTree->SetBranchAddress( "muminus_IPCHI2_OWNPV",&muminus_IPCHI2_OWNPV);
   theTree->SetBranchAddress( "J_psi_1S_IPCHI2_OWNPV",&J_psi_1S_IPCHI2_OWNPV );
   theTree->SetBranchAddress( "piplus_IPCHI2_OWNPV",&piplus_IPCHI2_OWNPV);
   theTree->SetBranchAddress( "muplus_PT",&muplus_PT);
   theTree->SetBranchAddress( "muminus_PT",&muminus_PT);
   theTree->SetBranchAddress( "J_psi_1S_PT",&J_psi_1S_PT);
   theTree->SetBranchAddress( "piplus_PT",&piplus_PT);
   theTree->SetBranchAddress( "B_cplus_LOKI_DTF_CTAU", &B_cplus_LOKI_DTF_CTAU);
   theTree->SetBranchAddress( "B_cplus_LOKI_DTF_VCHI2NDOF", &B_cplus_LOKI_DTF_VCHI2NDOF);
    theTree->SetBranchAddress( "BDTG",&r_BDTG);

   //output file---------------------------------------------------------------------------------------------------------------------------------------
  
   // Float_t r_BDTG_response;
//Float_t r_BDTG;
// double BDTG;
   //tree->Branch("BDTG_response",&r_BDTG_response, "BDTG_response/F");
   tree->Branch("BDTG",&r_BDTG, "BDTG/D");

   std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;

   TStopwatch sw;
   sw.Start();
   int N = theTree->GetEntries();
   for (Long64_t ievt=0; ievt< N ;ievt++) {

      if (ievt%5000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;

      theTree->GetEntry(ievt);


      // r_B_cplus_IPCHI2_OWNPV = sqrt(B_cplus_IPCHI2_OWNPV);
      r_muplus_IPCHI2_OWNPV = sqrt(muplus_IPCHI2_OWNPV);
      r_muminus_IPCHI2_OWNPV = sqrt(muminus_IPCHI2_OWNPV);
      // r_J_psi_1S_IPCHI2_OWNPV = sqrt(J_psi_1S_IPCHI2_OWNPV);
      r_piplus_IPCHI2_OWNPV = sqrt(piplus_IPCHI2_OWNPV);
      r_muplus_PT = muplus_PT;
      r_muminus_PT = muminus_PT;
      r_J_psi_1S_PT = J_psi_1S_PT;
      r_piplus_PT = piplus_PT;
      r_B_cplus_LOKI_DTF_CTAU = B_cplus_LOKI_DTF_CTAU;
      r_B_cplus_LOKI_DTF_VCHI2NDOF = B_cplus_LOKI_DTF_VCHI2NDOF;

      r_BDTG=reader->EvaluateMVA(myMethod);
      BDTG = double(r_BDTG);
      tree->Fill();    
   }

   // Get elapsed time
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();

   tree->Write();
   delete reader;
   hFile->Close();
    
   cout << "Wrote to file: " << outFileName << endl;
   cout << "==> TMVAClassificationApplication is done!" << endl << endl;
} 
