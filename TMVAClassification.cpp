//BDT for optomisation

namespace ewalton {}
using namespace ewalton;

//Load required modules
#include <map>
#include <math.h>
#include <string>

#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TObjString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TMVA/DataLoader.h"


#include "../TMVA-v4.2.0/test/TMVAGui.C"

#if not defined(__CINT__) || defined(__MAKECINT__)
// needs to be included when makecint runs (ACLIC)
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"
#endif

void TMVAClassification( TString myMethodList = "BDTG", TString trainOn = "MC" )
{

	//load the the signal and background files

	//Signal
	TFile* signal_file = new TFile();

	signal_file = TFile().Open("Signal_Opt.root");

	//test the file has loaded correctly

	signal_file->ls();

	TChain* signal = (TChain*)signal_file->Get("DecayTree");

	//check the signal has loaded correctly
	signal->Print();

	//Background
	TFile* background_file = new TFile();

	//For testing purposes

	//background_file = TFile().Open("Background_Opt.root");

	background_file = TFile().Open("Signal_Opt.root");

	//test the file has loaded correctly
	background_file->ls();

	TChain* background = (TChain*)background_file->Get("DecayTree");

	//Check the background has loaded correctly
	background->Print();

   //---------------------------------------------------------------
   // This loads the library
   TMVA::Tools::Instance();

   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   // --- Boosted Decision Trees
   Use["BDT"]             = 1; // uses Adaptive Boost
   Use["BDTG"]            = 1; // uses Gradient Boost
   Use["BDTB"]            = 0; // uses Bagging
   Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
   Use["BDTF"]            = 0; // allow usage of fisher discriminant for node splitting
   // ---------------------------------------------------------------

   std::cout << std::endl;
   std::cout << "==> Start TMVAClassification" << std::endl;

   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = TMVA::gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) std::cout << it->first << " ";
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
      }
   }

   // --------------------------------------------------------------------------------------------------

   // --- Here the preparation phase begins

   // Create a ROOT output file where TMVA will store ntuples, histograms, etc.

   //TString outDir = "plots";

	 //Output into the same directory as the network
   TString outDir = "../";

 		//name the output file
   TString outfileName = "TMVA_Bc2JpsiPi_" +  myMethodList + "_" + trainOn + "_" + ".root";
   TFile* outputFile = TFile::Open( outfileName, "RECREATE" );

   // Create the factory object.
   // TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_" + trainOn + "_" , outputFile,
   //                                             "!V:!Silent:Color:DrawProgressBar:Transformations=I;D;P;G,D:AnalysisType=Classification" );

   TMVA::Factory *factory = new TMVA::Factory( "TMVAClassification_" + trainOn + "_" , outputFile,
                                               "!V:!Silent:Color:DrawProgressBar:Transformations=I:AnalysisType=Classification" );

	//Create the dataset
   TMVA::DataLoader *dataloader=new TMVA::DataLoader("dataset");


   // Define the input variables that shall be used for the MVA training

	 //These must have the same name in both "signal" and "background"

	 //Here's where my input starts

	 //kinematic variables
	 dataloader->AddVariable( "B_P","B_P","", 'F' );
	 //dataloader->AddVariable( "B_PE","B_PE","", 'F' );
	 dataloader->AddVariable( "B_PT","B_PT","", 'F' );
	 //dataloader->AddVariable( "B_PX","B_PX","", 'F' );
	 //dataloader->AddVariable( "B_PY","B_PY","", 'F' );
	 //dataloader->AddVariable( "B_PZ","B_PZ","", 'F' );

	 //dataloader->AddVariable( "Jpsi_PT","Jpsi_PT","", 'F' );
	 //dataloader->AddVariable( "mum_PT","mum_PT","", 'F' );
	 //dataloader->AddVariable( "mup_PT","mup_PT","", 'F' );
	 //dataloader->AddVariable( "pi_PT","pi_PT","", 'F' );

	 //goodness of fit variables & IP
	 dataloader->AddVariable( "mup_IP_OWNPV","B_IP_OWNPV","", 'F' );
	 dataloader->AddVariable( "B_IPCHI2_OWNPV","B_IPCHI2_OWNPV","", 'F' );

	 dataloader->AddVariable( "Jpsi_IPCHI2_OWNPV","Jpsi_IPCHI2_OWNPV","", 'F' );
	 dataloader->AddVariable( "Jpsi_IP_OWNPV","Jpsi_IP_OWNPV","", 'F' );

	 dataloader->AddVariable( "mup_IPCHI2_OWNPV","mup_IPCHI2_OWNPV","", 'F' );
	 dataloader->AddVariable( "mum_IPCHI2_OWNPV","mum_IPCHI2_OWNPV","", 'F' );
	 dataloader->AddVariable( "mum_IP_OWNPV","mum_IP_OWNPV","", 'F' );
	 dataloader->AddVariable( "mup_IP_OWNPV","mup_IP_OWNPV","", 'F' );

	 dataloader->AddVariable( "pi_IPCHI2_OWNPV","pi_IPCHI2_OWNPV","", 'F' );
	 dataloader->AddVariable( "pi_IP_OWNPV","pi_IP_OWNPV","", 'F' );



   //New Variables as of 1/3/2023
   //dataloader->AddVariable( "B_FD*","B_FD*","", 'F' );
   dataloader->AddVariable( "mum_ORIVX_CHI2","mum_ORIVX_CHI2*","", 'F' );
   dataloader->AddVariable( "mup_ORIVX_CHI2","mup_ORIVX_CHI2","", 'F' );
	 dataloader->AddVariable( "pi_ORIVX_CHI2","pi_ORIVX_CHI2","", 'F' );

   dataloader->AddVariable( "Jpsi_ORIVX_CHI2","Jpsi_ORIVX_CHI2","", 'F' );
	 dataloader->AddVariable( "Jpsi_ORIVX_NDOF","Jpsi_ORIVX_NDOF","", 'F' );
	 dataloader->AddVariable( "Jpsi_FDCHI2_ORIVX","Jpsi_FDCHI2_ORIVX","", 'F' );

   dataloader->AddVariable( "B_NumVtxWithinChi2WindowOneTrack","B_NumVtxWithinChi2WindowOneTrack","", 'F' );

   dataloader->AddVariable( "B_FDCHI2_OWNPV","B_FDCHI2_OWNPV","", 'F' );

	 dataloader->AddVariable( "B_NextBestPVToMCPV_*", "B_NextBestPVToMCPV_*", 'F' );
	//Spectator variables

	//Tom's recomenadation (23/2/23)
	 dataloader->AddSpectator("B_M" );
	 dataloader->AddSpectator("B_MM" );
//////////////////////////////////////

	 dataloader->AddSpectator("PVNDOF" );

	 dataloader->AddSpectator( "nPV" );
	 dataloader->AddSpectator( "nTracks" );
	 dataloader->AddSpectator( "nVeloTracks" );
	 dataloader->AddSpectator( "B_RecPV_NextPV" );
	 dataloader->AddSpectator( "B_RecPV_NextPV_nTracks" );

	 dataloader->AddSpectator( "B_RecPV_nTracks" );
	 dataloader->AddSpectator( "B_RecPV_nTracks_Forwards" );
	 dataloader->AddSpectator( "B_RecPV_nTracks_Backwards" );

	 //Refit
	 dataloader->AddSpectator( "B_RecPV_ReFit_nTracks" );
	 dataloader->AddSpectator( "B_RecPV_ReFit_nTracks_Backwards" );
	 dataloader->AddSpectator( "B_RecPV_ReFit_nTracks_Forwards" );

	 //Location of the B

	 dataloader->AddSpectator( "PVNTRACKS" );
	 dataloader->AddSpectator( "PVNDOF" );

    //Background catagory
    dataloader->AddSpectator( "B_BKGCAT" );



	 // global event weights per tree (see below for setting event-wise weights)
   Double_t signalWeight     = 1.0;
   Double_t backgroundWeight = 1.0;

   // Apply additional cuts on the signal and background samples (can be different)

   //for truth matching, add the BKG cut. Ref: https://hackmd.io/@sbouchiba/HkQv6WJMq
   //TCut mycutSig;
   //if(trainOn == "MC")
	 TCut mycutSig = "B_MM > 6150  && B_MM < 6350 && B_RecPV_nTracks > 40 && (B_BKGCAT == 20)";

	 //||(B_BKGCAT==50))

    //Use the upper-mass sideband as the background
	 TCut mycutBkg = "B_MM > 6350 && B_RecPV_nTracks > 40";


   dataloader->AddSignalTree    ( signal,     signalWeight     );
   dataloader->AddBackgroundTree( background, backgroundWeight );
   dataloader->PrepareTrainingAndTestTree( mycutSig, mycutBkg,
                                        "nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V" );
  //If nTrain Signal=0 and nTest Signal=0, the signal sample is split in half for training and testing

   // dataloader->SetSignalWeightExpression("weight");

   // ---- Book MVA methods

   // Boosted Decision Trees
   if (Use["BDTG"]) // Gradient Boost
      factory->BookMethod(dataloader, TMVA::Types::kBDT, "BDTG",
                           "!H:!V:NTrees=500:MinNodeSize=2.5%:BoostType=Grad:Shrinkage=0.10:UseBaggedBoost:BaggedSampleFraction=0.5:nCuts=40:MaxDepth=3:NegWeightTreatment=Pray" );

   if (Use["BDT"])  // Adaptive Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDT",
                           "!H:!V:NTrees=500:MinNodeSize=3.5%:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:UseBaggedBoost:BaggedSampleFraction=0.5:SeparationType=GiniIndex:nCuts=80" );

   if (Use["BDTB"]) // Bagging
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTB",
                           "!H:!V:NTrees=400:BoostType=Bagging:SeparationType=GiniIndex:nCuts=20" );

   if (Use["BDTD"]) // Decorrelation + Adaptive Boost
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTD",
                           "!H:!V:NTrees=400:MinNodeSize=5%:MaxDepth=3:BoostType=AdaBoost:SeparationType=GiniIndex:nCuts=20:VarTransform=Decorrelate" );

   if (Use["BDTF"])  // Allow Using Fisher discriminant in node splitting for (strong) linearly correlated variables
      factory->BookMethod( dataloader, TMVA::Types::kBDT, "BDTMitFisher",
                           "!H:!V:NTrees=50:MinNodeSize=2.5%:UseFisherCuts:MaxDepth=3:BoostType=AdaBoost:AdaBoostBeta=0.5:SeparationType=GiniIndex:nCuts=20" );

   // Train MVAs using the set of training events
   factory->TrainAllMethods();

   // ---- Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // ----- Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();

   // --------------------------------------------------------------

   // Save the output
   outputFile->Close();

   std::cout << "==> Wrote root file: " << outputFile->GetName() << std::endl;
   std::cout << "==> TMVAClassification is done!" << std::endl;

   delete factory;
   delete dataloader;

   // Launch the GUI for the root macros
   if (!gROOT->IsBatch()) TMVA::TMVAGui( outfileName );


}
