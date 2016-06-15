import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class MinDka {
	
	public static List<String> states = new ArrayList<String>(); //MAIN list of states (we are minimizing this list)
	public static List<String> alphabet = new ArrayList<String>(); //list of all the symbols in the alphabet
	public static List<String> acc_states = new ArrayList<String>(); //list of accepted states (no need to change this after first initilization
	public static String first_state; //starting state
	public static List<Function> functions = new ArrayList<Function>(); //list of all functions (minimize this in the end)
	public static List<Testing_Pair> tps = new ArrayList<Testing_Pair>();
	
	public static class Function implements Comparable {
		public String cur_state;
		public String symbol;
		public String next_state;
		
		public Function(String cur, String sym, String next){
			cur_state = cur;
			symbol = sym;
			next_state = next;
		}
		
		public int compareTo(Object o){
			return this.cur_state.compareTo(((Function) o).cur_state);
		}
	}
	
	public static class Testing_Pair {
		public String s1;
		public String s2;
		
		public Testing_Pair(String S1, String S2){
			s1 = S1;
			s2 = S2;
		}
		
		public boolean equals(Object o){
			if(!(o instanceof Testing_Pair))
				return false;
			Testing_Pair tp = (Testing_Pair) o;
			if((this.s1.equals(tp.s1) && this.s2.equals(tp.s2)) 
					|| (this.s1.equals(tp.s2) && this.s2.equals(tp.s1)))
				return true;
			return false;
		}
	}
	
	public static void remove_unobtainable(){
		List<String> obt_states = new ArrayList<String>(); //put obtainable states here
		obt_states.add(first_state);
		List<String> temp_states = new ArrayList<String>(); //put new obtainable states in each iteration here
		boolean smthing_chngd = true; //every time new obtainable state is found set to 'true'
		
		while(smthing_chngd){
			smthing_chngd = false;
			
			for(String state : obt_states){
				for(Function func : functions){
					if(state.equals(func.cur_state) 
							&& !obt_states.contains(func.next_state)
							&& !temp_states.contains(func.next_state)){
						temp_states.add(func.next_state);
						smthing_chngd = true;
					}
				}
			}
			
			obt_states.addAll(temp_states);
			temp_states.clear();
		}
		
		states = obt_states;
	}
	
	public static void minimize(){
		List<List<String>> ssg = new ArrayList<List<String>>(); //same state groups
		boolean smthing_chngd = true;
		
		while(smthing_chngd){
			smthing_chngd = false;
			
			for(String state : states){
				List<String> newg = new ArrayList<String>();
				newg.add(state);
				ssg.add(newg);
			}
			
			for(String state1 : states){
				for(String state2 : states){
					if(state1.equals(state2))
						continue;
					tps.clear();
					if(equality(state1, state2)){
						smthing_chngd = true;
						for(List<String> tmpList1 : ssg){
							if(tmpList1.contains(state1)){
								for(List<String> tmpList2 : ssg){
									if(tmpList2.contains(state2)){
										if(tmpList1 == tmpList2)
											break;
										tmpList1.addAll(tmpList2);
										tmpList2.clear();
										break;
									}
								}
								break;
							}
						}
					}
				}
			}
			
			if(smthing_chngd){
				List<String> temp_states = new ArrayList<String>();
				for(List<String> tmp : ssg){
					if(tmp.isEmpty())
						continue;
					if(tmp.contains(first_state)){
						Collections.sort(tmp);
						first_state = tmp.get(0);
					}
					Collections.sort(tmp);
					temp_states.add(tmp.get(0));
				}
				states = temp_states;
				minimize_functions(ssg);
				ssg.clear();
			}
		}
	}
	
	public static boolean equality(String s1, String s2){
		if(s1.equals(s2))
			return true;
		if(acc_states.contains(s1) && !acc_states.contains(s2))
			return false;
		if(!acc_states.contains(s1) && acc_states.contains(s2))
			return false;
		
		Testing_Pair cur = new Testing_Pair(s1, s2);
		if(tps.contains(cur))
			return true;
		tps.add(cur);
		
		for(String sym : alphabet){
			String nxtS1 = "", nxtS2 = "";
			for(Function func : functions){
				if(func.symbol.equals(sym) && func.cur_state.equals(s1)){
					nxtS1 = func.next_state;
					break;
				}
			}
			for(Function func : functions){
				if(func.symbol.equals(sym) && func.cur_state.equals(s2)){
					nxtS2 = func.next_state;
					break;
				}
			}
			if(!equality(nxtS1, nxtS2))
				return false;
		}
		return true;
	}
	
	public static void minimize_functions(List<List<String>> ssg){
		List<Function> temp_functions = new ArrayList<Function>();
		
		for(Function func : functions){
			if(states.contains(func.cur_state))
				temp_functions.add(func);
		}
		
		functions.clear();
		functions.addAll(temp_functions);
		
		if(ssg == null)
			return;
		
		for(Function func : functions){
			for(List<String> tmpList : ssg){
				if(tmpList.contains(func.next_state)){
					Collections.sort(tmpList);
					func.next_state = tmpList.get(0);
				}
			}
		}
	}
	
	public static void minimize_acc_states(){
		List<String> temp_acc_states = new ArrayList<String>();
		
		for(String state : acc_states){
			if(states.contains(state))
				temp_acc_states.add(state);
		}
		
		acc_states.clear();
		acc_states.addAll(temp_acc_states);
		Collections.sort(acc_states);
	}
	
	public static void print_end_result(){
		Collections.sort(states);
		boolean first = true;
		for(String state : states){
			if(!first)
				System.out.print(",");
			else
				first = false;
			System.out.print(state);
		}
		System.out.println();
		
		first = true;
		for(String sym : alphabet){
			if(!first)
				System.out.print(",");
			else
				first = false;
			System.out.print(sym);
		}
		System.out.println();
		
		first = true;
		for(String state : acc_states){
			if(!first)
				System.out.print(",");
			else
				first = false;
			System.out.print(state);
		}
		System.out.println();
		
		System.out.println(first_state);
		
		for(Function func : functions){
			System.out.format("%s,%s->%s\n", func.cur_state, func.symbol, func.next_state);
		}
	}
	
	
	
	public static void main(String[] args) {
		
		try{
			BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
			String[] line = reader.readLine().split(",");
			for(String cur : line)
				states.add(cur);
			
			line = reader.readLine().split(",");
			for(String cur : line)
				alphabet.add(cur);
			
			line = reader.readLine().split(",");
			for(String cur : line)
				acc_states.add(cur);
			
			first_state = reader.readLine();
			
			String cur;
			while((cur = reader.readLine()) != null){
				if(cur.equals(""))
					break;
				line = cur.split("->");
				String next_state = line[1];
				line = line[0].split(",");
				functions.add(new Function(line[0], line[1], next_state));
			}
		}
		catch(Exception exc){
			System.out.println("Exception during the reading of input");
		}
		
		remove_unobtainable();
		minimize();
		minimize_functions(null);
		minimize_acc_states();
		print_end_result();
	}
}