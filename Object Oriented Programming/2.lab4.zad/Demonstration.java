package hr.fer.oop.lab2.topic7.zad4;
import hr.fer.oop.lab1.topic2.pic.*;

public class Demonstration {
	
	static final int WIDTH = 100;
	static final int HEIGHT = 100;

	/**
	 * Main method
	 * @param args
	 */
	public static void main(String[] args) {
		Picture pic = new Picture(3*WIDTH, 3*HEIGHT);
		DrawableShapeCreator factory = new RandomShapeFactory(WIDTH, HEIGHT);
		DrawableShape[] shapes = factory.create(5);
		
		for(DrawableShape s : shapes){
			s.drawOnPicture(pic);
		}
		
		pic.renderImageToStream(System.out);
		PictureDisplay.showPicture(pic);
	}

}
