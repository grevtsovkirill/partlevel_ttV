#ifndef CtagOpt_h
#define CtagOpt_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

// Headers needed by this particular selector
#include <vector>



class CtagOpt : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderArray<float> truthflav = {fReader, "truthflav"};
   TTreeReaderArray<float> j_pt = {fReader, "j_pt"};
   TTreeReaderArray<float> score_DL1r_pu = {fReader, "score_DL1r_pu"};
   TTreeReaderArray<float> score_DL1r_pc = {fReader, "score_DL1r_pc"};
   TTreeReaderArray<float> score_DL1r_pb = {fReader, "score_DL1r_pb"};
   TTreeReaderValue<Double_t> weight_tot = {fReader, "weight_tot"};


   CtagOpt(TTree * /*tree*/ =0) { }
   virtual ~CtagOpt() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
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

   ClassDef(CtagOpt,0);

};

#endif

#ifdef CtagOpt_cxx
void CtagOpt::Init(TTree *tree)
{

   fReader.SetTree(tree);
}

Bool_t CtagOpt::Notify()
{

   return kTRUE;
}


#endif // #ifdef CtagOpt_cxx
