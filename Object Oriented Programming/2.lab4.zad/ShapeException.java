package hr.fer.oop.lab2.topic7.zad4;

public class ShapeException extends RuntimeException{
	private String report;
	
	public ShapeException(String msg){
		super(msg);
		report = msg;
	}
}
