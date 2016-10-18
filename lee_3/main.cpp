#include "main.h"
#include<fstream>
#include<iostream>
#include<queue>
#include <ctime>
using namespace std;

// a sample exported function
void DLL_EXPORT SomeFunction(const LPCSTR sometext)
{
    MessageBoxA(0, sometext, "DLL Message", MB_OK | MB_ICONINFORMATION);
}

ifstream Map;
ifstream LocDim;
ofstream map;
ofstream out;
ofstream g;
int x[3000][3000], n, m, moves[3000][3000], viz[3000][3000], QueueElements, MoveList[3000], MoveCount, InitDir;
bool Done;
struct position { int sx, sy, dx, dy, Direction; };
position StartPosition, StopPosition;
clock_t t1;
queue<position> Queue;

void PrintUI()
{
	int i;
	i = MoveCount;
	while (i > 0)
	{
		if (MoveList[i] == 5)  g << "Turn right", out << 1 << '\n';
		else if (MoveList[i] == 6) g << "Turn left", out << 0 << '\n';
		else
		{
			int a, c = 0;
			a = MoveList[i];
			while (i > 1 && MoveList[i - 1] == a)
			{
				c++;
				i--;
			}
			g << "Do " << c << " steps";
			out << c << '\n';
		}
		g << "   ->   ";
		i--;
	}
}

void Compute()
{
	position ActualPosition;
	do
	{
		ActualPosition = Queue.front();
		Queue.pop();
#pragma region UP
		//UP///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//cout << "try UP\n";
		if (ActualPosition.sx != 1 && ActualPosition.Direction != 3)//if not on the edge and not heading the opposite direction
		{
			bool GoodMove = true;
			for (int i = ActualPosition.sy; i <= ActualPosition.dy; i++)
				if (x[ActualPosition.sx - 1][i] == 1)
					GoodMove = false;
			if (GoodMove)
			{
				//Check if turn is needed
				bool WithTurn = false;
				if (ActualPosition.Direction != 1)
					WithTurn = true;
				else;//no turn needed

				position NextPosition;
				NextPosition.sx = ActualPosition.sx - 1;
				NextPosition.sy = ActualPosition.sy;
				NextPosition.dx = ActualPosition.dx - 1;
				NextPosition.dy = ActualPosition.dy;
				NextPosition.Direction = 1;
				if (viz[NextPosition.sx][NextPosition.sy] > viz[ActualPosition.sx][ActualPosition.sy] + 1 + (int)WithTurn)
				{
					viz[NextPosition.sx][NextPosition.sy] = viz[ActualPosition.sx][ActualPosition.sy] + 1 + (int)WithTurn;
					moves[NextPosition.sx][NextPosition.sy] = 1;
					Queue.push(NextPosition);
				}

			}
		}
#pragma endregion
#pragma region RIGHT
		//RIGHT////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//cout << "try RIGHT\n";
		if (ActualPosition.dy != m && ActualPosition.Direction != 4)//if not on the edge and not heading the opposite direction
		{
			bool GoodMove = true;
			for (int i = ActualPosition.sx; i <= ActualPosition.dx; i++)
				if (x[i][ActualPosition.dy + 1] == 1)
					GoodMove = false;
			if (GoodMove)
			{
				//Check if turn is needed
				bool WithTurn = false;
				if (ActualPosition.Direction != 2)
					WithTurn = true;
				else;//no turn needed

				position NextPosition;
				NextPosition.sx = ActualPosition.sx;
				NextPosition.sy = ActualPosition.sy + 1;
				NextPosition.dx = ActualPosition.dx;
				NextPosition.dy = ActualPosition.dy + 1;
				NextPosition.Direction = 2;
				if (viz[NextPosition.sx][NextPosition.sy] > viz[ActualPosition.sx][ActualPosition.sy] + 1 + (int)WithTurn)
				{
					viz[NextPosition.sx][NextPosition.sy] = viz[ActualPosition.sx][ActualPosition.sy] + 1 + (int)WithTurn;
					moves[NextPosition.sx][NextPosition.sy] = 2;
					Queue.push(NextPosition);
				}
			}
		}
#pragma endregion
#pragma region DOWN
		//DOWN/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//cout << "try DOWN\n";
		if (ActualPosition.dx != n && ActualPosition.Direction != 1)//if not on the edge and not heading the opposite direction
		{
			bool GoodMove = true;
			for (int i = ActualPosition.sy; i <= ActualPosition.dy; i++)
				if (x[ActualPosition.dx + 1][i] == 1)
					GoodMove = false;
			if (GoodMove)
			{
				//Check if turn is needed
				bool WithTurn = false;
				if (ActualPosition.Direction != 3)
					WithTurn = true;
				else;//no turn needed

				position NextPosition;
				NextPosition.sx = ActualPosition.sx + 1;
				NextPosition.sy = ActualPosition.sy;
				NextPosition.dx = ActualPosition.dx + 1;
				NextPosition.dy = ActualPosition.dy;
				NextPosition.Direction = 3;
				if (viz[NextPosition.sx][NextPosition.sy] > viz[ActualPosition.sx][ActualPosition.sy] + 1 + (int)WithTurn)
				{
					viz[NextPosition.sx][NextPosition.sy] = viz[ActualPosition.sx][ActualPosition.sy] + 1 + (int)WithTurn;
					moves[NextPosition.sx][NextPosition.sy] = 3;
					Queue.push(NextPosition);
				}

			}
		}
#pragma endregion
#pragma region LEFT
		if (ActualPosition.sy != 1 && ActualPosition.Direction != 2)//if not on the edge and not heading the opposite direction
		{
			bool GoodMove = true;
			for (int i = ActualPosition.sx; i <= ActualPosition.dx; i++)
				if (x[i][ActualPosition.sy - 1] == 1)
					GoodMove = false;
			if (GoodMove)
			{
				//Check if turn is needed
				bool WithTurn = false;
				if (ActualPosition.Direction != 4)
					WithTurn = true;
				else;//no turn needed

				position NextPosition;
				NextPosition.sx = ActualPosition.sx;
				NextPosition.sy = ActualPosition.sy - 1;
				NextPosition.dx = ActualPosition.dx;
				NextPosition.dy = ActualPosition.dy - 1;
				NextPosition.Direction = 4;
				if (viz[NextPosition.sx][NextPosition.sy] > viz[ActualPosition.sx][ActualPosition.sy] + 1 + (int)WithTurn)
				{
					viz[NextPosition.sx][NextPosition.sy] = viz[ActualPosition.sx][ActualPosition.sy] + 1 + (int)WithTurn;
					moves[NextPosition.sx][NextPosition.sy] = 4;
					Queue.push(NextPosition);
				}
			}
		}
#pragma endregion
	} while (!Queue.empty());
}
void Initialize()
{
	LocDim >> InitDir;
	StartPosition.Direction = 0;
	LocDim >> StartPosition.sx >> StartPosition.sy >> StartPosition.dx >> StartPosition.dy;
	LocDim >> StopPosition.sx >> StopPosition.sy >> StopPosition.dx >> StopPosition.dy;
	Queue.push(StartPosition);

	StartPosition.Direction = InitDir + 1;
	viz[StartPosition.sx][StartPosition.sy] = 0;

}

extern "C" int DLL_EXPORT main()
{
    Map.open("D:\Map.txt");
    LocDim.open("D:\LocDim.txt");
    map.open("D:\leemap.txt");
    out.open("D:\Directions.txt");
    g.open("D:\\UIDirections.txt");

	t1 = clock();
	cout << "Reading MAP;\t";
	Map >> n >> m;
	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
		{
			Map >> x[i][j];
			if (x[i][j] == 255)
				x[i][j] = 1;
			else
				x[i][j] = 0;
			viz[i][j] = 10000;
		}

	}
	cout << "Time elapsed: " << (double)clock() - (double)t1 << '\n';
	Initialize();
	Compute();
	/*for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= m;j++)
			g<< viz[i][j]<<' ';
		g << '\n';
	}
	g << '\n';
	g << '\n';
	g << '\n';

	for (int i = 1;i <= n;i++)
	{
		for (int j = 1;j <= m;j++)
			g << moves[i][j] << ' ';
		g << '\n';
	}*/
	int minx, miny, mx, my;
	minx = StopPosition.sx;
	miny = StopPosition.sy;
	for (int i = StopPosition.sx; i <= StopPosition.dx; i++)
		for (int j = StopPosition.sy; j <= StopPosition.dy; j++)
			if (viz[i][j] < viz[minx][miny])
				minx = i, miny = j;
	/*for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= m; j++)
			map << moves[i][j] << " ";
		map << '\n';
	}*/
	moves[StartPosition.sx][StartPosition.sy] = StartPosition.Direction;
	mx = minx;
	my = miny;
	while (minx != StartPosition.sx || miny != StartPosition.sy)
	{

		if (moves[minx][miny] == 1)
		{
			MoveList[++MoveCount] = 1;
			minx++;
		}
		else if (moves[minx][miny] == 2)
		{
			MoveList[++MoveCount] = 2;
			miny--;
		}
		else if (moves[minx][miny] == 3)
		{
			MoveList[++MoveCount] = 3;
			minx--;
		}
		else if (moves[minx][miny] == 4)
		{
			MoveList[++MoveCount] = 4;
			miny++;
		}
		if (moves[mx][my] != moves[minx][miny])
		{
			cout << moves[mx][my] << ' ' << moves[minx][miny] << '\n';
			if ((moves[minx][miny] == 1 && moves[mx][my] == 3) ||
				(moves[minx][miny] == 2 && moves[mx][my] == 4) ||
				(moves[minx][miny] == 3 && moves[mx][my] == 1) ||
				(moves[minx][miny] == 4 && moves[mx][my] == 2))
			{
				MoveList[++MoveCount] = 5;
				MoveList[++MoveCount] = 5;
			}
			else if ((moves[minx][miny] == 1 && moves[mx][my] == 2) ||
				(moves[minx][miny] == 2 && moves[mx][my] == 3) ||
				(moves[minx][miny] == 3 && moves[mx][my] == 4) ||
				(moves[minx][miny] == 4 && moves[mx][my] == 1))
				MoveList[++MoveCount] = 5;
			else
				MoveList[++MoveCount] = 6;
		}
		mx = minx;
		my = miny;
	}
	int i;
	/*for (i = MoveCount; i > 0; i--)
		out << MoveList[i] << ' ';
	g << '\n';*/
	PrintUI();


	cout << "Total time elapsed: " << (double)clock() - (double)t1 << '\n';
	map.flush();
	out.flush();
	g.flush();
    LocDim.close();
	Map.close();
	map.close();

	out.close();
	g.close();

	return 0;
}



extern "C" DLL_EXPORT BOOL APIENTRY DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    switch (fdwReason)
    {
        case DLL_PROCESS_ATTACH:
            // attach to process
            // return FALSE to fail DLL load
            break;

        case DLL_PROCESS_DETACH:
            // detach from process
            break;

        case DLL_THREAD_ATTACH:
            // attach to thread
            break;

        case DLL_THREAD_DETACH:
            // detach from thread
            break;
    }
    return TRUE; // succesful
}
