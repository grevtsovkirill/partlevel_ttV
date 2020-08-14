#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TInterpreter.h"

#include "/Users/grevtsov/Documents/working_files/AtlasStyle/AtlasStyle.C"
#include "/Users/grevtsov/Documents/working_files/AtlasStyle/AtlasUtils.C"

void ATLASLabel(Double_t x,Double_t y,const char* text="",Color_t color=1, Double_t tsize=0.05);
TGraphAsymmErrors * band(TH1D *h_var,TH1D *h_var_up, TH1D * h_var_down ){

  double nbinsx = h_var->GetXaxis()->GetNbins();
  const int gs = nbinsx;
  cout << "nbinsx="<<gs<<endl;
  cout << "Hist bin content: "<<endl;
  Double_t xg[gs];
  Double_t xlg[gs]; Double_t xhg[gs];   Double_t yg[gs]; Double_t ylg[gs]; Double_t yhg[gs];
  for(int ib=1; ib<nbinsx+1;ib++){
    double nom=h_var->GetBinContent(ib);
    double errUp=h_var_up->GetBinContent(ib);
    double errDown=h_var_down->GetBinContent(ib);
    double xc=h_var->GetXaxis()->GetBinCenter(ib);
    double xl = h_var->GetXaxis()->GetBinWidth(ib)/2;
    double xh = h_var->GetXaxis()->GetBinWidth(ib)/2;
    cout<<h_var->GetBinContent(ib)<< " +  "<<errUp<< " - "<<errDown << " delta = "<< abs(errUp-errDown) << ", xc = "<<xc <<"["<<xl<<";"<<xh<<"]" <<endl;
    xg[ib-1]=xc;
    xlg[ib-1]=xl;
    xhg[ib-1]=xh;
    yg[ib-1]=nom;

    if( (nom-errUp) <0){ 
      yhg[ib-1]=abs(nom-errUp);
      ylg[ib-1]=abs(nom-errDown);
    }
    else{
      ylg[ib-1]=abs(nom-errUp);
      yhg[ib-1]=abs(nom-errDown);
    }
    if (yg[ib-1]==0){
      yg[ib-1]=1;
    }
  }
  
  auto gae = new TGraphAsymmErrors(gs,xg,yg,xlg,xhg,ylg,yhg);
  return gae;
}

void r3_note(bool norm_xs_plots=false)
{

  gROOT->Reset();
  SetAtlasStyle();

  TFile *file[10][15];
  //file[2] = TFile::Open("Res_ttW.root");
  TLatex latex2; latex2.SetTextSize(0.06); latex2.SetNDC();
  char text[1000];  char text1[1000];  char text2[1000]; char norm_name[1000];
  TString atl_lable = "Internal";// Simulation Preliminary Simulation Internal unapproved
  string lep_flav="nominal"; 
  //sprintf(text1,"#sqrt{s} = 13 TeV, 2b %s 2lSS",lep_flav.c_str());
  sprintf(text2,"");
  
  TH1D* h_var[10][35][20][50];
  TGraphAsymmErrors* graph[10][35][20][50];
  //TGraph* graph[10][35][20][50];

  vector<string> region_names={"0#tau_{had} 1#font[52]{b} #geq4#font[52]{j}", "0#tau_{had} #geq2#font[52]{b} #geq4#font[52]{j}","0#tau_{had} 1#font[52]{b} 3#font[52]{j}", "0#tau_{had} #geq2#font[52]{b} 3#font[52]{j}","1#tau_{had} #geq1#font[52]{b} #geq3#font[52]{j}"};//, "0t=3j","0tg4j","otg3g0b"};

  
  //
  //vector<string>  nj_reg={"0"}; vector<string> variable={"nJets","HT_jets","DRll01"};  vector<string> variable_X={"Number of jets","#font[52]{HT}^{jets} [GeV]","DRll01"};
  //vector<string>  nj_reg={"0"}; vector<string> variable={"nJets"};  vector<string> variable_X={"Number of jets"};


  //*
    vector<string>  nj_reg={"0","1","2","3","4"};//,"5","6","7"};
  vector<string> variable={"nJets","DRll01","lep_Pt_0","lep_Pt_1",
			   "jet_Pt_4","jet_Pt_5","jet_Pt_6",
			   "Bjet_Pt_0","Bjet_Pt_1",
			   "min_DRl0j","min_DRl1j","maxEta_ll",
			   "HT_jets","HT_leps","HT",
			   "nBtagJets","MET","lep_Eta_0","lep_Eta_1","lep_Phi_0","lep_Phi_1","lep_dPhi","jet_Pt_1","jet_Pt_2","jet_Pt_3"}; //

  vector<string> variable_X={"Number of jets","#Delta R_{l_{0},l_{1}}","Leading lepton #font[52]{p}_{T} [GeV]","Subeading lepton #font[52]{p}_{T} [GeV]",
			     "4th jet #font[52]{p}_{T} [GeV]","5th jet #font[52]{p}_{T} [GeV]","6th jet #font[52]{p}_{T} [GeV]",
			     "Leading #font[52]{b}-jet #font[52]{p}_{T} [GeV]","Subleading #font[52]{b}-jet #font[52]{p}_{T} [GeV]",
			     "#font[52]{min} #Delta R_{l_{0},jet}","#font[52]{min} #Delta R_{l_{1},jet}",
			     "#font[52]{max} |#eta _{l}|",
			     "#font[52]{HT}^{jets} [GeV]","#font[52]{HT}^{lep} [GeV]","#font[52]{HT} [GeV]",
			     "Number of #font[52]{b}-jets","#font[52]{E}_{T}^{miss}","Leading lepton #eta","Subleading lepton #eta","Leading lepton #phi","Subleading lepton #phi","#Delta #phi ^{ll}",
			     "1th jet #font[52]{p}_{T} [GeV]","2nd jet #font[52]{p}_{T} [GeV]","3rd jet #font[52]{p}_{T} [GeV]"
}; //

  //*/

  
  //vector<string> variable={"lep_Eta_0","lep_Eta_1","lep_Phi_0","lep_Phi_1"};
  //*
  //vector<string> type={"Sherpa","MG"}; 
  //ATLAS - CMS comparison
  //Int_t color_sample[8]={864,594,633,921,922,617,860,868};//625
  //AT-rivet Sherpa
  //Int_t color_sample[8]={1,633,601,920,922,799,617,625};
  //AT-rivet MG
  //Int_t color_sample[8]={601,418,617,799,617,625,1,633};

  //Int_t linestyle[8]={1,1,7,9,4,10,3,2};
  //                 AS AM cM, Su, Sd
  //Int_t linestyle[8]={1, 7, 1, 3,  4, 2,3,2};
  //*/
  //                     s  sew m  CMS Avars   Cvars
  Int_t color_sample[10]={864,4,594,633,860,868,921,922,860,860};//625
  Int_t linestyle[10]={1,7,1,1,3,3,2,2,2,2};
  Int_t mstyle[10]={20,24,22,1,1,1,1,1,1,1};

  //string var_type="Scale ";
  string var_type="PDF ";
  vector<string> env_type={"Up","Down","+alpha up" ,"+alpha down" };
  Double_t env_col[4]={618,612,418,409};



  char sf_name[1000] ;char band_name[1000] ;
  TLegend* legend[100][100];
  TCanvas * canv[100][100];
  TPad * pad1[100][100];
  TPad * pad2[100][100];
  char canvas_name[1000];char p1_name[1000];  char p2_name[1000]; char o_name[1000];

  string base_name="input/Res";  
  string file_name;

  Double_t norm_hist=1;
  cout <<"loop to load histos"<< endl;
  vector<string> type={"ATLAS Sherpa 228","ATLAS Sherpa+EWK",
		       "ATLAS aMC@NLO","CMS aMC@NLO FxFx",
		       "ATLAS Sherpa #mu_{R}0.5#mu_{F}0.5","ATLAS Sherpa #mu_{R}2#mu_{F}2",
		       "CMS #mu_{R}0.5#mu_{F}0.5","CMS #mu_{R}2#mu_{F}2",
		       "AME","aME",
		       "m05","m2"
		       //"r27"
  };

  Int_t n_nom_samples = 2;
  Bool_t pdf_nom=false;
  Bool_t w_cms=true; //false
  //,"Sherpa up" ,"Sherpa down"
  /*
  vector<string> type_path={
			    "MUR0.5_MUF0.5_PDF261000_PSMUR0.5_PSMUF0.5"
			    ,"MUR0.5_MUF1_PDF261000_PSMUR0.5_PSMUF1"
			    ,"MUR1_MUF0.5_PDF261000_PSMUR1_PSMUF0.5"
			    ,"MUR2_MUF1_PDF261000_PSMUR2_PSMUF1"
			    ,"MUR1_MUF2_PDF261000_PSMUR1_PSMUF2"
			    ,"MUR2_MUF2_PDF261000_PSMUR2_PSMUF2"
  };
  //*/
  vector<string> type_path = {"MUR1_MUF1_PDF261000","MUR1_MUF1_PDF261000_ASSEWLO1LO2LO3",
			      "_muR010000E+01_muF010000E+01_","dyn=___1_muR=0.10000E_01_muF=0.10000E_01",
			      "MUR05_MUF05_PDF261000_PSMUR05_PSMUF05","MUR2_MUF2_PDF261000_PSMUR2_PSMUF2",
			      "dyn=___1_muR=0.50000E_00_muF=0.50000E_00","dyn=___1_muR=0.20000E_01_muF=0.20000E_01",
			      "ME_ONLY_MUR05_MUF05_PDF261000_PSMUR05_PSMUF05","ME_ONLY_MUR2_MUF2_PDF261000_PSMUR2_PSMUF2",
			      "_muR050000E+00_muF050000E+00_","_muR020000E+01_muF020000E+01_",
			      //"ttw_ttH"
  };
  //type_path.push_back("MUR1_MUF1_PDF261000");
  //type_path.push_back("_muR010000E+01_muF010000E+01_");
  //type_path.push_back("MUR1_MUF1_PDF91400");
  /*
  for(int ipdf=1;ipdf<33;ipdf++){
    if (ipdf<10)
      type_path.push_back("MUR1_MUF1_PDF9140"+to_string(ipdf));
    else
      type_path.push_back("MUR1_MUF1_PDF914"+to_string(ipdf));
  }
  //*/
  //file[0][0] = TFile::Open("input/r3_2020/v1_full_syst/ttW700000_scalevar.root");
  file[0][0] = TFile::Open("input/r3_2020/v3/ttW700000_scalevar_v32.root");
  file[0][1] = TFile::Open("input/r3_2020/v3/ttW700000_scalevar_v32.root");
      
  //file[0][2] = TFile::Open("input/r3_2020/v1_full_syst/ttW410155_xsscalevar.root");
  file[0][2] = TFile::Open("input/r3_2020/v3/ttW410155_scalevar_v32.root");
  //file[0][2] = TFile::Open("input/r3_2020/v1_full_syst/ttWCMS.root");
  file[0][3] = TFile::Open("input/r3_2020/v1_full_syst/ttWCMS_v2.root");
  file[0][4] = TFile::Open("input/r3_2020/v3/ttW700000_scalevar_v32.root");
  file[0][5] = TFile::Open("input/r3_2020/v3/ttW700000_scalevar_v32.root");
    //  file[0][3] = TFile::Open("input/r3_2020/v1_full_syst/ttW700000_scalevar.root");
    //file[0][4] = TFile::Open("input/r3_2020/v1_full_syst/ttW700000_scalevar.root");
  file[0][6] = TFile::Open("input/r3_2020/v1_full_syst/ttWCMS_v2.root");  
  file[0][7] = TFile::Open("input/r3_2020/v1_full_syst/ttWCMS_v2.root");
  //file[0][7] = TFile::Open("input/r3_2020/testR3/sh28r27.root");
  file[0][8] = TFile::Open("input/r3_2020/v3/ttW700000_scalevar_v32.root");
  file[0][9] = TFile::Open("input/r3_2020/v3/ttW700000_scalevar_v32.root");
  file[0][10] = TFile::Open("input/r3_2020/v3/ttW410155_scalevar_v32.root");
  file[0][11] = TFile::Open("input/r3_2020/v3/ttW410155_scalevar_v32.root");

  string do_raw="";
  //if (norm_xs_plots) do_raw = "RAW/" ;

  for(int t=0;t<type.size();t++){ 
    //file_name=base_name+"_"+type[t]+".root";

    for(int i=0;i<nj_reg.size();i++){
      //variable
      for(int j=0;j<variable.size();j++){
		
	sprintf(sf_name,"%sCMSATLAS_TTW_ttHBCKG/%s_%s[%s]",do_raw.c_str(),variable[j].c_str(),nj_reg[i].c_str(),type_path[t].c_str());
	//if(t==8)
	//  sprintf(sf_name,"ttw_ttH/%s_%s",variable[j].c_str(),nj_reg[i].c_str());

	h_var[i][j][0][t] = (TH1D *)file[0][t]->Get(sf_name);			  
      
	/* else if(t>n_nom_samples-1){ */
	/*   sprintf(sf_name,"%s/ttw_ttH/%s_%s",type_path[t-n_nom_samples].c_str(),variable[j].c_str(),nj_reg[i].c_str()); */
	/*   h_var[i][j][0][t] = (TH1D *)file[0][3]->Get(sf_name); */
	/*     //} */
	/* } */

	/* if(pdf_nom){ */
	/*   sprintf(sf_name,"MUR1_MUF1_PDF91400/ttw_ttH/%s_%s",variable[j].c_str(),nj_reg[i].c_str()); */
	/*   h_var[i][j][0][0] = (TH1D *)file[0][3]->Get(sf_name); */
	/* } */
	/* //AT version */
	/* else if(t==2) sprintf(sf_name,"%s_%s",variable[j].c_str(),nj_reg[i].c_str()); */
	
	cout <<"h_var["<<i<<"]["<<j<<"][0]["<<t<<"] sf_name " << sf_name<< " , variable in histo - "<< variable[j]<< endl;
	
	if (!norm_xs_plots) norm_hist = h_var[i][j][0][t]->GetSumOfWeights();
	else{
	  norm_hist = 1;
	  if(t==0 ||t==1 || t==4 ||t==5) norm_hist = 589.2/600.8;
	  else if (t==2) norm_hist = 548.30/600.8;
	}
	
	h_var[i][j][0][t]->Scale(1/norm_hist);
	norm_hist=1;
      }//variable - j
    }// region - i
  }// file


    
  //cout <<"histos are load "<<h_var[0][0][0][5]->GetXaxis()->GetNbins() << endl;
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

      //legend[i][j] = new TLegend(0.6,0.6,0.9,0.9);
      legend[i][j] = new TLegend(0.5,0.6,0.9,0.9);
      legend[i][j]->SetTextFont(42);legend[i][j]->SetFillColor(0);  legend[i][j]->SetBorderSize(0); legend[i][j]->SetFillStyle(0);  legend[i][j]->SetTextSize(0.05);
      

      Double_t nom_bin_i=0,diff_bin_ib=0,var_bin_i=0,shift_bin_i=0, alpha=0,ashift_bin_i=0;
      //loop over hist bins
      int nbinsx=0;
      sprintf(sf_name,"unc_up_%s_%s",variable[j].c_str(),nj_reg[i].c_str());   
      h_var[i][j][4][0] = (TH1D*) h_var[i][j][0][0]->Clone(sf_name);
      sprintf(sf_name,"unc_down_%s_%s",variable[j].c_str(),nj_reg[i].c_str());   
      h_var[i][j][5][0] = (TH1D*) h_var[i][j][0][0]->Clone(sf_name);

      sprintf(sf_name,"aunc_up_%s_%s",variable[j].c_str(),nj_reg[i].c_str());   
      h_var[i][j][6][0] = (TH1D*) h_var[i][j][0][0]->Clone(sf_name);
      sprintf(sf_name,"aunc_down_%s_%s",variable[j].c_str(),nj_reg[i].c_str());   
      h_var[i][j][7][0] = (TH1D*) h_var[i][j][0][0]->Clone(sf_name);

      nbinsx = -1;
      nbinsx = h_var[i][j][0][0]->GetXaxis()->GetNbins(); //get Nbins from nominal sample
      //cout <<"h_var["<<i<<"]["<<j<<"][0][0]"<<"  nbinsx = "<< nbinsx <<endl;
      /*
      for(int ib=0; ib<nbinsx+1;ib++){
	nom_bin_i=h_var[i][j][0][0]->GetBinContent(ib);
	diff_bin_ib=0;
	for(int t=n_nom_samples;t<type.size()+type_path.size();t++){
	  if(t<29+n_nom_samples){
	  var_bin_i=h_var[i][j][0][t]->GetBinContent(ib);
	  diff_bin_ib+=pow((nom_bin_i-var_bin_i),2);
	  }	    
	}
	alpha=0;
	if(pdf_nom){	alpha=0.5*(h_var[i][j][0][31]->GetBinContent(ib) - h_var[i][j][0][32]->GetBinContent(ib));
	  cout <<"alpha = "<<alpha<<endl;
	}

	shift_bin_i=0;ashift_bin_i=0;
	shift_bin_i=sqrt(diff_bin_ib);
	ashift_bin_i=sqrt(diff_bin_ib + alpha*alpha);
	h_var[i][j][4][0]->SetBinContent(ib,nom_bin_i+shift_bin_i);	h_var[i][j][5][0]->SetBinContent(ib,nom_bin_i-shift_bin_i);
	h_var[i][j][6][0]->SetBinContent(ib,nom_bin_i+ashift_bin_i);	h_var[i][j][7][0]->SetBinContent(ib,nom_bin_i-ashift_bin_i);
      }
      */
      
      for(int t=0;t<type.size();t++){
	cout << " - load file: "<< t << " - "<<  type[t] << endl;
	if(t==0){	  

	  //if (variable[j]!="nBtagJets") h_var[i][j][k][t]->SetYTitle("Normalized");
	  //else h_var[i][j][k][t]->SetYTitle("Events");
	  //h_var[i][j][0][t]->SetYTitle("Events"); 
	  if (norm_xs_plots) 	  h_var[i][j][0][t]->SetYTitle("#sigma_{fid} [pb]"); 
	  //h_var[i][j][0][t]->SetYTitle("Normalized"); 
	  else if (!norm_xs_plots) h_var[i][j][0][t]->SetYTitle("Arbitrary Units"); 

	  h_var[i][j][0][t]->GetXaxis()->SetLabelOffset(0.015);
	  //if(variable[i].find("nJets")!= std::string::npos) h_var[i][j][0][t]->GetXaxis()->SetNdivisions(500, kTRUE);

	  //||variable[i].find("nBtagJets")
	  h_var[i][j][0][t]->SetXTitle((variable_X[j]).c_str());
	  h_var[i][j][0][t]->GetYaxis()->SetTitleSize(0.06); 
	  h_var[i][j][0][t]->GetYaxis()->SetTitleOffset(0.7); 
	  //h_var[i][j][0][t]->GetXaxis()->SetRangeUser(20,500);
	  h_var[i][j][0][t]->SetMaximum(h_var[i][j][0][t]->GetMaximum()*2);
	  h_var[i][j][0][t]->Draw("E1");
	}
	
	h_var[i][j][0][t]->SetLineColor(color_sample[t]);
	h_var[i][j][0][t]->SetMarkerColor(color_sample[t]);
	h_var[i][j][0][t]->SetMarkerStyle(mstyle[t]);
	
	h_var[i][j][0][t]->SetLineWidth(2);
	h_var[i][j][0][t]->SetLineStyle(linestyle[t]);
	//if(h_var[i][j][0][t]->Integral()>0){
	if(t<4){
	  h_var[i][j][0][t]->Draw("E1histsame");
	  legend[i][j]->AddEntry(h_var[i][j][0][t],(type[t]+ " ").c_str(),"LP");
	}
	//}//
	sprintf(sf_name,"ratio_%s_%s_%s",variable[j].c_str(),nj_reg[i].c_str(),type[t].c_str());   
	cout<< "ratio name "<< sf_name<< ", t's bins = "<< h_var[i][j][0][t]->GetXaxis()->GetNbins()<< ", 0's bins = "<< h_var[i][j][0][0]->GetXaxis()->GetNbins()<< endl;
	
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

	//Scale unc
	h_var[i][j][3][t]->SetMinimum(0.55);
	h_var[i][j][3][t]->SetMaximum(1.45);

	//PDF unc
	//h_var[i][j][3][t]->SetMinimum(0.78);
	//h_var[i][j][3][t]->SetMaximum(1.22);

	//h_var[i][j][3][t]->SetMinimum(0.95);
	//h_var[i][j][3][t]->SetMaximum(1.05);

	//For comparison Gen-Rivet
	//h_var[i][j][3][t]->SetMinimum(0.91);
	//h_var[i][j][3][t]->SetMaximum(1.09);
	if(t==0){

	  /*
	  for(int unc=4;unc<8;unc++){
	    h_var[i][j][unc][0]->SetMarkerColor(env_col[unc-4]); h_var[i][j][unc][0]->SetMarkerSize(0.1);  h_var[i][j][unc][0]->SetLineColor(env_col[unc-4]);
	    h_var[i][j][unc][0]->Draw("E1histsame");
	    legend[i][j]->AddEntry(h_var[i][j][unc][0],(var_type+env_type[unc-4]).c_str(),"LP");
	    
	    sprintf(sf_name,"syst_ratio_%s_%s_%d",variable[j].c_str(),nj_reg[i].c_str(),unc);   
	    h_var[i][j][4+unc][0] = (TH1D*) h_var[i][j][unc][0]->Clone(sf_name);
	    h_var[i][j][4+unc][0]->Divide(h_var[i][j][0][0]);
	    
	  }//loop over uncertainties
	  //*/
	}
	//*/
	//}    
      }//t loop: nominal - variations      
      
      sprintf(text1,"#sqrt{s} = 13 TeV, ttW"); //, rivet
      sprintf(text2,"2#font[52]{l}SS %s ",region_names[i].c_str());
      
      //ATLASLabel(0.18,0.87,atl_lable,1,0.065); 
      latex2.DrawLatex(0.18, 0.87, "ATLAS+CMS Simulation");
      latex2.DrawLatex(0.18, 0.80, "For LHCXSWG");
      latex2.DrawLatex(0.18, 0.73, text1);  
      latex2.DrawLatex(0.18, 0.66, text2); //latex2.DrawLatex(0.20, 0.7, "Data");
      legend[i][j]->Draw("same");
      
      pad2[i][j]->cd();
      //*

      h_var[i][j][3][0]->SetYTitle("Ratio to Sherpa");
      //h_var[i][j][3][0]->SetYTitle("Ratio to AT");
      h_var[i][j][3][0]->Draw("hist");
      for(int t=1;t<type.size();t++){
	h_var[i][j][3][t]->SetLineColor(color_sample[t]);
	h_var[i][j][3][t]->SetMarkerColor(color_sample[t]);
	h_var[i][j][3][t]->SetLineStyle(linestyle[t]);
	if(t<4){
	  h_var[i][j][3][t]->SetLineWidth(3);
	  h_var[i][j][3][t]->Draw("histsame");
	}
	//else if(t>2 &&t<5)	h_var[i][j][0][t]->SetLineWidth(1);
	else{
	  h_var[i][j][3][t]->SetLineWidth(4);
	  //h_var[i][j][3][t]->Draw("histsame");
	}
	
      }

      cout << " ==========  sherpa ME+PS  =========== "<<'\n'<<endl;
      auto gr = band(h_var[i][j][3][0],h_var[i][j][3][4],h_var[i][j][3][5]);
      gr->SetLineColor(0);
      //gr->SetFillColor(868);
      //gr->SetFillStyle(3004); //3154
      gr->SetFillColorAlpha(868, 0.35);
      gr->Print("all"); 
      gr->Draw("2, same");
      legend[i][j]->AddEntry(gr,"ATLAS scale variation ME+PS ","F");


      cout << " ==========  CMS aMC  =========== "<<'\n'<<endl;

      auto grCMS = band(h_var[i][j][3][3],h_var[i][j][3][6],h_var[i][j][3][7]);
      grCMS->SetLineColor(0);
      //grCMS->SetFillColor(2);
      //grCMS->SetFillStyle(3006);
      grCMS->SetFillColorAlpha(2, 0.35);
      grCMS->Print("all"); 
      grCMS->Draw("2, same");
      legend[i][j]->AddEntry(grCMS,"CMS scale variation ","F");

      /*
      cout << " ==========  sherpa MEonly  =========== "<<'\n'<<endl;
      auto grME = band(h_var[i][j][3][0],h_var[i][j][3][8],h_var[i][j][3][9]);
      grME->SetLineColor(0);      grME->SetFillColor(922);
      grME->SetFillStyle(3005);
      grME->Print("all"); 
      grME->Draw("2, same");
      legend[i][j]->AddEntry(grME,"ATLAS scale variation ME-only  ","F");


      cout << " ==========  atlas amc  =========== "<<'\n'<<endl; 
      auto grMG = band(h_var[i][j][3][2],h_var[i][j][3][10],h_var[i][j][3][11]);
      grMG->SetLineColor(0);      grMG->SetFillColor(594);
      grMG->SetFillStyle(3354);
      grMG->Print("all"); 
      grMG->Draw("2, same");
      legend[i][j]->AddEntry(grMG,"ATLAS aMC@NLO scale variation  ","F");

      //*/

      if (norm_xs_plots) sprintf(norm_name,"f");
      else if (!norm_xs_plots) sprintf(norm_name,"n");
      

      sprintf(o_name,"P2020/v3/r3_v32yr4_%s/%s.pdf",norm_name,canvas_name);
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
