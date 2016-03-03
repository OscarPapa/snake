#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctype.h>
#include <iterator>
#include <list>
#include <deque>
#include <time.h>
#include <algorithm>

typedef unsigned short int usi;
enum Direction{ North, West, South, East };
enum TypeOfPoint{Fild, Wall, Food};

class Point {
public:
	Point();
	Point(usi x, usi y);
	~Point();
    
	usi GetX() const { return theX; }
	usi GetY() const { return theY; }
	void SetX(usi x) { theX = x; }
	void SetY(usi y) { theY = y; }

	bool operator==(const Point & rsh);
    
	void East();
	void West();
	void North();
	void South();
    
private:
	TypeOfPoint theType;
	usi theX, theY;
};

class Snake {
public:
	Snake();
	~Snake();
	void IncreaseSnake();
	void Eat();
	void Digestion();
	void Move();
	std::list<Point> snake;
	Direction SnakeDirection;
	std::deque<Point> eaten;
};

class CnslSnk{
public:
	CnslSnk();
	~CnslSnk();
	void Initialisation();
	void Visualisation();
	void GenerateFood();
	bool Crash();
	Snake ConsoleSnake;
	std::list<Point> food;
private: 
	char **GameArea = nullptr;
	const usi Ax = 100, Ay = 40;
};