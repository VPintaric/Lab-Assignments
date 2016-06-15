package hr.fer.oop.lab1.topic1.prob3;

/* Source za Hostadter Q niz:
 *  	 http://en.wikipedia.org/wiki/Hofstadter_sequence#Hofstadter_Q_sequence */

public class HofstadterQ {

	/**
	 * Method calculates the i. number of HofstadterQ sequence
	 * @param i
	 * @return long
	 */
	public static long Q(long i){
		
		if((i == 1) || (i == 2)) return 1;
		
		return Q(i - Q(i-1)) + Q(i - Q(i-2));
	}
	
	/**
	 * Main method
	 * @param args
	 */
	public static void main(String[] args) {
		long i, Qseries;
		
		if(args.length != 1){
			System.out.format("Invalid number of arguments.\n");
			System.exit(1);
		}
		
		i = Long.parseLong(args[0]);
		Qseries = Q(i);
		
		System.out.format("You requested calculation of %d. number of Hofstadter's sequence. ",i );
		System.out.format("The requested number is %d.", Qseries);
		
	}

}
