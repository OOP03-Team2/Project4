#include "team.h"
#include <iostream>
#include <iomanip>

using namespace std;

team::team()
{
}

team::~team()
{
}

void team::createStats(int pos, string name, int p, int w, int d, int l, int gf, int ga, int pts, float xPts)
{
    position = pos;

    this->name = name;
    if (p == w + d + l)
        played = p, win = w, draw = d, lose = l;
    this->gf = gf, this->ga = ga, gd = gf - ga;
    points = pts;
    xPoints = xPts;
}

void team::createProb(int index, float xPos)
{
    xPosition[index] = xPos;
}

void team::printStats(char option)
{
    cout << right << setw(2) << position << "  "
         << left << setw(15) << name;

    if (option == 's') // 's' means simple
    {
        cout << right << setw(3) << played
             << setw(4) << showpos << gd
             << setw(4) << noshowpos << points;
    }

    else if (option == 'v' || option == 'x') // 'v' means verbose, 'x' means expected
    {
        cout << right << setw(3) << played
             << setw(3) << win << setw(3) << draw << setw(3) << lose
             << setw(4) << gf << setw(3) << ga;
        cout << setw(4) << showpos << gd
             << setw(5) << noshowpos << points;
        if (option == 'p')
            cout << setw(6) << fixed << setprecision(2) << xPoints;
    }

    else if (option == 'p')
    {
        int count = sizeof(xPosition) / sizeof(xPosition[0]);
        for (int i = 0; i < count; i++)
        {
            if (xPosition[i] >= .0f)
                cout << right << setw(5) << fixed << setprecision(1) << xPosition[i] << "%";
        }
    }
}
