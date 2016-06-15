package hr.fer.oop.lab2.topic7.zad4;
import hr.fer.oop.lab1.topic2.pic.*;

public class Circle implements DrawableShape{
		private int x;
		private int y;
		private int r;
		
		/**
		 * Constructor for Circle
		 * @param x Coordinate x
		 * @param y Coordinate y
		 * @param r Radius
		 */
		public Circle(int x, int y, int r){
			if((x < 0) || (x > Demonstration.WIDTH))
				throw new ShapeException("x-coordinate of Circle is invalid\n");
			
			if((y < 0) || (y > Demonstration.HEIGHT))
				throw new ShapeException("y-coordinate of Circle is invalid\n");
			
			if(r <= 0)
				throw new ShapeException("Radius of Circle cannot be 0 or negative\n");
			
			if(( r+x > Demonstration.WIDTH) || (r+y > Demonstration.HEIGHT)
					|| (x-r < 0) || (y-r < 0))
				throw new ShapeException("Circle out of bounds\n");
			
			this.x = x;
			this.y = y;
			this.r = r;
		}
		
		/**
		 * Constructor for Circle
		 * @param refCircle Referenced Circle
		 */
		public Circle(Circle refCircle){
			this.x = refCircle.x;
			this.y = refCircle.y;
			this.r = refCircle.r;
		}
		
		/**
		 * Draws object type Circle on Picture pic
		 * @param pic
		 */
		public void drawOnPicture(Picture pic){
			for(int i = x - r; i <= x + r; i++){
				for(int j = y - r; j <= y + r; j++){
					if(((i - x)*(i - x) + (j - y)*(j - y)) <= (r * r)){
						pic.turnPixelOn(i,j);
					}
				}
			}
		}
}
