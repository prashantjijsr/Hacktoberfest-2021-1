#include<iostream>
#include<iomanip>
  using namespace std;

   int main()
   {
     float c[20],f;
     char name[20][15];
     int n,i;
      cout<<"enter number of person::";
      cin>>n;
      for(i=0;i<n;i++)
      {
        cout<<"enter name and temperature(farenheit) of "<<i+1<<" person::";
        cin>>name[i]>>f;
        c[i]=(f-32)*5/9;
      }
      cout<<"person detail"<<endl;
      for(i=0 ; i<n ; i++)
      {
        cout << name[i] <<" " << fixed << setprecision(1) << c[i] << endl;
      }
   }
