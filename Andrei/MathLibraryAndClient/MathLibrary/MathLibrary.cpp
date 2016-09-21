#include<fstream>
#include<iostream>
#include<string>
using namespace std;
#ifdef MATHLIBRARY_EXPORTS
#define MATHLIBRARY_API __declspec(dllexport) 
#else
#define MATHLIBRARY_API __declspec(dllimport) 
#endif
namespace MathLibrary
{

	
	extern "C" MATHLIBRARY_API int Add(long map);
	extern "C" MATHLIBRARY_API void Test();
	extern "C" MATHLIBRARY_API void PrintArray(char **map, long n, long m);
	extern "C" MATHLIBRARY_API int **test(int **map);
	//extern "C" MATHLIBRARY_API int Add(int m);
	MATHLIBRARY_API int **test(int **map)
	{
		return map;
	}
	MATHLIBRARY_API void PrintArray(char **map,long n,long m)
	{

		ofstream g("D:/out.txt");
		for (int i = 0;i < n;i++)
		{
			for (int j = 0;j < m;j++)
				g << (int)map[i][j] << ' ';
			g << '\n';
		}
	}
	MATHLIBRARY_API int Add(long map)
	{
		ifstream f("%appdata%/out.txt");
		int val;
		f >> val;
		f.close();
		ofstream g("%appdata%/out.txt");
		g << val + map;
		g.close();
		return 0;

	}
	//////////////////////////////////////////////////////////////////////////////
	//APEL FISIERE APPDATA
	//////////////////////////////////////////////////////////////////////////////
	MATHLIBRARY_API void Test()
	{
		char* appdata = getenv("APPDATA");
		ofstream path("D:/path.txt");
		
		strcat(appdata, "\\out.txt");
		path << appdata;
		ofstream g(appdata);
		for (int i = 1;i <= 100;i++)
			g << i << ' ';
		g.close();

	}
	/*MATHLIBRARY_API int Add(int m)
	{
		return m*m;
	}*/
}