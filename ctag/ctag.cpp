#include <TMath.h>
#include "/Users/grevtsov/Documents/working_files/AtlasStyle/AtlasStyle.C"
#include "/Users/grevtsov/Documents/working_files/AtlasStyle/AtlasUtils.C"
void ATLASLabel(Double_t x,Double_t y,const char* text="",Color_t color=1, Double_t tsize=0.05);

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
  gROOT->Reset();
  SetAtlasStyle();
  
  TFile *f = TFile::Open("Files/ctag_700000_d.root");
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
  
  vector<float> fbs = {0.28,0.02,0.03};
  vector<int> flav = {0,4,5};
  vector<string> typeflav = {"l","c","b"};
  Int_t color_sample[12]={416,632,600};
  vector<float> dl1r_b[10];
  vector<float> dl1r_c[10];
  vector<float> dl1r_c_part[10][10];
  vector<float> w_vec[10];
  for(int i=0; i<(int)fbs.size();i++){
    for(int k=0; k<(int)flav.size();k++){
      hist_dlrc[i][k] = new TH1D(("dlrc_"+typeflav[k]+"_"+to_string(i)).c_str(), ("DL1r_{c} "+typeflav[k]+" "+to_string(fbs[i])+";DL1r_{c};Events").c_str(), 75, -10, 15);
    }
  }
  hist_dlrc[0][9] = (TH1D*)hist_dlrc[0][0]->Clone();
  
  for(int i=0; i<t1->GetEntries(); i++){
    t1->GetEntry(i);
    //cout<<"weight_tot: "<<weight_tot<<endl;
    //vector<float> dl1r_b;
    float vdl1r_b=0,vdl1r_c=0, vdl1r_c_jets=0;
    for (int j = 0; j < j_pt->size (); j++){
      vdl1r_b = GetDL1(score_DL1r_pb->at(j),score_DL1r_pc->at(j),score_DL1r_pu->at(j),fc);
      dl1r_b[0].push_back(vdl1r_b);      
      //dl1r_c.push_back(vdl1r_c);
      if(vdl1r_b<wp70t){  
	for(int i=0; i<(int)fbs.size();i++){
	  vdl1r_c = GetDL1(score_DL1r_pc->at(j),score_DL1r_pb->at(j),score_DL1r_pu->at(j),fbs[i]);
	  dl1r_c[i].push_back(vdl1r_c);      
	  for(int k=0; k<(int)flav.size();k++){ 
	    if (truthflav->at(j)==flav[k]){	  
	      hist_dlrc[i][k]->Fill(vdl1r_c,weight_tot);
	      dl1r_c_part[i][k].push_back(vdl1r_c);      
	      
	    }// flav selection
	  }//loop over flav
	}//loop over fb cuts
      }//b-veto
    }// loop over all jets in event
  }//evet loop


  // for(int i=0; i<dl1r_c[0].size(); i++){
  //   //hist_dlrc[0][9]->Fill(dl1r_cc[0].at(i),w_vec[0].at(i));
    
  // }  
  TCanvas * canv[100];
  TLegend* legend[100];
  char canvas_name[1000]; char text1[1000]; char text2[1000]; 
  TString atl_lable = "Internal";
  TLatex latex2; latex2.SetTextSize(0.045); latex2.SetNDC();
  for(int i=0; i<1;i++){
    
    sprintf(text1,"c eff =0.2, fb = %0.3f",fbs[i]);
    sprintf(text2,"cut = %0.2f",getCut(hist_dlrc[i][1]));
    sprintf(canvas_name,"c_fbs_%d",i);
    canv[i] = new TCanvas(canvas_name, "", 800, 600);
    canv[i]->SetLogy();
    legend[i] = new TLegend(0.67,0.6,0.9,0.9);
    legend[i]->SetTextFont(42);legend[i]->SetFillColor(0);  legend[i]->SetBorderSize(0); legend[i]->SetFillStyle(0);  legend[i]->SetTextSize(0.05);
    cout <<getCut(hist_dlrc[0][1])<< endl;

    for(int k=0; k<(int)typeflav.size();k++){             
      if(k==0){
	hist_dlrc[i][k]->Draw("hist");
      }
      hist_dlrc[i][k]->Draw("histsame");
      hist_dlrc[i][k]->SetLineColor(color_sample[k]);
      legend[i]->AddEntry(hist_dlrc[i][k],(typeflav[k]).c_str(),"l");
    }
    ATLASLabel(0.18,0.87,atl_lable,1,0.05);
    latex2.DrawLatex(0.18, 0.8, text1);
    latex2.DrawLatex(0.18, 0.73, text2);
    legend[i]->Draw("same");
  }

  cout << CountJets(dl1r_c[0] ,dl1r_b[0], getCut(hist_dlrc[0][1]))<<endl;

  cout << CountJets(dl1r_c_part[0][1] ,dl1r_b[0], getCut(hist_dlrc[0][1]))<<endl;
  cout << CountJets(dl1r_c_part[0][1] ,dl1r_b[0], -10)<<endl;
  
  cout << CountJets(dl1r_c_part[0][2] ,dl1r_b[0], getCut(hist_dlrc[0][1]))<<endl;
  cout << CountJets(dl1r_c_part[0][2] ,dl1r_b[0], -10)<<endl;
  cout << CountJets(dl1r_c_part[0][0] ,dl1r_b[0], getCut(hist_dlrc[0][1]))<<endl;
  cout << CountJets(dl1r_c_part[0][0] ,dl1r_b[0], -10)<<endl;
    
}

void ATLASLabel(Double_t x,Double_t y,const char* text,Color_t color, Double_t tsize)
{
  TLatex l;   l.SetTextSize(tsize);  l.SetNDC();  l.SetTextFont(72);  l.SetTextColor(color);
  double delx = 0.115*696*gPad->GetWh()/(472*gPad->GetWw());  l.DrawLatex(x,y,"ATLAS");
  if (text) {
    TLatex p;    p.SetNDC();    p.SetTextFont(42);
    p.SetTextColor(color);    p.SetTextSize(tsize);    p.DrawLatex(x+delx*0.9,y,text);
  }
}

