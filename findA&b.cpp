#include<bits/stdc++.h>

  using namespace std;

    int main()
    {
       int k;
       cin>>k;
       int b=(k+sqrt(k*k-4*1*k))/2;
       int a=k-b;
       if(a+b==k&&a*b==k)
        cout<<a<<" "<<b<<endl;
       else
        cout<<0<<endl;
     }
