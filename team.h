#ifndef TEAM_H
#define TEAM_H
#include <string>

class team
{
private:
    std::string name;
    int position;
    int played, win, draw, lose;
    int gf, ga, gd;               // gf: Goals For, ga: Goals Against, gd: Goal difference
    int points;                   // current Points
    float xPoints;                // expected Points at the end of the season
    float xPosition[20] = {-1.f}; // probability to end up that Position. For example, xPosition[0] means the probability to end up 1st.
    float odd;                    // TBA; Bet odd to be winner of the league. Form would be 1.15, 4.56

public:
    team();
    ~team();
    int getPos() { return position; }
    void createStats(int pos, std::string, int p, int w, int d, int l, int gf, int ga, int pts, float xPts);
    void createProb(int, float);
    void printStats(char);
};

#endif