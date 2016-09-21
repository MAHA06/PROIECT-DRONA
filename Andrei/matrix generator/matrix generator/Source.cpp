#include<fstream>
using namespace std;

ofstream g1("Matrix1.txt");
ofstream g2("Matrix2.txt");
ofstream g3("Matrix3.txt");
ofstream g4("Matrix4.txt");
ofstream g5("Matrix5.txt");
ofstream g6("Matrix6.txt");
ofstream g7("Matrix7.txt");
ofstream g8("Matrix8.txt");
ofstream g9("Matrix9.txt");
int n = 1000, m = 1000, i, j,x[10000][10000];
int main()
{
	for (i = 1;i <= n;i++)
		for (j = 1;j <= m;j++)
			x[i][j] = 255;
	for (i = 100;i <= 300;i++)
		for (j = 100;j <= 300;j++)
			x[i][j] = 0;

	for (i = 200;i <= 400;i++)
		for (j = 700;j <= 900;j++)
			x[i][j] = 0;

	for (i = 500;i <= 800;i++)
		for (j = 300;j <= 600;j++)
			x[i][j] = 0;


	for (i = 20;i <= 120;i++)
		for (j = 600;j <= 800;j++)
			x[i][j] = 0;

	for (i = 100;i <= 300;i++)
		for (j = 100;j <= 300;j++)
			x[i][j] = 0;

	for (i = 1;i <= n/100;i++)
		for (j = 1;j <= m/100;j++)
		{
			if (i % 2 == j % 2)
				x[i * 100][j * 100] = 100;
			else
				x[i * 100][j * 100] = 170;
			x[i * 100-1][j * 100-1] = x[i * 100-1][j * 100] = x[i * 100-1][j * 100+1] = x[i * 100][j * 100+1] = x[i * 100+1][j * 100+1] = x[i * 100+1][j * 100] = x[i * 100+1][j * 100-1] = x[i * 100][j * 100-1] = x[i * 100][j * 100];
		}
	/*for (i = 1;i <= 3;i++)
		for (j = 1;j <= 3;j++)
			x[i][j] = 2;


	for (i = 98;i <= 100;i++)
		for (j = 98;j <= 100;j++)
			x[i][j] = 3;
			*/
	for (i = 1;i <= 400;i++)
	{
		for (j = 1;j <= 400;j++)
			g1 << x[i][j]<<' ';
		g1 << '\n';
	}
	for (i = 1;i <= 400;i++)
	{
		for (j = 300;j <= 700;j++)
			g2 << x[i][j] << ' ';
		g2 << '\n';
	}
	for (i = 1;i <= 400;i++)
	{
		for (j = 600;j <= 1000;j++)
			g3 << x[i][j] << ' ';
		g3 << '\n';
	}
	for (i = 300;i <= 700;i++)
	{
		for (j = 600;j <= 1000;j++)
			g4<< x[i][j] << ' ';
		g4 << '\n';
	}
	for (i = 300;i <= 700;i++)
	{
		for (j = 300;j <= 700;j++)
			g5 << x[i][j] << ' ';
		g5 << '\n';
	}
	for (i = 300;i <= 700;i++)
	{
		for (j = 1;j <= 400;j++)
			g6 << x[i][j] << ' ';
		g6 << '\n';
	}
	for (i = 600;i <= 1000;i++)
	{
		for (j = 1;j <= 400;j++)
			g7 << x[i][j] << ' ';
		g7 << '\n';
	}
	for (i = 600;i <= 1000;i++)
	{
		for (j = 300;j <= 1000;j++)
			g8 << x[i][j] << ' ';
		g8 << '\n';
	}
	for (i = 600;i <= 1000;i++)
	{
		for (j = 600;j <= 1000;j++)
			g9 << x[i][j] << ' ';
		g9 << '\n';
	}
	return 0;
}