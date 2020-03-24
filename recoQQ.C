void recoQQ(string name="413008", string comp="xs", bool onNAF = true){
  /*
    413008.root
  */

  TChain *ch=new TChain("nominal");
  string choose_tag="";
  string name1="";
  string path="";
  string prod_version = "GFW1_v0_0320"; //
  if(onNAF)
    path="/nfs/dust/atlas/group/top/ttH_ML/ttW_run2/ttWqq/Reco_files/"+prod_version+"/mc16d/"+name+".root";  
  else
    path="/Users/grevtsov/Documents/working_files/ttH/Wtt_run2/Files/ttWqq/Reco_files/"+prod_version+"/mc16d/"+name+".root";

  cout << "path = " << path<< endl;



  TChain *weight_chain=new TChain("sumWeights");
  weight_chain->Add(path.c_str());
  Double_t  sum_w=0;
  Float_t totalEventsWeighted;
  weight_chain->SetBranchAddress("totalEventsWeighted",&totalEventsWeighted);

  for(int i=0; i<weight_chain->GetEntries();i++){
    weight_chain->GetEntry(i);
    sum_w+=totalEventsWeighted;
  }
  cout<<" total sw:"<<to_string(sum_w)<<endl;

  ch->Add(path.c_str());
  cout << ch->GetNtrees()<< ", entr: "<< ch->GetEntries()<< endl;
  string  option=to_string(sum_w)+"/"+name+"-"+comp;

  ch->Process("source/reco_wqq.C+",option.c_str());

}
