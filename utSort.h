#ifndef UTSORT_H
#define UTSORT_H
#include "include/Shapes.h"
#include "include/Media.h"
#include "include/Sort.h"

TEST (Sort, sortByIncreasingPerimeter) {
	std::list<Shape *> test;
	std::list<Shape *>* shapeList = & test;
	vertex a,b,c;
	a.x = 0;
	a.y = 0;
	b.x = 10;
	b.y = 10;
	c.x = 20;
	c.y = 0;
	Shape *tempCir = new Circle(0, 0, 2,"circle");
	Shape *tempRec = new Rectangle(0, 0, 4 , 6 , "rectangle");
	Shape *tempTri = new Triangle(a, b, c, "triangle");
	shapeList->push_back(tempCir);
	shapeList->push_back(tempRec);
	shapeList->push_back(tempTri);
	Sort implementSort;
	implementSort.sortByIncreasingPerimeter(shapeList);
	std::list<Shape *>::iterator itertest = test.begin();

	// std::cout <<(*(*itertest)).name <<":" <<(*(*itertest)).perimeter() <<"\n" ;
	// itertest++;
	// std::cout <<(*(*itertest)).name <<":" <<(*(*itertest)).perimeter() <<"\n" ;
	// itertest++;
	// std::cout <<(*(*itertest)).name <<":" <<(*(*itertest)).perimeter() <<"\n" ;
	ASSERT_EQ(tempCir->perimeter(), (*(*itertest)).perimeter());	
	itertest++;
	ASSERT_EQ(tempRec->perimeter(), (*(*itertest)).perimeter());
	itertest++;
	ASSERT_EQ(tempTri->perimeter(), (*(*itertest)).perimeter());
	
	// ASSERT_EQ(temp3->perimeter(),(*(--test.end()))->perimeter());
}

TEST (Sort, sortByDecreasingPerimeter) {
	std::list<Shape *> test;
	std::list<Shape *>* shapeList = & test;
	vertex a,b,c;
	a.x = 0;
	a.y = 0;
	b.x = 10;
	b.y = 10;
	c.x = 20;
	c.y = 0;
	Shape *tempCir = new Circle(0, 0, 2,"circle");
	Shape *tempRec = new Rectangle(0, 0, 4 , 6 , "rectangle");
	Shape *tempTri = new Triangle(a, b, c, "triangle");
	shapeList->push_back(tempCir);
	shapeList->push_back(tempRec);
	shapeList->push_back(tempTri);
	Sort implementSort;
	implementSort.sortByDecreasingPerimeter(shapeList);
	std::list<Shape *>::iterator itertest = test.begin();

	// std::cout <<(*(*itertest)).name <<":" <<(*(*itertest)).perimeter() <<"\n" ;
	// itertest++;
	// std::cout <<(*(*itertest)).name <<":" <<(*(*itertest)).perimeter() <<"\n" ;
	// itertest++;
	// std::cout <<(*(*itertest)).name <<":" <<(*(*itertest)).perimeter() <<"\n" ;

	ASSERT_EQ(tempTri->perimeter(), (*(*itertest)).perimeter());	
	itertest++;
	ASSERT_EQ(tempRec->perimeter(), (*(*itertest)).perimeter());
	itertest++;
	ASSERT_EQ(tempCir->perimeter(), (*(*itertest)).perimeter());
}

TEST (Sort, sortByIncreasingArea) {
	std::list<Shape *> test;
	std::list<Shape *>* shapeList = & test;
	vertex a,b,c;
	a.x = 0;
	a.y = 0;
	b.x = 10;
	b.y = 10;
	c.x = 20;
	c.y = 0;
	Shape *tempCir = new Circle(0, 0, 2,"circle");
	Shape *tempRec = new Rectangle(0, 0, 4 , 6 , "rectangle");
	Shape *tempTri = new Triangle(a, b, c, "triangle");
	shapeList->push_back(tempCir);
	shapeList->push_back(tempRec);
	shapeList->push_back(tempTri);
	Sort implementSort;
	implementSort.sortByIncreasingArea(shapeList);
	std::list<Shape *>::iterator itertest = test.begin();
	
	// std::cout << (*(*itertest)).name << ":" << (*(*itertest)).area() << "\n" ;
	// itertest ++;
	// std::cout << (*(*itertest)).name << ":" << (*(*itertest)).area() << "\n" ;
	// itertest++;
	// std::cout << (*(*itertest)).name << ":" << (*(*itertest)).area() << "\n" ;
	ASSERT_EQ(tempCir, (*itertest));	
	ASSERT_EQ(tempCir->area(), (*(*itertest)).area());
	itertest++;
	ASSERT_EQ(tempRec->area(), (*(*itertest)).area());
	itertest++;	
	ASSERT_EQ(tempTri->area(), (*(*itertest)).area()); 

}

TEST (Sort, sortByDecreasingArea) {
	std::list<Shape *> test;
	std::list<Shape *>* shapeList = & test;
	vertex a,b,c;
	a.x = 0;
	a.y = 0;
	b.x = 10;
	b.y = 10;
	c.x = 20;
	c.y = 0;
	Shape *tempCir = new Circle(0, 0, 2,"circle");
	Shape *tempRec = new Rectangle(0, 0, 4 , 6 , "rectangle");
	Shape *tempTri = new Triangle(a, b, c, "triangle");
	shapeList->push_back(tempCir);
	shapeList->push_back(tempRec);
	shapeList->push_back(tempTri);
	Sort implementSort;
	implementSort.sortByDecreasingArea(shapeList);
	std::list<Shape *>::iterator itertest = test.begin();
	ASSERT_EQ(tempTri->area(),(*(*itertest)).area());
	itertest++;
	ASSERT_EQ(tempRec->area(),(*(*itertest)).area());
	itertest++;
	ASSERT_EQ(tempCir->area(),(*(*itertest)).area());
	itertest++;

}

TEST (Sort, sortByIncreasingCompactness) {
	std::list<Shape *> test;
	std::list<Shape *>* shapeList = & test;
	vertex a,b,c;
	a.x = 0;
	a.y = 0;
	b.x = 10;
	b.y = 10;
	c.x = 20;
	c.y = 0;
	Shape *tempCir = new Circle(0, 0, 2,"circle");
	Shape *tempRec = new Rectangle(0, 0, 4 , 6 , "rectangle");
	Shape *tempTri = new Triangle(a, b, c, "triangle");
	shapeList->push_back(tempCir);
	shapeList->push_back(tempRec);
	shapeList->push_back(tempTri);
	Sort implementSort ;
	implementSort.sortByIncreasingCompactness(shapeList);
	std::list<Shape *>::iterator itertest = test.begin();

	// std::cout <<(*(*itertest)).name <<":" << ((*(*itertest)).perimeter() / (*(*itertest)).area()) <<"\n" ;
	// itertest++;
	// std::cout <<(*(*itertest)).name <<":" <<((*(*itertest)).perimeter() / (*(*itertest)).area()) <<"\n" ;
	// itertest++;
	// std::cout <<(*(*itertest)).name <<":" <<((*(*itertest)).perimeter() / (*(*itertest)).area())  <<"\n" ;


	ASSERT_EQ(tempTri->perimeter() / tempTri ->area(),(*(*itertest)).perimeter() /(*(*itertest)).area()  );
	itertest++;	
	ASSERT_EQ(tempRec->perimeter() / tempRec ->area() ,(*(*itertest)).perimeter() /(*(*itertest)).area() );
	itertest++;	
	ASSERT_EQ(tempCir->perimeter() / tempCir ->area(),(*(*itertest)).perimeter() /(*(*itertest)).area() );
	itertest++;

}

#endif
