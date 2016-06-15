package hr.fer.oop.lab2.topic4.zad1;

public class HashtableTest {

	/**
	 * Main method
	 * @param args
	 */
	public static void main(String[] args) {
		SimpleHashtable table = new SimpleHashtable(3);
		
		if(table.isEmpty()) System.out.format("Before putting entries: Table = empty\n");
		table.put("Dag" , Integer.valueOf(1));
		table.put("Lovro", Integer.valueOf(5));
		table.put("Alen", Integer.valueOf(5));
		table.put("Luka", Integer.valueOf(-1));
		table.put("Teo", Integer.valueOf(32));
		table.put("Martin", Integer.valueOf(6));
		if(!table.isEmpty()) System.out.format("After putting entries: Table != empty\n");
		
		System.out.format(table.toString());
		if(table.containsKey("Lovro")) System.out.format("Contains Lovro\n");
		else System.out.format("Does not contain Lovro\n");
		
		if(table.containsValue(Integer.valueOf(5))) System.out.format("Contains value of 5\n");
		else System.out.format("Does not contain value of 5\n");
		
		System.out.format("Size before removing 1 entry: %d\n", table.size());
		table.removeObject("Lovro");
		System.out.format("Size after removing 1 entry: %d\n", table.size());
		
		if(!table.containsKey("Lovro")) System.out.format("Does not contain Lovro\n");
		if(table.containsValue(Integer.valueOf(5))) System.out.format("Does contain value of 5\n\n");
		
		System.out.format(table.toString());
	}

}
