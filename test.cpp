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

void testPrint(deque<process> dp, int size) {
	for(int i=0; i<size; i++)
	{
		cout << dp.at(i).arrivalTime << " ";
		cout << dp.at(i).burstTime << " ";
		cout << dp.at(i).priority << " ";
		cout << dp.at(i).index << endl;
	}
	cout << "\n";
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

string output(string algorithm, int numProcesses, int Q){
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
			if (i<numProcesses-1){
				for(int j = 0; j<numProcesses-1;j++){ 
					//if the arrival of the next processes is equal to the current
					if(newProcessDeck.at(j+1).arrivalTime == newProcessDeck.at(j).arrivalTime){
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
	
	else if (algorithm == "SJF"){ //DONE
		//cout << "before:" << endl; 
		//testPrint(processDeck, numProcesses);
		deque<process> newProcessDeck = sortAscendingDeck(processDeck, numProcesses, "arrivalTime");
		int elapsed = newProcessDeck.at(0).arrivalTime;
		//cout << "sorted by arrival" << endl;
		//testPrint(newProcessDeck, numProcesses);
		for(int i = 0; i<numProcesses;i++){
			
			
			//for handling processes w/ same burstTime
			for(process p : newProcessDeck) {
				if (i<numProcesses-1){
					for(int j = 0; j<numProcesses-1;j++){ 
					
						//if the arrivalTime of the next processes is equal to the current
						if(newProcessDeck.at(j+1).arrivalTime == newProcessDeck.at(j).arrivalTime){
							//cout << "hi" << endl;
							//if the BT of the next process is less than the current
							//cout << "bursttime of next: " << newProcessDeck.at(j+1).burstTime;
							//cout << "\nburstime of current: " << newProcessDeck.at(j).burstTime << endl;
							if(newProcessDeck.at(j+1).burstTime < newProcessDeck.at(j).burstTime){
								//cout << "hello" << endl;
								//swap places
								swap(newProcessDeck.at(j+1), newProcessDeck.at(j));
							} 
							else if(newProcessDeck.at(j+1).burstTime == newProcessDeck.at(j).burstTime) {
								if(newProcessDeck.at(j+1).index < newProcessDeck.at(j).index){
									//cout << "yeet" << endl;
									swap(newProcessDeck.at(j+1), newProcessDeck.at(j));
								}
							}
						}
					//cout << "i " << i << " j "<<j << endl;
					//testPrint(newProcessDeck, numProcesses);
					}
					
					
					//if the arrivalTime of the next is less than elapsed
					if(newProcessDeck.at(i+1).arrivalTime < elapsed){ 
						//if the burst of the next is less than the current
						if(newProcessDeck.at(i+1).burstTime < newProcessDeck.at(i).burstTime){ 
							//swap places
							swap(newProcessDeck.at(i+1), newProcessDeck.at(i));
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
		
	else if (algorithm == "NPP"){ //FAILS TEST#2, 3
		cout << "before:" << endl; 
		testPrint(processDeck, numProcesses);
		deque<process> newProcessDeck = sortAscendingDeck(processDeck, numProcesses, "arrivalTime");
		int elapsed = newProcessDeck.at(0).arrivalTime;
		cout << "sorted by arrival" << endl;
		testPrint(newProcessDeck,numProcesses);
		for(int i = 0; i<numProcesses;i++){
			
			//for handling processes w/ same priority
			for(process p : newProcessDeck) {
				
				if (i<numProcesses-1){
					for(int j = 0; j<numProcesses-1;j++){ 
						//if the arrivalTime of the next processes is equal to the current
						if(newProcessDeck.at(j+1).arrivalTime == newProcessDeck.at(j).arrivalTime){
							cout << "hi" << endl;
							cout << "priority of next: " << newProcessDeck.at(j+1).priority;
							cout << "\npriority of current: " << newProcessDeck.at(j).priority << endl;
							//if the priorty of the next process < than the current
							if(newProcessDeck.at(j+1).priority < newProcessDeck.at(j).priority){
								cout << "hello" << endl;
								//swap places
								swap(newProcessDeck.at(j+1), newProcessDeck.at(j));
							} 
							//if there is a tie breaker between priority, use lower index
							else if(newProcessDeck.at(j+1).priority == newProcessDeck.at(j).priority) {
								if(newProcessDeck.at(j+1).index < newProcessDeck.at(j).index){
									cout << "yeet" << endl;
									swap(newProcessDeck.at(j+1), newProcessDeck.at(j));
								}
							}
						}
						else { //SOMETHING HERE 1 5 NPP 6 2 2 11 1 2 5 8 3 8 4 1 7 5 2
							
							//if the next processes arrives before the current processes terminates
							if(newProcessDeck.at(i+1).arrivalTime < elapsed){ 
								
								//if the burst of the next is less than the current
								//WHY ARE WE USING BURST TIME AGAIN??
								if(newProcessDeck.at(i+1).burstTime < newProcessDeck.at(i).burstTime){ 
									//swap places
									cout <<"what"<<endl;
									swap(newProcessDeck.at(i+1), newProcessDeck.at(i));
								}
							}
						}
						
					//if the arrival time of the next process is < elapsed time (arrival + burst)
					//if the priority of the next is < the priority of the current
					//swap
					cout << "i " << i << " j "<<j << endl;
					testPrint(newProcessDeck, numProcesses);
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
	else if (algorithm == "P"){
	
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
	else if (algorithm == "RR") { //DONE (OMG??)
		//ALTERNATE IMPLEMENTATION
		//create another empty deque
		//only go through that stack
		//PUT AT THE BOTTOM OF THE QUEUE
		
		deque<process> newProcessDeck = sortAscendingDeck(processDeck, numProcesses, "arrivalTime");

		//empty "queue"
		deque<process> queue;
		
		testPrint(newProcessDeck, numProcesses);
		
		int elapsed = newProcessDeck.at(0).arrivalTime;
		
		int time = 0;
		
		int i = 0; //0 or 1??
		
		//while there are still processes to run
		while(numProcesses !=0){
			cout << "time: " << time << endl;
			
			//check all the processes
			for(process p : newProcessDeck){
				//if the arrivalTime matches the time that has passed
				if(time == p.arrivalTime){
					p.burstTime +=1; //add 1 to the burst time so that it will "start" in the next cycle
					queue.push_back(p);	 //put it at the end of the queue
				}
			}
			
			//check what's in the queue
			for(process p : queue){
				cout << p.arrivalTime << " " << p.burstTime << " " << p.priority << " " << p.index << endl;
			}
			
			//if the queue has stuff in it
			if (!(queue.empty())) {
				//what's on top?
				cout << "top: " << queue.front().arrivalTime << " " << queue.front().burstTime << " " << queue.front().priority << " " << queue.front().index << endl;
				
				//if it doesn't need to run anymore (can be terminated)
				if(queue.front().burstTime <= 1){ //should be 1 or 0?
					cout << "TERMINATE NEXT CC: " << queue.front().arrivalTime << " " << queue.front().burstTime << " " << queue.front().priority << " " << queue.front().index << endl;
					
					
					//CHART
					chart += to_string(time-i) + " ";
					chart += to_string(queue.front().index) + " ";
					chart += to_string(i) + "X\n";
					
					//remove it 
					queue.pop_front();
					numProcesses--;
					i = 0; //reset the quantam time
					
					//start the next process right away
					queue.front().burstTime -= 1;  
					i++;
				}
				//if it still needs to complete the process
				else{ 
					//if the quantam time hasn't been reached yet
					if(i != Q){
						//let it run (reduce the burst time)
						queue.front().burstTime -= 1;  
						i++;
						
					}
					//if the quantam time has been reached
					else if(i == Q) {
						
						//CHART
						chart += to_string(time-i) + " ";
						chart += to_string(queue.front().index) + " ";
						chart += to_string(i) + "\n";
						
						//remove from the top and move to the bottom
						cout << "STOP! QuantamTime has been reached!" << endl;
						queue.push_back(queue.front()); //get the first element and push to the bottom
						queue.pop_front(); //delete the top
						i = 0; //reset the time
						
						//start the next process right away
						queue.front().burstTime -= 1;  
						i++;
					}
				}
			}
			time++;
			cout << endl;
		}
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
		if (algorithm == "RR"){
			cin >> Q;
			//cout << "Q:" << Q <<endl;
		} 
		
		//cout << numProcesses << " " << algorithm << " " << Q << endl;
		answer += output(algorithm, numProcesses, Q);
	
	}
	cout << answer << "\n\n" << endl;
	return 0;
}
