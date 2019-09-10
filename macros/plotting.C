#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TInterpreter.h"

#include "/Users/grevtsov/Documents/working_files/AtlasStyle/AtlasStyle.C"
#include "/Users/grevtsov/Documents/working_files/AtlasStyle/AtlasUtils.C"

void ATLASLabel(Double_t x,Double_t y,const char* text="",Color_t color=1, Double_t tsize=0.05);
void plotting()
{

  gROOT->Reset();
  SetAtlasStyle();

  TFile *file[10][10];
  //file[2] = TFile::Open("Res_ttW.root");
  TLatex latex2; latex2.SetTextSize(0.06); latex2.SetNDC();
  char text[1000];  char text1[1000];  char text2[1000];
  TString atl_lable = "Internal";
  string lep_flav="nominal"; 
  //sprintf(text1,"#sqrt{s} = 13 TeV, 2b %s 2lSS",lep_flav.c_str());
  sprintf(text2,"");
  
  TH1D* h_var[5][35][5][5];

  //  vector<string> region_names={"0t 1b 3j","0t 2b 3j"}; vector<string>  nj_reg={"2","3"};

  //vector<string> region_names={"0t 1b 4j", "0t 2b 4j","0t 1b 3j", "0t 2b 3j", "1t 1b 3j"};
  vector<string> region_names={"0t 1b 4j", "0t 2b 4j","0t 1b 3j", "0t 2b 3j","1t 1b 3j"};
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
  vector<string>  nj_reg={"0","1","2","3","4"};
  vector<string> variable={"DRll01","lep_Pt_0","lep_Pt_1","jet_Pt_4","jet_Pt_5","jet_Pt_6","Bjet_Pt_0","Bjet_Pt_0","min_DRl0j","min_DRl1j","maxEta_ll","HT_jets","HT_leps","HT","nJets","nBtagJets","MET"}; //

  //*
  vector<string> type={"Sherpa","MG","SherpaScaleUp","SherpaScaleDown"};
  Int_t color_sample[6]={1,633,601,418,617,799};
  Int_t linestyle[6]={1,1,7,9,4,10};
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
  //string base_name="input/mc_histos_ttW"; //reco  
  string base_name="input/Res";  
  string file_name;

  Double_t norm_hist=1;
  cout <<"loop to load histos"<< endl;
  for(int t=0;t<type.size();t++){ 
    file_name=base_name+"_"+type[t]+".root";
    cout<< "file_name  - " << file_name<< endl;
    file[0][t] = TFile::Open(file_name.c_str());
    
    //region
    for(int i=0;i<nj_reg.size();i++){
      //variable
      for(int j=0;j<variable.size();j++){
	sprintf(sf_name,"%s_%s",variable[j].c_str(),nj_reg[i].c_str());   
	cout << "sf_name " << sf_name<< " reg = "<< region_names[i]<< ", variable in histo - "<< variable[j]<< endl;
	h_var[i][j][0][t] = (TH1D *)file[0][t]->Get(sf_name);		 
	norm_hist = h_var[i][j][0][t]->GetSumOfWeights();
	h_var[i][j][0][t]->Scale(1/norm_hist);
	norm_hist=1;
      }//variable - j
    }// region - i
  }// file
  
  cout <<"histos are load "<< endl;
  cout << "=============================="<<'\n'<<'\n'<<'\n'<<"loop to make plots using loaded histos"<< endl;
  for(int i=0;i<nj_reg.size();i++){
    for(int j=0;j<variable.size();j++){
      
      sprintf(canvas_name,"c_Region_%s_%s",nj_reg[i].c_str(), variable[j].c_str() );
      cout << "canvas_name "<< canvas_name<< endl;
      canv[i][j] = new TCanvas(canvas_name, "", 800, 600);
      
      sprintf(p1_name,"p1_%s_%s",nj_reg[i].c_str(),variable[j].c_str() );
      sprintf(p2_name,"p2_%s_%s",nj_reg[i].c_str(),variable[j].c_str() );

      pad1[i][j] = new TPad(p1_name, "pad1", 0, 0.32, 1, 1);
      pad2[i][j] = new TPad(p2_name, "pad2", 0, 0, 1, 0.3);
      pad1[i][j]->SetBottomMargin(0.01);
      pad1[i][j]->SetBorderMode(0);
      pad1[i][j]->SetLeftMargin(0.1);
      pad2[i][j]->SetTopMargin(0);
      pad2[i][j]->SetLeftMargin(0.1);
      pad2[i][j]->SetBottomMargin(0.3);
      //pad1[i][j]->SetLogx(); 
      //pad2[i][j]->SetLogx(); 
      pad1[i][j]->Draw();
      pad2[i][j]->Draw();
      
      pad1[i][j]->cd();             

      legend[i][j] = new TLegend(0.6,0.7,0.9,0.9);
      legend[i][j]->SetTextFont(42);legend[i][j]->SetFillColor(0);  legend[i][j]->SetBorderSize(0); legend[i][j]->SetFillStyle(0);  legend[i][j]->SetTextSize(0.05);
      

      for(int t=0;t<type.size();t++){
	cout << " - load file: "<< t << " - "<<  type[t] << endl;
	if(t==0){	  

	  //if (variable[j]!="nBtagJets") h_var[i][j][k][t]->SetYTitle("Normalized");
	  //else h_var[i][j][k][t]->SetYTitle("Events");
	  h_var[i][j][0][t]->SetYTitle("Normalized");
	  h_var[i][j][0][t]->SetXTitle((variable[j]).c_str());
	  h_var[i][j][0][t]->GetYaxis()->SetTitleSize(0.06); 
	  h_var[i][j][0][t]->GetYaxis()->SetTitleOffset(0.7); 
	  //h_var[i][j][0][t]->GetXaxis()->SetRangeUser(20,500);
	  h_var[i][j][0][t]->SetMaximum(h_var[i][j][0][t]->GetMaximum()*1.5);
	  h_var[i][j][0][t]->Draw("E1");
	}
	
	h_var[i][j][0][t]->SetLineColor(color_sample[t]);
	h_var[i][j][0][t]->SetMarkerColor(color_sample[t]);
	h_var[i][j][0][t]->SetMarkerStyle(20+t);
	
	h_var[i][j][0][t]->SetLineWidth(2);
	h_var[i][j][0][t]->SetLineStyle(linestyle[t]);
	//if(h_var[i][j][0][t]->Integral()>0){
	h_var[i][j][0][t]->Draw("E1histsame");
	legend[i][j]->AddEntry(h_var[i][j][0][t],(type[t]+ " ").c_str(),"LP");
	//}//
	sprintf(sf_name,"ratio_%s_%s_%s",variable[j].c_str(),nj_reg[i].c_str(),type[t].c_str());   
	cout<< "ratio name "<< sf_name<< endl;
	
	//sprintf(sf_name,"ratio_%s_%s",variable[j].c_str(),nj_reg[i].c_str());   
	//*
	
	// i region, j - variable, t -nom/variation, 
	h_var[i][j][3][t] = (TH1D*) h_var[i][j][0][t]->Clone(sf_name);
	h_var[i][j][3][t]->Divide(h_var[i][j][0][0]);
	
	h_var[i][j][3][t]->GetXaxis()->SetTitleSize(0.14); 
	h_var[i][j][3][t]->GetYaxis()->SetTitleSize(0.14); 
	h_var[i][j][3][t]->GetXaxis()->SetTitleOffset(1.); 
	h_var[i][j][3][t]->GetYaxis()->SetTitleOffset(0.33); 
	h_var[i][j][3][t]->GetXaxis()->SetLabelSize(0.14);
	h_var[i][j][3][t]->GetYaxis()->SetLabelSize(0.14);
	h_var[i][j][3][t]->GetYaxis()->SetNdivisions(405, kTRUE);
	
	h_var[i][j][3][t]->GetXaxis()->SetTickLength(0.1); 
	h_var[i][j][3][t]->SetLineWidth(2);
	
	
	h_var[i][j][3][t]->SetMinimum(0.7);
	h_var[i][j][3][t]->SetMaximum(1.3);
	
	//*/
	//}    
      }//t loop: nominal - variations      
      
      sprintf(text1,"#sqrt{s} = 13 TeV, 2lSS%s ",region_names[i].c_str());
      sprintf(text2,"Variable: %s",variable[j].c_str());//+nj_reg[i]+variable[j]
      
      ATLASLabel(0.2,0.87,atl_lable,1,0.065); latex2.DrawLatex(0.20, 0.8, text1);  latex2.DrawLatex(0.20, 0.73, text2); //latex2.DrawLatex(0.20, 0.7, "Data");
      legend[i][j]->Draw("same");
      
      pad2[i][j]->cd();
      //*

      h_var[i][j][3][0]->SetYTitle("Ratio to Sherpa");
      h_var[i][j][3][0]->Draw("hist");
      for(int t=1;t<type.size();t++){
	h_var[i][j][3][t]->SetLineWidth(3);
	h_var[i][j][3][t]->SetLineColor(color_sample[t]);
	h_var[i][j][3][t]->SetMarkerColor(color_sample[t]);
	h_var[i][j][3][t]->SetLineStyle(linestyle[t]);
	h_var[i][j][3][t]->Draw("histsame");
	
      }
      
      sprintf(o_name,"Plots_pl_87_v3/%s.pdf",canvas_name);
      //sprintf(o_name,"Plots_MGvar_1/%s.pdf",canvas_name);
      canv[i][j]->Print(o_name);
      //*/
    }//j loop: variable
  }//i loop: region 0-7
  
  
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
