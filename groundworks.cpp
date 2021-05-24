#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
struct Groundwork
{	
	//create the struct Groundwork
	int start_time;
	int duration;
	int end_time;
};
struct Available_Groundworks
{
	// create struct available groundworks
	int n;
	Groundwork gwks[100]; // initialize the array with a large number assuming that n would surely be less than this
};
void sort(Groundwork gwks[], int n){
	// fucntion to sort the array using selection sort
	if(n == 1)
		return; // base condition
	int min_i = 0;
	int min = gwks[0].start_time;
	for(int i =0;i<n;i++){
		// find element with minimum start_time
		if(gwks[i].start_time<min){
			min = gwks[i].start_time;
			min_i = i;
		}
		else if(gwks[i].start_time == min){
			// the function with min duration should come first
			if(gwks[i].duration<gwks[min_i].duration){
				min = gwks[i].start_time;
				min_i = i;
			}
		}
	}
	Groundwork temp = gwks[0];
	gwks[0] = gwks[min_i] ;
	gwks[min_i] = temp;
	sort(&gwks[1],n-1); // recursion, sort the rest of the array

}
Available_Groundworks* initialize (int start_time[], int duration[], int n){
	// initialize an Available_Groundworks object using start_time and duration
	Available_Groundworks* a; 
	a = new Available_Groundworks; // store the object in heap memory
	a->n = n;
	// initialize each groundowork
	for(int i=0;i<n;i++){
		a->gwks[i].start_time = start_time[i];
		a->gwks[i].duration = duration[i];
		a->gwks[i].end_time = start_time[i]+duration[i];
	}
	return a; 
}
int CalculateMaxGroundworks(Available_Groundworks* ptr){
	//function to calculate maximum groundworks that someone can attend
	int n = ptr->n;
	int x = 1;
	int i_last = 0;
	sort(ptr->gwks, n); //sorts the array on basis of start_time and then duration
	for(int i = 1; i<n; i++){
		if(ptr->gwks[i].start_time >= ptr->gwks[i_last].end_time){
			x++;
			i_last = i;
		}
	}
	return x;
}

int main(){
	ifstream infile("Schedule.txt"); // read the input file
	string line;
	int start_time[100];
	int duration[100];
	int n;
	if(infile.is_open()){
		//iterate through each line of input file
		 for(n =0; getline(infile,line); n++){
		 	// extract start_time and duration from each line
		 	start_time[n] = stoi(line.substr(5,6));
		 	duration[n] = stoi(line.substr(8));
       	}
	}
	Available_Groundworks* available;
	available = initialize(start_time, duration, n); // pointer to the initialized Availble_groundworks object
	int x = CalculateMaxGroundworks(available);
	cout << x<<endl;
}