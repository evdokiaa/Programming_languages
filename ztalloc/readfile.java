import java.io.File;
import java.util.*;

public class readfile {
	private Scanner x;
	
	public void openFile() {
		try {
			x=new Scanner(new File("z1.txt"));
		}
		catch (Exception e) {
			System.out.println("couldnotfindfile");
		}
	}
		
		public void readLoops() {
			while(x.hasNext()) {
				String a = x.next();
				System.out.println(a);
			}
		}
	}

