#define CtagOpt_cxx


#include "CtagOpt.h"
#include <TH2.h>
#include <TStyle.h>

void CtagOpt::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void CtagOpt::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();

}

Bool_t CtagOpt::Process(Long64_t entry)
{
   fReader.SetEntry(entry);

   return kTRUE;
}

void CtagOpt::SlaveTerminate()
{
 
}

void CtagOpt::Terminate()
{
 
}
