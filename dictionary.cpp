#include <bits/stdc++.h>
using namespace std;
#include "dictionary.h"

int main()
{
    Dictionary dict;
    Node* root = nullptr;
    int choice, program;

    root = dict.loadFromFile(root, "Dictionary.txt");
    cout << "\nDictionary loaded successfully! Here are the words:\n";
    dict.inorder(root);

    do
    {
        cout << "\n\n\t\t\t\t\t******************** Dictionary Menu ********************";
        cout << "\n 1. Add Word";
        cout << "\n 2. Search Word";
        cout << "\n 3. Delete Word";
        cout << "\n 4. Display Dictionary";
        cout << "\n 5. Find Nearest Word";
        cout << "\n 6. Find Smallest Word";
        cout << "\n 7. Exit";

        cout << "\n\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        if (choice== 4)
        {
            cout << "Dictionary contents:\n";
            dict.inorder(root);
        }

        else if (choice== 1)
        {
            string w, m;
            cout << "Enter word: ";
            getline(cin, w);
            cout << "Enter meaning: ";
            getline(cin, m);
            root = dict.create(root, w, m);
            cout << "Word added successfully!\n";
        }

        else if (choice== 2)
        {
            string w;
            cout << "Enter word to search: ";
            getline(cin, w);
            dict.search(root, w);
        }

        else if (choice== 3)
        {
            string w;
            cout << "Enter word to delete: ";
            getline(cin, w);
            root = dict.deleteNode(w, root);
            cout << "Word deleted (if found).\n";
        }

        else if (choice== 5)
        {
            string w;
            cout << "Enter word to find nearest match: ";
            getline(cin, w);
            dict.searchNearestWord(root, w);
        }

        else if (choice== 6)
        {
            cout << "Smallest word in dictionary:\n";
            dict.findmin(root);
        }

        else if (choice== 7)
        {
            cout <<"Exiting...\n";
            return 0;
        }

        else
        {
            cout <<"Invalid choice! Please try again.\n";
        }

        cout << "\nDo you want to continue? (1 for Yes, 0 for No): ";
        cin >> program;
        cin.ignore();

    }
    while (program== 1);

    cout << "Program terminated. Goodbye!";
    return 0;
}
