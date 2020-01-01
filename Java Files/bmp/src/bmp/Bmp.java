package bmp;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;


public class Bmp {

    public static void main(String[] args) throws FileNotFoundException {
        Scanner input = new Scanner(new File("t.txt"));
        while (input.hasNextLine()) {
            String s = input.nextLine();
            //printCommas(s);
            printBinArray(s);
        }
    }
    
    public static void printCommas(String s) {
        int count = 0;
        for (int i = 0; i < s.length(); ++i) {
            count++;
            if (count == 8) {
                System.out.println(s.substring(0, count));
                printCommas(s.substring(count));
            }
        }
    }
    
    public static void printBinArray(String s) {
        System.out.println("B" + s + ",");
    }

}    
