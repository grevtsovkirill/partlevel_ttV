void Zrun(string name="Sherpa", string comp="a"){
  TChain *ch=new TChain("particleLevel");
  string choose_tag="";
  string name1="";
  if(name.find("Sherpa")!= std::string::npos) name1="413023"; 
  else if(name.find("MG")!= std::string::npos) name1="410156";
 
  //string path="/Users/grevtsov/Documents/working_files/ttH/ttH-ML/Combination_ttV/Files/particle_level/"+name1+"d_v3.root";
  string path="/Users/grevtsov/Documents/working_files/ttH/ttH-ML/Combination_ttV/Files/particle_level/"+name1+"d_87_v1.root";
  cout << "path = " << path<< endl;

  ch->Add(path.c_str());
  cout << ch->GetNtrees()<< ", entr: "<< ch->GetEntries()<< endl;
  //eventually, start Proof Lite on cores
  //TProof::Open("workers=4");
  //ch->SetProof();
  ch->Process("souce/partlevel_ttZ.C+",name.c_str(),10000);
}
