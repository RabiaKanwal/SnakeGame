#ifndef TETRIS_CPP_
#define TETRIS_CPP_

#include "util.h"
#include <iostream>
#include<vector>
#include<algorithm>
//#include<cstdlib>
#include<ctime>
#include<string>
#include <fstream>
//#include<sys/wait.h>
//#include<stdlib.h>
//#include<stdio.h>
//#include<unistd.h>
#include<sstream>
#include<cmath>    
using namespace std;
void PwrTimer(int);
void Timer(int);
void NonPrintableKeys(int, int, int);
void PwrDisappear(int);
void PwrTimer(int);
void PwrVanish(int);
void FoodTimer(int);
int bodycount = 2;
int key1 = 3;
int points = 0;
int mov = 1;
int pausepnt = 450;
int pwr[2] = { 800,800 };
int glowcolor = 25;
bool power = false;
bool pausegame = true;
int difficulty = 1;
int ucoor[13][2] = {};
int zcoor[13][2] = {};
bool highscoredisp = false;
bool historydisp = false;
bool newgame = false;
int highscore = 0;
string highscorestr = "";
/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
int headx = 200, heady = 200;
bool gameover = false;
bool historyadd = false;
int food[5][2] = {};
int bodypt[600][2] = { {headx,heady - 10},{headx,heady - 20} };
/*
 * Main Canvas drawing function.
 * */
string pointsstr = "0";
double startx = 320, starty = 400;
bool full = false;
bool hs = false;
void collisionDetect(int m)
{
	if (headx == 0 || headx == 650 || heady == 0 || heady == 650)
	{
		gameover = true;
	}
	for (int i = 0; i < bodycount; i++)
	{
		if (bodypt[i][0] == headx && bodypt[i][1] == heady)
		{
			gameover = true;
		}
		for (int i = 0; i < 13; i++)
		{
			if (headx == ucoor[i][0] && heady == ucoor[i][1])
			{
				gameover = true;
			}
		}
		for (int i = 0; i < 13; i++)
		{
			if (headx == zcoor[i][0] && heady == zcoor[i][1])
			{
				gameover = true;
			}
		}
	}
	for (int i = 0; i < 5; i++)
	{
		if (headx == food[i][0] && heady == food[i][1])
		{
			points = points + (difficulty * 5);
			pointsstr = to_string(points);
			food[i][0] = 0;
			food[i][1] = 0;
			if (key1 == 1)
			{
				bodypt[bodycount][0] = bodypt[bodycount - 1][0] + 10;
				bodypt[bodycount][1] = bodypt[bodycount - 1][1];
			}
			else if (key1 == 2)
			{
				bodypt[bodycount][0] = bodypt[bodycount - 1][0];
				bodypt[bodycount][1] = bodypt[bodycount - 1][1] - 10;
			}
			else if (key1 == 3)
			{
				bodypt[bodycount][0] = bodypt[bodycount - 1][0] - 10;
				bodypt[bodycount][1] = bodypt[bodycount - 1][1];
			}
			else if (key1 == 4)
			{
				bodypt[bodycount][0] = bodypt[bodycount - 1][0];
				bodypt[bodycount][1] = bodypt[bodycount - 1][1] + 10;
			}
			bodycount++;
		}
	}
	if (headx == pwr[0] && heady == pwr[1])
	{
		points = points + (difficulty * 20);
		pointsstr = to_string(points);
		pwr[0] = 800;
		pwr[1] = 800;
		power = true;
		glutTimerFunc(75000.0 / FPS, PwrDisappear, 0);
		glutTimerFunc(300000.0 / FPS, PwrTimer, 0);
		if (key1 == 1)
		{
			bodypt[bodycount][0] = bodypt[bodycount - 1][0] + 10;
			bodypt[bodycount][1] = bodypt[bodycount - 1][1];
		}
		else if (key1 == 2)
		{
			bodypt[bodycount][0] = bodypt[bodycount - 1][0];
			bodypt[bodycount][1] = bodypt[bodycount - 1][1] - 10;
		}
		else if (key1 == 3)
		{
			bodypt[bodycount][0] = bodypt[bodycount - 1][0] - 10;
			bodypt[bodycount][1] = bodypt[bodycount - 1][1];
		}
		else if (key1 == 4)
		{
			bodypt[bodycount][0] = bodypt[bodycount - 1][0];
			bodypt[bodycount][1] = bodypt[bodycount - 1][1] + 10;
		}
		bodycount++;
	}
	glutPostRedisplay();
	glutTimerFunc(0, collisionDetect, 0);
}
void PwrDisappear(int m)
{
	power = false;
}
void HurdleGen(int m)
{
	if (!pausegame && !gameover)
	{
		do
		{
			ucoor[0][0] = (rand() % 57 + 1) * 10;
			ucoor[0][1] = (rand() % 57 + 1) * 10;
		} while (headx == ucoor[0][0] && heady == ucoor[0][1]);
		for (int i = 1; i < 5; i++)
		{
			ucoor[i][0] = ucoor[i - 1][0];
			ucoor[i][1] = ucoor[i - 1][1] - 10;
		}
		for (int i = 5; i < 9; i++)
		{
			ucoor[i][1] = ucoor[i - 1][1];
			ucoor[i][0] = ucoor[i - 1][0] + 10;
		}
		for (int i = 9; i < 13; i++)
		{
			ucoor[i][0] = ucoor[i - 1][0];
			ucoor[i][1] = ucoor[i - 1][1] + 10;
		}
		for (int i = 0; i < 13; i++)
		{
			if (headx == ucoor[i][0] && heady == ucoor[i][1])
			{
				HurdleGen(0);
			}
		}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				if (food[i][0] == ucoor[j][0] && food[i][1] == ucoor[j][1])
				{
					HurdleGen(0);
				}
			}
		}
		for (int j = 0; j < 13; j++)
		{
			if (pwr[0] == ucoor[j][0] && pwr[1] == ucoor[j][1])
			{
				HurdleGen(0);
			}
		}
		if (difficulty >= 2)
		{
			do
			{
				zcoor[0][0] = (rand() % 57 + 1) * 10;
				zcoor[0][1] = (rand() % 57 + 1) * 10;
			} while (headx == zcoor[0][0] && heady == zcoor[0][1]);
			for (int i = 1; i < 5; i++)
			{
				zcoor[i][0] = zcoor[i - 1][0] + 10;
				zcoor[i][1] = zcoor[i - 1][1];
			}
			for (int i = 5; i < 9; i++)
			{
				zcoor[i][1] = zcoor[i - 1][1] - 10;
				zcoor[i][0] = zcoor[i - 1][0] - 10;
			}
			for (int i = 9; i < 13; i++)
			{
				zcoor[i][0] = zcoor[i - 1][0] + 10;
				zcoor[i][1] = zcoor[i - 1][1];
			}
			for (int i = 0; i < 13; i++)
			{
				if (headx == zcoor[i][0] && heady == zcoor[i][1])
				{
					HurdleGen(0);
				}
			}
			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 13; j++)
				{
					if (food[i][0] == zcoor[j][0] && food[i][1] == zcoor[j][1])
					{
						HurdleGen(0);
					}
				}
			}
		}glutPostRedisplay();

		
	}
	glutTimerFunc(150000.0 / FPS, HurdleGen, 0);
}
void PauseMenu()
{
	DrawLine(200, pausepnt, 350, pausepnt, 10, colors[BROWN]);
	DrawLine(200, pausepnt + 5, 350, pausepnt + 5, 10, colors[BROWN]);
	DrawLine(200, pausepnt + 10, 350, pausepnt + 10, 10, colors[BROWN]);
	DrawLine(200, pausepnt + 15, 350, pausepnt + 15, 10, colors[BROWN]);
	DrawString(200, 450, "New Game ", colors[GREEN]);
	DrawString(200, 410, "Resume Game ", colors[GREEN]);
	switch (difficulty)
	{
	case 1: DrawString(200, 370, "Difficulty ", colors[GREEN]);
		DrawTriangle(300, 372, 300, 384, 310, 378, colors[MISTY_ROSE]);
		DrawString(530, 20, "Normal", colors[YELLOW]);
		break;
	case 2: DrawTriangle(210, 372, 210, 384, 200, 378, colors[MISTY_ROSE]);
		DrawString(220, 370, "Difficulty ", colors[GREEN]);
		DrawTriangle(320, 372, 320, 384, 330, 378, colors[MISTY_ROSE]);
		DrawString(530, 20, "Hard", colors[CRIMSON]);
		break;
	case 3: DrawTriangle(210, 372, 210, 384, 200, 378, colors[MISTY_ROSE]);
		DrawString(220, 370, "Difficulty ", colors[GREEN]);
		DrawString(530, 20, "Very Hard", colors[BLACK]);
		break;
	}
	DrawString(200, 330, "High Scores ", colors[GREEN]);
	DrawString(200, 290, "Game History ", colors[GREEN]);
	DrawString(200, 250, "Exit Game ", colors[GREEN]); // this will print given string at x=50 , y=600
	if (pausepnt == 370)
	{
		DrawString(10, 40, "Left Key: Decrease", colors[MISTY_ROSE]); // this will print given string at x=50 , y=600}
		DrawString(10, 20, "Right Key: Increase", colors[MISTY_ROSE]);
	}
	else
	{
		DrawString(10, 20, " ENTER: Confirm ", colors[MISTY_ROSE]);
	} // this will print given string at x=50 , y=600
}
void Display() {
	// set the background color using function glClearColotgr.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.

	glClearColor(0/*Red Component*/, 0.05/*Green Component*/,
		0.15/*Blue Component*/, 0.1 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
	glClear(GL_COLOR_BUFFER_BIT);   //Update the colors
	for (int i = 0; i < 13; i++)
	{
		DrawSquare(ucoor[i][0] - 4, ucoor[i][1] - 4, 10, colors[MISTY_ROSE]);
		DrawSquare(zcoor[i][0] - 4, zcoor[i][1] - 4, 10, colors[MISTY_ROSE]);  //This will draw a square shape of size 100x100  at x=300 and y=300				
	}
	for (int i = 0; i < 5; i++)
	{
		DrawCircle(food[i][0], food[i][1], 4, colors[FIREBRICK]);  //This will draw a square shape of size 100x100  at x=300 and y=300
	}
	//This will draw a square shape of size 100x100  at x=300 and y=300
	DrawCircle(pwr[0], pwr[1], 8, colors[rand() % 139]);


	DrawString(500, 670, "Score: ", colors[MISTY_ROSE]); // this will print given string at x=50 , y=570
	DrawString(570, 670, pointsstr, colors[MISTY_ROSE]);

	glowcolor = 53 - glowcolor;
	// This will draw a circle at x=200,y=200 of radius 50 	
	if (points < (140*difficulty))
	{
		for (int i = 0; i < bodycount; i++)
		{
			DrawSquare(bodypt[i][0] - 4, bodypt[i][1] - 4, 10, colors[LIGHT_GREEN]);  //This will draw a square shape of size 100x100  at x=300 and y=300
		}
	}
	else
	{
		for (int i = 0; i < bodycount; i++)
		{
			DrawSquare(bodypt[i][0] - 4, bodypt[i][1] - 4, 10, colors[glowcolor]);  //This will draw a square shape of size 100x100  at x=300 and y=30
		}
	}
	DrawCircle(headx, heady, 7.75, colors[DARK_GREEN]);
	//	DrawCircle( x  -key1 , y , 1, colors[YELLOW]);
	if (key1 == 1)
	{
		DrawCircle(headx + mov * 2, heady - mov * 2, 1, colors[YELLOW]);
	}
	else
	{
		DrawCircle(headx + mov * 2, heady + mov * 2, 1, colors[YELLOW]);
	}


	if (gameover)
	{
		glClearColor(0/*Red Component*/, 0.0/*Green Component*/,
			0.05/*Blue Component*/, 0.1 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
		glClear(GL_COLOR_BUFFER_BIT);
		DrawString(130, 320, "GAME OVER! PRESS ESC TO EXIT", colors[YELLOW]); // this will print given string at x=50 , y=600
		DrawString(500, 670, "Score: ", colors[MISTY_ROSE]);
		DrawString(570, 670, pointsstr, colors[MISTY_ROSE]);
		gameover = true;
		ifstream hsfile("highscore.txt");

		hsfile >> highscorestr;

		stringstream s(highscorestr);
		s >> highscore;
		hsfile.close();
		if (points > highscore)
		{
			highscore = points;
			stringstream s2;
			ofstream ohsfile("highscore.txt");
			s2 << highscore;
			ohsfile << s2.str();
			ohsfile.close();
			highscorestr = s2.str();
			hs = true;
		}
		if(hs)
			DrawString(100, 280, "CONGRATULATIONS! NEW HIGH SCORE", colors[rand() % 139]);
		if (!historyadd)
		{
			fstream oghfile("gamehistory.txt", ios::app);
			oghfile << pointsstr << endl;
			oghfile.close();
			historyadd = true;
		}
	}
	DrawString(20, 670, "Snake: ", colors[GREEN]); // this will print given string at x=20 , y=670
	DrawLine(90, 675, 370, 675, 5, colors[GRAY]);
	if (points <= (140*difficulty))
	{
		DrawLine(90, 675, 90 + ((points * 2) / difficulty), 675, 7, colors[DARK_GREEN]);
	}
	else
	{
		DrawLine(90, 675, 370, 675, 7, colors[DARK_GREEN]);
		DrawString(400, 670, "FULL", colors[rand() % 139]);
		full = true;
	}


	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	DrawLine(650, 0, 650, 650, 10, colors[CRIMSON]);
	DrawLine(0, 0, 0, 650, 10, colors[CRIMSON]);
	DrawLine(0, 0, 650, 0, 10, colors[CRIMSON]);
	DrawLine(0, 650, 650, 650, 10, colors[CRIMSON]);

	if (pausegame)
	{
		glClearColor(0/*Red Component*/, 0.1/*Green Component*/,
			0.2/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
		glClear(GL_COLOR_BUFFER_BIT);
		PauseMenu();
		//DrawString( 250, 620, "GAME PAUSED.", colors[RED]); // this will print given string at x=50 , y=600
		if (newgame)
		{
			DrawString(500, 670, "Score: ", colors[MISTY_ROSE]);
			DrawString(570, 670, pointsstr, colors[MISTY_ROSE]);
		}
		else
		{
			DrawString(50, 660, "RABIA'S SNAKE GAME", colors[LIME_GREEN]);

			for (int i = 0; i < 5; i++)
			{
				DrawSquare(500 + (10 * i) - 4, 665, 10, colors[FOREST_GREEN]);
			}  //This will draw a square shape of size 10x10  at x=500 + 10*i and y=665
			DrawCircle(500, 670, 9, colors[DARK_GREEN]);
		}
	}
	if (highscoredisp)
	{
		glClearColor(0/*Red Component*/, 0.1/*Green Component*/,
			0.2/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
		glClear(GL_COLOR_BUFFER_BIT);
		DrawString(200, 300, "Highest Score: ", colors[MISTY_ROSE]);
		DrawString(350, 300, highscorestr, colors[MISTY_ROSE]);
		DrawString(10, 20, " BACKSPACE: Back ", colors[MISTY_ROSE]);
	}
	if (historydisp)
	{
		glClearColor(0/*Red Component*/, 0.1/*Green Component*/,
			0.2/*Blue Component*/, 0 /*Alpha component*/);// Red==Green==Blue==1 --> White Colour
		glClear(GL_COLOR_BUFFER_BIT);
		string line = "";
		vector<string> v(5);
		ifstream file("gamehistory.txt");
		if (file.eof())
			file >> line;
		if (file)
		{
			while (getline(file, line))
			{
				v.push_back(line);
			}
			/* Printing the lines from Bottom to Top */
			for (int i = v.size() - 1, k = 1; i >= v.size() - 5; i--, k++)
			{
				DrawString(300, 500 - (k * 50), v[i], colors[MISTY_ROSE]);
			}
		}
		file.close();
		DrawString(10, 20, " BACKSPACE: Back ", colors[MISTY_ROSE]);
	}
	glutSwapBuffers(); // do not modify this line..
}
/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

void NonPrintableKeys(int key, int a, int b) {
	if (!gameover)
	{
		if (pausegame)
		{
			if (key == GLUT_KEY_DOWN && pausepnt > 250)
			{
				pausepnt -= 40;
			}
			if (key == GLUT_KEY_UP && pausepnt < 450)
			{
				pausepnt += 40;
			}
			if (key == GLUT_KEY_LEFT && pausepnt == 370 && difficulty > 1)
			{
				difficulty--;
			}
			if (key == GLUT_KEY_RIGHT && pausepnt == 370 && difficulty < 3)
			{
				difficulty++;
			}
		}
		else
		{
			if (key == GLUT_KEY_LEFT && key1 != 2   /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
			{
				key1 = 1;
				mov = -1;
				for (int i = bodycount - 1; i >= 1; i--)
				{
					bodypt[i][0] = bodypt[i - 1][0];
					bodypt[i][1] = bodypt[i - 1][1];
				}
				bodypt[0][0] = headx;
				bodypt[0][1] = heady;									// what to do when left key is pressed...
				headx -= 10;

				glutPostRedisplay();

			}
			else if (key == GLUT_KEY_RIGHT && key1 != 1  /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/)
			{
				key1 = 2;
				mov = 1;
				for (int i = bodycount - 1; i >= 1; i--)
				{
					bodypt[i][0] = bodypt[i - 1][0];
					bodypt[i][1] = bodypt[i - 1][1];
				}
				bodypt[0][0] = headx;
				bodypt[0][1] = heady;
				headx += 10;


			}
			else if (key == GLUT_KEY_UP && key1 != 4) /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/
			{
				key1 = 3;
				mov = 1;
				for (int i = bodycount - 1; i >= 1; i--)
				{
					bodypt[i][0] = bodypt[i - 1][0];
					bodypt[i][1] = bodypt[i - 1][1];
				}
				bodypt[0][0] = headx;
				bodypt[0][1] = heady;
				heady += 10;


			}
			else if (key == GLUT_KEY_DOWN && key1 != 3)   /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/
			{
				key1 = 4;
				mov = -1;
				for (int i = bodycount - 1; i >= 1; i--)
				{
					bodypt[i][0] = bodypt[i - 1][0];
					bodypt[i][1] = bodypt[i - 1][1];
				}
				bodypt[0][0] = headx;
				bodypt[0][1] = heady;
				heady -= 10;

			}
		}


	}
	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/
	glutPostRedisplay();
}


/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == KEY_ESC/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}
	if (key == 'R' || key == 'r'/* Escape key ASCII*/) {
		//exit(1); // exit the program when escape key is pressed.
	}

	else if (int(key) == 13)
	{
	}
	else if (int(key) == 32)
	{
		pausegame = !pausegame;

	}
	if (pausegame)
	{
		if (key == 13)
		{
			if (pausepnt == 250)
			{
				exit(1);
			}
			if (pausepnt == 410 && newgame)
			{
				pausegame = 0;
			}
			if (pausepnt == 330)
			{
				highscoredisp = true;
			}
			if (pausepnt == 290)
			{
				historydisp = true;
			}
			if (pausepnt == 450)
			{
				headx = 200;
				heady = 200;
				
				gameover = false;
				for (int i = 0; i < 5; i++)
				{
					food[i][0] = 800;
					food[i][1] = 800;
				}
				bodypt[0][0] = headx;
				bodypt[0][1] = heady - 10;
				bodypt[1][0] = headx;
				bodypt[1][1] = heady - 20;

				pointsstr = "0";
				startx = 320, starty = 400;
				full = false;
				bodycount = 2;
				key1 = 3;
				points = 0;
				mov = 1;
				pausepnt = 410;
				pwr[0] = 800;
				pwr[1] = 800;
				glowcolor = 25;
				power = false;
				pausegame = false;
				for (int i = 0; i < 13; i++)
				{
					ucoor[i][0] = 0;
					zcoor[i][0] = 0;
					ucoor[i][1] = 0;
					zcoor[i][1] = 0;
				}
				if (!newgame)
				{
					glutTimerFunc(0 / FPS, Timer, 0);
					glutTimerFunc(0 / FPS, FoodTimer, 0);
					glutTimerFunc(300000.0 / FPS, PwrTimer, 0);

					glutTimerFunc(0 / FPS, HurdleGen, 0);
				}
				glutPostRedisplay();
				newgame = true;
			}
		}
	}
	if (highscoredisp || historydisp)
	{
		if (key == 8)
		{
			highscoredisp = false;
			historydisp = false;
		}
	}
	glutPostRedisplay();
}

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void FoodTimer(int m)
{
	if (!gameover && !pausegame)
	{
		for (int i = 0; i < 5; i++)
		{
			food[i][0] = (rand() % 63 + 1) * 10;
			food[i][1] = (rand() % 63 + 1) * 10;
			for (int j = 0; j < 5; j++)
			{
				if (i == j)
				{
					continue;
				}
				while ((food[i][0] == food[j][0]) || (food[i][1] == food[j][1]))
				{
					food[i][0] = (rand() % 63 + 1) * 10;
					food[i][1] = (rand() % 63 + 1) * 10;
				}
			}
		}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				if (food[i][0] == ucoor[j][0] && food[i][1] == ucoor[j][1])
				{
					FoodTimer(0);
				}
			}
		}
		glutPostRedisplay();
		
	}
	glutTimerFunc(75000.0 / FPS, FoodTimer, 0);
}
void PwrVanish(int m)
{
	pwr[0] = 800;
	pwr[1] = 800;
	glutTimerFunc(300000.0 / FPS, PwrTimer, 0);
}

void PwrTimer(int m)
{
	if (!gameover && !pausegame)
	{
		pwr[0] = (rand() % 63 + 1) * 10;
		pwr[1] = (rand() % 63 + 1) * 10;
		glutPostRedisplay();
		
	}
	glutTimerFunc(75000.0 / FPS, PwrVanish, 0);
}

void Timer(int m) {
	if (!gameover && !pausegame)
	{
		if (key1 == 1   /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
		{

			for (int i = bodycount - 1; i >= 1; i--)
			{
				bodypt[i][0] = bodypt[i - 1][0];
				bodypt[i][1] = bodypt[i - 1][1];
			}
			bodypt[0][0] = headx;
			bodypt[0][1] = heady;							// what to do when left key is pressed...
			headx -= 10;
		}

		else if (key1 == 2  /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/)
		{
			for (int i = bodycount - 1; i >= 1; i--)
			{
				bodypt[i][0] = bodypt[i - 1][0];
				bodypt[i][1] = bodypt[i - 1][1];
			}
			bodypt[0][0] = headx;
			bodypt[0][1] = heady;
			headx += 10;

		}
		else if (key1 == 3) /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/
		{
			for (int i = bodycount - 1; i >= 1; i--)
			{
				bodypt[i][0] = bodypt[i - 1][0];
				bodypt[i][1] = bodypt[i - 1][1];
			}
			bodypt[0][0] = headx;
			bodypt[0][1] = heady;
			heady += 10;


			glutPostRedisplay();
		}
		else if (key1 == 4)   /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/
		{
			for (int i = bodycount - 1; i >= 1; i--)
			{
				bodypt[i][0] = bodypt[i - 1][0];
				bodypt[i][1] = bodypt[i - 1][1];
			}
			bodypt[0][0] = headx;
			bodypt[0][1] = heady;
			heady -= 10;



			/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
			 * this function*/
			glutPostRedisplay();
		}

		glutPostRedisplay();

	}
	glutTimerFunc((1000.0 - (500 * power)) / (FPS * difficulty), Timer, 0);
}

/*
 * our gateway main function
 * */
int main(int argc, char* argv[]) {

	ifstream hsfile2("highscore.txt");

	hsfile2 >> highscorestr;
	hsfile2.close();
	int width = 650, height = 700; // i have set my window size to be 650 x 700
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(100, 100); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("RABIA's Snake Game"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

// Register your functions to the library,
// you are telling the library names of function to call for different tasks.
//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.
	glutDisplayFunc(Display); // tell library which function to call for drawing Canvas.
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
 /*   glutTimerFunc(0 / FPS, Timer, 0);
	glutTimerFunc(0 / FPS, FoodTimer, 0);
	glutTimerFunc(300000.0 / FPS, PwrTimer, 0);

	glutTimerFunc(150.0/FPS, HurdleGen, 0);*/
	glutTimerFunc(0, collisionDetect, 0);
	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* Snake Game */