import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.IOException;
import java.util.*;


public class hello{
	
	
	int rows; int columns;
	int flooded[][];
	int beenthere[][];
	Triplet previous[][];
	
	Queue<Triplet> water = new ArrayDeque<Triplet>();
	
	Triplet souri;
	Triplet safe;
	
	
	public void Set(int x,int y) {
		this.safe=new Triplet(-2,-2,-2);
		this.souri=new Triplet(1,1,0);
		this.rows=x;
		this.columns=y;		
		this.flooded=new int[rows][columns]; 
		this.beenthere=new int[rows][columns];
		this.previous=new Triplet[rows][columns];
		
		for (int i=0; i<rows; i++) {
			for(int j=0; j<columns; j++) {
				this.flooded[i][j]=rows*columns+1;
				this.beenthere[i][j]=0;
			}
		}
	}
	
	
	public void flooding() {
		while(!water.isEmpty()) {
			//System.out.println("f1");
			Triplet front = new Triplet(water.remove());
			if (flooded[front.x][front.y]==rows*columns+1) {
				flooded[front.x][front.y]=front.z;
				if (front.x!=0) {
					water.add(new Triplet((front.x)-1,front.y,(front.z)+1));
				}
				if (front.x!=rows-1) {
					water.add(new Triplet((front.x)+1,front.y,(front.z)+1));
				}
				if (front.y!=0) {
					water.add(new Triplet(front.x,(front.y)-1,(front.z)+1));
				}
				if (front.y!=columns-1) {
					water.add(new Triplet(front.x,(front.y)+1,(front.z)+1));
				}
			}
		}
	}
	
	public void saveSouri () {
		water.add(souri);
		while(!water.isEmpty()) {
			//System.out.println("f2");
			Triplet front = new Triplet(water.poll());
			if ((flooded[front.x][front.y]-1!=rows*columns+1) && (flooded[front.x][front.y]-1>safe.z)) 
			{
				safe.x=front.x;
				safe.y=front.y;
				safe.z=flooded[front.x][front.y]-1;
			}
		    else if(flooded[front.x][front.y]-1==safe.z) {
				if (front.x<safe.x) {
					safe.x=front.x;
					safe.y=front.y;
					safe.z=flooded[front.x][front.y]-1;
				}
				else if(front.x==safe.x) {
					if (front.y<safe.y) {
						safe.x=front.x;
						safe.y=front.y;
						safe.z=flooded[front.x][front.y]-1;
					}
				}
			}
			//System.out.println("f2");
			if (front.x!=rows-1 && flooded[(front.x)+1][front.y]-1>front.z && beenthere[front.x+1][front.y]==0) {
				previous[front.x+1][front.y]=new Triplet(front.x,front.y,'D');
				water.add(new Triplet(front.x+1,front.y,front.z+1));
				beenthere[front.x+1][front.y]=1;			
			}
			if (front.y!=0 && flooded[front.x][(front.y)-1]-1>front.z && beenthere[front.x][front.y-1]==0) {
				previous[front.x][front.y-1]=new Triplet(front.x,front.y,'L');
				water.add(new Triplet(front.x,front.y-1,front.z+1));
				beenthere[front.x][front.y-1]=1;				
			}
			if (front.y!=columns-1 && flooded[front.x][(front.y)+1]-1>front.z && beenthere[front.x][front.y+1]==0) {
				previous[front.x][front.y+1]=new Triplet(front.x,front.y,'R');
				water.add(new Triplet(front.x,front.y+1,front.z+1));
				beenthere[front.x][front.y+1]=1;	
			}
			if (front.x!=0 && flooded[front.x-1][front.y]-1>front.z && beenthere[front.x-1][front.y]==0) {
				previous[front.x-1][front.y]=new Triplet(front.x,front.y,'U');
				water.add(new Triplet(front.x-1,front.y,front.z+1));
				beenthere[front.x-1][front.y]=1;	
			}
			//System.out.println("f3");
		}
	
		}
			
		
	public void findPath() {
		if (safe.z==-2 || safe.z==rows*columns) {
			System.out.println("infinity");
		}
		else {
			System.out.println(safe.z);
		}
		if ((souri.x==safe.x && souri.y==safe.y) || safe.z==-2) {
			System.out.println("stay");
		}
		else {
			char path =previous[safe.x][safe.y].c;
			String paths = new String();
			paths=path+paths;
			int curr_i=safe.x; 
			int curr_j=safe.y;
			while (curr_i!=souri.x || curr_j!=souri.y) {
				System.out.print(curr_i);
				System.out.println(curr_j);
				int temp=curr_i;
				curr_i=previous[curr_i][curr_j].x;
				curr_j=previous[temp][curr_j].y;
				if(curr_i!=souri.x || curr_j!=souri.y) {
					paths=previous[curr_i][curr_j].c+paths;
				}
				
			}
			System.out.println(paths);


	}
		
	}


public static void main (String[] args)throws IOException { 
	
	//hello Save = new hello();
	/*hello.Set(rows,columns);
	System.out.println(rows);
	Save.flooding();
	Save.saveSouri();
	Save.findPath();*/

    Scanner reader = new Scanner(new FileInputStream(args[0]));
    
    int arows,acolumns;
    try (BufferedReader br = new BufferedReader(new FileReader(args[0]))) {
    	   String line = null;
    	   arows = 0;
    	   acolumns = 0;
		while ((line = br.readLine()) != null) {
            arows++; 
    	      acolumns = line.length();
    	   }
	   	
		hello Save = new hello();
		hello.Set(arows,acolumns);
		
    	try (BufferedReader rt = new BufferedReader(new FileReader(args[0]))) {
    	int r;
    	for (int i=0; i< arows; i++) {
    		for (int j=0; j< acolumns+1; j++) {
    			r = rt.read();
    			if (r != -1){
    				 char ch = (char) r; 
    				 if (j!= acolumns) {
    				    if (ch == 'W') 
    				    	water.add(new Triplet(i,j,0)); 
    				     if (ch == 'X') 
    				    	 flooded[i][j]=-2;
    				     if (ch =='A')
    				    	 souri = new Triplet(i,j,0);}
    				    
    		            System.out.print(ch);
    		            
    			}
    			
    			} }
		Save.flooding();
    	Save.saveSouri();
    	
    	//for (int i=0; i<rows;i++) {
    		//for(int j=0;j<columns;j++) {
    			//System.out.print(flooded[i][j]);}}
    	
		Save.findPath(); 
		//System.out.println(rows);
		//System.out.println(columns);
    		        	}
    		            	
    				
    	   }
} }
