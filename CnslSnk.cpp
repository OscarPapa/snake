#include "CnslSnk.h"

Voxel::Voxel() {

}

Voxel::Voxel(GLfloat x, GLfloat y, GLfloat z, GLfloat size) :
	theX(x),
	theY(y),
	theZ(z),
	theSize(size) {

}

Voxel::~Voxel() {

}

void Voxel::Paint(void) {
	glRectf(theX, theY, theX + theSize, theY + theSize);
}

void Voxel::Muve(Direction direct) {
	switch (direct) {
	case North:
			theY += theSize;
		break;
	case West:
			theX -= theSize;
		break;
	case South:
			theY -= theSize;
		break;
	case East:
			theX += theSize;
		break;
	default:
		break;
	}
}

bool Voxel::operator==(Voxel & rsh) const {
	if (theX == rsh.theX && theY == rsh.theY && theZ == rsh.theZ && theSize == rsh.theSize)
		return true;
	else
		return false;
}

//CnslSnk----------------------------------------------
CnslSnk::CnslSnk() {
	//create Area
	GameArea = new char*[Ay];
	for (usi i = 0; i < Ay; i++)
		GameArea[i] = new char[Ax];
}

CnslSnk::~CnslSnk() {
	for (usi i = 0; i < Ay; i++)
		delete[] GameArea[i];
	GameArea = nullptr;
	food.clear();
}

void CnslSnk::Initialisation() {
}

void CnslSnk::Visualisation() {
}

void CnslSnk::GenerateFood() {
	while (food.size() < 5){
		usi x = rand() % (Ay - 2) + 2;
		usi y = rand() % (Ax - 2) + 2;
		//Point piceOfFood(x, y);
		//food.push_back(piceOfFood);
	}
}

bool CnslSnk::Crash() {
	return true;
}

//Snake----------------------------------------------

Snake::Snake() {
	SnakeDirection = East;
	Voxel tmp(0, 0, 0, 10);
	snake.push_back(tmp);
	for (usi i = 0; i < 5; i++) {
		tmp.Muve(West);
		snake.push_back(tmp);
	}
}

Snake::~Snake() {
	snake.clear();
	eaten.clear();
}

void Snake::IncreaseSnake() {	
}

void Snake::Eat() {
}

void Snake::Digestion() {
}

void Snake::Move() {
	Voxel tmp1 = *snake.begin();
	(*snake.begin()).Muve(SnakeDirection);
	for (std::list<Voxel>::iterator i = ++snake.begin(); i != snake.end(); i++){
		Voxel tmp2 = *i;
		*i = tmp1;
		tmp1 = tmp2;
 	}
}

void Snake::Paint() {
	for (std::list<Voxel>::iterator i = snake.begin(); i != snake.end(); i++)
		(*i).Paint();
}
