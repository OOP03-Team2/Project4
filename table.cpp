#include "table.h"
#include "team.h"
#include <iostream>
#include <iomanip>
#include <sstream> //For std::stringstream to parse csv file

using namespace std;

table::table()
{
}

table::~table()
{
}

void table::addTeam(int index, string line)
{
    stringstream ss(line);
    string pos_str, name, p_str, w_str, d_str, l_str, gf_str, ga_str, gd_str, pts_str, xPts_str;

    // 1. Position
    getline(ss, pos_str, ',');
    int pos = stoi(pos_str);
    // 2. Team name
    getline(ss, name, ',');
    // 3. Matches played
    getline(ss, p_str, ',');
    int p = stoi(p_str);
    // 4. Win
    getline(ss, w_str, ',');
    int w = stoi(w_str);
    // 5. Draw
    getline(ss, d_str, ',');
    int d = stoi(d_str);
    // 6. Lose
    getline(ss, l_str, ',');
    int l = stoi(l_str);
    // 7. Goals for
    getline(ss, gf_str, ',');
    int gf = stoi(gf_str);
    // 8. Goals against
    getline(ss, ga_str, ',');
    int ga = stoi(ga_str);
    // 9. Goal difference
    getline(ss, gd_str, ',');
    // 10. Current points
    getline(ss, pts_str, ',');
    int pts = stoi(pts_str);
    // 11. Expected points
    getline(ss, xPts_str, ',');
    float xPts = stof(xPts_str);

    Team[index].createStats(pos, name, p, w, d, l, gf, ga, pts, xPts);
}

void table::addProb(int index, std::string line)
{
    stringstream ss(line);
    string pos_str, name, xPos_str[teamCount];

    // 1. Position
    getline(ss, pos_str, ',');
    int pos = stoi(pos_str);
    // 2. Team name
    getline(ss, name, ',');

    // 3. Predicted Position
    if (pos == Team[index].getPos())
    {

        for (int i = 0; i < teamCount; i++)
        {
            getline(ss, xPos_str[i], ',');
            float xPos = stof(xPos_str[i]);
            Team[index].createProb(i, xPos);
        }
    }
}

void table::printTable(char option)
{
    cout << "===============================================\n"
         << leagueName << "\n"
         << right << setw(3) << "POS "
         << left << setw(15) << "TEAM";

    if (option == 's') // 's' means simple
        cout << right << setw(3) << "PL" << setw(4) << "GD" << setw(4) << "PTS";

    else if (option == 'v' || option == 'x') // 'v' means verbose, 'x' means expected
    {
        cout << right << setw(3) << "PL" << setw(3) << "W" << setw(3) << "D" << setw(3) << "L"
             << setw(4) << "GF" << setw(3) << "GA" << setw(4) << "GD"
             << setw(5) << "PTS";
        if (option == 'p')
            cout << setw(7) << "xPTS";
    }
    else if (option == 'p') // 'p' means predicted
    {
        cout << setw(5) << "1st"
             << setw(5) << "2nd"
             << setw(5) << "3rd";
        for (int i = 4; i < teamCount; i++)
            cout << setw(5) << i << "th";
    }

    // int count = sizeof(Team) / sizeof(Team[0]); // can be changed to teamCount
    for (int i = 0; i < teamCount; i++)
    {
        cout << "\n";
        Team[i].printStats(option);
    }
    cout << endl;
}
