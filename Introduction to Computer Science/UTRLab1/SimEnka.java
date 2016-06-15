
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class SimEnka {
	
	public static class State implements Comparable<State> {
		private String name;
		private boolean accepted;
		
		public State(String name, Boolean accepted){
			this.name = name;
			this.accepted = accepted;
		}
		
		public boolean isAccepted(){
			return accepted;
		}
		
		public String getName(){
			return name;
		}
		
		public int compareTo(State o){
			return name.compareTo(o.getName());
		}
		
		@Override
		public String toString(){
			return name;
		}
		
		public boolean isEmpty(){
			if(name.equals("#"))
				return true;
			return false;
		}
		
		@Override
		public boolean equals(Object o){
			if(!(o instanceof State))
				return false;
			State x = (State) o;
			if(x.getName().equals(name))
				return true;
			return false;
		}
	}


	public static class Function {
		private String state;
		private String symbol;
		private String[] next_states;
		
		public Function(String function){
			String[] parts = function.split("->");
			next_states = parts[1].split(",");
			String[] parts2 = parts[0].split(",");
			state = parts2[0];
			symbol = parts2[1];
		}
		
		public Function(String state, String symbol){
			this.state = state;
			this.symbol = symbol;
			next_states = null;
		}
		
		public String getState(){
			return state;
		}
	
		public String getSymbol(){
			return symbol;
		}
		
		public String[] getNextStates(){
			return next_states;
		}
		
		@Override
		public boolean equals(Object o){
			if(!(o instanceof Function))
				return false;
			Function x = (Function) o;
			if((x.getState().equals(state)) && (x.getSymbol().equals(symbol)))
				return true;
			return false;
		}
	}

	
	public static boolean isAccepted(String state, String[] acc_states){
		for(String cur : acc_states){
			if(cur.equals(state))
				return true;
		}
		return false;
	}
	
	public static void sort_and_print(List statesList){
		boolean first = true;
		Collections.sort(statesList);
		for(int i = 0; i < statesList.size(); i++){
			if(((State) statesList.get(i)).isEmpty() && statesList.size() > 1)
				continue;
			if(!first)
				System.out.print(",");
			else
				first = false;
			System.out.print(statesList.get(i).toString());
		}
	}
	
	public static void do_epsilon(List statesList, List functions, String[] acc_states){
		boolean do_again = true;
		while(do_again){
			do_again = false;
			for(int i = 0; i < statesList.size(); i++){
				for(int j = 0; j < functions.size(); j++){
					if(((State) statesList.get(i)).getName().equals(((Function) functions.get(j)).getState())
							&& ((Function) functions.get(j)).getSymbol().equals("$")){
						String[] new_states = ((Function) functions.get(j)).getNextStates();
						for(String state : new_states){
							if(!statesList.contains(new State(state, false))){
								statesList.add(new State(state, isAccepted(state, acc_states)));
								do_again = true;
							}
						}
					}
				}
			}
		}
		Collections.sort(statesList);
	}
	
	public static void main(String[] args) {
		List statesList = new ArrayList(100);
		List functions = new ArrayList(100);
		List temp_states = new ArrayList();
		
		try{
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			String line = reader.readLine();
			String[] inputs = line.split("\\|");
			line = reader.readLine();
			String[] states = line.split(",");
			line = reader.readLine();
			String[] alpha = line.split(",");
			line = reader.readLine();
			String[] acc_states = line.split(",");
			line = reader.readLine();
			String start_state = line;
			while((line = reader.readLine()) != null){
				if(line.equals(""))
					break;
				functions.add(new Function(line));
			}
			
			for(String input : inputs){
				statesList.add(new State(start_state, isAccepted(start_state, acc_states)));
				String[] splitted = input.split(",");
				for(String cur_c : splitted){
					do_epsilon(statesList, functions, acc_states);
					sort_and_print(statesList);
					System.out.print("|");
					
					for(int i = 0; i < statesList.size(); i++){
						String name = ((State) statesList.get(i)).getName();
						if(functions.contains(new Function(name, cur_c))){
							Function function = (Function) functions.get(functions.indexOf(new Function(name, cur_c)));
							for(String cur_state : function.getNextStates()){
								State state = new State(cur_state, isAccepted(cur_state, acc_states));
								if(!temp_states.contains(state))
									temp_states.add(state);
							}
						}
						else if(!temp_states.contains(new State("#", false))){
							temp_states.add(new State("#", false));
						}
					}
					statesList.clear();
					statesList.addAll(temp_states);
					temp_states.clear();
				}
				do_epsilon(statesList, functions, acc_states);
				sort_and_print(statesList);
				System.out.print("\n");
				statesList.clear();
			}
		}
		
		catch(IOException exc){
			exc.printStackTrace();
		}
	}

}
