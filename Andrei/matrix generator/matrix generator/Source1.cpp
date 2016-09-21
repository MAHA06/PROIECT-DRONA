#include<fstream>
#include<iostream>
#include<string>
using namespace std;

int n = 100, m = 100, i, j, x[100][100];
char a[100];
int main()
{

	char* appdata1 = getenv("AppData");


	for (i = 0; i < strlen(appdata1); i++)
	{
		a[i] = appdata1[i];
	}
	strcat(a, "\\matrix1.txt");
	
	ofstream g(a);
#pragma region stuff
	for (i = 1;i <= n;i++)
		for (j = 1;j <= m;j++)
			x[i][j] = 0;
#pragma region obstecole
	for (i = 10;i <= 80;i++)
		for (j = 10;j <= 70;j++)
			x[i][j] = 255;

	for (i = 30;i <= 40;i++)
		for (j = 30;j <= 50;j++)
			x[i][j] = 50;

#pragma endregion

	//start
	/*for (i = 46;i <= 50;i++)
		for (j = 1;j <= 5;j++)
			x[i][j] = 2;

	//stop
	for (i = 1;i <= 10;i++)
		for (j = 41;j <= 50;j++)
			x[i][j] = 3;*/

	
#pragma endregion
	g << n << ' ' << m << '\n';
	for (i = 1;i <= n;i++)
	{
		for (j = 1;j <= m;j++)
			g << x[i][j] << ' ';
		g << '\n';
	}
	g.close();

	return 0;
}