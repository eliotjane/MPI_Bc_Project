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

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

namespace ewalton {}
using namespace ewalton;

void Signal_digestion_URL(){

	//create the TChain
	TChain signal("/Btuple/DecayTree;1");

	//Create second TChain, get event tuple information
//	TChain eventTuple("/EventTuple/EventTuple;1");

	//Set size of the signal (not sure if necessary)
	signal.SetCacheSize(20*1024*1024);
	//eventTuple.SetCacheSize(20*1024*1024);

	// from the readerFile
	// Create a text string, which is used to output the text file
	string myText;

	// Read from the text file
	ifstream MyReadFile("MC-file-list.txt");

	// Use a while loop together with the getline() function to read the file line by line
	while (getline (MyReadFile, myText)) {

		//based on https://stackoverflow.com/questions/41456245/is-it-possible-to-iterate-through-a-text-file-lines-and-use-stringstream-to-pars

		string url;

		//std::replace(myText.begin(), myText.end(), ',', '');

		stringstream ss(myText);

		ss >> url;

		cout << "Url:" << url << "";

		cout << '\n';

	// Output the text from the file
		signal.Add(url.c_str());

	//add url files to event tuple information
	//	eventTuple.Add(url.c_str());

	}

	// Close the file
	MyReadFile.close();


//	`signal`.Add("/home/user1/Desktop/MPI_Bc_Project/MC_LFN_2018.root");
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

//add new vertex isolation information
	signal.SetBranchStatus("B_NextBestPVToMCPV_*", 1);

//get PVs
  signal.SetBranchStatus("PV*", 1);

	//Get trigger information
	signal.SetBranchStatus("*_L0*", 1);

	//get event tuple information
	//same method as above
//	eventTuple.SetBranchStatus("*", 0);
///	eventTuple.SetBranchStatus("eventNumber", 1);

//create new file and clone data to it

TFile newfile("Signal_Opt.root", "recreate");
auto newtree = signal.CloneTree(-1, "");
//auto newtree_twotree = eventTuple.CloneTree(-1, "");

//write to new file
newfile.Write();

}
