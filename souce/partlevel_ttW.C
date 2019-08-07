#define partlevel_ttW_cxx


#include "partlevel_ttW.h"
#include <TH2.h>
#include <TStyle.h>
#include "Math/Vector4D.h"

TH1F *h_cutflow_2l[2];
string input_name="";

void partlevel_ttW::Begin(TTree * /*tree*/)
{
  TString option = GetOption();
}

void partlevel_ttW::SlaveBegin(TTree * /*tree*/)
{
  TString option = GetOption();
  std::cout << "option ="<< option << std::endl;
  input_name=option;
  
  const std::vector<TString> s_cutDescs =
    {  "Preselections","Nleps","lepPt1>20","lepPt0>25","lepCentr","SS","jPt","bCentr","qforwE","mm","OF","ee"};
  int Ncuts = s_cutDescs.size();
  h_cutflow_2l[0] = new TH1F("cf2l","cf2l",Ncuts,0,Ncuts);
  h_cutflow_2l[1] = new TH1F("cf2l_raw","cf2l_raw",Ncuts,0,Ncuts);
  for (int bin=1;bin<=Ncuts;++bin){
    h_cutflow_2l[0]->GetXaxis()->SetBinLabel(bin,s_cutDescs[bin-1]);
    h_cutflow_2l[1]->GetXaxis()->SetBinLabel(bin,s_cutDescs[bin-1]);
  }



  
}

Bool_t partlevel_ttW::Process(Long64_t entry)
{
  
  //fReader.SetEntry(entry);
  fReader.SetLocalEntry(entry);
  // print some information about the current entry
  if ((entry)%10000 == 0)
    printf("Processing Entry  %llu \n", entry);

  // increase the total number of entries
  ++fNumberOfEvents;
  
  weight_tot=*weight_mc * *weight_pileup;
  int cf_counter=0;


  //loop over electrons and muons
  nJet = jet_pt.GetSize();
  nEl = el_pt.GetSize();
  nMu = mu_pt.GetSize();
  const int totleptons = nEl+nMu;
  int dilep_type = 1 + nEl;//  1(mumu) 2(OF) 3(ee)
  //Nlep


  //presel
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;

  //Nleps
  if(totleptons!=2) return 0;
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;

  //define lead/sublead lepton and it's charge

  float l0_charge,l1_charge;  
  float l0_pt=-999,l1_pt=-999;
  float l0_eta,l1_eta;
  //float l_charge[2]; float l_pt[2]; float l_eta[2];
  //TLorentzVector lep_4v[2];
  //  ROOT::Math::PtEtaPhiEVector lep_4v[2]; 

  if ( dilep_type==1 ){ 
    //lep_4v[0].SetCoordinates(mu_pt[0]/1e3,mu_eta[0],mu_phi[0],mu_e[0]);// sets pt,eta,phi,e for a PtEtaPhiEVector
    //lep_4v[1].SetCoordinates(mu_pt[1]/1e3,mu_eta[1],mu_phi[1],mu_e[1]);

    l0_charge= mu_charge[0]; l1_charge= mu_charge[1];
    l0_eta= mu_eta[0]; l1_eta= mu_eta[1];
    l0_pt= mu_pt[0]/1e3; l1_pt= mu_pt[1]/1e3;
  }
  else if ( dilep_type==3 ){ 
    //lep_4v[0].SetCoordinates(el_pt[0]/1e3,el_eta[0],el_phi[0],el_e[0]);// sets pt,eta,phi,e for a PtEtaPhiEVector
    //lep_4v[1].SetCoordinates(el_pt[1]/1e3,el_eta[1],el_phi[1],el_e[1]);

    l0_charge= el_charge[0]; l1_charge= el_charge[1];
    l0_eta= el_eta[0]; l1_eta= el_eta[1];
    l0_pt= el_pt[0]/1e3; l1_pt= el_pt[1]/1e3;
  }
  else if ( dilep_type==2 ){ 
    if(mu_pt[0]>el_pt[0]){ 
      //lep_4v[0].SetCoordinates(mu_pt[0]/1e3,mu_eta[0],mu_phi[0],mu_e[0]);// sets pt,eta,phi,e for a PtEtaPhiEVector
      //lep_4v[1].SetCoordinates(el_pt[0]/1e3,el_eta[0],el_phi[0],el_e[0]);

      l0_charge= mu_charge[0]; l1_charge= el_charge[0];
      l0_eta= mu_eta[0]; l1_eta= el_eta[0];
      l0_pt= mu_pt[0]/1e3; l1_pt= el_pt[0]/1e3;
    }
    else{    
      //lep_4v[0].SetCoordinates(el_pt[0]/1e3,el_eta[0],el_phi[0],el_e[0]);
      //lep_4v[1].SetCoordinates(mu_pt[0]/1e3,mu_eta[0],mu_phi[0],mu_e[0]);// sets pt,eta,phi,e for a PtEtaPhiEVector

      l1_charge= mu_charge[0]; l0_charge= el_charge[0];
      l1_eta= mu_eta[0]; l0_eta= el_eta[0];
      l1_pt= mu_pt[0]/1e3; l0_pt= el_pt[0]/1e3;
    }
  }


  //lep Pt cuts
  if(l1_pt<20) return 0;  
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;
  if(l0_pt<25) return 0;  
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;


//   for(unsigned int e=0;e<el_pt->size();e++){
//     if(el_pt->at(e)/1000.<27) continue;
//     if(fabs(el_eta->at(e))>2.5) continue;
//     Nlep+=1;
//   }

//   for(unsigned int m=0;m<mu_pt->size();m++){
//     if(mu_pt->at(m)/1000.<27) continue;
//     if(fabs(mu_eta->at(m))>2.5) continue;
//     Nlep+=1;
//   }

//   cout << Nlep << endl;

  //2 same sign charged leptons (e,mu) with pT>25(20)GeV 
  //sel_array[0]=(nTaus_OR_Pt25 == 0 && nJets_OR_T_MV2c10_70 == 1 && nJets_OR_T >= 4 );  // Region 1 
  //sel_array[1]=(nTaus_OR_Pt25 == 0 && nJets_OR_T_MV2c10_70 >= 2 && nJets_OR_T >= 4 );  // Region 2
  //sel_array[2]=(nTaus_OR_Pt25 == 0 && nJets_OR_T_MV2c10_70 == 1 && nJets_OR_T == 3 );  // Region 3 
  //sel_array[3]=(nTaus_OR_Pt25 == 0 && nJets_OR_T_MV2c10_70 >= 2 && nJets_OR_T == 3 );  // Region 4
  
  
  return kTRUE;
}

void partlevel_ttW::SlaveTerminate()
{
}

void partlevel_ttW::Terminate()
{
  printf("\nTotal Number of Events: %d\n", fNumberOfEvents);

  string outname="Res_"+input_name+".root";
  TFile hfile(outname.c_str(),"RECREATE"); //,"tHq"
  h_cutflow_2l[0]->Write(); 
  h_cutflow_2l[1]->Write(); 
  fOutput->Write();

  
}
