/**
 * Project: assignment01
 * File: Bedz.java
 * Date: 24-Sep-07
 * Time: 2:17:28 AM
 */

package a00683006.bedz;

import a00683006.bedz.data.BedAndBreakfast;
import a00683006.bedz.test.BedzTest;
import a00683006.bedz.ui.Console;

/**
 * Is the driver class for this program. This class creates
 * a new Bed & Breakfast and instantiates the classes that will
 * populate all of the necessary data from stored files.
 * @author Steffen L. Norgren, A00683006
 *
 */
public class Bedz {
	
	private BedAndBreakfast bedAndBreakfast;
	private Console console;

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		new Bedz();
	}
	
	public Bedz() {
		bedAndBreakfast = new BedAndBreakfast("The Queen Anne Bed & Breakfast Inn");
		console = new Console();
		
		new BedzTest(bedAndBreakfast, console);
	}
}