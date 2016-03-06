#include "CnslSnk.h"

//TODO fullscreen
//int const sX = GetSystemMetrics(SM_CXSCREEN)2;
//int const sY = GetSystemMetrics(SM_CYSCREEN);

usi const sX = 800, const sY = 600;
usi const pX = 10, const pY = 10;
static Snake tstsnake;
static SnakeGame game((GLfloat)sX, (GLfloat)sY);

void Init(void) {
	glClearColor(0.2, 0.4, 0.2, 0.0);
	glShadeModel(GL_FLAT);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glPushMatrix();
	game.Play();
	glPopMatrix();
	glutSwapBuffers();
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
		game.Turn(North);
		break;
	case GLUT_KEY_LEFT:
		game.Turn(West);
		break;
	case GLUT_KEY_DOWN:
		game.Turn(South);
		break;
	case GLUT_KEY_RIGHT:
		game.Turn(East);
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
