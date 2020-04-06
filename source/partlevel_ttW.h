//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Aug  5 14:32:13 2019 by ROOT version 6.15/02
// from TTree particleLevel/tree
// found on file: ../../Files/particle_level/413008d.root
//////////////////////////////////////////////////////////

#ifndef partlevel_ttW_h
#define partlevel_ttW_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include <vector>



class partlevel_ttW : public TSelector {
public :
  TTreeReader     fReader;  //!the tree reader
  TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain
  
  Bool_t stoploop; Bool_t nomS_w;Bool_t nomM_w; Bool_t scaleupS_w; Bool_t scaledownS_w;Bool_t scaleupM_w; Bool_t scaledownM_w;
  Double_t Acc;
  Bool_t sel_array[10];
  int nEl;
  int nMu;
  int Nlep;
  Double_t weight_tot;
  Int_t       fNumberOfEvents; 

  int Njets = 0;
  int Nbjets = 0;
  int region = -99;
  float DRll01 = -9999;
  
  // Readers to access the data (delete the ones you do not need).
  TTreeReaderValue<Float_t> weight_mc = {fReader, "weight_mc"};
  TTreeReaderValue<ULong64_t> eventNumber = {fReader, "eventNumber"};
  TTreeReaderValue<UInt_t> runNumber = {fReader, "runNumber"};
  TTreeReaderValue<UInt_t> randomRunNumber = {fReader, "randomRunNumber"};
  TTreeReaderValue<UInt_t> mcChannelNumber = {fReader, "mcChannelNumber"};
  TTreeReaderValue<Float_t> mu = {fReader, "mu"};
  TTreeReaderValue<Float_t> mu_actual = {fReader, "mu_actual"};
  TTreeReaderValue<Float_t> weight_pileup = {fReader, "weight_pileup"};
  TTreeReaderArray<float> el_pt = {fReader, "el_pt"};
  TTreeReaderArray<float> el_eta = {fReader, "el_eta"};
  TTreeReaderArray<float> el_phi = {fReader, "el_phi"};
  TTreeReaderArray<float> el_e = {fReader, "el_e"};
  TTreeReaderArray<float> el_charge = {fReader, "el_charge"};
  TTreeReaderArray<float> el_pt_bare = {fReader, "el_pt_bare"};
  TTreeReaderArray<float> el_eta_bare = {fReader, "el_eta_bare"};
  TTreeReaderArray<float> el_phi_bare = {fReader, "el_phi_bare"};
  TTreeReaderArray<float> el_e_bare = {fReader, "el_e_bare"};
  TTreeReaderArray<float> mu_pt = {fReader, "mu_pt"};
  TTreeReaderArray<float> mu_eta = {fReader, "mu_eta"};
  TTreeReaderArray<float> mu_phi = {fReader, "mu_phi"};
  TTreeReaderArray<float> mu_e = {fReader, "mu_e"};
  TTreeReaderArray<float> mu_charge = {fReader, "mu_charge"};
  TTreeReaderArray<float> mu_pt_bare = {fReader, "mu_pt_bare"};
  TTreeReaderArray<float> mu_eta_bare = {fReader, "mu_eta_bare"};
  TTreeReaderArray<float> mu_phi_bare = {fReader, "mu_phi_bare"};
  TTreeReaderArray<float> mu_e_bare = {fReader, "mu_e_bare"};
  TTreeReaderArray<float> jet_pt = {fReader, "jet_pt"};
  TTreeReaderArray<float> jet_eta = {fReader, "jet_eta"};
  TTreeReaderArray<float> jet_phi = {fReader, "jet_phi"};
  TTreeReaderArray<float> jet_e = {fReader, "jet_e"};
  TTreeReaderArray<int> jet_nGhosts_bHadron = {fReader, "jet_nGhosts_bHadron"};
  TTreeReaderArray<int> jet_nGhosts_cHadron = {fReader, "jet_nGhosts_cHadron"};
  TTreeReaderValue<Float_t> met_met = {fReader, "met_met"};
  TTreeReaderValue<Float_t> met_phi = {fReader, "met_phi"};
  TTreeReaderArray<float> PDFinfo_X1 = {fReader, "PDFinfo_X1"};
  TTreeReaderArray<float> PDFinfo_X2 = {fReader, "PDFinfo_X2"};
  TTreeReaderArray<int> PDFinfo_PDGID1 = {fReader, "PDFinfo_PDGID1"};
  TTreeReaderArray<int> PDFinfo_PDGID2 = {fReader, "PDFinfo_PDGID2"};
  TTreeReaderArray<float> PDFinfo_Q = {fReader, "PDFinfo_Q"};
  TTreeReaderArray<float> PDFinfo_XF1 = {fReader, "PDFinfo_XF1"};
  TTreeReaderArray<float> PDFinfo_XF2 = {fReader, "PDFinfo_XF2"};
  TTreeReaderArray<float> mc_generator_weights = {fReader, "mc_generator_weights"};
  //TTreeReaderArray<float> PDF4LHC15_nnlo_30_pdfas = {fReader, "PDF4LHC15_nnlo_30_pdfas"};
  TTreeReaderValue<Int_t> particle_level_ttW = {fReader, "particle_level_ttW"};
  //add taus 020919
  TTreeReaderArray<float> tau_pt = {fReader, "tau_pt"};
  TTreeReaderArray<float> tau_eta = {fReader, "tau_eta"};
  TTreeReaderArray<float> tau_phi = {fReader, "tau_phi"};
  TTreeReaderArray<float> tau_e = {fReader, "tau_e"};
  TTreeReaderArray<char> tau_isHadronic = {fReader, "tau_isHadronic"};


  partlevel_ttW(TTree * /*tree*/ =0):fNumberOfEvents(0)  { }
  virtual ~partlevel_ttW() { }
  virtual Int_t   Version() const { return 2; }
  virtual void    Begin(TTree *tree);
  virtual void    ReadOpt(double sumweights, int var_type);
  virtual void    SlaveBegin(TTree *tree);
  virtual void    Init(TTree *tree);
  virtual Bool_t  Notify();
  virtual Bool_t  Process(Long64_t entry);
  virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
  virtual void    SetOption(const char *option) { fOption = option; }
  virtual void    SetObject(TObject *obj) { fObject = obj; }
  virtual void    SetInputList(TList *input) { fInput = input; }
  virtual TList  *GetOutputList() const { return fOutput; }
  virtual void    SlaveTerminate();
  virtual void    Terminate();

  ClassDef(partlevel_ttW,0);

};

#endif

#ifdef partlevel_ttW_cxx
void partlevel_ttW::Init(TTree *tree)
{

  fReader.SetTree(tree);
}

Bool_t partlevel_ttW::Notify()
{

  return kTRUE;
}


#endif // #ifdef partlevel_ttW_cxx
