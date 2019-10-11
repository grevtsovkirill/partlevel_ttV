#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TInterpreter.h"

#include "/Users/grevtsov/Documents/working_files/AtlasStyle/AtlasStyle.C"
#include "/Users/grevtsov/Documents/working_files/AtlasStyle/AtlasUtils.C"

void ATLASLabel(Double_t x,Double_t y,const char* text="",Color_t color=1, Double_t tsize=0.05);
void acc()
{

  gROOT->Reset();
  SetAtlasStyle();

  TFile *file[10][10];
  //file[2] = TFile::Open("Res_ttW.root");
  TLatex latex2; latex2.SetTextSize(0.05); latex2.SetNDC();
  char text[1000];  char text1[1000];  char text2[1000];
  TString atl_lable = "Simulation Internal";//Simulation Internal unapproved
  string lep_flav="nominal"; 
  //sprintf(text1,"#sqrt{s} = 13 TeV, 2b %s 2lSS",lep_flav.c_str());
  sprintf(text2,"");
  
  TH1D* h_var[10][35][10][10];

  //  vector<string> region_names={"0t 1b 3j","0t 2b 3j"}; vector<string>  nj_reg={"2","3"};

  //vector<string> region_names={"0t 1b 4j", "0t 2b 4j","0t 1b 3j", "0t 2b 3j", "1t 1b 3j"};
  vector<string> region_names={"0t 1b 4j", "0t 2b 4j","0t 1b 3j", "0t 2b 3j","1t 1b 3j", "0t=3j","0tg4j","otg3g0b"};
  //			       "1t 1b 4j", "1t 2b 4j","1t 1b 3j", "1t 2b 3j"};
  
  //vector<string> region_names={"0t 1b 4j"}; vector<string>  nj_reg={"0"};
  //vector<string> region_names={"0t 2b 4j"}; vector<string>  nj_reg={"1"};
  //vector<string> region_names={"0t 1b 3j"}; vector<string>  nj_reg={"2"};
  //vector<string> region_names={"0t 2b 3j"}; vector<string>  nj_reg={"3"};

  //taus
  //vector<string> region_names={"1t 1b 4j"}; vector<string>  nj_reg={"4"};
  //vector<string> region_names={"1t 2b 4j"}; vector<string>  nj_reg={"5"};
  //vector<string> region_names={"1t 1b 3j"}; vector<string>  nj_reg={"6"};
  //vector<string> region_names={"1t 2b 3j"}; vector<string>  nj_reg={"7"};
//
  vector<string>  nj_reg={"0","1","2","3","4","5","6","7"};
  vector<string> variable={"DRll01","lep_Pt_0","lep_Pt_1","jet_Pt_4","jet_Pt_5","jet_Pt_6","Bjet_Pt_0","Bjet_Pt_1","min_DRl0j","min_DRl1j","maxEta_ll","HT_jets","HT_leps","HT","nJets","nBtagJets","MET","lep_Eta_0","lep_Eta_1","lep_Phi_0","lep_Phi_1","lep_dPhi","jet_Pt_1","jet_Pt_2","jet_Pt_3"}; //

  vector<string> variable_X={"#Delta R_{l_{0},l_{1}}","Leading lepton #font[52]{p}_{T} [GeV]","Subeading lepton #font[52]{p}_{T} [GeV]",
			     "4th jet #font[52]{p}_{T} [GeV]","5th jet #font[52]{p}_{T} [GeV]","6th jet #font[52]{p}_{T} [GeV]",
			     "Leading #font[52]{b}-jet #font[52]{p}_{T} [GeV]","Subleading #font[52]{b}-jet #font[52]{p}_{T} [GeV]",
			     "#font[52]{min} #Delta R_{l_{0},jet}","#font[52]{min} #Delta R_{l_{1},jet}",
			     "#font[52]{max} |#eta _{l}|",
			     "#font[52]{HT}^{jets} [GeV]","#font[52]{HT}^{lep} [GeV]","#font[52]{HT} [GeV]",
			     "Number of jets","Number of #font[52]{b}-jets","#font[52]{E}_{T}^{miss}","Leading lepton #eta","Subleading lepton #eta","Leading lepton #phi","Subleading lepton #phi","|#Delta #phi ^{ll}|",
			     "1th jet #font[52]{p}_{T} [GeV]","2nd jet #font[52]{p}_{T} [GeV]","3rd jet #font[52]{p}_{T} [GeV]"
}; //

  //vector<string> variable={"lep_Eta_0","lep_Eta_1","lep_Phi_0","lep_Phi_1"};
  //*
  //vector<string> type={"Sherpa","MG","SherpaScaleUp","SherpaScaleDown","SherpaPup","SherpaPdown"};
  //vector<string> type={"Sherpa","MG","SherpaScaleUp","SherpaScaleDown","SherpaNNup","SherpaNNdown"};
  //vector<string> type={"Sherpa","MG","SherpaScaleUp","SherpaScaleDown"};
  vector<string> type={"Sherpa","MG"};
  //vector<string> type={"Sherpa","MG"};
  //vector<string> type={"Sherpa","MG"};
  Int_t color_sample[8]={1,633,601,418,617,799,617,625};
  Int_t linestyle[8]={1,1,7,9,4,10,3,2};
  //*/

  /* MG vars
  vector<string> type={"MG","MGScaleUp","MGScaleDown"};
  Int_t color_sample[6]={633,601,418,617,799,1};
  Int_t linestyle[6]={1,7,9,4,10,1};
  //*/


  char sf_name[1000] ;char band_name[1000] ;
  TLegend* legend[100][100];
  TCanvas * canv[100][100];
  TPad * pad1[100][100];
  TPad * pad2[100][100];
  char canvas_name[1000];char p1_name[1000];  char p2_name[1000]; char o_name[1000];
  int rebin_val=1;

  Double_t xbins[] = {0,10,20,25,30,33,35,37,40,43,50,60};
  Int_t  binnum = sizeof(xbins)/sizeof(Double_t) - 1; 
  string base_name="input/Res";  
  string file_name;

  Double_t norm_hist=1;
  int i=0, j=0;
  cout <<"loop to load histos"<< endl;
  for(int t=0;t<type.size();t++){ 
    file_name=base_name+"_"+type[t]+".root";
    cout<< "file_name  - " << file_name<< endl;
    file[0][t] = TFile::Open(file_name.c_str());

    sprintf(sf_name,"cf2l");   
    h_var[i][j][0][t] = (TH1D *)file[0][t]->Get(sf_name);		 
    h_var[i][j][0][t]->Scale(1/3.);    
  }// file
  

  sprintf(canvas_name,"c_Region");
  gStyle->SetPaintTextFormat("4.2f");
  cout << "canvas_name "<< canvas_name<< endl;
  canv[i][j] = new TCanvas(canvas_name, "", 800, 600);
  legend[i][j] = new TLegend(0.6,0.7,0.9,0.9);
  legend[i][j]->SetTextFont(42);legend[i][j]->SetFillColor(0);  legend[i][j]->SetBorderSize(0); legend[i][j]->SetFillStyle(0);  legend[i][j]->SetTextSize(0.045);

  for(int t=0;t<type.size();t++){
    cout << " - load file: "<< t << " - "<<  type[t] << endl;
    if(t==0){	  
      
      //if (variable[j]!="nBtagJets") h_var[i][j][k][t]->SetYTitle("Normalized");
      //else h_var[i][j][k][t]->SetYTitle("Events");
      h_var[i][j][0][t]->SetYTitle("#sigma_{fid}"); 
      //h_var[i][j][0][t]->SetYTitle("Normalized"); 
      //h_var[i][j][0][t]->SetYTitle("Arbitrary Units"); 
      h_var[i][j][0][t]->SetXTitle(" ");
      h_var[i][j][0][t]->GetYaxis()->SetTitleSize(0.05); 
      h_var[i][j][0][t]->GetYaxis()->SetTitleOffset(0.7); 
      //h_var[i][j][0][t]->GetXaxis()->SetRangeUser(20,500);
      h_var[i][j][0][t]->SetMaximum(h_var[i][j][0][t]->GetMaximum()*1.6);
      h_var[i][j][0][t]->Draw("E1");
    }
    h_var[i][j][0][t]->SetLineColor(color_sample[t]);
    h_var[i][j][0][t]->SetMarkerColor(color_sample[t]);
    h_var[i][j][0][t]->SetMarkerStyle(20+t);
	
    h_var[i][j][0][t]->SetLineWidth(2);
    h_var[i][j][0][t]->SetLineStyle(linestyle[t]);

    if (t==1)   h_var[i][j][0][t]->SetBarOffset(0.25);
    //if(h_var[i][j][0][t]->Integral()>0){
    h_var[i][j][0][t]->Draw("E1histsame");
    h_var[i][j][0][t]->Draw("text12same");
    legend[i][j]->AddEntry(h_var[i][j][0][t],(type[t]+ " ").c_str(),"LP");
  }
  sprintf(text1,"#sqrt{s} = 13 TeV");
  //sprintf(text2,"Variable: %s",variable_X[j].c_str());//+nj_reg[i]+variable[j]
  //sprintf(text2,"2l SS %s ",region_names[i].c_str());
      
  ATLASLabel(0.18,0.87,atl_lable,1,0.05); 
  latex2.DrawLatex(0.18, 0.8, text1);  
  //    latex2.DrawLatex(0.18, 0.73, text2); //latex2.DrawLatex(0.20, 0.7, "Data");
  legend[i][j]->Draw("same");
      

}

void ATLASLabel(Double_t x,Double_t y,const char* text,Color_t color, Double_t tsize)
{
  TLatex l;   l.SetTextSize(tsize);  l.SetNDC();  l.SetTextFont(72);  l.SetTextColor(color);
  double delx = 0.115*696*gPad->GetWh()/(472*gPad->GetWw());  l.DrawLatex(x,y,"ATLAS");
  if (text) {    
    TLatex p;    p.SetNDC();    p.SetTextFont(42);    
    p.SetTextColor(color);    p.SetTextSize(tsize);    p.DrawLatex(x+delx*0.95,y,text);  
  }
}
