package hr.fer.oop.lab2.topic4.zad1;

public class SimpleHashtable {

	private TableEntry[] table;
	private int size;
	
	/**
	 * Default constructor for class SimpleHashtable
	 * sets the size of Hash to 16.
	 */
	public SimpleHashtable(){
			size = 16;
			table = new TableEntry[size];
	}
	
	/**
	 * Constructor which sets the size of hash
	 * to the equal or greater number than param size.
	 * Size is in the form of 2^n.
	 * @param size
	 */
	public SimpleHashtable(int capacity){
		int i;
		
		for(i = 1; i < capacity; i *= 2);
		size = i;
		table = new TableEntry[size];
	}
	
	/**
	 * Method creates new object TableEntry with attribute values
	 * of parameters name and value, then puts the object within the
	 * hash slots using attribute "name" as a key.
	 * 
	 * If there already exists an object with the same attribute
	 * "name", method will overwrite the old attribute "value" with the
	 * new parameter "value".
	 * @param key
	 * @param value
	 */
	public void put(Object key, Object value){
		int hash, slot;
		TableEntry cur;
		
		hash = key.hashCode();
		if(hash < 0) slot = (-hash) % size;
		else slot = hash % size;
		
		if(table[slot] == null){			//in case of empty table slot
			table[slot] = new TableEntry(key, value, null);
			return;
		}
		
		cur = table[slot];
		while(cur.next != null){
			if(hash == cur.key.hashCode()){   //if there already exists an entry within the slot
				cur.value = value;
				return;
			}
		}
		
		cur.next = new TableEntry(key, value, null);
	}
	
	/**
	 * Method returns the attribute "value" of an object with
	 * attribute "name" which is within the hashtable.
	 * @param key
	 * @return
	 */
	public Object get(Object key){
		int hash, slot;
		TableEntry cur;
		
		hash = key.hashCode();
		if(hash < 0) slot = (-hash) % size;
		else slot = hash % size;
		
		cur = table[slot];
		
		while(cur != null){
			if(hash == cur.key.hashCode()) return cur.value;
			cur = cur.next;
		}
		
		return null;
	}
	
	/**
	 * Method returns the amount of entries in the hashtable.
	 * @return
	 */
	public int size(){
		int nr_entries = 0;
		TableEntry cur;
		
		for(int i = 0; i < size; i++){
			cur = table[i];
			while(cur != null){
				nr_entries++;
				cur = cur.next;
			}
		}
		return nr_entries;
	}
	
	/**
	 * Return true if parameter "key" is inside the hashtable, otherwise returns false.
	 * @param key
	 * @return
	 */
	public boolean containsKey(Object key){
		int hash, slot;
		TableEntry cur;
		
		hash = key.hashCode();
		if(hash < 0) slot = (-hash) % size;
		else slot = hash % size;
		
		cur = table[slot];
		while(cur != null){
			if(cur.key.hashCode() == hash) return true;
			cur = cur.next;
		}
		
		return false;
	}
	
	/**
	 * Method returns "true" if parameter value is inside the hashtable, otherwise return false.
	 * @param value
	 * @return
	 */
	public boolean containsValue(Object value){
		int hash = value.hashCode();
		TableEntry cur;
		
		for(int i = 0; i < size; i++){
			cur = table[i];
			while(cur != null){
				if(hash == cur.value.hashCode()) return true;
				cur = cur.next;
			}
		}
		
		return false;
	}
	
	/**
	 * Method removes entry with attribute "key" from the hashtable.
	 * @param key
	 */
	public void removeObject(Object key){
		int hash, slot;
		TableEntry cur;
		
		hash = key.hashCode();
		if(hash < 0) slot = (-hash) % size;
		else slot = hash % size;
		
		if(table[slot].key.hashCode() == hash){
			table[slot] = table[slot].next;
			return;
		}
		
		cur = table[slot];
		
		while(cur.next != null){
			if(hash == cur.next.key.hashCode()){
				cur.next = cur.next.next;
				return;
			}
		}
	}
	
	/**
	 * Method return "true" if hashtable is empty, otherwise returns "false".
	 * @return
	 */
	public boolean isEmpty(){
		for(int i = 0; i < size; i++){
			if(table[i] != null) return false;
		}
		return true;
	}
	
	/**
	 * Override of the method toString from class Object.
	 */
	@Override
	public String toString(){
		String Info =  "Hashtable: \n";
		TableEntry cur;
		
		for(int i = 0; i < size; i++){
			Info += "Slot "+ i +". : ";
			cur = table[i];
			while(cur != null){
				Info += "("+cur.toString()+")" + "; ";
				cur = cur.next;
			}
			Info += "\n";
		}
		return Info;
	}
}