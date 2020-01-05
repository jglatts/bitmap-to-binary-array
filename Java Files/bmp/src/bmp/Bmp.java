/**
 *  ___                   ___    ___                    _               
 * | o )()||  _ _  _  _  |_ _|  | o )()  _  _   ___    / \  _  _  _ __  
 * | o \||| ]/ \ \/o\/o\  | /o\ | o \|||/ \/o\ /_\ V7 | o |/_|/_|/o\\ V7
 * |___/L|L|L_n_n|\_,]_/  |_\_/ |___/L|L_n|\_,]L| )/  |_n_|L| L| \_,])/ 
 *                   L|                          //                 //                                           
 * 
 *  Java Program to convert a Bitmap image into a Binary Array
 *  Used to display images on LCD screens, etc..
 * 
 *  @author: John G.
 */
package bmp;

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintStream;
import java.util.Scanner;


public class Bmp {
    
    public static void main(String[] args) throws FileNotFoundException {
        Scanner img = new Scanner(new File("b.txt"));
        String f = getFileName();
        PrintStream outPut = new PrintStream(new File(f));
        while (img.hasNextLine()) 
            writeBinaryFile(img.nextLine(), outPut);
        System.out.println("\n\nThe Binary Array is saved at: " + f);
    }
    
    public static String getFileName() {
        Scanner f = new Scanner(System.in);
        System.out.print("Enter a file name to save the Binary Array to: ");
        return f.nextLine();
    }
    
    public static void writeBinaryFile(String s, PrintStream p) {
        int count = 0;
        for (int i = 0; i < s.length(); ++i) {
            count++;
            if (count == 8) {
                p.println("B" + s.substring(0, count) + ",");
                writeBinaryFile(s.substring(count), p);
            }
        }    
    }
    
}    
