package hr.fer.oop.lab2.topic6.zad3;

public class HashException extends RuntimeException{
	private String report;
	/**
	 * Exception constructor.
	 * @param msg
	 */
	public HashException(String msg){
		super(msg);
		report = msg;
	}
	
	/**
	 * Overriden toString() method.
	 */
	@Override
	public String toString(){
		return report;
	}
}
