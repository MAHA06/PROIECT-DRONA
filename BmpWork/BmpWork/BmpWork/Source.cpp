#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdio>
#include <cmath>
using namespace std;

//
ofstream out1("D:\out1.txt");
ofstream outTarget("D:\outTarget.txt");
typedef struct point { int x, y; char type; };
clock_t t, t1, t2;
int Map1[5001][5001], Map2[7001][7001], Target[10002][10002];
int Lines[7][6001][6001];
int BMsize = 0, width, height, width1, height1, width2, height2, heightTarget, widthTarget;
char file[10];
#pragma region interface
void read_matrix1()
{
	char a[1000] = "D:\imaj";
	strcat(a, file);
	strcat(a, ".txt");
	ifstream f(a);
	f >> height1;
	f >> width1;
	cout << "Reading image " << file << ";\t";
	for (int i = 0; i < height1; i++)
		for (int j = 0; j < width1; j++)
			f >> Map1[i][j];
	cout << "Time elapsed: " << (double)clock() - (double)t1 << '\n';
	t1 = clock();
}
void read_matrix2()
{
	char a[1000] = "D:\imaj";
	strcat(a, file);
	strcat(a, ".txt");
	ifstream f(a);
	f >> height2;
	f >> width2;
	cout << "Reading image " << file << ";\t";
	for (int i = 0; i < height2; i++)
		for (int j = 0; j < width2; j++)
			f >> Map2[i][j];
	cout << "Time elapsed: " << (double)clock() - (double)t1 << '\n';
	t1 = clock();
}
/*
void print_cute()
{
	ifstream in("aia_mare.txt");
	in >> height1;
	in >> width1;
	for (int i = 0;i < height1;i++)
		for (int j = 0;j < width1;j++)
			in >> Map1[i][j];
}*/
void printMap1()
{
	cout << "Printing final map; \t Time elapsed: ";
	FILE *g = fopen("D:\Map.txt", "w");
	fprintf(g, "%d %d\n", height1, width1);
	for (int i = 0; i < height1; i++)
	{
		for (int j = 0; j < width1; j++)
		{
			fprintf(g, "%d ", Map1[i][j]);
			/*if (Map1[i][j] < 10) out << "  ";
			else if (Map1[i][j] < 100) out << " ";*/
		}
		fprintf(g, "\n");
	}
	cout << (double)clock() - (double)t1 << '\n';
}
void printMap2()
{
	for (int i = 0; i < height2; i++)
	{
		for (int j = 0; j < width2; j++)
		{
			if (!Map2[i][j])
				out1 << "  ";
			else
				out1 << Map2[i][j] << ' ';
			if (Map2[i][j] < 10) out1 << "  ";
			else if (Map2[i][j] < 100) out1 << " ";
		}
		out1 << '\n' << '\n' << '\n';
	}
}
//void printTarget()
//{
//	outTarget << heightTarget << ' ' << widthTarget << '\n';
//	for (int i = 0;i < heightTarget;i++)
//	{
//		for (int j = 0;j < widthTarget;j++)
//		{
//			if (Target[i][j] == 2)
//				outTarget << "  ";
//			else
//				outTarget << Target[i][j] << ' ';
//			if (Target[i][j] < 10) outTarget << "  ";
//			else if (Target[i][j] < 100) outTarget << " ";
//		}
//		outTarget << '\n';
//	}
//}
void printLine(int act_line)
{
	ofstream out("D:\out.txt");
	out << Lines[0][act_line][1] << ' ' << Lines[0][act_line][2] << '\n';
	for (int i = 0; i < Lines[0][act_line][1]; i++)
	{
		for (int j = 0; j < Lines[0][act_line][2]; j++)
		{
			out << Lines[act_line][i][j] << ' ';
			if (Lines[act_line][i][j] < 10) out << "  ";
			else if (Lines[act_line][i][j] < 100) out << " ";
		}
		out << '\n' << '\n' << '\n';
	}
}
/*void readBMP_RGB()
{
	ifstream f("input.txt");
	int a;
	f >> width;
	f >> height;
	while (BMsize <= 3 * width*height)
	{

		f >> a;
		BMap[++BMsize] = a;
	}
}
void print_RGB()
{
	ofstream r("red.txt");
	ofstream g("green.txt");
	ofstream b("blue.txt");
	out << width << ' ' << height << '\n';
	for (int i = 0;i < BMsize;i++)
	{

		out << BMap[i] << ' ';
		b << BMap[i] << ' ';
		if (BMap[i] < 10) b << "  ";
		else if (BMap[i] < 100) b << " ";
		g << BMap[++i] << ' ';
		if (BMap[i] < 10) g << "  ";
		else if (BMap[i] < 100) g << " ";
		r << BMap[++i] << ' ';
		if (BMap[i] < 10) r << "  ";
		else if (BMap[i] < 100) r << " ";


		if (i % width == 2)
		{
			r << '\n';
			g << '\n';
			b << '\n';
		}
	}
}*/
#pragma endregion

#pragma region normalize
void normalizeIsolatedPoints(int map)
{
	if (map == 1)
	{
		for (int i = 0; i < height1; i++)
			for (int j = 0; j < width1; j++)
				if (Map1[i][j] != Map1[i - 1][j] &&
					Map1[i][j] != Map1[i + 1][j] &&
					Map1[i][j] != Map1[i][j - 1] &&
					Map1[i][j] != Map1[i][j + 1])
					Map1[i][j] = 0;
		if (map == 2)
		{
			for (int i = 0; i < height2; i++)
				for (int j = 0; j < width2; j++)
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
	int ok = 0;
	if (map == 1)
	{
		while (!ok)
		{
			ok = 1;
			for (int i = 0; i < height1; i++)
				for (int j = 0; j < width1; j++)
				{
					int c = 0;
					if (Map1[i - 1][j] == Map1[i][j]) c++;
					if (Map1[i + 1][j] == Map1[i][j]) c++;
					if (Map1[i][j - 1] == Map1[i][j]) c++;
					if (Map1[i][j + 1] == Map1[i][j]) c++;
					if (c < 2 && Map1[i][j])
					{
						Map1[i][j] = 0;
						i -= 1;
						j -= 1;
						ok = 0;
					}
				}
		}
	}
	if (map == 2)
	{
		while (!ok)
		{
			ok = 1;
			for (int i = 0; i < height2; i++)
				for (int j = 0; j < width2; j++)
				{
					int c = 0;
					if (Map2[i - 1][j] == Map2[i][j]) c++;
					if (Map2[i + 1][j] == Map2[i][j]) c++;
					if (Map2[i][j - 1] == Map2[i][j]) c++;
					if (Map2[i][j + 1] == Map2[i][j]) c++;
					if (c < 2 && Map2[i][j])
					{
						Map2[i][j] = 0;
						i -= 1;
						j -= 1;
						ok = 0;
					}
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
			for (int i = 1; i < height1; i++)
				for (int j = 1; j < width1; j++)
				{
					if (Map1[i][j] == 0 && Map1[i - 1][j] + Map1[i][j - 1] + Map1[i + 1][j] + Map1[i][j + 1] >= 510)
					{
						Map1[i][j] = 255;
						if (i >= 1) i -= 1;
						if (j >= 1)j -= 1;
						ok = 0;
						//cout << i << ' ' << j << '\n';
					}

					else if (Map1[i][j] == 255 && Map1[i - 1][j] + Map1[i][j - 1] + Map1[i + 1][j] + Map1[i][j + 1] < 510)
					{
						Map1[i][j] = 0;
						if (i >= 1) i -= 1;
						if (j >= 1)j -= 1;
						ok = 0;
						//cout << i << ' ' << j << '\n';
					}

					int c50 = 0;
					if (Map1[i - 1][j] == 50) c50++;
					if (Map1[i + 1][j] == 50) c50++;
					if (Map1[i][j - 1] == 50) c50++;
					if (Map1[i][j + 1] == 50) c50++;
					if (Map1[i][j] != 50 && c50 >= 2)
					{
						Map1[i][j] = 50;
						if (i >= 1) i -= 1;
						if (j >= 1)j -= 1;
						//cout << i << ' ' << j << '\n';
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
						if (i >= 1) i -= 1;
						if (j >= 1)j -= 1;
						//cout << i << ' ' << j << '\n';
						ok = 0;
					}

				}
		}
	if (map == 2)
		while (!ok)
		{
			ok = 1;
			for (int i = 0; i < height2; i++)
				for (int j = 0; j < width2; j++)
				{
					if (Map2[i][j] == 0 && Map2[i - 1][j] + Map2[i][j - 1] + Map2[i + 1][j] + Map2[i][j + 1] >= 510)
					{
						Map2[i][j] = 255;
						if (i >= 1) i -= 1;
						if (j >= 1)j -= 1;
						//cout << i << ' ' << j << '\n';
						ok = 0;
					}

					else if (Map2[i][j] == 255 && Map2[i - 1][j] + Map2[i][j - 1] + Map2[i + 1][j] + Map2[i][j + 1] < 510)
					{
						Map2[i][j] = 0;
						if (i >= 1) i -= 1;
						if (j >= 1)j -= 1;
						//cout << i << ' ' << j << '\n';
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
						if (i >= 1) i -= 1;
						if (j >= 1)j -= 1;
						//cout << i << ' ' << j << '\n';
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
						if (i >= 1) i -= 1;
						if (j >= 1)j -= 1;
						//cout << i << ' ' << j << '\n';
						ok = 0;
					}

				}
		}
}

void normalize(int i, int pic)
{
	if (pic)
		cout << "Normalizing image " << pic << "; \t Time elapsed: ";
	else
		cout << "Normalizing final map; \t Time elapsed: ";
	normalizeIsolatedPoints(i);
	normalizeRectangles(i);
	normalizeDeadEnds(i);
	normalizeRectangles(i);
	cout << (double)clock() - (double)t1 << '\n';
	t1 = clock();
}
#pragma endregion

#pragma region utility
/*int minim(int a, int b)
{
	if (a < b) return a;
	return b;
}
int maxim(int a, int b)
{
	if (a > b) return a;
	return b;
}*/
point DetectTopLeft(int pic)
{
	int i, j;
	point P;
	int mini = 100000;
	if (!pic)
	{
		for (i = height2; i <= height1 + height2; i++)
			for (j = width2; j <= width1 + width2; j++)
				if (mini > i + j && (Target[i][j] == 50 || Target[i][j] == 100))
				{
					if (Target[i][j] == 50)
						P.type = 'R';
					if (Target[i][j] == 100)
						P.type = 'B';
					P.x = i;
					P.y = j;
					mini = i + j;
				}
	}
	else
	{
		for (i = 0; i < height2; i++)
			for (j = 0; j < width2; j++)
				if (mini > i + j && (Map2[i][j] == 50 || Map2[i][j] == 100))
				{
					if (Map2[i][j] == 50)
						P.type = 'R';
					if (Map2[i][j] == 100)
						P.type = 'B';
					P.x = i;
					P.y = j;
					mini = i + j;
				}
	}
	return P;
}
point DetectTopRight(int pic)
{
	int i, j;
	point P;
	int maxi = 0;
	if (!pic)
	{
		for (i = height2; i <= height1 + height2; i++)
			for (j = width1 + width2; j >= width2; j--)
				if (i - height2<j - width2 && (j - width2) - (i - height2)>maxi && (Target[i][j] == 50 || Target[i][j] == 100))
				{
					while (Target[i][j] == Target[i][j - 1])
						j--;
					if (Target[i][j] == 50)
						P.type = 'R';
					if (Target[i][j] == 100)
						P.type = 'B';
					P.x = i;
					P.y = j;
					maxi = j - i;
				}
	}
	else
	{
		for (i = 0; i < height2; i++)
			for (j = width2 - 1; j >= 0; j--)
				if (i<j && j - i>maxi && (Map2[i][j] == 50 || Map2[i][j] == 100))
				{
					while (Map2[i][j] == Map2[i][j - 1])
						j--;
					if (Map2[i][j] == 50)
						P.type = 'R';
					if (Map2[i][j] == 100)
						P.type = 'B';
					P.x = i;
					P.y = j;
					maxi = j - i;
				}
	}
	return P;
}
point DetectBottomLeft(int pic)
{
	int i, j;
	point P;
	if (!pic)
	{
		for (i = height1 + height2; i >= height2; i--)
			for (j = width2; j <= width1 + width2; j++)
				if (Target[i][j] != 0 && Target[i][j] != 255)
				{
					while (Target[i][j] == Target[i - 1][j])
						i--;
					if (Target[i][j] == 50)
						P.type = 'R';
					if (Target[i][j] == 100)
						P.type = 'B';
					if (Target[i][j] == 150)
						P.type = 'G';
					if (Target[i][j] == 200)
						P.type = 'C';
					P.x = i;
					P.y = j;
					return P;
				}
	}
	else
	{
		for (i = height2; i >= 1; i--)
			for (j = 1; j <= width2; j++)
				if (Map2[i][j] != 0 && Map2[i][j] != 255)
				{
					while (Map2[i][j] == Map2[i - 1][j])
						i--;
					if (Map2[i][j] == 50)
						P.type = 'R';
					if (Map2[i][j] == 100)
						P.type = 'B';
					if (Map2[i][j] == 150)
						P.type = 'G';
					if (Map2[i][j] == 200)
						P.type = 'C';
					P.x = i;
					P.y = j;
					return P;
				}
	}
}
point DetectBottomRight(int pic)
{
	int i, j;
	point P;
	if (!pic)
	{
		for (i = height1 + height2; i >= height2; i--)
			for (j = width1 + width2; j >= width2; j--)
				if (Target[i][j] != 0 && Target[i][j] != 255)
				{
					while (Target[i][j] == Target[i - 1][j])
						i--;
					while (Target[i][j] == Target[i][j - 1])
						j--;
					if (Target[i][j] == 50)
						P.type = 'R';
					if (Target[i][j] == 100)
						P.type = 'B';
					if (Target[i][j] == 150)
						P.type = 'G';
					if (Target[i][j] == 200)
						P.type = 'C';
					P.x = i;
					P.y = j;
					return P;
				}
	}
	else
	{
		for (i = height2; i >= 1; i--)
			for (j = width2; j >= 1; j--)
				if (Map2[i][j] != 0 && Map2[i][j] != 255)
				{
					while (Map2[i][j] == Map2[i][j - 1])
						j--;
					while (Map2[i][j] == Map2[i - 1][j])
						i--;
					if (Map2[i][j] == 50)
						P.type = 'R';
					if (Map2[i][j] == 100)
						P.type = 'B';
					if (Map2[i][j] == 150)
						P.type = 'G';
					if (Map2[i][j] == 200)
						P.type = 'C';
					P.x = i;
					P.y = j;
					return P;
				}
	}
}
void createLine(int line)
{

	cout << "Creating line " << line << "; \t Time elapsed: ";
	int i, j, i1, j1;
	if (line % 2 == 0)
	{
		for (i = height1 - 1; i >= 0; i--)
			for (j = 0; j < width1; j++)
				Lines[line][j][height1 - i - 1] = Map1[i][j];

		Lines[0][line][1] = width1;
		Lines[0][line][2] = height1;
	}
	else
	{
		for (i = 0; i < height1; i++)
			for (j = width1 - 1; j >= 0; j--)
				Lines[line][width1 - j - 1][i] = Map1[i][j];
		Lines[0][line][1] = width1;
		Lines[0][line][2] = height1;
		//cout << '\n'<<'\n' << '\n'<<height1<<' '<<width1;
	}
	cout << (double)clock() - (double)t1 << '\n';
	t1 = clock();
}
#pragma endregion

#pragma region compute
void create_target()
{
	int i, j;
	heightTarget = 2 * height2 + height1;
	widthTarget = 2 * width2 + width1;
	for (i = 0; i <= heightTarget; i++)
		for (j = 0; j <= widthTarget; j++)
			Target[i][j] = 0;
	for (i = height2; i < height1 + height2; i++)
		for (j = width2; j < width1 + width2; j++)
			Target[i][j] = Map1[i - height2][j - width2];

}
void merge()
{
	int i, i1, j1, j;
	int startx = 0, starty = 0, stopx = 0, stopy = 0;
	create_target();
#pragma region point aquisition
	point Pattern_TopLeft, Pattern_TopRight, Pattern_BottomLeft, Pattern_BottomRight;
	point Sticker_TopLeft, Sticker_TopRight, Sticker_BottomLeft, Sticker_BottomRight;
	Pattern_TopLeft = DetectTopLeft(0);
	//Sticker_TopLeft = DetectTopLeft(1);
	//Pattern_TopRight = DetectTopRight(0);
	Sticker_TopRight = DetectTopRight(1);
	//cout << '\n' << Sticker_TopRight.x << ' ' << Sticker_TopRight.y<<' '<<Sticker_TopRight.type << ' ' << Pattern_TopLeft.x << ' ' << Pattern_TopLeft.y << ' '<<Pattern_TopLeft.type<<'\n';
	//to fix
	/*Pattern_BottomLeft = DetectBottomLeft(0);
	Sticker_BottomLeft = DetectBottomLeft(1);
	Pattern_BottomRight = DetectBottomRight(0);
	Sticker_BottomRight = DetectBottomRight(1);*/
#pragma endregion
#pragma region Horizontal
	/*for (int i = 0;i < heightTarget;i++)
	{
		for (int j = 0;j < widthTarget;j++)
		{
			out << Target[i][j] << ' ';
			if (Target[i][j] < 10) out << "  ";
			else if (Target[i][j] < 100) out << " ";
		}
		out << '\n';
	}*/
	if (Pattern_TopLeft.type == Sticker_TopRight.type)
	{
		for (i = Pattern_TopLeft.x - (height2 - (height2 - Sticker_TopRight.x)), i1 = Sticker_TopRight.x - (height2 - (height2 - Sticker_TopRight.x));
			i <= Pattern_TopLeft.x + (height2 - Sticker_TopRight.x), i1 <= height2;
			i++, i1++)
			for (j = Pattern_TopLeft.y + (width2 - Sticker_TopRight.y), j1 = Sticker_TopRight.y + (width2 - Sticker_TopRight.y);
				j >= Pattern_TopLeft.y - Sticker_TopRight.y, j1 >= 0;
				j--, j1--)
				Target[i][j] = Map2[i1][j1];
	}
	for (i = 1; i < heightTarget; i++)
		for (j = 1; j < widthTarget; j++)
		{
			if (Target[i][j])
			{
				stopx = i;
				if (!startx)
					startx = i;
				if (j > stopy)
					stopy = j;
				if (!starty || starty > j)
					starty = j;
			}
		}
	/*startx = height1;
	stopx = Pattern_TopLeft.x + (height2 - Sticker_TopRight.x);
	starty = Pattern_TopLeft.y - Sticker_TopRight.y;
	stopy = width1 + width2;*/
	for (i = startx; i <= stopx; i++)
		for (j = starty; j <= stopy; j++)
			Map1[i - startx][j - starty] = Target[i][j];
	height1 = stopx - startx;
	width1 = stopy - starty;
#pragma endregion

	cout << (double)clock() - (double)t1 << '\n';
	t1 = clock();

}

#pragma endregion
int main()
{
	int count = 36;

	int c;

	for (int i = 1; i*i <= count; i++) c = i;
	count = c;
	for (c = 1; c <= count; c++)
	{
		int currCol;
		char currColChar[100];
		currCol = count*c;
		strcpy(currColChar, "");
		_itoa(currCol, currColChar, 10);
		strcat(currColChar, "\0");

		strcpy(file, currColChar);
		read_matrix1();
		normalize(1, currCol);

		for (currCol -= 1; currCol > (c - 1)*count; currCol--)
		{
			strcpy(currColChar, "");
			_itoa(currCol, currColChar, 10);
			strcat(currColChar, "\0");

			strcpy(file, currColChar);
			read_matrix2();
			normalize(2, currCol);
			cout << "Merging images; \t Time elapsed: ";
			merge();
			//printMap1();
		}
		createLine(count - c + 1);
	}


	for (int i = 0; i < Lines[0][count][1]; i++)
		for (int j = 0; j < Lines[0][count][2]; j++)
			Map1[i][j] = Lines[count][i][j];
	width1 = Lines[0][count][2];

	height1 = Lines[0][count][1];

	while (count - 1)
	{
		count--;
		for (int i = 0; i < Lines[0][count][1]; i++)
			for (int j = 0; j < Lines[0][count][2]; j++)
				Map2[i][j] = Lines[count][i][j];
		width2 = Lines[0][count][2];
		height2 = Lines[0][count][1];
		cout << height1 << " " << width1 << '\n';
		cout << "Merging line " << count << "; \t Time elapsed: ";
		merge();
	}

	cout << height1 << " " << width1 << '\n';
	normalize(1, 0);

	/*strcpy(file,"32");
	read_matrix1();
	normalize(1, 0);*/
	printMap1();
	//printLine(1);
	cout << "Total time elapsed:" << (double)clock() - (double)t << '\n';
	return 0;
}