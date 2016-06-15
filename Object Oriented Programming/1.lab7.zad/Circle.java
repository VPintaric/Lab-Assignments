package hr.fer.oop.lab1.topic2.prob1;
import hr.fer.oop.lab1.topic2.pic.*;

public class Circle {
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
