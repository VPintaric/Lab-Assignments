package hr.fer.oop.lab2.topic7.zad4;
import java.util.Random;

public class RandomShapeFactory implements DrawableShapeCreator{
	private int width;
	private int height;
	public final String[] legitTypes = {"rectangle", "line", "circle", "unlegit"};
	
	/**
	 * Constructor for the concrete factory.
	 * @param w
	 * @param h
	 */
	public RandomShapeFactory(int w, int h){
		width = w;
		height = h;
	}
	
	/**
	 * Returns an array of type DrawableShape of random subtypes.
	 * Number of elements if defined with parameter "num".
	 * @param num
	 */
	public DrawableShape[] create(int num){
		
		if(num <= 0) throw new ShapeException("Size of shapes array cannot be 0 or negative\n");
		
		Random rng = new Random();
		DrawableShape[] shapes = new DrawableShape[num];
		
		for(int i = 0; i < num; i++){
			shapes[i] = create(legitTypes[rng.nextInt(3)]);
		}
		return shapes;
	}
	
	/**
	 * Return an object type DrawableShape of subtype specified with
	 * param "typeOfShape". Legitimate parameter: "rectangle", "circle" and "line".
	 * @param typeOfShape
	 */
	public DrawableShape create(String typeOfShape){
		Random rng = new Random();
		
		switch(typeOfShape){
		case "rectangle":
				Rectangle obj1 = new Rectangle(rng.nextInt(width/2) + 1, rng.nextInt(height/2) + 1, rng.nextInt(10), rng.nextInt(10));
				return obj1;
		case "circle":
				Circle obj2 = new Circle(rng.nextInt(width/2) + width/2, rng.nextInt(height/2) + height/2, rng.nextInt(10));
				return obj2;
		case "line":
				Line obj3 = new Line(rng.nextInt(width) + 1, rng.nextInt(height) + 1, rng.nextInt(width) + 1, rng.nextInt(height) + 1);
				return obj3;
		default:
			throw new ShapeException("Wrong typeOfShape parameter sent to create(...) method\n");
		}
	}
}
