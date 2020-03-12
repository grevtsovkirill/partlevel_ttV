import os

samples = ['413008_ttw','410155_ttw','410156_ttZnunu','410157_ttZqq','410218_ttee','410219_ttmumu','410220_tttautau','410472_ttbar',
           '410658_topt','410659_atopt','410644_tops','410645_atops','304014_threeTop','410080_fourTop','410081_ttww','410408_WtZ']
#suff = "norm" ,'410472_ttbar'
suff = "xs"
#samples = ['410220_tttautau']
for i in samples:
    tick = "'"
    option = ""
    if suff:
        option = '","'+suff
    command = 'root -l -b -q '+tick+'QQrun.C("'+i+option+'")'+tick
    print(command)
    os.system(command)
