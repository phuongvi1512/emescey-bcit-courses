/**
 * Project: assignment02
 * File: DialogBox.java
 * Date: 25-Nov-07
 * Time: 10:28:03 PM
 */
package a00683006.bedz.ui;

import javax.swing.JOptionPane;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class DialogBox {
	public static void message(String message) {
		JOptionPane.showMessageDialog(null, message);
	}
	
	public static void message(String title, String message) {
		JOptionPane.showMessageDialog(null, message, title, JOptionPane.INFORMATION_MESSAGE);
	}
}
