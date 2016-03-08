#include <GL\glut.h>
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctype.h>
#include <iterator>
#include <list>
#include <deque>
#include <ctime>
#include <algorithm>

#ifndef CNSLSNK_H
#define CNSLSNK_H

typedef unsigned short int usi;
enum Direction{ North, West, South, East };

class Voxel {
public:
	Voxel();
	Voxel(GLfloat x = 0, GLfloat y= 0, GLfloat z = 0, GLfloat size = 1);
	~Voxel();

	GLfloat GetX() const { return theX; }
	GLfloat GetY() const { return theY; }

	void Paint(void);
	void Move(Direction direction);

	bool operator==(Voxel & rsh) const;

private:
	GLfloat theX, theY, theZ, theSize;
};


class Snake {
public:
	Snake();
	~Snake();
	void IncreaseSnake();
	void Eat(Voxel food);
	void Move();
	void Paint();
	Direction SnakeDirection;
	Voxel GetHead() const { return *snake.begin(); }
	bool SelfDestruction();
private:
	std::list<Voxel> snake;
	std::deque<Voxel> eaten;
};

class SnakeGame{
public:
	SnakeGame();
	SnakeGame(GLfloat xSize, GLfloat ySize);
	~SnakeGame();
	void Visualisation();
	void GenerateFood();
	bool Crash();
	void Turn(Direction side);
	void Play();
private:
	usi theGameSpeed = 150;
	Snake theSnake;
	std::list<Voxel> food;
	GLfloat *Ax = nullptr;
	GLfloat *Ay = nullptr;
};

#endif
