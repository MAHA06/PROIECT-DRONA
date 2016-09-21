#include<fstream>
#include<iostream>
#include<queue>
using namespace std;
int x[10000][10000], n, m, moves[10000][10000], viz[10000][10000], QueueElements, MoveList[10000];
bool Done;
struct position { int sx, sy, dx, dy, Direction; };
position StartPosition, StopPosition;

queue<position> Queue;

void Compute()
{
	position ActualPosition;
	do
	{
		ActualPosition = Queue.front();
		Queue.pop();
		//UP///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (ActualPosition.sx != 1 && ActualPosition.Direction != 3)//if not on the edge and not heading the opposite direction
		{
			bool GoodMove = true;
			for (int i = ActualPosition.sy;i <= ActualPosition.dy;i++)
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
				if (viz[NextPosition.sx][NextPosition.sy] > viz[ActualPosition.sx][ActualPosition.sy] + 1+ (int)WithTurn)
				{
					viz[NextPosition.sx][NextPosition.sy] = viz[ActualPosition.sx][ActualPosition.sy] + 1 + (int)WithTurn;
					moves[NextPosition.sx][NextPosition.sy] = 1;
					Queue.push(NextPosition);
				}

			}
		}
		//RIGHT////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (ActualPosition.dy != m && ActualPosition.Direction != 4)//if not on the edge and not heading the opposite direction
		{
			bool GoodMove = true;
			for (int i = ActualPosition.sx;i <= ActualPosition.dx;i++)
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
		//DOWN/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (ActualPosition.dx != n && ActualPosition.Direction != 1)//if not on the edge and not heading the opposite direction
		{
			bool GoodMove = true;
			for (int i = ActualPosition.sy;i <= ActualPosition.dy;i++)
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
		//LEFT/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if (ActualPosition.sy != 1 && ActualPosition.Direction != 2)//if not on the edge and not heading the opposite direction
		{
			bool GoodMove = true;
			for (int i = ActualPosition.sx;i <= ActualPosition.dx;i++)
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
	}while (!Queue.empty());
}
void FindStart()
{
	int i, j;
	for (i = 1;i <= n;i++)
		for (j = 1;j <= m;j++)
			viz[i][j] = 10000;

	for (i = 1;i <= n;i++)
		for (j = 1;j <= m;j++)
			if (x[i][j] == 2)
			{
				if (StartPosition.sx == 0 && StartPosition.sy == 0)
				{
					StartPosition.sx = i;
					StartPosition.sy = j;
				}
				else
				{
					StartPosition.dx = i;
					StartPosition.dy = j;
				}
			}
	StartPosition.Direction = 1;
	//One pixel for car
	if (StartPosition.dx == 0 && StartPosition.dy == 0)
		StartPosition.dx = StartPosition.sx, StartPosition.dy = StartPosition.sy;
	Queue.push(StartPosition);
	//call function
	viz[StartPosition.sx][StartPosition.sy] = 0;
	Compute();
}
void FindStop()
{
	int i, j;
	for (i = 1;i <= n;i++)
		for (j = 1;j <= m;j++)
			if (x[i][j] == 3)
			{
				if (StopPosition.sx == 0 && StopPosition.sy == 0)
				{
					StopPosition.sx = i;
					StopPosition.sy = j;
				}
				else
				{
					StopPosition.dx = i;
					StopPosition.dy = j;
				}
			}
	//One pixel for stop
	if (StopPosition.dx == 0 && StopPosition.dy == 0)
		StopPosition.dx = StopPosition.sx, StopPosition.dy = StopPosition.sy;
}

char appdata1[100];
char appdata2[100];
int main()
{
	/*for (int i = 0; i < 100;i++)
	{
		appdata1[i] = '\0';
		appdata2[i] = '\0';
	}
	char* appdata = getenv("APPDATA");
	for (int i = 0; i < strlen(appdata); i++)
	{
		appdata1[i] = appdata[i];
		appdata2[i] = appdata[i];
	}
	strcat(appdata1, "\\directions.txt");
	strcat(appdata2, "\\matrix.txt");
	ofstream g(appdata1);*/
	ifstream in("Text.txt");
	ofstream out("Directions.txt");
	/*ifstream f(appdata2);
	cout << appdata1 << '\n';
	cout << appdata2;
	cin >> n;*/
	in >> n >> m;
	for (int i = 1;i <= n;i++)
		for (int j = 1;j <= m;j++)
			in >> x[i][j];
	FindStart();
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
	FindStop();
	int minx,miny,mx,my;
	minx = StopPosition.sx;
	miny = StopPosition.sy;
	for (int i = StopPosition.sx;i <= StopPosition.dx;i++)
		for (int j = StopPosition.sy;j <= StopPosition.dy;j++)
			if (viz[i][j] < viz[minx][miny])
				minx = i, miny = j;
	moves[StartPosition.sx][StartPosition.sy] = 1;
	mx = minx;
	my = miny;
	int MoveCount = 0;
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
			if ((moves[minx][miny] == 1 && moves[mx][my] == 2) ||
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
	/*for (i = MoveCount;i > 0;i--)
		g << MoveList[i] << ' ';
	g << '\n';*/
	i = MoveCount;
	while (i > 0)
	{
		if (MoveList[i] == 5)  out << "Turn right";
		else if (MoveList[i] == 6) out << "Turn left";
		else
		{
			int a, c = 0;
			a = MoveList[i];
			while (i >1 && MoveList[i - 1] == a)
			{
				c++;
				i--;
			}
			out << "Do " << c << " steps";
		}
		out<< "   ->   ";
		i--;
	}
	return 0;
}
