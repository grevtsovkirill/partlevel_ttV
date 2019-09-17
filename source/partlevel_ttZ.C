#define partlevel_ttZ_cxx


#include "partlevel_ttZ.h"
#include <TH2.h>
#include <TStyle.h>
#include <TLorentzVector.h>
#include <math.h>

TH1F *h_cutflow_3l[2];
string input_name="";
/////////////////////////////
// Histograms booking 2lSS ttW:
////////////////////////////
TH1D *hist_DRll01[10];
TH1D *hist_DRll02[10];
TH1D *hist_DRll12[10];
TH1D *hist_lep_Pt_0[10];
TH1D *hist_lep_Pt_1[10];
TH1D *hist_lep_Pt_2[10];
// OS lepton
TH1D *hist_min_DRl0j[10];
TH1D *hist_maxEta_ll[10];
TH1D *hist_HT_jets[10];
TH1D *hist_HT[10];
TH1D *hist_nJets[10]; 
TH1D *hist_nBtagJets[10];
TH1D *hist_MET[10];

vector<string> region_names={"0t 1b", "0t 2b"};
//,"1t 1b"
void partlevel_ttZ::Begin(TTree * /*tree*/)
{
  TString option = GetOption();
}

void partlevel_ttZ::SlaveBegin(TTree * /*tree*/)
{
  stoploop=false;
  nom_w=false; scaleup_w=false;  scaledown_w=false;    
  TString option = GetOption();
  std::cout << "option ="<< option << std::endl;
  std::cout << "variation =";
  input_name=option;

  if(input_name.compare("sherpa")==0 ||input_name.compare("Sherpa")==0 || input_name.compare("MG")==0){
    std::cout << " nominal"<<  std::endl;
    nom_w=true;
  }
  else if (input_name.find("ScaleUp")!= std::string::npos){
    std::cout << " ScaleUp"<<  std::endl;
    scaleup_w=true;
  }
  else if (input_name.find("ScaleDown")!= std::string::npos){
    std::cout << " ScaleDown"<<  std::endl;
    scaledown_w=true;
  }
  else {std::cout << " error - incorrect variation. Stop."<<  std::endl; stoploop=true;}

  
  const std::vector<TString> s_cutDescs =
    {  "Preselections","Nleps=3","|TotCharge|=1","lepPt0>25","lepPt1>15","lepPt2>15","lepCentr","SFZ-veto","SFjpsi-veto","jPt/eta","2j>1b",
       "0t 1b", "0t 2b"};
  //,"1t >1b >2j"
  int Ncuts = s_cutDescs.size();
  h_cutflow_3l[0] = new TH1F("cf3l","cf3l",Ncuts,0,Ncuts);
  h_cutflow_3l[1] = new TH1F("cf3l_raw","cf3l_raw",Ncuts,0,Ncuts);
  for (int bin=1;bin<=Ncuts;++bin){
    h_cutflow_3l[0]->GetXaxis()->SetBinLabel(bin,s_cutDescs[bin-1]);
    h_cutflow_3l[1]->GetXaxis()->SetBinLabel(bin,s_cutDescs[bin-1]);
  }


    Float_t ht_bins[]={0,120,180,240,300,360,440,540,680,900,1500}; Int_t  ht_binnum = sizeof(ht_bins)/sizeof(Float_t) - 1;
    Float_t ht_j_bins[]={0,90,140,180,240,300,380,460,540,650,850,1500}; Int_t  ht_j_binnum = sizeof(ht_j_bins)/sizeof(Float_t) - 1;
    Float_t met_bins[]={0,20,50,80,120,180,300,500,1200}; Int_t  met_binnum = sizeof(met_bins)/sizeof(Float_t) - 1;
    Float_t lep_bins[]={0,20,25,33,45,60,80,110,160,500}; Int_t  lep_binnum = sizeof(lep_bins)/sizeof(Float_t) - 1;
    Float_t dr_max=4.8; Int_t dr_bins=12; 
    for(int i=0; i<(int)region_names.size();i++){
      //hist_DRll01[i] = new TH1D(("DRll01_"+to_string(i)).c_str(), ("#DeltaR_{l_{0},l_{1}} 3l"+region_names[i]+";#DeltaR_{l_{0},l_{1}};Events").c_str(), dr_bins, 0., dr_max);
      hist_lep_Pt_0[i] = new TH1D(("lep_Pt_0_"+to_string(i)).c_str(), ("OS lepton Pt 3l"+region_names[i]+";p_{T}(l_{0})[GeV];Events").c_str(), lep_binnum, lep_bins);//100, 0, 500
      hist_lep_Pt_1[i] = new TH1D(("lep_Pt_1_"+to_string(i)).c_str(), ("Second lepton Pt 3l"+region_names[i]+";p_{T}(l_{1})[GeV];Events").c_str(),lep_binnum, lep_bins);
      hist_lep_Pt_2[i] = new TH1D(("lep_Pt_2_"+to_string(i)).c_str(), ("Third lepton Pt 3l"+region_names[i]+";p_{T}(l_{1})[GeV];Events").c_str(),lep_binnum, lep_bins);
      //os lep
      hist_min_DRl0j[i] = new TH1D(("min_DRl0j_"+to_string(i)).c_str(), ("min #DeltaR_{l_{0},j} 3l"+region_names[i]+";min#DeltaR_{l_{0},j};Events").c_str(), dr_bins, 0., dr_max);
      hist_maxEta_ll[i] = new TH1D(("maxEta_ll_"+to_string(i)).c_str(), ("Max(#|{#eta}_{l}|) 3l"+region_names[i]+";Max(#|{#eta}_{l}|);Events").c_str(), 13, 0, 2.6); // maxEta = max( fabs( lep_Eta_0 ), fabs( lep_Eta_1 ) );
      hist_HT_jets[i] = new TH1D(("HT_jets_"+to_string(i)).c_str(), ( "H_{T}^{jets} 3l"+region_names[i]+";H_{T}^{jets}[GeV];Events").c_str(), ht_j_binnum, ht_j_bins);
      hist_HT[i] = new TH1D(("HT_"+to_string(i)).c_str(), ("H_{T}^{all} 3l"+region_names[i]+";H_{T}^{all}[GeV];Events").c_str(),ht_binnum, ht_bins);// 100, 0., 1000.
      hist_nJets[i] = new TH1D(("nJets_"+to_string(i)).c_str(),("N_{j} 3l"+region_names[i]+";N_{j};Events").c_str(), 8, 1.5, 9.5);
      hist_nBtagJets[i] = new TH1D(("nBtagJets_"+to_string(i)).c_str(),("N_{b} 3l"+region_names[i]+";N_{b};Events").c_str(), 3, 0.5, 3.5);
      hist_MET[i] = new TH1D(("MET_"+to_string(i)).c_str(),("MET 3l"+region_names[i]+";E_{T}^{miss}[GeV];Events").c_str(), met_binnum, met_bins);//100, 0., 1000.
    }

  
}

Bool_t partlevel_ttZ::Process(Long64_t entry)
{
  if(stoploop) return 0;
  //fReader.SetEntry(entry);
  fReader.SetLocalEntry(entry);
  // print some information about the current entry
  if ((entry)%100000 == 0)
    printf("Processing Entry  %llu \n", entry);

  // increase the total number of entries
  ++fNumberOfEvents;

  //weight definitions
  Double_t weight_to_use=1;
  //nom_w=false; scaleup_w=false;  scaledown_w=false;
  if (nom_w) weight_to_use = *weight_mc;
  else if (scaleup_w) weight_to_use = mc_generator_weights[10];
  else if (scaledown_w) weight_to_use = mc_generator_weights[4];
  else return 0;

  
  weight_tot=weight_to_use * *weight_pileup;



  int cf_counter=0;


  //loop over electrons and muons
  nEl = el_pt.GetSize();
  nMu = mu_pt.GetSize();
  const int totleptons = nEl+nMu;
  int trilep_type = 1 + nEl;//  1(mumu) 2(OF) 3(ee)
  //Nlep


  //presel
  h_cutflow_3l[0]->Fill(cf_counter,weight_tot);  h_cutflow_3l[1]->Fill(cf_counter,1);
  cf_counter++;

  //Nleps
  if(totleptons!=3) return 0;
  h_cutflow_3l[0]->Fill(cf_counter,weight_tot);  h_cutflow_3l[1]->Fill(cf_counter,1);
  cf_counter++;

  //define lead/sublead lepton and it's charge
  TLorentzVector lep_4v[3]; float lep_charge[3];float lep_flav[3];
  int lep_it=0;
  if(nEl!=0){
    for (int ie=0;ie<nEl;ie++){
      lep_4v[lep_it].SetPtEtaPhiE(el_pt[ie]/1e3,el_eta[ie],el_phi[ie],el_e[ie]);
      lep_charge[lep_it]=el_charge[ie];
      lep_flav[lep_it]=11;
      lep_it++;
    }
  }

  if(nMu!=0){
    for (int im=0;im<nMu;im++){
      lep_4v[lep_it].SetPtEtaPhiE(mu_pt[im]/1e3,mu_eta[im],mu_phi[im],mu_e[im]);
      lep_charge[lep_it]=mu_charge[im];
      lep_flav[lep_it]=13;
      lep_it++;
    }
  }


  float charges=lep_charge[0]+lep_charge[1]+lep_charge[2];
  //Charge  cout<< " tot charge = "<< charges;
  if(abs(charges)!=1) return 0;
  h_cutflow_3l[0]->Fill(cf_counter,weight_tot);  h_cutflow_3l[1]->Fill(cf_counter,1);
  cf_counter++;

  //for (int i=0;i<lep_it;i++) cout<< i  <<  "   "<< lep_4v[i].Pt()<< " pdg="<<lep_charge[i] *lep_flav[i]<< '\t'<< "mll="<<ll_4v[i].M();
  //cout<<'\n';

  // sort leptons:
  // Version ttH-ML:
  // lepton0 is defined as the one that has opposite sign to the total charge.
  // then lepton1 is the closest to lepton0 in DR
  Int_t idx[3]; Int_t non0idx[2];
  int non0i=0;
  //lep0
  for (int i=0;i<lep_it;i++) {
    if(lep_charge[i]== -charges)
      idx[0]=i;    
    else{
      non0idx[non0i]=i;
      non0i++;
    }
  }
  //cout << "idx0= "<< idx[0]<< ", non0 - "<< non0idx[0] << "  "<< non0idx[1]<<endl;
  int tmp0=non0idx[0];  int tmp1=non0idx[1];  int tmpF=idx[0];
  //cout << "closest to lep0 = ";
  //order lep1 and lep2 accordint to dR wrt lep0
  if (lep_4v[tmpF].DeltaR( lep_4v[tmp0]) > lep_4v[tmpF].DeltaR( lep_4v[tmp1] )){
    //cout <<"(if) "<< non0idx[1]<<endl;
    idx[1]=non0idx[1];
    idx[2]=non0idx[0];
  }
  else{ 
    //cout <<"(else)  "<<non0idx[0]<<endl;
    idx[1]=non0idx[0];
    idx[2]=non0idx[1];

  }

  // Version 2 - orderd by pT 
  //tbd


  // Ordered leps:
  int lep0= idx[0];  int lep1= idx[1];  int lep2= idx[2];


  float l0_pt=lep_4v[lep0].Pt(); 
  float l1_pt=lep_4v[lep1].Pt(); 
  float l2_pt=lep_4v[lep2].Pt(); 
  float l0_eta=lep_4v[lep0].Eta(); 
  float l1_eta=lep_4v[lep1].Eta(); 
  float l2_eta=lep_4v[lep2].Eta(); 
  //  if(lead_lep!=0)     cout <<  " 0  "<< lep_4v[0].Pt()<< "   1 " << lep_4v[1].Pt()<< ",  leading is "<< lead_lep<< endl;
  //if ((abs(lep_4v[lead_lep].Pt()-l0_pt)>0.0001) || (abs(lep_4v[lep1].Pt()-l1_pt)>0.0001)) cout <<  " 0  "<< lep_4v[0].Pt()<< "   1 " << lep_4v[1].Pt()<< ",  leading is "<< lead_lep <<  ",  l0pt="<<l0_pt <<  ",  l1pt="<<l1_pt << endl;


  //lep Pt cuts
  if(lep_4v[lep0].Pt()<25) return 0;  
  h_cutflow_3l[0]->Fill(cf_counter,weight_tot);  h_cutflow_3l[1]->Fill(cf_counter,1);
  cf_counter++;
  if(lep_4v[lep1].Pt()<15) return 0;  
  h_cutflow_3l[0]->Fill(cf_counter,weight_tot);  h_cutflow_3l[1]->Fill(cf_counter,1);
  cf_counter++;
  if(lep_4v[lep0].Pt()<15) return 0;  
  h_cutflow_3l[0]->Fill(cf_counter,weight_tot);  h_cutflow_3l[1]->Fill(cf_counter,1);
  cf_counter++;


  //lep eta cuts
  if(abs(lep_4v[lep0].Eta())>2.5||abs(lep_4v[lep1].Eta())>2.5||abs(lep_4v[lep2].Eta())>2.5) return 0;  
  h_cutflow_3l[0]->Fill(cf_counter,weight_tot);  h_cutflow_3l[1]->Fill(cf_counter,1);
  cf_counter++;



  //Dilepton mass definitions
  TLorentzVector ll_4v[3];
  //0 - 01;
  //1 - 02
  //2 - 12
  bool sf[3]; sf[0]=false;sf[0]=false;sf[1]=false;sf[2]=false;
  ll_4v[0]=lep_4v[lep0]+lep_4v[lep1]; if (abs(lep_flav[lep0])==abs(lep_flav[lep1])) sf[0]=true;
  ll_4v[1]=lep_4v[lep0]+lep_4v[lep2]; if (abs(lep_flav[lep0])==abs(lep_flav[lep2])) sf[1]=true; 
  ll_4v[2]=lep_4v[lep1]+lep_4v[lep2];  if (abs(lep_flav[lep1])==abs(lep_flav[lep2])) sf[2]=true;

  for(int i1=0;i1<3;i1++){
    if (sf[i1]) {
      if( (ll_4v[i1].M()-91.1876e3) < 10e3) return 0;  
      //cout << "SF pair  "<< i1 << " m= "<<ll_4v[i1].M()<<"  lfs:"<<lep_flav[lep0]<<", "<<lep_flav[lep1]<< ", "<<lep_flav[lep2]<< endl;;
    }    
  }
  // Zveto
  h_cutflow_3l[0]->Fill(cf_counter,weight_tot);  h_cutflow_3l[1]->Fill(cf_counter,1);
  cf_counter++;

  for(int i1=0;i1<3;i1++){
    if (sf[i1]) {
      if( ll_4v[i1].M() <12e3) return 0;  
    }    
  }
  // SF mll>12
  h_cutflow_3l[0]->Fill(cf_counter,weight_tot);  h_cutflow_3l[1]->Fill(cf_counter,1);
  cf_counter++;


  float max_eta_tmp0 =  max ( fabs( l0_eta ), fabs( l1_eta ) ); 
  float max_eta=-9999;
  max_eta=max ( fabs(max_eta_tmp0),  fabs( l2_eta ) );

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
  //jPt/eta
  h_cutflow_3l[0]->Fill(cf_counter,weight_tot);  h_cutflow_3l[1]->Fill(cf_counter,1);
  cf_counter++;
  
  //2j>1b 
  if(Njets<2 || Nbjets<1) return 0;
  h_cutflow_3l[0]->Fill(cf_counter,weight_tot);  h_cutflow_3l[1]->Fill(cf_counter,1);
  cf_counter++;

  HTall=HTjet+(l0_pt+l1_pt+l2_pt)*1000;

  // DeltaRs
  // ll 
  float DRll01=-9999;
  //DRll01= sqrt( pow( (lep_4v[lead_lep].Eta()-lep_4v[lep1].Eta()) ,2) + pow ( ( acos( cos( lep_4v[lead_lep].Phi()-lep_4v[lep1].Phi() )  ) ) ,2) );
  DRll01=lep_4v[lep0].DeltaR( lep_4v[lep1] ); // provide SAME results as "by hand"!!!
  //if (deltaR!=DRll01)   cout << DRll01 << ", dR "<< deltaR<< endl;
    //float  DR_LJ_0_tmp  = sqrt(pow((ntup.m_jet_eta->at(index_jets) - ntup.lep_Eta_0), 2.0) + pow((acos(cos(ntup.m_jet_phi->at(index_jets) - ntup.lep_Phi_0))), 2.0));
  
  // l-jet
  vector<float> dRl0j;  vector<float> dRl1j;
  for(int i=0; i<Njets;i++){
    dRl0j.push_back( lep_4v[lep0].DeltaR( jets_vec[i] ) );
    dRl1j.push_back( lep_4v[lep1].DeltaR( jets_vec[i] ) );
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

  sel_array[0]=(Nhtaus == 0 && Nbjets == 1 && Njets >= 2 );  // Region 1 
  sel_array[1]=(Nhtaus == 0 && Nbjets >= 2 && Njets >= 2 );  // Region 2

  float met = *met_met/1000.;

  for(int i=0; i<(int)region_names.size();i++){
    if(sel_array[i]){
      h_cutflow_3l[0]->Fill(cf_counter+i,weight_tot);  h_cutflow_3l[1]->Fill(cf_counter+i,1);
      
      //hist_DRll01[i]->Fill(DRll01, weight_tot);
      hist_lep_Pt_0[i]->Fill(l0_pt, weight_tot);
      hist_lep_Pt_1[i]->Fill(l1_pt, weight_tot);
      hist_lep_Pt_2[i]->Fill(l2_pt, weight_tot);
      hist_min_DRl0j[i]->Fill(min_DRl0j, weight_tot);
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

void partlevel_ttZ::SlaveTerminate()
{
}

void partlevel_ttZ::Terminate()
{
  printf("\nTotal Number of Events: %d\n", fNumberOfEvents);

  if(!stoploop){
    string outname="Res_TTZ_"+input_name+".root";
    TFile hfile(outname.c_str(),"RECREATE"); //,"tHq"
    h_cutflow_3l[0]->Write(); 
    h_cutflow_3l[1]->Write(); 
    
    for(int i=0; i<(int)region_names.size();i++){
      //hist_DRll01[i]->Write();
      hist_lep_Pt_0[i]->Write();
      hist_lep_Pt_1[i]->Write();
      hist_lep_Pt_2[i]->Write();
      hist_min_DRl0j[i]->Write();
      //hist_min_DRl1j[i]->Write();
      hist_maxEta_ll[i]->Write();
      hist_HT_jets[i]->Write();
      hist_HT[i]->Write();
      hist_nJets[i]->Write();
      hist_nBtagJets[i]->Write();
      hist_MET[i]->Write();
    }
    
    fOutput->Write();
  }
  
}
