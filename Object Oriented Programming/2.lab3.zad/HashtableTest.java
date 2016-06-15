package hr.fer.oop.lab2.topic6.zad3;
import java.util.Random;

public class HashtableTest {

	/**
	 * Main method
	 * @param args
	 */
	public static void main(String[] args) {
		SimpleHashtable table = null;
		String[] names = {"Dag", "Lovro", null, "Alen", "Luka", null, "Teo", "Martin"};
		Random rng = new Random();
		
		try{
		table = new SimpleHashtable(-2);
		}
		catch(HashException exc){
			System.out.format("%s", exc.toString());
			System.out.format("Setting SimpleHashtable capacity to the default capacity of 16...\n");
			table = new SimpleHashtable();
		}
		
		if(table.isEmpty()) System.out.format("Before putting entries: Table = empty\n");
		
		for(int i = 0; i < 8; i++){
			try{
				table.put(names[i], rng.nextInt());
			}
			catch(HashException exc){
				System.out.format("%s", exc.toString());
				System.out.format("Skipping the entry with null-key value...\n");
				continue;
			}
		}
		
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
