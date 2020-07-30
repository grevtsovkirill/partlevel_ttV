import os

import argparse

parser = argparse.ArgumentParser(description='Inputs')
parser.add_argument('-p','--path', required=True, type=str, help='Folder to look over ')
args = parser.parse_args()

mypath = vars(args)["path"]


flist = ['c_Region_1_nJets.pdf', 'c_Region_0_lep_dPhi.pdf', 'c_Region_1_nBtagJets.pdf', 'c_Region_0_DRll01.pdf', 'c_Region_0_maxEta_ll.pdf', 'c_Region_4_lep_Pt_0.pdf', 'c_Region_1_min_DRl0j.pdf', 'c_Region_0_Bjet_Pt_0.pdf', 'c_Region_0_HT_jets.pdf', 'c_Region_1_lep_dPhi.pdf', 'c_Region_0_nJets.pdf', 'c_Region_3_HT_jets.pdf', 'c_Region_1_HT_jets.pdf', 'c_Region_1_DRll01.pdf', 'c_Region_4_DRll01.pdf', 'c_Region_0_min_DRl0j.pdf', 'c_Region_1_lep_Pt_0.pdf', 'c_Region_1_maxEta_ll.pdf', 'c_Region_1_Bjet_Pt_0.pdf', 'c_Region_4_nJets.pdf', 'c_Region_0_lep_Pt_0.pdf', 'c_Region_4_nBtagJets.pdf', 'c_Region_0_nBtagJets.pdf', 'c_Region_2_HT_jets.pdf']

print(len(flist))
#onlyfiles = [f for f in os.listdir(mypath)]
#print(onlyfiles)

for f in os.listdir(mypath):
    if f in flist:
        #print("match ",f)
        command = 'cp '+mypath+f+' tmp_files/tonote'
        os.system(command)
