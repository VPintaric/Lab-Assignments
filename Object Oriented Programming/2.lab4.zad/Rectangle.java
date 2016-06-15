package hr.fer.oop.lab2.topic7.zad4;
import hr.fer.oop.lab1.topic2.pic.*;

public class Rectangle implements DrawableShape{
		private int x;
		private int y;
		private int width;
		private int height;
		
		/**
		 * Constructor for Rectangle
		 * @param x
		 * @param y
		 * @param width
		 * @param height
		 */
		public Rectangle(int x, int y, int width, int height){
			if((x < 0) || (x > Demonstration.WIDTH))
				throw new ShapeException("X-coordinate of Rectangle is invalid\n");
			
			if((y < 0) || (y > Demonstration.HEIGHT))
				throw new ShapeException("Y-coordinate of Rectangle is invalid\n");
			
			if(width < 0)
				throw new ShapeException("Width of Rectangle cannot be 0 or negative\n");
			
			if(height < 0)
				throw new ShapeException("Height of Rectangle cannot be 0 or negative\n");
			
			if((x+width > Demonstration.WIDTH) || (y+height > Demonstration.HEIGHT))
				throw new ShapeException("Rectangle out of bounds\n");
			
			this.x = x;
			this.y = y;
			this.width = width;
			this.height = height;
		}
		
		/**
		 * Constructor for Rectangle with a reference to another Rectangle
		 * @param refRectangle
		 */
		public Rectangle(Rectangle refRectangle){
			x = refRectangle.x;
			y = refRectangle.y;
			width = refRectangle.width;
			height = refRectangle.height;
		}
		
		/**
		 * Draws Rectangle on Picture pic
		 * @param pic
		 */
		public void drawOnPicture(Picture pic){
			for(int i = this.x; i <= this.x + this.width; i++){
				for(int j = this.y; j <= this.y + this.height; j++){
					pic.turnPixelOn(i, j);
				}
			}
		}
}
