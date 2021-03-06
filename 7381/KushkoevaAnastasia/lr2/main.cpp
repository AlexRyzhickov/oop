#include "pch.h"
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

enum  Colors{ RED, GREEN, BLUE, NOCOLOR};

class Shape 
{
public:
	Shape(double x = 0, double y = 0, double angle = 0, Colors color = Colors::NOCOLOR)
		: x(x)
		, y(y)
		, angle(angle)
		, color(color)
	{
		if (angle >= 360.0)
			this->angle = angle - int(angle / 360) * 360;
		else
			this->angle = angle;

		idCounter++;
		id = idCounter;
	}

	void move(double x, double y)
	{
		this->x = x;
		this->y = y;
	}

	virtual void scale(double k) = 0;

	void rotate(double alpha)
	{
		if (alpha >= 360)
			alpha = alpha - (alpha / 360) * 360;
		if (angle + alpha < 360.0)
			angle += alpha;
		else
			angle = (angle + alpha) - 360;
	}

	void setColor(Colors color)
	{
		this->color = color;
	}

	string getColor()
	{
		switch (color) 
		{
		case Colors::RED :
			return "Red";
		case Colors::GREEN :
			return "Green";
		case Colors::BLUE :
			return "Blue";
		case Colors::NOCOLOR :
			return "No color";
		default:
			return "Unknown color";
		}
	}

	friend std::ostream & operator << (std::ostream &out, Shape &a)
	{
		out << "Id:" << a.id << endl;
		out << "Color:" << a.getColor() << endl;
		out << "Angle:" << a.angle << " degrees" << endl;
		out << "x1:" << a.x << " y1:" << a.y << endl;
		return out;
	}

protected:
	double x;
	double y;
	double angle;
	Colors color;
	long int id;

private:
	static long int idCounter;
};

long int Shape::idCounter = 0;

class Rectangle : public Shape
{
public:
	Rectangle(double height, double width, double x = 0, double y = 0, double angle = 0, Colors color = Colors::NOCOLOR)
		: Shape(x, y, angle, color)
		, height(height)
		, width(width)
	{
	}

	void scale(double coef) override
	{
		height *= coef;
		width *= coef;
	}
	friend std::ostream & operator <<(std::ostream &out, Rectangle &a)
	{
		out << "Rectangle" << endl;
		out << (Shape&) a;
		out << "x2:" << a.x << " y2:" << a.y + a.height << std::endl;
		out << "x3:" << a.x + a.width << " y3:" << a.y + a.height << std::endl;
		out << "x4:" << a.x + a.width << " y4:" << a.y << std::endl;

		return out;
	}
private:
	double height; 
	double width; 
};


class Trapezoid : public Shape
{
public:
	Trapezoid(double upper, double bottom, double offset, double height, double x = 0, double y = 0, double angle = 0, Colors color = Colors::NOCOLOR)
		: Shape(x, y, angle, color)
		, upperBase(upper)
		, bottomBase(bottom)
		, offset(offset)
		, height(height)
	{
		if (upper > bottom)
		{
			upperBase = bottom;
			bottomBase = upper;
		}
	}

	void scale(double coef) override
	{
		upperBase *= coef;
		bottomBase *= coef;
		offset *= coef;
		height *= coef;
	}

	friend std::ostream & operator <<(std::ostream &out, Trapezoid &a)
	{
		out << "Trapezoid" << endl;
		out << (Shape&)a;
		out << "x2:" << (a.x + a.offset) << " y2:" << (a.y + a.height) << std::endl;
		out << "x3:" << (a.x + a.offset + a.upperBase) << " y3:" << (a.y + a.height) << std::endl;
		out << "x4:" << (a.x + a.bottomBase) << " y4:" << a.y  << std::endl;

		return out;
	}
private:
	double upperBase;
	double bottomBase;
	double offset;
	double height;
};

class IsTrapezoid : public Shape
{
public:
	IsTrapezoid(double upper, double bottom, double height, double x = 0, double y = 0, double angle = 0, Colors color = Colors::NOCOLOR)
		: Shape(x, y, angle, color)
		, upperBase(upper)
		, bottomBase(bottom)
		, height(height)
	{
		if(upper > bottom) 
		{
			upperBase = bottom;
			bottomBase = upper;
	}
	}

	void scale(double coef) override
	{
		upperBase *= coef;
		bottomBase *= coef;
		height *= coef;
	}
	friend std::ostream & operator <<(std::ostream &out, IsTrapezoid &a)
	{
		out << "Isosceles trapezoid" << endl;
		out << (Shape&)a;
		out << "x2:" << a.x + (a.upperBase - a.bottomBase)/2 << " y2:" << a.y + a.height << std::endl;
		out << "x3:" << a.x + (a.upperBase + a.bottomBase)/2 << " y3:" << a.y + a.height << std::endl;
		out << "x4:" << a.x + a.bottomBase << " y4:" << a.y << std::endl;

		return out;
	}

private:
	double upperBase;
	double bottomBase;
	double height;
};

int main()
{
	Rectangle rect(100, 200);
	Trapezoid trap(30.0, 100.0, 20.0, 40.0);
	IsTrapezoid itrap(10.0, 20.0, 60.0);

	cout << "BEFORE:" << endl;
	cout << rect << endl;
	cout << trap << endl;
	cout << itrap << endl;

	cout << "\nAFTER: " << endl;
	rect.rotate(90.0);
	rect.scale(3.5);
	rect.setColor(Colors::RED);

	trap.rotate(10.0);
	trap.move(10, -5);
	trap.scale(0.33);
	trap.setColor(Colors::BLUE);

	itrap.rotate(-40.0);
	itrap.move(12.0, -20.0);
	itrap.setColor(Colors::GREEN);

	cout << rect << endl;
	cout << trap << endl;
	cout << itrap << endl;

	return 0;
}
