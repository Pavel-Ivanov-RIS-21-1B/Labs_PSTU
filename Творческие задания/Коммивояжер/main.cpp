#include "graph.h"
#include <glut.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>



int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "rus");
	glutInit(&argc, argv);
	graph = makeGraph();
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("Граф");
	WinW = glutGet(GLUT_WINDOW_WIDTH);
	WinH = glutGet(GLUT_WINDOW_HEIGHT);
	glutDisplayFunc(display);
	glutMouseFunc(mouseClick);
	glutMainLoop();
	return 0;
}