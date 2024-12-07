#include "Team.h"
#include <iostream>
#include <iomanip>

using namespace std;

Team::Team()
{
    // Initalize probability of each position to -1, meaning to end up that position is impossible.
    int count = sizeof(predictedPos) / sizeof(predictedPos[0]);
    for (int i = 0; i < count; i++)
        predictedPos[i] = -1.f;
}

Team::~Team()
{
}

void Team::createStats(int pos, string name, int p, int w, int d, int l, int gf, int ga, int pts, float xPts)
{
    position = pos;

    this->name = name;
    if (p == w + d + l)
        played = p, win = w, draw = d, loss = l;

    this->gf = gf, this->ga = ga, gd = gf - ga;

    points = pts;
    xPoints = xPts;
}
void Team::createProb(int index, float xPos)
{
    predictedPos[index] = xPos;
}

void Team::createStats(int pos, string name, int w, int l, float wP, string gb, string h, string r, string div, string conf, float ppg, float oppg, float dppg, string str, string l10)
{
    position = pos;

    this->name = name;
    win = w, loss = l, played = w + l;

    winPercent = wP;

    this->gb = gb;
    home = h, road = r, this->div = div, this->conf = conf;

    teamPpg = ppg, oppPpg = oppg, difPpg = dppg;

    streak = str, last10 = l10;
}
void Team::createProb(int n, int pos, std::string name, float stat)
{
    position = pos;
    this->name = name;
    predictedStat[n] = stat;
}

void Team::printStats(char option)
{
    /*
     * Football
     * Function to print stats of football team.
     */

    if (points >= 0)
    {
        cout << right << setw(2) << position << "  "
             << left << setw(15) << name;

        // 's' means simple
        if (option == 's')
        {
            cout << right << setw(3) << played
                 << setw(4) << showpos << gd
                 << setw(4) << noshowpos << points;
        }

        // 'v' means verbose, 'x' means expected
        else if (option == 'v' || option == 'x')
        {
            cout << right << setw(3) << played
                 << setw(3) << win << setw(3) << draw << setw(3) << loss
                 << setw(4) << gf << setw(3) << ga;
            cout << setw(4) << showpos << gd
                 << setw(5) << noshowpos << points;
            if (option == 'x')
                cout << right << setw(7) << fixed << setprecision(2) << xPoints;
        }

        // 'p' means predicted
        else if (option == 'p')
        {
            int count = sizeof(predictedPos) / sizeof(predictedPos[0]);
            for (int i = 0; i < count; i++)
            {
                if (predictedPos[i] >= .0f)
                    cout << right << setw(5) << fixed << setprecision(1) << predictedPos[i] << "%";
            }
        }
    }

    /*
     * Basketball
     * Function to print stats of basketball team.
     */

    else if (winPercent >= .0f || predictedStat[0] >= .0f)
    {
        cout << right << setw(2) << position << "  ";

        // 's' means simple
        if (option == 's')
        {
            cout << left << setw(22) << name
                 << right << setw(3) << win
                 << setw(3) << loss
                 << setw(6) << fixed << setprecision(3) << winPercent;
        }
        // 'v' means verbose
        else if (option == 'v')
        {
            cout << left << setw(22) << name
                 << right << setw(3) << played << setw(3) << win << setw(3) << loss
                 << setw(5) << gb
                 << setw(6) << home << setw(6) << road << setw(6) << div << setw(6) << conf
                 << setw(7) << fixed << setprecision(1) << teamPpg
                 << setw(8) << fixed << setprecision(1) << oppPpg;
            cout << setw(9) << fixed << setprecision(1) << showpos << difPpg;
            cout << setw(5) << noshowpos << streak << setw(8) << last10;
        }

        // 'p' means predicted
        else if (option == 'p')
        {
            cout << left << setw(13) << name
                 << right << setw(6) << fixed << setprecision(1) << predictedStat[0]
                 << setw(6) << fixed << setprecision(1) << predictedStat[1]
                 << setw(7) << fixed << setprecision(1) << predictedStat[2]
                 << setw(7) << fixed << setprecision(1) << predictedStat[3];
            cout << setw(7) << fixed << setprecision(1) << showpos << predictedStat[4];

            // Probability about PlayOffs
            cout << setw(8) << fixed << setprecision(1) << noshowpos << predictedStat[5] << "%"
                 << setw(9) << fixed << setprecision(1) << predictedStat[6] << "%"
                 << setw(8) << fixed << setprecision(1) << predictedStat[7] << "%"
                 << setw(10) << fixed << setprecision(1) << predictedStat[8] << "%"
                 << setw(8) << fixed << setprecision(1) << predictedStat[9] << "%";
        }
    }
}