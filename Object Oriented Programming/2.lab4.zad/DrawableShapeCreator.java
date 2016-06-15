package hr.fer.oop.lab2.topic7.zad4;
import hr.fer.oop.lab1.topic2.pic.*;

public interface DrawableShapeCreator {
	DrawableShape[] create(int num);
	DrawableShape create(String typeOfShape);
}
