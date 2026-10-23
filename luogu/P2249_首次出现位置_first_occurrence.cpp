#include<bits/stdc++.h>
using namespace std;
int find(vector<int>& a,int x)
{
    int l=0;
    int r=a.size()-1;

    int ans=-1;


    while(l<=r)
    {
        int mid=(l+r)/2;

        if(a[mid]==x)
        {
            ans=mid;
            r=mid-1;
        }
        else if(a[mid]<x)
        {
            l=mid+1;
        }
        else
        {
            r=mid-1;
        }
    }

    return ans;
}
int main()
{
    int n,m;

    cin>>n>>m;


    vector<int> a(n);

    for(int i=0;i<n;i++)
    {
        cin>>a[i];
    }


    while(m--)
    {
        int x;

        cin>>x;


        int ans=find(a,x);


        if(ans==-1)
        {
            cout<<-1<<" ";
        }
        else
        {
            cout<<ans+1<<" ";
        }
    }


    return 0;
}