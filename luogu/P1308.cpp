#include <bits/stdc++.h>
using namespace std;

int main()
{
    string word;
    string text;

    cin >> word;
    cin.ignore();
    getline(cin,text);

    for(char &c : word)
    {
        c = tolower(c);
    }

    for(char &c : text)
    {
        c = tolower(c);
    }

    return 0;
}