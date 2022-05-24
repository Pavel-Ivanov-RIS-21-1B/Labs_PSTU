#pragma once
#include <glut.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int n;// число вершин
int WinW;//длина окна
int WinH;//высота окна
const int maxSize = 10;//максимум вершин
int amountVerts;//счетчик вершин


class Graph
{
	vector<int> vertList;
	vector<int> labelList;
	bool* visitedVerts = new bool[vertList.size()];//переменная для пройденых вершин
public:
	int adjMatrix[maxSize][maxSize] = { 0 };//матрица смежности
	Graph();
	~Graph();
	void DrawGraph();
	void InsertEdge(const int& vertex1, const int& vertex2, int weight);//ребра графа
	void Plus_Vertex(const int& vertex);
	void DeleteVertex();
	int GetVertPos(const int& vertex);//позиция вершины графа
	bool IsEmpty();//граф пуст
	bool IsFull();//граф полон
	void Print();
};


int R;

struct vertCoord
{
	int x, y;
};
vertCoord vertC[20];

Graph::Graph()//конструктор 
{
	for (int i = 0; i < maxSize; ++i)
	{
		for (int j = 0; j < maxSize; ++j)
		{
			this->adjMatrix[i][j] = 0;
		}
	}
}
Graph graph;
void preparation(int***& matrix, int& n, int**& Array_way, int*& result)//подготовка к методу ветвей и границ
{
	n = amountVerts;

	Array_way = new int* [n];

	result = new int[n];

	matrix = new int** [n];

	for (int i = 0; i <= n; i++)
	{
		Array_way[i] = new int[n];
	}

	for (int i = 0; i < n; i++)
	{
		matrix[i] = new int* [n];
		for (int j = 0; j < n; j++)
		{
			if (graph.adjMatrix[i][j] == 0) {
				matrix[i][j] = nullptr;
				continue;
			}
			matrix[i][j] = new int(graph.adjMatrix[i][j]);
		}
	}
}
void Otwet(int*** matrix, int n, int** help, int* path)//Метод ветвей и границ
{

	for (int l = 0; l < n; l++)
	{
		for (int i = 0; i < n; i++)
		{
			int min = 100000;
			for (int j = 0; j < n; j++)
				if (matrix[i][j] && min > *matrix[i][j])
					min = *matrix[i][j];
			for (int j = 0; j < n; j++)
				if (matrix[i][j])
					*matrix[i][j] -= min;
		}
		for (int j = 0; j < n; j++)
		{
			int min = 100000;
			for (int i = 0; i < n; i++)
				if (matrix[i][j] && min > *matrix[i][j])
					min = *matrix[i][j];
			for (int i = 0; i < n; i++)
				if (matrix[i][j])
					*matrix[i][j] -= min;
		}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				help[i][j] = 0;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				if (matrix[i][j] && !*matrix[i][j])
				{
					int hmin = 100000;
					int vmin = 100000;

					for (int l = 0; l < n; l++)
						if (l != i && matrix[l][j] && hmin > *matrix[l][j])
							hmin = *matrix[l][j];

					for (int l = 0; l < n; l++)
						if (l != j && matrix[i][l] && vmin > *matrix[i][l])
							vmin = *matrix[i][l];

					help[i][j] = hmin + vmin;
				}
			}

		int mcost = 0, mi = 0, mj = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (matrix[i][j] && mcost < help[i][j])
				{
					mcost = help[i][j];
					mi = i;
					mj = j;
				}
		path[mi] = mj;

		for (int i = 0; i < n; i++)
			matrix[i][mj] = nullptr;

		for (int i = 0; i < n; i++)
			matrix[mi][i] = nullptr;

		matrix[mj][mi] = nullptr;
	}
}
void Min_Way(int*** matrix, int n, int** Array_way, int* result)//поиск минимального пути
{
	preparation(matrix, n, Array_way, result);
	int s = 0;
	Otwet(matrix, n, Array_way, result);
	for (int i = 0, j = 0; i < n; i++)
	{
		j = result[i];
		cout << i + 1 << " -> " << j + 1 << '\t';
		s += graph.adjMatrix[i][j];
	}
	cout << endl;
	cout << "Минимальный путь : ";
	int temp = 0;
	for (int l = 0; l < n;)
	{
		for (int i = 0, j = 0; i < n; i++)
		{
			if (temp == 0 || i + 1 == temp)
			{
				if (temp == 0) cout << i + 1;
				j = result[i];
				temp = j + 1;
				if (temp > 0)	cout << " -> " << temp;
				l++;
			}
		}
	}
	cout << " = "  << s;
	cout << endl;
}

void Graph::Plus_Vertex(const int& vertex) //добавление вершины
{
	if (!this->IsFull()) {
		this->vertList.push_back(vertex);
	}
	else {
		cout << "Граф полон." << endl;
		return;
	}
}

void Graph::DeleteVertex()//удаление вершины
{

	this->vertList.pop_back();

}


bool Graph::IsEmpty()//граф пуст 
{
	if (this->vertList.size() != 0)
		return false;
	else
		return true;
}

bool Graph::IsFull()//граф полон
{
	return (vertList.size() == maxSize);
}

int Graph::GetVertPos(const int& vertex)//позиция вершины 
{
	for (int i = 0; i < this->vertList.size(); ++i) {
		if (this->vertList[i] == vertex)
			return i;
	}
	return -1;
}




Graph::~Graph()//деструктор 
{

}

Graph makeGraph()//создание графа
{
	Graph graph; 
	int amountEdges, sourceVertex, targetVertex, edgeWeight; 
	cout << "Кол-во вершин: "; cin >> amountVerts; cout << endl;
	cout << "Кол - во рёбер : "; cin >> amountEdges; cout << endl;
	for (int i = 1; i <= amountVerts; ++i) {
		int* vertPtr = &i;
		graph.Plus_Vertex(*vertPtr);//Функция вставки вершины
	}

	for (int i = 0; i < amountEdges; ++i)//Цикл от кол-ва рёбер
	{
		cout << "Начальная верщина: "; cin >> sourceVertex; cout << endl;
		int* sourceVertPtr = &sourceVertex;
		cout << "Конечная вершина: "; cin >> targetVertex; cout << endl;
		int* targetVertPtr = &targetVertex;

		cout << "Вес ребра: "; cin >> edgeWeight; cout << endl;
		graph.InsertEdge(*sourceVertPtr, *targetVertPtr, edgeWeight);
	}
	cout << endl;
	return graph;
}

void Graph::InsertEdge(const int& vertex1, const int& vertex2, int weight)//добавление вершины/ребра графа
{
	if (this->GetVertPos(vertex1) != (-1) && this->GetVertPos(vertex2) != (-1))//если есть 2 соединённых вершины
	{
		int vertPos1 = GetVertPos(vertex1);
		int vertPos2 = GetVertPos(vertex2);
		if (this->adjMatrix[vertPos1][vertPos2] != 0
			&& this->adjMatrix[vertPos2][vertPos1] != 0) {
			cout << "Дорога уже существует" << endl;
			return;
		}
		else {
			this->adjMatrix[vertPos1][vertPos2] = weight;
			this->adjMatrix[vertPos2][vertPos1] = weight;
		}
	}
	else {
		cout << "Нельзя вставить вершину"  << endl;
		return;
	}
}

void Graph::Print()//печать матрицы в консоли
{
	if (!this->IsEmpty()) {
		cout << "Матрица смежности: " << endl;
		for (int i = 0, vertListSize = this->vertList.size(); i < vertListSize; ++i) {
			cout << this->vertList[i] << " ";
			for (int j = 0; j < vertListSize; ++j) {
				cout << " " << this->adjMatrix[i][j] << " ";
			}
			cout << endl;
		}

	}

}

void setCoord(int i, int n)//координаты окна
{
	int R_;

	int x0 = WinW / 2;
	int y0 = WinH / 2;
	if (WinW > WinH)
	{
		R = 5 * (WinH / 13) / n;
		R_ = WinH / 2 - R - 10;
	}
	else {
		R = 5 * (WinW / 13) / n;
		R_ = WinW / 2 - R - 10;
	}
	float theta = 2.0f * 3.1415926f * float(i) / float(n);
	float y1 = R_ * cos(theta) + y0;
	float x1 = R_ * sin(theta) + x0;

	vertC[i].x = x1;
	vertC[i].y = y1;
}

void drawCircle(int x, int y, int R)//отрисовка круга
{
	glColor3f(1.0, 1.0, 1.0);
	float x1, y1;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y1 = R * cos(theta) + y;
		x1 = R * sin(theta) + x;;
		glVertex2f(x1, y1);
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	float x2, y2;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y2 = R * cos(theta) + y;
		x2 = R * sin(theta) + x;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void drawText(int nom, int x1, int y1)//отрисовка текста
{
	GLvoid* font = GLUT_BITMAP_HELVETICA_18;
	string s = to_string(nom);
	glRasterPos2i(x1 - 5, y1 - 5);
	for (int j = 0; j < s.length(); j++)
		glutBitmapCharacter(font, s[j]);
}

void drawVertex(int n)//отрисовка вершины
{
	for (int i = 0; i < n; i++) {
		drawCircle(vertC[i].x, vertC[i].y, R);
		drawText(i + 1, vertC[i].x, vertC[i].y);
	}
}

void drawLine(int text, int x0, int y0, int x1, int y1)//отрисова ребра
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(x1, y1);
	glEnd();

	drawText(text, (x0 + x1) / 2 + 10, (y0 + y1) / 2 + 10);
}


void Graph::DrawGraph()//отрисовка графа
{
	int n = vertList.size();
	for (int i = 0; i < n; i++)
	{
		setCoord(i, n);
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			int a = adjMatrix[i][j];
			if (a != 0)
			{
				drawLine(a, vertC[i].x, vertC[i].y, vertC[j].x, vertC[j].y);
			}
		}
	}
	drawVertex(n);
}
void Text_Menu(string text, int x1, int y1)//текст кнопок меню
{
	glColor3d(0, 0, 0);
	GLvoid* font = GLUT_BITMAP_HELVETICA_18;
	string s = text;
	glRasterPos2i(x1 + 5, y1 - 20);
	for (int j = 0; j < s.length(); j++)
		glutBitmapCharacter(font, s[j]);
}
void Romb(int length,int hight)//функция изображения кнопки
{
glColor3d(1, 1, 1);
glBegin(GL_QUADS);
glVertex2i(length,hight-50);
glVertex2i(length +100, hight);
glVertex2i(length +200, hight-50);
glVertex2i(length +100, hight -100);
glEnd();
}
void drawMenu()//Отрисовка меню с кнопками
{
	glColor3d(1, 0, 0);//верхний треугольник
	glBegin(GL_QUADS);
	glVertex2i(105, 780);
	glVertex2i(210, 700);
	glVertex2i(0, 700);
	glVertex2i(105, 780);
	glEnd();
	glColor3d(1, 0, 0);

	glBegin(GL_QUADS);//фон кнопок
	glVertex2i(0, 700);
	glVertex2i(210, 700);
	glVertex2i(210, 100);
	glVertex2i(0, 100);
	glEnd();

	glColor3d(1, 0, 0);//нижний треугольник
	glBegin(GL_QUADS);
	glVertex2i(0, 100);
	glVertex2i(210, 100);
	glVertex2i(105, 20);
	glVertex2i(0, 100);
	glEnd();

	Romb(5, 700);
	Text_Menu("New Vertex", 45, 660);
	Romb(5, 575);
	Text_Menu("Delete Vertex", 40, 535);
	Romb(5, 450);
	Text_Menu("Print Matrix", 50, 410);
	Romb(5, 325);
	Text_Menu("New Graf", 55, 285);
	Romb(5, 200);
	Text_Menu("Result", 70, 160);
	//текст и кнопки
}
int** Array_way;
int* result;
int*** matrix;
void mouseClick(int btn, int stat, int x, int y)//Функция для действий прик клике мыши
{
	if (stat == GLUT_DOWN) //Проверка на нажатие
	{
		if (x > 0 && x < 205 && y > 100 && y < 200)//добавление вершины
		{
			int sourceVertex;
			int targetVertex;
			int edgeWeight;


			cout << "Начальная вершина: "; cin >> sourceVertex; cout << endl;
			int* sourceVertPtr = &sourceVertex;
			cout << "Конечная вершина: "; cin >> targetVertex; cout << endl;
			int* targetVertPtr = &targetVertex;

			if (sourceVertex > amountVerts || targetVertex > amountVerts) 
			{
				amountVerts++;
				int* vertPtr = &amountVerts;
				graph.Plus_Vertex(*vertPtr);
			}

			cout << "Вес ребра: "; cin >> edgeWeight; cout << endl;
			graph.InsertEdge(*sourceVertPtr, *targetVertPtr, edgeWeight);
		}
		if (x > 0 && x < 205 && y > 225 && y < 325)//удаление вершины
		{
			int sourceVertex;

			cout << "Введите вершину: "; cin >> sourceVertex; cout << endl;
			int* sourceVertPtr = &sourceVertex;
			if (sourceVertex == amountVerts)
			{
				amountVerts--;
				graph.DeleteVertex();
			}
			else cout << "Невозможно удалить вершину \n";
		}
		if (x > 0 && x < 205 && y >  350 && y < 450)//печать матрицы смежности
		{
			graph.Print();
		}
		if (x > 0 && x < 205 && y >  475 && y < 575)//создание нового графа
		{
			graph = makeGraph();
		}
		if (x > 0 && x < 205 && y > 600 && y < 700)//Минимальный путь
		{
			Min_Way(matrix, n, Array_way, result);
		}
	}
	glutPostRedisplay();
}

void display()//настройки окна
{
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 1200, 0, 800);
	glViewport(0, 0, 1200, 800);
	glClearColor(0.28, 0.23, 0.91, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	graph.DrawGraph();
	drawMenu();
	glutSwapBuffers();
}
