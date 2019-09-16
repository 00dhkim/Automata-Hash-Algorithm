isCrash = 0
li1 = list()

f = open("output.txt","r")
li1 = f.readlines()
f.close()

for i in range(len(li1)):
    for j in range(i):
        if li1[i] == li1[j]:
            print("*"*20,"\nCRASH\n","*"*20)
            input('CRASH && CRASH &&'*7,'CRASH')
    if(not i%100): print(i)
input('press any key to exit')
