/*
    Copyright 2010 Etay Meiri
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    Tutorial 03 - First triangle
*/

#include <stdio.h>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include "include.h"

GLuint VBO; //переменная для хранения указателя на буфер вершин

static void RenderSceneCB()
{
	glClear(GL_COLOR_BUFFER_BIT); //очищаем буфер кадра

	glEnableVertexAttribArray(0); //индексируем атрибут вершины
	glBindBuffer(GL_ARRAY_BUFFER, VBO); //обратно привязываем буфер, приготавливая его для отрисовки
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); //говорим конвейеру как воспринимать данные внутри буфера

	glDrawArrays(GL_TRIANGLES, 0, 3); //вызываем функцию для отрисовки

	glDisableVertexAttribArray(0); //отключаем атрибут вершины

	glutSwapBuffers(); //меняем фоновый буфер и буфер кадра местами
}

static void InitializeGlutCallbacks()
{
	glutDisplayFunc(RenderSceneCB);
}

static void CreateVertexBuffer()
{
	Vector3f Vertices[3];
	Vertices[0] = Vector3f(-1.01f, -1.01f, 0.0f);
	Vertices[1] = Vector3f(1.0f, -1.01f, 0.0f);
	Vertices[2] = Vector3f(0.0f, 1.0f, 0.0f);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv); //инициализируем GLUT
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // настраиваем некоторые опции GLUT

	/*Задаём параметры окна*/
	glutInitWindowSize(1024, 768);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Tutorial 03");

	InitializeGlutCallbacks(); //присоединяем функцию RenderSceneCB к GLUT

	/*Инициализируем GLEW и проверяем на ошибки*/
	GLenum res = glewInit();
	if (res != GLEW_OK)
	{
		fprintf(stderr, "Error: '%s'\n", glewGetErrorString(res));
		return 1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //устанавливаем цвет, который будет использован во время очистки буфера кадра

	CreateVertexBuffer();

	glutMainLoop(); //передаём контроль GLUT'у

	return 0;
}