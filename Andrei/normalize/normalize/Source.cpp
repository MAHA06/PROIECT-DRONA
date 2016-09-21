#include <iostream>
#include <fstream>
#include <string>
using namespace std;

ofstream out("out.txt");
typedef struct point { int x, y; char type; };

int BMap[1000001];
int Map1[1001][1001], Map2[1001][1001], Target[2002][2002];
int BMsize = 0, width, height, width1, height1, width2, height2, heightTarget, widthTarget;
char file[10];
#pragma region interface
void read_matrix1()
{
	ifstream f("Text.txt");
	f >> height1;
	f >> width1;
	for (int i = 0;i < height1;i++)
		for (int j = 0;j < width1;j++)
			f >> Map1[i][j];
}
void printMap1()
{
	//out << height1 << ' ' << width1 << '\n';
	for (int i = 0;i < height1;i++)
	{
		for (int j = 0;j < width1;j++)
		{
			/*if (!Map1[i][j])
			out << "  ";
			else*/
			out << Map1[i][j] << ' ';
			if (Map1[i][j] < 10) out << "  ";
			else if (Map1[i][j] < 100) out << " ";
		}
		out << '\n';
	}
}
#pragma endregion
#pragma region normalize
void normalizeIsolatedPoints(int map)
{
	if (map == 1)
	{
		for (int i = 0;i <= height1;i++)
			for (int j = 0;j <= width1;j++)
				if (Map1[i][j] != Map1[i - 1][j] &&
					Map1[i][j] != Map1[i + 1][j] &&
					Map1[i][j] != Map1[i][j - 1] &&
					Map1[i][j] != Map1[i][j + 1])
					Map1[i][j] = 0;
		if (map == 2)
		{
			for (int i = 0;i <= height2;i++)
				for (int j = 0;j <= width2;j++)
					if (Map2[i][j] != Map2[i - 1][j] &&
						Map2[i][j] != Map2[i + 1][j] &&
						Map2[i][j] != Map2[i][j - 1] &&
						Map2[i][j] != Map2[i][j + 1])
						Map2[i][j] = 0;
		}
	}
}

void normalizeDeadEnds(int map)
{
	if (map == 1)
	{
		for (int i = 0;i <= height1;i++)
			for (int j = 0;j <= width1;j++)
			{
				int c = 0;
				if (Map1[i - 1][j] == Map1[i][j]) c++;
				if (Map1[i + 1][j] == Map1[i][j]) c++;
				if (Map1[i][j - 1] == Map1[i][j]) c++;
				if (Map1[i][j + 1] == Map1[i][j]) c++;
				if (c<2)
					Map1[i][j] = 255;
			}
		if (map == 2)
		{
			for (int i = 0;i <= height2;i++)
				for (int j = 0;j <= width2;j++)
				{
					int c = 0;
					if (Map2[i - 1][j] == Map2[i][j]) c++;
					if (Map2[i + 1][j] == Map2[i][j]) c++;
					if (Map2[i][j - 1] == Map2[i][j]) c++;
					if (Map2[i][j + 1] == Map2[i][j]) c++;
					if (c<2)
						Map2[i][j] = 255;
				}
		}
	}
}

void normalizeRectangles(int map)
{
	int ok = 0;
	if (map == 1)
		while (!ok)
		{
			ok = 1;
			for (int i = 0;i <= height1;i++)
				for (int j = 0;j <= width1;j++)
				{
					if (Map1[i][j] == 0 && Map1[i - 1][j] + Map1[i][j - 1] + Map1[i + 1][j] + Map1[i][j + 1] >= 510)
					{
						Map1[i][j] = 255;
						ok = 0;
					}

					if (Map1[i][j] == 255 && Map1[i - 1][j] + Map1[i][j - 1] + Map1[i + 1][j] + Map1[i][j + 1] < 510)
					{
						Map1[i][j] = 0;
						ok = 0;
					}

					int c50 = 0;
					if (Map1[i - 1][j] == 50) c50++;
					if (Map1[i + 1][j] == 50) c50++;
					if (Map1[i][j - 1] == 50) c50++;
					if (Map1[i][j + 1] == 50) c50++;
					if (Map1[i][j] != 50 && c50 >= 2)
					{
						Map1[i][j] = 50;
						ok = 0;
					}

					int c100 = 0;
					if (Map1[i - 1][j] == 100) c100++;
					if (Map1[i + 1][j] == 100) c100++;
					if (Map1[i][j - 1] == 100) c100++;
					if (Map1[i][j + 1] == 100) c100++;
					if (Map1[i][j] != 100 && c100 >= 2)
					{
						Map1[i][j] = 100;
						ok = 0;
					}

				}
		}
	if (map == 2)
		while (!ok)
		{
			ok = 1;
			for (int i = 0;i <= height2;i++)
				for (int j = 0;j <= width2;j++)
				{
					if (Map2[i][j] == 0 && Map2[i - 1][j] + Map2[i][j - 1] + Map2[i + 1][j] + Map2[i][j + 1] >= 510)
					{
						Map2[i][j] = 255;
						ok = 0;
					}

					if (Map2[i][j] == 255 && Map2[i - 1][j] + Map2[i][j - 1] + Map2[i + 1][j] + Map2[i][j + 1] < 510)
					{
						Map2[i][j] = 0;
						ok = 0;
					}

					int c50 = 0;
					if (Map2[i - 1][j] == 50) c50++;
					if (Map2[i + 1][j] == 50) c50++;
					if (Map2[i][j - 1] == 50) c50++;
					if (Map2[i][j + 1] == 50) c50++;
					if (Map2[i][j] != 50 && c50 >= 2)
					{
						Map2[i][j] = 50;
						ok = 0;
					}

					int c100 = 0;
					if (Map2[i - 1][j] == 100) c100++;
					if (Map2[i + 1][j] == 100) c100++;
					if (Map2[i][j - 1] == 100) c100++;
					if (Map2[i][j + 1] == 100) c100++;
					if (Map2[i][j] != 100 && c100 >= 2)
					{
						Map2[i][j] = 100;
						ok = 0;
					}

				}
		}
}

void normalize()
{
	normalizeIsolatedPoints(1);
	normalizeRectangles(1);
	normalizeDeadEnds(1);
	normalizeRectangles(1);
}
#pragma endregion



int main()
{
	read_matrix1();
	normalize();
	printMap1();
	return 0;
}