void recoQQ(string name="413008", string comp="xs", bool onNAF = true, bool multi_file = false, int num_split =4){
  /*
    413008.root
  */

  TChain *ch=new TChain("nominal");
  string choose_tag="d";
  string tmp="";
  string path="";
  string prod_version = "GFW1_v0_0320"; //
  if(onNAF)
    path="/nfs/dust/atlas/group/top/ttH_ML/ttW_run2/ttWqq/Reco_files/"+prod_version+"/mc16"+choose_tag+"/";  
  else
    path="/Users/grevtsov/Documents/working_files/ttH/Wtt_run2/Files/ttWqq/Reco_files/"+prod_version+"/mc16"+choose_tag+"/";

  cout << "path = " << path<< endl;

  if(!multi_file){
    path = path+name+".root";
  }



  TChain *weight_chain=new TChain("sumWeights");
  if(!multi_file){
    weight_chain->Add(path.c_str());
  }
  else{
    for(int i=0; i<num_split;i++){      
      tmp = path+name+"_"+to_string(i)+".root";
      weight_chain->Add(tmp.c_str());
    }
  }
  Double_t  sum_w=0;
  Float_t totalEventsWeighted;
  weight_chain->SetBranchAddress("totalEventsWeighted",&totalEventsWeighted);

  for(int i=0; i<weight_chain->GetEntries();i++){
    weight_chain->GetEntry(i);
    sum_w+=totalEventsWeighted;
  }
  cout<<" total sw:"<<to_string(sum_w)<<endl;

  if(!multi_file){
    ch->Add(path.c_str());
  }
  else{
    for(int i=0; i<num_split;i++){      
      tmp = path+name+"_"+to_string(i)+".root";
      ch->Add(tmp.c_str());
    }
  }

  cout << ch->GetNtrees()<< ", entr: "<< ch->GetEntries()<< endl;
  string  option=to_string(sum_w)+"/"+name+"-"+comp;

  ch->Process("source/reco_wqq.C+",option.c_str());

}
