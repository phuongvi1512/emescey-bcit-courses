/**
 * Project: assignment02
 * File: ReadWriteXML.java
 * Date: 26-Nov-07
 * Time: 12:51:02 AM
 */
package a00683006.bedz.util;

import java.beans.XMLDecoder;
import java.beans.XMLEncoder;
import java.io.*;
import java.util.*;
import a00683006.bedz.data.*;

/**
 * @author Steffen L. Norgren, A00683006
 *
 */
public class ReadWriteXML {
	public static void exportXML(HashMap<String, Guest> guestList,
			String path) throws IOException {
		XMLEncoder encodeXML = new XMLEncoder(
				new BufferedOutputStream(
						new FileOutputStream(path)));
		
		encodeXML.writeObject(guestList);
		encodeXML.close();
	}
	
	public static HashMap<String, Guest> importXML(String path) throws IOException {
		XMLDecoder decodeXML = new XMLDecoder(
				new BufferedInputStream(
						new FileInputStream(path)));

		HashMap<String, Guest> guestList = (HashMap<String, Guest>)decodeXML.readObject();
		decodeXML.close();
		
		return guestList;
	}
}
