package hr.fer.oop.lab1.topic1.prob6;

public class NumberDecomposition {

	/**
	 * Method returns "true" of the given number is a prime, else returns "false"
	 * @param number
	 * @return boolean
	 */
	public static boolean isPrime(int number){
		for(int j = number/2; j >= 2; j--){
			if(number % j == 0) return false;
		}
		return true;
	}
	
	/**
	 * Main method
	 * @param args
	 */
	public static void main(String[] args) {
		int number, i=1, factor = 2;
		
		if(args.length != 1){
			System.out.format("Invalid number of arguments.\n");
			System.exit(1);
		}
		
		number = Integer.parseInt(args[0]);
		
		if(number <= 1){
			System.out.format("Invalid value.\n");
			System.exit(2);
		}
		
		System.out.format("You requested decomposition of number %d onto prime factors. ", number);
		System.out.format("Here they are: \n");
		while(number != 1){
			if(isPrime(factor) && (number % factor == 0)){
				number /= factor;
				System.out.format("%d. %d\n", i, factor);
				i++;
			}
			else factor++;
		}

	}

}
