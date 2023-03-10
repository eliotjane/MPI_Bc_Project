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


//modified 21/2/23 for optomisation of selection EJW

namespace ewalton {}
using namespace ewalton;

//TString dir = "/eos/user/m/mwalton/DLL_Data/reporcessed_nominal/MPI_data_MC/2018_MC_*.root";

//DECLARE_COMPONENT( Background_digestion )

void Signal_digestion(){

	//directory
	//TString dir = "/root://eoslhcb.cern.ch//eos/user/m/mwalton/MPI_data/MC_2018_DST";


	TChain signal("/Btuple/DecayTree;1");

//	const char *h1dir = gSystem->AccessPathName(dir) ? "./2018_*.root" : "/root://eoslhcb.cern.ch//eos/user/m/mwalton/MPI_data/";


//	   gSystem->Setenv("H1",h1dir);
//	}

	//Set size of the signal (not sure if necessary)
	signal.SetCacheSize(20*1024*1024);

	//add all the files together
//  signal.Add("/eos/user/m/mwalton/MPI_MC/Vertex_2018_MD_MC_Opt*.root");

	TFile *f = TFile::Open("root://xrootd.echo.stfc.ac.uk/lhcb:user/lhcb/user/m/mwalton/2023_02/718592/718592997/Btuple_MC_Selection.root");


//	signal.Add("/home/user1/Desktop/MPI_Bc_Project/MC_LFN_2018.root");
	//deactivate all branches
	signal.SetBranchStatus("*", 0);

	//activate all desired branches
	signal.SetBranchStatus("*IP*",1);
	signal.SetBranchStatus("*IPCHI2_OWNPV*",1);
	signal.SetBranchStatus("*PT*",1);
	signal.SetBranchStatus("B_PT",0);

	signal.SetBranchStatus("B_OWNPV_CHI2",1);
	signal.SetBranchStatus("B_OWNPV_NDOF",1);
	signal.SetBranchStatus("nVeloTracks",1);
	signal.SetBranchStatus("nTracks",1);
	signal.SetBranchStatus("nPVs",1);
	signal.SetBranchStatus("B_MM",1);
	signal.SetBranchStatus("B_M",1);

	signal.SetBranchStatus("B_NEW_BPV_NTRACKS_BEFORE_REFIT", 1);
	signal.SetBranchStatus("B_NEW_BPV_TRACK_ETA", 1);
	signal.SetBranchStatus("B_NEW_BPV_NTRACKS", 1);
	signal.SetBranchStatus("B_NEW_BPV_NDOF_BEFORE_REFIT", 1);
	signal.SetBranchStatus("B_NEW_BPV_NDOF", 1);
	signal.SetBranchStatus("B_NEW_BPV_FORTRACKS", 1);
	signal.SetBranchStatus("B_NEW_BPV_BACKTRACKS", 1);
	signal.SetBranchStatus("B_MMERR", 1);

  signal.SetBranchStatus("B_MC*", 1);
  signal.SetBranchStatus("B_Rec*", 1);
	signal.SetBranchStatus("B_P*", 1);
  signal.SetBranchStatus("B_TRUE*", 1);
signal.SetBranchStatus("B_FD*", 1);
signal.SetBranchStatus("Jpsi_O*", 1);
signal.SetBranchStatus("Jpsi_F*",1);
signal.SetBranchStatus("B_NumV*",1);
signal.SetBranchStatus("B_BKGCAT",1);
signal.SetBranchStatus("*_ORIVX_*", 1);

//get PVs
  signal.SetBranchStatus("PV*", 1);

	//Get trigger information
	signal.SetBranchStatus("*_L0*", 1);


//create new file and clone data to it

TFile newfile("Signal_Opt.root", "recreate");
auto newtree = signal.CloneTree(-1, "");

//write to new file
newfile.Write();

}
