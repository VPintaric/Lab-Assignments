import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.*;


public class SimTS {
	public static char[] track;
	public static List<String> acc_states = new ArrayList<String>();
	public static String cur_state;
	public static int cur_pos;
	public static List<Function> functions = new ArrayList<Function>();
	
	public static class Function{
		public String state;
		public char sym;
		public String next_state;
		public char next_sym;
		public char move_to;
		
		public Function(String line){
			String[] split = line.split("->");
			String[] left = split[0].split(",");
			String[] right = split[1].split(",");
			
			state = left[0];
			sym = left[1].charAt(0);
			next_state = right[0];
			next_sym = right[1].charAt(0);
			move_to = right[2].charAt(0);
 		}
	}
	
	public static boolean do_stuff(){
		boolean found = false;
		Function function = null;
		
		for(Function func : functions){
			if(func.state.equals(cur_state) && func.sym == track[cur_pos]){
				function = func;
				found = true;
			}
		}
		
		if(!found) return false;
		
		if((cur_pos == 0 && function.move_to == 'L') 
				|| (cur_pos == 69 && function.move_to == 'R'))
			return false;
		
		track[cur_pos] = function.next_sym;
		cur_state = function.next_state;
		if(function.move_to == 'R')
			cur_pos++;
		else if(function.move_to == 'L')
			cur_pos--;
		else{
			System.out.print("YOU LIED TO ME!!!\n");
			return false;
		}
		
		return true;
	}
	
	public static void print_stuff(){
		System.out.print(cur_state + "|");
		System.out.print(Integer.valueOf(cur_pos).toString() + "|");

		for(char c : track)
			System.out.print(c);
		System.out.print("|");	
		
		for(String state : acc_states){
			if(state.equals(cur_state)){
				System.out.print("1\n");
				return;
			}
		}
		System.out.print("0\n");
	}
	
	public static void main(String[] args) throws IOException {
		try(BufferedReader reader = new BufferedReader(new InputStreamReader(System.in))){
			String[] line;
			String linee;
			reader.readLine();
			reader.readLine();
			reader.readLine();
			reader.readLine();
			track = reader.readLine().toCharArray();
			line = reader.readLine().split(",");
			for(int i=0; i<line.length; i++)
				acc_states.add(line[i]);
			cur_state = reader.readLine();
			cur_pos = Integer.parseInt(reader.readLine());
			
			while((linee = reader.readLine()) != null){
				if(linee.equals(""))
					break;
				functions.add(new Function(linee));
			}	
		}
		
		while(do_stuff());
		
		print_stuff();
	}

}
