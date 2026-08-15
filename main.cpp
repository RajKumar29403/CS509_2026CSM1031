#include <iostream>

using namespace std;

// Assignment 1
int assignment1();

// Assignment 2
int assignment2();

// Assignment 3
int assignment3();


int main()
{
    int choice;

    while (true)
    {
        cout << "\n=====================================\n";
        cout << "      CS509 Programming Assignment\n";
        cout << "=====================================\n";

        cout << "1. Assignment 1\n";
        cout << "2. Assignment 2\n";
        cout << "3. Assignment 3\n";
        cout << "4. Exit\n\n";

        cout << "Enter your choice : ";
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "\nInvalid input. Please enter a number.\n";
            continue;
        }


        switch (choice)
        {
            case 1:
                assignment1();
                break;

            case 2:
                assignment2();
                break;

            case 3:
                assignment3();
                break;

            case 4:
                cout << "\nThank You!\n";
                return 0;

            default:
                cout << "\nInvalid Choice.\n";
        }
    }
}