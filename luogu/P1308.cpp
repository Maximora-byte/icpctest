#include <bits/stdc++.h>
using namespace std;

int main()
{
    string target;
    string text;

    cin >> target;
    cin.ignore();
    getline(cin,text);

    for(char &c : target)
    {
        c=tolower(c);
    }

    for(char &c : text)
    {
        c=tolower(c);
    }


    int cnt=0;
    int first = -1; // 第一次找到的位置；-1 表示还没找到
    int i=0;
    while(i<text.size())
    {
        if(text[i]==' ')
        {
            i++;
            continue;
        }

        int start=i;

        while(i<text.size() && text[i]!=' ')
        {
            i++;
        }

        string temp=text.substr(start,i-start);

    if(temp == target)
{
    if(cnt == 0)       // 这是第一次找到
    {
        first = start; // 保存这个单词的起始下标
    }
    cnt++;
}
    }

    if(cnt == 0)
{
    cout << -1;
}
    else
{
    cout << cnt << " " << first;
}

    return 0;
}