#include <iostream>
#include <conio.h>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include <string>
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std;
/*------------------------ static values ----------------------- - */
#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70
#define enhancment_Algorithm
#define enhancment_DS
/*-------------------------------------------------------------- - */

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition; // To specify the coordinates

/*To initialize it at the half of the screen and that value will be updated according to the x position of the player's tank*/
int g_player_tank_pos = WIN_WIDTH / 2;

/*To check if the position of the player was inserted before */
int g_position_flag = 0;
/*Used in algoritm enhancment which represents the last position in hash table*/
int g_position_hash_table = 0;

/*-------------------------------------------------------------------*/
/*----------------------- data structure used -----------------------*/
/*-------------------------------------------------------------------*/
/*
[description]: this sector holds a hash class used as a data structure for the game that
by mapping the current location of the players tank to a certain index in a table, then assign the current location
by 1 and the other indexex are 0's and searching about the (1) value by using the hashes technic.
*/
class Hash
{

	// Pointer to an array
	int *table;

public:
	/*dummy variable used to pass the table elements to the pointer table use it as array*/
	int BUCKET;

	/*** the prototypes of the functions used in the hash class***/
	/*Constructor to get the intial values*/
	Hash(int x);

	/*inserts a key into hash table*/
	void insertItem(int no_of_indexes);

	/*deletes a key from hash table*/
	void deleteItem(int key);

	/*hash function to map values to key*/
	/*the hashing function that gives the index of the input that is from 0 to (no_of_indexes-1)*/
	int hashFunction(int x)
	{
		return (x % BUCKET);
	}

	/*search function*/
	int searchItem();

	/*distructor to deallocate the table from the memory*/
	~Hash()
	{
		for (int i = 0; i < BUCKET; i++)
		{
			table[i] = 0;
		}
	}
	/************************************************************/
};

/***functions definitions sector of the hash class***/

/*the constructor gets the value of no_of_indexes that represents the number of the elements in
the hash table "the pointer table at the class" */
Hash::Hash(int no_of_indexes)
{
	/*assigne the dummy variable "BUCKET"*/
	this->BUCKET = no_of_indexes;
	/*creating a dynamic array and make its head or name is table .. which is private element*/
	table = new int[BUCKET];
	/*To make sure it's all zeros*/
	for (int i = 0; i < BUCKET; i++)
	{
		table[i] = 0;
	}
}

/*function to insert postion of the player's tank as index to the table*/
void Hash::insertItem(int position)
{
	/*converts the location to index*/
	int index = hashFunction(position);
	table[index] = 1;
}

/*function to delete the previous player's position*/
void Hash::deleteItem(int position)
{
	// get the hash index of key
	int index = hashFunction(position);
	table[index] = 0;
}

/*function used for searching */
int Hash::searchItem()
{

#ifndef enhancment_Algorithm
	/*to get complixity of O(n) and n depends on the BUCKET value*/
	for (int i = 0; i < BUCKET; i++)
	{
		if (table[i] == 1)
		{
#ifdef enhancment_DS
			int pos = i + 17;
			if (pos == g_player_tank_pos)
				return pos;
			else
				return pos + 17;
#else
			return i;
#endif
		}
	}
#endif
#ifdef enhancment_Algorithm
	if (!g_position_flag)
	{
		for (int i = 0; i < BUCKET; i++)
		{
			if (table[i] == 1)
			{
				g_position_flag = 1;
				g_position_hash_table = i;
				if ((g_position_hash_table + 17) == g_player_tank_pos)
					return g_position_hash_table + 17;
				else
					return g_position_hash_table + 34;
			}
		}
	}
	else
	{
		int i = g_position_hash_table;
		int g = g_position_hash_table;
		while (1)
		{
			if (table[i] == 1)
			{
				g_position_hash_table = i;
				if ((g_position_hash_table + 17) == g_player_tank_pos)
					return (g_position_hash_table + 17);
				else
					return (g_position_hash_table + 34);
			}
			if (table[g] == 1)
			{
				g_position_hash_table = g;
				if ((g_position_hash_table + 17) == g_player_tank_pos)
					return (g_position_hash_table + 17);
				else
					return (g_position_hash_table + 34);
			}
			i++;
			g--;
		}
	}
#endif
}
/************************************************************/
/*-------------------------------------------------------------- - */

/*------------------------------------------------------------------------------------*/
/*-----------------------this sector for enemy and user variables ---------------------*/
/*------------------------------------------------------------------------------------*/

/*two arrays to define the location of the enemy "computers' tanks"*/
int g_computer_y[2];
int g_computer_x[2];
#ifdef enhancment_DS
Hash computerPos(17);
#else
Hash computerPos(51);
#endif

/*enemy flage to get the flage to enemy second creation*/
int g_computer_tank_flag[2];

/*------------the shape of the player's and the computers tanks----------*/
int g_player_tank[4][4] = {
	{254, 32, 32, 254},
	{254, 254, 254, 254},
	{254, 254, 254, 254},
	{254, 32, 32, 254}};

int g_enemy_tank[4][4] = {
	{194, 32, 32, 194},
	{194, 194, 194, 194},
	{194, 194, 194, 194},
	{194, 32, 32, 194}};
/*-----------------------------------------------------------------------*/
/*-------------------------------------------------------------------------------------*/
int score = 0; // Initialize score with zero

/*function to set the cursor on the location (x,y) on the screen*/
void gotoxy(int x, int y)
{
	/*passing the positions x and y to the structure CursorPosition*/
	CursorPosition.X = x;
	CursorPosition.Y = y;
	/*passing the structure to the function SetConsoleCursorPosition to set the cursor on that (x,y) posision*/
	SetConsoleCursorPosition(console, CursorPosition);
}

void setcursor(bool visible, DWORD size)
{
	if (size == 0)
		size = 20;

	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}

/*function used just to set the borders layout of the game play*/
void drawBorder()
{
	for (int row = 0; row < SCREEN_HEIGHT; row++)
	{
		for (int col = 0; col < 17; col++)
		{
			gotoxy(0 + col, row);
			cout << char(178);
			gotoxy(WIN_WIDTH - col, row);
			cout << char(178);
		}
	}
	for (int row = 0; row < SCREEN_HEIGHT; row++)
	{
		gotoxy(SCREEN_WIDTH, row);
		cout << char(178);
	}
}

/*function used to get the users position and moves it to the g_computer_x[i] xlocation*/
void genEnemy(int ind)
{
	g_computer_x[ind] = computerPos.searchItem();
}

/*Function used to draw and set the enemy on the screen */
void drawEnemy(int ind)
{
	if (g_computer_tank_flag[ind] == true)
	{
		int i;
		gotoxy(g_computer_x[ind], g_computer_y[ind]);
		for (i = 0; i < 4; i++)
		{
			cout << char(g_enemy_tank[0][i]);
		}
		gotoxy(g_computer_x[ind], g_computer_y[ind] + 1);
		for (i = 0; i < 4; i++)
		{
			cout << char(g_enemy_tank[1][i]);
		}
		gotoxy(g_computer_x[ind], g_computer_y[ind] + 2);
		for (i = 0; i < 4; i++)
		{
			cout << char(g_enemy_tank[2][i]);
		}
		gotoxy(g_computer_x[ind], g_computer_y[ind] + 3);
		for (i = 0; i < 4; i++)
		{
			cout << char(g_enemy_tank[3][i]);
		}
	}
}

/*Function used to delete the enemy from the screen */
void eraseEnemy(int ind)
{
	if (g_computer_tank_flag[ind] == true)
	{
		gotoxy(g_computer_x[ind], g_computer_y[ind]);
		cout << "    ";
		gotoxy(g_computer_x[ind], g_computer_y[ind] + 1);
		cout << "    ";
		gotoxy(g_computer_x[ind], g_computer_y[ind] + 2);
		cout << "    ";
		gotoxy(g_computer_x[ind], g_computer_y[ind] + 3);
		cout << "    ";
	}
}

/*function used to regenerate and draw and set the enemy on the screen*/
void resetEnemy(int ind)
{
	eraseEnemy(ind);
	g_computer_y[ind] = 1;
	genEnemy(ind);
}

/*Function used to draw and set the player's tank on the screen depending on g_player_tank_pos*/
void draw_player_tank()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			gotoxy(j + g_player_tank_pos, i + 22);
			cout << char(g_player_tank[i][j]);
		}
	}
}

/*Function used to delete the the player's tank from the screen */
void erase_player_tank()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			gotoxy(j + g_player_tank_pos, i + 22);
			cout << " ";
		}
	}
}
/*function to detecte if there it collision happends between the enemy and player's tanks*/
int collision()
{
	if (g_computer_y[0] + 4 >= 23)
	{
		if (g_computer_x[0] + 4 - g_player_tank_pos >= 0 && g_computer_x[0] + 4 - g_player_tank_pos < 9)
		{
			g_position_flag = 0;
			return 1;
		}
	}
	g_position_hash_table = 0;
	return 0;
}

/*function gives the layout of gameover message*/
void gameover()
{
	ifstream indata; // indata is like
	ofstream file;
	int max_score;
	indata.open("best_score.txt");
	if (!indata)
	{
		max_score = 0;
		file.open("best_score.txt");
		file << max_score;
		file.close();
	}
	indata >> max_score;
	indata.close();
	if (score > max_score)
	{
		max_score = score;
		file.open("best_score.txt");
		file << max_score;
		file.close();
	}
	system("cls");
	cout << endl;
	cout << "\t\t--------------------------" << endl;
	cout << "\t\t-------- Game Over -------" << endl;
	cout << "\t\t--------------------------" << endl
		 << endl;
	cout << "\t\t----- your score: " << score << " -----" << endl
		 << endl;
	cout << "\t\t---- best score: " << max_score << " ------" << endl;
	cout << "\t\tPress any key to go back to menu.";
	getch();
}
void updateScore()
{
	gotoxy(WIN_WIDTH + 7, 5);
	cout << "Score: " << score << endl;
}
/*-----------------------------------------------------------------------------*/
/*--------------------------------- the game play -----------------------------*/
/*-----------------------------------------------------------------------------*/
void play()
{
	/*initializing:
	the user's tank position
	the first enemy's postion
	the score
	gives the flag to the firest enemy
	set the flag of the second enemy by 0
	set the y position of the enemy's tanks by 1
	*/

	g_player_tank_pos = -1 + WIN_WIDTH / 2;
	computerPos.insertItem(g_player_tank_pos);
	score = 0;
	g_computer_tank_flag[0] = 1;
	g_computer_tank_flag[1] = 0;
	g_computer_y[0] = g_computer_y[1] = 1;

	/*initialize the system*/
	system("cls");
	/*call these functions to set the game display layout*/
	drawBorder();
	updateScore();

	gotoxy(WIN_WIDTH + 2, 2);
	cout << "War of Tanks Game";
	gotoxy(WIN_WIDTH + 6, 4);
	cout << "----------";
	gotoxy(WIN_WIDTH + 6, 6);
	cout << "----------";
	gotoxy(WIN_WIDTH + 7, 12);
	cout << "Control ";
	gotoxy(WIN_WIDTH + 7, 13);
	cout << "-------- ";
	gotoxy(WIN_WIDTH + 2, 14);
	cout << " A Key - Left";
	gotoxy(WIN_WIDTH + 2, 15);
	cout << " D Key - Right";
	gotoxy(WIN_WIDTH + 2, 16);
	cout << " esc Key - to end";
	gotoxy(18, 5);
	cout << "Press any key to start";
	getch();
	gotoxy(18, 5);
	cout << "                      ";

	/*generate first and seconed enemys*/
	genEnemy(0);
	genEnemy(1);

	while (1)
	{
		/********section to control the user's tank position*******/
		if (kbhit())
		{
			char ch = getch();
			if (ch == 'a' || ch == 'A')
			{
				/*To delete the previous position from hash table*/
				computerPos.deleteItem(g_player_tank_pos);
				if (g_player_tank_pos > 18)
					g_player_tank_pos -= 4;
				/*To insert the previous position from hash table*/
				computerPos.insertItem(g_player_tank_pos);
			}
			if (ch == 'd' || ch == 'D')
			{
				/*To delete the previous position from hash table*/
				computerPos.deleteItem(g_player_tank_pos);
				if (g_player_tank_pos < 50)
					g_player_tank_pos += 4;
				/*To insert the previous position from hash table*/
				computerPos.insertItem(g_player_tank_pos);
			}

			if (ch == 27)
			{
				computerPos.~Hash();
				g_position_hash_table = 0;
				break;
			}
		}
		/**********************************************************/
		/*drawing the enemy and the player's tanks*/
		draw_player_tank();
		drawEnemy(0);
		drawEnemy(1);
		/******************************************/

		if (collision() == 1)
		{
			gameover();
			return;
		}
		/*sleep function just used to slow down the motion of the system*/
		Sleep(40);

		/*erasing the privious tanks before the up comming detection loop*/
		erase_player_tank();
		eraseEnemy(0);
		eraseEnemy(1);
		/*****************************************************************/

		/*------------section for the enemy flag----------------------*/
		/*
		[description]: this section detects if the difference between the y postions
		of the two enemy tanks, and if its 10 positions it gives a flag to set the second
		and when the distance of an enemy is SCREEN_HEIGHT - 4 the score will be updated
		*/
		if (g_computer_y[0] == 10)
			if (g_computer_tank_flag[1] == 0)
				g_computer_tank_flag[1] = 1;

		if (g_computer_tank_flag[0] == 1)
			g_computer_y[0] += 1;

		if (g_computer_tank_flag[1] == 1)
			g_computer_y[1] += 1;

		if (g_computer_y[0] > SCREEN_HEIGHT - 4)
		{
			resetEnemy(0);
			score++;
			updateScore();
		}
		if (g_computer_y[1] > SCREEN_HEIGHT - 4)
		{
			resetEnemy(1);
			score++;
			updateScore();
		}
		/*-----------------------------------------------------------*/
	}
}

int main()
{
	setcursor(0, 0);

	/*this do while(1) loop is a super loop to hang the system till the user choose "2. Quit"*/
	do
	{
		system("cls"); // To clear the whole screen
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x09);
		gotoxy(10, 5);
		cout << " -------------------------- ";
		gotoxy(10, 6);
		cout << " |        Tank Game        | ";
		gotoxy(10, 7);
		cout << " --------------------------";
		gotoxy(10, 9);
		cout << "1. Start Game";
		gotoxy(10, 10);
		cout << "2. Quit";
		gotoxy(10, 12);
		cout << "Select option press 1 or 2";
		char op = getche(); // To get a char

		if (op == '1')
			/*if the pressed key is 1 the play function will be called and the game will start*/
			play();
		else if (op == '2')
			/*if the pressed key is 2 the exit function will be called and the game will terminate*/
			exit(0);

	} while (1);
	return 0;
}