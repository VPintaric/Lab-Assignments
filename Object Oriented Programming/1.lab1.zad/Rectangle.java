package hr.fer.oop.lab1.topic1.prob1;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.String;

public class Rectangle {

	/**
	 * Method reads one float from stdio
	 * @return float
	 * @throws IOException
	 */
	public static float ReadWidth() throws IOException {
		
		float width;
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		
		while(true){
			System.out.format("Please provide width: ");
			String line = reader.readLine();
			line = line.trim();
			
			if(line.isEmpty()){
				System.out.format("Nothing was given.\n");
				continue;
			}
			
			width = Float.parseFloat(line);
		
			if(width <= 0) System.out.format("Width has to be a positive number.\n");
			else return width;
		}

	}
	
	/**
	 * Method reads one float from stdio.
	 * @return float
	 * @throws IOException
	 */
	public static float ReadHeight() throws IOException {
		
		BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		float height;
		
		while(true){
			System.out.format("Please provide height: ");
			String line = reader.readLine();
			line = line.trim();
			
			if(line.isEmpty()){
				System.out.format("Nothing was given.\n");
				continue;
			}
			
			height = Float.parseFloat(line);
			
			if(height <= 0) System.out.format("Height has to be a positive number.\n");
			else return height;
			}
	}
	
	/**
	 * Main method
	 * @param args Program startup arguments
	 * @throws IOException
	 */
	public static void main(String[] args) throws IOException {
		float height = 0, width = 0, area, perimeter;
		
		if(args.length == 2){
			width = Float.parseFloat(args[0]);
			height = Float.parseFloat(args[1]);
		}
		
		else if(( args.length > 2) || (args.length == 1)){
			System.out.format("Invalid number of arguments was provided.\n");
			System.exit(99);
		}
		
		else{
			width = ReadWidth();
			height = ReadHeight();
		}
		
		area = width * height;
		perimeter = 2*width + 2*height;
		
		System.out.format("You have specified a rectangle with width %.1f and height %.1f. ", width, height);
		System.out.format("Its area is %.1f and its perimeter is %.1f.\n", area, perimeter);
		
		}
}
