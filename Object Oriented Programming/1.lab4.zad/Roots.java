package hr.fer.oop.lab1.topic1.prob4;

import java.lang.Math;

public class Roots {

	/**
	 * Main method
	 * @param args
	 */
	public static void main(String[] args) {

		double Re, Im, module, argument;
		int Root;
		
		if(args.length != 3){
			System.out.format("Invalid number of arguments.\n");
			System.exit(1);
		}
		
		Re = Double.parseDouble(args[0]);
		Im = Double.parseDouble(args[1]);
		Root = Integer.parseInt(args[2]);
		
		if(Root <= 1){
			System.out.format("Invalid value for root.\n");
			System.exit(1);
		}
		
		
		module = Math.sqrt(Re * Re + Im * Im);  //Calculate module
		module = Math.pow(module, 1./Root);		//Calculate module of the result
		argument = Math.atan(Im / Re);			//Calculate argument of the complex number
		argument = argument / Root;				//Calculate argument of the 1st result
		
		for(int i = 1; i <= Root; i++){			//Calculate real and imaginary part of the result
			Re = module * Math.cos(argument);	//for each argument of the result
			Im = module * Math.sin(argument);
			
			if(Im < 0) System.out.format("%d) %.2f - %.2fi\n", i, Re, -Im);
			else System.out.format("%d) %.2f + %.2fi\n", i, Re, Im);
			
			argument += 2*Math.PI / Root;
		}
	}

}
