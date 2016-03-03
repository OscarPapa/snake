#include "CnslSnk.h"

Point::Point():
	theType(Fild),
	theX(0),
	theY(0){
}

Point::Point( usi x, usi y):
	theX(x),
	theY(y){
}

Point::~Point() {
}

void Point::East() {
	++theY;
}

void Point::West() {
	--theY;
}

void Point::North() {
	--theX;
}

void Point::South() {
	++theX;
}

bool Point::operator==(const Point & rsh) {
	if (theX == rsh.GetX() && theY == rsh.GetY())
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
	GameArea[0][0] = char(201);
	GameArea[Ay-1][0] = char(200);
	GameArea[0][Ax-1] = char(187);
	GameArea[Ay-1][Ax-1] = char(188);
	for (usi i = 1; i < (Ay - 1); i++){
		GameArea[i][0] = char(186);
		GameArea[i][Ax - 1] = char(186);
	}
	for (usi i = 1; i < (Ay - 1); i++)
		for (usi j = 1; j < (Ax - 1); j++)
			GameArea[i][j] = ' ';
	for (usi i = 1; i < (Ax - 1); i++){
		GameArea[0][i] = char(205);
		GameArea[Ay - 1][i] = char(205);
	}
	for (std::list<Point>::iterator i = ConsoleSnake.snake.begin(); i != ConsoleSnake.snake.end(); i++){
		GameArea[(*i).GetX()][(*i).GetY()] = char(15);
	}
	if (food.empty())
		GenerateFood();
	for (std::list<Point>::iterator i = food.begin(); i != food.end(); i++)
		GameArea[(*i).GetX()][(*i).GetY()] = char(3);
}

void CnslSnk::Visualisation() {
	system("cls");
	for (usi i = 0; i < Ay; i++) {
		for (usi j = 0; j < Ax; j++)
			std::cout << GameArea[i][j];
		std::cout << "\n";
	}
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
	std::list<Point>::iterator sneakHead = ConsoleSnake.snake.begin();

	if ((*sneakHead).GetX() == 0 || (*sneakHead).GetX() == (Ay - 1)) {
			std::cout << "GAME OVER!";
			return false;
	}
	if ((*sneakHead).GetY() == 0 || (*sneakHead).GetY() == (Ax - 1)) {
		std::cout << "GAME OVER!";
		return false;
	}

	if (ConsoleSnake.snake.size() > 5) {
		std::list<Point>::iterator i = sneakHead;
		for (usi j = 0; j < 5; j++)
			++i;
		for (i; i != ConsoleSnake.snake.end(); i++)
			if ((*sneakHead) == (*i)) {
				std::cout << "GAME OVER!";
				return false;
			}
	}

	for (std::list<Point>::iterator i = food.begin(); i != food.end(); i++) {
		if ((*sneakHead) == (*i)) {
			ConsoleSnake.eaten.push_back(*i);
			
			//TODO delete food from food list
			food.remove(*i);
			//food.erase(i);
		}
	}
	return true;
}

//Snake----------------------------------------------

Snake::Snake() {
	SnakeDirection = East;
	for (usi i = 5; i > 0; i--) {
		Point tmp(i, 5);
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
	//TODO

	//delete from deque Complexity: O(n) 
	//Point tmp;
	//auto itr = remove(eaten.begin(), eaten.end(), tmp);
	//eaten.erase(itr, eaten.end());
}

void Snake::Digestion() {
}

void Snake::Move() {
	Point tmp1 = *snake.begin();
	switch (SnakeDirection) {
	case East:
		(*snake.begin()).East();
		break;
	case South:
		(*snake.begin()).South();
		break;
	case West:
		(*snake.begin()).West();
		break;
	case North:
		(*snake.begin()).North();
		break;
	default:
		break;
	}
	for (std::list<Point>::iterator i = ++snake.begin(); i != snake.end(); i++){
		Point tmp2 = *i;
		*i = tmp1;
		tmp1 = tmp2;
 	}
}