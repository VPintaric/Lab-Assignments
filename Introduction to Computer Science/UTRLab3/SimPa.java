import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class SimPa {
	public static String curState;
	public static String firstState;
	public static String firstStackState;
	public static List<String> stack;
	public static List<Function> functions;
	public static List<String> accStates;
	
	public static class Function {
		public String curState;
		public String input;
		public String curStackTop;
		public String nextState;
		public String nextStackTop;
		
		public Function(String input){
			String[] splitInput = input.split("->");
			String[] splitLeftSide = splitInput[0].split(",");
			this.curState = splitLeftSide[0];
			this.input = splitLeftSide[1];
			this.curStackTop = splitLeftSide[2];
			String[] splitRightSide = splitInput[1].split(",");
			this.nextState = splitRightSide[0];
			this.nextStackTop = splitRightSide[1];
		}
	}
	
	public static void do_epsilon_stuff(){
		boolean stuff_happened = true;
		
		while(stuff_happened){
			stuff_happened = false;
			
			for(Function func : functions){
				if(curState.equals(func.curState)
						&& (stack.get(stack.size()-1)).equals(func.curStackTop)
						&& "$".equals(func.input)){
					stuff_happened = true;
					curState = func.nextState;
					if(stack.size() > 1)
						stack.remove(stack.size()-1);
					if(!func.nextStackTop.equals("$"))
						for(int j = func.nextStackTop.length()-1; j>=0; j--)
							stack.add(func.nextStackTop.substring(j, j+1));
					
					System.out.print(curState + "#");
					if(stack.size() > 1)
						for(int i = stack.size()-1; i>0; i--)
							System.out.print(stack.get(i));
					else
						System.out.print(stack.get(0));
					System.out.print("|");
					break;
				}
			}
		}
	}
	
	public static void do_epsilon_stuff_with_ending(){
		boolean stuff_happened = true;
		
		while(stuff_happened){
			stuff_happened = false;
			
			for(Function func : functions){
				if(curState.equals(func.curState)
						&& (stack.get(stack.size()-1)).equals(func.curStackTop)
						&& "$".equals(func.input)){
					stuff_happened = true;
					curState = func.nextState;
					if(stack.size() > 1)
						stack.remove(stack.size()-1);
					if(!func.nextStackTop.equals("$"))
						for(int j = func.nextStackTop.length()-1; j>=0; j--)
							stack.add(func.nextStackTop.substring(j, j+1));
					
					System.out.print(curState + "#");
					if(stack.size() > 1)
						for(int i = stack.size()-1; i>0; i--)
							System.out.print(stack.get(i));
					else
						System.out.print(stack.get(0));
					System.out.print("|");
					
					if(accStates.contains(curState)){
						System.out.print("1\n");
						return;
					}
					break;
				}
			}
		}
		
		System.out.print("0\n");
	}
	
	public static void main(String[] args) {
		stack = new ArrayList<String>();
		functions = new ArrayList<Function>();
		accStates = new ArrayList<String>();
		String[] inputs = null;
		
		try{
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			String line = reader.readLine();
			inputs = line.split("\\|");
			
			line = reader.readLine();
			
			line = reader.readLine();
			
			line = reader.readLine();
			
			line = reader.readLine();
			String[] splitLine = line.split(",");
			for(String c : splitLine)
				accStates.add(c);
			
			firstState = reader.readLine();
			
			firstStackState = reader.readLine();
			
			while((line = reader.readLine()) != null){
				if(line.equals(""))
					break;
				functions.add(new SimPa.Function(line));
			}
		}
		catch(Exception exc){ System.out.println("Sumthing wery wery wrong!\n"); };
		
		for(String input : inputs){
			boolean function_exists = false;
			stack.clear();
			curState = firstState;
			stack.add("$");
			if(!firstStackState.equals("$"))
				stack.add(firstStackState);
			
			String[] input_chars = input.split(",");
			for(String c : input_chars){
				System.out.print(curState + "#");
				if(stack.size() > 1)
					for(int i = stack.size()-1; i>0; i--)
						System.out.print(stack.get(i));
				else
					System.out.print(stack.get(0));
				System.out.print("|");
				
				do_epsilon_stuff();
				
				function_exists = false;
				for(Function func : functions){
					if(curState.equals(func.curState)
							&& (stack.get(stack.size()-1)).equals(func.curStackTop)
							&& c.equals(func.input)){
						function_exists = true;
						curState = func.nextState;
						if(stack.size() > 1)
							stack.remove(stack.size()-1);
						if(!func.nextStackTop.equals("$"))
							for(int j = func.nextStackTop.length()-1; j>=0; j--)
								stack.add(func.nextStackTop.substring(j, j+1));
						break;
					}
				}
				if(!function_exists){
					System.out.print("fail|");
					break;
				}
			}
			
			if(function_exists){
				System.out.print(curState + "#");
				if(stack.size() > 1)
					for(int i = stack.size()-1; i>0; i--)
						System.out.print(stack.get(i));
				else
					System.out.print(stack.get(0));
				System.out.print("|");
			
				
				
				if(accStates.contains(curState))
					System.out.print("1\n");
				else
					do_epsilon_stuff_with_ending();
			}
			else
				System.out.print("0\n");
		}
	}
}
