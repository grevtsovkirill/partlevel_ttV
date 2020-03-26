void QQrun(string name="413008_ttw", string comp="xs", bool onNAF = true, bool multi_file = false, int num_split =4){
  TChain *ch=new TChain("particleLevel");
  string tmp="";
  string path="";
  string prod_version = "v2_0311"; //v1_0228
  if(onNAF)
    path="/nfs/dust/atlas/group/top/ttH_ML/ttW_run2/ttWqq/"+prod_version+"/";  
  else
    path="/Users/grevtsov/Documents/working_files/ttH/Wtt_run2/Files/ttWqq/"+prod_version+"/";

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
      tmp = path+name+to_string(i)+".root";
      weight_chain->Add(tmp.c_str());
    }
  }

  Double_t  sum_w=0;
  Float_t totalEventsWeighted;
  vector<float> *totalEventsWeighted_mc_generator_weights=0;
  weight_chain->SetBranchAddress("totalEventsWeighted",&totalEventsWeighted);
  weight_chain->SetBranchAddress("totalEventsWeighted_mc_generator_weights",&totalEventsWeighted_mc_generator_weights);

  int mc_weight_index=9999;
  mc_weight_index=0;

  for(int i=0; i<weight_chain->GetEntries();i++){
    weight_chain->GetEntry(i);
    if(i==0)    cout<< "mc_weight_index= "<< mc_weight_index<< endl;
    sum_w+=totalEventsWeighted_mc_generator_weights->at(mc_weight_index);
  }
  cout<<" total sw:"<<to_string(sum_w)<<endl;

  if(!multi_file){
    ch->Add(path.c_str());
  }
  else{
    for(int i=0; i<num_split;i++){      
      tmp = path+name+to_string(i)+".root";
      ch->Add(tmp.c_str());
    }
  }

  cout << ch->GetNtrees()<< ", entr: "<< ch->GetEntries()<< endl;
  string  option=to_string(sum_w)+"/"+name+"-"+comp;

  ch->Process("source/partlevel_wqq.C+",option.c_str());

}
