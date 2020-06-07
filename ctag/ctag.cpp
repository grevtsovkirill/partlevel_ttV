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
  if(DL1b>bWP70)
    return false;
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

void ctag(){

  TFile *f = TFile::Open("Files/ctag_700000_d_test.root");
  TTree *t1 = (TTree*)f->Get("ftagTree");

  double weight_tot;
  std::vector<float> *j_pt ;
  t1->SetBranchAddress("weight_tot",&weight_tot);
  t1->SetBranchAddress("j_pt",&j_pt);
  for(int i=0; i<t1->GetEntries(); i++){
    t1->GetEntry(i);
    cout<<"weight_tot: "<<weight_tot<<endl;
    for (int i = 0; i < j_pt->size (); ++i){
      cout<<"j_pt: "<<j_pt->at(i)<<endl;
      
    }
  }

}
