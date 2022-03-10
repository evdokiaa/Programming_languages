from collections import deque
import sys

def isFinal(min,max,Lout,Rout):
    if (min>=Lout and max<=Rout):
        return True
    
def readnext():
    c=next(f).split()
    print(c[1])

f=open(sys.argv[1])
N=int(next(f))

for x in range(N):
    c=next(f).split()
    initial=(int(c[0]),int(c[1]),'')
    Lout=int(c[2])
    Rout=int(c[3])
    remaining=deque()
    states=1
    remaining.append(initial)
    while(remaining):
        s=remaining.popleft()
        if (isFinal(s[0],s[1],Lout,Rout)):
            if(s[2]==''):
                print('EMPTY')
            else:
                print(s[2])
            break
        if (s[0]!=0 and s[1]!=0):
            remaining.append((s[0]//2,s[1]//2,s[2]+'h'))
            states=states+1
        elif(s[0]==0 and s[1]!=0):
            remaining.append((0,s[1]//2,s[2]+'h'))
            states=states+1
        remaining.append((s[0]*3+1,s[1]*3+1,s[2]+'t'))
        states=states+1
        if (states>999999):
             print('IMPOSSIBLE')
             break
        

f.close()

    

