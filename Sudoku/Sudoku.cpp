#include "pch.h"
//#include <bits/stdc++.h>  //final si bun
#include <windows.h>

using namespace std;
int l = 81, nrhint, u, i1, jj1, asol[10][10], ahint[10][10], a[10][10];
HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
struct abc {
	int q, p;
};
abc hints[100];
int a1[10][10] = { {1,0,0,4,8,9,0,0,6},
			   {7,3,0,0,0,0,0,4,0},
			   {0,0,0,0,0,1,2,9,5},
			   {0,0,7,1,2,0,6,0,0},
			   {5,0,0,7,0,3,0,0,8},   //EASY
			   {0,0,6,0,9,5,7,0,0},
			   {9,1,4,6,0,0,0,0,0},
			   {0,2,0,0,0,0,0,3,7},
			   {8,0,0,5,1,2,0,0,4} };
int a2[10][10] = { {0,2,0,6,0,8,0,0,0},
			   {5,8,0,0,0,9,7,0,0},
			   {0,0,0,0,4,0,0,0,0},
			   {3,7,0,0,0,0,5,0,0},    //INTERMEDIATE
			   {6,0,0,0,0,0,0,0,4},
			   {0,0,8,0,0,0,0,1,3},
			   {0,0,0,0,2,0,0,0,0},
			   {0,0,9,8,0,0,0,3,6},
			   {0,0,0,3,0,6,0,9,0} };
int a3[10][10] = { {2,0,0,3,0,0,0,0,0},
				{8,0,4,0,6,2,0,0,3},
				{0,1,3,8,0,0,2,0,0},
				{0,0,0,0,2,0,3,9,0},    //HARD
				{5,0,7,0,0,0,6,2,1},
				{0,3,2,0,0,6,0,0,0},
				{0,2,0,0,0,9,1,4,0},
				{6,0,1,2,5,0,8,0,9},
				{0,0,0,0,0,1,0,0,2} };
int a4[10][10] = { {0,2,0,0,0,0,0,0,0},
				{0,0,0,6,0,0,0,0,3},
				{0,7,4,0,8,0,0,0,0},
				{0,0,0,0,0,3,0,0,2},
				{0,8,0,0,4,0,0,1,0},    //INSANE
				{6,0,0,5,0,0,0,0,0},
				{0,0,0,0,1,0,7,8,0},
				{5,0,0,0,0,9,0,0,0},
				{0,0,0,0,0,0,0,4,0} };
namespace hint
{
	void construire()
	{
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				if (a[i][j] != 0)
					ahint[i][j] = 1, l--;
	}
	int chooserandomvalue()
	{
		int x;
		srand(time(NULL));
		x = rand() % l, x++;
		return x;
	}
	void inlocuire()
	{
		int k = 0, kprim = chooserandomvalue();
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				if (a[i][j] == 0)
				{
					k++;
					if (k == kprim)
						a[i][j] = asol[i][j], hints[u].q = i, hints[u++].p = j;
				}

	}
}
namespace rezSudoku
{
	int verif(int b, int c, int q) //CHECKING IF OUR NUMBER IS CORRECT
	{
		int nn, mm;
		for (int i = 0; i < 9; i++)
		{
			//WE CHECK THE ROW
			if (asol[b][i] == q)
				return 0;
			//WE CHECK THE COLUMN
			if (asol[i][c] == q)
				return 0;
		}
		nn = b - b % 3, mm = c - c % 3;
		//WE CHECK THE SQUARE
		for (int i = nn; i < nn + 3; i++)
			for (int j = mm; j < mm + 3; j++)
				if (asol[i][j] == q)
					return 0;
		return 1;
	}
	int gasire() //FINDING THE FIRST UNCOMPLETED NUMBER
	{
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				if (asol[i][j] == 0)
				{
					i1 = i, jj1 = j;
					return 0;
				}
		return 1;
	}
	int gasiregenerala() //FINDING THE FIRST UNCOMPLETED NUMBER
	{
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				if (a[i][j] == 0)
					return 0;
		return 1;
	}
	int rezolvare(int i, int j) //BACKTRACKING PART
	{
		for (int l = 1; l <= 9; l++)
			if (verif(i, j, l))
			{
				asol[i][j] = l;
				gasire();
				rezolvare(i1, jj1);
				if (gasire())
					return 0;
				asol[i][j] = 0;
			}
	}
	void afisare()
	{
		cout << "    1  2  3  4  5  6  7  8  9" << endl << endl << endl;
		for (int i = 0; i < 9; i++)
		{
			cout << i + 1 << "   ";
			SetConsoleTextAttribute(h, FOREGROUND_RED);
			for (int j = 0; j < 9; j++)
				cout << asol[i][j] << "  ";
			SetConsoleTextAttribute(h, FOREGROUND_GREEN);
			cout << endl << endl;
		}

	}
};
int main()
{
	int g;
	cout << "Welcome to our Sudoku minigame, enjoy :)" << endl;
	cout << "To submit a number type the row then press enter , collumn then enter and so on" << endl;
	cout << "If you find yourself stuck write --Hint-- and a random empty bracket will be completed" << endl;
	cout << "If you want to give up write --Solution-- and the solution of the Sudoku will be displayed" << endl;
	cout << "Please select the dificulty:" << endl;
	cout << "1) Easy" << endl;
	cout << "2) Intermediate" << endl;
	cout << "3) Hard" << endl;
	cout << "4) Insane" << endl;
	cin >> g;
	cin.get();
	if (g == 1)
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				a[i][j] = a1[i][j];
	if (g == 2)
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				a[i][j] = a2[i][j];
	if (g == 3)
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				a[i][j] = a3[i][j];
	if (g == 4)
		for (int i = 0; i < 9; i++)
			for (int j = 0; j < 9; j++)
				a[i][j] = a4[i][j];
	for (int i = 0; i < 9; i++)
		for (int j = 0; j < 9; j++)
			asol[i][j] = a[i][j];
	rezSudoku::gasire();
	rezSudoku::rezolvare(i1, jj1);
	hint::construire();
	system("cls");
	char rcaracter[10];
	int r, c, n, rc, rr, lc, lr, flag1, flag2, flag3, flag4, flagsol = 0, flag5;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_GREEN);
	do
	{
		flag5 = flag1 = flag2 = flag3 = flag4 = 0;
		cout << "    1  2  3  4  5  6  7  8  9" << endl << endl << endl;
		for (int i = 0; i < 9; i++) //Displaying the current state of the board
		{
			cout << i + 1 << "   ";
			for (int j = 0; j < 9; j++)
			{
				for (int y = 0; y < u; y++)
					if (hints[y].q == i && hints[y].p == j)
					{
						SetConsoleTextAttribute(h, FOREGROUND_BLUE);
						cout << a[i][j] << "  ";
						SetConsoleTextAttribute(h, FOREGROUND_GREEN);
						flag5 = 1;
					}
				if (flag5 == 0)
					cout << a[i][j] << "  ";
				flag5 = 0;
			}
			cout << endl << endl;
		}
		cout << "Enter your move :(row, column, digit) " << endl;
		cin.getline(rcaracter, 10);
		if (strcmp(rcaracter, "Solution") == 0)//We check if the user has given up and wants to see the solution
		{
			system("cls");
			rezSudoku::afisare();
			flagsol = 1;
			break;
		}
		if (strcmp(rcaracter, "Hint") == 0)//We check if the user wants to receive a hint
		{
			nrhint++;
			system("cls");
			hint::inlocuire();
			l--;
			continue;
		}
		r = atoi(rcaracter);
		cin >> c >> n;
		cin.get();
		r = r - 1, c = c - 1;
		system("cls");
		if (a[r][c] != 0)
		{
			if (ahint[r][c] == 1) //Error for overwriting that bracket
			{
				cout << "That is not possible, there is already a number there, choose another bracket" << endl;
				continue;
			}
			else {
				a[r][c] = n;
				continue;
			}
		}
		rr = r - r % 3, rc = c - c % 3, lr = rr + 3, lc = rc + 3;
		//Searching the square
		for (int i = rr; i < lr; i++)
			for (int j = rc; j < lc; j++)
				if (a[i][j] == n && i != r && j != c)
					flag1 = 1;
		if (flag1 == 1)
		{
			cout << "That is not possible there is the same number in that square, choose another number" << endl;
			continue;
		}
		//Searching the column
		for (int i = 0; i < 9; i++)
			if (a[i][c] == n && i != r)
				flag2 = 1;
		if (flag2 == 1)
		{
			cout << "That is not possible there is the same number in that column, choose another number" << endl;
			continue;
		}
		//Searcing the row
		for (int i = 0; i < 9; i++)
			if (a[r][i] == n && i != c)
				flag3 = 1;
		if (flag3 == 1)
		{
			cout << "That is not possible there is the same number in that row, choose another number" << endl;
			continue;
		}
		a[r][c] = n, l--;
		if (n >= 10) //Error for writing a number that is not a digit
		{
			cout << "Please enter a digit" << endl;
			continue;
		}

	} while (rezSudoku::gasiregenerala() == 0);
	if (flagsol == 0)
		cout << "CONGRATULATIONS, YOU FINISHED THE SUDOKU PUZZLE!" << endl << "You used " << nrhint << " hints";
	else cout << "Maybe you will do better next time!";
	return 0;
}
