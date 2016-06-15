package hr.fer.oop.lab2.topic5.zad2;

public class SimpleCalc implements Calculator {
	
	private Register memory, operator;
	private Display display;
	
	/**
	 * Constructor, creates 3 new objects type "Register".
	 */
	public SimpleCalc(){
		display = new Display();
		memory = new Register();
		operator = new Register();
	}
	
	/**
	 * Method returns the value of register "display".
	 */
	public String getDisplay(){
		String output;
		output = display.toString();
		
		if(output == null) return "0";
		else return output;
	}
	
	/**
	 * Method is called in case of sign "equal" being pressed before
	 * any operator is given. Method terminates the program.
	 */
	public void press(Button button){
		
		if((button.toString() == "=") && (operator.getValue() == null)){
			System.out.format("Terminating program...\n");
			System.exit(1);
		}
		
		switch(button.toString()){
			case "+": pressPlus(); break;
			case "-": pressMinus(); break;
			case "=": pressEquals(); break;
			case "C": pressClear(); break;
			default: pressDigit(Integer.valueOf( Integer.parseInt(button.toString() ))); break;
		}
	}
	
	/**
	 * Method signals the calculator that a digit was pressed.
	 * @param digit
	 */
	public void pressDigit(int digit){
		if(display.toString() == null) display.setValue(Integer.parseInt( Integer.toString( Integer.valueOf(digit) ) ) );
		
		else display.setValue( Integer.parseInt( display.toString() + Integer.toString( Integer.valueOf(digit) ) ) );
	}
	
	/**
	 * Method signals the calculator that an "equals" sign was pressed.
	 */
	public void pressEquals(){
		String operator;
		int a, b;
		
		operator = (String) this.operator.getValue();
		a = (Integer) memory.getValue();
		b = (Integer) display.getValue();
		
		if(operator == "+") display.setValue(a+b);
		else if(operator == "-") display.setValue(a-b);
		
		memory.clear();
	}
	
	/**
	 * Method signals the calculator that a "plus" sign was pressed.
	 */
	public void pressPlus(){
		if(memory.getValue() != null){
			int a = (int) memory.getValue();
			int b = (int) display.getValue();
			
			if(operator.getValue() == "+") memory.setValue(a+b);
			else memory.setValue(a-b);
		}
		
		else memory.setValue(display.getValue());
		display.clear();
		operator.setValue("+");
	}
	
	/**
	 * Method signals the calculator that a "minus" sign was pressed.
	 */
	public void pressMinus(){
		if(memory.getValue() != null){
			int a = (int) memory.getValue();
			int b = (int) display.getValue();
			
			if(operator.getValue() == "+") memory.setValue(a+b);
			else memory.setValue(a-b);
		}
		
		else memory.setValue(display.getValue());
		display.clear();
		operator.setValue("-");
	}
	
	/**
	 * Method signals the calculator that a "clear" sign was pressed.
	 */
	public void pressClear(){
		memory.clear();
		display.clear();
		operator.clear();
	}
	
	/**
	 * Overriding method for printing info about SimpleCalc object.
	 */
	@Override
	public String toString(){
		String output = "(";
		
		if(display.getValue() != null){
			output += "D="+display.toString();
			if(memory.getValue() != null) output += ", M=" + memory.toString();
			if(operator.getValue() != null) output += ", O=" + operator.toString();
		}
		
		else if(memory.getValue() != null){
			output += "M="+memory.toString();
			if(operator.getValue() != null) output += ", O=" + operator.toString();
		}
		
		else if(operator.getValue() != null) output += "O=" + operator.toString();
		
		output += ")";
		
		return output;
	}
	
	/**
	 * Overriding method for testing equality of two SimpleCalc objects.
	 * @param c
	 * @return
	 */
	@Override
	public boolean equals(Object c){
		if(!(c instanceof SimpleCalc)) return false;
		
		if(display.equals( ((SimpleCalc)c).display )
				&& memory.equals( ((SimpleCalc)c).memory )
				&& operator.equals( ((SimpleCalc)c).operator ))
			return true;
		
		return false;
	}
}
