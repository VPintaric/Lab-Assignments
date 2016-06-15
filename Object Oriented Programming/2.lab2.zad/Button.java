package hr.fer.oop.lab2.topic5.zad2;

public class Button {
	
	private String buttonName;
	
	public static final Button EQUALS = new Button( "=" );
	public static final Button CLEAR = new Button( "C" );
	
	/**
	 * Private enumerating constructor.
	 * @param name
	 */
	protected Button(String name){
		buttonName = name;
	}
	
	/**
	 * Override of toString() method.
	 */
	@Override
	public String toString(){
		return buttonName;
	}
}