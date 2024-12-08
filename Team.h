#ifndef TEAM_H
#define TEAM_H
#include <string>

class Team
{
private:
    /*
     * Universal stats
     */
    int position;
    std::string name;
    int played, win, draw = 0, loss;

    /*
     * Shared by more than one sport
     */
    int gf, ga, gd; // gf: Goals For, ga: Goals Against, gd: Goal difference
    float winPercent = -1.f;
    std::string home, road, division, conference; // results at Home, on Road, from Division, from Conference
    std::string streak;                           // consecutive win/lose,

    /*
     * Only applied to Football
     */
    int points = -1;        // current Points
    float xPoints;          // Expected Points at the end of the season. Or odds.
    float predictedPos[20]; // probability to end up that Position. For example, xPosition[0] means the probability to end up 1st.

    /*
     * Only applied to Basketball
     */
    std::string gb;                    // Games Behind
    float teamPpg = 0, oppPpg, difPpg; // Points Per Game by itself, by opponent and difference
    std::string last10;                // performance by last 10 games
    float predictedStat[10];           // xWin, xLoss, Offersive / Defensive / Net Rating and Probability to make Playoffs / Conf SF / Conf F / Finals / Champion

    /*
     * Only applied to American Football
     */
    std::string last5;
    float pStat[7]; // xWin, xLoss, and Probability to make Playoffs / win Divison / make Conference Final / make Super Bowls / Chmapion

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

    // for A. Football
    void createStats(int pos, std::string, int w, int l, int t, float wP, int gf, int ga, std::string h, std::string r, std::string div, std::string conf, std::string str, std::string l5);
    void createProb(int, std::string, float, int);

    void printStats(char);
};

#endif