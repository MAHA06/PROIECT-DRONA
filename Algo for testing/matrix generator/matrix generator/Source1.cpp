#include<fstream>
#include<iostream>
#include<string>
using namespace std;
int n = 100, m = 100, i, j, x[100][100];
char a[100];
void printnice()
{
	ofstream g("D:\\Text1.txt");
	g << n << ' ' << m << '\n';
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= m; j++)
			if (x[i][j] == 0)
				g << ' ';
			else
				g << x[i][j];
		g << '\n';
	}
	g.close();
}
int main()
{

	char* appdata1 = getenv("AppData");


	for (i = 0; i < strlen(appdata1); i++)
	{
		a[i] = appdata1[i];
	}
	strcat(a, "\\matrix2.txt");
	
	ofstream g(a);
#pragma region stuff
	for (i = 1;i <= n;i++)
		for (j = 1;j <= m;j++)
			x[i][j] = 0;
#pragma region obstecole
	for (i = 1;i <= 90;i++)
		for (j = 1;j <= 19;j++)
			x[i][j] = 1;

	for (i = 1;i <= 49;i++)
		for (j = 29;j <= 39;j++)
			x[i][j] = 1;

	for (i = 60; i <= 90; i++)
		for (j = 30; j <= 39; j++)
			x[i][j] = 1;

	for (i = 25; i <= 100; i++)
		for (j = 50; j <= 75; j++)
			x[i][j] = 1;


#pragma endregion

	//start
	for (i = 91;i <= 100;i++)
		for (j = 1;j <= 10;j++)
			x[i][j] = 2;

	//stop
	for (i = 10;i <= 21;i++)
		for (j = 40;j <= 49;j++)
			x[i][j] = 3;

	
#pragma endregion
	printnice();
	g << n << ' ' << m << '\n';
	for (i = 1;i <= n;i++)
	{
		for (j = 1;j <= m;j++)
			g << x[i][j]<< ' ';
		g << '\n';
	}
	g.close();

	return 0;
}