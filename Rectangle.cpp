/**
 * Rectangle.cpp
 * Project UID 8b3bcc444eb500121e420f7e2e359014
 *
 * EECS 183, Fall 2019
 * Project 4: CoolPics
 *
 * <Tin Long Rex Fung, Isaac Lok-Tin Li>
 * <rexfung, isaliac>
 *
 * <This file contains the class "Rectangle">
 */

#include "Rectangle.h"
#include "Line.h"
#include "Triangle.h"
#include "Graphics.h"
#include <algorithm>
using namespace std;

//default constructor
Rectangle::Rectangle() {}

//constructor for rectangle with one color
Rectangle::Rectangle(Point pt1, Point pt2, Color color) {
	start = pt1;
	end = pt2;
	colorTopLeft = color;
	colorTopRight = color;
	colorBottomLeft = color;
	colorBottomRight = color;
}

//constructor for rectangle with 4 colors
Rectangle::Rectangle(Point pt1, Point pt2, Color cTopLeft, Color cTopRight,
	Color cBottomRight, Color cBottomLeft) {
	start = pt1;
	end = pt2;
	colorTopLeft = cTopLeft;
	colorTopRight = cTopRight;
	colorBottomLeft = cBottomLeft;
	colorBottomRight = cBottomRight;
}

void Rectangle::setStart(Point pt) {
	start = pt;
}

Point Rectangle::getStart() {
	return start;
}

void Rectangle::setEnd(Point pt) {
	end = pt;
}

Point Rectangle::getEnd() {
	return end;
}

//one color for the whole rectangle
void Rectangle::setColor(Color color) {
	colorTopLeft = color;
	colorTopRight = color;
	colorBottomRight = color;
	colorBottomLeft = color;
}

void Rectangle::setColorTopLeft(Color color) {
	colorTopLeft = color;
}

Color Rectangle::getColorTopLeft() {
	return colorTopLeft;
}

void Rectangle::setColorTopRight(Color color) {
	colorTopRight = color;
}

Color Rectangle::getColorTopRight() {
	return colorTopRight;
}

void Rectangle::setColorBottomRight(Color color) {
	colorBottomRight = color;
}

Color Rectangle::getColorBottomRight() {
	return colorBottomRight;
}

void Rectangle::setColorBottomLeft(Color c) {
	colorBottomLeft = c;
}

Color Rectangle::getColorBottomLeft() {
	return colorBottomLeft;
}

void Rectangle::read(istream& ins) {
	ins >> start >> end >> colorTopLeft;
	//checks if rectangle has one color or many colors, and reads accordingly
	ins >> colorTopRight;
	if (ins.fail() == false) {
		ins >> colorBottomRight >> colorBottomLeft;
	}
	else {
		colorTopRight = colorTopLeft;
		colorBottomRight = colorTopLeft;
		colorBottomLeft = colorTopLeft;
		ins.clear();
	}
}

void Rectangle::write(ostream& outs) {
	outs << start << " " << end << " " << colorTopLeft << " "
	<< colorTopRight << " " << colorBottomRight << " " << colorBottomLeft;

}

// Your code goes above this line.
// Don't change the implementations below!

istream& operator >> (istream& ins, Rectangle& rectangle)
{
    rectangle.read(ins);
    return ins;
}

ostream& operator << (ostream& outs, Rectangle rectangle)
{
    rectangle.write(outs);
    return outs;
}

void Rectangle::draw(Graphics & drawer)
{
    // four points of rectangles
    Point topLeft = start;
    Point topRight(end.getX(), start.getY());
    Point bottomRight = end;
    Point bottomLeft(start.getX(), end.getY());

    // center point and color by averaging
    Point center((start.getX() + end.getX()) / 2,
                 (start.getY() + end.getY()) / 2);
    Color colorCenter((colorTopLeft.getRed() + colorTopRight.getRed() +
                       colorBottomRight.getRed() +
                       colorBottomLeft.getRed()) / 4,
                      (colorTopLeft.getGreen() + colorTopRight.getGreen() +
                       colorBottomRight.getGreen() +
                       colorBottomLeft.getGreen()) / 4,
                      (colorTopLeft.getBlue() + colorTopRight.getBlue() +
                       colorBottomRight.getBlue() +
                       colorBottomLeft.getBlue()) / 4);

    // four triangles to represent rectangle
    Triangle top(topLeft, colorTopLeft, topRight, colorTopRight,
                 center, colorCenter);
    Triangle bottom(bottomLeft, colorBottomLeft, bottomRight, colorBottomRight,
                    center, colorCenter);
    Triangle left(topLeft, colorTopLeft, bottomLeft, colorBottomLeft,
                  center, colorCenter);
    Triangle right(topRight, colorTopRight, bottomRight, colorBottomRight,
                   center, colorCenter);
    top.draw(drawer);
    bottom.draw(drawer);
    left.draw(drawer);
    right.draw(drawer);
}
