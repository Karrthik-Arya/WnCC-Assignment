#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
struct Groundwork
{
	int start_time;
	int duration;
	int end_time;
};
struct Available_Groundworks
{
	int n;
	Groundwork gwks[100];
};
void sort(Groundwork gwks[], int n){
	if(n == 1)
		return;
	int min_i = 0;
	int min = gwks[0].start_time;
	for(int i =0;i<n;i++){
		if(gwks[i].start_time<min){
			min = gwks[i].start_time;
			min_i = i;
		}
		else if(gwks[i].start_time == min){
			if(gwks[i].duration<gwks[min_i].duration){
				min = gwks[i].start_time;
				min_i = i;
			}
		}
	}
	Groundwork temp = gwks[0];
	gwks[0] = gwks[min_i] ;
	gwks[min_i] = temp;
	sort(&gwks[1],n-1);

}
Available_Groundworks* initialize (int start_time[], int duration[], int n){
	Available_Groundworks* a;
	a = new Available_Groundworks;
	a->n = n;
	for(int i=0;i<n;i++){
		a->gwks[i].start_time = start_time[i];
		a->gwks[i].duration = duration[i];
		a->gwks[i].end_time = start_time[i]+duration[i];
	}
	return a;
}
int CalculateMaxGroundworks(Available_Groundworks* ptr){
	int n = ptr->n;
	int x = 1;
	int i_last = 0;
	sort(ptr->gwks, n);
	for(int i=0;i<n;i++){
		cout<<ptr->gwks[i].start_time<<" "<<ptr->gwks[i].end_time<<endl;
	}
	for(int i = 1; i<n; i++){
		if(ptr->gwks[i].start_time >= ptr->gwks[i_last].end_time){
			x++;
			i_last = i;
		}
	}
	return x;
}

int main(){
	ifstream infile("Schedule.txt");
	string line;
	int start_time[100];
	int duration[100];
	int n;
	if(infile.is_open()){
		 for(n =0; getline(infile,line); n++){
		 	start_time[n] = stoi(line.substr(5,6));
		 	duration[n] = stoi(line.substr(8));
       	}
	}
	Available_Groundworks* available;
	available = initialize(start_time, duration, n);
	int x = CalculateMaxGroundworks(available);
	cout << x;
}