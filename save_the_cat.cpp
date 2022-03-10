#include <iostream>
#include <queue>
#include <tuple>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

using namespace std;

int main (int argc, char *argv[]) {
	queue<tuple<int,int,int>> water;
	int rows=0, columns=0;
	string line;
	ifstream file(argv[1]);
	while (getline (file,line)){ 
		rows++; 
		if (rows==1){
			columns=line.size();
		}
	}
	file.clear();
	file.seekg(0, ios::beg );     //epistrefei pointer sthn arxh tou arxeiou   

	char map[rows][columns];
	int flooded[rows][columns];
        for (int k=0; k<rows; k++){
                for(int p=0; p<columns; p++){
                        flooded[k][p]=rows*columns+1; //arxikopoihsh pinaka flooded 
                }
        }

	tuple<int,int,int> souri;   //gata 

	for (int i=0; i<rows; i++){
		for (int j=0; j<columns; j++){
			file >> map[i][j];          //diavasma apo arxeio
			if (map[i][j]=='W') water.push(make_tuple(i,j,0));       //an einai phgh prosthetw sthn oura gia flood fill algorithm- i,j syntetagmenes, 0 xronos  
			if (map[i][j]=='X') flooded[i][j]=-2;                    //an einai empodio -2 
			if (map[i][j]=='A') souri=make_tuple(i,j,0);             //an einai h gata ftiaxnw to tuple 
			}
		}
	file.close();
 
        //1o BFS 
	while (!water.empty()){         //oso h oura den einai kenh 
		if (flooded[get<0>(water.front())][get<1>(water.front())]==rows*columns+1){   //an to tetragwno den einai hdh plimirismeno 
				flooded[get<0>(water.front())][get<1>(water.front())]=get<2>(water.front());   //plymirhse to, get<2> = xronos plimirismatos 
		//elegje an einai se kapoia akrh, kai prosthese ta geitonika tetragwna sthn oura 
		if (get<0>(water.front())!=0)    water.push(make_tuple(get<0>(water.front())-1,get<1>(water.front()),  get<2>(water.front())+1));          
		if (get<0>(water.front())!=rows-1) water.push(make_tuple(get<0>(water.front())+1,get<1>(water.front()),  get<2>(water.front())+1));
		if (get<1>(water.front())!=0)    water.push(make_tuple(get<0>(water.front()),  get<1>(water.front())-1,get<2>(water.front())+1));
		if (get<1>(water.front())!=columns-1) water.push(make_tuple(get<0>(water.front()),  get<1>(water.front())+1,get<2>(water.front())+1)); 
	       	
		}
	water.pop(); //afairese apo thn oura 
	}
	
	//2o BFS
	water.push(souri);            //prosthetw th gata sthn oura 
	tuple<int,int,int> safe;   
	safe=make_tuple(-2,-2,-2);
	tuple<int,int,char> previous[rows][columns];
	bool beenthere[rows][columns]={0};                   
	beenthere[get<0>(souri)][get<1>(souri)]=1;          
	while (!water.empty()){         //oso h oura den einai kenh 
		if ( flooded[get<0>(water.front())][get<1>(water.front())]-1!=rows*columns+1 &&  flooded[get<0>(water.front())][get<1>(water.front())]-1 > get<2>(safe))  {
			get<0>(safe) = get<0>(water.front());
			get<1>(safe) = get<1>(water.front());
			get<2>(safe) = flooded[get<0>(water.front())][get<1>(water.front())]-1 ;
		}  //vriskoume ton asfalh xrono paramonhs, an autos einai megalyteros apo auton poy eixame vrei mexri tote, enhmerwnoume

		else if (flooded[get<0>(water.front())][get<1>(water.front())]-1 == get<2>(safe)){		// vriskei lejikografika mikroteres syntetagmenes
			if (get<0>(water.front())<get<0>(safe)) {
				get<0>(safe) = get<0>(water.front());
                        	get<1>(safe) = get<1>(water.front());
                        	get<2>(safe) = flooded[get<0>(water.front())][get<1>(water.front())]-1 ;
			}
			else if (get<0>(water.front())==get<0>(safe)){		
				if (get<1>(water.front())<get<1>(safe)){
					get<0>(safe) = get<0>(water.front());
                        		get<1>(safe) = get<1>(water.front());
                        		get<2>(safe) = flooded[get<0>(water.front())][get<1>(water.front())]-1 ;

						}}}
                //prosthetoume ta geitonika sthn oura, kratwntas kai thn kinhsh pou kaname 
		if (get<0>(water.front())!=rows-1 && (flooded[get<0>(water.front())+1][get<1>(water.front())]-1)>get<2>(water.front()) && beenthere[get<0>(water.front())+1][get<1>(water.front())]==0){ 
			previous[get<0>(water.front())+1][get<1>(water.front())] = make_tuple(get<0>(water.front()),get<1>(water.front()) , 'D') ;
			water.push(make_tuple(get<0>(water.front())+1,get<1>(water.front()),  get<2>(water.front())+1)) ;   
			beenthere[get<0>(water.front())+1][get<1>(water.front())]=1;
		}  //D
		if (get<1>(water.front())!=0 && (flooded[get<0>(water.front())][get<1>(water.front())-1]-1)>get<2>(water.front()) && beenthere[get<0>(water.front())][get<1>(water.front())-1]==0){    
			previous[get<0>(water.front())][get<1>(water.front())-1] = make_tuple(get<0>(water.front()),get<1>(water.front()) ,'L') ;  
			water.push(make_tuple(get<0>(water.front()),  get<1>(water.front())-1,get<2>(water.front())+1));  
			beenthere[get<0>(water.front())][get<1>(water.front())-1]=1;
		}     //L
		if (get<1>(water.front())!=columns-1 && (flooded[get<0>(water.front())][get<1>(water.front())+1]-1)>get<2>(water.front()) && beenthere[get<0>(water.front())][get<1>(water.front())+1]==0){
		       	previous[get<0>(water.front())][get<1>(water.front())+1] = make_tuple(get<0>(water.front()),get<1>(water.front()) ,'R') ;
			water.push(make_tuple(get<0>(water.front()),  get<1>(water.front())+1,get<2>(water.front())+1)); 
			beenthere[get<0>(water.front())][get<1>(water.front())+1]=1;
		}  //R
		if (get<0>(water.front())!=0 && (flooded[get<0>(water.front())-1][get<1>(water.front())]-1)>get<2>(water.front()) && beenthere[get<0>(water.front())-1][get<1>(water.front())]==0) {   
			previous[get<0>(water.front())-1][get<1>(water.front())] = make_tuple(get<0>(water.front()),get<1>(water.front()) ,'U') ;
			water.push(make_tuple(get<0>(water.front())-1,get<1>(water.front()),  get<2>(water.front())+1)); 
			beenthere[get<0>(water.front())-1][get<1>(water.front())]=1; 
		}     //U 
		water.pop();
 	}       
	if (get<2>(safe)==-2 || get<2>(safe)==rows*columns) cout << "infinity" << endl;
	else cout << get<2>(safe) << endl;	
	if ((get<0>(souri)==get<0>(safe) && get<1>(souri)==get<1>(safe)) || get<2>(safe)==-2 ) cout << "stay"  ;
	  else {
			string paths;
			char path=get<2>(previous[get<0>(safe)][get<1>(safe)]);
			int curr_i=get<0>(safe), curr_j=get<1>(safe);
			paths=path;
			while  (curr_i!=get<0>(souri) || curr_j!=get<1>(souri) ){
				int temp=curr_i;
				curr_i=get<0>(previous[curr_i][curr_j]);
				curr_j=get<1>(previous[temp][curr_j]);
				char chandler=get<2>(previous[curr_i][curr_j]);
				paths=chandler+paths;		
			}
			char exit[paths.size()+1];
			copy(paths.begin(), paths.end() ,exit);
			exit[paths.size()]='\0';
			for (unsigned int i=1; i<paths.size(); i++) cout << exit[i] ;
			//cout << paths << '\0' << endl; 
		}

		
	


		
}





	

