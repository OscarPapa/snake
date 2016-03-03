#include <GL\glut.h>
#include "CnslSnk.h"

int const sX = 400, const sY = 400, const pX = 10, const pY = 10;
static GLfloat sx = 0, sy = 0, sz = 0;
static Direction dir = East;

void Init(void) {
	glClearColor(0.3, 0.3, 0.3, 0.0);
	glShadeModel(GL_FLAT);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	//glTranslatef();
	glRectf(sx, sy, sx + 10, sy - 10);

	//glutSolidTeapot(20.0);
	//glutWireTeapot(50.0);
	glPopMatrix();
	glutSwapBuffers();
	//glFlush();
}

void Move(void) {
	switch (dir) {
	case North:
		if (sy < (sY / 2))
			sy += 10;
		break;
	case West:
		if (sx >((-1)*sX / 2))
			sx -= 10;
		break;
	case South:
		if (sy > ((-1)*sY / 2) + 10)
			sy -= 10;
		break;
	case East:
		if (sx < (sX / 2) - 10)
			sx += 10;
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-sX / 2, sX / 2, -sY / 2, sY / 2, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void Keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case GLUT_KEY_RIGHT:
		dir = East;
		Move();
		//glutIdleFunc(Move);
		break;
	case 'w':
		dir = North;
		Move();
		break;
	case 'a':
		dir = West;
		Move();
		break;
	case 's':
		dir = South;
		Move();
		break;
	case 'd':
		dir = East;
		Move();
		break;
	case char(27) :
		exit(0);
		break;
	default:
		glutIdleFunc(NULL);
		break;
	}
}

void SpecKeys(int key, int x, int y) {
	switch (key) {
	case GLUT_KEY_UP:
		dir = North;
		Move();
		break;
	case GLUT_KEY_LEFT:
		dir = West;
		Move();
		break;
	case GLUT_KEY_DOWN:
		dir = South;
		Move();
		break;
	case GLUT_KEY_RIGHT:
		dir = East;
		Move();
		break;
		
	default:
		glutIdleFunc(NULL);
		break;
	}
}

void Mouse(int button, int state, int x, int y) {
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN) {
			dir = West;
			glutIdleFunc(Move);
		}
		else
			glutIdleFunc(NULL);
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN) {
			dir = East;
			glutIdleFunc(Move);
		}
		else
			glutIdleFunc(NULL);
		break;
	default:
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(pX, pY);
	glutInitWindowSize(sX, sY);
	glutCreateWindow(argv[0]);
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutMouseFunc(Mouse);
	//glutMotionFunc(void (*func) (void));  func, которая вызывается, когда указатель мыши перемещается в пределах окна принажатой
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecKeys);
	//glutPostRedisplay();
	glutMainLoop();
	return 0;
}

//enum Commands { UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77, ESC = 27 };
////-----------------------------------------------------
//int main() {
//	int button = 0;
//	system("cls");
//	CnslSnk ConsoleSnak;
//	ConsoleSnak.Initialisation();
//	ConsoleSnak.Visualisation();
//	bool exekute = true;
//	while (exekute){
//		ConsoleSnak.Initialisation();
//		ConsoleSnak.Visualisation();
//		if (_kbhit()) {
//			button = _getch();
//			if (button == 224) {
//				button = _getch();
//				switch (button) {
//				case UP:
//					if (ConsoleSnak.ConsoleSnake.SnakeDirection == South)
//						break;
//					ConsoleSnak.ConsoleSnake.SnakeDirection = North;
//					std::cout << "UP\n";
//					break;
//				case DOWN:
//					if (ConsoleSnak.ConsoleSnake.SnakeDirection == North)
//						break;
//					ConsoleSnak.ConsoleSnake.SnakeDirection = South;
//					std::cout << "DOWN\n";
//					break;
//				case LEFT:
//					if (ConsoleSnak.ConsoleSnake.SnakeDirection == East)
//						break;
//					ConsoleSnak.ConsoleSnake.SnakeDirection = West;
//					std::cout << "LEFT\n";
//					break;
//				case RIGHT:
//					if (ConsoleSnak.ConsoleSnake.SnakeDirection == West)
//						break;
//					ConsoleSnak.ConsoleSnake.SnakeDirection = East;
//					std::cout << "RIGHT\n";
//					break;
//				default:
//					std::cout << "othe\n";
//					break;
//				}
//			}
//			else if (button = 27){
//				std::cout << "ESC\n";
//				break;
//			}
//		}
//		//TODO ConsoleSnak.Crash();
//		exekute = ConsoleSnak.Crash();
//		ConsoleSnak.ConsoleSnake.Move();
//		//TODO Cek_kros_sneak and food
//		Sleep(150);
//	}
//}