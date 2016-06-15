package hr.fer.oop.lab2.topic7.zad4;

import hr.fer.oop.lab1.topic2.pic.Picture;

public class Line implements DrawableShape{
		private int x1;
		private int y1;
		private int x2;
		private int y2;
		
		public Line(){};
		
		/**
		 * Constructor for line through 2 points
		 * @param x1 Coordinate x for starting point
		 * @param y1 Coordinate y for starting point
		 * @param x2 Coordinate x for ending point
		 * @param y2 Coordinate y for ending point
		 */
		public Line(int x1, int y1, int x2, int y2){
			if((x1 > Demonstration.WIDTH) || (x1 < 0)
					|| (x2 < 0) || (x2 > Demonstration.WIDTH)
					|| (y1 < 0) || (y1 > Demonstration.HEIGHT)
					|| (y2 < 0) || (y2 > Demonstration.HEIGHT))
				throw new ShapeException("Line out of bounds\n");
			
			this.x1 = x1;
			this.y1 = y1;
			this.x2 = x2;
			this.y2 = y2;
			}
		
		/**
		 * Constructor for line
		 * @param refLine Referenced Line
		 */
		public Line(Line refLine){
			this.x1 = refLine.x1;
			this.y1 = refLine.y1;
			this.x2 = refLine.x2;
			this.y2 = refLine.y2;
			}
		
		/**
		 * Resets the attributes of a line
		 * @param start Starting point
		 * @param end Ending point
		 */
		public void setLine(Point start, Point end){
			x1 = start.x;
			y1 = start.y;
			x2 = end.x;
			y2 = end.y;
		}
		
		/**
		 * Draws the line on Picture pic
		 * @param pic
		 */
		public void drawOnPicture(Picture pic){
			if(x2 < x1){               //ako je x2 "lijevo" od x1 zamijeni pocetnu i krajnju tocku
				int temp = x2;
				x2 = x1;
				x1 = temp;
				temp = y2;
				y2 = y1;
				y1 = temp;
			}
			
			int dx = x2 - x1;
			int dy = y2 - y1;
			
			if(dx == 0){         //ako je dx = 0 linija je vertikalna
				int increment;
				
				if (dy == 0) {    //ako je i dx i dy = 0 linija je zapravo samo jedna tocka
					pic.turnPixelOn(x1, y1);
					return;
				}
				
				if(dy < 0) increment = -1;   //provjera je li krajnja tocka ispod ili iznad pocetne
				else increment = 1;
				
				for(int i = x1, j = y1; j != y2; j += increment) 
					pic.turnPixelOn(i, j);
				
				return;
			}
			
			float k = ((float) dy)/dx;  	//ako linija nije vertikalna onda racunaj nagib
			float check_y = 0;    			//varijabla za provjeru koliko y koordinata "skace"
			
			for(int i = x1, j = y1; i <= x2; i++){
				pic.turnPixelOn(i, j);
				check_y += k; 				//kada "skok" prijede +-0.5 pixela potrebno je promijeniti gdje
				while(check_y > 0.5f){ 		//crtamo na y-osi
					j++;					//ako je skok velik moramo crtati vise piksela na istoj x koordinati
					check_y -= 1.f;			//da na slici nemamo prekida linije
					pic.turnPixelOn(i, j);
				}
				while(check_y < -0.5f){
					j--;
					check_y += 1.f;
					pic.turnPixelOn(i, j);
					}
				}
		
			}
}
