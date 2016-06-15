package hr.fer.oop.lab2.topic5.zad2;

public class Register {
	Object value;
	
	/**
	 * Constructor, sets value to "null".
	 */
	public Register(){
		value = null;
	}
	
	/**
	 * Returns the stored "value".
	 * @return
	 */
	public final Object getValue(){
		return value;
	}
	
	/**
	 * Sets "value" to parameter "o".
	 * @param o
	 */
	public void setValue(Object o){
		value = o;
	}
	
	/**
	 * Resets the attribute "value" to "null".
	 */
	public final void clear(){
		value = null;
	}
	
	public String toString(){
		if(value == null) return null;
		return value.toString();
	}
	
	public boolean equals(Object r){
		if(!(r instanceof Register)) return false;
		
		if( ((Register)r).value == value) return true;
		
		return false;
	}
}
