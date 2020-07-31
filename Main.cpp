/// Progrann works with random num of  angles and coordinates of pts /// 
/// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// /// 
#include "math.h"
#include "windows.h"
#include "stdio.h"
#include <windows.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>


using namespace std;
struct fPoint // Structure for creating pts (x - Abscissa, y ordinate) 
{
    float x, y;
    fPoint() {}
    fPoint(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
};


static void DrawFigure(HDC hdc, fPoint* array, int len) // That function recieve Win32 parameters and size of figure  for draw that one 
{
    MoveToEx(hdc, array->x, array->y, 0); // Position 
    while (len--) LineTo(hdc, array[len].x, array[len].y); //  Cycle is adds a line to the current subpath with an ending point
}

static bool IsIntersect(fPoint* array_1, int len_1, fPoint* array_2, int len_2) // Algo of intersect checking
{
#define vect(a,b,c) (((a).x-(b).x)*((a).y-(c).y)-((a).y-(b).y)*((a).x-(c).x)) 
    /* all vectors lie on the X-Y plane, their cross result (which must be perpendicular to the vectors being multiplied). */
    int i, j, next_i, next_j;
    for (int i = 0; i < len_1; i++)
    {
        next_i = i == len_1 - 1 ? 0 : i + 1;
        for (j = 0; j < len_2; j++)
        {
            next_j = j == len_2 - 1 ? 0 : j + 1;                                                                                    //////////////////////////////////////////////////////////////////////////////////////////////////////
            if (vect(array_1[next_i], array_1[i], array_2[j]) * vect(array_1[next_i], array_1[i], array_2[next_j]) < 0 &&            // Calculate the equation of the planes. Tihs are looking for the intersection line of these planes.//
                vect(array_2[next_j], array_2[j], array_1[i]) * vect(array_2[next_j], array_2[j], array_1[next_i]) < 0)                 //////////////////////////////////////////////////////////////////////////////////////////////////////
                return true;

        }
    }
    bool a = vect(array_2[0], array_2[len_2 - 1], array_1[0]) < 0;
    for (j = 1; j < len_2; j++)
        if (a != vect(array_2[j], array_2[j - 1], array_1[0]) < 0) break;               ///////////////////////////////////////////////////////////////////////////////////////
    if (j == len_2) return true;                                                    // Then compare if the segments intersect, the figures is intersectand or conversely.//
                                                                                    ///////////////////////////////////////////////////////////////////////////////////////

    a = vect(array_1[0], array_1[len_1 - 1], array_2[0]) < 0;
    for (i = 1; i < len_1; i++)
        if (a != vect(array_1[i], array_1[i - 1], array_2[0]) < 0) break;
    return i == len_1;
}

class Figure
{
public:

    int lenght = rand() % 5 + 3; //Generator num of pts

    fPoint* points;

    Figure()
    {
        points[lenght];
    }
    ~Figure() {


    }
    void GetFigure(HDC hdc) //DrawFigure
    {
        DrawFigure(hdc, points, lenght);
    }
};





int main(int argc, char* argv[])
{
    char ch;
    std::srand(std::time(nullptr));
    do {

        Figure fig1; // Figure 1
        fig1.points = new fPoint[fig1.lenght]; // New array of pts 
        for (int i = 0; i < fig1.lenght; i++)
        {
            fig1.points[i] = fPoint(150 + rand() % 200, 100 + rand() % 300); //randomizer of coordinates
        };
        Figure fig2; // Figure 2
        fig2.points = new fPoint[fig2.lenght];
        for (int i = 0; i < fig2.lenght; i++)
        {
            fig2.points[i] = fPoint(100 + rand() % 150, 100 + rand() % 200); //randomizer of coordinates
        };
        HWND hwnd = GetForegroundWindow(); //GetDesktopWindow();
        HDC hdc = GetWindowDC(hwnd);
        HPEN hPen = CreatePen(3, 2, RGB(0, 255, 255)); // Pen
        HPEN hPen1 = CreatePen(3, 2, RGB(255, 0, 0));

        SelectObject(hdc, hPen); //Win32 api calling for select window and used pen 
        cout << "Press any key for draw Figure 1 (Random generation of pts): " << endl;
        _getch();

        fig1.GetFigure(hdc);
        cout << "Press any key for draw Figure 2 (Random generation of pts): " << endl;
        _getch();

        SelectObject(hdc, hPen1); //Win32 api calling for select window and used pen 
        fig2.GetFigure(hdc);
        ReleaseDC(hwnd, hdc); // Stop thread of drawing
        printf(IsIntersect(fig1.points, fig1.lenght, fig2.points, fig1.lenght) ? "Intersected" : "Not intersected");

        _getch();
        system("cls");
        fig1.points = nullptr; // Null ptr of array in object (it's nessesary before destructor calls) 
        fig2.points = nullptr;
        fig1.~Figure(); // Destr
        fig2.~Figure();
        std::cout << "******Enter any symphol for continue or 'q' for exit and press: ";
        ch = getchar();
        system("cls");
    } while (ch != 'q');


    return 0;
}

