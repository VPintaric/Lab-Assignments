package hr.fer.oop.lab3.topic1;


public class HashtableTest {

	/**
	 * Main method
	 * @param args
	 */
	public static void main(String[] args) {
		// create collection:
		SimpleHashtable examMarks = new SimpleHashtable(2);
		
		// fill data:
		examMarks.put("Ivana", Integer.valueOf(2));
		examMarks.put("Ante", Integer.valueOf(2));
		examMarks.put("Jasna", Integer.valueOf(2));
		examMarks.put("Kristina", Integer.valueOf(5));
		examMarks.put("Ivana", Integer.valueOf(5)); // overwrites old grade for Ivana
		
		for(Object entry : examMarks) {
		SimpleHashtable.TableEntry pair = (SimpleHashtable.TableEntry) entry;
		System.out.printf("%s => %s%n", pair.getKey(), pair.getValue());
		}
	}

}
