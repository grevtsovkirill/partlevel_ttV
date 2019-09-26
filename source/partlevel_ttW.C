#define partlevel_ttW_cxx


#include "partlevel_ttW.h"
#include <TH2.h>
#include <TStyle.h>
#include <TLorentzVector.h>
#include <math.h>

TH1F *h_cutflow_2l[2];
string input_name="";
string input_option="";
/////////////////////////////
// Histograms booking 2lSS ttW:
////////////////////////////
TH1D *hist_DRll01[10];
TH1D *hist_jet_Pt_4[10];
TH1D *hist_jet_Pt_5[10];
TH1D *hist_jet_Pt_6[10];
TH1D *hist_Bjet_Pt_0[10];
TH1D *hist_Bjet_Pt_1[10];
TH1D *hist_lep_Pt_0[10];
TH1D *hist_lep_Pt_1[10];
TH1D *hist_min_DRl0j[10];
TH1D *hist_min_DRl1j[10];
TH1D *hist_maxEta_ll[10];
TH1D *hist_HT_jets[10];
TH1D *hist_HT_leps[10];
TH1D *hist_HT[10];
TH1D *hist_nJets[10]; 
TH1D *hist_nBtagJets[10];
TH1D *hist_MET[10];
//
TH1D *hist_lep_Eta_0[10];
TH1D *hist_lep_Eta_1[10];
TH1D *hist_lep_Phi_0[10];
TH1D *hist_lep_Phi_1[10];

TH1D *hist_lep_dPhi[10];

TH1D *hist_Weights[10];

/*
 *        0 *        4 *          MUR05_MUF05_PDF261000 *
 *        0 *        5 *           MUR05_MUF1_PDF261000 *
 *        0 *        6 *           MUR1_MUF05_PDF261000 *
 *        0 *        7 *            MUR1_MUF1_PDF261000 *
 *        0 *        8 *            MUR1_MUF2_PDF261000 *
 *        0 *        9 *            MUR2_MUF1_PDF261000 *
 *        0 *       10 *            MUR2_MUF2_PDF261000 *

*/

vector<string> weight_names = {"MUR05_MUF05","MUR05_MUF1","MUR1_MUF05","MUR1_MUF1","MUR1_MUF2","MUR2_MUF1","MUR2_MUF2"};



 
vector<string> region_names={"0t 1b 4j", "0t 2b 4j","0t 1b 3j", "0t 2b 3j","1t 1b 3j"};
//,
			     //"1t 1b 4j", "1t 2b 4j","1t 1b 3j", "1t 2b 3j"};

void partlevel_ttW::Begin(TTree * /*tree*/)
{
  TString option = GetOption();
}

void partlevel_ttW::ReadOpt(double sumweights, int var_type)
{
  double inval1 = sumweights;
  int inval2 = var_type;
  std::cout<< "i'm in the ReadOpt function -  "<<inval1<< " " <<inval2 << std::endl;      
}

void partlevel_ttW::SlaveBegin(TTree * /*tree*/)
{
  stoploop=false;
  nomS_w=false; nomM_w=false; scaleupS_w=false;  scaledownS_w=false;    scaleupM_w=false;  scaledownM_w=false;    
  TString option = GetOption();
  std::cout << "option ="<< option << std::endl;
  input_option = option;
  string tmp = input_option.substr(0,input_option.find("_"));
  double smw=-9999;
  smw=  std::stod (tmp);
  //cout.precision(17);
  std::cout << "SumW ="<< tmp<< ", double - "<< smw << std::endl;
  //1 / (sum of weights per variation)
  // xs from ami , 
  // sherpa 413008: 652 fb;  7446700.5
  // MG 410155: 548 fb ;  4111925.0
  Acc=1/smw;
  


  input_name=input_option.substr(input_option.find("_")+1);

  std::cout << "variation =";
  if(input_name.compare("Sherpa")==0){
    std::cout << " nominal Sherpa"<<  std::endl;
    nomS_w=true;
  }
  else if(input_name.compare("MG")==0){
    std::cout << " nominal MG"<<  std::endl;
    nomM_w=true;
  }
  else if (input_name.find("SherpaScaleUp")!= std::string::npos){
    std::cout << " ScaleUp"<<  std::endl;
    scaleupS_w=true;
  }
  else if (input_name.find("SherpaScaleDown")!= std::string::npos){
    std::cout << " ScaleDown"<<  std::endl;
    scaledownS_w=true;
  }  else if (input_name.find("MGScaleUp")!= std::string::npos){
    std::cout << " ScaleUp"<<  std::endl;
    scaleupM_w=true;
  }
  else if (input_name.find("MGScaleDown")!= std::string::npos){
    std::cout << " ScaleDown"<<  std::endl;
    scaledownM_w=true;
  }
  else {std::cout << " error - incorrect variation. Stop."<<  std::endl; stoploop=true;}


  
  const std::vector<TString> s_cutDescs =
    {  "Preselections","Nleps","lepPt1>20","lepPt0>25","lepCentr","SS","jPt/eta","3j1b",
       "0t 1b 4j", "0t 2b 4j","0t 1b 3j", "0t 2b 3j","1t >1b >3j"};
  int Ncuts = s_cutDescs.size();
  h_cutflow_2l[0] = new TH1F("cf2l","cf2l",Ncuts,0,Ncuts);
  h_cutflow_2l[1] = new TH1F("cf2l_raw","cf2l_raw",Ncuts,0,Ncuts);
  for (int bin=1;bin<=Ncuts;++bin){
    h_cutflow_2l[0]->GetXaxis()->SetBinLabel(bin,s_cutDescs[bin-1]);
    h_cutflow_2l[1]->GetXaxis()->SetBinLabel(bin,s_cutDescs[bin-1]);
  }


    Float_t ht_bins[]={0,120,180,240,300,360,440,540,680,900,1500}; Int_t  ht_binnum = sizeof(ht_bins)/sizeof(Float_t) - 1;
    Float_t ht_j_bins[]={0,90,140,180,240,300,380,460,540,650,850,1500}; Int_t  ht_j_binnum = sizeof(ht_j_bins)/sizeof(Float_t) - 1;
    Float_t ht_l_bins[]={0,20,50,80,110,150,200,300,400,550,800}; Int_t  ht_l_binnum = sizeof(ht_l_bins)/sizeof(Float_t) - 1;
    Float_t met_bins[]={0,20,50,80,120,180,300,500,1200}; Int_t  met_binnum = sizeof(met_bins)/sizeof(Float_t) - 1;
    Float_t lep_bins[]={0,20,25,33,45,60,80,110,160,500}; Int_t  lep_binnum = sizeof(lep_bins)/sizeof(Float_t) - 1;
    Float_t jet_bins[]={0,20,25,33,45,60,80,110,200}; Int_t  jet_binnum = sizeof(jet_bins)/sizeof(Float_t) - 1;
    Float_t bjet_bins[]={0,20,25,33,45,60,80,110,150,200,300,500}; Int_t  bjet_binnum = sizeof(bjet_bins)/sizeof(Float_t) - 1;
    Float_t dr_max=4.8; Int_t dr_bins=12; 
    for(int i=0; i<(int)region_names.size();i++){
      hist_DRll01[i] = new TH1D(("DRll01_"+to_string(i)).c_str(), ("#DeltaR_{l_{0},l_{1}} 2lSS"+region_names[i]+";#DeltaR_{l_{0},l_{1}};Events").c_str(), dr_bins, 0., dr_max);
      hist_lep_Pt_0[i] = new TH1D(("lep_Pt_0_"+to_string(i)).c_str(), ("Leading lepton Pt 2lSS"+region_names[i]+";p_{T}(l_{0})[GeV];Events").c_str(), lep_binnum, lep_bins);//100, 0, 500
      hist_lep_Pt_1[i] = new TH1D(("lep_Pt_1_"+to_string(i)).c_str(), ("Subleading lepton Pt 2lSS"+region_names[i]+";p_{T}(l_{1})[GeV];Events").c_str(),lep_binnum, lep_bins);
      //jets:
      hist_jet_Pt_4[i] = new TH1D(("jet_Pt_4_"+to_string(i)).c_str(), ("4th jet Pt 2lSS"+region_names[i]+";p_{T}(j_{4})[GeV];Events").c_str(),jet_binnum, jet_bins);
      hist_jet_Pt_5[i] = new TH1D(("jet_Pt_5_"+to_string(i)).c_str(), ("5th jet Pt 2lSS"+region_names[i]+";p_{T}(j_{5})[GeV];Events").c_str(),jet_binnum, jet_bins);
      hist_jet_Pt_6[i] = new TH1D(("jet_Pt_6_"+to_string(i)).c_str(), ("6th jet Pt 2lSS"+region_names[i]+";p_{T}(j_{6})[GeV];Events").c_str(),jet_binnum, jet_bins);
      //bjets
      hist_Bjet_Pt_0[i] = new TH1D(("Bjet_Pt_0_"+to_string(i)).c_str(), ("Lead Bjet Pt 2lSS"+region_names[i]+";p_{T}(bj_{0})[GeV];Events").c_str(),bjet_binnum, bjet_bins);
      hist_Bjet_Pt_1[i] = new TH1D(("Bjet_Pt_1_"+to_string(i)).c_str(), ("Sublead Bjet Pt 2lSS"+region_names[i]+";p_{T}(bj_{1})[GeV];Events").c_str(),jet_binnum, jet_bins);

      hist_min_DRl0j[i] = new TH1D(("min_DRl0j_"+to_string(i)).c_str(), ("min #DeltaR_{l_{0},j} 2lSS"+region_names[i]+";min#DeltaR_{l_{0},j};Events").c_str(), dr_bins, 0., dr_max);
      hist_min_DRl1j[i] = new TH1D(("min_DRl1j_"+to_string(i)).c_str(), ("min #DeltaR_{l_{1},j} 2lSS"+region_names[i]+";min#DeltaR_{l_{1},j};Events").c_str(), dr_bins, 0., dr_max);
      hist_maxEta_ll[i] = new TH1D(("maxEta_ll_"+to_string(i)).c_str(), ("Max(#|{#eta}_{l}|) 2lSS"+region_names[i]+";Max(#|{#eta}_{l}|);Events").c_str(), 13, 0, 2.6); // maxEta = max( fabs( lep_Eta_0 ), fabs( lep_Eta_1 ) );
      hist_HT_jets[i] = new TH1D(("HT_jets_"+to_string(i)).c_str(), ( "H_{T}^{jets} 2lSS"+region_names[i]+";H_{T}^{jets}[GeV];Events").c_str(), ht_j_binnum, ht_j_bins);
      hist_HT_leps[i] = new TH1D(("HT_leps_"+to_string(i)).c_str(), ( "H_{T}^{leps} 2lSS"+region_names[i]+";H_{T}^{leps}[GeV];Events").c_str(), ht_l_binnum, ht_l_bins);
      hist_HT[i] = new TH1D(("HT_"+to_string(i)).c_str(), ("H_{T}^{all} 2lSS"+region_names[i]+";H_{T}^{all}[GeV];Events").c_str(),ht_binnum, ht_bins);// 100, 0., 1000.
      hist_nJets[i] = new TH1D(("nJets_"+to_string(i)).c_str(),("N_{j} 2lSS"+region_names[i]+";N_{j};Events").c_str(), 7, 2.5, 9.5);
      hist_nBtagJets[i] = new TH1D(("nBtagJets_"+to_string(i)).c_str(),("N_{b} 2lSS"+region_names[i]+";N_{b};Events").c_str(), 3, 0.5, 3.5);
      hist_MET[i] = new TH1D(("MET_"+to_string(i)).c_str(),("MET 2lSS"+region_names[i]+";E_{T}^{miss}[GeV];Events").c_str(), met_binnum, met_bins);//100, 0., 1000.
      //
      hist_lep_Eta_0[i] = new TH1D(("lep_Eta_0_"+to_string(i)).c_str(), ("#{#eta}_{l0}} 2lSS"+region_names[i]+";#{#eta}_{l0};Events").c_str(), 13, -2.6, 2.6);
      hist_lep_Eta_1[i] = new TH1D(("lep_Eta_1_"+to_string(i)).c_str(), ("#{#eta}_{l1}} 2lSS"+region_names[i]+";#{#eta}_{l1};Events").c_str(), 13, -2.6, 2.6);
      hist_lep_Phi_0[i] = new TH1D(("lep_Phi_0_"+to_string(i)).c_str(), ("#{#phi}_{l0}} 2lSS"+region_names[i]+";#{#phi}_{l0};Events").c_str(), 16, -3.2, 3.2);
      hist_lep_Phi_1[i] = new TH1D(("lep_Phi_1_"+to_string(i)).c_str(), ("#{#phi}_{l1}} 2lSS"+region_names[i]+";#{#phi}_{l1};Events").c_str(), 16, -3.2, 3.2);
      hist_lep_dPhi[i] = new TH1D(("lep_dPhi_"+to_string(i)).c_str(), ("#Delta#{#phi}_{ll}} 2lSS"+region_names[i]+";#{#Delta#phi}_{ll};Events").c_str(), 8, 0, 3.2);

    }


    //(int)weight_names.size()
    for(int i=0; i<(int)weight_names.size();i++){
      hist_Weights[i] = new TH1D( (weight_names[i]).c_str(), (weight_names[i]+";weight;Events").c_str(), 300, -4, 4);
    }  
}

Bool_t partlevel_ttW::Process(Long64_t entry)
{
  if(stoploop) return 0;
  //fReader.SetEntry(entry);
  fReader.SetLocalEntry(entry);
  // print some information about the current entry
  if ((entry)%10000 == 0)
    printf("Processing Entry  %llu \n", entry);

  // increase the total number of entries
  ++fNumberOfEvents;

  //weight definitions
  Double_t weight_to_use=1;

  if (nomS_w) weight_to_use = *weight_mc *Acc ;
  else if (nomM_w) weight_to_use = *weight_mc *Acc;
  else if (scaleupS_w) weight_to_use = mc_generator_weights[10]  *Acc ;//10 *            MUR2_MUF2_PDF261000 *
  else if (scaledownS_w) weight_to_use = mc_generator_weights[4] *Acc ;//4 *          MUR05_MUF05_PDF261000 *
  else if (scaleupM_w) weight_to_use = mc_generator_weights[4] *Acc; //4 *   muR=020000E+01muF=020000E+01
  else if (scaledownM_w) weight_to_use = mc_generator_weights[8] *Acc;//8 *   muR=050000E+00muF=050000E+00
  else return 0;

  double shift=0;
  double shift2=0;
  //  you have to compute the relative uncertainty using the 30 eigenvectors (index xxx01-xxx30) wrt. the PDF4LHC15 nominal (index xxx00). 
  // The additional 2 variations (index xxx31 and xxx32) are an alphaS variation, which I'm not sure you have to use (it depends what you want to compute I guess).
  double pdf_var_up=1,pdf_var_down=1;

  for (int i=1; i<31;i++){
    shift2+=pow((PDF4LHC15_nnlo_30_pdfas[i]-PDF4LHC15_nnlo_30_pdfas[0]),2);
  }
  shift=sqrt(shift2);
  pdf_var_up=(PDF4LHC15_nnlo_30_pdfas[0]+shift)/PDF4LHC15_nnlo_30_pdfas[0];
  pdf_var_down=(PDF4LHC15_nnlo_30_pdfas[0]-shift)/PDF4LHC15_nnlo_30_pdfas[0];
  
  // access names of the weights:
  // sumWeights->Scan("names_mc_generator_weights","","colsize=30")
  // check values:
  //
  weight_tot=weight_to_use * *weight_pileup ;
  // by hand PDF uncertainties
  //* pdf_var_up
  //* pdf_var_down

  if (entry==0) cout<< "PDF4LHC15_nnlo_30_pdfas [0] = " << PDF4LHC15_nnlo_30_pdfas[0]<<" [1] = " << PDF4LHC15_nnlo_30_pdfas[1]<<endl;


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
  vector<TLorentzVector> bjets_vec;

  //loop over jet vectors
  int lowjets=0;
  for(unsigned int j=0;j<jet_pt.GetSize(); j++){
    if(jet_pt[j]/1000.<25){
      lowjets++;
      return 0;
      cout <<lowjets<< endl;
    }

    if(fabs(jet_eta[j])>2.5) return 0;
  
    Njets+=1;

    TLorentzVector jj;
    jj.SetPtEtaPhiE(jet_pt[j],jet_eta[j],jet_phi[j],jet_e[j]);
    jets_vec.push_back(jj);

    if(jet_nGhosts_bHadron[j]>0){
      Nbjets+=1;
      bjets_vec.push_back(jj);
    }

    HTjet+=jet_pt[j];
    
  }
  if(lowjets>0) return 0;
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
  int Nhtaus = 0;
  for(unsigned int t=0;t<tau_pt.GetSize(); t++){
    if(tau_pt[t]/1000.<25) return 0;

    if(fabs(tau_eta[t])>2.5) return 0;
  
    Ntaus+=1;
    if(tau_isHadronic[t]!=0) Nhtaus+=1;
  }


  //fill weights
  for(int i=0; i<(int)weight_names.size();i++){
    hist_Weights[i]->Fill(mc_generator_weights[i+4]);
  }  



  //cout <<"Ntaus ="<<Ntaus<<", Nhtaus="<< Nhtaus   << endl;
  //2 same sign charged leptons (e,mu) with pT>25(20)GeV 
  sel_array[0]=(Nhtaus == 0 && Nbjets == 1 && Njets >= 4 );  // Region 1 
  sel_array[1]=(Nhtaus == 0 && Nbjets >= 2 && Njets >= 4 );  // Region 2
  sel_array[2]=(Nhtaus == 0 && Nbjets == 1 && Njets == 3 );  // Region 3 
  sel_array[3]=(Nhtaus == 0 && Nbjets >= 2 && Njets == 3 );  // Region 4
  sel_array[4]=(Nhtaus == 1 && Nbjets >= 1 && Njets >= 3 );  // Region 5

  float met = *met_met/1000.;

  for(int i=0; i<(int)region_names.size();i++){
    if(sel_array[i]){
      h_cutflow_2l[0]->Fill(cf_counter+i,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter+i,1);
      
      hist_DRll01[i]->Fill(DRll01, weight_tot);
      hist_lep_Pt_0[i]->Fill(l0_pt, weight_tot);
      hist_lep_Pt_1[i]->Fill(l1_pt, weight_tot);
      if(Njets >= 4){
	hist_jet_Pt_4[i]->Fill(jets_vec[3].Pt()/1e3, weight_tot);
	if(Njets >= 5) hist_jet_Pt_5[i]->Fill(jets_vec[4].Pt()/1e3, weight_tot);
	if(Njets >= 6) hist_jet_Pt_6[i]->Fill(jets_vec[5].Pt()/1e3, weight_tot);
      }
      hist_Bjet_Pt_0[i]->Fill(bjets_vec[0].Pt()/1e3, weight_tot);
      if(Nbjets > 1){
	hist_Bjet_Pt_1[i]->Fill(bjets_vec[1].Pt()/1e3, weight_tot);
      }

      hist_min_DRl0j[i]->Fill(min_DRl0j, weight_tot);
      hist_min_DRl1j[i]->Fill(min_DRl1j, weight_tot);
      hist_maxEta_ll[i]->Fill(max_eta, weight_tot);
      hist_HT_jets[i]->Fill(HTjet/1000, weight_tot);
      hist_HT_leps[i]->Fill((l0_pt+l1_pt), weight_tot);
      hist_HT[i]->Fill(HTall/1000, weight_tot);
      hist_nJets[i]->Fill(Njets, weight_tot);
      hist_nBtagJets[i]->Fill(Nbjets, weight_tot);
      hist_MET[i]->Fill(met, weight_tot);
      
      hist_lep_Eta_0[i]->Fill(lep_4v[lead_lep].Eta(), weight_tot);
      hist_lep_Eta_1[i]->Fill(lep_4v[sublead_lep].Eta(), weight_tot);
      hist_lep_Phi_0[i]->Fill(lep_4v[lead_lep].Phi(), weight_tot);
      hist_lep_Phi_1[i]->Fill(lep_4v[sublead_lep].Phi(), weight_tot);
      hist_lep_dPhi[i]->Fill(abs(lep_4v[lead_lep].Phi()-lep_4v[sublead_lep].Phi()), weight_tot);
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

  if(!stoploop){
    string outname="Res_"+input_name+".root";
    TFile hfile(outname.c_str(),"RECREATE"); //,"tHq"
    //*
    h_cutflow_2l[0]->Write(); 
    h_cutflow_2l[1]->Write(); 
    
    for(int i=0; i<(int)region_names.size();i++){
      hist_DRll01[i]->Write();
      hist_lep_Pt_0[i]->Write();
      hist_lep_Pt_1[i]->Write();
      hist_jet_Pt_4[i]->Write();
      hist_jet_Pt_5[i]->Write();
      hist_jet_Pt_6[i]->Write();
      hist_Bjet_Pt_0[i]->Write();
      hist_Bjet_Pt_1[i]->Write();
      hist_min_DRl0j[i]->Write();
      hist_min_DRl1j[i]->Write();
      hist_maxEta_ll[i]->Write();
      hist_HT_jets[i]->Write();
      hist_HT_leps[i]->Write();
      hist_HT[i]->Write();
      hist_nJets[i]->Write();
      hist_nBtagJets[i]->Write();
      hist_MET[i]->Write();
      //      
      hist_lep_Eta_0[i]->Write();
      hist_lep_Eta_1[i]->Write();
      hist_lep_Phi_0[i]->Write();
      hist_lep_Phi_1[i]->Write();
      hist_lep_dPhi[i]->Write();
    }
    //*/

    /*
    for(int i=0; i<(int)weight_names.size();i++){
      hist_Weights[i]->Write();
    }  
    //*/

    fOutput->Write();
  }
  
}
