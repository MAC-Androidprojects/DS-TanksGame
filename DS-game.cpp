#include <iostream>
#include <conio.h>
#include <dos.h>
#include <windows.h>
#include <time.h>
#include <string>
#include <fstream>

#define SCREEN_WIDTH 90
#define SCREEN_HEIGHT 26
#define WIN_WIDTH 70

using namespace std;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;       // To specify the coordinates
int carPos = WIN_WIDTH / 2; // To initialize it at the half of the screen

class Hash
{

    // Pointer to an array
    int *table;

public:
    int BUCKET;
    Hash(int x); // Constructor

    // inserts a key into hash table
    void insertItem(int x);

    // deletes a key from hash table
    void deleteItem(int key);

    // hash function to map values to key
    int hashFunction(int x)
    {
        return (x % BUCKET);
    }

    int searchItem();
};

Hash::Hash(int x)
{
    this->BUCKET = x;
    table = new int[BUCKET];
}

void Hash::insertItem(int key)
{
    int index = hashFunction(key);
    table[index] = 1;
}

void Hash::deleteItem(int key)
{
    // get the hash index of key
    int index = hashFunction(key);
    table[index] = 0;
}
int Hash::searchItem()
{
    for (int i = 0; i < BUCKET; i++)
    {
        if (table[i] == 1)
        {
            int pos = i + 17;
            if (pos == carPos)
                return pos;
            else
                return pos + 17;
        }
    }
}

int enemyY[3];
int enemyX[3];
Hash computerPos(17);

int enemyFlag[3];
int car[4][4] = {
    {254, 32, 32, 254},
    {254, 254, 254, 254},
    {254, 254, 254, 254},
    {254, 32, 32, 254}};

int g_enemy_tank[4][4] = {
    {194, 32, 32, 194},
    {194, 194, 194, 194},
    {194, 194, 194, 194},
    {194, 32, 32, 194}};

int score = 0; // Initialize score with zero

void gotoxy(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
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
void drawBorder()
{
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        for (int j = 0; j < 17; j++)
        {
            gotoxy(0 + j, i);
            cout << char(178);
            gotoxy(WIN_WIDTH - j, i);
            cout << char(178);
        }
    }
    for (int i = 0; i < SCREEN_HEIGHT; i++)
    {
        gotoxy(SCREEN_WIDTH, i);
        cout << char(178);
    }
}
void genEnemy(int ind)
{
    enemyX[ind] = computerPos.searchItem();
}
void drawEnemy(int ind)
{
    if (enemyFlag[ind] == true)
    {
        int i;
        gotoxy(enemyX[ind], enemyY[ind]);
        for (i = 0; i < 4; i++)
        {
            cout << char(g_enemy_tank[0][i]);
        }
        gotoxy(enemyX[ind], enemyY[ind] + 1);
        for (i = 0; i < 4; i++)
        {
            cout << char(g_enemy_tank[1][i]);
        }
        gotoxy(enemyX[ind], enemyY[ind] + 2);
        for (i = 0; i < 4; i++)
        {
            cout << char(g_enemy_tank[2][i]);
        }
        gotoxy(enemyX[ind], enemyY[ind] + 3);
        for (i = 0; i < 4; i++)
        {
            cout << char(g_enemy_tank[3][i]);
        }
    }
}
void eraseEnemy(int ind)
{
    if (enemyFlag[ind] == true)
    {
        gotoxy(enemyX[ind], enemyY[ind]);
        cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 1);
        cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 2);
        cout << "    ";
        gotoxy(enemyX[ind], enemyY[ind] + 3);
        cout << "    ";
    }
}
void resetEnemy(int ind)
{
    eraseEnemy(ind);
    enemyY[ind] = 1;
    genEnemy(ind);
}

void drawCar()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoxy(j + carPos, i + 22);
            cout << char(car[i][j]);
        }
    }
}
void eraseCar()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            gotoxy(j + carPos, i + 22);
            cout << " ";
        }
    }
}

int collision()
{
    if (enemyY[0] + 4 >= 23)
    {
        if (enemyX[0] + 4 - carPos >= 0 && enemyX[0] + 4 - carPos < 9)
        {
            return 1;
        }
    }
    return 0;
}
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
    cout << "\t\t----- your score: " << score << " -----" << endl;

    cout << "\t\t---- best score: " << max_score << " ------" << endl;
    cout << "\t\tPress any key to go back to menu.";
    getch();
}
void updateScore()
{
    gotoxy(WIN_WIDTH + 7, 5);
    cout << "Score: " << score << endl;
}

void instructions()
{

    system("cls");
    cout << "Instructions";
    cout << "\n----------------";
    cout << "\n Avoid Cars by moving left or right. ";
    cout << "\n\n Press 'a' to move left";
    cout << "\n Press 'd' to move right";
    cout << "\n Press 'escape' to exit";
    cout << "\n\nPress any key to go back to menu";
    getch();
}

void play()
{
    carPos = -1 + WIN_WIDTH / 2;
    computerPos.insertItem(carPos);
    score = 0;
    enemyFlag[0] = 1;
    enemyFlag[1] = 0;
    enemyY[0] = enemyY[1] = 1;

    system("cls");
    drawBorder();
    updateScore();
    genEnemy(0);
    genEnemy(1);

    gotoxy(WIN_WIDTH + 7, 2);
    cout << "Car Game";
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

    gotoxy(18, 5);
    cout << "Press any key to start";
    getch();
    gotoxy(18, 5);
    cout << "                      ";

    while (1)
    {
        if (kbhit())
        {
            computerPos.deleteItem(carPos);
            char ch = getch();
            if (ch == 'a' || ch == 'A')
            {
                if (carPos > 18)
                    carPos -= 4;
            }
            if (ch == 'd' || ch == 'D')
            {
                if (carPos < 50)
                    carPos += 4;
            }
            if (ch == 27)
            {
                break;
            }
            computerPos.insertItem(carPos);
        }

        drawCar();
        drawEnemy(0);
        drawEnemy(1);
        if (collision() == 1)
        {
            gameover();
            return;
        }
        Sleep(50);
        eraseCar();
        eraseEnemy(0);
        eraseEnemy(1);

        if (enemyY[0] == 10)
            if (enemyFlag[1] == 0)
                enemyFlag[1] = 1;

        if (enemyFlag[0] == 1)
            enemyY[0] += 1;

        if (enemyFlag[1] == 1)
            enemyY[1] += 1;

        if (enemyY[0] > SCREEN_HEIGHT - 4)
        {
            resetEnemy(0);
            score++;
            updateScore();
        }
        if (enemyY[1] > SCREEN_HEIGHT - 4)
        {
            resetEnemy(1);
            score++;
            updateScore();
        }
    }
}

int main()
{

    setcursor(0, 0);
    srand((unsigned)time(NULL));

    do
    {
        system("cls"); // To clear the whole screen
        gotoxy(10, 5);
        cout << " -------------------------- ";
        gotoxy(10, 6);
        cout << " |        Car Game        | ";
        gotoxy(10, 7);
        cout << " --------------------------";
        gotoxy(10, 9);
        cout << "1. Start Game";
        gotoxy(10, 10);
        cout << "2. Instructions";
        gotoxy(10, 11);
        cout << "3. Quit";
        gotoxy(10, 13);
        cout << "Select option: ";
        char op = getche(); // To get a char

        if (op == '1')
            play();
        else if (op == '2')
            instructions();
        else if (op == '3')
            exit(0);

    } while (1);

    return 0;
}