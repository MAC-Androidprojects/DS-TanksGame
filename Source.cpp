#include <iostream>
#include <windows.h>
#include<conio.h>
#include <time.h>

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


char g_tank[4][3]={
	{'*','*','*'},
	{' ','*',' '},
	{' ','*',' '},
	{'*','*','*'}
};

int g_my_tank_position_x = 0;
int g_enemy_tank_position_x = 0;

/*to calculate the center position of the tanck*/
int g_my_tank_center = SCREEN_WIDTH/2;

/*to calculate the center position of the tanck*/
int g_enemy_tank_center = SCREEN_WIDTH/2;


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

void draw_bourder(){
	for(int row = 0 ; row < SCREEN_HEIGHT; row++){
		/*this loop used to draw the bourders of the left side*/
		for(int col = 0 ; col < 10 ; col++){
			gotoxy(col , row);
			cout<<"+";
		}
		/*this loop used to draw the bourders of the rigth side*/
		for(int col = SCREEN_WIDTH - 10 ; col < SCREEN_WIDTH; col++){
			gotoxy(col , row);
			cout<<"+";
		}
	}

}

/*function used to draw the user's tank */
void draw_my_tank(){
	/*for loop to get the tank coordenates and draw it*/
	/*this loop to detect the y of the height of the tank*/
	for(int posy = 0 ; posy < 4 ; posy++){
		gotoxy((g_my_tank_center - 1) , (MY_TANK_POSTIONY - posy));
		/*this loop to detect the x of the wigth of the tank*/
		for(int posx = 0 ; posx < 3 ; posx++){
			/*draw the tank using the array g_tank*/
			cout<<g_tank[posy][posx];
		}
	}
}

/*function used to draw the PC's tank */
void draw_enemy_tank(){
	/*for loop to get the tank coordenates and draw it*/
	/*this loop to detect the y of the height of the tank*/
	for(int posy = 0 ; posy < 4 ; posy++){
		gotoxy((g_enemy_tank_center - 1) , (posy));
		/*this loop to detect the x of the wigth of the tank*/
		for(int posx = 0 ; posx < 3 ; posx++){
			/*draw the tank using the array g_tank*/
			cout<<g_tank[posy][posx];
		}
	}

}

/****************************************************/
int main(){
	draw_enemy_tank();
	draw_my_tank();
	draw_bourder();

	cout<<endl;
	return 0;
}