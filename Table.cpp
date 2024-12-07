#include "Table.h"
#include "Team.h"
#include <iostream>
#include <iomanip>
#include <sstream> // For std::stringstream to parse csv file
#include <vector>  // For std::vector<std::string>

using namespace std;

Table::Table()
{
}

Table::~Table()
{
}

void Table::addFootTeam(int index, string line)
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
    // 11. Expected points or Odds
    getline(ss, xPts_str, ',');
    float xPts = stof(xPts_str);
    if (xPts < 10)
        xPts += 1;

    team[index].createStats(pos, name, p, w, d, l, gf, ga, pts, xPts);
}
void Table::addBasketTeam(int index, std::string line)
{
    stringstream ss(line);
    string pos_str, name, w_str, l_str, wp_str, gb, home, road, div, conf, ppg_str, oppg_str, dppg_str, str, l10;

    // 1. Position
    getline(ss, pos_str, ',');
    int pos = stoi(pos_str);
    // 2. Team name
    getline(ss, name, ',');
    // 3. Wins
    getline(ss, w_str, ',');
    int w = stoi(w_str);
    // 4. Loss
    getline(ss, l_str, ',');
    int l = stoi(l_str);
    // 5. Win Percentage
    getline(ss, wp_str, ',');
    float wp = stof(wp_str);
    // 6. Games behind
    getline(ss, gb, ',');
    // 7. results at Home
    getline(ss, home, ',');
    // 8. results on road
    getline(ss, road, ',');
    // 9. results from its divison
    getline(ss, div, ',');
    // 10. results from its conference
    getline(ss, conf, ',');
    // 11. PPG
    getline(ss, ppg_str, ',');
    float ppg = stof(ppg_str);
    // 12. opponent PPG
    getline(ss, oppg_str, ',');
    float oppg = stof(oppg_str);
    // 13. PPG difference
    getline(ss, dppg_str, ',');
    float dppg = stof(dppg_str);
    // 14. results from its conference
    getline(ss, str, ',');
    // 15. PPG
    getline(ss, l10, ',');

    team[index].createStats(pos, name, w, l, wp, gb, home, road, div, conf, ppg, oppg, dppg, str, l10);
}

void Table::addProb(int index, string line)
{
    stringstream ss(line);
    string pos_str, name;
    vector<string> xPos_str(teamCount); // Modified from array to vector: since MSVC cannot handle VLA

    // 1. Position
    getline(ss, pos_str, ',');
    int pos = stoi(pos_str);

    // 2. Team name
    getline(ss, name, ',');

    // 3. Predicted Position
    if (pos == team[index].getPos())
    {
        for (int i = 0; i < teamCount; i++)
        {
            getline(ss, xPos_str[i], ',');
            float xPos = stof(xPos_str[i]);
            team[index].createProb(i, xPos);
        }
    }
}
void Table::addProb(string line, int index)
{
    stringstream ss(line);
    string pos_str, name, stat_str[10];

    // 1. Position
    getline(ss, pos_str, ',');
    int pos = stoi(pos_str);

    // 2. Team name
    getline(ss, name, ',');

    // 3. Predicted stats
    int count = sizeof(stat_str) / sizeof(stat_str[0]);
    for (int n = 0; n < count; n++)
    {
        getline(ss, stat_str[n], ',');
        float stat = stof(stat_str[n]);
        team[index].createProb(n, pos, name, stat);
    }
}

void Table::printTable(char option)
{
    cout << "=======================================================\n"
         << leagueName << "\n"
         << "-------------------------------------------------------\n";

    /*
     * Football
     * Function to print table of football team.
     * teamCount == 20 -> Premier League, Serie A and La Liga
     * teamCount == 18 -> Bundesliga and Ligue 1
     * teamCount == 36 -> Uefa Champions League
     */

    if (teamCount == 20 || teamCount == 18 || teamCount == 36)
    {
        cout << right << setw(3) << "POS "
             << left << setw(17) << "TEAM";

        // 's' means simple
        if (option == 's')
            cout << right << setw(3) << "PL" << setw(4) << "GD" << setw(4) << "PTS";

        // 'v' means verbose, 'x' means expected
        else if (option == 'v' || option == 'x')
        {
            cout << right << setw(3) << "PL" << setw(3) << "W" << setw(3) << "D" << setw(3) << "L"
                 << setw(4) << "GF" << setw(3) << "GA" << setw(4) << "GD"
                 << setw(5) << "PTS";
            if (option == 'x')
                if (teamCount == 36)
                    cout << setw(8) << "Bet Odd";
                else
                    cout << setw(7) << "xPTS";
        }

        // 'p' means predicted
        else if (option == 'p')
        {
            cout << right << setw(5) << " 1st"
                 << setw(6) << "2nd"
                 << setw(6) << "3rd";
            for (int i = 4; i < teamCount + 1; i++)
                cout << right << setw(4) << i << "th";
        }

        for (int i = 0; i < teamCount; i++)
        {
            cout << "\n";
            team[i].printStats(option);
        }

        // Detail for stats
        if (teamCount == 36 && option == 'x')
            cout << "\n\n*Bet Odds are referred from bet365.";
    }

    /*
     * Basketball
     * Function to print table of basketball team.
     * teamCount == 15 -> Eastern and Western conference league
     * teamCount == 30 -> Combined one
     */

    else if (teamCount == 15 || teamCount == 30)
    {
        cout << right << setw(3) << "POS ";

        // 's' means simple
        if (option == 's')
            cout << left << setw(22) << "TEAM"
                 << right << setw(3) << "W" << setw(3) << "L"
                 << setw(7) << "WIN%";

        // 'v' means verbose
        else if (option == 'v')
        {
            cout << left << setw(22) << "TEAM"
                 << right << setw(3) << "PL" << setw(3) << "W" << setw(3) << "L"
                 << setw(5) << "GB" << setw(6) << "HOME" << setw(6) << "ROAD" << setw(6) << "DIV" << setw(6) << "CONF"
                 << setw(7) << "PPG" << setw(8) << "OPP.PPG" << setw(10) << "PPG DIF."
                 << setw(5) << "STRK" << setw(8) << "LAST 10";
        }

        // 'p' means predicted
        else if (option == 'p')
        {
            cout << left << setw(13) << "TEAM"
                 << right << setw(6) << "xWINS" << setw(6) << "xLOSS"
                 << setw(8) << "OFF R." << setw(7) << "DEF R." << setw(7) << "NET R."
                 << setw(9) << "MAKE PO" << setw(10) << "MAKE CSF" << setw(9) << "MAKE CF"
                 << setw(13) << "MAKE FINALS" << setw(7) << "WIN";
        }

        for (int i = 0; i < teamCount; i++)
        {
            cout << "\n";
            team[i].printStats(option);
        }

        // Detail for stats
        if (option == 'v')
            cout << "\n\n*GB: Games Behind, *PPG: Points Per Game, *STRK: Streak";
        else if (option == 'p')
            cout << "\n\n*R.: Rating, *PO: Playoff, *C(S)F: Conference (Semi-)Final";
    }

    cout << "\n=======================================================\n"
         << endl;
}
