#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TInterpreter.h"

#include "/Users/grevtsov/Documents/working_files/AtlasStyle/AtlasStyle.C"
#include "/Users/grevtsov/Documents/working_files/AtlasStyle/AtlasUtils.C"

void ATLASLabel(Double_t x,Double_t y,const char* text="",Color_t color=1, Double_t tsize=0.05);
void rivet_weights_compute(bool norm_xs_plots=false)
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
  
  TH1D* h_var[10][35][20][10];

  //  vector<string> region_names={"0t 1b 3j","0t 2b 3j"}; vector<string>  nj_reg={"2","3"};

  //vector<string> region_names={"0t 1b 4j", "0t 2b 4j","0t 1b 3j", "0t 2b 3j", "1t 1b 3j"};
  vector<string> region_names={"0#tau_{had} 1#font[52]{b} #geq4#font[52]{j}", "0#tau_{had} #geq2#font[52]{b} #geq4#font[52]{j}","0#tau_{had} 1#font[52]{b} 3#font[52]{j}", "0#tau_{had} #geq2#font[52]{b} 3#font[52]{j}","1#tau_{had} #geq1#font[52]{b} #geq3#font[52]{j}"};//, "0t=3j","0tg4j","otg3g0b"};

  vector<string>  nj_reg={"0","1","2","3","4"};//,"5","6","7"};
  //vector<string>  nj_reg={"0"};
  //vector<string> variable={"nJets","DRll01"};//,"DRll01","lep_Pt_0","lep_Pt_1","jet_Pt_4","jet_Pt_5","jet_Pt_6","Bjet_Pt_0","Bjet_Pt_1","min_DRl0j","min_DRl1j","maxEta_ll","HT_jets","HT_leps","HT","nBtagJets","MET","lep_Eta_0","lep_Eta_1","lep_Phi_0","lep_Phi_1","lep_dPhi","jet_Pt_1","jet_Pt_2","jet_Pt_3"}; //
  vector<string> variable={"nJets","DRll01","lep_Pt_0","lep_Pt_1","jet_Pt_4","jet_Pt_5","jet_Pt_6","Bjet_Pt_0","Bjet_Pt_1","min_DRl0j","min_DRl1j","maxEta_ll","HT_jets","HT_leps","HT","nBtagJets","MET","lep_Eta_0","lep_Eta_1","lep_Phi_0","lep_Phi_1","lep_dPhi","jet_Pt_1","jet_Pt_2","jet_Pt_3"}; //

  vector<string> variable_X={"Number of jets","#Delta R_{l_{0},l_{1}}","Leading lepton #font[52]{p}_{T} [GeV]","Subeading lepton #font[52]{p}_{T} [GeV]",
			     "4th jet #font[52]{p}_{T} [GeV]","5th jet #font[52]{p}_{T} [GeV]","6th jet #font[52]{p}_{T} [GeV]",
			     "Leading #font[52]{b}-jet #font[52]{p}_{T} [GeV]","Subleading #font[52]{b}-jet #font[52]{p}_{T} [GeV]",
			     "#font[52]{min} #Delta R_{l_{0},jet}","#font[52]{min} #Delta R_{l_{1},jet}",
			     "#font[52]{max} |#eta _{l}|",
			     "#font[52]{HT}^{jets} [GeV]","#font[52]{HT}^{lep} [GeV]","#font[52]{HT} [GeV]",
			     "Number of #font[52]{b}-jets","#font[52]{E}_{T}^{miss}","Leading lepton #eta","Subleading lepton #eta","Leading lepton #phi","Subleading lepton #phi","#Delta #phi ^{ll}",
			     "1th jet #font[52]{p}_{T} [GeV]","2nd jet #font[52]{p}_{T} [GeV]","3rd jet #font[52]{p}_{T} [GeV]"
}; //

  //vector<string> variable={"lep_Eta_0","lep_Eta_1","lep_Phi_0","lep_Phi_1"};
  //*
  //vector<string> type={"Sherpa","MG","SherpaScaleUp","SherpaScaleDown","SherpaPup","SherpaPdown"};
  //vector<string> type={"Sherpa","MG","SherpaScaleUp","SherpaScaleDown","SherpaNNup","SherpaNNdown"};
  //vector<string> type={"413008","410155"};
  //vector<string> type={"ATLAS Sherpa 221","ATLAS aMC@NLO","CMS aMC@NLO FxFx","ATLAS Sherpa muR2muF2" ,"ATLAS Sherpa muR0.5muF0.5","ATLAS Sherpa 228"};
  //vector<string> type={"ATLAS Sherpa 221","Up","Down"};
  //vector<string> type={"Rivet Chris","Rivet Kirill","AnalysisTop"};
  //vector<string> type={"Sherpa 221","aMC@NLO","Sherpa 228","S221 muR2muF2" ,"S221 muR0.5muF0.5" };
  //vector<string> type={"AnalysisTop","Rivet"};
  //vector<string> type={"gen-lev: MG","Rivet: MG"};
  //vector<string> type={"Sherpa","MG"}; 
  //ATLAS - CMS comparison
  Int_t color_sample[8]={864,921,433,922,868,594,625,617};// 860, 625  red 633
  //AT-rivet Sherpa
  //Int_t color_sample[8]={1,633,601,920,922,799,617,625};
  //AT-rivet MG
  //Int_t color_sample[8]={601,418,617,799,617,625,1,633};

  //Int_t linestyle[8]={1,1,7,9,4,10,3,2};
  //                 AS AM cM, Su, Sd

  Int_t linestyle[8]={1, 7, 5, 3,  4, 2,3,2};
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
  TPad * pad3[100][100];
  char canvas_name[1000];char p1_name[1000];  char p2_name[1000]; char p3_name[1000]; char o_name[1000];
  int rebin_val=1;

  Double_t xbins[] = {0,10,20,25,30,33,35,37,40,43,50,60};
  Int_t  binnum = sizeof(xbins)/sizeof(Double_t) - 1; 
  string base_name="input/Res";  
  string file_name;

  Double_t norm_hist=1;
  vector<string> env_type={"tot Up","tot Down","rf:05+2 up" ,"rf:05+2 down" };
  Double_t env_col[4]={418,409,618,612};
  vector<string> type={"Nominal","R05F05","R05F1","R1F05","R2F1","R1F2","R2F2" };
  vector<string> type_path={"nom"
			    ,"MUR0.5_MUF0.5_PDF261000_PSMUR0.5_PSMUF0.5"
			    ,"MUR0.5_MUF1_PDF261000_PSMUR0.5_PSMUF1"
			    ,"MUR1_MUF0.5_PDF261000_PSMUR1_PSMUF0.5"
			    ,"MUR2_MUF1_PDF261000_PSMUR2_PSMUF1"
			    ,"MUR1_MUF2_PDF261000_PSMUR1_PSMUF2"
			    ,"MUR2_MUF2_PDF261000_PSMUR2_PSMUF2"
  };

  /*
    s228_ttw_20.01/700000_mePS_scale.root :
    MUR0.5_MUF0.5_PDF261000_PSMUR0.5_PSMUF0.5
    MUR0.5_MUF1_PDF261000_PSMUR0.5_PSMUF1
    MUR1_MUF0.5_PDF261000_PSMUR1_PSMUF0.5
    MUR2_MUF1_PDF261000_PSMUR2_PSMUF1
    MUR1_MUF2_PDF261000_PSMUR1_PSMUF2
    MUR2_MUF2_PDF261000_PSMUR2_PSMUF2
   */
  
  cout <<"loop to load histos"<< endl;
  //413008_v3.root
  file[0][0] = TFile::Open("input/rivet/s228_ttw_20.01/700000_nom.root");
  file[0][1] = TFile::Open("input/rivet/s228_ttw_20.01/700000_mePS_scale.root");
  //file[0][1] = TFile::Open("input/rivet/413008_v3_up.root");
  //file[0][2] = TFile::Open("input/rivet/413008_v3_down.root");
 
  /* file[0][1] = TFile::Open("input/rivet/410155_v3.root"); */
  /* //file[0][0] = TFile::Open("input/rivet/413008cg.root"); */
  /* //file[0][2] = TFile::Open("input/rivet/700000_v3.root"); */
  /* file[0][2] = TFile::Open("input/rivet/cms_v0/TTWJetsToLNuMerged.root"); */
  /* //file[0][2] = TFile::Open("input/Res_Sherpa.root"); */
  
  /* file[0][3] = TFile::Open("input/rivet/413008_v3_up.root"); */
  /* file[0][4] = TFile::Open("input/rivet/413008_v3_down.root"); */
  /* file[0][5] = TFile::Open("input/rivet/700000_v3.root"); */
  
  //file[0][0] = TFile::Open("input/Res_Sherpa.root");
  //file[0][1] = TFile::Open("input/rivet/413008_v3.root");
  /* file[0][2] = TFile::Open("input/rivet/413008_withNu.root"); */
  
  //up
  //file[0][0] = TFile::Open("input/Res_SherpaScaleUp.root");
  //file[0][1] = TFile::Open("input/rivet/413008_v1_up.root");
  //MG
  //file[0][0] = TFile::Open("input/Res_MG5_aMcAtNlo.root");
  //file[0][1] = TFile::Open("input/rivet/410155_v3.root");

  for(int t=0;t<type.size();t++){ 
    file_name=base_name+"_"+type[t]+".root";

    //cout<< "file_name  - " << file_name<< endl;
    //  file[0][t] = TFile::Open(file_name.c_str());    
    //region
    for(int i=0;i<nj_reg.size();i++){
      //variable
      for(int j=0;j<variable.size();j++){
	//For Comparison Gen-Rivet
	//if(t==0) sprintf(sf_name,"%s_%s",variable[j].c_str(),nj_reg[i].c_str());   
	//else if(t>0) sprintf(sf_name,"ttw_ttH/%s_%s",variable[j].c_str(),nj_reg[i].c_str());

	// For rivet only
	if(t==0){
	  sprintf(sf_name,"ttw_ttH/%s_%s",variable[j].c_str(),nj_reg[i].c_str());
	  h_var[i][j][0][t] = (TH1D *)file[0][0]->Get(sf_name);
	}
	else{
	  sprintf(sf_name,"%s/ttw_ttH/%s_%s",type_path[t].c_str(),variable[j].c_str(),nj_reg[i].c_str());
	  h_var[i][j][0][t] = (TH1D *)file[0][1]->Get(sf_name);		 
	}
	//For Comparison with CMS
	//if(t<2 || t>2) sprintf(sf_name,"ttw_ttH/%s_%s",variable[j].c_str(),nj_reg[i].c_str());
	//else if(t==2) sprintf(sf_name,"CMS_2019_TTH_TTWBCKG/%s_%s",variable[j].c_str(),nj_reg[i].c_str());
	/* //AT version */
	/* else if(t==2) sprintf(sf_name,"%s_%s",variable[j].c_str(),nj_reg[i].c_str()); */
	
	//cout << "sf_name " << sf_name<< " reg = "<< region_names[i]<< ", variable in histo - "<< variable[j] << << endl;
	//cout <<"ij0t= "<<i<<j<<t << "sf_name " << sf_name<< " nbins  "<< h_var[i][j][0][t]->GetXaxis()->GetNbins() << ", variable in histo - "<< variable[j] << endl;
	//cout <<"read; n bins for h_var["<<i<<"]["<<j<<"][0]["<<t<<"] = "<<h_var[i][j][0][t]->GetXaxis()->GetNbins() <<endl; 
 
	if (!norm_xs_plots) norm_hist = h_var[i][j][0][t]->GetSumOfWeights();
	else if (norm_xs_plots) norm_hist = 1;
	
	h_var[i][j][0][t]->Scale(1/norm_hist);
	norm_hist=1;
      }//variable - j
    }// region - i
  }// file
  



  cout <<"histos are load  " << endl;

  cout << "=============================="<<'\n'<<'\n'<<'\n'<<"loop to make plots using loaded histos"<< endl;
  for(int i=0;i<nj_reg.size();i++){
    for(int j=0;j<variable.size();j++){
      
      sprintf(canvas_name,"c_Region_%s_%s",nj_reg[i].c_str(), variable[j].c_str() );
      cout << "canvas_name "<< canvas_name<< endl;
      //canv[i][j] = new TCanvas(canvas_name, "", 800, 750);
      canv[i][j] = new TCanvas(canvas_name, "", 600, 750);
      
      sprintf(p1_name,"p1_%s_%s",nj_reg[i].c_str(),variable[j].c_str() );
      sprintf(p2_name,"p2_%s_%s",nj_reg[i].c_str(),variable[j].c_str() );
      sprintf(p3_name,"p3_%s_%s",nj_reg[i].c_str(),variable[j].c_str() );

      pad1[i][j] = new TPad(p1_name, "pad1", 0, 0.43, 1, 1);
      pad1[i][j]->SetBottomMargin(0.018);
      pad1[i][j]->SetBorderMode(0);
      pad1[i][j]->SetLeftMargin(0.1);
      pad1[i][j]->SetFillStyle(0);

      pad2[i][j] = new TPad(p2_name, "pad2", 0, 0.25, 1, 0.435);
      //pad2[i][j]->SetTopMargin(0);
      pad2[i][j]->SetLeftMargin(0.1);
      //pad2[i][j]->SetBottomMargin(0.3);
      pad2[i][j]->SetBottomMargin(0.04);
      pad2[i][j]->SetFillStyle(4000);
      pad2[i][j]->SetBorderMode(4000);

      pad3[i][j] = new TPad(p3_name, "pad3", 0, 0, 1, 0.25);
      pad3[i][j]->SetTopMargin(0);
      pad3[i][j]->SetLeftMargin(0.1);
      pad3[i][j]->SetBottomMargin(0.3);
      pad3[i][j]->SetFillStyle(4000);
      pad3[i][j]->SetBorderMode(4000);
      //pad2[i][j]->SetFillColorAlpha(kBlue, 0.99);
      //pad1[i][j]->SetLogx(); 
      //pad2[i][j]->SetLogx(); 
      pad1[i][j]->Draw();
      pad2[i][j]->Draw();
      pad3[i][j]->Draw();
      
      pad1[i][j]->cd();             

      //legend[i][j] = new TLegend(0.6,0.6,0.9,0.9);
      legend[i][j] = new TLegend(0.65,0.4,0.9,0.9);
      legend[i][j]->SetTextFont(42);legend[i][j]->SetFillColor(0);  legend[i][j]->SetBorderSize(0); legend[i][j]->SetFillStyle(0);  legend[i][j]->SetTextSize(0.05);
      
      Double_t nom_bin_i=0,diff_bin_ib=0,var_bin_i=0,shift_bin_i=0,
	diffA_bin_ib=0,varA_bin_i=0,shiftA_bin_i=0;
      //loop over hist bins
      int nbinsx=0;
      sprintf(sf_name,"unc_up_%s_%s",variable[j].c_str(),nj_reg[i].c_str());   
      h_var[i][j][4][0] = (TH1D*) h_var[i][j][0][0]->Clone(sf_name);
      sprintf(sf_name,"unc_down_%s_%s",variable[j].c_str(),nj_reg[i].c_str());   
      h_var[i][j][5][0] = (TH1D*) h_var[i][j][0][0]->Clone(sf_name);

      /*
      sprintf(sf_name,"a_up_%s_%s",variable[j].c_str(),nj_reg[i].c_str());   
      h_var[i][j][6][0] = (TH1D*) h_var[i][j][0][0]->Clone(sf_name);
      sprintf(sf_name,"a_down_%s_%s",variable[j].c_str(),nj_reg[i].c_str());   
      h_var[i][j][7][0] = (TH1D*) h_var[i][j][0][0]->Clone(sf_name);
      //*/
      
      nbinsx = -1;
      nbinsx = h_var[i][j][0][0]->GetXaxis()->GetNbins(); //get Nbins from nominal sample
      //cout <<"h_var["<<i<<"]["<<j<<"][0][0]"<<"  nbinsx = "<< nbinsx <<endl;

      //HESSIAN Set - sum in quadrature:
      /*
      for(int ib=0; ib<nbinsx+1;ib++){
	
	nom_bin_i=h_var[i][j][0][0]->GetBinContent(ib);
	diff_bin_ib=0;	diffA_bin_ib=0;
	for(int t=1;t<type.size();t++){
	  var_bin_i=h_var[i][j][0][t]->GetBinContent(ib);
	  diff_bin_ib+=pow((nom_bin_i-var_bin_i),2);
	  if(type[t]=="R05F05"|| type[t]=="R2F2"){
	    varA_bin_i=h_var[i][j][0][t]->GetBinContent(ib);
	    diffA_bin_ib+=pow((nom_bin_i-varA_bin_i),2);
	    //cout << "type[t] "<< type[t]<< endl;
	  }
	}
	shift_bin_i=sqrt(diff_bin_ib);
	shiftA_bin_i=sqrt(diffA_bin_ib);
	//cout<< "nom_bin_i= "<<nom_bin_i<<", shift_bin_i="<< shift_bin_i<< "; up = "<< nom_bin_i+shift_bin_i<< "; down = "<< nom_bin_i-shift_bin_i<< "; orig up/down= "<< h_var[i][j][0][1]->GetBinContent(ib)<<"/"<<h_var[i][j][0][2]->GetBinContent(ib)<< endl;
	h_var[i][j][4][0]->SetBinContent(ib,nom_bin_i+shift_bin_i);	h_var[i][j][5][0]->SetBinContent(ib,nom_bin_i-shift_bin_i);
	h_var[i][j][6][0]->SetBinContent(ib,nom_bin_i+shiftA_bin_i);	h_var[i][j][7][0]->SetBinContent(ib,nom_bin_i-shiftA_bin_i);
      }
      //*/

      Double_t edge_up,edge_down;
      // Envelope = larges contribution
      for(int ib=0; ib<nbinsx+1;ib++){
	
	nom_bin_i=h_var[i][j][0][0]->GetBinContent(ib);
	//diff_bin_ib=0;	diffA_bin_ib=0;
	edge_up=nom_bin_i;
	edge_down=nom_bin_i;
	for(int t=1;t<type.size();t++){
	  var_bin_i=h_var[i][j][0][t]->GetBinContent(ib);
	  //diff_bin_ib+=pow((nom_bin_i-var_bin_i),2);
	  if(edge_up<var_bin_i) edge_up=var_bin_i;
	  
	  if(edge_down>var_bin_i) edge_down=var_bin_i;
	  
	  if(type[t]=="R05F05"|| type[t]=="R2F2"){
	    varA_bin_i=h_var[i][j][0][t]->GetBinContent(ib);
	    diffA_bin_ib+=pow((nom_bin_i-varA_bin_i),2);
	    //cout << "type[t] "<< type[t]<< endl;
	  }	  	 	
	}
	
	//cout<< "nom_bin_i= "<<nom_bin_i<<", shift_bin_i="<< shift_bin_i<< "; up = "<< nom_bin_i+shift_bin_i<< "; down = "<< nom_bin_i-shift_bin_i<< "; orig up/down= "<< h_var[i][j][0][1]->GetBinContent(ib)<<"/"<<h_var[i][j][0][2]->GetBinContent(ib)<< endl;
	h_var[i][j][4][0]->SetBinContent(ib,edge_up);	h_var[i][j][5][0]->SetBinContent(ib,edge_down);
	//h_var[i][j][6][0]->SetBinContent(ib,nom_bin_i+shiftA_bin_i);	h_var[i][j][7][0]->SetBinContent(ib,nom_bin_i-shiftA_bin_i);
      }
	    
      for(int t=0;t<type.size();t++){
  //*

	//cout << " - load file: "<< t << " - "<<  type[t] << endl;
	if(t==0){	  

	  //if (variable[j]!="nBtagJets") h_var[i][j][k][t]->SetYTitle("Normalized");
	  //else h_var[i][j][k][t]->SetYTitle("Events");
	  //h_var[i][j][0][t]->SetYTitle("Events"); 
	  if (norm_xs_plots) 	  h_var[i][j][0][t]->SetYTitle("#sigma_{fid} [fb]"); 
	  //h_var[i][j][0][t]->SetYTitle("Normalized"); 
	  else if (!norm_xs_plots) h_var[i][j][0][t]->SetYTitle("Arbitrary Units"); 

	  h_var[i][j][0][t]->GetXaxis()->SetLabelOffset(0.015);
	  //if(variable[i].find("nJets")!= std::string::npos) h_var[i][j][0][t]->GetXaxis()->SetNdivisions(500, kTRUE);

	  //||variable[i].find("nBtagJets")
	  h_var[i][j][0][t]->SetXTitle((variable_X[j]).c_str());
	  h_var[i][j][0][t]->GetYaxis()->SetTitleSize(0.06); 
	  h_var[i][j][0][t]->GetYaxis()->SetTitleOffset(0.7); 
	  //h_var[i][j][0][t]->GetXaxis()->SetRangeUser(20,500);
	  h_var[i][j][0][t]->SetMaximum(h_var[i][j][0][t]->GetMaximum()*1.6);
	  h_var[i][j][0][t]->Draw("E1");
	  h_var[i][j][0][t]->Draw("histsame");
	}
	
	h_var[i][j][0][t]->SetLineColor(color_sample[t]);
	h_var[i][j][0][t]->SetMarkerColor(color_sample[t]);
	h_var[i][j][0][t]->SetMarkerStyle(20+t);
	
	h_var[i][j][0][t]->SetLineWidth(2);
	//if(t==5)	h_var[i][j][0][t]->SetLineWidth(4);
	h_var[i][j][0][t]->SetLineStyle(linestyle[t]);
	//if(h_var[i][j][0][t]->Integral()>0){
	//if(t<3 || t==5)
	//h_var[i][j][0][t]->Draw("E1histsame");
	//h_var[i][j][0][0]->Draw("E1histsame");
	legend[i][j]->AddEntry(h_var[i][j][0][t],(type[t]+ " ").c_str(),"LP");
	//}//
	sprintf(sf_name,"ratio_%s_%s_%s",variable[j].c_str(),nj_reg[i].c_str(),type[t].c_str());   
	//cout<< "ratio name "<< sf_name<< endl;
	
	//sprintf(sf_name,"ratio_%s_%s",variable[j].c_str(),nj_reg[i].c_str());   
	
	// i region, j - variable, t -nom/variation, 
	h_var[i][j][3][t] = (TH1D*) h_var[i][j][0][t]->Clone(sf_name);
	//cout << "N var("<<t<<") bins ="<<h_var[i][j][3][t]->GetXaxis()->GetNbins()<< "; N nom bins = "<<h_var[i][j][0][0]->GetXaxis()->GetNbins()<< endl;;
	//ratio only:
	//h_var[i][j][3][t]->Divide(h_var[i][j][0][0]);
	//syst-nom/nom:
	h_var[i][j][3][t]->Add(h_var[i][j][0][0],-1);
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

	//ratio
	//h_var[i][j][3][t]->SetMinimum(0.65);
	//h_var[i][j][3][t]->SetMaximum(1.35);
	//(syst-nom_nom:
	h_var[i][j][3][0]->SetMinimum(-0.4);
	h_var[i][j][3][0]->SetMaximum(0.4);

	//For comparison Gen-Rivet
	//h_var[i][j][3][t]->SetMinimum(0.91);
	//h_var[i][j][3][t]->SetMaximum(1.09);

	//}    
	
      }//t loop: nominal - variations      


            
      for(int t=1;t<type.size();t++){
      	  if(type[t]=="R2F2"){
	    sprintf(sf_name,"a_up_%s_%s",variable[j].c_str(),nj_reg[i].c_str());   
	    h_var[i][j][6][0] = (TH1D*) h_var[i][j][0][t]->Clone(sf_name);
	  }
	  else if(type[t]=="R05F05"){
	    sprintf(sf_name,"a_down_%s_%s",variable[j].c_str(),nj_reg[i].c_str());   
	    h_var[i][j][7][0] = (TH1D*) h_var[i][j][0][t]->Clone(sf_name);
	    
	  }
      }

      //if(t==0){
      
      for(int unc=4;unc<8;unc++){
	if(unc<6){
	  h_var[i][j][unc][0]->SetMarkerColor(env_col[unc-4]); h_var[i][j][unc][0]->SetMarkerSize(0.1);  h_var[i][j][unc][0]->SetLineColor(env_col[unc-4]); h_var[i][j][unc][0]->SetLineWidth(3);
	  legend[i][j]->AddEntry(h_var[i][j][unc][0],("env "+env_type[unc-4]).c_str(),"LP");
	h_var[i][j][unc][0]->Draw("E1histsame");
	}
	
	sprintf(sf_name,"syst_ratio_%s_%s_%d",variable[j].c_str(),nj_reg[i].c_str(),unc);   
	h_var[i][j][4+unc][0] = (TH1D*) h_var[i][j][unc][0]->Clone(sf_name);
	h_var[i][j][4+unc][0]->Divide(h_var[i][j][0][0]);
	
      }//loop over uncertainties
	  //}//for nominal case only

	//sprintf(text1,"#sqrt{s} = 13 TeV, rivet routine");
      //sprintf(text1,"#sqrt{s} = 13 TeV, Sherpa 221, 413008");
      sprintf(text1,"#sqrt{s} = 13 TeV, Sherpa 228, 700000");
      //sprintf(text1,"#sqrt{s} = 13 TeV, aMC@NLO, 410155");
      //sprintf(text2,"Variable: %s",variable_X[j].c_str());//+nj_reg[i]+variable[j]
      sprintf(text2,"ttW 2#font[52]{l}SS %s ",region_names[i].c_str());
      
      ATLASLabel(0.18,0.87,atl_lable,1,0.065); 
      latex2.DrawLatex(0.18, 0.8, text1);  
      latex2.DrawLatex(0.18, 0.73, text2); //latex2.DrawLatex(0.20, 0.7, "Data");
      legend[i][j]->Draw("same");
      
      pad2[i][j]->cd();
      
      //h_var[i][j][3][0]->SetYTitle("Ratio to Sherpa");
      //h_var[i][j][3][0]->SetYTitle("Ratio to nominal");
      h_var[i][j][3][0]->SetYTitle("(Syst-Nom)/Nom");
      //h_var[i][j][3][0]->SetYTitle("Ratio to AT");
      h_var[i][j][3][0]->Draw("hist");
      for(int t=1;t<type.size();t++){
	//if(t<3)
	h_var[i][j][3][t]->SetLineWidth(3);
	//else if(t>2 &&t<5)	h_var[i][j][0][t]->SetLineWidth(1);
	//else h_var[i][j][3][t]->SetLineWidth(4);
	h_var[i][j][3][t]->SetLineColor(color_sample[t]);
	h_var[i][j][3][t]->SetMarkerColor(color_sample[t]);
	h_var[i][j][3][t]->SetLineStyle(linestyle[t]);
	h_var[i][j][3][t]->Draw("histsame");
	
	//*/
      }
      
      pad3[i][j]->cd();
      //cout  << "p3["<<i<<j<<"] h_var[0][1][0][0]  nb ="<< h_var[0][1][0][0]->GetXaxis()->GetNbins()  <<endl;
      sprintf(sf_name,"ratio_%s_%s_%s",variable[j].c_str(),nj_reg[i].c_str(),type[0].c_str());   
      h_var[i][j][15][0] = (TH1D*) h_var[i][j][3][0]->Clone(sf_name);
      h_var[i][j][15][0]->SetMinimum(0.45);
      h_var[i][j][15][0]->SetMaximum(1.55);
      h_var[i][j][15][0]->SetYTitle("Envelope");
      h_var[i][j][15][0]->Draw("hist");
      h_var[i][j][8][0]->Draw("histsame");
      h_var[i][j][9][0]->Draw("histsame");
      h_var[i][j][10][0]->Draw("histsame");
      h_var[i][j][11][0]->Draw("histsame");

      //      pad1[i][j]->RedrawAxis();
      //pad1[i][j]->Update();
      //pad1[i][j]->RedrawAxis();

      if (norm_xs_plots) sprintf(norm_name,"f");
      else if (!norm_xs_plots) sprintf(norm_name,"n");
      
      sprintf(o_name,"Uncertainty/Plot_s228_scaleEnv_%s/%s.pdf",norm_name,canvas_name);
      //sprintf(o_name,"Plots_gen_rivet_12_%s/%s.pdf",norm_name,canvas_name);
      canv[i][j]->Print(o_name);

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
