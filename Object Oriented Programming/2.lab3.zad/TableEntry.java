package hr.fer.oop.lab2.topic6.zad3;

public class TableEntry {
	
	Object key;
	Object value;
	TableEntry next;
	
	/**
	 * Constructor which sets the name, value and
	 * the pointer on next entry.
	 * @param key
	 * @param value
	 * @param next
	 */
	public TableEntry(Object key, Object value, TableEntry next){
		if(key == null){
			throw new HashException("Key can't be null\n");
		}
		this.key = key;
		this.value = value;
		this.next = next;
	}
	
	/**
	 * Override of method toString from upper class Object
	 */
	@Override
	public String toString(){
		return "key: "+ key.toString() + ", value: " + value.toString();
	}
	
	/**
	 * Method returns the attribute "key" of the entry.
	 * @return
	 */
	public Object getKey(){
		return key;
	}
	
	/**
	 * Method returns the attribute "value" of the entry.
	 * @return
	 */
	public Object getValue(){
		return value;
	}
	
	/**
	 * Method sets the attribute "value" of entry to the sent parameter "value".
	 * @param value
	 */
	public void setValue(Object value){
		this.value = value;
	}
}
