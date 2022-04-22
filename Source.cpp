#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <string>

using namespace std;

/*static configurations*/
#define SCREEN_WIDTH 70
#define SCREEN_HEIGHT 30
#define GAME_WIDTH 50
#define MY_TANK_POSTIONY 29
#define ENEMY_TANK_POSTIONY 0
/*******************************/

/*****Global variables*****/
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD cursor_position; // To specify the coordinates

/*Genral tank "for user and for the enemy"*/
int g_tank[4][4] = {
	{254, 32, 32, 254},
	{254, 254, 254, 254},
	{254, 254, 254, 254},
	{254, 32, 32, 254}};

int g_my_rocket[2][4] = {
	{193, 193, 193, 193},
	{32, 193, 193, 32}};

int g_enemy_rocket[2][4] = {
	{194, 194, 194, 194},
	{32, 194, 194, 32}};

/*the x positions for user and enemy .. y position is constant for both "user and enemy"*/
int g_my_tank_position_x = 0;
int g_enemy_tank_position_x = 0;

/*to calculate the center position of the tanck*/
int g_my_tank_center = SCREEN_WIDTH / 2;

/*to calculate the center position of the tanck*/
int g_enemy_tank_center = SCREEN_WIDTH / 2;

/****************************************************/

/*Functions definitions*/
void gotoxy(int x, int y)
{
	/*to determine the x position of the cursor in the console */
	cursor_position.X = x;
	/*to determine the y position of the cursor in the console */
	cursor_position.Y = y;
	/*passing the x,y position to the fucnction SetConsoleCursorPosition to move the cursor to the determined position*/
	SetConsoleCursorPosition(console, cursor_position);
}

void draw_bourder()
{
	for (int row = 0; row < SCREEN_HEIGHT; row++)
	{
		/*this loop used to draw the bourders of the left side*/
		for (int col = 0; col < 10; col++)
		{
			gotoxy(col, row);
			cout << char(178);
		}
		/*this loop used to draw the bourders of the rigth side*/
		for (int col = SCREEN_WIDTH - 10; col < SCREEN_WIDTH; col++)
		{
			gotoxy(col, row);
			cout << char(178);
		}
	}
}

/*---------------- sector for user elements---------------------*/
/*function used to draw the user's tank */
void draw_my_tank()
{
	/*for loop to get the tank coordenates and draw it*/
	/*this loop to detect the y of the height of the tank*/
	for (int posy = 0; posy < 4; posy++)
	{
		gotoxy((g_my_tank_center - 1), (MY_TANK_POSTIONY - posy));
		/*this loop to detect the x of the wigth of the tank*/
		for (int posx = 0; posx < 4; posx++)
		{
			/*draw the tank using the array g_tank*/
			cout << char(g_tank[posy][posx]);
		}
	}
}

/*function used to draw the user's rocket */
void draw_my_rocket()
{
	/*for loop to get the racket coordenates and draw it*/
	/*this loop to detect the y of the height of the rocket*/
	for (int posy = 0; posy < 2; posy++)
	{
		gotoxy((g_my_tank_center - 1), (MY_TANK_POSTIONY - 4 - posy));
		/*this loop to detect the x of the wigth of the rocket*/
		for (int posx = 0; posx < 4; posx++)
		{
			/*draw the user rocket using the array g_my_rocket*/
			cout << char(g_my_rocket[posy][posx]);
		}
	}
}
/*--------------------------------------------------------------------------------*/

/*---------------- sector for enemy elements---------------------*/
/*function used to draw the PC's tank */
void draw_enemy_tank()
{
	/*for loop to get the tank coordenates and draw it*/
	/*this loop to detect the y of the height of the tank*/
	for (int posy = 0; posy < 4; posy++)
	{
		gotoxy((g_enemy_tank_center - 1), (posy));
		/*this loop to detect the x of the wigth of the tank*/
		for (int posx = 0; posx < 4; posx++)
		{
			/*draw the tank using the array g_tank*/
			cout << char(g_tank[posy][posx]);
		}
	}
}

/*function used to draw the enemy's rocket */
void draw_enemy_rocket()
{
	/*for loop to get the racket coordenates and draw it*/
	/*this loop to detect the y of the height of the rocket*/
	for (int posy = 0; posy < 2; posy++)
	{
		gotoxy((g_enemy_tank_center - 1), (posy + 4));
		/*this loop to detect the x of the wigth of the rocket*/
		for (int posx = 0; posx < 4; posx++)
		{
			/*draw the racket using the array g_enemy_rocket*/
			cout << char(g_enemy_rocket[posy][posx]);
		}
	}
}
/*--------------------------------------------------------------------------------*/

/****************************************************/
int main()
{
	/* To clear the whole screen*/
	system("cls");
	/*calling just for test*/
	draw_enemy_tank();
	draw_enemy_rocket();
	draw_my_tank();
	draw_my_rocket();
	draw_bourder();

	cout << endl;
	return 0;
}