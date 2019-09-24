void run(string name="Sherpa", string comp="a"){
  TChain *ch=new TChain("particleLevel");
  string choose_tag="";
  string name1="";
  if(name.find("Sherpa")!= std::string::npos) name1="413008"; 
  else if(name.find("MG")!= std::string::npos) name1="410155";
 
  //string path="/Users/grevtsov/Documents/working_files/ttH/ttH-ML/Combination_ttV/Files/particle_level/"+name1+"d_v3.root";
  string path="/Users/grevtsov/Documents/working_files/ttH/ttH-ML/Combination_ttV/Files/particle_level/"+name1+"d_87_v1.root";
  cout << "path = " << path<< endl;



  TChain *weight_chain=new TChain("sumWeights");
  weight_chain->Add(path.c_str());
  Double_t  sum_w=0;
  Float_t totalEventsWeighted;
  vector<float> *totalEventsWeighted_mc_generator_weights=0;
  weight_chain->SetBranchAddress("totalEventsWeighted",&totalEventsWeighted);
  weight_chain->SetBranchAddress("totalEventsWeighted_mc_generator_weights",&totalEventsWeighted_mc_generator_weights);


  // MG nominal =0;    scaleup = 4, scaledown = 8
  // Sherpa nom = 0/7, scaleup = 10, scaledown= 4
  int mc_weight_index=9999;
  
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

  for(int i=0; i<weight_chain->GetEntries();i++){
    weight_chain->GetEntry(i);
    if(i==0)    cout<< "mc_weight_index= "<< mc_weight_index<< endl;
    sum_w+=totalEventsWeighted_mc_generator_weights->at(mc_weight_index);
  }
  cout<<" total sw:"<<to_string(sum_w)<<endl;

  //new option definition; "sm"_"opt"
  ch->Add(path.c_str());
  cout << ch->GetNtrees()<< ", entr: "<< ch->GetEntries()<< endl;
  string  option=to_string(sum_w)+"_"+name;
  ch->Process("source/partlevel_ttW.C+",option.c_str());
}
