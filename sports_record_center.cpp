#include <iostream>
#include <fstream>
#include <cctype> // For std::isdigit()
#include "team.h"
#include "table.h"
#define FOOTBALL 5 // PL, SerieA, Laliga, Bundes, Ligue1

using namespace std;

int main()
{

    ifstream data1("./src/current_table.csv");
    ifstream data2("./src/predicted_table.csv");

    table footballTable[FOOTBALL];
    for (int i = 0; i < FOOTBALL; i++)
    {
        // 1. Read and add current data
        string line;
        while (getline(data1, line))
        {
            if (line.empty()) // Skip to the next table if line is blank
                break;
            if (!isdigit(line[0])) // Skip the line if it is header: Premier League, La Liga, ...
                continue;

            int index = footballTable[i].getTeamCount();
            footballTable[i].addTeam(index, line);
            footballTable[i].incrementTeamCount();
        }

        // 2. Read and add predicted data
        line.clear();
        int j = 0;
        while (getline(data2, line))
        {
            if (line.empty())
                break;
            if (!isdigit(line[0]))
            {
                footballTable[i].setName(line);
                continue;
            }
            footballTable[i].addProb(j++, line);
        }
    }

    int option = 0;
    while (option != 5)
    {
        cout << "Hello!\n"
             << "1. Football\n2. Basketball\n3. American Football\n4. Baseball\n5. Exit" << endl;
        cout << "Enter an option> ";
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "\nDisplaying football table among Top 5 league in europe......\n";
            while (true)
            {
                cout << "\n1. Premier League\n2. Serie-A\n3. La Liga\n4. Bundesliga\n5. Ligue 1\n6. Go Back\n"
                     << "Enter an option> ";
                int league;
                cin >> league;
                if (league < 1 || league > 6)
                {
                    cout << "Invalid option. Please try again.\n";
                    continue; // Skip the rest of the loop and prompt again
                }
                if (league == 6)
                    break;

                cout << "\n1. Short\n2. Full\n3. Expected\n4. Predicted(PREMIUM)\n"
                     << "Enter an option> ";
                int opt;
                cin >> opt;
                if (opt == 1)
                    footballTable[league - 1].printTable('s');
                else if (opt == 2)
                    footballTable[league - 1].printTable('v');
                else if (opt == 3)
                    footballTable[league - 1].printTable('x');
                else if (opt == 4)
                    footballTable[league - 1].printTable('p');
            }
            break;
        case 2:
            cout << "Basketball - N/A\n";
            break;
        case 3:
            cout << "NFL - N/A\n";
            break;
        case 4:
            cout << "Baseball - N/A\n";
            break;
        default:
            break;
        }
    }

    return 0;
}