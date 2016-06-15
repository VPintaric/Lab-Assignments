package hr.fer.oop.lab2.topic5.zad2;

public class DigitButton extends Button{
	
	public static final DigitButton B0 = new DigitButton(0);
	public static final DigitButton B1 = new DigitButton(1);
	public static final DigitButton B2 = new DigitButton(2);
	public static final DigitButton B3 = new DigitButton(3);
	public static final DigitButton B4 = new DigitButton(4);
	public static final DigitButton B5 = new DigitButton(5);
	public static final DigitButton B6 = new DigitButton(6);
	public static final DigitButton B7 = new DigitButton(7);
	public static final DigitButton B8 = new DigitButton(8);
	public static final DigitButton B9 = new DigitButton(9);
	
	private DigitButton(int digit){
		super(Integer.toString(digit));
	}
	
	public static void main(String[] args){
		Calculator c = new SimpleCalc();
		
		System.out.format("%s\n", c.getDisplay());
		System.out.format("%s\n\n", c.toString());
		
		c.press(DigitButton.B1);
		
		System.out.format("%s\n", c.getDisplay());
		System.out.format("%s\n\n", c.toString());
		
		c.press(DigitButton.B0);
		
		System.out.format("%s\n", c.getDisplay());
		System.out.format("%s\n\n", c.toString());
		
		c.press(OperatorButton.MINUS);
		
		System.out.format("%s\n", c.getDisplay());
		System.out.format("%s\n\n", c.toString());
		
		c.press(DigitButton.B2);
		
		System.out.format("%s\n", c.getDisplay());
		System.out.format("%s\n\n", c.toString());
		
		c.press(DigitButton.B9);
		
		System.out.format("%s\n", c.getDisplay());
		System.out.format("%s\n\n", c.toString());
		
		c.press(OperatorButton.PLUS);
		
		System.out.format("%s\n", c.getDisplay());
		System.out.format("%s\n\n", c.toString());
		
		c.press(DigitButton.B3);
		
		System.out.format("%s\n", c.getDisplay());
		System.out.format("%s\n\n", c.toString());
		
		c.press(Button.EQUALS);
		
		System.out.format("%s\n", c.getDisplay());
		System.out.format("%s\n\n", c.toString());
		
		c.press(Button.CLEAR);
		
		System.out.format("%s\n", c.getDisplay());
		System.out.format("%s\n\n", c.toString());
		
		c.press(Button.EQUALS);
	}
	
	
}
