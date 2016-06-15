package hr.fer.oop.lab1.topic2.prob1;
import hr.fer.oop.lab1.topic2.pic.*;

public class Demonstration {

	/**
	 * Main method
	 * @param args
	 */
	public static void main(String[] args) {
		Picture pic = new Picture(100, 50);
		
		Rectangle rec1 = new Rectangle(60, 10, 5, 7);
		Rectangle rec2 = new Rectangle(40, 10, 2, 4);
		Circle cir1 = new Circle(60, 25, 5);
		Circle cir2 = new Circle(30, 10, 4);
		Line lin1 = new Line(0, 0, 20, 25);
		Line lin2 = new Line(20, 0, 20, 25);
		Point[] points = new Point[3];
		points[0] = new Point(50, 25);
		points[1] = new Point(60, 40);
		points[2] = new Point(80, 40);
		Path pat1 = new Path(points);
		
		rec1.drawOnPicture(pic);
		rec2.drawOnPicture(pic);
		cir1.drawOnPicture(pic);
		cir2.drawOnPicture(pic);
		lin1.drawOnPicture(pic);
		lin2.drawOnPicture(pic);
		pat1.drawOnPicture(pic);
		
		pic.renderImageToStream(System.out);
		PictureDisplay.showPicture(pic);
	}

}
