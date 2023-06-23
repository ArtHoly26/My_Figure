#define _USE_MATH_DEFINES
#include <Windows.h>
#include <iostream>

using namespace std;

namespace Geometry
{
	enum Color
	{
		red = 0x000000FF,
		green = 0x0000FF00,
		blue = 0x00FF0000,
		yellow = 0x0000FFFF,
		grey = 0x00AAAAAA,
		white = 0x00FFFFFF,
	};

	enum Limits
	{
		MIN_START_X = 100,
		MAX_START_X = 1000,
		MIN_START_Y = 100,
		MAX_START_Y = 800,
		MIN_LINE_WIDTH = 1,
		MAX_LINE_WIDTH = 30,

		MIN_LENGTH = 20,
		MAX_LENGTH = 800

	};

#define SHAPE_TAKE_PARAMETRS Color color , int start_x, int start_y, int line_width = 5
#define SHAPE_GIVE_PATAMETRS color, start_x, start_y, line_width

	class Shape
	{
	protected:
		Color color;
		int start_x;
		int start_y;
		int line_width;

	public:
		Shape(SHAPE_TAKE_PARAMETRS)
		{
			set_color(color);
			set_start_x(start_x);
			set_start_y(start_y);
			set_line_width(line_width);
		}
		Color get_color()const
		{
			return color;
		}
		int get_start_x()const
		{
			return start_x;
		}
		int get_start_y()const
		{
			return start_y;
		}
		int get_line_width()const
		{
			return line_width;
		}
		void set_color(Color color)
		{
			this->color = color;
		}
		void set_start_x(int start_x)
		{
			if (start_x < Limits::MIN_START_X) start_x = Limits::MIN_START_X;
			if (start_x > Limits::MAX_START_X) start_x = Limits::MAX_START_X;
			this->start_x = start_x;
		}
		void set_start_y(int start_y)
		{
			if (start_y < Limits::MIN_START_Y) start_y = Limits::MIN_START_Y;
			if (start_y > Limits::MAX_START_Y) start_y = Limits::MAX_START_Y;
			this->start_y = start_y;
		}
		void set_line_width(int line_width)
		{
			if (line_width < Limits::MIN_LINE_WIDTH)line_width = Limits::MIN_LINE_WIDTH;
			if (line_width > Limits::MAX_LINE_WIDTH)line_width = Limits::MAX_LINE_WIDTH;
			this->line_width = line_width;
		}
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

	class Rectangle : public Shape
	{
		double width;
		double length;
	public:
		Rectangle(double width, double length, SHAPE_TAKE_PARAMETRS) :Shape(SHAPE_GIVE_PATAMETRS)
		{
			set_width(width);
			set_length(length);
		}
		void set_width(double width)
		{
			if (width < MIN_LENGTH)width = MIN_LENGTH;
			if (width > MAX_LENGTH) width = MAX_LENGTH;
			this->width = width;
		}
		void set_length(double length)
		{
			if (length < MIN_LENGTH)length = MIN_LENGTH;
			if (length > MAX_LENGTH)length = MAX_LENGTH;
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
			HPEN hPen = CreatePen(PS_SOLID, 5, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);
			::Rectangle(hdc, start_x, start_y, start_x + width, start_y + length);
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

	class Square : public Rectangle
	{
		double side;
	public:
		Square(double side, SHAPE_TAKE_PARAMETRS) :Rectangle(side, side, SHAPE_GIVE_PATAMETRS) {}
	};

	class Circle : public Shape
	{
		double radius;
	public:
		Circle(double radius, SHAPE_TAKE_PARAMETRS) :Shape(SHAPE_GIVE_PATAMETRS)
		{
			set_radius(radius);
		}
		void set_radius(double radius)
		{
			if (radius < Limits::MIN_LENGTH) radius = Limits::MIN_LENGTH;
			if (radius > Limits::MAX_LENGTH) radius = Limits::MAX_LENGTH;
			this->radius = radius;
		}
		double get_radius()const
		{
			return radius;
		}
		double get_area()const
		{
			return M_PI * radius * radius;
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
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);

			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			::Ellipse(hdc, start_x, start_y, start_x + get_diametr(), start_y + get_diametr());

			DeleteObject(hPen);
			DeleteObject(hBrush);

			ReleaseDC(hwnd, hdc);

		}

		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Радиус: " << get_radius() << endl;
			Shape::info();
		}
	};

	class Triangle : public Shape
	{
	public:
		Triangle(SHAPE_TAKE_PARAMETRS) : Shape(SHAPE_GIVE_PATAMETRS) {};
		virtual double get_height()const = 0;
		void info()const
		{
			cout << "Высота треугнольника: " << get_height() << endl;
			Shape::info();
		}
	};

	class EquillateralTriangle :public Triangle
	{
		double side;
	public:
		EquillateralTriangle(double side, SHAPE_TAKE_PARAMETRS) :Triangle(SHAPE_GIVE_PATAMETRS)
		{
			set_side(side);
		}
		void set_side(double side)
		{
			if (side < Limits::MIN_LENGTH)side = Limits::MIN_LENGTH;
			if (side > Limits::MAX_LENGTH)side = Limits::MAX_LENGTH;
			this->side = side;
		}
		double get_side()const
		{
			return side;
		}
		double get_height()const
		{
			return sqrt(pow(side, 2) - pow(side / 2, 2));
		}
		double get_area()const
		{
			return (side / 2 * get_height());
		}
		double get_perimeter()const
		{
			return side * 3;
		}
		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);

			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vertex[] =
			{
				{start_x,start_y + side},
				{start_x + side,start_y + side},
				{start_x + side / 2,start_y + side - get_height()}
			};

			::Polygon(hdc, vertex, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}
		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Длинна сторны: " << get_side() << endl;
			Triangle::info();
		}
	};

	class IsoscalesTriangle : public Triangle
	{
		double base;
		double side;
	public:
		IsoscalesTriangle(double base, double side, SHAPE_TAKE_PARAMETRS) :Triangle(SHAPE_GIVE_PATAMETRS)
		{
			set_base(base);
			set_side(side);
		}
		void set_base(double base)
		{
			if (base < Limits::MIN_LENGTH) base = Limits::MIN_LENGTH;
			if (base > Limits::MAX_LENGTH) base = Limits::MAX_LENGTH;
			this->base = base;
		}
		void set_side(double side)
		{
			if (side < Limits::MIN_LENGTH) side = Limits::MIN_LENGTH;
			if (side > Limits::MAX_LENGTH) side = Limits::MAX_LENGTH;
			this->side = side;
		}

		double get_base()const
		{
			return base;
		}
		double get_side()const
		{
			return side;
		}

		double get_height()const
		{
			return sqrt(pow(side, 2) - pow(base / 2, 2));
		}

		double get_area()const
		{
			return base * get_height() / 2;
		}

		double get_perimeter()const
		{
			return base + 2 * side;
		}

		void draw()const
		{
			HWND hwnd = GetConsoleWindow();
			HDC hdc = GetDC(hwnd);
			HPEN hPen = CreatePen(PS_SOLID, line_width, color);
			HBRUSH hBrush = CreateSolidBrush(color);
			SelectObject(hdc, hPen);
			SelectObject(hdc, hBrush);

			POINT vertex[] =
			{
				{start_x,start_y + side},
				{start_x + base,start_y + side},
				{start_x + base / 2,start_y + side - get_height()}
			};

			::Polygon(hdc, vertex, 3);

			DeleteObject(hBrush);
			DeleteObject(hPen);

			ReleaseDC(hwnd, hdc);
		}

		void info()const
		{
			cout << typeid(*this).name() << endl;
			cout << "Основание: " << get_base() << endl;
			cout << "Сторона: " << get_side() << endl;
			Triangle::info();
		}
	};
}

void main()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleDisplayMode(hConsole, CONSOLE_FULLSCREEN_MODE, NULL);

	setlocale(LC_ALL, "Rus");
	Geometry::Square sq(50, Geometry::Color::red, 300, 100, 5);
	sq.info();
	Geometry::Rectangle rect(250, 150, Geometry::Color::grey, 500, 100);
	rect.info();
	Geometry::Circle sun(150, Geometry::yellow, 800, 100);
	sun.info();
	Geometry::EquillateralTriangle eq_tri(80, Geometry::Color::green, 500, 300, 1);
	eq_tri.info();
	Geometry::IsoscalesTriangle iso_tri(250, 200, Geometry::Color::blue, 200, 270);
	iso_tri.info();
}