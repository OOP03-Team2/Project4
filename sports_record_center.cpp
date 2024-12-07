#include <iostream>
#include <fstream>
#include <cctype> // For std::isdigit()
#include "Table.h"
#include "Team.h"
#define FOOTBALL 5   // PL, Serie A, La liga, Bundesliga, and Ligue 1
#define BASKETBALL 4 // Eastern, Western, All, and Predicted

using namespace std;

int main()
{
    // // Run the Python script and check its exit status
    // int return_code1 = system("./myenv/bin/python3.12 ./scrap_football.py");
    // int return_code2 = system("./myenv/bin/python3.12 ./scrap_basketball.py");

    // if (return_code1 || return_code2)
    // {
    //     cout << "Python script failed with exit code: " << return_code1 << endl;
    //     cout << "Python script failed with exit code: " << return_code2 << endl;
    //     return 1;
    // }
    // cout << "Python script executed successfully!" << endl;

    ifstream data1("./table_football_current.csv");
    ifstream data2("./table_football_predicted.csv");

    ifstream data3("./table_basketball_current.csv");
    ifstream data4("./table_basketball_predicted.csv");

    Table footTable[FOOTBALL];
    for (int i = 0; i < FOOTBALL; i++)
    {
        // 1. Read and add current data
        string line;
        while (getline(data1, line) && !line.empty())
        {
            if (!isdigit(line[0])) // Skip the line if it is header: Premier League, La Liga, ...
                continue;

            int index = footTable[i].getTeamCount();
            footTable[i].addFootTeam(index, line);
            footTable[i].incrementTeamCount();
        }

        // 2. Read and add predicted data
        line.clear();
        int j = 0;
        while (getline(data2, line) && !line.empty())
        {
            if (!isdigit(line[0]))
            {
                footTable[i].setName(line);
                continue;
            }
            footTable[i].addProb(j++, line);
        }
    }

    Table basketTable[BASKETBALL];
    for (int i = 0; i < BASKETBALL - 1; i++)
    {
        // 1. Read and add current data
        string line;
        while (getline(data3, line) && !line.empty())
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
    while (getline(data4, line) && !line.empty())
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
            cout << "\nDisplaying football table among Top 5 leagues in Europe......\n";
            while (true)
            {
                cout << "\n1. Premier League\n2. Serie A\n3. La Liga\n4. Bundesliga\n5. Ligue 1\n6. Go Back\n"
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
                    footTable[league - 1].printTable('s');
                else if (opt == 2)
                    footTable[league - 1].printTable('v');
                else if (opt == 3)
                    footTable[league - 1].printTable('x');
                else if (opt == 4)
                    footTable[league - 1].printTable('p');
            }
            break;
        case 2:
            cout << "\nDisplaying NBA table......\n";
            while (true)
            {
                cout << "\n1. Eastern Conference\n2. Western Conference\n3. All\n4. Predicted(PREMIUM)\n5. Go Back\n"
                     << "Enter an option> ";
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
                     << "Enter an option> ";
                int opt;
                cin >> opt;
                if (opt == 1)
                    basketTable[league - 1].printTable('s');
                else if (opt == 2)
                    basketTable[league - 1].printTable('v');
            }
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