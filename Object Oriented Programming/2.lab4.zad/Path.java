package hr.fer.oop.lab2.topic7.zad4;

import hr.fer.oop.lab1.topic2.pic.Picture;

import java.util.Random;

public class Path {
		private Point[] points;
		
		/**
		 * Constructor for path with randomly chosen noOfPoints Points
		 * @param noOfPoints
		 */
		public Path(int noOfPoints){
			points = new Point[noOfPoints];
			Random r = new Random();
			for(int i = 0; i < noOfPoints; i++){
				int x = r.nextInt(Constants.MAX_X) + 1;
				int y = r.nextInt(Constants.MAX_Y) + 1;
				Point p = new Point(x ,y);
				points[i] = p;
			}
		}
		
		/**
		 * Constructor for path through array of points Point[]
		 * @param points
		 */
		public Path(Point[] points){
			this.points = new Point[points.length];
			for(int i = 0; i < points.length; i++){
				this.points[i] = new Point(points[i]);
			}
		}
		
		/**
		 * Constructor for path through a number of points
		 * @param x1
		 * @param y1
		 * @param x2
		 * @param y2
		 * @param xy
		 */
		public Path(int x1, int y1, int x2, int y2, int...xy){
			points = new Point[2 + xy.length / 2];
			points[0] = new Point(x1,y1);
			points[1] = new Point(x2,y2);
			for(int i = 0; i < xy.length / 2; i++){
				points[i+2] = new Point(xy[2*i], xy[2*i + 1]);
			}
		}
		
		/**
		 * Returns the array of points that Path goes through
		 * @return Point[]
		 */
		public Point[] getPoints() {
			return points;
		}
		
		/**
		 * Returns the length of a Path
		 * @return double
		 */
		public double length(){
			double len = 0;
			for(int i = 0; i < points.length - 1; i++){
				Point a = points[i];
				Point b = points[i+1];
				len += Math.sqrt((b.x - a.x)*(b.x - a.x) + (b.y - a.y)*(b.y - a.y));
			}
			return len;
		}
		
		/**
		 * Prints information about the Path points on stdio
		 * @param path
		 */
		public static void writePath(Path path){
			System.out.println("The path contains these points:");
			for(Point pt: path.getPoints()){
				System.out.println(pt);
			}
			System.out.format("Path length = %.2f", path.length());
		}
		
		/**
		 * Draws the Path on Picture pic
		 * @param pic
		 */
		public void drawOnPicture(Picture pic){
			Line partOfPath = new Line();
			
			for(int i = 0; i < points.length - 1; i++){
				partOfPath.setLine(points[i], points[i+1]);
				partOfPath.drawOnPicture(pic);
			}
		}
}
