#include "Team.h"
#include <iostream>
#include <iomanip>

using namespace std;

Team::Team()
{
    int count = sizeof(predictedStat) / sizeof(predictedStat[0]);
    for (int i = 0; i < count; i++)
        predictedStat[i] = -1.f;
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
    home = h, road = r, division = div, conference = conf;

    teamPpg = ppg, oppPpg = oppg, difPpg = dppg;

    streak = str, last10 = l10;
}
void Team::createProb(int n, int pos, string name, float stat)
{
    position = pos;
    this->name = name;
    predictedStat[n] = stat;
}

void Team::createStats(int pos, string name, int w, int l, int t, float wP, int gf, int ga, string h, string r, string div, string conf, string str, string l5)
{
    position = pos;
    this->name = name;

    win = w, loss = l, draw = t;
    played = w + l + t;

    winPercent = wP;

    this->gf = gf, this->ga = ga, gd = gf - ga;

    home = h, road = r, division = div, conference = conf;
    streak = str, last5 = l5;
}
void Team::createProb(int pos, string name, float stat, int n)
{
    position = pos;
    this->name = name;
    pStat[n] = stat;
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
             << left << setw(17) << name;

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
                if (predictedPos[0] < .0f)
                    cout << right << setw(8) << fixed << setprecision(1) << xPoints;
                else
                    cout << right << setw(8) << fixed << setprecision(2) << xPoints;
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

    else if (teamPpg >= 1.f || predictedStat[0] >= .0f)
    {
        cout << right << setw(2) << position << "  ";

        // 's' means simple
        if (option == 's')
        {
            cout << left << setw(22) << name
                 << right << setw(3) << win
                 << setw(3) << loss
                 << setw(7) << fixed << setprecision(3) << winPercent;
        }
        // 'v' means verbose
        else if (option == 'v')
        {
            cout << left << setw(22) << name
                 << right << setw(3) << played << setw(3) << win << setw(3) << loss
                 << setw(5) << gb
                 << setw(6) << home << setw(6) << road << setw(6) << division << setw(6) << conference
                 << setw(7) << fixed << setprecision(1) << teamPpg
                 << setw(8) << fixed << setprecision(1) << oppPpg;
            cout << setw(9) << fixed << setprecision(1) << showpos << difPpg;
            cout << setw(6) << noshowpos << streak << setw(8) << last10;
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
            cout << setw(9) << fixed << setprecision(1) << noshowpos << predictedStat[5] << "%"
                 << setw(9) << fixed << setprecision(1) << predictedStat[6] << "%"
                 << setw(8) << fixed << setprecision(1) << predictedStat[7] << "%"
                 << setw(10) << fixed << setprecision(1) << predictedStat[8] << "%"
                 << setw(8) << fixed << setprecision(1) << predictedStat[9] << "%";
        }
    }

    /*
     * American Football
     * Function to print stats of A. football team.
     */

    else
    {
        cout << right << setw(2) << position << "  ";

        // 's' means simple
        if (option == 's')
        {
            cout << left << setw(11) << name
                 << right << setw(3) << win
                 << setw(3) << loss
                 << setw(7) << fixed << setprecision(3) << winPercent;
        }
        // 'v' means verbose
        else if (option == 'v')
        {
            cout << left << setw(11) << name
                 << right << setw(3) << played << setw(3) << win << setw(3) << loss << setw(7) << fixed << setprecision(3) << winPercent
                 << setw(4) << gf << setw(4) << ga << setw(6) << showpos << gd;
            cout << noshowpos << setw(8) << home << setw(7) << road << setw(7) << division << setw(7) << conference
                 << setw(5) << streak << setw(8) << last5;
        }

        // 'p' means predicted
        else if (option == 'p')
        {
            cout << left << setw(11) << name
                 << right << setw(6) << fixed << setprecision(1) << pStat[0]
                 << setw(6) << fixed << setprecision(1) << pStat[1];

            // Probability about PlayOffs
            cout << setw(8) << fixed << setprecision(1) << pStat[2] << "%"
                 << setw(9) << fixed << setprecision(1) << noshowpos << pStat[3] << "%"
                 << setw(8) << fixed << setprecision(1) << pStat[4] << "%"
                 << setw(11) << fixed << setprecision(1) << pStat[5] << "%"
                 << setw(6) << fixed << setprecision(1) << pStat[6] << "%";
        }
    }
}
