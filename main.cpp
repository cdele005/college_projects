#include <iostream>
#include <iomanip>
#include "vec.h"

using namespace std;

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <math.h>

void Dump_png(unsigned int* data,int width,int height,const char* filename);

/*
  Problems 1-4

  Rewrite each loop so that only addition and subtraction occur inside any loop.
  This includes operations performed on the vec3 vectors.  Ignore the operations
  that occur while printing the results.

  Each problem is worth 10 points.  Note that for Problem 4, you must clear the
  multiplications and divisions from both loops.  If you are able to clear the
  multiplications and divisions from only the inner loop, you will still get 5
  points.
*/

void Problem_1(int n, float x, float y)
{
    /*
    for(int i = -n ; i <= n ; i++)
    {
        float z = i * x + y;
        cout << z << endl;
    }
    */

    float z = -n * x + y;
    for (int i = 0; i <= 2*n; i++)
    {
        cout << z << endl;
        z = z + x;
    }
}

void Problem_2(int n, float x, float dx)
{
    /*
    for(int i = 0 ; i < n ; i++)
    {
        float y = x + dx * i;
        float z = y * y;
        cout << z << endl;
    }
    */

    float n0 = x * x;
    float n1 = (x*x) + (2 * x * dx) + (dx * dx);
    float a = 2 * dx * dx;
    float z = 0;

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
        cout << n0 << endl;

        else if (i == 1)
        cout << n1 << endl;

        else 
        {
           z = n1 + n1 - n0 + a;
           cout << z << endl;
           n0 = n1;
           n1 = z;
        }
    }
}

void Problem_3(int n, vec3 u, vec3 v, vec3 du)
{
    /*
    for(int i = 0 ; i < n ; i++)
    {
        vec3 w = u + du * i;
        float z = dot(w,v)/dot(v,v);
        cout << z << endl;
    }
    */

    float denom = dot(v,v);
    float n0 = dot(u,v) / denom;
    float a = dot(v,du) / denom;

    for (int i = 0; i < n; i++)
    {
        if (i == 0)
            cout << n0 << endl;
        
        else
        {
            float z = n0 + a;
            cout << z << endl;
            n0 = z;
        }
    }
}

void Problem_4(int n, vec3 w, vec3 u, vec3 v)
{
    /*
    for(int i = 0 ; i <= n ; i++)
    {
        for(int j = 0 ; i + j <= n ; j++)
        {
            float a = (float)i/n;
            float b = (float)j/n;
            float c = 1 - a - b;
            vec3 z = a * w + b * u + c * v;
            cout << z << endl;
        }
    }
    */

    vec3 n00 = v;
    vec3 wn = w / (float)n;
    vec3 un = u / (float)n;
    vec3 vn = v / (float)n;
    vec3 x = n00 + un - vn;

    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; i + j <= n; j++)
        {
            if (j == 0)
                n00 = x;

            if (i == 0 && j == 0)
            {
                cout << v << endl;
                n00 = v;
            }

            else 
            {
                cout << x << endl;

                if (i + j < n)
                x = x + un - vn;
            }
        }
        x = n00 + wn - vn;
    }
}

/*
  Problem 5

  Draw a white circle centered at (x,y) with radius r.
  For example, data[y][x]=0xffffffff; would set the center of the circle to white.
  The circle should not have gaps.
  You may assume that the circle does not cross the edges of the circle.

  20 points.

  Extra credit options:
  A = you don't use any floating point.
  B = you do not use * or / in any loop, including in the loop condition.
  C = you fill the circle red (0xff0000ff) while keeping the outline white.

  A = 2% extra credit
  A + B = 5% extra credit
  A + B + C = 10% extra credit
*/
void draw_circle(int x, int y, int r)
{
    unsigned int data[512][512];
    for(int i = 0 ; i < 512; i++)
        for(int j = 0 ; j < 512; j++)
            data[i][j] = 0xff000000; // set all pixels to (0,0,0,1) = black.

    // TODO: your code here

    Dump_png(&data[0][0],512,512,"circle.png");
}

int main()
{
    cout << std::setprecision(4);

    cout << "== Problem 1 ==" << endl;
    
    Problem_1(5, -0.123, 2.114);
    
    cout << "== Problem 2 ==" << endl;

    Problem_2(5, -0.123, 2.114);
    
    cout << "== Problem 3 ==" << endl;

    Problem_3(5, vec3(.1,.2,.3), vec3(0.9,0.2,0.8), vec3(0.0,0.1,0.6));

    cout << "== Problem 4 ==" << endl;
 
    Problem_4(5, vec3(.1,.2,.3), vec3(0.9,0.2,0.8), vec3(0.0,0.1,0.6));

    cout << "== Problem 5 ==" << endl;

    return 0;
}

