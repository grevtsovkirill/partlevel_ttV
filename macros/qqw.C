#include "TFile.h"
#include "TTree.h"
#include "TBranch.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TInterpreter.h"

#include "/Users/grevtsov/Documents/working_files/AtlasStyle/AtlasStyle.C"
#include "/Users/grevtsov/Documents/working_files/AtlasStyle/AtlasUtils.C"

void ATLASLabel(Double_t x,Double_t y,const char* text="",Color_t color=1, Double_t tsize=0.05);
void qqw(string sampleversion = "xs",  bool do_stack=true,bool do_log = true, bool do_text = false)
{
  gROOT->Reset();
  SetAtlasStyle();

  TFile *file[10][10];
  TLatex latex2; latex2.SetTextSize(0.06); latex2.SetNDC();
  char sf_name[1000] ;char band_name[1000] ;char ytest[1000];
  char text[1000];  char text1[1000];  char text2[1000]; 
  TString atl_lable = "Internal";
  TLegend* legend[100][100];
  TLegend* legend1[100][100];
  TCanvas * canv[100][100];
  TPad * pad1[100][100];
  TPad * pad2[100][100];
  char canvas_name[1000];char p1_name[1000];  char p2_name[1000]; char o_name[1000];
  TH1D* h_var[10][35][20][50];
  TH1D* h_allMC[10][35][20][50];

  vector<string>  nj_reg={"0"};vector<string> region_names={"2b4j"};
  //vector<string>  nj_reg={"0","1","2","3","4"};  vector<string> region_names={"2b4j","2b4j>0c","2b4jww","2b4jww>0c","2b4jwwJJpt"};
  //vector<string> variable={"nJets"};//,"Whmass","Whpt","DRlb0","DRlb1","DRlb2","DRlb3"};
  vector<string> variable={"mjj","nJets","Whmass"};//,"DRlb0","DRlb1","leps_tr_type","leps_tr_origin","jets_tr_type","jets_tr_origin"};
  //,"DRlb2","DRlb3"
  //vector<string> variable={"nJets","DRll01","Whmass","lep_Pt_0","lep_Pt_1","jet_Pt_4","jet_Pt_5","jet_Pt_6","Bjet_Pt_0","Bjet_Pt_1","min_DRl0j","min_DRl1j","maxEta_ll","HT_jets","HT_leps","HT","nBtagJets","MET","lep_Eta_0","lep_Eta_1","lep_Phi_0","lep_Phi_1","lep_dPhi","jet_Pt_1","jet_Pt_2","jet_Pt_3"}; //
  //,"DRll01"

  //vector<string> variable={"mjj","nJets","Whmass","jjpt","lep_Pt_0","lep_Pt_1","jet_Pt_4","jet_Pt_5","jet_Pt_6","Bjet_Pt_0","Bjet_Pt_1","min_DRl0j","min_DRl1j","maxEta_ll","HT_jets","HT_leps","HT","nBtagJets","MET","lep_Eta_0","lep_Eta_1","lep_Phi_0","lep_Phi_1","lep_dPhi","jet_Pt_1","jet_Pt_2","jet_Pt_3","jets_tr_type","jets_tr_origin"}; //
  vector<string> variable_X={"m_{j0j1}","Number of jets","m_{Wqq}","p_T^{Wqq}",
			     //"min#Delta R_{l_{0},b}","min#Delta R_{l_{1},b}",
			     //"Leps TruthType","Leps Origin","Jets TruthType","Jets Origin",
			     //"L0origin","L1origin",
			     //"#Delta R_{l_{1},b_{0}}","#Delta R_{l_{1},b_{1}}",
			     //"#Delta R_{l_{0},l_{1}}",
			     "Leading lepton #font[52]{p}_{T} [GeV]","Subeading lepton #font[52]{p}_{T} [GeV]",
			     "4th jet #font[52]{p}_{T} [GeV]","5th jet #font[52]{p}_{T} [GeV]","6th jet #font[52]{p}_{T} [GeV]",
			     "Leading #font[52]{b}-jet #font[52]{p}_{T} [GeV]","Subleading #font[52]{b}-jet #font[52]{p}_{T} [GeV]",
			     "#font[52]{min} #Delta R_{l_{0},jet}","#font[52]{min} #Delta R_{l_{1},jet}",
			     "#font[52]{max} |#eta _{l}|",
			     "#font[52]{HT}^{jets} [GeV]","#font[52]{HT}^{lep} [GeV]","#font[52]{HT} [GeV]",
			     "Number of #font[52]{b}-jets","#font[52]{E}_{T}^{miss}","Leading lepton #eta","Subleading lepton #eta","Leading lepton #phi","Subleading lepton #phi","#Delta #phi ^{ll}",
			     "1th jet #font[52]{p}_{T} [GeV]","2nd jet #font[52]{p}_{T} [GeV]","3rd jet #font[52]{p}_{T} [GeV]",
			     "Jets TruthType","Jets Origin"};  
  //*
  string truthOriginLabel[] = {
			       "NonDefined - 0","SingleElec - 1","SingleMuon - 2","SinglePhot - 3","SingleTau - 4","PhotonConv - 5","DalitzDec - 6","ElMagProc - 7",
			       "Mu - 8","TauLep - 9","top - 10","QuarkWeakDec - 11","WBoson - 12","ZBoson - 13","Higgs - 14","HiggsMSSM - 15","HeavyBoson - 16",
			       "WBosonLRSM - 17","NuREle - 18","NuRMu - 19","NuRTau - 20","LQ - 21","SUSY - 22","LightMeson - 23","StrangeMeson - 24","CharmedMeson - 25",
			       "BottomMeson - 26","CCbarMeson - 27","JPsi - 28","BBbarMeson - 29","LightBaryon - 30","StrangeBaryon - 31","CharmedBaryon - 32","BottomBaryon - 33",
			       "PionDecay - 34","KaonDecay - 35","BremPhot - 36","PromptPhot - 37","UndrPhot - 38","ISRPhot - 39","FSRPhot - 40","NucReact - 41","PiZero - 42",
			       "DiBoson - 43","ZorHeavyBoson - 44","QCD - 45", "OtherBSM - 46,", "MultiBoson- 47",
  };
  //*/

  string truthTypeLabel[] =  { 
			      "Unknown  =  0", "UnknownElectron=  1", "IsoElectron =  2", "NonIsoElectron =  3", "BkgElectron =  4", "UnknownMuon =  5",
			      "IsoMuon  =  6", "NonIsoMuon  =  7", "BkgMuon  =  8", "UnknownTau  =  9", "IsoTau=  10", "NonIsoTau=  11",
			      "BkgTau=  12", "UnknownPhoton  =  13", "IsoPhoton=  14", "NonIsoPhoton=  15", "BkgPhoton=  16", "Hadron=  17",
			      "Neutrino =  18", "NuclFrag =  19", "NonPrimary  =  20", "GenParticle =  21", "SUSYParticle=  22",
			      "BBbarMesonPart =  23", "BottomMesonPart=  24", "CCbarMesonPart =  25", "CharmedMesonPart  =  26", "BottomBaryonPart  =  27",
			      "CharmedBaryonPart =  28","StrangeBaryonPart =  29", "LightBaryonPart=  30", "StrangeMesonPart  =  31", "LightMesonPart =  32",
			      "BJet  =  33", "CJet  =  34", "LJet  =  35", "GJet  =  36", "TauJet=  37", "UnknownJet  =  38", "OtherBSMParticle  =  39"
  };

  /*
  string truthOriginLabel[] = {
			       "NonDefined - 0","SingleElec - 1","SingleMuon - 2","","","","","ElMagProc - 7",
			       "Mu - 8","TauLep - 9","top - 10","QuarkWeakDec - 11","WBoson - 12","ZBoson - 13","Higgs - 14","HiggsMSSM - 15","HeavyBoson - 16",
			       "WBosonLRSM - 17","","","","","","LightMeson - 23","StrangeMeson - 24","CharmedMeson - 25",
			       "BottomMeson - 26","CCbarMeson - 27","JPsi - 28","BBbarMeson - 29","LightBaryon - 30","StrangeBaryon - 31","CharmedBaryon - 32","BottomBaryon - 33",
			       "PionDecay - 34","KaonDecay - 35","BremPhot - 36","PromptPhot - 37","UndrPhot - 38","ISRPhot - 39","FSRPhot - 40","NucReact - 41","PiZero - 42",
			       "DiBoson - 43","ZorHeavyBoson - 44","QCD - 45", "OtherBSM - 46,", "MultiBoson- 47",
  };
  //*/
  

  //'413008_ttw','410472_ttbar','410156_ttZnunu','410157_ttZqq','410218_ttee','410219_ttmumu','410220_tttautau
  //type
  //file[0][0] = TFile::Open("input/Wqq/ttwqq1.root");
  //file[0][1] = TFile::Open("input/Wqq/ttzqq.root");
  //vector<string> type={"413008_ttw","410472_ttbar","410156_ttZnunu","410157_ttZqq","410218_ttee","410219_ttmumu","410220_tttautau"};
  std::map<std::string, std::string> sample_map;
  sample_map["ttW"]= "413008";
  sample_map["ttW_aMC"]= "410155";
  sample_map["ttbar"]= "410472";
  sample_map["ttbarNH"]= "410470";
  sample_map["ttZqq"]= "410157";
  sample_map["ttZnunu"]= "410156";
  sample_map["ttZee"]= "410218";
  sample_map["ttZmumu"]= "410219";
  sample_map["ttZtautau"]= "410220";
  sample_map["topt"]= "410658"; // 0
  sample_map["atopt"]= "410659"; // 0
  sample_map["tops"]= "410644"; // 0
  sample_map["atops"]= "410644"; // 0
  sample_map["threeTop"]= "304014"; // non-zero
  sample_map["fourTop"]= "410080"; // non-zero
  sample_map["ttWW"]= "410081"; // non-zero
  sample_map["Wtz"]= "410408";  // non-zero


  //reco:
  /*
    ttHsemilep 345874
    ttHdilep 345875
    ZqqZll 363356
    WqqZvv 363357
    WqqZll 363358
    WpqqWmlv 363359
    llvvjj 364285
   */
  user.pfalke.363356.Sherpa.DAOD_HIGG8D1.e5525_s3126_r10201_r10210_p3983.FS_mc16d_ttWprod_v2_output.root
  //           '304014_threeTop','410080_fourTop','410081_ttww','410408_WtZ']

  //632,
  //  Int_t color_sample[12]={632,868,867,865,801,802,805,922,921,920,0};//625
  //vector<string> type={"ttW","ttZee","ttZmumu","ttZqq","Wtz","ttWW","ttZtautau","fourTop","ttZnunu","threeTop","ttbar"}; //"ttW_aMC"
  //reco:
  Int_t color_sample[12]={632,868,867,865,0,801,802,805,922,921,920};//625
  vector<string> type={"ttW","ttZee","ttZmumu","ttZtautau","ttbarNH"}; //"ttW_aMC"
  //  vector<string> type={"ttbar"};
  //vector<string> type={"ttW","ttbar"};
  //vector<string> type={"ttW","ttW_aMC"};
  //vector<string> type={"ttW_aMC","ttbar"};
  //vector<string> type={"ttWpartlevel","ttWreco"};
  //vector<string> type={"ttbar partlevel","ttbar reco"};
  //vector<string> type={"ttbar dilep","ttbar nonallhad"};
  
  string pathversion = "v3_ljgeq2"; //v2_MCTC_0 v1_truthInfo //v1_e2b_lJqq, v2_ctag_minDRlb //v1_truthInfo_newXS //reco_v0_gn1v0

  string leg_type="f";  
  string reco_part=""; //
  reco_part="reco_"; pathversion="reco_v3_matchpartlev_medium";
  //=false;
  
  //if (sampleversion != "norm")
  //  do_log=true;
  //file[0][0] = TFile::Open("input/Wqq/v3_ljgeq2/wqq_413008_xs.root"); 
  //file[0][1] = TFile::Open("input/Wqq/reco_v3_matchpartlev_medium/wqq_reco_413008_xs.root"); 
  //file[0][0] = TFile::Open("input/Wqq/v2_MCTC_0/wqq_410472_xs.root"); 
  //file[0][1] = TFile::Open("input/Wqq/reco_v0_gn1v0/wqq_reco_410218_xs.root"); 
  //file[0][1] = TFile::Open("input/Wqq/reco_v0_gn1v0/wqq_reco_410470_xs.root");
  //file[0][1] = TFile::Open("input/Wqq/v2_MCTC_0/wqq_410470_xs.root"); 

  Double_t norm_hist=0;
  for(int t=0;t<type.size();t++){
    //region
    file[0][t] = TFile::Open(("input/Wqq/"+pathversion+"/wqq_"+reco_part+sample_map[type[t]]+"_xs.root").c_str()); //+sampleversion+
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
      std::map<string,float> yields;
      yields["TotalMC"] = 0.;
      yields["TotalBkg"] = 0.;
      
      sprintf(canvas_name,"c_Region_%s_%s",nj_reg[i].c_str(), variable[j].c_str() );
      //cout << "canvas_name "<< canvas_name<< endl;
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
      
      legend[i][j] = new TLegend(0.5,0.5,0.9,0.9);
      legend[i][j]->SetNColumns(2);
      
      legend[i][j]->SetTextFont(42);legend[i][j]->SetFillColor(0);  legend[i][j]->SetBorderSize(0); legend[i][j]->SetFillStyle(0);  legend[i][j]->SetTextSize(0.05);

      THStack *hs = new THStack("hs","Stacked 1D histograms");
 
      pad1[i][j]->cd();

      for(int t=0;t<type.size();t++){
	cout << " - load file: "<< t << " - "<<  type[t] << endl;
	
	yields[type[t]] = (h_var[i][j][0][t]->GetBinContent(0) + h_var[i][j][0][t]->Integral() +  h_var[i][j][0][t]->GetBinContent(h_var[i][j][0][t]->GetNbinsX() + 1)) ;
	if (type[t] != "ttW")yields["TotalBkg"] += yields[type[t]];
	yields["TotalMC"] += yields[type[t]];
	cout << type[t] << "\t" << yields[type[t]] << "\t"  << endl;
				
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
	if(type[t]=="ttbar" || type[t]=="ttbarNH"){
	  h_var[i][j][0][t]->SetLineColor(1);
	  h_var[i][j][0][t]->SetMarkerColor(1);
	}

	if(!do_stack){
	  h_var[i][j][0][t]->SetLineWidth(2);
	  //h_var[i][j][0][t]->SetLineStyle(linestyle[t]);
	  h_var[i][j][0][t]->Draw("E1histsame");
	}
	hs->Add(h_var[i][j][0][t]);
	sprintf(ytest,"%0.2f",yields[type[t]]);
	if(sampleversion=="norm"){
	      sprintf(ytest,"%0.2f", h_var[i][j][0][t]->GetMean());
	}
	//cout << " ============ "<< ytest<< endl;//to_string(yields[type[t]] )
	legend[i][j]->AddEntry(h_var[i][j][0][t],(type[t]+ "  "+ ytest).c_str(),leg_type.c_str());		

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
      //cout << "TotalMC = " << "\t" << yields[ "TotalMC"] << "\t" << yields[ "TotalBkg"] << "\t"  << endl;

      if(do_stack){
	hs->Draw("hist");
	
	hs->GetXaxis()->SetLabelOffset(0.015);
	hs->GetXaxis()->SetTitle((variable_X[j]).c_str());
	hs->GetYaxis()->SetTitleSize(0.06); 
	hs->GetYaxis()->SetTitleOffset(0.7); 
	
	if(do_log){
	  pad1[i][j]->SetLogy();
	  hs->SetMaximum(hs->GetMaximum()*1e3); 
	  hs->SetMinimum(1e-1); 
	}
	else
	  hs->SetMaximum(hs->GetMaximum()*1.6); 
	
	sprintf(ytest,"TotMC %0.2f",yields["TotalMC"]);
	legend[i][j]->AddEntry(h_allMC[i][j][0][0], ytest ,"P");
	sprintf(ytest," S/B = %0.2f %%",yields["ttW"]/yields[ "TotalBkg"]*100);
	legend[i][j]->AddEntry(h_allMC[i][j][0][0],ytest ,"");
	h_allMC[i][j][0][0]->Draw("E1same");
	if (do_text){
	  h_allMC[i][j][0][0]->SetMarkerSize(2);	
	  h_allMC[i][j][0][0]->Draw("text0same");
	}
	cout << "h_allMC[i][j][0][0] = "<< h_allMC[i][j][0][0]->GetSumOfWeights()<< ", integral = "<< h_allMC[i][j][0][0]->GetBinContent(0) +h_allMC[i][j][0][0]->Integral() + h_allMC[i][j][0][0]->GetBinContent(h_allMC[i][j][0][0]->GetNbinsX() + 1)<< endl;
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

	if(variable[j]=="leps_tr_origin" ||	   variable[j]=="jets_tr_origin" ||
	   //variable[j]=="lep0_tr_origin" ||	   variable[j]=="lep1_tr_origin" ||
	   variable[j]=="leps_tr_type" ||	   variable[j]=="jets_tr_type"){
	  int Nbins = h_allMC[i][j][0][1]->GetNbinsX();
	  // cout << " === " <<Nbins<< "   "<< truthOriginLabel[40]<<endl;
	  for (int bin=1;bin<=Nbins;++bin){ 
	    //cout << h_allMC[i][j][0][0]->GetBinContent(bin) <<endl;
	    if(h_allMC[i][j][0][0]->GetBinContent(bin)!=0){
	      if(variable[j]=="leps_tr_origin" ||	   variable[j]=="jets_tr_origin" )
		h_allMC[i][j][0][1]->GetXaxis()->SetBinLabel(bin,truthOriginLabel[bin-1].c_str());
	      if(variable[j]=="leps_tr_type" ||	   variable[j]=="jets_tr_type" )
		h_allMC[i][j][0][1]->GetXaxis()->SetBinLabel(bin,truthTypeLabel[bin-1].c_str());
	    }
	  }

	}

	h_allMC[i][j][0][1]->SetYTitle("No sense Ratio");
	h_allMC[i][j][0][1]->Draw("E1");
	h_allMC[i][j][0][1]->Draw("histsame");	
	
      }
      else{

	if(variable[j]=="leps_tr_origin"|| variable[j]=="lep0_tr_origin" || variable[j]=="lep1_tr_origin"){
	  int Nbins = h_var[i][j][3][0]->GetNbinsX();
	  //cout << " === " <<Nbins<< "   "<< truthOriginLabel[40]<<endl;
	  for (int bin=1;bin<=Nbins;++bin){ 
	    h_var[i][j][3][0]->GetXaxis()->SetBinLabel(bin,truthOriginLabel[bin-1].c_str());
	  }	  
	}
	else if(variable[j]=="leps_tr_type"|| variable[j]=="lep0_tr_type" || variable[j]=="lep1_tr_type"){
	  int Nbins = h_var[i][j][3][0]->GetNbinsX();
	  //cout << " === " <<Nbins<< "   "<< truthOriginLabel[40]<<endl;
	  for (int bin=1;bin<=Nbins;++bin){ 
	    h_var[i][j][3][0]->GetXaxis()->SetBinLabel(bin,truthTypeLabel[bin-1].c_str());
	  }
	}
	
	h_var[i][j][3][0]->SetMinimum(0.68);
	h_var[i][j][3][0]->SetMaximum(1.32);
	h_var[i][j][3][0]->SetYTitle("Ratio to ttW");
	h_var[i][j][3][0]->Draw("hist");
	for(int t=1;t<type.size();t++){
	  h_var[i][j][3][t]->SetLineWidth(3);
	  h_var[i][j][3][t]->SetLineColor(color_sample[t]);
	  h_var[i][j][3][t]->SetMarkerColor(color_sample[t]);
	  if(type[t]=="ttbar" || type[t]=="ttbarNH"){
	    h_var[i][j][3][t]->SetLineColor(1);
	    h_var[i][j][3][t]->SetMarkerColor(1);
	  }
	  //h_var[i][j][3][t]->SetLineStyle(linestyle[t]);
	  h_var[i][j][3][t]->Draw("histsame");
	
	}
	
      }
	

      
      sprintf(o_name,"WqqPlots/v3/v3_ttwreco_part/%s.pdf",canvas_name);   // v2_ttWOnlytruth v2_ttbarOnlytruth
      //canv[i][j]->Print(o_name);
  
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
