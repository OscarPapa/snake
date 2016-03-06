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

void Voxel::Move(Direction direct) {
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

//SnakeGame----------------------------------------------
SnakeGame::SnakeGame() {

}

SnakeGame::SnakeGame(GLfloat xSize, GLfloat ySize) {
	Ax = new GLfloat(xSize);
	Ay = new GLfloat(ySize);
}

SnakeGame::~SnakeGame() {
	delete Ax;
	Ax = nullptr;
	delete Ay;
	Ay = nullptr;
	food.clear();
}

void SnakeGame::Visualisation() {
	glColor3d(1, 0, 0);
	for (std::list<Voxel>::iterator i = food.begin(); i != food.end(); i++)
		(*i).Paint();
	theSnake.Paint();
	glutPostRedisplay();
}

void SnakeGame::GenerateFood() {
	srand((unsigned int)time(0));
	while (food.size() < 5){
		GLfloat x = (GLfloat)((-1) * ((*Ax / 10) / 2) + rand() % (int)(*Ax / 10)) * 10;
		GLfloat y = (GLfloat)((-1) * ((*Ay / 10) / 2) + rand() % (int)(*Ay / 10)) * 10;
		Voxel piceOfFood(x, y, 0, 10);
		food.push_back(piceOfFood);
	}
}

bool SnakeGame::Crash() {
	for (std::list<Voxel>::iterator i = food.begin(); i != food.end(); i++)
		if (theSnake.GetHead() == (*i)) {
			theSnake.Eat(*i);
			i = food.erase(i);
			theGameSpeed--;
			break;
		}
	if (theSnake.GetHead().GetX() < -(*Ax / 2) || theSnake.GetHead().GetX() > *Ax / 2 - 10 || theSnake.GetHead().GetY() < -(*Ay / 2) || theSnake.GetHead().GetY() > *Ay / 2 - 10)
		return true;
	else
		return theSnake.SelfDestruction();
}

void SnakeGame::Turn(Direction side) {
	if((side == North || side == South) && (theSnake.SnakeDirection == North || theSnake.SnakeDirection == South))
		return;
	else if ((side == East || side == West) && (theSnake.SnakeDirection == East || theSnake.SnakeDirection == West))
		return;
	else
		theSnake.SnakeDirection = side;
}

void SnakeGame::Play() {
	if (food.empty())
		GenerateFood();
	Visualisation();
	if (Crash()) {
		Sleep(2000);
		exit(0);
	}
	theSnake.Move();
	Sleep(theGameSpeed);
}

//Snake----------------------------------------------

Snake::Snake() {
	SnakeDirection = East;
	Voxel tmp(0, 0, 0, 10);
	snake.push_back(tmp);
	for (usi i = 0; i < 15; i++) {
		tmp.Move(West);
		snake.push_back(tmp);
	}
}

Snake::~Snake() {
	snake.clear();
	eaten.clear();
}

void Snake::IncreaseSnake() {
	if (!eaten.empty())
		if (*(--eaten.end()) == *(--snake.end())) {
			snake.push_back(*(--eaten.end()));
			eaten.pop_back();
		}
}

void Snake::Eat(Voxel food) {
	eaten.push_front(food);
}

void Snake::Move() {
	IncreaseSnake();
	Voxel tmp1 = *snake.begin();
	(*snake.begin()).Move(SnakeDirection);
	for (std::list<Voxel>::iterator i = ++snake.begin(); i != snake.end(); i++){
		Voxel tmp2 = *i;
		*i = tmp1;
		tmp1 = tmp2;
 	}
}

void Snake::Paint() {
	glColor3d(0.9, 0.9, 0.1);
	for (std::list<Voxel>::iterator i = snake.begin(); i != snake.end(); i++)
		(*i).Paint();
}

bool Snake::SelfDestruction() {
	std::list<Voxel>::iterator i = snake.begin();
	++i;
	for (i; i != snake.end(); i++)
		if (GetHead() == (*i)) {
			return true;
		}
	return false;
}
