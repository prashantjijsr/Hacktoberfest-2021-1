//=====================================HEADER FILE========================================================================================

#include<iostream>
#include<vector>
#include<queue>
#include<iomanip>
#include<stdlib.h>

 using namespace std;
//====================================================CLASS PROCESS DEFINITION==============================================================

class process
  {
    public:
     int arr_t,b_t,wait_t,tat,pid,p,r_t,cm_t;
     process()
     {
       arr_t=b_t=wait_t=tat=pid=p=cm_t=0;
       r_t=-1;
     }
   priority_queue<process> runFCFS(priority_queue<process> &pq,int n,int &tat,int &twt);

   process pop_index(priority_queue<process>* main_queue, int index);

   int min_BT_index(priority_queue<process> main_queue, int limit);

   priority_queue<process> runsjf(priority_queue<process> &pq,int n,int &tat,int &twt);

   int max_priority_index(priority_queue<process> main_queue, int limit);

   priority_queue<process> runNP(priority_queue<process> &pq,int n,int &tat,int &twt);

   int min_BT(priority_queue<process> main_queue, int clock);

   priority_queue<process> runsrtf(priority_queue<process> pq,int n,int &ttat,int &twt);

   int max_priority(priority_queue<process> main_priority_queue,int limit);

   priority_queue<process> runPriority(priority_queue<process> pq,int n,int &ttat,int &twt);

   priority_queue<process> insertpos(priority_queue<process> pq,process temp,int time,int inc);

   priority_queue<process> runRR(priority_queue<process> pq,int n, int Time_Slice,int &tat,int &twt);

};


//===========================================COMPARISION FUNCTION==========================================================

   bool operator<(const process& p1, const process& p2)
    {
      if(p1.arr_t==p2.arr_t)
        return p1.pid > p2.pid;
     return p1.arr_t >= p2.arr_t;
    }

//================================CLASS PROCESS FUNCTION DEFINITION===================================================

//=============================== FUNCTION TO PERFORM FIRST COME FIRST SERVE SCHEDULING===============================

   priority_queue<process> process:: runFCFS(priority_queue<process> &pq,int n,int &tat,int &twt)
     {
        process temp;
        priority_queue<process> c_q;
        int time=0,f=0;
        tat=0,twt=0;
        cout<<"\n\t========================================================================";
        cout<<"\n\t GAINT CHART:: (";
        while(!pq.empty())
        {
            temp=pq.top();
            if(temp.arr_t>time)
            {
                 if(f==1)
               cout<<"--idle--"<<temp.arr_t;
                else
                cout<<time<<"--idle--"<<temp.arr_t;
                 time=temp.arr_t;
                 f=1;
            }
            if(time<=time+temp.b_t)
           {
               temp.r_t=time-temp.arr_t;
             if(f==0)
               cout<<time<<"--"<<"P"<<temp.pid<<"--"<<time+temp.b_t;
               else
               {
                   cout<<"--"<<"P"<<temp.pid<<"--"<<time+temp.b_t;
               }
              time+=temp.b_t;
              temp.cm_t=time;
                f=1;
             temp.tat=time-temp.arr_t;
             temp.wait_t=temp.tat-temp.b_t;;
             tat+=temp.tat;
             twt+=temp.wait_t;
           }

           c_q.push(temp);
           pq.pop();
        }

         cout<<" )"<<endl;
         return pq=c_q;
     }

 //==============================FUNCTION TO POP THE PROCESS AT GIVEN INDEX===========================================

   process process:: pop_index(priority_queue<process>* main_queue, int index)
  {
       priority_queue<process> rm_index;
       int i;
       process p;
       switch (index)
        {
           case 0:
            p = (*main_queue).top();
            (*main_queue).pop();
            break;
          default:
              for (i = 0; i < index; i++)
                {
                  rm_index.push((*main_queue).top());
                 (*main_queue).pop();
                }
              p = (*main_queue).top();
              (*main_queue).pop();
           while (!(*main_queue).empty())
            {
               rm_index.push((*main_queue).top());
              (*main_queue).pop();
            }
         (*main_queue) = rm_index;
          break;
       }
    return p;
  }

// ====================FUNCTION TO FIND THE PROCESS WITH MINIMUM BURST TIME AT GIVEN TIME===============================

  int process:: min_BT_index(priority_queue<process> main_queue, int limit)
   {
    int index, i = 0;
    int min = 0;
    while (!main_queue.empty() && main_queue.top().arr_t <= limit)
        {
          if (min == 0 || main_queue.top().b_t < min)
          {
            min = main_queue.top().b_t;
            index = i;
          }
         main_queue.pop();
         i++;
        }
    return index;
   }

//==========================FUNCTION TO PERFORM SHORTEST JOB FIRST SCHEDULING==========================================

    priority_queue<process> process:: runsjf(priority_queue<process> &pq,int n,int &tat,int &twt)
     {
         priority_queue<process> c_q;
         process temp;
         int time=0,f=0;
         tat=0,twt=0;
           cout<<"\n\t=======================================================================================\n";
          cout<<"\n\t GAINT CHART:: (";
         while(pq.size())
         {
             temp=pq.top();
             if(temp.arr_t>time)
             {
                 if(f==1)
               cout<<"--idle--"<<temp.arr_t;
                else
                cout<<time<<"--idle--"<<temp.arr_t;
                 time=temp.arr_t;
                 f=1;
             }
              temp=pop_index(&pq,min_BT_index(pq,time));
            if(time<=time+temp.b_t)
            {
               temp.r_t=time-temp.arr_t;
              if(f==0)
               cout<<time<<"--"<<"P"<<temp.pid<<"--"<<time+temp.b_t;
               else
               {
                   cout<<"--"<<"P"<<temp.pid<<"--"<<time+temp.b_t;
               }
              time+=temp.b_t;
              temp.cm_t=time;
                f=1;
              temp.tat=time-temp.arr_t;
              tat+=temp.tat;
              temp.wait_t=temp.tat-temp.b_t;
              twt+=temp.wait_t;
            }
         c_q.push(temp);

        }
        cout<<" )"<<endl<<endl;
       return pq=c_q;
     }

 //=======================FUNCTION TO FIND THE INDEX OF PROCESS WITH MAXIMUM PRIORITY AT GIVEN TIME=============================

  int process:: max_priority_index(priority_queue<process> main_queue, int limit)
    {
       int max = -1, i = 0, index = 0;

        while (!main_queue.empty() && main_queue.top().arr_t <= limit)
         {
            if (main_queue.top().p > max)
             {
                max = main_queue.top().p;
                index = i;
             }
            main_queue.pop();
            i++;
         }
      return index;
    }

//=============================FUNCTION TO PERFORM NONPREEMPTIVE PRIORITY SCHEDULING===========================================

   priority_queue<process> process:: runNP(priority_queue<process> &pq,int n,int &tat,int &twt)
     {
         priority_queue<process> c_q;
         process temp;
         int time=0,f=0;
          tat=0,twt=0;
           cout<<"\n\t=============================================================================\n";
        cout<<"\n\t GAINT CHART:: (";
         while(pq.size())
         {
             temp=pq.top();
             if(temp.arr_t>time)
            {
                 if(f==1)
               cout<<"--idle--"<<temp.arr_t;
                else
                cout<<time<<"--idle--"<<temp.arr_t;
                 time=temp.arr_t;
                 f=1;
            }
              temp=pop_index(&pq,max_priority_index(pq,time));
            if(time<=time+temp.b_t)
           {
               temp.r_t=time-temp.arr_t;
             if(f==0)
               cout<<time<<"--"<<"P"<<temp.pid<<"--"<<time+temp.b_t;
               else
               {
                   cout<<"--"<<"P"<<temp.pid<<"--"<<time+temp.b_t;
               }
              time+=temp.b_t;
              temp.cm_t=time;
                f=1;
             temp.tat=time-temp.arr_t;
             tat+=temp.tat;
             temp.wait_t=temp.tat-temp.b_t;
             twt+=temp.wait_t;
            }
        c_q.push(temp);

      }
        cout<<" )"<<endl<<endl;
      return pq=c_q;
     }

 //============================================FUNCTION TO FIND THE MINIMUM BURST TIME AT GIVEN TIME==========================================

   int process:: min_BT(priority_queue<process> main_queue, int clock)
  {
      int min = 0;
      while (!main_queue.empty() && main_queue.top().arr_t <= clock)
     {
        if (min == 0 || min > main_queue.top().b_t)
            min = main_queue.top().b_t;
        main_queue.pop();
     }
    return min;
  }

 //=============================================FUNCTION TO PERFORM SHORTEST REMAINING TIME FIRST SCHEDULING==================================

   priority_queue<process> process:: runsrtf(priority_queue<process> pq,int n,int &ttat,int &twt)
     {
         ttat=twt=0;
         priority_queue<process> c_q;
         vector<int> b(n);
         process temp;
         int time=0,f=0,start=0;
         cout<<"\n\n\t=================================================================================\n";
         cout<<"\n\t GAINT CHART:: (";
         while(pq.size())
         {
             temp=pq.top();

              if(temp.arr_t>time)
            {
                 if(f==1)
                  cout<<"-idle-"<<temp.arr_t;
                else
                 cout<<time<<"-idle-"<<temp.arr_t;
                 time=temp.arr_t;
                 f=1;
            }
              temp=pop_index(&pq,min_BT_index(pq,time));
              if(temp.r_t==-1)
              {
                temp.r_t=time-temp.arr_t;
                 b[temp.pid-1]=temp.b_t;
              }
               start=time;
           while(temp.b_t > 0 && (pq.empty() ||  pq.top().arr_t > time || temp.b_t <= min_BT(pq,time)))
            {
             temp.b_t--;
             time++;
            }
          if(temp.b_t==0)
           {
             if(f==0)
               cout<<start<<"-"<<"P"<<temp.pid<<"-"<<time;
               else
               {
                   cout<<"-"<<"P"<<temp.pid<<"-"<<time;
               }
                f=1;
             temp.b_t=b[temp.pid-1];
             temp.cm_t=time;
             temp.tat=time-temp.arr_t;
             temp.wait_t=temp.tat-temp.b_t;
              ttat+=temp.tat;
              twt+=temp.wait_t;
             c_q.push(temp);
            }
          else
            {
             if(f==0)
               cout<<start<<"-"<<"P"<<temp.pid<<"-"<<time;
               else
               {
                   cout<<"-"<<"P"<<temp.pid<<"-"<<time;
               }
                f=1;
              pq.push(temp);

            }
      }
      cout<<" )"<<endl<<endl;
      return pq=c_q;
    }

//================================FUNCTION TO FIND MAXIMUM PRIORITY OF PROCESS AT GIVEN TIME===============================

   int process:: max_priority(priority_queue<process> main_priority_queue,int limit)
    {
       int max = -1;
           while (!main_priority_queue.empty()&& main_priority_queue.top().arr_t <= limit)
         {
             if (main_priority_queue.top().p > max)
                max = main_priority_queue.top().p;
             main_priority_queue.pop();
         }
      return max;
    }

//===================FUNCTION TO PERFORM PREEMPTIVE PRIORITY SCHEDULING================================================

    priority_queue<process> process:: runPriority(priority_queue<process> pq,int n,int &ttat,int &twt)
     {
         ttat=twt=0;
         priority_queue<process> c_q;
         vector<int> b(n+1);
         process temp;
         int time=0,f=0,start=0;
            cout<<"\n\n\t==================================================================================\n";
        cout<<"\n\t GAINT CHART:: (";
         while(!pq.empty())
         {
             temp=pq.top();

              if(temp.arr_t>time)
            {
                 if(f==1)
                  cout<<"-idle-"<<temp.arr_t;
                else
                 cout<<time<<"-idle-"<<temp.arr_t;
                 time=temp.arr_t;
                 f=1;
            }
              temp=pop_index(&pq,(max_priority_index(pq, time)));
              if(temp.r_t==-1)
              {
                temp.r_t=time-temp.arr_t;
                 b[temp.pid]=temp.b_t;
              }
               start=time;
           while (temp.b_t > 0 && (pq.empty() ||  pq.top().arr_t > time|| temp.p >=max_priority(pq,time)))
            {
             temp.b_t--;
             time++;
            }
          if(temp.b_t==0)
           {
             if(f==0)
               cout<<start<<"-"<<"P"<<temp.pid<<"-"<<time;
               else
               {
                   cout<<"-"<<"P"<<temp.pid<<"-"<<time;
               }
                f=1;
              temp.b_t=b[temp.pid];
              temp.cm_t=time;
              temp.tat=time-temp.arr_t;
              temp.wait_t=temp.tat-temp.b_t;
              ttat+=temp.tat;
              twt+=temp.wait_t;
              c_q.push(temp);
           }
            else
            {
             if(f==0)
               cout<<start<<"-"<<"P"<<temp.pid<<"-"<<time;
               else
               {
                   cout<<"-"<<"P"<<temp.pid<<"-"<<time;
               }
                f=1;
              pq.push(temp);
            }
      }
        cout<<" )"<<endl<<endl;
        return pq=c_q;
   }
//====================FUNCTION TO INSERT THE PROCESS AT RIGHT POSITION=================================================

  priority_queue<process> process:: insertpos(priority_queue<process> pq,process temp,int time,int inc)
      {
          priority_queue<process> tpq;
          int t=0;
         while(pq.top().arr_t<=time&&(pq.size()!=0))
         {
             tpq.push(pq.top());
             t=pq.top().arr_t;
             pq.pop();
         }
         if(pq.size()==0)
         {
            temp.arr_t=(t+1);
            tpq.push(temp);
         }
         else
         {
          temp.arr_t+=inc;
          tpq.push(temp);
         }
         while(!pq.empty())
         {
            tpq.push(pq.top());
            pq.pop();
         }
         return tpq;
      }

//============================FUNCTION TO PERFORM ROUND ROBIN SCHEDULING==============================================


  priority_queue<process> process:: runRR(priority_queue<process> pq,int n, int Time_Slice,int &tat,int &twt)
   {
         tat=twt=0;
         priority_queue<process> c_q;
         vector<int> b(n),a(n);
         process temp;
         int time=0,f=0,start=0,s,inc=Time_Slice+1;
         cout<<"\n\n\t=========================================================================================\n";
         cout<<"\n\t GAINT CHART:: (";
     while (!pq.empty())
       {
        temp = pq.top();
         pq.pop();
           if(temp.arr_t>time)
            {
                 if(f==1)
                  cout<<"-idle-"<<temp.arr_t;
                else
                 cout<<time<<"-idle-"<<temp.arr_t;
                 time=temp.arr_t;
                 f=1;
            }
        if(temp.r_t==-1)
              {
                 temp.r_t=time-temp.arr_t;
                 b[temp.pid-1]=temp.b_t;
                 a[temp.pid-1]=temp.arr_t;
              }
               start=time;
               s=0;
       while(temp.b_t>0&&(s<Time_Slice||pq.empty()||pq.top().arr_t>time))
       {
           time++;
           s++;
           temp.b_t--;
       }
        if(temp.b_t==0)
           {
             if(f==0)
               cout<<start<<"-"<<"P"<<temp.pid<<"-"<<time;
               else
               {
                   cout<<"-"<<"P"<<temp.pid<<"-"<<time;
               }
                f=1;
             temp.b_t=b[temp.pid-1];
             temp.arr_t=a[temp.pid-1];
             temp.cm_t=time;
             temp.tat=time-temp.arr_t;
             temp.wait_t=temp.tat-temp.b_t;
              tat+=temp.tat;
              twt+=temp.wait_t;
             c_q.push(temp);
         }
        else
        {
            if(f==0)
               cout<<start<<"-"<<"P"<<temp.pid<<"-"<<time;
               else
               {
                   cout<<"-"<<"P"<<temp.pid<<"-"<<time;
               }
                f=1;

              pq=insertpos(pq,temp,time,inc);
        }
    }
     cout<<" )"<<endl<<endl;
      return pq=c_q;
  }

//==================================================================================================================



 //===============(CLASS TO TAKE INPUT AND PRINT TABLE OF DIFFERENT TIMES)===============================================

 class entry
  {
      public:
          int num;
      process ob;
    priority_queue<process> getEntry(priority_queue<process> pq,int f)
    {
        cout<<"\n\n\tenter number of process::";
        cin>>num;
        for(int i=0;i<num;i++)
        {
            if(f==1)
            {
            cout<<"\n\tenter arrival time  burst time and priority of  process "<<i+1<<" ::";
            ob.pid=i+1;
            cin>>ob.arr_t>>ob.b_t>>ob.p;
            }
            else
            {
             cout<<"\n\tenter arrival time and burst time of  process "<<i+1<<" ::";
             ob.pid=i+1;
             cin>>ob.arr_t>>ob.b_t;
            }
            pq.push(ob);
        }
        return pq;
    }

    void printChart(priority_queue<process> &pq,int n,int tat,int twt,int f)
    {
        process ob;
        if(f==1)
      {
        cout<<"\t================================================================================================================================\n";
        cout<<"\t||process_Id ||  arr_time || burst_time ||  priority   || response_time ||  completion_time || turnaround_time || waiting_time ||\n";
        cout<<"\t||===========||===========||============||=============||===============||==================||=================||==============||\n";
        for(int i=0;i<n;i++)
        {
            ob=pq.top();
            cout<<setw(4)<<"\t||  "<<setw(4)<<ob.pid<<"     ||  "<<setw(4)<<ob.arr_t<<"     ||   "<<setw(4)<<ob.b_t<<"     ||   "<<setw(4)<<ob.p<<"      ||     "<<setw(4)<<ob.r_t<<"      ||      "<<setw(4)<<ob.cm_t<<"        ||   "<<setw(4)<<ob.tat<<"          ||    "<<setw(4)<<ob.wait_t<<"      ||\n";
            pq.pop();
        }
         cout<<"\t=================================================================================================================================\n\n";
      }
      else
      {
          cout<<"\t====================================================================================================================\n";
        cout<<"\t||process_Id ||  arr_time || burst_time ||  response_time ||  completion_time ||  turnaround_time || waiting_time   ||\n";
        cout<<"\t||===========||===========||============||================||==================||==================||================||\n";
        for(int i=0;i<n;i++)
        {
            ob=pq.top();
            cout<<setw(4)<<"\t||  "<<setw(4)<<ob.pid<<"     ||  "<<setw(4)<<ob.arr_t<<"     ||   "<<setw(4)<<ob.b_t<<"     ||     "<<setw(4)<<ob.r_t<<"       ||      "<<setw(4)<<ob.cm_t<<"         ||   "<<setw(4)<<ob.tat<<"          ||     "<<setw(4)<<ob.wait_t<<"       ||\n";
            pq.pop();
        }
         cout<<"\t======================================================================================================================\n\n";
      }
        cout<<"\n\t TOTAL TURNAROUND TIME = "<<tat;
        cout<<"\n\t AVERAGE TURNAROUND TIME = "<<((float)tat)/n<<endl<<endl;
        cout<<"\n\t TOTAL WAITING TIME = "<<twt;
        cout<<"\n\t AVERAGE WAITING TIME = "<<(float(twt)/n)<<endl<<endl;
    }
  };

//------------------------------------------------------------------------------------------------------------------------------------------

//=================CLASS PREMPTIVE INHERITING CLASS PROCESS AND ENTRY=================================================
  class preEmptive:public process,public entry
  {
   public:
       char showMenu()
       {
           system("cls");
           char ch;
           int tat=0,twt=0;
           priority_queue<process> pq;
           cout<<"\n\n\t DIFFERENT PREEMPTIVE CPU SCHEDULING ALGORITHM\n";
           cout<<"\t=================================================\n\n";
           cout<<"\t1. SHORTEST REMAINING TIME FIRST\n";
           cout<<"\t2. ROUND ROBIN\n";
           cout<<"\t3. PRIORITY\n";
           cout<<"\t4. BACK TO PREVIOUS MENU\n";
           cout<<"\t5. BACK TO MAIN MENU\n";
           cout<<"\t6. EXIT\n\n";
           cin>>ch;
           system("cls");
           switch(ch)
           {
            case '1':
                cout<<"\t  SHORTEST REMAININF TIME FIRST SCHEDULING ALGORITHM";
                cout<<"\n\t======================================================\n";
              pq=getEntry(pq,0);
              pq=runsrtf(pq,num,tat,twt);
              printChart(pq,num,tat,twt,0);
              system("pause");
              return '0';
              break;
            case '2':
                cout<<"\t  ROUND ROBIN SCHEDULING ALGORITHM";
                cout<<"\n\t======================================";
                int t;
                pq=getEntry(pq,0);
                cout<<"\n enter time slice(quantum time)::";
                cin>>t;
                pq=runRR(pq,num,t,tat,twt);
                printChart(pq,num,tat,twt,0);
                system("pause");
                return '0';
                break;
            case '3':
                cout<<"\t  PREEMPTIVE PRIORITY SCHEDULING";
                cout<<"\n\t===================================";
             pq=getEntry(pq,1);
            //  printChart(pq,num,tat,twt,1);
             pq=runPriority(pq,num,tat,twt);
             printChart(pq,num,tat,twt,1);
             system("pause");
             return '0';
             break;
            case '5':
                return '1';
            case '6':
             return '2';
        }
       }
  };

  //=====================CLASS NONPREEMPTIVE INHERETING CLASS PROCESS AND ENTRY========================================

  class nonPreEmptive : public process , public entry
  {
      char ch;
      priority_queue<process> pq;
    public:
         char showMenu()
       {
           int tat=0,twt=0;
           system("cls");
           cout<<"\n\n\t DIFFERENT NONPREEMPTIVE CPU SCHEDULING ALGORITHM\n";
           cout<<"\t=================================================\n\n";
           cout<<"\t1. FIRST COME FIRST SERVE\n";
           cout<<"\t2. SHORTEST JOB FIRST\n";
           cout<<"\t3. PRIORITY\n";
           cout<<"\t4. BACK TO PREVIOUS MENU\n";
           cout<<"\t5. BACK TO MAIN MENU\n";
           cout<<"\t6. EXIT\n\n";
           cout<<"\tenter your choice::";
           cin>>ch;
           system("cls");
           switch(ch)
           {
           case '1':
               cout<<"\t  FIRST COME FIRST SERVE SCHEDULING";
               cout<<"\n\t=====================================";
               pq=getEntry(pq,0);
               pq=runFCFS(pq,num,tat,twt);
               printChart(pq,num,tat,twt,0);
               system("pause");
               return '0';
               break;
           case '2':
               cout<<"\t  SHORTEST JOB FIRST SCHEDULING";
               cout<<"\n\t==================================";
              pq=getEntry(pq,0);
              pq=runsjf(pq,num,tat,twt);
              printChart(pq,num,tat,twt,0);
              system("pause");
              return '0';
              break;
           case '3':
               cout<<"\t  NON-PREEMPTIVE PRIORITY SCHEDULING";
               cout<<"\n\t========================================";
            pq=getEntry(pq,1);
            pq=runNP(pq,num,tat,twt);
            printChart(pq,num,tat,twt,1);
            system("pause");
            break;
           case '5':
             return '1';
            case '6':
             return '2';
        }
     }
  };

 //===========CLASS START INHERITING CLASS PREEMPTIVE AND NON-PREEMPTIVE==============================================

  class start:public preEmptive,public nonPreEmptive
  {
    char ch='0';
    public:
    start()
    {
      {
        cout<<"\n\n\t*******************************************************\n";
        cout<<"\t*                                                     *\n";
        cout<<"\t*\tPROJECT OF OS JOB SCHEDULING IN C++           *\n";
        cout<<"\t*                                                     *\n";
        cout<<"\t*\t     BY SHYAM JEE SINGH                       *\n";
        cout<<"\t*\t            AND                               *\n";
        cout<<"\t*\t        PANKAJ PANDEY                         *\n";
        cout<<"\t*                                                     *\n";
        cout<<"\t*                                                     *\n";
        cout<<"\t*                                                     *\n";
        cout<<"\t*******************************************************\n";
      }
      cout<<endl<<endl;
      system("pause");
    }
    int firstMenu()
    {
      system("cls");
      cout<<"\n\n\n\n\t\t1. SEE ABOUT PROJECT.\n";
      cout<<"\t\t2. ABOUT DEVELOPER.\n";
      cout<<"\t\t3. EXIT\n";
      cout<<"\t\t4. ANY OTHER KEY TO PROCESS JOB SCHEDULING.\n\n";
      cin>>ch;
        switch(ch)
        {
         case '1':
             ch=aboutProject();
              break;
         case '2':
             ch=aboutDeveloper();
             break;
         case '3':
             endProject();
         default:
             while(ch!='1')
             ch=mainMenu();
             ch='0';
        }
        return ch;
    }
    int aboutProject();
    int aboutDeveloper();
    int mainMenu();
    void endProject();
  };

 // ==============================================class start function definition===================================


   int start::aboutDeveloper()
   {
      system("cls");
      cout<<"\n\n\t\t DEVELPOER  DETAIL\n";
      cout<<"\t======================================\n\n";
      cout<<"\t   Developer name 1 :: SHYAM JEE SINGH\n";
      cout<<"\tRegistration number :: 2019PGCACA41\n";
      cout<<"\t   Developer name 2 :: PANKAJ PANDEY\n";
      cout<<"\tRegistration number :: 2019PGCACA42\n";
      cout<<"\t   Developer branch :: MASTER OF COMPUTER APPLICATION\n";
      cout<<"\t           Semester :: 2nd SEMESTER\n";
      cout<<"\t       College Name :: NIT JAMSHEDPUT\n\n";
      system("pause");
      return '0';
   }

   int start::aboutProject()
   {
       system("cls");
       cout<<"PROJECT NAME:: OS JOB SCHEDULING PROCESS.                                          UNDER GUIDENCE OF ASST. PROFESSER.\n";
       cout<<"                                                                                           ALEKHA KUMAR MISHRA\n";
       cout<<"OPERATING SYSTEM: WINDOWS.\n";
       cout<<"       PLATEFORM: CODE BLOCK.\n";
       cout<<"        LANGUAGE: C++.\n";

       cout<<"\n\n\n What is CPU Scheduling?\n====================================\n\tCPU Scheduling is a process of determining which process will own CPU for execution while another process is on\n hold. The main task of CPU scheduling is to make sure that whenever the CPU remains idle, the OS at least select one\n of the processes available in the ready queue for execution. The selection process will be carried out by the CPU\n scheduler. It selects one of the processes in memory that are ready for execution.\n";
       cout<<"\nImportant CPU scheduling Terminologies.\n";
       cout<<"===============================================\n";
       cout<<">> Burst Time/Execution Time: It is a time required by the process to complete execution. It is also called running time.\n";
       cout<<">> Arrival Time: when a process enters in a ready state.\n";
       cout<<">> Multiprogramming: A number of programs which can be present in memory at the same time.\n";
       cout<<">> CPU/IO burst cycle: Characterizes process execution, which alternates between CPU and I/O activity. CPU times are usually shorter than the time of I/O.\n";
       cout<<"\n\nTypes of CPU scheduling Algorithm.\n---------------------------\n\tThere are mainly six types of process scheduling algorithms.\n\n1. First Come First Serve (FCFS)\n2. Shortest-Job-First (SJF) Scheduling\n3. Shortest Remaining Time\n4. Priority Scheduling\n5. Round Robin Scheduling\n6. Multilevel Queue Scheduling\n\n";
       system("pause");
       return '0';
   }

   int start::mainMenu()
   {
       system("cls");
       cout<<"\n\n\tPLEASE CHOOSE ANY TYPE OF JOB SCHEDULING\n\n";
       cout<<"\t1. PRE-EMPTIVE\n";
       cout<<"\t2. NON PRE-EMPTIVE\n";
       cout<<"\t3. BACK TO PREVIOUS MENU\n";
       cout<<"\t>> ANY OTHER KEY TO EXIT\n";
       cin>>ch;
       char a;
       switch(ch)
       {
       case '1':
            a=preEmptive::showMenu();
           break;
       case '2':
            a=nonPreEmptive::showMenu();
           break;
       case '3':
           return '1';
       default:
          endProject();
       }
       if(a=='2')
        endProject();
     return a;
   }

   void start::endProject()
   {
       exit(0);
   }

  // ================================================MAIN FUNCTION===================================================
  int main()
  {
      char n='0';
    start ob;
    while(n=='0')
    {
      n=ob.firstMenu();
    }
    return 0;
  }

  //----------------------------------------------------------------------------------------------------------------------
