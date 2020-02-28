#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TInterpreter.h"

#include "/Users/grevtsov/Documents/working_files/AtlasStyle/AtlasStyle.C"
#include "/Users/grevtsov/Documents/working_files/AtlasStyle/AtlasUtils.C"

void ATLASLabel(Double_t x,Double_t y,const char* text="",Color_t color=1, Double_t tsize=0.05);
void qqw(string sampleversion = "xs",  bool do_stack=true)
{
  gROOT->Reset();
  SetAtlasStyle();

  TFile *file[10][10];
  TLatex latex2; latex2.SetTextSize(0.06); latex2.SetNDC();
  char sf_name[1000] ;char band_name[1000] ;
  char text[1000];  char text1[1000];  char text2[1000]; 
  TString atl_lable = "Internal";
  TLegend* legend[100][100];
  TCanvas * canv[100][100];
  TPad * pad1[100][100];
  TPad * pad2[100][100];
  char canvas_name[1000];char p1_name[1000];  char p2_name[1000]; char o_name[1000];
  TH1D* h_var[10][35][20][50];
  TH1D* h_allMC[10][35][20][50];
  
  vector<string>  nj_reg={"0","1"};//
  vector<string> region_names={"2b4j","2b4j>0c"};
  //vector<string> variable={"nJets"};//,"Whmass","Whpt","DRlb0","DRlb1","DRlb2","DRlb3"};
  vector<string> variable={"nJets","Whmass","Whpt","DRlb0","DRlb1"};
  //,"DRlb2","DRlb3"
  //vector<string> variable={"nJets","DRll01","Whmass","lep_Pt_0","lep_Pt_1","jet_Pt_4","jet_Pt_5","jet_Pt_6","Bjet_Pt_0","Bjet_Pt_1","min_DRl0j","min_DRl1j","maxEta_ll","HT_jets","HT_leps","HT","nBtagJets","MET","lep_Eta_0","lep_Eta_1","lep_Phi_0","lep_Phi_1","lep_dPhi","jet_Pt_1","jet_Pt_2","jet_Pt_3"}; //
  vector<string> variable_X={"Number of jets","m_{Wqq}","p_T^{Wqq}",
			     "min#Delta R_{l_{0},b}","min#Delta R_{l_{1},b}",
			     //"#Delta R_{l_{1},b_{0}}","#Delta R_{l_{1},b_{1}}",
			     "#Delta R_{l_{0},l_{1}}","Leading lepton #font[52]{p}_{T} [GeV]","Subeading lepton #font[52]{p}_{T} [GeV]",
			     "4th jet #font[52]{p}_{T} [GeV]","5th jet #font[52]{p}_{T} [GeV]","6th jet #font[52]{p}_{T} [GeV]",
			     "Leading #font[52]{b}-jet #font[52]{p}_{T} [GeV]","Subleading #font[52]{b}-jet #font[52]{p}_{T} [GeV]",
			     "#font[52]{min} #Delta R_{l_{0},jet}","#font[52]{min} #Delta R_{l_{1},jet}",
			     "#font[52]{max} |#eta _{l}|",
			     "#font[52]{HT}^{jets} [GeV]","#font[52]{HT}^{lep} [GeV]","#font[52]{HT} [GeV]",
			     "Number of #font[52]{b}-jets","#font[52]{E}_{T}^{miss}","Leading lepton #eta","Subleading lepton #eta","Leading lepton #phi","Subleading lepton #phi","#Delta #phi ^{ll}",
			     "1th jet #font[52]{p}_{T} [GeV]","2nd jet #font[52]{p}_{T} [GeV]","3rd jet #font[52]{p}_{T} [GeV]"  };  
  

  //'413008_ttw','410472_ttbar','410156_ttZnunu','410157_ttZqq','410218_ttee','410219_ttmumu','410220_tttautau
  //type
  //file[0][0] = TFile::Open("input/Wqq/ttwqq1.root");
  //file[0][1] = TFile::Open("input/Wqq/ttzqq.root");
  //vector<string> type={"413008_ttw","410472_ttbar","410156_ttZnunu","410157_ttZqq","410218_ttee","410219_ttmumu","410220_tttautau"};
  std::map<std::string, std::string> sample_map;
  sample_map["ttW"]= "413008";
  sample_map["ttbar"]= "410472";
  sample_map["ttZqq"]= "410157";
  sample_map["ttZnunu"]= "410156";
  sample_map["ttZee"]= "410218";
  sample_map["ttZmumu"]= "410219";
  sample_map["ttZtautau"]= "410220";
  
  Int_t color_sample[8]={632,861,921,922,617,860,0,868};//625
  Int_t linestyle[8]={1, 1, 1, 1,  1, 1,1,1};
  vector<string> type={"ttW","ttZqq","ttZnunu","ttZee","ttZmumu","ttZtautau","ttbar"};
  
  string pathversion = "v2_ctag_minDRlb"; //v1_e2b_lJqq

  string leg_type="f";
  
  bool do_log;

  //=false;
  
  if (sampleversion != "norm")
    do_log=true;
  
  Double_t norm_hist=0;
  for(int t=0;t<type.size();t++){
    //region
    file[0][t] = TFile::Open(("input/Wqq/"+pathversion+"/wqq_"+sample_map[type[t]]+"_xs.root").c_str()); //+sampleversion+
    for(int i=0;i<nj_reg.size();i++){
      //variable
      for(int j=0;j<variable.size();j++){
	sprintf(sf_name,"%s_%s",variable[j].c_str(),nj_reg[i].c_str());
	cout << "h_var["<<i<<"]["<<j<<"][0]["<<t<<"] sf_name " << sf_name<< " , variable in histo - "<< variable[j]<< endl;
	h_var[i][j][0][t] = (TH1D *)file[0][t]->Get(sf_name);			  
	norm_hist = h_var[i][j][0][t]->GetSumOfWeights();
 	//h_var[i][j][0][t]->Scale(xs[t]);
	if (sampleversion == "norm") h_var[i][j][0][t]->Scale(1/norm_hist);
     }
    }    
  }


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
      pad1[i][j]->Draw();
      pad2[i][j]->Draw();
      
      legend[i][j] = new TLegend(0.5,0.6,0.9,0.9);
      legend[i][j]->SetTextFont(42);legend[i][j]->SetFillColor(0);  legend[i][j]->SetBorderSize(0); legend[i][j]->SetFillStyle(0);  legend[i][j]->SetTextSize(0.05);
      
      THStack *hs = new THStack("hs","Stacked 1D histograms");

      pad1[i][j]->cd();

      for(int t=0;t<type.size();t++){
	cout << " - load file: "<< t << " - "<<  type[t] << endl;
	if(t==0){	  
	  sprintf(sf_name,"total_%s_%s_%s",variable[j].c_str(),nj_reg[i].c_str(),type[t].c_str());   
	  h_allMC[i][j][0][0] = (TH1D*)h_var[i][j][0][t]->Clone();

	  if(!do_stack){
	    if (sampleversion == "norm")
	      h_var[i][j][0][t]->SetYTitle("Normalized");
	    else
	      h_var[i][j][0][t]->SetYTitle("Events");  
	    leg_type="LP";
	    h_var[i][j][0][t]->GetXaxis()->SetLabelOffset(0.015);
	    h_var[i][j][0][t]->SetXTitle((variable_X[j]).c_str());
	    h_var[i][j][0][t]->GetYaxis()->SetTitleSize(0.06); 
	    h_var[i][j][0][t]->GetYaxis()->SetTitleOffset(0.7); 
	    h_var[i][j][0][t]->SetMaximum(h_var[i][j][0][t]->GetMaximum()*1.6); //1.6
	    h_var[i][j][0][t]->Draw("E1");
	  }

	}
	else{
	  h_allMC[i][j][0][0]->Add(h_var[i][j][0][t]);	  
	}
	
	h_var[i][j][0][t]->SetLineColor(color_sample[t]);
	h_var[i][j][0][t]->SetMarkerColor(color_sample[t]);
	h_var[i][j][0][t]->SetMarkerStyle(20+t);
	if(do_stack)	h_var[i][j][0][t]->SetFillColor(color_sample[t]);
	if(type[t]=="ttbar"){
	  h_var[i][j][0][t]->SetLineColor(1);
	  h_var[i][j][0][t]->SetMarkerColor(1);
	}

	if(!do_stack){
	  h_var[i][j][0][t]->SetLineWidth(2);
	  h_var[i][j][0][t]->SetLineStyle(linestyle[t]);
	  h_var[i][j][0][t]->Draw("E1histsame");
	}
	hs->Add(h_var[i][j][0][t]);
	legend[i][j]->AddEntry(h_var[i][j][0][t],(type[t]+ " ").c_str(),leg_type.c_str());		

	//
	if(!do_stack){
	  sprintf(sf_name,"ratio_%s_%s_%s",variable[j].c_str(),nj_reg[i].c_str(),type[t].c_str());   
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
	  h_var[i][j][3][t]->SetMinimum(0.59);
	  h_var[i][j][3][t]->SetMaximum(1.41);

	}
	
      }

      if(do_stack){
	hs->Draw("hist");
	
	hs->GetXaxis()->SetLabelOffset(0.015);
	hs->GetXaxis()->SetTitle((variable_X[j]).c_str());
	hs->GetYaxis()->SetTitleSize(0.06); 
	hs->GetYaxis()->SetTitleOffset(0.7); 
	
	if(do_log){
	  pad1[i][j]->SetLogy();
	  hs->SetMaximum(hs->GetMaximum()*1e2); 
	  hs->SetMinimum(1e-1); 
	}
	else
	  hs->SetMaximum(hs->GetMaximum()*1.6); 
	
	
	legend[i][j]->AddEntry(h_allMC[i][j][0][0],"MC (tbr by data) ","P");
	h_allMC[i][j][0][0]->Draw("E1same");
	
	if (sampleversion == "norm")
	  hs->GetYaxis()->SetTitle("Normalized");
	else
	  hs->GetYaxis()->SetTitle("Events");  
      }
      
      sprintf(sf_name,"ratio_%s_%s",variable[j].c_str(),nj_reg[i].c_str());   
      h_allMC[i][j][0][1] = (TH1D*)h_allMC[i][j][0][0]->Clone();
      h_allMC[i][j][0][1]->Divide(h_allMC[i][j][0][0]);
      h_allMC[i][j][0][1]->SetXTitle((variable_X[j]).c_str());
      h_allMC[i][j][0][1]->GetXaxis()->SetTitleSize(0.14); 
      h_allMC[i][j][0][1]->GetYaxis()->SetTitleSize(0.14); 
      h_allMC[i][j][0][1]->GetXaxis()->SetTitleOffset(1.); 
      h_allMC[i][j][0][1]->GetYaxis()->SetTitleOffset(0.33); 
      h_allMC[i][j][0][1]->GetXaxis()->SetLabelSize(0.14);
      h_allMC[i][j][0][1]->GetYaxis()->SetLabelSize(0.14);
      h_allMC[i][j][0][1]->GetYaxis()->SetNdivisions(405, kTRUE);      
      h_allMC[i][j][0][1]->GetXaxis()->SetTickLength(0.1); 
      h_allMC[i][j][0][1]->SetLineWidth(2);
      h_allMC[i][j][0][1]->SetMinimum(0.88);
      h_allMC[i][j][0][1]->SetMaximum(1.12);
    
      sprintf(text1,"#sqrt{s} = 13 TeV,");
      sprintf(text2,"2#font[52]{l}OS Wqq %s",region_names[i].c_str()); //
      
      ATLASLabel(0.18,0.87,atl_lable,1,0.065); 
      latex2.DrawLatex(0.18, 0.8, text1);  
      latex2.DrawLatex(0.18, 0.73, text2); //latex2.DrawLatex(0.20, 0.7, "Data");
      legend[i][j]->Draw("same");


      pad2[i][j]->cd();
      //*
      if(do_stack){
	h_allMC[i][j][0][1]->SetYTitle("No sense Ratio");
	h_allMC[i][j][0][1]->Draw("E1");
	h_allMC[i][j][0][1]->Draw("histsame");

      }
      else{
	h_var[i][j][3][0]->SetMinimum(0.68);
	h_var[i][j][3][0]->SetMaximum(1.32);
	h_var[i][j][3][0]->SetYTitle("Ratio to ttW");
	h_var[i][j][3][0]->Draw("hist");
	for(int t=1;t<type.size();t++){
	  h_var[i][j][3][t]->SetLineWidth(3);
	  h_var[i][j][3][t]->SetLineColor(color_sample[t]);
	  h_var[i][j][3][t]->SetMarkerColor(color_sample[t]);
	  if(type[t]=="ttbar"){
	    h_var[i][j][3][t]->SetLineColor(1);
	    h_var[i][j][3][t]->SetMarkerColor(1);
	  }
	  h_var[i][j][3][t]->SetLineStyle(linestyle[t]);
	  h_var[i][j][3][t]->Draw("histsame");
	
	}
	
      }
	

      
      sprintf(o_name,"WqqPlots/v1_shapes_full/%s.pdf",canvas_name);   
      canv[i][j]->Print(o_name);
  
    }
  }

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
