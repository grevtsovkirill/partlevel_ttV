import os

#samples = ['413008_ttw','410472_ttbar','410156_ttZnunu','410157_ttZqq','410218_ttee','410219_ttmumu','410220_tttautau']
samples = ['410220_tttautau']
for i in samples:
    tick = "'"
    command = 'root -l -b -q '+tick+'QQrun.C("'+i+'")'+tick
    print(command)
    os.system(command)
