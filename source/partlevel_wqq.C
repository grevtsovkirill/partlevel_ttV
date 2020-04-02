#define partlevel_wqq_cxx


#include "partlevel_wqq.h"
#include <TH2.h>
#include <TStyle.h>
#include <TLorentzVector.h>
#include <math.h>
#include <map>

TH1F *h_cutflow_2l[2];
string input_name="";
string input_option="";
string comp_name="";
/////////////////////////////
// Histograms booking 2lOS ttW:
////////////////////////////
TH1D *hist_DRll01[10];
TH1D *hist_jet_Pt_1[10];
TH1D *hist_jet_Pt_2[10];
TH1D *hist_jet_Pt_3[10];
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
TH1D *hist_min_DRlb[10][5];

TH1D *hist_Weights[10];
TH1D *hist_Whmass[10];
TH1D *hist_Whpt[10];
TH1D *hist_lep_truth_origin[10];
TH1D *hist_lep_truth_origin_0[10];
TH1D *hist_lep_truth_origin_1[10];

TH1D *hist_lep_truth_type[10];
TH1D *hist_lep_truth_type_0[10];
TH1D *hist_lep_truth_type_1[10];

TH1D *hist_jet_truth_origin[10];
TH1D *hist_jet_truth_type[10];
TH1D *hist_jet0_truth_origin[10];
TH1D *hist_jet0_truth_type[10];
TH1D *hist_jet1_truth_origin[10];
TH1D *hist_jet1_truth_type[10];

TH2D *hist_mqq_jet_truth_origin[10];
TH2D *hist_mqqP_jet_truth_origin[10];
TH2D *hist_mqq_jet_truth_type[10];
TH2D *hist_mqqP_jet_truth_type[10];

vector<string> weight_names = {"MUR05_MUF05","MUR05_MUF1","MUR1_MUF05","MUR1_MUF1","MUR1_MUF2","MUR2_MUF1","MUR2_MUF2"};
 
vector<string> region_names={"2b4j", ">0cjet","Wwidnow","Wwidnow>0cjet"};
void partlevel_wqq::Begin(TTree * /*tree*/)
{
  TString option = GetOption();
}

void partlevel_wqq::ReadOpt(double sumweights, int var_type)
{
  double inval1 = sumweights;
  int inval2 = var_type;
  std::cout<< "i'm in the ReadOpt function -  "<<inval1<< " " <<inval2 << std::endl;      
}

void partlevel_wqq::SlaveBegin(TTree * /*tree*/)
{
  stoploop=false;
  nomS_w=false; nomM_w=false; scaleupS_w=false;  scaledownS_w=false;    scaleupM_w=false;  scaledownM_w=false;    
  TString option = GetOption();
  std::cout << "option ="<< option << std::endl;
  input_option = option;
  string tmp = input_option.substr(0,input_option.find("/"));
  double smw=-9999;
  smw=  std::stod (tmp);
  //cout.precision(17);
  std::cout << "SumW ="<< tmp<< ", double - "<< smw << std::endl;

  input_name=input_option.substr(input_option.find("/")+1,(input_option.find("_")-input_option.find("/")-1));
  comp_name=input_option.substr(input_option.find("-")+1);

  std::map<std::string, double> xs_map;
  
  xs_map["413008"]= 0.652 * 0.920 ;
  xs_map["410157"]= 0.52771 * 1.11 ;
  xs_map["410156"]= 0.15499 * 1.11;
  xs_map["410155"]= 0.54830 * 1.10;
  xs_map["410218"]= 0.036888 * 1.12 ;
  xs_map["410219"]= 0.036895 * 1.12 ;
  xs_map["410220"]= 0.036599 * 1.12 ;
  xs_map["410472"]= 76.95 * 1.1398;
  xs_map["410470"]= 396.87 * 1.1398;       
  xs_map["410658"]= 36.993 * 1.191;
  xs_map["410659"]= 22.175 * 1.183;
  xs_map["410644"]= 2.0268 * 1.015 ;
  xs_map["410645"]= 1.2676 * 1.015;
  xs_map["304014"]= 0.0016398 * 1.0;
  xs_map["410080"]= 0.0091622 * 1.0042 ;
  xs_map["410081"]= 0.0080975 * 1.2231 ;
  xs_map["410408"]= 0.016046 * 1.0 ;


  std::cout << "input_name ="<< input_name<< ", comp_name - "<< comp_name<< ", xs = "<<xs_map[input_name] << std::endl;  
  Double_t gen_xs=1;
  gen_xs=xs_map[input_name];
  Acc=gen_xs*1e3/smw;
  //Acc=1/smw;
  
  const std::vector<TString> s_cutDescs =
    {  "Preselections","Nleps","lepPt1>20","lepPt0>25","lepCentr","OS","jPt/eta","2b","4j",
       "Whad", "4j2b",">0cj"};//"w>20","w>10","w>5"
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
    //Float_t w_bins[]={0,10,20,25,33,45,60,80,110,140,180,240,400}; Int_t  w_binnum = sizeof(w_bins)/sizeof(Float_t) - 1;
    Float_t dr_max=4.8; Int_t dr_bins=12;
    Float_t origin_bins = 48;
    for(int i=0; i<(int)region_names.size();i++){
      hist_DRll01[i] = new TH1D(("DRll01_"+to_string(i)).c_str(), ("#DeltaR_{l_{0},l_{1}} 2lOS"+region_names[i]+";#DeltaR_{l_{0},l_{1}};Events").c_str(), dr_bins, 0., dr_max);
      hist_lep_Pt_0[i] = new TH1D(("lep_Pt_0_"+to_string(i)).c_str(), ("Leading lepton Pt 2lOS"+region_names[i]+";p_{T}(l_{0})[GeV];Events").c_str(), lep_binnum, lep_bins);//100, 0, 500
      hist_lep_Pt_1[i] = new TH1D(("lep_Pt_1_"+to_string(i)).c_str(), ("Subleading lepton Pt 2lOS"+region_names[i]+";p_{T}(l_{1})[GeV];Events").c_str(),lep_binnum, lep_bins);
      //jets:
      hist_jet_Pt_1[i] = new TH1D(("jet_Pt_1_"+to_string(i)).c_str(), ("1th jet Pt 2lOS"+region_names[i]+";p_{T}(j_{1})[GeV];Events").c_str(),jet_binnum, jet_bins);
      hist_jet_Pt_2[i] = new TH1D(("jet_Pt_2_"+to_string(i)).c_str(), ("2th jet Pt 2lOS"+region_names[i]+";p_{T}(j_{2})[GeV];Events").c_str(),jet_binnum, jet_bins);
      hist_jet_Pt_3[i] = new TH1D(("jet_Pt_3_"+to_string(i)).c_str(), ("3th jet Pt 2lOS"+region_names[i]+";p_{T}(j_{3})[GeV];Events").c_str(),jet_binnum, jet_bins);
      hist_jet_Pt_4[i] = new TH1D(("jet_Pt_4_"+to_string(i)).c_str(), ("4th jet Pt 2lOS"+region_names[i]+";p_{T}(j_{4})[GeV];Events").c_str(),jet_binnum, jet_bins);
      hist_jet_Pt_5[i] = new TH1D(("jet_Pt_5_"+to_string(i)).c_str(), ("5th jet Pt 2lOS"+region_names[i]+";p_{T}(j_{5})[GeV];Events").c_str(),jet_binnum, jet_bins);
      hist_jet_Pt_6[i] = new TH1D(("jet_Pt_6_"+to_string(i)).c_str(), ("6th jet Pt 2lOS"+region_names[i]+";p_{T}(j_{6})[GeV];Events").c_str(),jet_binnum, jet_bins);
      //bjets
      hist_Bjet_Pt_0[i] = new TH1D(("Bjet_Pt_0_"+to_string(i)).c_str(), ("Lead Bjet Pt 2lOS"+region_names[i]+";p_{T}(bj_{0})[GeV];Events").c_str(),bjet_binnum, bjet_bins);
      hist_Bjet_Pt_1[i] = new TH1D(("Bjet_Pt_1_"+to_string(i)).c_str(), ("Sublead Bjet Pt 2lOS"+region_names[i]+";p_{T}(bj_{1})[GeV];Events").c_str(),jet_binnum, jet_bins);

      hist_min_DRl0j[i] = new TH1D(("min_DRl0j_"+to_string(i)).c_str(), ("min #DeltaR_{l_{0},j} 2lOS"+region_names[i]+";min#DeltaR_{l_{0},j};Events").c_str(), dr_bins, 0., dr_max);
      hist_min_DRl1j[i] = new TH1D(("min_DRl1j_"+to_string(i)).c_str(), ("min #DeltaR_{l_{1},j} 2lOS"+region_names[i]+";min#DeltaR_{l_{1},j};Events").c_str(), dr_bins, 0., dr_max);
      hist_maxEta_ll[i] = new TH1D(("maxEta_ll_"+to_string(i)).c_str(), ("Max(#|{#eta}_{l}|) 2lOS"+region_names[i]+";Max(#|{#eta}_{l}|);Events").c_str(), 13, 0, 2.6); // maxEta = max( fabs( lep_Eta_0 ), fabs( lep_Eta_1 ) );
      hist_HT_jets[i] = new TH1D(("HT_jets_"+to_string(i)).c_str(), ( "H_{T}^{jets} 2lOS"+region_names[i]+";H_{T}^{jets}[GeV];Events").c_str(), ht_j_binnum, ht_j_bins);
      hist_HT_leps[i] = new TH1D(("HT_leps_"+to_string(i)).c_str(), ( "H_{T}^{leps} 2lOS"+region_names[i]+";H_{T}^{leps}[GeV];Events").c_str(), ht_l_binnum, ht_l_bins);
      hist_HT[i] = new TH1D(("HT_"+to_string(i)).c_str(), ("H_{T}^{all} 2lOS"+region_names[i]+";H_{T}^{all}[GeV];Events").c_str(),ht_binnum, ht_bins);// 100, 0., 1000.
      hist_nJets[i] = new TH1D(("nJets_"+to_string(i)).c_str(),("N_{j} 2lOS"+region_names[i]+";N_{j};Events").c_str(), 7, 2.5, 9.5);
      hist_nBtagJets[i] = new TH1D(("nBtagJets_"+to_string(i)).c_str(),("N_{b} 2lOS"+region_names[i]+";N_{b};Events").c_str(), 3, 0.5, 3.5);
      hist_MET[i] = new TH1D(("MET_"+to_string(i)).c_str(),("MET 2lOS"+region_names[i]+";E_{T}^{miss}[GeV];Events").c_str(), met_binnum, met_bins);//100, 0., 1000.
      //
      hist_lep_Eta_0[i] = new TH1D(("lep_Eta_0_"+to_string(i)).c_str(), ("#{#eta}_{l0}} 2lOS"+region_names[i]+";#{#eta}_{l0};Events").c_str(), 13, -2.6, 2.6);
      hist_lep_Eta_1[i] = new TH1D(("lep_Eta_1_"+to_string(i)).c_str(), ("#{#eta}_{l1}} 2lOS"+region_names[i]+";#{#eta}_{l1};Events").c_str(), 13, -2.6, 2.6);
      hist_lep_Phi_0[i] = new TH1D(("lep_Phi_0_"+to_string(i)).c_str(), ("#{#phi}_{l0}} 2lOS"+region_names[i]+";#{#phi}_{l0};Events").c_str(), 16, -3.2, 3.2);
      hist_lep_Phi_1[i] = new TH1D(("lep_Phi_1_"+to_string(i)).c_str(), ("#{#phi}_{l1}} 2lOS"+region_names[i]+";#{#phi}_{l1};Events").c_str(), 16, -3.2, 3.2);
      hist_lep_dPhi[i] = new TH1D(("lep_dPhi_"+to_string(i)).c_str(), ("|#Delta#{#phi}_{ll}}| 2lOS"+region_names[i]+";|#{#Delta#phi}_{ll}|;Events").c_str(), 16, 0, 6.4);

      hist_Whmass[i] = new TH1D(("Whmass_"+to_string(i)).c_str(), ("m_{Wqq} "+region_names[i]+";m_{Wqq};Events").c_str(), 50, 50, 150); //420, 50, 410
      hist_Whpt[i] = new TH1D(("Whpt_"+to_string(i)).c_str(), ("p_T^{Wqq} "+region_names[i]+";p_T^{Wqq};Events").c_str(),60,0,300 ); //w_binnum, w_bins

      hist_lep_truth_origin[i] = new TH1D(("leps_tr_origin_"+to_string(i)).c_str(), ("Origins 2lOS"+region_names[i]+";Origin;Events").c_str(), origin_bins, 0, origin_bins);
      hist_lep_truth_origin_0[i] = new TH1D(("lep0_tr_origin_"+to_string(i)).c_str(), ("L0 Origin 2lOS"+region_names[i]+";l0 Origin;Events").c_str(), origin_bins, 0, origin_bins);
      hist_lep_truth_origin_1[i] = new TH1D(("lep1_tr_origin_"+to_string(i)).c_str(), ("L1 Origin 2lOS"+region_names[i]+";l1 Origin;Events").c_str(), origin_bins, 0, origin_bins);

      hist_lep_truth_type[i] = new TH1D(("leps_tr_type_"+to_string(i)).c_str(), ("Types 2lOS"+region_names[i]+";Type;Events").c_str(), origin_bins, 0, origin_bins);
      hist_lep_truth_type_0[i] = new TH1D(("lep0_tr_type_"+to_string(i)).c_str(), ("L0 Type 2lOS"+region_names[i]+";l0 Type;Events").c_str(), origin_bins, 0, origin_bins);
      hist_lep_truth_type_1[i] = new TH1D(("lep1_tr_type_"+to_string(i)).c_str(), ("L1 Type 2lOS"+region_names[i]+";l1 Type;Events").c_str(), origin_bins, 0, origin_bins);

      hist_jet_truth_origin[i] = new TH1D(("jets_tr_origin_"+to_string(i)).c_str(), ("Origins 2lOS"+region_names[i]+";Origin;Events").c_str(), origin_bins, 0, origin_bins);
      hist_jet_truth_type[i] = new TH1D(("jets_tr_type_"+to_string(i)).c_str(), ("Types 2lOS"+region_names[i]+";Type;Events").c_str(), origin_bins, 0, origin_bins);

      hist_jet0_truth_origin[i] = new TH1D(("jet0_tr_origin_"+to_string(i)).c_str(), ("Origins 2lOS"+region_names[i]+";Origin;Events").c_str(), origin_bins, 0, origin_bins);
      hist_jet0_truth_type[i] = new TH1D(("jet0_tr_type_"+to_string(i)).c_str(), ("Types 2lOS"+region_names[i]+";Type;Events").c_str(), origin_bins, 0, origin_bins);
      hist_jet1_truth_origin[i] = new TH1D(("jet1_tr_origin_"+to_string(i)).c_str(), ("Origins 2lOS"+region_names[i]+";Origin;Events").c_str(), origin_bins, 0, origin_bins);
      hist_jet1_truth_type[i] = new TH1D(("jet1_tr_type_"+to_string(i)).c_str(), ("Types 2lOS"+region_names[i]+";Type;Events").c_str(), origin_bins, 0, origin_bins);
        //hist_min_DRlb
      for(int db=0; db<2;db++){
	hist_min_DRlb[i][db] = new TH1D(("DRlb"+to_string(db)+"_"+to_string(i)).c_str(), (" #DeltaR_{l,b} 2lOS"+region_names[i]+";min#DeltaR_{l,b};Events").c_str(), dr_bins, 0., dr_max);
      }
      
      hist_mqq_jet_truth_origin[i] = new TH2D(("mqq_jets_tr_origin_"+to_string(i)).c_str(), ("Origins 2lOS"+region_names[i]+";Origin;Events").c_str(), origin_bins, 0, origin_bins,50, 50, 150);
      hist_mqqP_jet_truth_origin[i] = new TH2D(("mqq_qqjet_tr_origin_"+to_string(i)).c_str(), ("Origins 2lOS"+region_names[i]+";Origin;Events").c_str(), origin_bins, 0, origin_bins,50, 50, 150);
      hist_mqq_jet_truth_type[i] = new TH2D(("mqq_jets_tr_type_"+to_string(i)).c_str(), ("Types 2lOS"+region_names[i]+";Type;Events").c_str(), origin_bins, 0, origin_bins,50, 50, 150);
      hist_mqqP_jet_truth_type[i] = new TH2D(("mqq_qqjet_tr_type_"+to_string(i)).c_str(), ("Types 2lOS"+region_names[i]+";Type;Events").c_str(), origin_bins, 0, origin_bins,50, 50, 150);

  }


    //(int)weight_names.size()
    for(int i=0; i<(int)weight_names.size();i++){
      hist_Weights[i] = new TH1D( (weight_names[i]).c_str(), (weight_names[i]+";weight;Events").c_str(), 300, -4, 4);
    }  
}

Bool_t partlevel_wqq::Process(Long64_t entry)
{
  if(stoploop) return 0;
  //fReader.SetEntry(entry);
  fReader.SetLocalEntry(entry);
  // print some information about the current entry
  if ((entry)%10000 == 0)
    printf("Processing Entry  %llu \n", entry);

  //if ((entry)%1000 == 0)    printf("    --  milestone  %llu \n", entry);

  // increase the total number of entries
  ++fNumberOfEvents;

  //weight definitions
  Double_t weight_to_use=1;
  weight_to_use = *weight_mc *Acc;

  double shift=0;
  double shift2=0;
  double pdf_var_up=1,pdf_var_down=1;
  weight_tot=weight_to_use ;
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

  float l0_true_origin=0,l1_true_origin=0;  
  float l0_true_type=0,l1_true_type=0;  
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

    l0_true_origin= mu_true_origin[0]; l1_true_origin= mu_true_origin[1];
    l0_true_type= mu_true_type[0]; l1_true_type= mu_true_type[1];
}
  else if ( dilep_type==3 ){ 
    lep_4v[0].SetPtEtaPhiE(el_pt[0]/1e3,el_eta[0],el_phi[0],el_e[0]);
    lep_4v[1].SetPtEtaPhiE(el_pt[1]/1e3,el_eta[1],el_phi[1],el_e[1]);

    l0_charge= el_charge[0]; l1_charge= el_charge[1];
    l0_eta= el_eta[0]; l1_eta= el_eta[1];
    l0_pt= el_pt[0]/1e3; l1_pt= el_pt[1]/1e3;

    l0_true_origin= el_true_origin[0]; l1_true_origin= el_true_origin[1];
    l0_true_type= el_true_type[0]; l1_true_type= el_true_type[1];
  }
  else if ( dilep_type==2 ){ 
    if(mu_pt[0]>el_pt[0]){ 
      lep_4v[0].SetPtEtaPhiE(mu_pt[0]/1e3,mu_eta[0],mu_phi[0],mu_e[0]);
      lep_4v[1].SetPtEtaPhiE(el_pt[0]/1e3,el_eta[0],el_phi[0],el_e[0]);

      l0_charge= mu_charge[0]; l1_charge= el_charge[0];
      l0_eta= mu_eta[0]; l1_eta= el_eta[0];
      l0_pt= mu_pt[0]/1e3; l1_pt= el_pt[0]/1e3;

      l0_true_origin= mu_true_origin[0]; l1_true_origin= el_true_origin[0];
      l0_true_type= mu_true_type[0]; l1_true_type= el_true_type[0];
    }
    else{    
      lep_4v[0].SetPtEtaPhiE(el_pt[0]/1e3,el_eta[0],el_phi[0],el_e[0]);
      lep_4v[1].SetPtEtaPhiE(mu_pt[0]/1e3,mu_eta[0],mu_phi[0],mu_e[0]);

      l1_charge= mu_charge[0]; l0_charge= el_charge[0];
      l1_eta= mu_eta[0]; l0_eta= el_eta[0];
      l1_pt= mu_pt[0]/1e3; l0_pt= el_pt[0]/1e3;

      l1_true_origin= mu_true_origin[0]; l0_true_origin= el_true_origin[0];
      l1_true_type= mu_true_type[0]; l0_true_type= el_true_type[0];
    }
  }
  

  int lead_lep=9999, sublead_lep=9999;
  if(  lep_4v[0].Pt()>lep_4v[1].Pt()){
    lead_lep=0;sublead_lep=1;}
  else {    lead_lep=1;sublead_lep=0;}
  

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


  float charges=l0_charge+l1_charge;
  //SS
  //f(charges!=0)       cout <<"      +====+++ big trouble     " << endl;
  //OS
  if(charges!=0) return 0;
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;
 
  float max_eta=  max ( fabs( l0_eta ), fabs( l1_eta ) ); 

  int Njets=0, Nbjets=0, Ncjets=0;
  float HTall=0, HTjet=0; 
  vector<TLorentzVector> jets_vec;
  vector<TLorentzVector> ljets_vec;
  vector<TLorentzVector> bjets_vec;
  vector<TLorentzVector> cjets_vec;
  vector<int> sel_jet_true_type;
  vector<int> sel_jet_true_origin;
  
  vector<int> mqq_jet_true_type;
  vector<int> mqq_jet_true_origin;
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
    sel_jet_true_type.push_back(jet_true_type[j]);
    sel_jet_true_origin.push_back(jet_true_origin[j]);

    if(jet_nGhosts_bHadron[j]>0){
      Nbjets+=1;
      bjets_vec.push_back(jj);
      
    }
    else{
      ljets_vec.push_back(jj);
      
      
      if(jet_nGhosts_cHadron[j]>0){
	Ncjets+=1;
	cjets_vec.push_back(jj);
      }

      mqq_jet_true_type.push_back(jet_true_type[j]);
      mqq_jet_true_origin.push_back(jet_true_origin[j]);

    }
    
    HTjet+=jet_pt[j];
    
  }
  if(lowjets>0) return 0;
  //central jets above 25 gev
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;

  if(Nbjets!=2) return 0;
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;

  // if(Njets<3 || Nbjets<1) return 0;
  if(Njets<4) return 0;
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;



  HTall=HTjet+(lep_4v[lead_lep].Pt()+lep_4v[sublead_lep].Pt())*1000;

  // check pt ordering in jets
  double jptmax=0;
  for (unsigned int i=0; i<jets_vec.size();i++){
    if(jets_vec[i].Pt()/1e3>jptmax){    jptmax=jets_vec[i].Pt()/1e3;

      if(i!=0)     cout << "pT (jet #"<<i<<")=" <<jets_vec[i].Pt()/1e3<< ", while jet0="<< jets_vec[0].Pt()/1e3<<endl;
    }
  }

  double bjptmax=0;
  for (unsigned int i=0; i<bjets_vec.size();i++){
    if(bjets_vec[i].Pt()/1e3>bjptmax){    bjptmax=bjets_vec[i].Pt()/1e3;

      if(i!=0)     cout << "pT (bjet #"<<i<<")=" <<bjets_vec[i].Pt()/1e3<< ", while bjet0="<< bjets_vec[0].Pt()/1e3<<endl;
    }
  }

  double ljptmax=0;
  for (unsigned int i=0; i<ljets_vec.size();i++){
    if(ljets_vec[i].Pt()/1e3>ljptmax){    ljptmax=ljets_vec[i].Pt()/1e3;

      if(i!=0)     cout << "pT (bjet #"<<i<<")=" <<ljets_vec[i].Pt()/1e3<< ", while ljet0="<< ljets_vec[0].Pt()/1e3<<endl;
    }
  }


  // DeltaRs
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


  
  //cout << " -------  search for  Wqq:   jets_vec.size() = "<< jets_vec.size()  << endl;
  double bestWmass = 1000.0*1e6;
  double mWPDG = 80.399*1e3;
  int Wj1index = -1, Wj2index = -1;
  bool found_w=false;
  double wmass=999;
  for (unsigned int i = 0; i < (ljets_vec.size() - 1); ++i) {
    for (unsigned int j = i + 1; j < ljets_vec.size(); ++j) {
      wmass = (ljets_vec[i] + ljets_vec[j]).M();
      
      if (fabs(wmass - mWPDG) < fabs(bestWmass - mWPDG)) {
	bestWmass = wmass;
	Wj1index = i;
	Wj2index = j;
	found_w=true;	
	
	//cout << " -------====  bestWmass [i="<<i<<", j="<<j<<"] =  "<< bestWmass  << endl;

      }
    }
  }

  // found W->qq
  if (!found_w) return 0;
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;
  
  TLorentzVector pjet1 = ljets_vec[Wj1index];
  TLorentzVector pjet2 = ljets_vec[Wj2index];
  // compute hadronic W boson
  TLorentzVector pWhadron = pjet1 + pjet2;


  vector<float> dRl0b;  vector<float> dRl1b;
  for(int i=0; i<Nbjets;i++){
    dRl0b.push_back( lep_4v[lead_lep].DeltaR( bjets_vec[i] ) );
    dRl1b.push_back( lep_4v[sublead_lep].DeltaR( bjets_vec[i] ) );
  }
   
  Double_t dRlb[2];
  dRlb[0]= *min_element(dRl0b.begin(),dRl0b.end());
  dRlb[1]= *min_element(dRl1b.begin(),dRl1b.end());
  

  sel_array[0]=(Nhtaus == 0 && Njets >= 4 );  // Region inclusive
  sel_array[1]=(Nhtaus == 0 && Njets >= 4 && Ncjets>0 );  // 
  sel_array[2]=(Nhtaus == 0 && Njets >= 4 && abs(pWhadron.M()-mWPDG)<1e4);
  sel_array[3]=(Nhtaus == 0 && Njets >= 4 && Ncjets>0 && abs(pWhadron.M()-mWPDG)<1e4);  //
  
  //sel_array[2]=(Nhtaus == 0 && Njets >= 4 && abs(mWPDG - pWhadron.M())/1e3<10 );  // Region 10GeV Wmass region
  //sel_array[3]=(Nhtaus == 0 && Njets >= 4 && abs(mWPDG - pWhadron.M())/1e3<5 );  // Region 5GeV Wmass region

  //cout << " -------====  Wmass =  "<< bestWmass << ", Njets = "<<Njets <<  ", Nbjets = "<<Nbjets <<  ", Ncjets = "<<Ncjets << ", dRlb[0] = " <<dRlb[0]<< ", dRlb[1] = " <<dRlb[1]  << endl;

  float met = *met_met/1000.;

  for(int i=0; i<(int)region_names.size();i++){
    if(sel_array[i]){
      h_cutflow_2l[0]->Fill(cf_counter+i,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter+i,1);
      
      hist_DRll01[i]->Fill(DRll01, weight_tot);
      hist_lep_Pt_0[i]->Fill(lep_4v[lead_lep].Pt(), weight_tot);
      hist_lep_Pt_1[i]->Fill(lep_4v[sublead_lep].Pt(), weight_tot);
      hist_jet_Pt_1[i]->Fill(jets_vec[0].Pt()/1e3, weight_tot);
      hist_jet_Pt_2[i]->Fill(jets_vec[1].Pt()/1e3, weight_tot);
      hist_jet_Pt_3[i]->Fill(jets_vec[2].Pt()/1e3, weight_tot);
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
      hist_HT_leps[i]->Fill( (lep_4v[lead_lep].Pt()+lep_4v[sublead_lep].Pt()), weight_tot);
      hist_HT[i]->Fill(HTall/1000, weight_tot);
      hist_nJets[i]->Fill(Njets, weight_tot);
      hist_nBtagJets[i]->Fill(Nbjets, weight_tot);
      hist_MET[i]->Fill(met, weight_tot);

      hist_lep_Eta_0[i]->Fill(lep_4v[lead_lep].Eta(), weight_tot);
      hist_lep_Eta_1[i]->Fill(lep_4v[sublead_lep].Eta(), weight_tot);
      hist_lep_Phi_0[i]->Fill(lep_4v[lead_lep].Phi(), weight_tot);
      hist_lep_Phi_1[i]->Fill(lep_4v[sublead_lep].Phi(), weight_tot);
      hist_lep_dPhi[i]->Fill(abs(lep_4v[lead_lep].Phi()-lep_4v[sublead_lep].Phi()), weight_tot);
      hist_Whmass[i]->Fill(pWhadron.M()/1e3, weight_tot);
      hist_Whpt[i]->Fill(pWhadron.Pt()/1e3, weight_tot);
      
      hist_lep_truth_origin[i]->Fill(l0_true_origin, weight_tot);
      hist_lep_truth_origin[i]->Fill(l1_true_origin, weight_tot);
      hist_lep_truth_origin_0[i]->Fill(l0_true_origin, weight_tot);
      hist_lep_truth_origin_1[i]->Fill(l1_true_origin, weight_tot);
      
      hist_lep_truth_type[i]->Fill(l0_true_type, weight_tot);
      hist_lep_truth_type[i]->Fill(l1_true_type, weight_tot);
      hist_lep_truth_type_0[i]->Fill(l0_true_type, weight_tot);
      hist_lep_truth_type_1[i]->Fill(l1_true_type, weight_tot);


      for(int j=0; j<Njets;j++){
	//cout << "    jet_true_type["<<j<<"/"<<Njets<<"]/sel = " << jet_true_type[j]<< " / "<<  sel_jet_true_type[j]<< "    jet_true_origin["<<j<<"]" << jet_true_origin[j]<< ", pt="<<jets_vec[j].Pt()/1e3<<endl;
	hist_jet_truth_origin[i]->Fill(sel_jet_true_origin[j], weight_tot);
	hist_jet_truth_type[i]->Fill(sel_jet_true_type[j], weight_tot);

	hist_mqq_jet_truth_origin[i]->Fill(sel_jet_true_origin[j],pWhadron.M()/1e3, weight_tot);
	hist_mqq_jet_truth_origin[i]->Fill(sel_jet_true_origin[j],pWhadron.M()/1e3, weight_tot);

	hist_mqq_jet_truth_type[i]->Fill(sel_jet_true_type[j],pWhadron.M()/1e3, weight_tot);
	hist_mqq_jet_truth_type[i]->Fill(sel_jet_true_type[j],pWhadron.M()/1e3, weight_tot);

      }

      hist_mqqP_jet_truth_origin[i]->Fill(mqq_jet_true_origin[Wj1index],pWhadron.M()/1e3, weight_tot);
      hist_mqqP_jet_truth_origin[i]->Fill(mqq_jet_true_origin[Wj2index],pWhadron.M()/1e3, weight_tot);

      hist_mqqP_jet_truth_type[i]->Fill(mqq_jet_true_type[Wj1index],pWhadron.M()/1e3, weight_tot);
      hist_mqqP_jet_truth_type[i]->Fill(mqq_jet_true_type[Wj2index],pWhadron.M()/1e3, weight_tot);

      hist_jet0_truth_origin[i]->Fill(mqq_jet_true_origin[Wj1index], weight_tot);
      hist_jet0_truth_type[i]->Fill(mqq_jet_true_type[Wj1index], weight_tot);
      hist_jet1_truth_origin[i]->Fill(mqq_jet_true_origin[Wj2index], weight_tot);
      hist_jet1_truth_type[i]->Fill(mqq_jet_true_type[Wj2index], weight_tot);
      
      for(int db=0; db<2;db++){
	hist_min_DRlb[i][db]->Fill(dRlb[db], weight_tot);
      }
    }
  }  
  
  return kTRUE;
}

void partlevel_wqq::SlaveTerminate()
{
}

void partlevel_wqq::Terminate()
{
  printf("\nTotal Number of Events: %d\n", fNumberOfEvents);

  if(!stoploop){
    string outname="wqq_"+input_name+"_"+comp_name+".root";
    TFile hfile(outname.c_str(),"RECREATE"); //,"tHq"
    //*
    h_cutflow_2l[0]->Write(); 
    h_cutflow_2l[1]->Write(); 
    
    for(int i=0; i<(int)region_names.size();i++){
      hist_DRll01[i]->Write();
      hist_lep_Pt_0[i]->Write();
      hist_lep_Pt_1[i]->Write();
      hist_jet_Pt_1[i]->Write();
      hist_jet_Pt_2[i]->Write();
      hist_jet_Pt_3[i]->Write();
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
      hist_Whmass[i]->Write();
      hist_Whpt[i]->Write();
      hist_lep_truth_origin[i]->Write();
      hist_lep_truth_origin_0[i]->Write();
      hist_lep_truth_origin_1[i]->Write();

      hist_lep_truth_type[i]->Write();
      hist_lep_truth_type_0[i]->Write();
      hist_lep_truth_type_1[i]->Write();

      hist_jet_truth_origin[i]->Write();
      hist_jet_truth_type[i]->Write();

      hist_mqq_jet_truth_origin[i]->Write();
      hist_mqqP_jet_truth_origin[i]->Write();

      hist_mqq_jet_truth_type[i]->Write();
      hist_mqqP_jet_truth_type[i]->Write();

      hist_jet0_truth_origin[i]->Write();
      hist_jet0_truth_type[i]->Write();
      hist_jet1_truth_origin[i]->Write();
      hist_jet1_truth_type[i]->Write();
      
      //hist_min_DRlb
      for(int db=0; db<2;db++){
	hist_min_DRlb[i][db]->Write();
      }

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
