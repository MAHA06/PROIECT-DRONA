#include "main.h"
#include <fstream>
using namespace std;

// a sample exported function
int DLL_EXPORT passInstruction()
{
    ifstream in("D:\\Directions.txt");
    int dir, i, j, directionsArr[400];
    i=-1;
    in>>dir;
    while(in>>directionsArr[++i]);
    in.close();
    ofstream out("D:\\Directions.txt");
    for (j=0; j<i; j++)
        out<<directionsArr[j]<<'\n';
    return dir;

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
