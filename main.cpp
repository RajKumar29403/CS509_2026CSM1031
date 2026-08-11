#include <iostream>

using namespace std;

// Assignment 1
int assignment1();

// Assignment 2
int assignment2();

int main()
{
    while (true)
    {
        int choice;

        cout << "\n=====================================\n";
        cout << "      CS509 Programming Assignment\n";
        cout << "=====================================\n";
        cout << "1. Assignment 1\n";
        cout << "2. Assignment 2\n";
        cout << "3. Exit\n";
        cout << "Enter your choice : ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                assignment1();
                break;

            case 2:
                assignment2();
                break;

            case 3:
                cout << "\nThank You!\n";
                return 0;

            default:
                cout << "\nInvalid Choice!\n";
                continue;
        }

        char again;
        cout << "\nReturn to Main Menu? (y/n): ";
        cin >> again;

        if (again == 'n' || again == 'N')
        {
            cout << "\nThank You!\n";
            break;
        }
    }

    return 0;
}