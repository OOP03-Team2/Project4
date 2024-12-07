#ifndef TABLE_H
#define TABLE_H
#include "Team.h"
#include <iostream>

class Table
{
private:
    std::string leagueName;
    int teamCount = 0;
    Team team[30]; // Can be changed to dynamic allocation or vector: new team[teamCount], vector<team>

public:
    Table();
    ~Table();

    void setName(std::string name) { leagueName = name; }
    int getTeamCount() { return teamCount; }
    void incrementTeamCount() { teamCount++; }

    // for Top 5 league
    void addFootTeam(int, std::string);
    // for Uefa Champions League
    void addFootTeam(std::string);
    void addProb(int, std::string);

    // for Basketball
    void addBasketTeam(int, std::string);
    void addProb(std::string, int index);

    void printTable(char);
};

#endif