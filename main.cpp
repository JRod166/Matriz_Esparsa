#include <iostream>
#include "MatrizEsparsa.h"
#include <cstdlib>
#include <ctime>
#include <iomanip>

using namespace std;

int main()
{
    MatrizEsparsa<int> m;
    m(0,0) = 20;
    m(2000,2000) = 50;
    m(0,10) = 10;
    m(2001,2000) = 2000;
    cout << m(0,0) << " " << m(2000,2000) << endl;
    cout << m(0,10) << " " << m(2001,2000) << endl << endl;

    m.reset();
    cout << m(0,0) << " " << m(2000,2000) << endl;
    cout << m(0,10) << " " << m(2001,2000) << endl << endl;

    return 0;
}
