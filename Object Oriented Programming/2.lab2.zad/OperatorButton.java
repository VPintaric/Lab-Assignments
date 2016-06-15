package hr.fer.oop.lab2.topic5.zad2;

public class OperatorButton extends Button{
	
	public static final OperatorButton PLUS = new OperatorButton("+");
	public static final OperatorButton MINUS = new OperatorButton("-");
	
	private OperatorButton(String operation){
		super(operation);
	}
}
