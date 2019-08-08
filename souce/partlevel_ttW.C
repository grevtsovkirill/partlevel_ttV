#define partlevel_ttW_cxx


#include "partlevel_ttW.h"
#include <TH2.h>
#include <TStyle.h>
#include <TLorentzVector.h>
#include <math.h>

TH1F *h_cutflow_2l[2];
string input_name="";
/////////////////////////////
// Histograms booking 2lSS ttW:
////////////////////////////
TH1D *hist_DRll01[10];
TH1D *hist_lep_Pt_0[10];
TH1D *hist_lep_Pt_1[10];
TH1D *hist_min_DRl0j[10];
TH1D *hist_min_DRl1j[10];
TH1D *hist_maxEta_ll[10];
TH1D *hist_HT_jets[10];
TH1D *hist_HT[10];
TH1D *hist_nJets[10]; 
TH1D *hist_nBtagJets[10];
TH1D *hist_MET[10];

vector<string> region_names={"0t 1b 4j", "0t 2b 4j","0t 1b 3j", "0t 2b 3j"};
//,
			     //"1t 1b 4j", "1t 2b 4j","1t 1b 3j", "1t 2b 3j"};

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
    {  "Preselections","Nleps","lepPt1>20","lepPt0>25","lepCentr","SS","jPt/eta","3j1b",
       "0t 1b 4j", "0t 2b 4j","0t 1b 3j", "0t 2b 3j"};
  int Ncuts = s_cutDescs.size();
  h_cutflow_2l[0] = new TH1F("cf2l","cf2l",Ncuts,0,Ncuts);
  h_cutflow_2l[1] = new TH1F("cf2l_raw","cf2l_raw",Ncuts,0,Ncuts);
  for (int bin=1;bin<=Ncuts;++bin){
    h_cutflow_2l[0]->GetXaxis()->SetBinLabel(bin,s_cutDescs[bin-1]);
    h_cutflow_2l[1]->GetXaxis()->SetBinLabel(bin,s_cutDescs[bin-1]);
  }


    Float_t ht_bins[]={0,120,180,240,300,360,440,540,680,900,1500}; Int_t  ht_binnum = sizeof(ht_bins)/sizeof(Float_t) - 1;
    Float_t ht_j_bins[]={0,90,140,180,240,300,380,460,540,650,850,1500}; Int_t  ht_j_binnum = sizeof(ht_j_bins)/sizeof(Float_t) - 1;
    Float_t met_bins[]={0,20,50,80,120,180,300,500,1200}; Int_t  met_binnum = sizeof(met_bins)/sizeof(Float_t) - 1;
    Float_t lep_bins[]={0,20,25,33,45,60,80,110,160,500}; Int_t  lep_binnum = sizeof(lep_bins)/sizeof(Float_t) - 1;
    Float_t dr_max=4.8; Int_t dr_bins=12; 
    for(int i=0; i<(int)region_names.size();i++){
      hist_DRll01[i] = new TH1D(("DRll01_"+to_string(i)).c_str(), ("#DeltaR_{l_{0},l_{1}} 2lSS"+region_names[i]+";#DeltaR_{l_{0},l_{1}};Events").c_str(), dr_bins, 0., dr_max);
      hist_lep_Pt_0[i] = new TH1D(("lep_Pt_0_"+to_string(i)).c_str(), ("Leading lepton Pt 2lSS"+region_names[i]+";p_{T}(l_{0})[GeV];Events").c_str(), lep_binnum, lep_bins);//100, 0, 500
      hist_lep_Pt_1[i] = new TH1D(("lep_Pt_1_"+to_string(i)).c_str(), ("Subleading lepton Pt 2lSS"+region_names[i]+";p_{T}(l_{1})[GeV];Events").c_str(),lep_binnum, lep_bins);
      hist_min_DRl0j[i] = new TH1D(("min_DRl0j_"+to_string(i)).c_str(), ("min #DeltaR_{l_{0},j} 2lSS"+region_names[i]+";min#DeltaR_{l_{0},j};Events").c_str(), dr_bins, 0., dr_max);
      hist_min_DRl1j[i] = new TH1D(("min_DRl1j_"+to_string(i)).c_str(), ("min #DeltaR_{l_{1},j} 2lSS"+region_names[i]+";min#DeltaR_{l_{1},j};Events").c_str(), dr_bins, 0., dr_max);
      hist_maxEta_ll[i] = new TH1D(("maxEta_ll_"+to_string(i)).c_str(), ("Max(#|{#eta}_{l}|) 2lSS"+region_names[i]+";Max(#|{#eta}_{l}|);Events").c_str(), 13, 0, 2.6); // maxEta = max( fabs( lep_Eta_0 ), fabs( lep_Eta_1 ) );
      hist_HT_jets[i] = new TH1D(("HT_jets_"+to_string(i)).c_str(), ( "H_{T}^{jets} 2lSS"+region_names[i]+";H_{T}^{jets}[GeV];Events").c_str(), ht_j_binnum, ht_j_bins);
      hist_HT[i] = new TH1D(("HT_"+to_string(i)).c_str(), ("H_{T}^{all} 2lSS"+region_names[i]+";H_{T}^{all}[GeV];Events").c_str(),ht_binnum, ht_bins);// 100, 0., 1000.
      hist_nJets[i] = new TH1D(("nJets_"+to_string(i)).c_str(),("N_{j} 2lSS"+region_names[i]+";N_{j};Events").c_str(), 7, 2.5, 9.5);
      hist_nBtagJets[i] = new TH1D(("nBtagJets_"+to_string(i)).c_str(),("N_{b} 2lSS"+region_names[i]+";N_{b};Events").c_str(), 3, 0.5, 3.5);
      hist_MET[i] = new TH1D(("MET_"+to_string(i)).c_str(),("MET 2lSS"+region_names[i]+";E_{T}^{miss}[GeV];Events").c_str(), met_binnum, met_bins);//100, 0., 1000.
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

  float l0_charge=0,l1_charge=0;  
  float l0_pt=-999,l1_pt=-999;
  float l0_eta=-999,l1_eta=-999;
  TLorentzVector lep_4v[2];

  if ( dilep_type==1 ){ 
    lep_4v[0].SetPtEtaPhiE(mu_pt[0]/1e3,mu_eta[0],mu_phi[0],mu_e[0]);
    lep_4v[1].SetPtEtaPhiE(mu_pt[1]/1e3,mu_eta[1],mu_phi[1],mu_e[1]);

    l0_charge= mu_charge[0]; l1_charge= mu_charge[1];
    l0_eta= mu_eta[0]; l1_eta= mu_eta[1];
    l0_pt= mu_pt[0]/1e3; l1_pt= mu_pt[1]/1e3;
  }
  else if ( dilep_type==3 ){ 
    lep_4v[0].SetPtEtaPhiE(el_pt[0]/1e3,el_eta[0],el_phi[0],el_e[0]);
    lep_4v[1].SetPtEtaPhiE(el_pt[1]/1e3,el_eta[1],el_phi[1],el_e[1]);

    l0_charge= el_charge[0]; l1_charge= el_charge[1];
    l0_eta= el_eta[0]; l1_eta= el_eta[1];
    l0_pt= el_pt[0]/1e3; l1_pt= el_pt[1]/1e3;
  }
  else if ( dilep_type==2 ){ 
    if(mu_pt[0]>el_pt[0]){ 
      lep_4v[0].SetPtEtaPhiE(mu_pt[0]/1e3,mu_eta[0],mu_phi[0],mu_e[0]);
      lep_4v[1].SetPtEtaPhiE(el_pt[0]/1e3,el_eta[0],el_phi[0],el_e[0]);

      l0_charge= mu_charge[0]; l1_charge= el_charge[0];
      l0_eta= mu_eta[0]; l1_eta= el_eta[0];
      l0_pt= mu_pt[0]/1e3; l1_pt= el_pt[0]/1e3;
    }
    else{    
      lep_4v[0].SetPtEtaPhiE(el_pt[0]/1e3,el_eta[0],el_phi[0],el_e[0]);
      lep_4v[1].SetPtEtaPhiE(mu_pt[0]/1e3,mu_eta[0],mu_phi[0],mu_e[0]);

      l1_charge= mu_charge[0]; l0_charge= el_charge[0];
      l1_eta= mu_eta[0]; l0_eta= el_eta[0];
      l1_pt= mu_pt[0]/1e3; l0_pt= el_pt[0]/1e3;
    }
  }


  int lead_lep=9999, sublead_lep=9999;
  if(  lep_4v[0].Pt()>lep_4v[1].Pt()){
    lead_lep=0;sublead_lep=1;}
  else {    lead_lep=1;sublead_lep=0;}
  
  //  if(lead_lep!=0)     cout <<  " 0  "<< lep_4v[0].Pt()<< "   1 " << lep_4v[1].Pt()<< ",  leading is "<< lead_lep<< endl;
  //if ((abs(lep_4v[lead_lep].Pt()-l0_pt)>0.0001) || (abs(lep_4v[sublead_lep].Pt()-l1_pt)>0.0001)) cout <<  " 0  "<< lep_4v[0].Pt()<< "   1 " << lep_4v[1].Pt()<< ",  leading is "<< lead_lep <<  ",  l0pt="<<l0_pt <<  ",  l1pt="<<l1_pt << endl;


  //lep Pt cuts
  if(lep_4v[sublead_lep].Pt()<20) return 0;  
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;
  if(lep_4v[lead_lep].Pt()<25) return 0;  
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;


  //lep eta cuts
  if(abs(lep_4v[lead_lep].Eta())>2.5||abs(lep_4v[sublead_lep].Eta())>2.5) return 0;  
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;

  float charges=l0_charge*l1_charge;
  //SS
  if(charges<0) return 0;
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;
 
  float max_eta=  max ( fabs( l0_eta ), fabs( l1_eta ) ); 

  int Njets=0, Nbjets=0;
  float HTall=0, HTjet=0; 
  vector<TLorentzVector> jets_vec;

  //loop over jet vectors
  for(unsigned int j=0;j<jet_pt.GetSize(); j++){
    if(jet_pt[j]/1000.<25) return 0;

    if(fabs(jet_eta[j])>2.5) return 0;
  
    Njets+=1;

    TLorentzVector jj;
    jj.SetPtEtaPhiE(jet_pt[j],jet_eta[j],jet_phi[j],jet_e[j]);
    jets_vec.push_back(jj);

    if(jet_nGhosts_bHadron[j]>0) Nbjets+=1;

    HTjet+=jet_pt[j];
    
  }
  //central jets above 25 gev
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;
  
  if(Njets<3 || Nbjets<1) return 0;
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;

  HTall=HTjet+(l0_pt+l1_pt)*1000;

  // DeltaRs
  // ll 
  float DRll01=-9999;
  //DRll01= sqrt( pow( (lep_4v[lead_lep].Eta()-lep_4v[sublead_lep].Eta()) ,2) + pow ( ( acos( cos( lep_4v[lead_lep].Phi()-lep_4v[sublead_lep].Phi() )  ) ) ,2) );
  DRll01=lep_4v[lead_lep].DeltaR( lep_4v[sublead_lep] ); // provide SAME results as "by hand"!!!
  //if (deltaR!=DRll01)   cout << DRll01 << ", dR "<< deltaR<< endl;
    //float  DR_LJ_0_tmp  = sqrt(pow((ntup.m_jet_eta->at(index_jets) - ntup.lep_Eta_0), 2.0) + pow((acos(cos(ntup.m_jet_phi->at(index_jets) - ntup.lep_Phi_0))), 2.0));
  
  // l-jet
  vector<float> dRl0j;  vector<float> dRl1j;
  for(int i=0; i<Njets;i++){
    dRl0j.push_back( lep_4v[lead_lep].DeltaR( jets_vec[i] ) );
    dRl1j.push_back( lep_4v[sublead_lep].DeltaR( jets_vec[i] ) );
  }
  
  float min_DRl0j=-9999, min_DRl1j=-9999;
  min_DRl0j= *min_element(dRl0j.begin(),dRl0j.end());
  min_DRl1j= *min_element(dRl1j.begin(),dRl1j.end());

  int Ntaus = 0; //in case we will process taus
  //2 same sign charged leptons (e,mu) with pT>25(20)GeV 
  sel_array[0]=(Ntaus == 0 && Nbjets == 1 && Njets >= 4 );  // Region 1 
  sel_array[1]=(Ntaus == 0 && Nbjets >= 2 && Njets >= 4 );  // Region 2
  sel_array[2]=(Ntaus == 0 && Nbjets == 1 && Njets == 3 );  // Region 3 
  sel_array[3]=(Ntaus == 0 && Nbjets >= 2 && Njets == 3 );  // Region 4

  float met = *met_met/1000.;

  for(int i=0; i<(int)region_names.size();i++){
    if(sel_array[i]){
      h_cutflow_2l[0]->Fill(cf_counter+i,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter+i,1);
      
      hist_DRll01[i]->Fill(DRll01, weight_tot);
      hist_lep_Pt_0[i]->Fill(l0_pt, weight_tot);
      hist_lep_Pt_1[i]->Fill(l1_pt, weight_tot);
      hist_min_DRl0j[i]->Fill(min_DRl0j, weight_tot);
      hist_min_DRl1j[i]->Fill(min_DRl1j, weight_tot);
      hist_maxEta_ll[i]->Fill(max_eta, weight_tot);
      hist_HT_jets[i]->Fill(HTjet/1000, weight_tot);
      hist_HT[i]->Fill(HTall/1000, weight_tot);
      hist_nJets[i]->Fill(Njets, weight_tot);
      hist_nBtagJets[i]->Fill(Nbjets, weight_tot);
      hist_MET[i]->Fill(met, weight_tot);
      

    }
  }
  
  
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

  for(int i=0; i<(int)region_names.size();i++){
    hist_DRll01[i]->Write();
    hist_lep_Pt_0[i]->Write();
    hist_lep_Pt_1[i]->Write();
    hist_min_DRl0j[i]->Write();
    hist_min_DRl1j[i]->Write();
    hist_maxEta_ll[i]->Write();
    hist_HT_jets[i]->Write();
    hist_HT[i]->Write();
    hist_nJets[i]->Write();
    hist_nBtagJets[i]->Write();
    hist_MET[i]->Write();
  }

  fOutput->Write();

  
}
