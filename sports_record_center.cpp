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
#define HANDEGG 8    // Maybe 10?

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

int main()
{
    // Run the Python script and check its exit status
    // #ifdef _WIN32 // Windows
    //     int ret1 = system(".\scrap_football.exe");
    //     int ret2 = system(".\scrap_basketball.exe");
    // #elif __linux__ // Linux
    //     int ret1 = system("./scrap_football");
    //     int ret2 = system("./scrap_basketball");
    // #else
    //     cerr << "Unsupported OS!" << endl;
    //     return 1;
    // #endif
    //     if (ret1 || ret2)
    //     {
    //         cout << "Python script failed with exit code: " << ret1 << endl;
    //         cout << "Python script failed with exit code: " << ret2 << endl;
    //         return 1;
    //     }
    //     cout << "Python script executed successfully!" << endl;

    displayWelcomeMessage();

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
        while (getline(data2, line) && !line.empty())
        {
            if (!isdigit(line[0]))
                continue;
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
            cout << "\nDisplaying football table among Top 5 leagues in Europe......\n";
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
                cout << "1. Eastern Conference\n"
                     << "2. Western Conference\n"
                     << "3. All\n"
                     << "4. Predicted(PREMIUM)\n"
                     << "5. Go Back\n"
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