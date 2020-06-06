getDL1function= '''
using namespace ROOT::VecOps;

'''

countJets= '''
int CountJets(RVec<float> DL1c,RVec<float> DL1b, float cut) {
    int njets = 0;
    for(unsigned int i = 0 ; i < DL1c.size() ; ++i){
         if(DL1c[i]>=cut && DL1b[i]<2.195)
            ++njets;
    }
    return njets;
}
'''
