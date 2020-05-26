#define reco_wqq_cxx


#include "reco_wqq.h"
#include <TH2.h>
#include <TStyle.h>
#include <TLorentzVector.h>
#include <math.h>
#include <map>

TH1F *h_cutflow_2l[2];
int debug=21;
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

TH1D *hist_jjpt[10];
TH1D *hist_mjj[10];

TH1D *hist_lep_truth_origin[10];
TH1D *hist_lep_truth_origin_0[10];
TH1D *hist_lep_truth_origin_1[10];

TH1D *hist_lep_truth_type[10];
TH1D *hist_lep_truth_type_0[10];
TH1D *hist_lep_truth_type_1[10];

TH1D *hist_jet_truth_origin[10];
TH1D *hist_jet_truth_type[10];

TFile *newfile;
TTree *outTree;


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

vector<string> region_names={"2b4j",">1b4j","2bWm","1bWm","2bWmPt","1bWmPt"};

void reco_wqq::Begin(TTree * /*tree*/)
{
  TString option = GetOption();
}

void reco_wqq::ReadOpt(double sumweights, int var_type)
{
  double inval1 = sumweights;
  int inval2 = var_type;
  std::cout<< "i'm in the ReadOpt function -  "<<inval1<< " " <<inval2 << std::endl;      
}

void reco_wqq::SlaveBegin(TTree * /*tree*/)
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

  input_name=input_option.substr(input_option.find("/")+1,(input_option.find("-")-input_option.find("/")-1));
  comp_name=input_option.substr(input_option.find("-")+1);

  //1 / (sum of weights per variation)
  // xs from ami , 
  /*
  #ttW       0.00065206 nb
  # ttZ(qq)  0.00052821 nb
  # ttbar    0.72977 nb
  //*/ 
  std::map<std::string, double> xs_map;
  
  xs_map["700000"]= 0.58922 * 1 ;
  xs_map["413008"]= 0.652 * 0.920 ;
  xs_map["410157"]= 0.52771 * 1.11 ;
  xs_map["410156"]= 0.15499 * 1.11;
  xs_map["410155"]= 0.54830 * 1.10;
  xs_map["410218"]= 0.036888 * 1.12 ;
  xs_map["410219"]= 0.036895 * 1.12 ;
  xs_map["410220"]= 0.036599 * 1.12 ;
  xs_map["410472"]= 76.95 * 1.1398;
  xs_map["410470"]= 396.87 * 1.1398;  
  xs_map["410470_0"]= 396.87 * 1.1398; xs_map["410470_1"]= 396.87 * 1.1398; xs_map["410470_2"]= 396.87 * 1.1398; xs_map["410470_3"]= 396.87 * 1.1398;  xs_map["410470_4"]= 396.87 * 1.1398; xs_map["410470_5"]= 396.87 * 1.1398; xs_map["410470_6"]= 396.87 * 1.1398; xs_map["410470_7"]= 396.87 * 1.1398;
  xs_map["410658"]= 36.993 * 1.191;
  xs_map["410659"]= 22.175 * 1.183;
  xs_map["410644"]= 2.0268 * 1.015 ;
  xs_map["410645"]= 1.2676 * 1.015;
  xs_map["304014"]= 0.0016398 * 1.0;
  xs_map["410080"]= 0.0091622 * 1.0042 ;
  xs_map["410081"]= 0.0080975 * 1.2231 ;
  xs_map["410408"]= 0.016046 * 1.0 ;

  xs_map["345874"]=  0.22276 * 1.0 ;
  xs_map["345875"]=  0.05343 * 1.0 ;
  xs_map["363356"]=  15.563  * 0.13961 ;
  xs_map["363357"]=  6.7973 * 1.0 ;
  xs_map["363358"]=  3.437 * 1.0 ;
  xs_map["363359"]=  24.717 * 1.0 ;
  xs_map["364285"]=  0.1163 * 1.0 ;


  std::cout << "input_name ="<< input_name<< ", comp_name - "<< comp_name<< ", xs = "<<xs_map[input_name] << std::endl;  
  Double_t gen_xs=1;
  gen_xs=xs_map[input_name];
  totalEventsWeighted=gen_xs/smw; //*1e3 match units of integrated luminosity to be in pb
  //Acc=1/smw;


  const std::vector<TString> s_cutDescs =
    {  "Preselections","Nleps","lepPt1>20","lepPt0>25","lepCentr","lepID","OS","4j",">1b","0tau",
       ">2nonb", "4j2b","4j","2bWjj",">1bWjj","2bWjjPtjj","1bWjjPtjj"};//"w>20","w>10","w>5"
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

    hist_jjpt[i] = new TH1D(("jjpt_"+to_string(i)).c_str(), ("p_T^{jj} "+region_names[i]+";p_T^{jj};Events").c_str(),60,0,300 ); //w_binnum, w_bins
    hist_mjj[i] = new TH1D(("mjj_"+to_string(i)).c_str(), ("m_{jj} "+region_names[i]+";m_{jj};Events").c_str(), 50, 50, 150); //420, 50, 410

    hist_lep_truth_origin[i] = new TH1D(("leps_tr_origin_"+to_string(i)).c_str(), ("Origins 2lOS"+region_names[i]+";Origin;Events").c_str(), origin_bins, 0, origin_bins);
    hist_lep_truth_origin_0[i] = new TH1D(("lep0_tr_origin_"+to_string(i)).c_str(), ("L0 Origin 2lOS"+region_names[i]+";l0 Origin;Events").c_str(), origin_bins, 0, origin_bins);
    hist_lep_truth_origin_1[i] = new TH1D(("lep1_tr_origin_"+to_string(i)).c_str(), ("L1 Origin 2lOS"+region_names[i]+";l1 Origin;Events").c_str(), origin_bins, 0, origin_bins);

    hist_lep_truth_type[i] = new TH1D(("leps_tr_type_"+to_string(i)).c_str(), ("Types 2lOS"+region_names[i]+";Type;Events").c_str(), origin_bins, 0, origin_bins);
    hist_lep_truth_type_0[i] = new TH1D(("lep0_tr_type_"+to_string(i)).c_str(), ("L0 Type 2lOS"+region_names[i]+";l0 Type;Events").c_str(), origin_bins, 0, origin_bins);
    hist_lep_truth_type_1[i] = new TH1D(("lep1_tr_type_"+to_string(i)).c_str(), ("L1 Type 2lOS"+region_names[i]+";l1 Type;Events").c_str(), origin_bins, 0, origin_bins);

    hist_jet_truth_origin[i] = new TH1D(("jets_tr_origin_"+to_string(i)).c_str(), ("Origins 2lOS"+region_names[i]+";Origin;Events").c_str(), origin_bins, 0, origin_bins);
    hist_jet_truth_type[i] = new TH1D(("jets_tr_type_"+to_string(i)).c_str(), ("Types 2lOS"+region_names[i]+";Type;Events").c_str(), origin_bins, 0, origin_bins);
    //hist_min_DRlb
    for(int db=0; db<2;db++){
      hist_min_DRlb[i][db] = new TH1D(("DRlb"+to_string(db)+"_"+to_string(i)).c_str(), (" #DeltaR_{l,b} 2lOS"+region_names[i]+";min#DeltaR_{l,b};Events").c_str(), dr_bins, 0., dr_max);
    }

  }


  string ntupname="skimReco_"+input_name+"_"+comp_name+".root";
  
  newfile = new TFile(ntupname.c_str(),"recreate"); 
  outTree = new TTree("outTree","outTree");
  outTree->Branch("Njets",&Njets,"Njets/I");
  
  outTree->Branch("Nbjets",&Nbjets,"Nbjets/I");
  outTree->Branch("HTall",&HTall,"HTall/F");
  outTree->Branch("HTjet",&HTjet,"HTjet/F");
  outTree->Branch("drll01",&drll01,"drll01/F");
  outTree->Branch("max_eta",&max_eta,"max_eta/F");
  outTree->Branch("lep_dphi",&lep_dphi,"lep_dphi/F");
  outTree->Branch("region",&region,"region/I");
  outTree->Branch("weight_tot",&weight_tot,"weight_tot/D");
  outTree->Branch("l0_pt",&l0_pt,"l0_pt/F");
  outTree->Branch("l1_pt",&l1_pt,"l1_pt/F");
  outTree->Branch("l0_eta",&l0_eta,"l0_eta/F");
  outTree->Branch("l1_eta",&l1_eta,"l1_eta/F");
  outTree->Branch("l0_e",&l0_e,"l0_e/F");
  outTree->Branch("l1_e",&l1_e,"l1_e/F");
  outTree->Branch("l0_phi",&l0_phi,"l0_phi/F");
  outTree->Branch("l1_phi",&l1_phi,"l1_phi/F");
  outTree->Branch("l0_id",&l0_id,"l0_id/F");
  outTree->Branch("l1_id",&l1_id,"l1_id/F");
  outTree->Branch("dileptype",&dileptype,"dileptype/F");
  //outTree->Branch("min_DRl0j",&min_DRl0j,"min_DRl0j/F");
  //outTree->Branch("min_DRl1j",&min_DRl1j,"min_DRl1j/F");
  outTree->Branch("met",&met,"met/F");
  outTree->Branch("metphi",&metphi,"metphi/F");
  outTree->Branch("mjj",&mjj,"mjj/F");  outTree->Branch("ptjj",&ptjj,"ptjj/F");
  outTree->Branch("etajj",&etajj,"etajj/F");  outTree->Branch("phijj",&phijj,"phijj/F");
  outTree->Branch("ptj0",&ptj0,"ptj0/F");outTree->Branch("etaj0",&etaj0,"etaj0/F");outTree->Branch("phij0",&phij0,"phij0/F");outTree->Branch("isbj0",&isbj0,"isbj0/F");outTree->Branch("ej0",&ej0,"ej0/F");
  outTree->Branch("ptj1",&ptj1,"ptj1/F");outTree->Branch("etaj1",&etaj1,"etaj1/F");outTree->Branch("phij1",&phij1,"phij1/F");outTree->Branch("isbj1",&isbj1,"isbj1/F");outTree->Branch("ej1",&ej1,"ej1/F");
  outTree->Branch("ptj2",&ptj2,"ptj2/F");outTree->Branch("etaj2",&etaj2,"etaj2/F");outTree->Branch("phij2",&phij2,"phij2/F");outTree->Branch("isbj2",&isbj2,"isbj2/F");outTree->Branch("ej2",&ej2,"ej2/F");
  outTree->Branch("ptj3",&ptj3,"ptj3/F");outTree->Branch("etaj3",&etaj3,"etaj3/F");outTree->Branch("phij3",&phij3,"phij3/F");outTree->Branch("isbj3",&isbj3,"isbj3/F");outTree->Branch("ej3",&ej3,"ej3/F");
  outTree->Branch("ptj4",&ptj4,"ptj4/F");outTree->Branch("etaj4",&etaj4,"etaj4/F");outTree->Branch("phij4",&phij4,"phij4/F");outTree->Branch("isbj4",&isbj4,"isbj4/F");outTree->Branch("ej4",&ej4,"ej4/F");
  outTree->Branch("ptj5",&ptj5,"ptj5/F");outTree->Branch("etaj5",&etaj5,"etaj5/F");outTree->Branch("phij5",&phij5,"phij5/F");outTree->Branch("isbj5",&isbj5,"isbj5/F");outTree->Branch("ej5",&ej5,"ej5/F");
  outTree->Branch("ptj6",&ptj6,"ptj6/F");outTree->Branch("etaj6",&etaj6,"etaj6/F");outTree->Branch("phij6",&phij6,"phij6/F");outTree->Branch("isbj6",&isbj6,"isbj6/F");outTree->Branch("ej6",&ej6,"ej6/F");
  outTree->Branch("ptj7",&ptj7,"ptj7/F");outTree->Branch("etaj7",&etaj7,"etaj7/F");outTree->Branch("phij7",&phij7,"phij7/F");outTree->Branch("isbj7",&isbj7,"isbj7/F");outTree->Branch("ej7",&ej7,"ej7/F");
  outTree->Branch("ptj8",&ptj8,"ptj8/F");outTree->Branch("etaj8",&etaj8,"etaj8/F");outTree->Branch("phij8",&phij8,"phij8/F");outTree->Branch("isbj8",&isbj8,"isbj8/F");outTree->Branch("ej8",&ej8,"ej8/F");
  outTree->Branch("ptj9",&ptj9,"ptj9/F");outTree->Branch("etaj9",&etaj9,"etaj9/F");outTree->Branch("phij9",&phij9,"phij9/F");outTree->Branch("isbj9",&isbj9,"isbj9/F");outTree->Branch("ej9",&ej9,"ej9/F");
  outTree->Branch("ptj10",&ptj10,"ptj10/F");outTree->Branch("etaj10",&etaj10,"etaj10/F");outTree->Branch("phij10",&phij10,"phij10/F");outTree->Branch("isbj10",&isbj10,"isbj10/F");outTree->Branch("ej10",&ej10,"ej10/F");
  outTree->Branch("ptj11",&ptj11,"ptj11/F");outTree->Branch("etaj11",&etaj11,"etaj11/F");outTree->Branch("phij11",&phij11,"phij11/F");outTree->Branch("isbj11",&isbj11,"isbj11/F");outTree->Branch("ej11",&ej11,"ej11/F");


  outTree->Branch("truth_m",&truth_m);
  outTree->Branch("truth_pt",&truth_pt);
  outTree->Branch("truth_eta",&truth_eta);
  outTree->Branch("truth_phi",&truth_phi);
  outTree->Branch("truth_e",&truth_e);
  outTree->Branch("truth_pdgId",&truth_pdgId);
  outTree->Branch("truth_status",&truth_status);
  outTree->Branch("truth_barcode",&truth_barcode);
  outTree->Branch("truth_parents",&truth_parents);
  outTree->Branch("truth_children",&truth_children);
  
//*/
  
  //(int)weight_names.size()
  for(int i=0; i<(int)weight_names.size();i++){
    hist_Weights[i] = new TH1D( (weight_names[i]).c_str(), (weight_names[i]+";weight;Events").c_str(), 300, -4, 4);
  }  
}

Bool_t reco_wqq::Process(Long64_t entry)
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
  //weight_to_use = *weight_mc *totalEventsWeighted;
  weight_to_use = (36074.6*(*randomRunNumber<=311481)+43813.7*(*randomRunNumber>311481 && *randomRunNumber <=341649)+58450.1*(*randomRunNumber>341649))
    * *weight_pileup
    * *weight_jvt
    * *weight_mc
    * totalEventsWeighted;

  if(debug<21 && weight_to_use>10)
    cout << "*weight_pileup= "<< *weight_pileup << " *weight_jvt="<< *weight_jvt << " totalEventsWeighted="<< totalEventsWeighted<< "; randomRunNumber= "<< *randomRunNumber
	 << '\n'<< weight_to_use << endl;
  
  weight_tot=weight_to_use ;
  //cout<< "weight_tot = "<< weight_tot<< endl;
  int cf_counter=0;

  //presel
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;

  if(debug<5)
      cout<< "dilep_type="<<*dilep_type<<"  *nJets_OR ="<<*nJets_OR<<endl;
  //Nleps
  if(!*dilep_type) return 0;
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;

  if(debug<5)
      cout<< "lep_Pt_1="<<*lep_Pt_1<<"  *nJets_OR ="<<*nJets_OR<<endl;

  //lep Pt cuts
  if(*lep_Pt_1<20*1e3) return 0;  
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;

  if(debug<5)
    cout<< "lep_Pt_0="<<*lep_Pt_0<<"  *nJets_OR ="<<*nJets_OR<<endl;

  if(*lep_Pt_0<20*1e3) return 0;  
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;


  if(debug<5)
    cout<< "lep_Eta_0="<<*lep_Eta_0<<"  *nJets_OR ="<<*nJets_OR<<endl;
//lep eta cuts
  if(abs(*lep_Eta_0)>2.5||abs(*lep_Eta_1)>2.5) return 0;  
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;

  if(debug<6)
    cout<< "lep_isMedium_0="<<int(*lep_isMedium_0)<< " lep_isMedium_1="<<int(*lep_isMedium_1)<<"  *nJets_OR ="<<*nJets_OR<<endl;

  //tight leptons
  //if(!int(*lep_isTight_0)||!int(*lep_isTight_1)) return 0;  
  //if(!int(*lep_isLoose_0)||!int(*lep_isLoose_1)) return 0;  
  if(!int(*lep_isMedium_0)||!int(*lep_isMedium_1)) return 0;  
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;

  if(debug<7)
    cout<< "OS => lep_ID_0="<<*lep_ID_0<< " lep_ID_1="<<*lep_ID_1<<"  *nJets_OR ="<<*nJets_OR<<endl;
  
  if(*lep_ID_0 * *lep_ID_1 > 0) return 0;
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;


  Njets=0;
  Nbjets=0;
  Int_t Ncjets=0;
  int lowjets=0;
  vector<TLorentzVector> jets_vec;
  vector<TLorentzVector> bjets_vec;
  vector<TLorentzVector> nonbjets_vec;

  
  //for(int j=0;j< int(*nJets_OR); j++){
  for(int j=0;j< int(jets_pt.GetSize()); j++){
    if(jets_pt[j]/1000.<25){
      lowjets++;      
      return 0;
    }    
    if(fabs(jets_eta[j])>2.5) return 0;

    Njets++;
    TLorentzVector jj;
    jj.SetPtEtaPhiE(jets_pt[j],jets_eta[j],jets_phi[j],jets_e[j]);
    jets_vec.push_back(jj);

    if(jets_btagFlag_DL1r_FixedCutBEff_70[j]>0){
      Nbjets++;
      bjets_vec.push_back(jj);
    }
    else
      nonbjets_vec.push_back(jj);
    //check option of getting c-tagger
  
  }

  if(debug<21 && (int(*nJets_OR)>10))
    cout<< "jets_pt["<<*nJets_OR<<"] "<<jets_pt[int(*nJets_OR)-1]<< ", lowjets = "<< lowjets<<endl;

  if(debug<21 && (int(*nJets_OR)!=int(jets_pt.GetSize())))
    cout<< "int(jets_pt.GetSize() "<<int(jets_pt.GetSize())<<"  *nJets_OR ="<<*nJets_OR<<endl;
  
  if(debug<21 && (int(*nJets_OR_DL1r_70)!=int(bjets_vec.size())))
    cout<< "bjets_vec.size "<<bjets_vec.size()<<"  *nJets_OR_DL1r_70 ="<<*nJets_OR_DL1r_70<<endl;
  
  if(debug<20 ){
    if(Nbjets==0 && *nJets_OR_DL1r_70!=0){
      cout <<  " Njets = "<<Njets << ",  *nJets_OR ="<<*nJets_OR <<  ", Nbjets = "<<Nbjets   << "; *nJets_OR_DL1r_70 = "<<*nJets_OR_DL1r_70<<endl;
      cout <<'\n';
    }
  }

  

  if(*nJets_OR<4) return 0;
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;
  
  if(debug<8)
    cout<< "nB => *nJets_OR_DL1r_70="<<*nJets_OR_DL1r_70 << ", Nbjets = "<< Nbjets<<"  *nJets_OR ="<<*nJets_OR<<endl;

  //Bjets
  if(*nJets_OR_DL1r_70<1) return 0;
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;



  if(debug<8)
    cout<< "tau => ="<<*nTaus_OR_Pt25<<"  *nJets_OR ="<<*nJets_OR<<endl;

  // 0-taus
  if (*nTaus_OR_Pt25) return 0;
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;

  if (nonbjets_vec.size()<2) return 0;
  h_cutflow_2l[0]->Fill(cf_counter,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter,1);
  cf_counter++;

  double bestWmass = 1000.0*1e6;
  double mWPDG = 80.399*1e3;
  int Wj1index = -1, Wj2index = -1;
  bool found_w=false;
  double wmass=999;
  for (unsigned int i = 0; i < (nonbjets_vec.size() - 1); ++i) {
    for (unsigned int j = i + 1; j < nonbjets_vec.size(); ++j) {
      wmass = (nonbjets_vec[i] + nonbjets_vec[j]).M();      
      if (fabs(wmass - mWPDG) < fabs(bestWmass - mWPDG)) {
	bestWmass = wmass;
	Wj1index = i;	Wj2index = j;	found_w=true;	
      }
    }
  }
  
  if(*nJets_OR_DL1r_70!=Nbjets){
    cout<< "nB => *nJets_OR_DL1r_70="<<*nJets_OR_DL1r_70 << ", Nbjets = "<< Nbjets<<"  *nJets_OR ="<<*nJets_OR<<endl;
  }

  if(*nJets_OR!=Njets){
    cout<< "nj (gn1) => *nJets_OR="<<*nJets_OR << ", Njets = "<< Njets<<endl;
  }
    


  TLorentzVector pmjj = nonbjets_vec[0]+nonbjets_vec[1];

  TLorentzVector pjet1 = nonbjets_vec[Wj1index];
  TLorentzVector pjet2 = nonbjets_vec[Wj2index];
  // compute hadronic W boson
  TLorentzVector pWhadron = pjet1 + pjet2;
  if(debug<9)
    cout << " - Wmass =  "<< pWhadron.M()/1e3 << "; pmjj = "<<pmjj.M()/1e3 << ", Njets = "<<Njets <<  ", Nbjets = "<<Nbjets   << endl;

  if(debug<12)
    cout <<  " Njets = "<<Njets << ",  *nJets_OR ="<<*nJets_OR <<  ", Nbjets = "<<Nbjets   << endl;

  /*
 

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
  vector<float> dRl0b;  vector<float> dRl1b;
  for(int i=0; i<Nbjets;i++){
    dRl0b.push_back( lep_4v[lead_lep].DeltaR( bjets_vec[i] ) );
    dRl1b.push_back( lep_4v[sublead_lep].DeltaR( bjets_vec[i] ) );
  }
   
  Double_t dRlb[2];
  dRlb[0]= *min_element(dRl0b.begin(),dRl0b.end());
  dRlb[1]= *min_element(dRl1b.begin(),dRl1b.end());

  */  
  
  Njets = *nJets_OR;
  Nbjets = *nJets_OR_DL1r_70;
  l0_pt = *lep_Pt_0; l0_eta = *lep_Eta_0;  l0_phi = *lep_Phi_0; l0_e = *lep_E_0;
  l1_pt = *lep_Pt_1; l1_eta = *lep_Eta_1;  l1_phi = *lep_Phi_1; l1_e = *lep_E_1;
  l0_id= *lep_ID_0;
  l1_id = *lep_ID_1;
  dileptype = *dilep_type;
  lep_dphi = abs(*lep_Phi_0-*lep_Phi_1);
  drll01 = *DRll01;
  max_eta=  max ( fabs( l0_eta ), fabs( l1_eta ) ); 
  HTall = *HT;
  HTjet = *HT_jets;
  met = *met_met;
  metphi = *met_phi;
  mjj = pmjj.M();
  ptjj = pmjj.Pt();
  etajj = pmjj.Eta();
  phijj = pmjj.Phi();
  ej0=jets_e[0]; ptj0=jets_pt[0]; etaj0=jets_eta[0]; phij0=jets_phi[0]; isbj0 = jets_btagFlag_DL1r_FixedCutBEff_70[0];
  ej1=jets_e[1];  ptj1=jets_pt[1]; etaj1=jets_eta[1]; phij1=jets_phi[1]; isbj1 = jets_btagFlag_DL1r_FixedCutBEff_70[1];
  ej2=jets_e[2];  ptj2=jets_pt[2]; etaj2=jets_eta[2]; phij2=jets_phi[2]; isbj2 = jets_btagFlag_DL1r_FixedCutBEff_70[2];
  ej3=jets_e[3];  ptj3=jets_pt[3]; etaj3=jets_eta[3]; phij3=jets_phi[3]; isbj3 = jets_btagFlag_DL1r_FixedCutBEff_70[3];

  ej4=-99;ptj4=-99;etaj4=-99;phij4=-99;isbj4=-99;
  ej5=-99;ptj5=-99;etaj5=-99;phij5=-99;isbj5=-99;
  ej6=-99;ptj6=-99;etaj6=-99;phij6=-99;isbj6=-99;
  ej7=-99;ptj7=-99;etaj7=-99;phij7=-99;isbj7=-99;
  ej8=-99;ptj8=-99;etaj8=-99;phij8=-99;isbj8=-99;
  ej9=-99;ptj9=-99;etaj9=-99;phij9=-99;isbj9=-99;
  ej10=-99;ptj10=-99;etaj10=-99;phij10=-99;isbj10=-99;
  ej11=-99;ptj11=-99;etaj11=-99;phij11=-99;isbj11=-99;

  if(Njets >= 5){
    ej4=jets_e[4]; ptj4=jets_pt[4];    etaj4=jets_eta[4]; phij4=jets_phi[4]; isbj4 = jets_btagFlag_DL1r_FixedCutBEff_70[4];
  }

  if(Njets >= 6){
    ej5=jets_e[5];    ptj5=jets_pt[5];    etaj5=jets_eta[5]; phij5=jets_phi[5]; isbj5 = jets_btagFlag_DL1r_FixedCutBEff_70[5];
  }

  if(Njets >= 7){
    ej6=jets_e[6];    ptj6=jets_pt[6];    etaj6=jets_eta[6]; phij6=jets_phi[6]; isbj6 = jets_btagFlag_DL1r_FixedCutBEff_70[6];
  }

  if(Njets >= 8){
    ej7=jets_e[7];    ptj7=jets_pt[7];    etaj7=jets_eta[7]; phij7=jets_phi[7]; isbj7 = jets_btagFlag_DL1r_FixedCutBEff_70[7];
  }

  if(Njets >= 9){
    ej8=jets_e[8];    ptj8=jets_pt[8];    etaj8=jets_eta[8]; phij8=jets_phi[8]; isbj8 = jets_btagFlag_DL1r_FixedCutBEff_70[8];
  }

  if(Njets >= 10){
    ej9=jets_e[9];    ptj9=jets_pt[9];    etaj9=jets_eta[9]; phij9=jets_phi[9]; isbj9 = jets_btagFlag_DL1r_FixedCutBEff_70[9];
  }

  if(Njets >= 11){
    ej10=jets_e[10];    ptj10=jets_pt[10];    etaj10=jets_eta[10]; phij10=jets_phi[10]; isbj10 = jets_btagFlag_DL1r_FixedCutBEff_70[10];
  }

  if(Njets >= 12){
    ej11=jets_e[11];    ptj11=jets_pt[11];    etaj11=jets_eta[11]; phij11=jets_phi[11]; isbj11 = jets_btagFlag_DL1r_FixedCutBEff_70[11];
  }
  
  truth_m.clear();  
  truth_pt.clear();
  truth_eta.clear();
  truth_phi.clear();
  truth_e.clear();
  truth_pdgId.clear();
  truth_status.clear();
  truth_barcode.clear();
  truth_parents.clear();
  truth_children.clear();

  /*
  for(int j=0;j< int(m_truth_m.GetSize()); j++){ 
     truth_m.emplace_back(m_truth_m[j]); 
     truth_pt.emplace_back(m_truth_pt[j]); 
     truth_eta.emplace_back(m_truth_eta[j]); 
     truth_phi.emplace_back(m_truth_phi[j]); 
     truth_e.emplace_back(m_truth_e[j]); 
     truth_pdgId.emplace_back(m_truth_pdgId[j]); 
     truth_status.emplace_back(m_truth_status[j]); 
     truth_barcode.emplace_back(m_truth_barcode[j]);
     truth_parents.emplace_back(m_truth_parents[j]);
     truth_children.emplace_back(m_truth_children[j]);
     //for(int i=0;i< int(m_truth_parents[j].size()); i++)
     //cout <<"j("<<j<<")i("<<i <<") "<< m_truth_parents[j][i]<< endl;     
     //for(int k=0;k< int(m_truth_children[j].size()); k++)
       //cout <<"j("<<j<<")k("<<k <<") "<< m_truth_children[j][k]<< endl;           
   } 

  for(int j=0;j< int(m_truth_m.GetSize()); j++){ 
    if(m_truth_m[j]!=truth_m[j])
      cout <<m_truth_m[j] <<" "<< truth_m[j]<< endl; 
      } 
  //*/

  sel_array[0]=( Njets >= 4 && Nbjets==2 );  // Region inclusive
  sel_array[1]=( Njets >= 4  );  // && Ncjets>0
  sel_array[2]=(Njets >= 4 && Nbjets==2 && abs(pmjj.M()-mWPDG)<1e4);  
  sel_array[3]=(Njets >= 4 && abs(pmjj.M()-mWPDG)<1e4);  // && Ncjets>0
  sel_array[4]=(Njets >= 4 && Nbjets==2 && abs(pmjj.M()-mWPDG)<1e4 && (pmjj.Pt()/1e3>90 ) );  //
  sel_array[6]=(Njets >= 4 && abs(pmjj.M()-mWPDG)<1e4 && (pmjj.Pt()/1e3>90 ) );  //

  if(sel_array[0]) region = 0;
  else if(sel_array[1]) region = 1;

  outTree->Fill();
  
  float met = *met_met/1000.;
  for(int i=0; i<(int)region_names.size();i++){
    if(sel_array[i]){
      h_cutflow_2l[0]->Fill(cf_counter+i,weight_tot);  h_cutflow_2l[1]->Fill(cf_counter+i,1);

      hist_lep_Pt_0[i]->Fill(*lep_Pt_0/1e3, weight_tot);
      hist_lep_Pt_1[i]->Fill(*lep_Pt_1/1e3, weight_tot);
      hist_DRll01[i]->Fill(*DRll01, weight_tot);
      
      hist_jet_Pt_1[i]->Fill(jets_vec[0].Pt()/1e3, weight_tot);
      hist_jet_Pt_2[i]->Fill(jets_vec[1].Pt()/1e3, weight_tot);
      hist_jet_Pt_3[i]->Fill(jets_vec[2].Pt()/1e3, weight_tot);
      if(Njets >= 4){
	hist_jet_Pt_4[i]->Fill(jets_vec[3].Pt()/1e3, weight_tot);
	if(Njets >= 5) hist_jet_Pt_5[i]->Fill(jets_vec[4].Pt()/1e3, weight_tot);
	if(Njets >= 6) hist_jet_Pt_6[i]->Fill(jets_vec[5].Pt()/1e3, weight_tot);
      }
      /* hist_Bjet_Pt_0[i]->Fill(bjets_vec[0].Pt()/1e3, weight_tot); */
      /* if(Nbjets > 1){ */
      /* 	hist_Bjet_Pt_1[i]->Fill(bjets_vec[1].Pt()/1e3, weight_tot); */
      /* } */

      /* hist_min_DRl0j[i]->Fill(min_DRl0j, weight_tot); */
      /* hist_min_DRl1j[i]->Fill(min_DRl1j, weight_tot); */
      hist_maxEta_ll[i]->Fill(max_eta, weight_tot);
      hist_HT_jets[i]->Fill(*HT_jets/1e3, weight_tot);
      hist_HT_leps[i]->Fill( *HT_lep/1e3, weight_tot);
      hist_HT[i]->Fill(*HT/1e3, weight_tot);
      hist_nJets[i]->Fill(*nJets_OR, weight_tot);
      hist_nBtagJets[i]->Fill(*nJets_OR_DL1r_70, weight_tot);
      hist_MET[i]->Fill(met, weight_tot);

      hist_lep_Eta_0[i]->Fill(*lep_Eta_0, weight_tot);
      hist_lep_Eta_1[i]->Fill(*lep_Eta_1, weight_tot);
      hist_lep_Phi_0[i]->Fill(*lep_Phi_0, weight_tot);
      hist_lep_Phi_1[i]->Fill(*lep_Phi_1, weight_tot);
      hist_lep_dPhi[i]->Fill(abs(*lep_Phi_0-*lep_Phi_1), weight_tot);
      hist_Whmass[i]->Fill(pWhadron.M()/1e3, weight_tot);
      hist_Whpt[i]->Fill(pWhadron.Pt()/1e3, weight_tot);

      hist_mjj[i]->Fill(pmjj.M()/1e3, weight_tot);
      hist_jjpt[i]->Fill(pmjj.Pt()/1e3, weight_tot);

    }
  }  
  return kTRUE;
}

void reco_wqq::SlaveTerminate()
{
}

void reco_wqq::Terminate()
{
  printf("\nTotal Number of Events: %d\n", fNumberOfEvents);

  if(!stoploop){
    string outname="wqq_reco_"+input_name+"_"+comp_name+".root";
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
      hist_jjpt[i]->Write();
      hist_mjj[i]->Write();
      hist_lep_truth_origin[i]->Write();
      hist_lep_truth_origin_0[i]->Write();
      hist_lep_truth_origin_1[i]->Write();

      hist_lep_truth_type[i]->Write();
      hist_lep_truth_type_0[i]->Write();
      hist_lep_truth_type_1[i]->Write();

      hist_jet_truth_origin[i]->Write();
      hist_jet_truth_type[i]->Write();
      
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
    outTree->Write();
    outTree->AutoSave();
  }
  
}
