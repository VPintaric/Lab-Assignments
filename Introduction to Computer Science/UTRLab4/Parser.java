import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;


public class Parser {
	public static String input;
	public static int index = 0;
	
	public static boolean S(){
		System.out.print("S");
		if(index < input.length() && input.charAt(index) == 'a'){
			index++;
			if(!A())
				return false;
			if(!B())
				return false;
			return true;
		}
		else if(index < input.length() && input.charAt(index) == 'b'){
			index++;
			if(!B())
				return false;
			if(!A())
				return false;
			return true;
		}
		else
			return false;
	}
	
	public static boolean A(){
		System.out.print("A");
		if(index < input.length() && input.charAt(index) == 'b'){
			index++;
			if(!C())
				return false;
			return true;
		}
		else if(index < input.length() && input.charAt(index) == 'a'){
			index++;
			return true;
		}
		else
			return false;
	}
	
	public static boolean B(){
		System.out.print("B");
		if(index < input.length() && input.charAt(index) == 'c'){
			index++;
			if(!(index < input.length() && input.charAt(index) == 'c'))
				return false;
			index++;
			if(!S())
				return false;
			if(!(index < input.length() && input.charAt(index) == 'b'))
				return false;
			index++;
			if(!(index < input.length() && input.charAt(index) == 'c'))
				return false;
			index++;
			return true;
		}
		else
			return true;
	}
	
	public static boolean C(){
		System.out.print("C");
		if(!A())
			return false;
		if(!A())
			return false;
		return true;
	}
	
	public static void main(String[] args) throws IOException {
		try(BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))){
			input = reader.readLine();
		}
		
		if(S() && index == input.length())
			System.out.printf("\nDA\n");
		else
			System.out.printf("\nNE\n");
	}

}
