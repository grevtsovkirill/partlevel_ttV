from ROOT import *
import ROOT
import array

from  definitions import *


ROOT.gInterpreter.Declare(getDL1function+countJets)


def main():
    ntupleLoc = 'Files/'

    bkgFiles = ["ctag_410470_d"]
    bkgFilesToUse=ROOT.vector("string")()
    for infile in bkgFiles:
        fn = ntupleLoc+infile+'.root'
        inFile=ROOT.TFile(fn,'r')
        if inFile.IsZombie() or not inFile.Get("ftagTree"):
            bkgFiles.remove(infile)
            inFile.Close()
            continue
        bkgFilesToUse.push_back(fn)

    dbkg = RDataFrame("ftagTree", bkgFilesToUse)
    print("Signal and BG dataframes loaded...")

if __name__== "__main__":
    main()
