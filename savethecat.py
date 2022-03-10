from collections import deque 
import sys

f=open(sys.argv[1])

lines=(f.readlines())
columns=len(lines[0])-1
rows=len(lines)
f.seek(0)


flooded=[[rows*columns+1 for x in range(columns)] for y in range(rows)]

water=deque()


for x in range(0,rows):
    for y in range(0,columns+1):
        c=f.read(1)
        if c=='W':
            water.append((x,y,0))
        elif c=='X':
            flooded[x][y]=-2
        elif c=='A':
            souri=(x,y,0)

f.close()


while water:
    front=water.popleft()
    if flooded[front[0]][front[1]]==rows*columns+1:
        flooded[front[0]][front[1]]=front[2]
        if front[0]!=0:
            water.append((front[0]-1,front[1],front[2]+1))
        if front[0]!=rows-1:
            water.append((front[0]+1,front[1],front[2]+1))
        if front[1]!=0:
            water.append((front[0],front[1]-1,front[2]+1))
        if front[1]!=columns-1:
            water.append((front[0],front[1]+1,front[2]+1))
    
water.append(souri)
safe=[-2,-2,-2]
beenthere=[[0 for x in range(columns)] for y in range(rows)]
previous=[[0 for x in range(columns)] for y in range(rows)]

while water:
    front=water.popleft()
    if flooded[front[0]][front[1]]-1!=rows*columns+1 and flooded[front[0]][front[1]]-1 > safe[2]:
        safe[0]=front[0]
        safe[1]=front[1]
        safe[2]=flooded[front[0]][front[1]]-1
    elif flooded[front[0]][front[1]]-1 == safe[2]: 
        if front[0]<safe[0]:
            safe[0]=front[0]
            safe[1]=front[1]
            safe[2]=flooded[front[0]][front[1]]-1
        elif front[0]==safe[0]:
            if front[1]<safe[1]:
                safe[0]=front[0]
                safe[1]=front[1]
                safe[2]=flooded[front[0]][front[1]]-1
    if front[0]!=rows-1 and flooded[front[0]+1][front[1]]-1>front[2] and beenthere[front[0]+1][front[1]]==0:
        previous[front[0]+1][front[1]]=(front[0],front[1],'D')
        water.append((front[0]+1,front[1],front[2]+1))
        beenthere[front[0]+1][front[1]]=1
    if front[1]!=0 and flooded[front[0]][front[1]-1]-1>front[2] and beenthere[front[0]][front[1]-1]==0:
        previous[front[0]][front[1]-1]=(front[0],front[1],'L')
        water.append((front[0],front[1]-1,front[2]+1))
        beenthere[front[0]][front[1]-1]=1
    if front[1]!=columns-1 and flooded[front[0]][front[1]+1]-1>front[2] and beenthere[front[0]][front[1]+1]==0:
        previous[front[0]][front[1]+1]=(front[0],front[1],'R')
        water.append((front[0],front[1]+1,front[2]+1))
        beenthere[front[0]][front[1]+1]=1
    if front[0]!=0 and flooded[front[0]-1][front[1]]-1>front[2] and beenthere[front[0]-1][front[1]]==0:
        previous[front[0]-1][front[1]]=(front[0],front[1],'U')
        water.append((front[0]-1,front[1],front[2]+1))
        beenthere[front[0]-1][front[1]]=1


if (safe[2]==-2 or safe[2]==rows*columns):
    print('infinity')
else:
    print(safe[2])
if souri[0]==safe[0] and souri[1]==safe[1] or safe[2]==-2:
    print('stay')
else:
    path=previous[safe[0]][safe[1]][2]
    curr_i=safe[0]
    curr_j=safe[1]
    while (curr_i!=souri[0] or curr_j!=souri[1]):
        temp=curr_i
        curr_i=previous[curr_i][curr_j][0]
        curr_j=previous[temp][curr_j][1]
        if (curr_i!=souri[0] or curr_j!=souri[1]):
            path=previous[curr_i][curr_j][2]+path
    print(path)    
   
                

                



        


