import java.util.ArrayDeque;
import java.util.HashSet;
import java.util.Queue;
import java.util.Set;

/* A class that implements a solver that explores the search space
 * using breadth-first search (BFS).  This leads to a solution that
 * is optimal in the number of moves from the initial to the final
 * state.
 */
public class BFSolver  {
	 private int Lout;
	 private int Rout;
	
  
  public ZtallocState solve (ZtallocState initial) {
    Set<ZtallocState> seen = new HashSet<>();
    Queue<ZtallocState> remaining = new ArrayDeque<>();
    remaining.add(initial);
    seen.add(initial);
    while (!remaining.isEmpty()) {
      ZtallocState s = remaining.remove();
      if (s.isFinal(Lout,Rout)) return s;
      for (ZtallocState n : s.next())
        if (!seen.contains(n) ){
          remaining.add(n);
          seen.add(n);
        }
    }
    return null;
  }
  public void SetLoutRout(int a, int b) {
	  Lout=a;
	  Rout=b;
  }
  
  
}
