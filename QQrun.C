

void QQrun(string name="413008_ttw", string comp="xs"){
  /*
    410156_ttZnunu.root
    410157_ttZqq.root
    410218_ttee.root
    410219_ttmumu.root
    410220_tttautau.root
    413008_ttw.root
  */


  TChain *ch=new TChain("particleLevel");
  string choose_tag="";
  string name1="";
  //if(name.find("Sherpa")!= std::string::npos) name1="413008_ttw"; 
  //else if(name.find("MG")!= std::string::npos) name1="410155";

  string path="/Users/grevtsov/Documents/working_files/ttH/Wtt_run2/Files/ttWqq/v0_0206/"+name+".root";;
  cout << "path = " << path<< endl;



  TChain *weight_chain=new TChain("sumWeights");
  //weight_chain->Add((path+"a.root").c_str());
  //weight_chain->Add((path+"d.root").c_str());
  //weight_chain->Add((path+"e.root").c_str());
  weight_chain->Add(path.c_str());
  Double_t  sum_w=0;
  Float_t totalEventsWeighted;
  vector<float> *totalEventsWeighted_mc_generator_weights=0;
  weight_chain->SetBranchAddress("totalEventsWeighted",&totalEventsWeighted);
  weight_chain->SetBranchAddress("totalEventsWeighted_mc_generator_weights",&totalEventsWeighted_mc_generator_weights);


  // MG nominal =0;    scaleup = 4, scaledown = 8
  // Sherpa nom = 0/7, scaleup = 10, scaledown= 4
  int mc_weight_index=9999;
  mc_weight_index=0;
  //Only nominal
  /*
  if(name.compare("Sherpa")==0){ 
    mc_weight_index=0;
  }
  else if(name.compare("MG")==0){
    mc_weight_index=0;
  }
  else if (name.find("SherpaScaleUp")!= std::string::npos){
    mc_weight_index=10;
  }
  else if (name.find("SherpaScaleDown")!= std::string::npos){
    mc_weight_index=4;
  }  else if (name.find("MGScaleUp")!= std::string::npos){
    mc_weight_index=4;
  }
  else if (name.find("MGScaleDown")!= std::string::npos){
    mc_weight_index=8;
  }
  else {std::cout << " error - incorrect variation. "<<  std::endl;
  }
  //*/

  for(int i=0; i<weight_chain->GetEntries();i++){
    weight_chain->GetEntry(i);
    if(i==0)    cout<< "mc_weight_index= "<< mc_weight_index<< endl;
    sum_w+=totalEventsWeighted_mc_generator_weights->at(mc_weight_index);
  }
  cout<<" total sw:"<<to_string(sum_w)<<endl;

  ch->Add(path.c_str());
  cout << ch->GetNtrees()<< ", entr: "<< ch->GetEntries()<< endl;
  string  option=to_string(sum_w)+"/"+name+"-"+comp;

  ch->Process("source/partlevel_wqq.C+",option.c_str());

}
