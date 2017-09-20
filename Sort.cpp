#include "include/Sort.h"

void Sort::sortByIncreasingPerimeter(std::list<Shape *> * shapeList){
    shapeList->sort( [] (Shape* firShapePerimeter , Shape* secShapePerimeter) { return  (firShapePerimeter->perimeter()) < (secShapePerimeter->perimeter()) ;});
}
void Sort::sortByDecreasingPerimeter(std::list<Shape *> * shapeList){
    shapeList->sort( [] (Shape* firShapePerimeter , Shape* secShapePerimeter) {return (firShapePerimeter->perimeter()) > (secShapePerimeter->perimeter()) ;});
}

void Sort::sortByIncreasingArea(std::list<Shape *> * shapeList){
    shapeList->sort([] (Shape* firShapeArea, Shape* secShapeArea) { return firShapeArea->area() < secShapeArea->area();});
}

void Sort::sortByDecreasingArea(std::list<Shape *> * shapeList){
    shapeList->sort([] (Shape* firShapeArea, Shape* secShapeArea) { return firShapeArea->area() > secShapeArea->area();});    
}

void Sort:: sortByIncreasingCompactness(std::list<Shape *> * shapeList){
    shapeList->sort([] (Shape* firShapeCompactness , Shape* secShapeCompactness) { return (firShapeCompactness->perimeter() / firShapeCompactness->area()) < ((secShapeCompactness->perimeter() / secShapeCompactness->area())) ;});
} 


