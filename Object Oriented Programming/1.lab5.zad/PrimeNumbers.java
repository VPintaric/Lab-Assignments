package hr.fer.oop.lab1.topic1.prob5;

public class PrimeNumbers {

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
		int n, number = 2, i = 0;
		
		if(args.length != 1){
			System.out.format("Invalid number of arguments.\n");
			System.exit(1);
		}

		n = Integer.parseInt(args[0]);
		
		System.out.format("You requested calculation of %d prime numbers. Here they are: \n", n);
		while(i < n){
			if(isPrime(number)){
				i++;
				System.out.format("%d. %d\n",i , number);
			}
			number++;
		}
	}

}
