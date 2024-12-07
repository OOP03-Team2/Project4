#ifndef TEAM_H
#define TEAM_H
#include <string>

class Team
{
private:
    /*
     *Universal stats
     */
    std::string name;
    int position;
    int played, win, draw = 0, loss;

    /*
     *Only applied to Football
     */
    int gf, ga, gd;         // gf: Goals For, ga: Goals Against, gd: Goal difference
    int points = -1;        // current Points
    float xPoints;          // Expected Points at the end of the season. Or odds.
    float predictedPos[20]; // probability to end up that Position. For example, xPosition[0] means the probability to end up 1st.

    /*
     *Only applied to Basketball
     */
    float winPercent = -1.f;
    std::string gb;                    // Games Behind
    std::string home, road, div, conf; // results at Home, on Road, from Division, from Conference
    float teamPpg, oppPpg, difPpg;     // Points Per Game by itself, by opponent and difference
    std::string streak, last10;        // consecutive win/lose, and recent performance
    float predictedStat[10];           // xWin, xLoss, Offersive / Defensive / Net Rating and Probability to make Playoffs / Conf SF / Conf F / Finals / Champion

public:
    Team();
    ~Team();

    int getPos() { return position; }

    // for Football
    void createStats(int pos, std::string, int p, int w, int d, int l, int gf, int ga, int pts, float xPts);
    void createProb(int, float);

    // for Basketball
    void createStats(int pos, std::string, int w, int l, float wP, std::string gb, std::string h, std::string r, std::string div, std::string conf, float ppg, float oppg, float dppg, std::string str, std::string l10);
    void createProb(int, int, std::string, float);

    void printStats(char);
};

#endif