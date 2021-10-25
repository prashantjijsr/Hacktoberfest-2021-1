#include<bits/stdc++.h>

 using namespace std;

 int main()
 {
   int n,m,l,r,count=0;
   cin>>n>>m;
   vector<int>bitArr(n),flipArr(n);
   for(int i=0;i<n;i++)
   {
     cin>>bitArr[i];
   }

   while(m--)
   {
     cin>>l>>r;
      flipArr[l-1]=!flipArr[l-1];
    if(r<n)
        flipArr[r]=!flipArr[r];
   }
    for(int i=1;i<n;i++)
    {
      flipArr[i]=(flipArr[i]^flipArr[i-1]);
    }
    for(int i=0;i<n;i++)
    {
       if(flipArr[i]==1)
        bitArr[i]=!bitArr[i];
        if(bitArr[i]==1)
            count++;
    }
    cout<<count<<" "<<n-count;
    return 0;
 }
