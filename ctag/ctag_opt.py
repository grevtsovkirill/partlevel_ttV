import uproot
import pandas as pd
import numpy as np
from  definitions import *

def main():
    ntupleLoc = 'Files/'

    bkgFiles = ["ctag_410470_d"]
    dbkg = pd.DataFrame()
    for infile in bkgFiles:
        fn = ntupleLoc+infile+'.root'
        inFile = uproot.open(fn)["ftagTree"]
        dbkg = dbkg.append(inFile.pandas.df())
    
    print("BG dataframes loaded:", dbkg[:15])

if __name__== "__main__":
    main()
