//priority scheduling algorithm (non-premptive)

#include <iostream>
#include <algorithm>
using namespace std;

//process class
class Process{
    public:
        int pid;    //process id
        int art;    //arrival time
        int bt;     //burst time
        int pri;    //priority
        int tat;    //turn around time
        int wt;     //waiting time
        bool status = false;        //status ,if process executed or not
        bool operator<(Process b);  //comparision operator for sorting priority values
};

bool Process::operator<(Process b){
    return (this->pri<b.pri);
}

//priority scheduling (non-premptive)
void priority_sheduling(Process p[],int n){
    int completed = 0;  //initially completed process = 0
    int current_time = 0; //execution starts at t=0
    while(completed!=n){
        Process q[n];   //ready queue at current time
        int l = 0;
        for(int i=0; i<n; i++){
            if(p[i].art<=current_time && !(p[i].status)){
                q[l++] = p[i];
            }
        }
        
        if(l){
            sort(q,q+l); //sort all process in ready queue by priority order
            for(int i=0; i<n; i++){
                if(p[i].pid == q[0].pid){
                    p[i].status = true;
                    current_time+=p[i].bt;
                    completed++;
                    //turn around time
                    p[i].tat = current_time-p[i].art;
                    break;
                }
            }
        }
    }
    //waiting time
    for(int i=0; i<n; i++){
        p[i].wt = p[i].tat - p[i].bt;
    }
}

//main function
int main(){
    int n;
    float avg_wt=0,avg_tat=0;
    cout<<"\nEnter number of process: ";
    cin>>n;
    Process p[n];
    cout<<"Enter Burst time for each process:\n";
    for(int i=0; i<n; i++){
        cout<<"Process P"<<(i+1)<<" : ";
        cin>>p[i].bt;
        p[i].pid = i+1;
    }
    
    cout<<"Enter Arrival time for each process:\n";
    for(int i=0; i<n; i++){
        cout<<"Process P"<<(i+1)<<" : ";
        cin>>p[i].art;
    }
    cout<<"Enter Priority of each process (lower no -> higher priority): \n";
    for(int i=0; i<n; i++){
        cout<<"Process P"<<(i+1)<<" : ";
        cin>>p[i].pri;
    }
    
    priority_sheduling(p,n);
    cout<<"\n\nProcess\t\tArrival time\tBurst time\tPriority\tWaiting time\tTurn around time\n";
    for(int i=0; i<n; i++){
        cout<<p[i].pid<<"\t\t"<<p[i].art<<"\t\t"<<p[i].bt<<"\t\t"<<p[i].pri<<"\t\t"<<p[i].wt<<"\t\t"<<p[i].tat<<"\n";
        avg_tat+=p[i].tat;
        avg_wt+=p[i].wt;
    }
    
    avg_wt/=n;
    avg_tat/=n;
    cout<<"\n\nAverage waiting time:  "<<avg_wt<<"\n";
    cout<<"Average turn around time:  "<<avg_tat<<"\n";
    return 0;
}