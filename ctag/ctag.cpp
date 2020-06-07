#include <TMath.h>


float GetDL1(float pB,float pC,float pL, double fraction){
  float dl1=TMath::Log(pB/( fraction*pC + (1-fraction)*pL ));
  return dl1;
}

int CountJets(vector<float> DL1c ,vector<float> DL1b, float cut, float bWP70 = 3.245){
  int njets = 0;
  for(unsigned int i = 0 ; i < DL1c.size() ; ++i){
    if(DL1c[i]>=cut && DL1b[i]<bWP70)
      ++njets;
  }
  return njets;
}

float GetDistFlav(float tagger,float DL1b,int truthflav, std::vector<int> jet_targets, float bWP70 = 3.245){
  float tagger_corr=0;
  //if(DL1b>bWP70)
  //  return false;
  bool goodFlav=false;
  for( int jet_target : jet_targets){
    
    if(fabs(truthflav) == jet_target)
      goodFlav=true;
    else if(abs(truthflav) < 4 && jet_target <0 )
      goodFlav=true;
  }
  if( goodFlav)
    tagger_corr=tagger;

  return tagger_corr;    
  
}

float getCut(TH1 *histCharm, float effWP = 0.2){
  float cut = 0;  
  for (int ibin=0; ibin<histCharm->GetNbinsX();ibin++){
    if (histCharm->Integral(ibin+1,-1)/histCharm->Integral() <= effWP){
      cut=histCharm->GetBinLowEdge(ibin+1);
      break;
    }
  }
  return cut;
}


void ctag(){

  TFile *f = TFile::Open("Files/ctag_700000_d_test.root");
  TTree *t1 = (TTree*)f->Get("ftagTree");

  double weight_tot;
  std::vector<float> *j_pt ;
  std::vector<float> *score_DL1r_pu ;
  std::vector<float> *score_DL1r_pc ;
  std::vector<float> *score_DL1r_pb ;
  std::vector<float> *truthflav ;
  truthflav = 0;
  j_pt = 0;
  score_DL1r_pu = 0;
  score_DL1r_pc = 0;
  score_DL1r_pb = 0;
  
  t1->SetBranchAddress("weight_tot",&weight_tot);
  t1->SetBranchAddress("j_pt",&j_pt);
  t1->SetBranchAddress("score_DL1r_pu",&score_DL1r_pu);
  t1->SetBranchAddress("score_DL1r_pc",&score_DL1r_pc);
  t1->SetBranchAddress("score_DL1r_pb",&score_DL1r_pb);
  t1->SetBranchAddress("truthflav",&truthflav);

  float fc=0.018;
  float fb=0.28;
  float wp70t=3.245;
  TH1D *hist_dlrc[10][10];
  
  vector<float> fbs = {0.02,0.03};
  vector<int> flav = {0,4,5};
  vector<string> typeflav = {"l","c","b"};
  for(int i=0; i<(int)fbs.size();i++){
    for(int k=0; k<(int)flav.size();k++){
      hist_dlrc[i][k] = new TH1D(("dlrc_"+typeflav[k]+"_"+to_string(i)).c_str(), ("DL1r_{c} "+typeflav[k]+" "+to_string(fbs[i])+";DL1r_{c};Events").c_str(), 75, -10, 15);
    }
  }
  
  for(int i=0; i<t1->GetEntries(); i++){
    t1->GetEntry(i);
    //cout<<"weight_tot: "<<weight_tot<<endl;
    vector<float> dl1r_b;
    vector<float> dl1r_c;
    vector<float> dl1r_c_jets;
    float vdl1r_b=0,vdl1r_c=0, vdl1r_c_jets=0;
    for (int j = 0; j < j_pt->size (); j++){
      vdl1r_b = GetDL1(score_DL1r_pb->at(j),score_DL1r_pc->at(j),score_DL1r_pu->at(j),fc);
      dl1r_b.push_back(vdl1r_b);      
      //dl1r_c.push_back(vdl1r_c);
      if(vdl1r_b<wp70t){  
	//vdl1r_c_jets = GetDistFlav(vdl1r_c,vdl1r_b,truthflav->at(j),{4,44});
	vdl1r_c = GetDL1(score_DL1r_pc->at(j),score_DL1r_pb->at(j),score_DL1r_pu->at(j),fb);

	for(int k=0; k<(int)flav.size();k++){ 
	  if (truthflav->at(j)==flav[k]){	  
	    hist_dlrc[0][k]->Fill(vdl1r_c,weight_tot);
	  }
	}
      }
    }
  }

  hist_dlrc[0][1]->Draw();
  hist_dlrc[0][1]->Draw("histsame");
}
