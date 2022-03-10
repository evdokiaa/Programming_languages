
public class Triplet {
	int x;
	int y;
	int z;
	char c;
	
	
	public Triplet(int x, int y, int z) {
		this.x=x;
		this.y=y;
		this.z=z;
	}
	
	public Triplet(int x,int y, char c) {
		this.x=x;
		this.y=y;
		this.c=c;
	}
	
	public Triplet(Triplet second) {
		this.x=second.x;
		this.y=second.y;
		this.z=second.z;
		this.c=second.c;
	}
	
	
	

}
