#include <iostream>
#include <cstdio>
#include <deque>

using namespace std;

struct process {
	int arrivalTime; //arrival time into the ready queue
	int	burstTime; //burst time in the CPU
	int priority; //priority of the process
	int index; //index (based off of arrival into ready queue)
};

void swap(int *xp, int *yp) 
{ 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 

//Selection sort 
deque<process> sortAscendingDeck(deque<process> dp, int size, string sortBy){
	//You can sort the processes by arrivalTime, burstTime, or priority
	int i, j, minIndex;
	if(sortBy == "arrivalTime"){
		for(i=0; i<size-1; i++)
		{
			minIndex = i;
			for(j = i+1; j<size; j++){	
				if(dp.at(j).arrivalTime < dp.at(minIndex).arrivalTime)
				{	
					minIndex = j;
				}
			}
			swap(dp.at(minIndex), dp.at(i));
		}
	}
	else if(sortBy == "burstTime"){
		for(i=0; i<size-1; i++)
		{
			minIndex = i;
			for(j = i+1; j<size; j++){	
				if(dp.at(j).burstTime < dp.at(minIndex).burstTime)
				{	
					minIndex = j;
				}
			}
			swap(dp.at(minIndex), dp.at(i));
		}
	}
	else if(sortBy == "priority"){
		for(i=0; i<size-1; i++)
		{
			minIndex = i;
			for(j = i+1; j<size; j++){	
				if(dp.at(j).priority < dp.at(minIndex).priority)
				{	
					minIndex = j;
				}
			}
			swap(dp.at(minIndex), dp.at(i));
		}
	}
	else if(sortBy == "index"){
		for(i=0; i<size-1; i++)
		{
			minIndex = i;
			for(j = i+1; j<size; j++){	
				if(dp.at(j).index < dp.at(minIndex).index)
				{	
					minIndex = j;
				}
			}
			swap(dp.at(minIndex), dp.at(i));
		}
	}
	return dp;
}

string output(string algorithm, int numProcesses){
	string chart;
	
	//make a deck of processes
	deque<process> processDeck (numProcesses); //deck implementation of struct of processes
	
	//take in inputs
	int arrival, burst, priority;
	for(int i = 0; i<numProcesses;i++){
		cin >> arrival;
		cin >> burst;
		cin >> priority;
		
		processDeck.at(i).arrivalTime = arrival;
		processDeck.at(i).burstTime = burst;
		processDeck.at(i).priority = priority;
		processDeck.at(i).index = i+1;
	}

	if (algorithm == "FCFS"){ //DONE	
		deque<process> newProcessDeck = sortAscendingDeck(processDeck, numProcesses, "arrivalTime");

		int elapsed = newProcessDeck.at(0).arrivalTime;
		for(int i = 0; i<numProcesses;i++){
			
			chart += to_string(elapsed) + " "; 
			chart += to_string(newProcessDeck.at(i).index) + " ";
			chart += to_string(newProcessDeck.at(i).burstTime) + "X\n";
			
			//for getting elapsed time
			if (i<numProcesses-1) {
				//if the arrivalTime of the next process is > the elapsed time
				if (newProcessDeck.at(i+1).arrivalTime > elapsed+newProcessDeck.at(i).burstTime){
					elapsed = newProcessDeck.at(i+1).arrivalTime;
				}
				else{
					elapsed += newProcessDeck.at(i).burstTime;
				}
			}
		}
	}
	
	else if (algorithm == "SJF"){
	
	}
	
	else if (algorithm == "SRTF"){ //NOT DONE,,,WTF IS THIS
		deque<process> newProcessDeck = sortAscendingDeck(processDeck, numProcesses, "arrivalTime");

		int elapsed = newProcessDeck.at(0).arrivalTime;
		string cpuTime = "";
		int i = 0;
		while(numProcesses!=0){ //will keep going until all processes have terminated
			
			//if the arrival time of the next processes is < the burst time of the current program 
				//switch to the next process:
					//CPUtime = arrivalTime of the next process
					//update burstTime of current process (current burstTime - arrivalTime)
			
			//if burstTime of current process < arrivalTime of the next	
				//terminate the program: (because it's finished running)
					//CPUtime += X
					//numProcesses-=1
			
			if (newProcessDeck.at(i).burstTime < newProcessDeck.at(i+1).arrivalTime){
				cpuTime += "X";
				numProcesses-=1;
			}
				
			i++;
			
			
		}
			// for(int i = 0; i<numProcesses;i++){
				// cpuTime = to_string(newProcessDeck.at(i).burstTime); //cpuTime = burstTime
				
				// //if the arrival time of the next process is < the burst time of the current program
				// //burst time = arrival time of the next processes
				// //switch to the next process
				
				// if (i<numProcesses-1) { //is not the last process
					// if(newProcessDeck.at(i+1).arrivalTime < newProcessDeck.at(i).burstTime){
						// cout << "arrivalTime of next: " << newProcessDeck.at(i+1).arrivalTime << " < " << " burstTime of current: " << newProcessDeck.at(i).burstTime << endl;
						// newProcessDeck.at(i).burstTime -= newProcessDeck.at(i+1).arrivalTime; //update the remaining burst time
						// cpuTime = to_string(newProcessDeck.at(i+1).arrivalTime); //use arrival time
					// }
				// }
				
				
				// //newProcessDeck.at(i).burstTime += 				
				
				// chart += to_string(elapsed) + " "; 
				// chart += to_string(newProcessDeck.at(i).index) + " ";
				
				// //for getting elapsed time
				// if (i<numProcesses-1) {
					
					// //if the arrivalTime of the next process is > the elapsed time
					// if (newProcessDeck.at(i+1).arrivalTime > elapsed+newProcessDeck.at(i).burstTime){
						
						
						// elapsed = newProcessDeck.at(i+1).arrivalTime;
						
						
						// cpuTime += "X";
						
						// //numProcesses -=1;
					// }
					// else{
						// elapsed += newProcessDeck.at(i).burstTime;
					// }
				// }
				// chart += cpuTime + "\n";
			// }
		
	}
	
	else if (algorithm == "P"){
	
	}
	
	else if (algorithm == "NPP"){ //only works when arrival time is the same			
       		// deque<process> newProcessDeck = sortAscendingDeck(processDeck, numProcesses, "arrivalTime");
			deque<process> newProcessDeck = sortAscendingDeck(processDeck, numProcesses, "priority");
			
			for (process p: newProcessDeck) cout << p.index << endl;
			
			// //for handling arrivalTime
				// for(int j = 0; j<numProcesses-1;j++){ //2 1 3 --> 1 2 3 --> 3 1 2
					// for (process p: newProcessDeck) cout << p.index << endl;
					// if(newProcessDeck.at(j).arrivalTime > newProcessDeck.at(j+1).arrivalTime){
						// swap(newProcessDeck.at(j+1), newProcessDeck.at(j));
					// }
				// }
			

			
			
			
			
			
       		int elapsed = newProcessDeck.at(0).arrivalTime;
			
			//newProcessDeck = sortAscendingDeck(processDeck, numProcesses, "priority");
			
       		for(int i = 0; i<numProcesses;i++){
			
			
				// if (i<numProcesses-1){
					// for (int j = 0; j<numProcesses-1;j++){
						// //if the arrival time of the next process is < arrivalTime of the current 
						// if(newProcessDeck.at(j+1).arrivalTime < newProcessDeck.at(j).arrivalTime){
							// //swap places
							// swap(newProcessDeck.at(j+1), newProcessDeck.at(j));
						// }
					// }
				// }
			
			//for handling processes w/ same priority
			if (i<numProcesses-1){
				for(int j = 0; j<numProcesses-1;j++){ 
					//if the priority of the next processes is equal to the current
					if(newProcessDeck.at(j+1).priority == newProcessDeck.at(j).priority){
						//if the index of the next process is less than the current
						if(newProcessDeck.at(j+1).index < newProcessDeck.at(j).index){
							//swap places
							swap(newProcessDeck.at(j+1), newProcessDeck.at(j));
						}	
					}
				}
			}
			
			chart += to_string(elapsed) + " "; 
			chart += to_string(newProcessDeck.at(i).index) + " ";
			chart += to_string(newProcessDeck.at(i).burstTime) + "X\n";
			
			//for getting elapsed time
			if (i<numProcesses-1) {
				//if the arrivalTime of the next process is > the elapsed time
				if (newProcessDeck.at(i+1).arrivalTime > elapsed+newProcessDeck.at(i).burstTime){
					elapsed = newProcessDeck.at(i+1).arrivalTime;
				}
				else{
					elapsed += newProcessDeck.at(i).burstTime;
				}
			}
		}
	}
	
	else if (algorithm == "RR") {
	
	}
	return chart;
}

int main(){
	int numCases;
	cin >> numCases;
	string answer="";
	
	for(int i = 0; i<numCases;i++){
		int numProcesses; 
		string algorithm;
		int Q = 0; //time splice for RR
		answer += to_string(i+1) + "\n";
		
		cin >> numProcesses;
		cin >> algorithm;
		if (algorithm == "RR") cin >> Q;
		
		//cout << numProcesses << " " << algorithm << " " << Q << endl;
		answer += output(algorithm, numProcesses);
	
	}
	cout << answer << "\n\n" << endl;
	return 0;
}
