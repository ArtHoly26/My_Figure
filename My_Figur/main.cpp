#include <Windows.h>
#include <iostream>
#include <conio.h>

#define M_PI 3.14159265358979323846
using namespace std;

namespace Geometry
{
	class Shape
	{
	public:
		virtual double get_area() const = 0;
		virtual double get_perimeter()const = 0;
		virtual void draw()const = 0;
		virtual void info()const
		{
			cout << "Площадь фигуры: " << get_area() << endl;
			cout << "Периметр фигуры: " << get_perimeter() << endl;
			draw();
		}
	};

	class Square : public Shape
	{
		double side;
	public:
		Square(double side)
		{
			this->side = side;
		}
		double get_side()const
		{
			return side;
		}
		double get_diagonal()const
		{
			return side * sqrt(2);
		}
		double get_area()const
		{
			return side * side;
		}
		double get_perimeter()const
		{
			return side * 4;
		}
		void draw()const
		{
			for (int i = 0; i < side; i++)
			{
				for (int i = 0; i < side; i++)
				{
					cout << "* ";
				}
				cout << endl;
			}
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Длинна стороны: " << get_side() << endl;
			cout << "Диагональ: " << get_diagonal() << endl;
			Shape::info();
		}
	};

	class Rectangle : public Shape
	{
		double width;
		double length;
	public:
		Rectangle(double width, double length)
		{
			this->width = width;
			this->length = length;
		}
		double get_width()const
		{
			return width;
		}
		double get_length()const
		{
			return length;
		}
		double get_area()const
		{
			return width * length;
		}
		double get_perimeter()const
		{
			return (width + length) * 2;
		}
		double get_diagonal()const
		{
			return sqrt(pow(width, 2) + pow(length, 2));
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, 5, RGB(255, 0, 0));
			HBRUSH hBrush = CreateSolidBrush(RGB(255, 0, 0));
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Rectangle(hdc,100, 100, 300, 200);
			DeleteObject(hPen);
			DeleteObject(hBrush);
			ReleaseDC(hwnd, hdc);
			
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Ширина: " << get_width() << endl;
			cout << "Длинна: " << get_length() << endl;
			cout << "Диагональ: " << get_diagonal() << endl;
			Shape::info();
		}
	};

	class Circle : public Shape
	{
		double radius;
	public:
		Circle(double radius)
		{
			this->radius = radius;
		}
		double get_radius()const
		{
			return radius;
		}
		double get_area()const
		{
			return M_PI * pow(radius, 2);
		}
		double get_perimeter()const
		{
			return 2 * M_PI * radius;
		}
		double get_diametr()const
		{
			return 2 * radius;
		}
		void draw()const
		{
			
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус: " << get_radius() << endl;
			cout << "Диаметр: " << get_diametr() << endl;
			Shape::info();
		}
	};

	class Triangle : public Shape
	{
		double side;

	public:
		Triangle(double side)
		{
			this->side = side;
		}
		double get_side()const
		{
			return side;
		}
		double get_area()const
		{
			return (pow(side, 2) * sqrt(3)) / 4;
		}
		double get_perimeter()const
		{
			return side * 3;
		}
		double get_height()const
		{
			return (side * sqrt(3)) / 2;
		}
		void draw()const
		{
			
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Сторона треугольника: " << get_side() << endl;
			cout << "Высота треугольника: " << get_height() << endl;
			Shape::info();
		}
	};
}

void main()
{
	setlocale(LC_ALL, "Rus");
	Geometry::Square sq(5);
	Geometry::Rectangle rect(10, 5);
	Geometry::Circle cr(6);
	Geometry::Triangle tr(5);
	sq.info();
	cout << endl;
	cr.info();
	cout << endl;
	tr.info();
	cout << endl;
	rect.info();
}