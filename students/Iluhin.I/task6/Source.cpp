#include <iostream>
#include <time.h>
#include <vector>
#include <Windows.h>
#include <conio.h>

using namespace std;

struct Point 
{
	int x;
	int y;
	Point() {};
	Point(int _x, int _y)
	{
		x = _x;
		y = _y;
	}
};

enum Course {LEFT,RIGHT,UP,DOWN};

/*void SetColor(int text, int background)
{
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hStdOut, (WORD)((background << 4) | text));
}
*/

class Zmeyka 
{
private:
	Course dir = LEFT;
	vector<Point> zmey;
	Point Beetle;
	char map[21][21];
public:
	Zmeyka() 
	{
		srand(time(NULL));
		Initialzation();
		GenerateBeetle();
		Update();
	}

	void Initialzation()
	{
		for (int i = 0; i < 5; i++)
		{
			Point a(15 + i, 5);
			zmey.push_back(a);
		}
	}

	void Update()
	{
		while (zmey.size()<400 && Validation())
		{

			if (InsideZmey())
			{
				zmey.push_back(zmey[zmey.size() - 1]);
				GenerateBeetle();
			}

			Draw();
			Move();
			Point dif;
			
			if (_kbhit()) 
			{
				switch (_getch())
				{
					case 'a':
						dir = LEFT;
						break;
					case 'd':
						dir = RIGHT;
						break;
					case 'w':
						dir = UP;
						break;
					case 's':
						dir = DOWN;
						break;
				}				
			}
			
			switch (dir)
			{
				case LEFT: {dif.x = -1; dif.y = 0; break; }
				case RIGHT: {dif.x = 1; dif.y = 0; break; }
				case UP: {dif.x = 0; dif.y = -1; break; }
				case DOWN: {dif.x = 0; dif.y = 1; break; }
			}

			zmey[0].x += dif.x;
			zmey[0].y += dif.y;

			Sleep(350);
		}
		//Clear();
		cout << "\n\tGAME OVER";
	}

	bool Validation()
	{
		if (zmey[0].x == -1 || zmey[0].y == -1 || zmey[0].x == 21 || zmey[0].y == 21)
			return false;
		for (int i = 1; i < zmey.size(); i++)
			if (zmey[0].x == zmey[i].x && zmey[0].y == zmey[i].y)
				return false;
		return true;
	}

	void Move()
	{
		for (int i = zmey.size()-1; i > 0; i--)
			zmey[i] = zmey[i-1];
	}

	void Draw() 
	{
		Clear();
		map[Beetle.x][Beetle.y] = 'Æ';
		for each (auto a in zmey)
		{
			map[a.x][a.y] = 'O';
		}
		for (int i = 0; i < 21; i++)
		{
			for (int j = 0; j < 21; j++)
				cout << map[j][i];
			cout << "|\n";
		}
		for (int i = 0; i < 21; i++)
			cout << "-";
		SetConsoleTextAttribute(hStdOut, 10);
	}

	void Clear() 
	{
		system("cls");
		for (int i = 0; i < 21; i++)
			for (int j = 0; j < 21; j++)
				map[i][j] = ' ';
	}

	void GenerateBeetle()
	{
		Beetle.x = rand() % 20;
		Beetle.y = rand() % 20;
		if (InsideZmey())
			GenerateBeetle();
	}

	bool InsideZmey()
	{
		for each (Point a in zmey)
		{
			if (a.x == Beetle.x && a.y == Beetle.y)
				return true;
		}
		return false;
	}

	HANDLE hConsole;
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

	enum ConsoleColor
	{
		Black = 0,
		Blue = 1,
		Green = 2,
		Cyan = 3,
		Red = 4,
		Magenta = 5,
		Brown = 6,
		LightGray = 7,
		DarkGray = 8,
		LightBlue = 9,
		LightGreen = 10,
		LightCyan = 11,
		LightRed = 12,
		LightMagenta = 13,
		Yellow = 14,
		White = 15
	};

	void SetColor(ConsoleColor head, ConsoleColor background)
	{
		SetConsoleTextAttribute(hStdOut, (WORD)((0 << 4) | 2));
	}
};




int main()
{
	setlocale(LC_ALL, "");
	Zmeyka z;
	cout << "\n";
	system("pause");
	return 0;
}