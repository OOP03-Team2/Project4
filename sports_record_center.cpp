#include <cstdlib> // For system()
#include <iostream>
#include <fstream>
#include <cctype> // For std::isdigit()
#include <thread> // For greeter
#include <chrono> // For greeter
#include <ctime>
#include "Table.h"
#include "Team.h"
#define FOOTBALL 6   // PL, Serie A, La liga, Bundesliga, Ligue 1 and UCL
#define BASKETBALL 4 // Eastern, Western, All, and Predicted
#define HANDEGG 12   // 4 AFC, 4 NFC, 2 Conference, All and Predicted

using namespace std;

void typeWriterEffect(const string &message, int delay_ms = 100)
{
    for (char c : message)
    {
        cout << c;
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(delay_ms));
    }
    cout << endl;
}

void displayWelcomeMessage()
{
    string days[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    int year = 1900 + ltm->tm_year;
    int month = 1 + ltm->tm_mon;
    int date = ltm->tm_mday;
    string today = days[ltm->tm_wday] + ", " + to_string(date) + ". " + to_string(month) + ". " + to_string(year) + ".";

    typeWriterEffect("*********************************************************\n", 50);
    typeWriterEffect("*****      Welcome to the Sports Record Center!     *****\n", 50);
    typeWriterEffect("*   Football, Basketball, American Football and more!   *\n", 50);
    typeWriterEffect("*****          Today is " + today + "           *****\n", 50);
    typeWriterEffect("***   We Always provide the most recent information!  ***\n", 50);
    typeWriterEffect("***      Please choose an option from the menu.       ***\n", 50);
    typeWriterEffect("*****            Let's get started!               *******\n", 50);
    typeWriterEffect("*********************************************************\n", 50);
}

void displayFootballTable(Table *);
void displayBasketballTable(Table *);
void displayNFLTable(Table *);

int main()
{
// Run the Python script and check its exit status
#ifdef _WIN32 // Windows
    int ret1 = system("scrap_football.exe");
    int ret2 = system("scrap_basketball.exe");
    int ret3 = system("scrap_handegg.exe");
#elif __linux__ // Linux
    int ret1 = system("./scrap_football");
    int ret2 = system("./scrap_basketball");
    int ret3 = system("./scrap_handegg");
#else
    cerr << "Unsupported OS!" << endl;
    return 1;
#endif
    if (ret1 || ret2 || ret3)
    {
        cout << "Python script failed with exit code: " << ret1 << endl;
        cout << "Python script failed with exit code: " << ret2 << endl;
        cout << "Python script failed with exit code: " << ret3 << endl;
        return 1;
    }
    cout << "Python script executed successfully!" << endl;

    displayWelcomeMessage();

    /*
     * 1. Initialize Football table
     */
    ifstream footData1("./table_football_current.csv");
    ifstream footData2("./table_football_predicted.csv");
    Table footTable[FOOTBALL];
    for (int i = 0; i < FOOTBALL; i++)
    {
        // 1. Read and add current data
        string line;
        while (getline(footData1, line) && !line.empty())
        {
            if (!isdigit(line[0])) // Skip the line if it is header: Premier League, La Liga, ...
            {
                footTable[i].setName(line);
                continue;
            }

            int index = footTable[i].getTeamCount();
            footTable[i].addFootTeam(index, line);
            footTable[i].incrementTeamCount();
        }
        if (i == FOOTBALL - 1)
            break;

        // 2. Read and add predicted data
        line.clear();
        int j = 0;
        while (getline(footData2, line) && !line.empty())
        {
            if (!isdigit(line[0]))
                continue;
            footTable[i].addProb(j++, line);
        }
    }

    /*
     * 2. Initialize Basketball table
     */
    ifstream basketData1("./table_basketball_current.csv");
    ifstream basketData2("./table_basketball_predicted.csv");
    Table basketTable[BASKETBALL];
    // 1. Read and add current data
    for (int i = 0; i < BASKETBALL - 1; i++)
    {
        string line;
        while (getline(basketData1, line) && !line.empty())
        {
            if (!isdigit(line[0]))
            {
                basketTable[i].setName(line);
                continue;
            }

            int index = basketTable[i].getTeamCount();
            basketTable[i].addBasketTeam(index, line);
            basketTable[i].incrementTeamCount();
        }
    }
    // 2. Read and add predicted data
    string line;
    while (getline(basketData2, line) && !line.empty())
    {
        if (!isdigit(line[0]))
        {
            basketTable[3].setName(line);
            continue;
        }
        int index = basketTable[3].getTeamCount();
        basketTable[3].addProb(line, index);
        basketTable[3].incrementTeamCount();
    }

    /*
     * 3. Initialize NFL table
     */
    ifstream nflData1("./table_handegg_current.csv");
    ifstream nflData2("./table_handegg_predicted.csv");
    Table nflTable[HANDEGG];
    for (int i = 0; i < HANDEGG - 1; i++)
    {
        string line;
        while (getline(nflData1, line) && !line.empty())
        {
            if (!isdigit(line[0]))
            {
                nflTable[i].setName(line);
                continue;
            }

            int index = nflTable[i].getTeamCount();
            nflTable[i].addHandTeam(index, line);
            nflTable[i].incrementTeamCount();
        }
    }
    line.clear();
    while (getline(nflData2, line) && !line.empty())
    {
        if (!isdigit(line[0]))
        {
            nflTable[11].setName(line);
            continue;
        }
        int index = nflTable[11].getTeamCount();
        nflTable[11].addProb(line, index, 0);
        nflTable[11].incrementTeamCount();
    }

    int option = 0;
    while (option != 5)
    {
        cout << "\nPlease choose an option:\n"
             << "1. Football\n"
             << "2. Basketball\n"
             << "3. American Football\n"
             << "4. Baseball\n"
             << "5. Exit\n"
             << "Enter your choice (1/2/3/4/5): ";
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "\nDisplaying European Football tables......\n";
            displayFootballTable(footTable);
            break;
        case 2:
            cout << "\nDisplaying NBA tables......\n";
            displayBasketballTable(basketTable);
            break;
        case 3:
            cout << "\nDisplaying NFL tables......\n";
            displayNFLTable(nflTable);
            break;
        case 4:
            cout << "\nDisplaying Baseball tables.....\n";
            break;
        default:
            break;
        }
    }

    return 0;
}

void displayFootballTable(Table *footTable)
{
    while (true)
    {
        cout << "1. Premier League\n"
             << "2. Serie A\n"
             << "3. La Liga\n"
             << "4. Bundesliga\n"
             << "5. Ligue 1\n"
             << "6. Uefa Champions League\n"
             << "7. Go Back\n"
             << "Enter your choice (1/2/3/4/5/6/7): ";
        int league;
        cin >> league;
        if (league < 1 || league > 7)
        {
            cout << "Invalid option. Please try again.\n";
            continue; // Skip the rest of the loop and prompt again
        }
        if (league == 7)
            break;

        cout << "\n1. Short\n2. Full\n3. Expected\n4. Predicted(PREMIUM)\n"
             << "Enter your choice (1/2/3/4): ";
        int opt;
        cin >> opt;
        if (opt == 1)
            footTable[league - 1].printTable('s');
        else if (opt == 2)
            footTable[league - 1].printTable('v');
        else if (opt == 3)
            footTable[league - 1].printTable('x');
        else if (opt == 4)
            footTable[league - 1].printTable('p');
    }
}

void displayBasketballTable(Table *basketTable)
{
    while (true)
    {
        cout << "1. Eastern Conference\n"
             << "2. Western Conference\n"
             << "3. All\n"
             << "4. Predicted(PREMIUM)\n"
             << "5. Go Back\n"
             << "Enter your choice(1/2/3/4/5): ";
        int league;
        cin >> league;
        if (league < 1 || league > 5)
        {
            cout << "Invalid option. Please try again.\n";
            continue; // Skip the rest of the loop and prompt again
        }
        else if (league == 4)
        {
            basketTable[league - 1].printTable('p');
            break;
        }
        else if (league == 5)
            break;

        cout << "\n1. Short\n2. Full\n"
             << "Enter your choice(1/2): ";
        int opt;
        cin >> opt;
        if (opt == 1)
            basketTable[league - 1].printTable('s');
        else if (opt == 2)
            basketTable[league - 1].printTable('v');
    }
}

void displayNFLTable(Table *nflTable)
{
    while (true)
    {
        cout << "1. Division\n"
             << "2. Conference\n"
             << "3. All\n"
             << "4. Predicted(PREMIUM)\n"
             << "5. Go Back\n"
             << "Enter your choice(1/2/3/4/5): ";
        int league;
        cin >> league;
        if (league < 1 || league > 5)
        {
            cout << "Invalid option. Please try again.\n";
            continue;
        }
        else if (league == 4)
        {
            nflTable[11].printTable('p');
            break;
        }
        else if (league == 5)
            break;

        int opt;
        if (league == 1)
        {
            cout << "\n1. AFC\n"
                 << "2. NFC\n"
                 << "3. All\n"
                 << "Enter your choice(1/2/3): ";
            cin >> opt;
            if (opt == 1)
                for (int i = 0; i < 4; i++)
                    nflTable[i].printTable('v');
            else if (opt == 2)
                for (int i = 4; i < 8; i++)
                    nflTable[i].printTable('v');
            else if (opt == 3)
                for (int i = 0; i < 8; i++)
                    nflTable[i].printTable('v');
        }
        else if (league == 2)
        {
            cout << "\n1. AMERICAN\n"
                 << "2. NATIONAL\n"
                 << "3. All\n"
                 << "Enter your choice(1/2/3): ";
            cin >> opt;
            if (opt == 1)
                nflTable[8].printTable('v');
            else if (opt == 2)
                nflTable[9].printTable('v');
            else if (opt == 3)
                for (int i = 8; i < 10; i++)
                    nflTable[i].printTable('v');
        }
        else if (league == 3)
        {
            cout << "\n1. Short\n2. Full\n"
                 << "Enter your choice(1/2): ";
            cin >> opt;
            if (opt == 1)
                nflTable[10].printTable('s');
            else if (opt == 2)
                nflTable[10].printTable('v');
        }
    }
}