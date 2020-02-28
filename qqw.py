import os

samples = ['413008_ttw','410155_ttw','410156_ttZnunu','410157_ttZqq','410218_ttee','410219_ttmumu','410220_tttautau']
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
