#include <GL\glut.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctype.h>
#include <iterator>
#include <list>
#include <deque>
#include <time.h>
#include <algorithm>

#ifndef CNSLSNK_H
#define CNSLSNK_H

typedef unsigned short int usi;
enum Direction{ North, West, South, East };
enum TypeOfPoint{Fild, Wall, Food};

class Voxel {
public:
	Voxel();
	Voxel(GLfloat x = 0, GLfloat y= 0, GLfloat z = 0, GLfloat size = 1);
	~Voxel();

	void Paint(void);
	void Muve(Direction direction);

	bool operator==(Voxel & rsh) const;

private:
	GLfloat theX, theY, theZ, theSize;
};


class Snake {
public:
	Snake();
	~Snake();
	void IncreaseSnake();
	void Eat();
	void Digestion();
	void Move();
	void Paint();
	Direction SnakeDirection;
	std::deque<Voxel> eaten;
private:
	std::list<Voxel> snake;
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
	std::list<Voxel> food;
private: 
	char **GameArea = nullptr;
	const usi Ax = 100, Ay = 40;
};

#endif
