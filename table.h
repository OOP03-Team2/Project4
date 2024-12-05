#ifndef TABLE_H // Include guard start
#define TABLE_H
#include "team.h"
#include <iostream>

class table
{
private:
    std::string leagueName;
    int teamCount = 0;
    team Team[20]; // Can be changed to use dynamic allocation: new team[teamCount]

public:
    table();
    ~table();
    void setName(std::string name) { leagueName = name; }
    int getTeamCount() { return teamCount; }
    void incrementTeamCount() { teamCount++; }
    void addTeam(int, std::string);
    void addProb(int, std::string);
    void printTable(char);
};

#endif