#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>

#include "TLorentzVector.h"
#include "TFile.h"
#include "TNtuple.h"
#include "TCanvas.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"


using namespace std;

void myFirstMacro()
{
	//Initialize histograms
	TH1F *h = new TH1F("h", "h", 100, 0, 4);
	TH1F *k = new TH1F("k", "k", 100, -5, 5);

	//Read in AMPT file
	ifstream myFile;
	myFile.open("ampt 1.dat");

	if (!myFile)
	{
		printf("Input file does not exist!\n");
		return;
	}
	else
	{
		cout << "--> Successfully opened file! " << endl << endl;
	}

	while (myFile)
	{
		int evtnumber;
		int testnum;
		int nlist;
		double impactpar;
		int npartproj;
		int nparttarg;
		int npartprojelas;
		int npartprojinelas;
		int nparttargelas;
		int nparttarginelas;
		double junk;

		myFile >> evtnumber >> testnum >> nlist >> impactpar >> npartproj >> nparttarg >> npartprojelas >> npartprojinelas >> nparttargelas >> nparttarginelas >> junk;

		if (!myFile) break;

		for (int i = 0; i < nlist; i++)
		{
			int partid;
			float px;
			float py;
			float pz;
			float mass;
			double space[4];

			myFile >> partid >> px >> py >> pz >> mass >> space[0] >> space[1] >> space[2] >> space[3];

			if (abs(partid) != 211 && abs(partid) != 321 && abs(partid) != 2212)
			{
				continue;
			}

			float pT;
			float pse;

			pT = TMath::Sqrt(px * px + py * py);
			h->Fill(pT);

			pse = -TMath::Log((TMath::Sqrt(px * px + py * py)) / (TMath::Sqrt(px * px + py * py + pz * pz) + pz));
			k->Fill(pse);
		}
	}


	TCanvas *c1 = new TCanvas("c1", "aa", 700, 600);
	h->Draw();
	TCanvas *c2 = new TCanvas("c2", "bb", 700, 600);
	k->Draw();

	//Initialize and fill histogram with random Gaussian data
	/*
	TH1F *h = new TH1F("h","h",10,0,10);
	h->Fill(1);
	h->Fill(1);
	h->Fill(1);
	h->Fill(5);
	h->Fill(2);
	h->Fill(7);
	h->Fill(7);
	h->Draw();

	//Get mean
	float mean = h->GetMean();
	cout << "The mean is " << mean << endl;

	//Get width
	float width = h->GetRMS();
	cout <<"The width is " << width << endl;

	h->SetFillColor(kBlue);
	 */
}
