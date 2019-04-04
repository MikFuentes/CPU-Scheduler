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
		
		//check for any ties in arrival and rearrange according to lower index
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

		//empty "queue"
		deque<process> queue;
		
		//testPrint(newProcessDeck, numProcesses);
		
		int elapsed = newProcessDeck.at(0).arrivalTime;
		
		int time = 0;
		
		int i = 0; //0 or 1??
		
		//while there are still processes to run
		while(numProcesses !=0){
			//cout << "time: " << time << endl;
			
			//check all the processes
			for(process p : newProcessDeck){
				//if the arrivalTime matches the time that has passed
				if(time == p.arrivalTime){
					p.burstTime +=1; //add 1 to the burst time so that it will "start" in the next cycle
					queue.push_back(p);	 //put it at the end of the queue
				}
			}
			
			// //check what's in the queue
			// for(process p : queue){
				// cout << p.arrivalTime << " " << p.burstTime << " " << p.priority << " " << p.index << endl;
			// }
			
			//if the queue has stuff in it
			if (!(queue.empty())) {
				//what's on top?
				// cout << "top: " << queue.front().arrivalTime << " " << queue.front().burstTime << " " << queue.front().priority << " " << queue.front().index << endl;
				
				//if it doesn't need to run anymore (can be terminated)
				if(queue.front().burstTime <= 1){ //should be 1 or 0?
					// cout << "TERMINATE NEXT CC: " << queue.front().arrivalTime << " " << queue.front().burstTime << " " << queue.front().priority << " " << queue.front().index << endl;
					
					//CHART
					chart += to_string(time-i) + " ";
					chart += to_string(queue.front().index) + " ";
					chart += to_string(i) + "X\n";
					
					//remove it 
					queue.pop_front();
					numProcesses--;
					i = 0; //reset the quantum time
					
					//if the queue is STILL not emtpy...
					if(!(queue.empty())) { 
						//start the next process right away
						queue.front().burstTime -= 1;  
						i++;
					}
				}
				//if it still needs to complete the process
				else{ 
					//let it run (reduce the burst time)
					queue.front().burstTime -= 1;  
					i++;
				}
			}
			time++;
			// cout << endl;
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
		
	else if (algorithm == "NPP"){ //DONE?
		deque<process> newProcessDeck = sortAscendingDeck(processDeck, numProcesses, "arrivalTime");

		// testPrint(newProcessDeck, numProcesses);
		
		for (process p: newProcessDeck) {
			//check for any ties in arrival and rearrange according to lower priority, if tie in priority, lower index
			for(int j = 0; j<numProcesses-1;j++){ 
				//if the arrival of the next processes is equal to the current
				if(newProcessDeck.at(j+1).arrivalTime == newProcessDeck.at(j).arrivalTime){
					//if the priority is equal to the current
					if(newProcessDeck.at(j+1).priority == newProcessDeck.at(j).priority) {
						//if the index of the next process is less than the current
						if(newProcessDeck.at(j+1).index < newProcessDeck.at(j).index){
							//swap places
							swap(newProcessDeck.at(j+1), newProcessDeck.at(j));
						}	
					} //if the priority of the next is less than the current
					else if (newProcessDeck.at(j+1).priority < newProcessDeck.at(j).priority){
						//swap places
						swap(newProcessDeck.at(j+1), newProcessDeck.at(j));
					}
				}
			}
		}
		
		//empty "queue"
		deque<process> queue;
		
		// testPrint(newProcessDeck, numProcesses);
		
		int elapsed = newProcessDeck.at(0).arrivalTime;
		
		int time = 0;
		
		int i = 0; //0 or 1??
		
		// bool run;
		
		//while there are still processes to run
		while(numProcesses !=0){
			// cout << "time: " << time << endl;
			// cout << "i: " << to_string(i) << endl;
			//check all the processes
			for(process p : newProcessDeck){
				//if the arrivalTime matches the time that has passed
				if(time == p.arrivalTime){					
					p.burstTime +=1; //add 1 to the burst time so that it will "start" in the next cycle
					queue.push_back(p);	 //put it at the end of the queue		
				}
			}
			
			// //check what's in the queue
			// for(process p : queue){
				// cout << p.arrivalTime << " " << p.burstTime << " " << p.priority << " " << p.index << endl;
			// }
			
			//if the queue has stuff in it
			if (!(queue.empty())) {
				//what's on top?
				
				// cout << "top: " << queue.front().arrivalTime << " " << queue.front().burstTime << " " << queue.front().priority << " " << queue.front().index << endl;
				
				//if it doesn't need to run anymore (can be terminated)
				if(queue.front().burstTime <= 1){ //should be 1 or 0?
					// cout << "TERMINATE NEXT CC: " << queue.front().arrivalTime << " " << queue.front().burstTime << " " << queue.front().priority << " " << queue.front().index << endl;
					// cout << "ELAPSED: " << to_string(time-i) << endl;
					// cout << "INDEX: " << to_string(queue.front().index) << endl;
					// cout << "BURST TIME: " << to_string(i) << endl;
					
					//CHART
					chart += to_string(time-i) + " ";
					chart += to_string(queue.front().index) + " ";
					chart += to_string(i) + "X\n";
					
					//remove it 
					queue.pop_front();
					numProcesses--;
					i = 0; //reset the time
					
					//if the queue is STILL not emtpy...
					if(!(queue.empty())) { 
						
						//re-sort the queue according to priority
						for(process p : queue) {
							//rearrange according to lower priority, if tie in priority, lower index
							for(int j = 0; j<queue.size()-1;j++){ 
							
								//if the priority of the next is less than the current
								if (queue.at(j+1).priority < queue.at(j).priority){
									//swap places
									swap(queue.at(j+1), queue.at(j));
								}
							
								//if the priority is equal to the current
								else if(queue.at(j+1).priority == queue.at(j).priority) {
									//if the index of the next process is less than the current
									if(queue.at(j+1).index < queue.at(j).index){
										//swap places
										swap(queue.at(j+1), queue.at(j));
									}	
								}
							}
						}
					
						//start the next process right away
						queue.front().burstTime -= 1;  
						i++;
					}
				}
				//if it still needs to complete the process
				else{ 
					//let it run (reduce the burst time)
					queue.front().burstTime -= 1; 
					i++;
				}
			}
			time++;
			// cout << endl;
		}	
	
		//OLD IMPLEMENTATION
		
		// //cout << "before:" << endl; 
		// //testPrint(processDeck, numProcesses);
		// deque<process> newProcessDeck = sortAscendingDeck(processDeck, numProcesses, "arrivalTime");
		// int elapsed = newProcessDeck.at(0).arrivalTime;
		// //cout << "sorted by arrival" << endl;
		// //testPrint(newProcessDeck,numProcesses);
		// for(int i = 0; i<numProcesses;i++){
			
			// //for handling processes w/ same priority
			// for(process p : newProcessDeck) {
				
				// if (i<numProcesses-1){
					// for(int j = 0; j<numProcesses-1;j++){ 
						// //if the arrivalTime of the next processes is equal to the current
						// if(newProcessDeck.at(j+1).arrivalTime == newProcessDeck.at(j).arrivalTime){
							// //cout << "hi" << endl;
							// //cout << "priority of next: " << newProcessDeck.at(j+1).priority;
							// //cout << "\npriority of current: " << newProcessDeck.at(j).priority << endl;
							// //if the priorty of the next process < than the current
							// if(newProcessDeck.at(j+1).priority < newProcessDeck.at(j).priority){
								// //cout << "hello" << endl;
								// //swap places
								// swap(newProcessDeck.at(j+1), newProcessDeck.at(j));
							// } 
							// //if there is a tie breaker between priority, use lower index
							// else if(newProcessDeck.at(j+1).priority == newProcessDeck.at(j).priority) {
								// if(newProcessDeck.at(j+1).index < newProcessDeck.at(j).index){
									// //cout << "yeet" << endl;
									// swap(newProcessDeck.at(j+1), newProcessDeck.at(j));
								// }
							// }
						// }
						// else {
							
							// //if the next processes arrives before the current processes terminates
							// if(newProcessDeck.at(i+1).arrivalTime < elapsed){ 
								
								// //if the burst of the next is less than the current
								// //WHY ARE WE USING BURST TIME AGAIN??
								// if(newProcessDeck.at(i+1).priority < newProcessDeck.at(i).priority){ 
									// //swap places
									// //cout <<"what"<<endl;
									// swap(newProcessDeck.at(i+1), newProcessDeck.at(i));
								// }
							// }
						// }
						
					// //if the arrival time of the next process is < elapsed time (arrival + burst)
					// //if the priority of the next is < the priority of the current
					// //swap
					// //cout << "i " << i << " j "<<j << endl;
					// //testPrint(newProcessDeck, numProcesses);
					// }
				// }
			// }
			
			// chart += to_string(elapsed) + " "; 
			// chart += to_string(newProcessDeck.at(i).index) + " ";
			// chart += to_string(newProcessDeck.at(i).burstTime) + "X\n";
			
			// //for getting elapsed time
			// if (i<numProcesses-1) {
				// //if the arrivalTime of the next process is > the elapsed time
				// if (newProcessDeck.at(i+1).arrivalTime > elapsed+newProcessDeck.at(i).burstTime){
					// elapsed = newProcessDeck.at(i+1).arrivalTime;
				// }
				// else{
					// elapsed += newProcessDeck.at(i).burstTime;
				// }
			// }
		// }
	}
	
	else if (algorithm == "PP"){ //DONE
		deque<process> newProcessDeck = sortAscendingDeck(processDeck, numProcesses, "arrivalTime");

		//check for any ties in arrival and rearrange according to lower burstTime, if tie in burstTime, lower index
		for(int j = 0; j<numProcesses-1;j++){ 
			//if the arrival of the next processes is equal to the current
			if(newProcessDeck.at(j+1).arrivalTime == newProcessDeck.at(j).arrivalTime){
				//if the priority is equal to the current
				if(newProcessDeck.at(j+1).priority == newProcessDeck.at(j).priority) {
					//if the index of the next process is less than the current
					if(newProcessDeck.at(j+1).index < newProcessDeck.at(j).index){
						//swap places
						swap(newProcessDeck.at(j+1), newProcessDeck.at(j));
					}	
				} //if the priority of the next is less than the current
				else if (newProcessDeck.at(j+1).priority < newProcessDeck.at(j).priority){
					//swap places
					swap(newProcessDeck.at(j+1), newProcessDeck.at(j));
				}
			}
		}
		
		//empty "queue"
		deque<process> queue;
		
		// testPrint(newProcessDeck, numProcesses);
		
		int elapsed = newProcessDeck.at(0).arrivalTime;
		
		int time = 0;
		
		int i = 0; //0 or 1??
		
		bool run;
		
		//while there are still processes to run
		while(numProcesses !=0){
			cout << "time: " << time << endl;
			cout << "i: " << to_string(i) << endl;
			//check all the processes
			for(process p : newProcessDeck){
				//if the arrivalTime matches the time that has passed
				if(time == p.arrivalTime){					
					p.burstTime +=1; //add 1 to the burst time so that it will "start" in the next cycle
					queue.push_back(p);	 //put it at the end of the queue		
				}
			}
			
			// //check what's in the queue
			// for(process p : queue){
				// cout << p.arrivalTime << " " << p.burstTime << " " << p.priority << " " << p.index << endl;
			// }
			
			//if the queue has stuff in it
			if (!(queue.empty())) {
				//what's on top?
				
				// cout << "top: " << queue.front().arrivalTime << " " << queue.front().burstTime << " " << queue.front().priority << " " << queue.front().index << endl;
				
				//if it doesn't need to run anymore (can be terminated)
				if(queue.front().burstTime <= 1){ //should be 1 or 0?
					// cout << "TERMINATE NEXT CC: " << queue.front().arrivalTime << " " << queue.front().burstTime << " " << queue.front().priority << " " << queue.front().index << endl;
					// cout << "ELAPSED: " << to_string(time-i) << endl;
					// cout << "INDEX: " << to_string(queue.front().index) << endl;
					// cout << "BURST TIME: " << to_string(i) << endl;
					
					//CHART
					chart += to_string(time-i) + " ";
					chart += to_string(queue.front().index) + " ";
					chart += to_string(i) + "X\n";
					
					//remove it 
					queue.pop_front();
					numProcesses--;
					i = 0; //reset the time
					
					//if the queue is STILL not emtpy...
					if(!(queue.empty())) { 
						
						//re-sort the queue according to priority
						for(process p : queue) {
							//rearrange according to lower priority, if tie in priority, lower index
							for(int j = 0; j<queue.size()-1;j++){ 
							
								//if the priority of the next is less than the current
								if (queue.at(j+1).priority < queue.at(j).priority){
									//swap places
									swap(queue.at(j+1), queue.at(j));
								}
							
								//if the priority is equal to the current
								else if(queue.at(j+1).priority == queue.at(j).priority) {
									//if the index of the next process is less than the current
									if(queue.at(j+1).index < queue.at(j).index){
										//swap places
										swap(queue.at(j+1), queue.at(j));
									}	
								}
							}
						}
					
						//start the next process right away
						queue.front().burstTime -= 1;  
						i++;
					}
				}
				//if it still needs to complete the process
				else{ 
					//if there are at least two
					if(queue.size()>=2) {
						//check what's in the queue
						for(process p : queue){
							//if there aren't any other processes in the "queue" w/ a lower priority number
							if(queue.front().priority < p.priority){
								//it is allowed to run
								run = true;
							}
							//if there are processes w/ a lower priority number than the current
							else if(queue.front().priority > p.priority){
								//it is NOT allowed to run
								run = false;
							}
							//if there is a tie between priority
							else if(queue.front().priority == p.priority){
								//if the index of the process is lower than the current
								if(queue.front().index > p.index){
									//it is NOT allowed to run
									run = false;
								}
							}
						}
					}
					else if (queue.size()==1){ //if there is only one
						run = true;
					}
					
					//if there aren't any other processes in the "queue" w/ a shorter burst time
					if(run){ //or there is only 1 process
						//let it run (reduce the burst time)
						queue.front().burstTime -= 1; 
						i++;
						
					}
					//if there are processes w/ a shorter burst time than the current
					else if(!(run)) {
						
						//CHART
						chart += to_string(time-i) + " ";
						chart += to_string(queue.front().index) + " ";
						chart += to_string(i) + "\n";
						
						//remove from the top and move to the bottom
						// << "STOP! NO LONGER SHORTEST REMAINING BURST TIME IN THE QUEUE" << endl;
						//cout << "ELAPSED: " << to_string(time-i) << endl;
						//cout << "INDEX: " << to_string(queue.front().index) << endl;
						//cout << "BURST TIME: " << to_string(i) << endl;
						
						queue.push_back(queue.front()); //get the first element and push to the bottom
						queue.pop_front(); //delete the top
						i = 0; //reset the time
						
						
						//if there are at least two
						if(queue.size()>=2) {
							//re-sort the queue according to priority
							for(process p : queue) {
								//rearrange according to lower priority, if tie in priority, lower index
								for(int j = 0; j<queue.size()-1;j++){ 
								
									//if the priority of the next is less than the current
									if (queue.at(j+1).priority < queue.at(j).priority){
										//swap places
										swap(queue.at(j+1), queue.at(j));
									}
								
									//if the priority is equal to the current
									else if(queue.at(j+1).priority == queue.at(j).priority) {
										//if the index of the next process is less than the current
										if(queue.at(j+1).index < queue.at(j).index){
											//swap places
											swap(queue.at(j+1), queue.at(j));
										}	
									}
								}
							}
						}
							
						//start the next process right away
						queue.front().burstTime -= 1;  
						i++;
					}
				}
			}
			time++;
			// cout << endl;
		}	
	}
	
	else if (algorithm == "SRTF"){ //DONE
		deque<process> newProcessDeck = sortAscendingDeck(processDeck, numProcesses, "arrivalTime");

		//check for any ties in arrival and rearrange according to lower burstTime, if tie in burstTime, lower index
		for(int j = 0; j<numProcesses-1;j++){ 
			//if the arrival of the next processes is equal to the current
			if(newProcessDeck.at(j+1).arrivalTime == newProcessDeck.at(j).arrivalTime){
				//if the burstTime is equal to the current
				if(newProcessDeck.at(j+1).burstTime == newProcessDeck.at(j).burstTime) {
					//if the index of the next process is less than the current
					if(newProcessDeck.at(j+1).index < newProcessDeck.at(j).index){
						//swap places
						swap(newProcessDeck.at(j+1), newProcessDeck.at(j));
					}	
				}
				//if the burstTime is equal to the current
				else if(newProcessDeck.at(j+1).burstTime < newProcessDeck.at(j).burstTime){
					swap(newProcessDeck.at(j+1), newProcessDeck.at(j));
				}
			}
		}
		
		//empty "queue"
		deque<process> queue;
		
		//testPrint(newProcessDeck, numProcesses);
		
		int elapsed = newProcessDeck.at(0).arrivalTime;
		
		int time = 0;
		
		int i = 0; //0 or 1??
		
		bool run;
		
		//while there are still processes to run
		while(numProcesses !=0){
			//cout << "time: " << time << endl;
			//cout << "i: " << to_string(i) << endl;
			//check all the processes
			for(process p : newProcessDeck){
				//if the arrivalTime matches the time that has passed
				if(time == p.arrivalTime){					
					p.burstTime +=1; //add 1 to the burst time so that it will "start" in the next cycle
					queue.push_back(p);	 //put it at the end of the queue
					
				}
			}
						
			// //check what's in the queue
			// for(process p : queue){
				// cout << p.arrivalTime << " " << p.burstTime << " " << p.priority << " " << p.index << endl;
			// }
			
			//if the queue has stuff in it
			if (!(queue.empty())) {
				//what's on top?
				
				//cout << "top: " << queue.front().arrivalTime << " " << queue.front().burstTime << " " << queue.front().priority << " " << queue.front().index << endl;
				
				//if it doesn't need to run anymore (can be terminated)
				if(queue.front().burstTime <= 1){ //should be 1 or 0?
					// cout << "TERMINATE NEXT CC: " << queue.front().arrivalTime << " " << queue.front().burstTime << " " << queue.front().priority << " " << queue.front().index << endl;
					// cout << "ELAPSED: " << to_string(time-i) << endl;
					// cout << "INDEX: " << to_string(queue.front().index) << endl;
					// cout << "BURST TIME: " << to_string(i) << endl;
					
					//CHART
					chart += to_string(time-i) + " ";
					chart += to_string(queue.front().index) + " ";
					chart += to_string(i) + "X\n";
					
					//remove it 
					queue.pop_front();
					numProcesses--;
					i = 0; //reset the time
					
					//if the queue is STILL not emtpy...
					if(!(queue.empty())) { 
						
						//re-sort the queue according to burst
						for(process p : queue) {
							//rearrange according to lower burstTime, if tie in burstTime, lower index
							for(int j = 0; j<queue.size()-1;j++){ 
							
								//if the bursttime of the next is less than the current
								if (queue.at(j+1).burstTime < queue.at(j).burstTime){
									//swap places
									swap(queue.at(j+1), queue.at(j));
								}
							
								//if the burstTime is equal to the current
								else if(queue.at(j+1).burstTime == queue.at(j).burstTime) {
									//if the index of the next process is less than the current
									if(queue.at(j+1).index < queue.at(j).index){
										//swap places
										swap(queue.at(j+1), queue.at(j));
									}	
								}
							}
						}
					
						//start the next process right away
						queue.front().burstTime -= 1;  
						i++;
					}
				}
				//if it still needs to complete the process
				else{ 
					//if there are at least two
					if(queue.size()>=2) {
						//check what's in the queue
						for(process p : queue){
							//if there aren't any other processes in the "queue" w/ a shorter burst time
							if(queue.front().burstTime < p.burstTime){
								//it is allowed to run
								run = true;
							}
							//if there are processes w/ a shorter burst time than the current
							else if(queue.front().burstTime > p.burstTime){
								//it is NOT allowed to run
								run = false;
							}
							//if there is a tie between burst time
							else if(queue.front().burstTime == p.burstTime){
								//if the index of the process is lower than the current
								if(queue.front().index > p.index){
									//it is NOT allowed to run
									run = false;
								}
							}
						}
					}
					else if (queue.size()==1){ //if there is only one
						run = true;
					}
					
					//if there aren't any other processes in the "queue" w/ a shorter burst time
					if(run){ //or there is only 1 process
						//let it run (reduce the burst time)
						queue.front().burstTime -= 1; 
						i++;
						
					}
					//if there are processes w/ a shorter burst time than the current
					else if(!(run)) {
						
						//CHART
						chart += to_string(time-i) + " ";
						chart += to_string(queue.front().index) + " ";
						chart += to_string(i) + "\n";
						
						//remove from the top and move to the bottom
						// cout << "STOP! NO LONGER SHORTEST REMAINING BURST TIME IN THE QUEUE" << endl;
						// cout << "ELAPSED: " << to_string(time-i) << endl;
						// cout << "INDEX: " << to_string(queue.front().index) << endl;
						// cout << "BURST TIME: " << to_string(i) << endl;
						
						queue.push_back(queue.front()); //get the first element and push to the bottom
						queue.pop_front(); //delete the top
						i = 0; //reset the time
						
						
						//if there are at least two
						if(queue.size()>=2) {
							//re-sort the queue according to burst
							for(process p : queue) {
								//rearrange according to lower burstTime, if tie in burstTime, lower index
								for(int j = 0; j<queue.size()-1;j++){ 
								
									//if the bursttime of the next is less than the current
									if (queue.at(j+1).burstTime < queue.at(j).burstTime){
										//swap places
										swap(queue.at(j+1), queue.at(j));
									}
								
									//if the burstTime is equal to the current
									else if(queue.at(j+1).burstTime == queue.at(j).burstTime) {
										//if the index of the next process is less than the current
										if(queue.at(j+1).index < queue.at(j).index){
											//swap places
											swap(queue.at(j+1), queue.at(j));
										}	
									}
								}
							}
						}
						
							
						//start the next process right away
						queue.front().burstTime -= 1;  
						i++;
					}
				}
			}
			time++;
			// cout << endl;
		}	
	}
	else if (algorithm == "RR") { //DONE (OMG??)
		
		deque<process> newProcessDeck = sortAscendingDeck(processDeck, numProcesses, "arrivalTime");
		
		//check for any ties in arrival and rearrange according to lower index
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

		//empty "queue"
		deque<process> queue;
		
		// testPrint(newProcessDeck, numProcesses);
		
		int elapsed = newProcessDeck.at(0).arrivalTime;
		
		int time = 0;
		
		int i = 0; //0 or 1??
		
		//while there are still processes to run
		while(numProcesses !=0){
			// cout << "time: " << time << endl;
			
			//check all the processes
			for(process p : newProcessDeck){
				//if the arrivalTime matches the time that has passed
				if(time == p.arrivalTime){
					p.burstTime +=1; //add 1 to the burst time so that it will "start" in the next cycle
					queue.push_back(p);	 //put it at the end of the queue
				}
			}
			
			// // //check what's in the queue
			// for(process p : queue){
				// cout << p.arrivalTime << " " << p.burstTime << " " << p.priority << " " << p.index << endl;
			// }
			
			//if the queue has stuff in it
			if (!(queue.empty())) {
				//what's on top?
				// cout << "top: " << queue.front().arrivalTime << " " << queue.front().burstTime << " " << queue.front().priority << " " << queue.front().index << endl;
				
				//if it doesn't need to run anymore (can be terminated)
				if(queue.front().burstTime <= 1){ //should be 1 or 0?
					// cout << "TERMINATE NEXT CC: " << queue.front().arrivalTime << " " << queue.front().burstTime << " " << queue.front().priority << " " << queue.front().index << endl;
					
					//CHART
					chart += to_string(time-i) + " ";
					chart += to_string(queue.front().index) + " ";
					chart += to_string(i) + "X\n";
					
					//remove it 
					queue.pop_front();
					numProcesses--;
					i = 0; //reset the quantum time
					
					
					//if the queue is STILL not emtpy...
					if(!(queue.empty())) { 
						//start the next process right away
						queue.front().burstTime -= 1;  
						i++;
					}
				}
				//if it still needs to complete the process
				else{ 
					//if the quantum time hasn't been reached yet
					if(i != Q){
						//let it run (reduce the burst time)
						queue.front().burstTime -= 1;  
						i++;
						
					}
					//if the quantum time has been reached
					else if(i == Q) {
						
						//CHART
						chart += to_string(time-i) + " ";
						chart += to_string(queue.front().index) + " ";
						chart += to_string(i) + "\n";
						
						//remove from the top and move to the bottom
						cout << "STOP! quantumTime has been reached!" << endl;
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
			// cout << endl;
		}
	}
	return chart;
}

int main(){
	int numCases;
	cin >> numCases;
	string answer="\n";
	
	for(int i = 0; i<numCases;i++){
		int numProcesses; 
		string algorithm;
		int Q = 0; //time splice for RR
		answer += to_string(i+1) + "\n";
		
		cin >> numProcesses;
		cin >> algorithm;
		if (algorithm == "RR"){
			cin >> Q;
		} 
		
		answer += output(algorithm, numProcesses, Q);
	}
	cout << answer << "\n\n" << endl;
	return 0;
}
