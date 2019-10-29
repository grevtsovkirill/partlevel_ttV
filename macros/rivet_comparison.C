#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TInterpreter.h"

#include "/Users/grevtsov/Documents/working_files/AtlasStyle/AtlasStyle.C"
#include "/Users/grevtsov/Documents/working_files/AtlasStyle/AtlasUtils.C"

void ATLASLabel(Double_t x,Double_t y,const char* text="",Color_t color=1, Double_t tsize=0.05);
void rivet_comparison(bool norm_xs_plots=false)
{

  gROOT->Reset();
  SetAtlasStyle();

  TFile *file[10][10];
  //file[2] = TFile::Open("Res_ttW.root");
  TLatex latex2; latex2.SetTextSize(0.06); latex2.SetNDC();
  char text[1000];  char text1[1000];  char text2[1000]; char norm_name[1000];
  TString atl_lable = "Internal";// Simulation Preliminary Simulation Internal unapproved
  string lep_flav="nominal"; 
  //sprintf(text1,"#sqrt{s} = 13 TeV, 2b %s 2lSS",lep_flav.c_str());
  sprintf(text2,"");
  
  TH1D* h_var[10][35][10][10];

  //  vector<string> region_names={"0t 1b 3j","0t 2b 3j"}; vector<string>  nj_reg={"2","3"};

  //vector<string> region_names={"0t 1b 4j", "0t 2b 4j","0t 1b 3j", "0t 2b 3j", "1t 1b 3j"};
  vector<string> region_names={"0#tau_{had} 1#font[52]{b} #geq4#font[52]{j}", "0#tau_{had} #geq2#font[52]{b} #geq4#font[52]{j}","0#tau_{had} 1#font[52]{b} 3#font[52]{j}", "0#tau_{had} #geq2#font[52]{b} 3#font[52]{j}","1#tau_{had} #geq1#font[52]{b} #geq3#font[52]{j}"};//, "0t=3j","0tg4j","otg3g0b"};

  vector<string>  nj_reg={"0","1","2","3","4"};//,"5","6","7"};
  vector<string> variable={"DRll01","lep_Pt_0","lep_Pt_1","jet_Pt_4","jet_Pt_5","jet_Pt_6","Bjet_Pt_0","Bjet_Pt_1","min_DRl0j","min_DRl1j","maxEta_ll","HT_jets","HT_leps","HT","nJets","nBtagJets","MET","lep_Eta_0","lep_Eta_1","lep_Phi_0","lep_Phi_1","lep_dPhi","jet_Pt_1","jet_Pt_2","jet_Pt_3"}; //

  vector<string> variable_X={"#Delta R_{l_{0},l_{1}}","Leading lepton #font[52]{p}_{T} [GeV]","Subeading lepton #font[52]{p}_{T} [GeV]",
			     "4th jet #font[52]{p}_{T} [GeV]","5th jet #font[52]{p}_{T} [GeV]","6th jet #font[52]{p}_{T} [GeV]",
			     "Leading #font[52]{b}-jet #font[52]{p}_{T} [GeV]","Subleading #font[52]{b}-jet #font[52]{p}_{T} [GeV]",
			     "#font[52]{min} #Delta R_{l_{0},jet}","#font[52]{min} #Delta R_{l_{1},jet}",
			     "#font[52]{max} |#eta _{l}|",
			     "#font[52]{HT}^{jets} [GeV]","#font[52]{HT}^{lep} [GeV]","#font[52]{HT} [GeV]",
			     "Number of jets","Number of #font[52]{b}-jets","#font[52]{E}_{T}^{miss}","Leading lepton #eta","Subleading lepton #eta","Leading lepton #phi","Subleading lepton #phi","#Delta #phi ^{ll}",
			     "1th jet #font[52]{p}_{T} [GeV]","2nd jet #font[52]{p}_{T} [GeV]","3rd jet #font[52]{p}_{T} [GeV]"
}; //

  //vector<string> variable={"lep_Eta_0","lep_Eta_1","lep_Phi_0","lep_Phi_1"};
  //*
  //vector<string> type={"Sherpa","MG","SherpaScaleUp","SherpaScaleDown","SherpaPup","SherpaPdown"};
  //vector<string> type={"Sherpa","MG","SherpaScaleUp","SherpaScaleDown","SherpaNNup","SherpaNNdown"};
  //vector<string> type={"413008","410155"};
  //vector<string> type={"Rivet: Sherpa","Rivet: MG"};
  vector<string> type={"gen-lev: Sherpa","Rivet: Sherpa"};
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
  cout <<"loop to load histos"<< endl;

  file[0][0] = TFile::Open("input/Res_Sherpa.root");
  file[0][1] = TFile::Open("input/rivet/413008_v1.root");
  //file[0][1] = TFile::Open("input/rivet/410155.root");

  for(int t=0;t<type.size();t++){ 
    file_name=base_name+"_"+type[t]+".root";
    //cout<< "file_name  - " << file_name<< endl;
    //  file[0][t] = TFile::Open(file_name.c_str());
    
    //region
    for(int i=0;i<nj_reg.size();i++){
      //variable
      for(int j=0;j<variable.size();j++){
	
	if(t==0) sprintf(sf_name,"%s_%s",variable[j].c_str(),nj_reg[i].c_str());   
	else if(t==1) sprintf(sf_name,"ttw_ttH/%s_%s",variable[j].c_str(),nj_reg[i].c_str());   
	cout << "sf_name " << sf_name<< " reg = "<< region_names[i]<< ", variable in histo - "<< variable[j]<< endl;
	h_var[i][j][0][t] = (TH1D *)file[0][t]->Get(sf_name);		 
	if (!norm_xs_plots) norm_hist = h_var[i][j][0][t]->GetSumOfWeights();
	else if (norm_xs_plots) norm_hist = 3;
	
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
      pad1[i][j]->SetBottomMargin(0.018);
      pad1[i][j]->SetBorderMode(0);
      pad1[i][j]->SetLeftMargin(0.1);
      pad1[i][j]->SetFillStyle(0);

      pad2[i][j] = new TPad(p2_name, "pad2", 0, 0, 1, 0.3);
      pad2[i][j]->SetTopMargin(0);
      pad2[i][j]->SetLeftMargin(0.1);
      pad2[i][j]->SetBottomMargin(0.3);
      pad2[i][j]->SetFillStyle(4000);
      pad2[i][j]->SetBorderMode(4000);
      //pad2[i][j]->SetFillColorAlpha(kBlue, 0.99);
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
	  //h_var[i][j][0][t]->SetYTitle("Events"); 
	  if (norm_xs_plots) 	  h_var[i][j][0][t]->SetYTitle("#sigma_{fid} [fb]"); 
	  //h_var[i][j][0][t]->SetYTitle("Normalized"); 
	  else if (!norm_xs_plots) h_var[i][j][0][t]->SetYTitle("Arbitrary Units"); 

	  h_var[i][j][0][t]->GetXaxis()->SetLabelOffset(0.015);
	  if(variable[i].find("nJets")!= std::string::npos) h_var[i][j][0][t]->GetXaxis()->SetNdivisions(500, kTRUE);

	  //||variable[i].find("nBtagJets")
	  h_var[i][j][0][t]->SetXTitle((variable_X[j]).c_str());
	  h_var[i][j][0][t]->GetYaxis()->SetTitleSize(0.06); 
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
	
	
	h_var[i][j][3][t]->SetMinimum(0.85);
	h_var[i][j][3][t]->SetMaximum(1.15);
	
	//*/
	//}    
      }//t loop: nominal - variations      
      
      sprintf(text1,"#sqrt{s} = 13 TeV,");
      //sprintf(text2,"Variable: %s",variable_X[j].c_str());//+nj_reg[i]+variable[j]
      sprintf(text2,"2#font[52]{l}SS %s ",region_names[i].c_str());
      
      ATLASLabel(0.18,0.87,atl_lable,1,0.065); 
      latex2.DrawLatex(0.18, 0.8, text1);  
      latex2.DrawLatex(0.18, 0.73, text2); //latex2.DrawLatex(0.20, 0.7, "Data");
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
      
      //      pad1[i][j]->RedrawAxis();
      pad1[i][j]->Update();
      pad1[i][j]->RedrawAxis();

      if (norm_xs_plots) sprintf(norm_name,"f");
      else if (!norm_xs_plots) sprintf(norm_name,"n");
      
      sprintf(o_name,"Plots_gen_rivet_%s/%s.pdf",norm_name,canvas_name);
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