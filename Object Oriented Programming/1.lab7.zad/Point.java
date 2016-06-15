package hr.fer.oop.lab1.topic2.prob1;

import hr.fer.oop.lab1.topic2.pic.Picture;

public class Point {
		public int x;
		public int y;
		
		/**
		 * Constructor for Point with coordinates x and y
		 * @param x
		 * @param y
		 */
		public Point(int x, int y){
			this.x = x;
			this.y = y;
		}
		
		/**
		 * Constructor for Point with a reference to another Point
		 * @param refPoint
		 */
		public Point(Point refPoint){
			x = refPoint.x;
			y = refPoint.y;
		}
		
		/**
		 * Redefined toString method from Object.class
		 */
		public String toString(){
			return "("+x+", "+y+")";
		}
		
		/**
		 * Draws the Point on Picture pic
		 * @param pic
		 */
		public void drawOnPicture(Picture pic){
			pic.turnPixelOn(x, y);
		}
}
