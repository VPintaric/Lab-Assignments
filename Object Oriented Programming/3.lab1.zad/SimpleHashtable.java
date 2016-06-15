package hr.fer.oop.lab3.topic1;
import java.util.Iterator;

/**
 * Class that implements a simple hashtable and an iterator.
 * @author Vedran Pintariæ
 *
 */
public class SimpleHashtable implements Iterable {
	/**
	 * Class for every entry within the hashtable.
	 * @author Vedran Pintariæ
	 *
	 */
	public static class TableEntry {
		
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
			this.key = key;
			this.value = value;
			this.next = next;
		}
		
		/**
		 * Override of method toString from upper class Object.
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
	
	/**
	 * Conrete realisation of iterator for class SimpleHashtable.
	 * @author Vedran Pintariæ
	 *
	 */
	public class HashIterator implements Iterator {
		boolean first;
		int curRow;
		TableEntry cur;
		
		/**
		 * Constructor for concrete iterator for SimpleHashtable.s
		 */
		public HashIterator(){
			curRow = 0;
			first = true;
			
			while((table[curRow] == null) && (curRow < size))
				curRow++;
			
			if(curRow == size) cur = null;
			else cur = table[curRow];
		}
		
		
		/**
		 * Implementation of hasNext() method from iterator interface.
		 */
		@Override
		public boolean hasNext(){
			if(first) return true;
			if(cur.next != null) return true;
			
			int i = curRow + 1;
			
			while(i < size){
				if(table[i] != null) return true;
			}
			
			return false;
		}
		
		
		/**
		 * Implementation of next() method from iterator interface.
		 */
		@Override
		public TableEntry next(){
			if(first){
				first = false;
				return cur;
			}
			
			if(cur.next != null){
				cur = cur.next;
				return cur;
			}
			
			curRow++;
			while(curRow < size){
				if(table[curRow] != null){
					cur = table[curRow];
					return cur;
				}
			}
			return null; //with assumption that the existence of next iteration is checked
			//with next() method this outcome is impossible.
		}
	}


	private TableEntry[] table;
	private int size;
	
	/**
	 * Implementation of a iterator() function from Iterable interface.
	 */
	@Override
	public Iterator iterator(){
		return new HashIterator();
	}
	
	
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
			cur = cur.next;
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