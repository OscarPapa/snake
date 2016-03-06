#include "CnslSnk.h"

//TODO fullscreen
//int const sX = GetSystemMetrics(SM_CXSCREEN)2;
//int const sY = GetSystemMetrics(SM_CYSCREEN);

int const sX = 800, const sY = 600;
int const pX = 10, const pY = 10;
static Direction dir = East;
static Snake tstsnake;

void Init(void) {
	glClearColor(0.3, 0.3, 0.3, 0.0);
	glShadeModel(GL_FLAT);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	tstsnake.Paint();
	glPopMatrix();
	glutSwapBuffers();
}

void Move(void) {
	tstsnake.Move();
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
		tstsnake.SnakeDirection = North;
		Move();
		break;
	case GLUT_KEY_LEFT:
		tstsnake.SnakeDirection = West;
		Move();
		break;
	case GLUT_KEY_DOWN:
		tstsnake.SnakeDirection = South;
		Move();
		break;
	case GLUT_KEY_RIGHT:
		tstsnake.SnakeDirection = East;
		Move();
		break;
	default:
		glutIdleFunc(NULL);
		break;
	}
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(pX, pY);
	glutInitWindowSize(sX, sY);
	glutCreateWindow(argv[0]);
	Init();
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(SpecKeys);
	glutMainLoop();
	return 0;
}
