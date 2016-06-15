package hr.fer.oop.lab2.topic5.zad2;

public class Display extends Register{
	
	/**
	 * Method overrides the higher-class method to check if
	 * the given parameter is integer.
	 */
	public void setValue(Object o){
		if(o instanceof Integer) value = o;
		else value = null;
	}
}
