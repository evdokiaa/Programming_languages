#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;



int main(int argc, char *argv[] ) {
        int N, K;
	ifstream file(argv[1]);
                file >> N;
                file >> K;
        int color[N]={0};
       
	for (int i=0; i<N; i++) file >> color[i];
	int found[K]={0}, c_found=0, min_chain=N+1, j=-1;
        for (int i=0; i<N; i++){
        	if (found[color[i]-1]==0) c_found++;		 
        	found[color[i]-1]++;				
        	if (c_found==K){			 
        		do{
         			j++;
         			found[color[j]-1]--;
         		}
        		while(found[color[j]-1]>0);
        		c_found--;
       		        if (min_chain>(i-j+1)) min_chain=i-j+1;
        	}	
    	}	
    	if (min_chain==N+1)  cout<< 0;
    	else cout << min_chain << endl;

}

