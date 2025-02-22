/**
 * Week #1 - Lab #1 Questions:
 * 1. What does this algorithm compute?
 *    This algorithm computes the smallest and largest value in an array
 *    of size n-1 and then returns the difference.
 *    
 * 2. What is its basic operation?
 *    The basic operation is an assignment operation.
 *    
 * 3. How many times is the basic operation executed?
 *    The basic operation is executed S(2n + 1) using a worst-case scenario
 * 
 * 4. What is the time efficiency of this algorithm?
 *    T(2n);
 * 
 * 5. Run your program on different magnitudes of random input size n 
 *    (e.g, n = 10, 20, 100, 500, 1000, ���) and verify its running time.
 *    We need to use a size of 100 000 or greater before we are able to gleam
 *    any meaningful running times.
 */
import java.util.*;

public class Lab01 {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		System.out.println("Result: " + Secret(MakeSeqArray(100000)));
	}
	
	/**
	 * An array of A[0..n - 1] of n real numbers
	 * @param array
	 */
	private static int Secret(int[] array) {
		long start = Calendar.getInstance().getTimeInMillis();

		int minVal, maxVal;
		
		minVal = array[0];
		maxVal = array[0];
		
		for (int i = 0; i < array.length; i++) {
			if (array[i] < minVal) {
				minVal = array[i];
			}
			else if (array[i] > maxVal) {
				maxVal = array[i];
			}
		}
		
		System.out.println("Run Time: " + (Calendar.getInstance().getTimeInMillis() - start) + "ms");
		return maxVal - minVal;
	}
	
	private static int[] MakeRandArray(int size) {
		int[] array = new int[size];
		Calendar rightNow = Calendar.getInstance();
		Random generator = new Random(rightNow.getTimeInMillis());
		
		for (int i = 0; i < size; i++) {
			array[i] = generator.nextInt();
		}
		
		return array;
	}

	private static int[] MakeSeqArray(int size) {
		int[] array = new int[size];
		
		for (int i = 0; i < size; i++) {
			array[i] = i;
		}
		
		return array;
	}
}
