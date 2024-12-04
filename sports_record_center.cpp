#include <iostream>
using namespace std;

int main()
{

    cout << "Hello!\n"
         << "1. Football\n"
         << "2. Basketball\n"
         << "3. American Football\n"
         << "4. Baseball\n"
         << "5. Exit" << endl;

    int option = 0;
    do
    {
        cout << "Enter an option> ";
        cin >> option;
        switch (option)
        {
        case 1:
            cout << "Football - N/A\n";
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
    } while (option != 5);

    return 0;
}