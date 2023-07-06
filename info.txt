What is the program? 

This program outputs the Gantt charts of a specified scheduling algorithm given the arrival time, burst time, and priority of an inputted number of processes. 
It contains the algorithms to run the First Come First Served (FCFS), Shortest Job First (SJF), Non-preemptive Priority (NPP), Shortest Remaining Time First (SRTF), Preemptive Priority (PP), and Round Robin (RR) scheduling algorithms.

How do you run and use the program? 

Some devices may require you to compile the cpp file with c++11 (g++ -std=c++11 CS162A_Project1_Fuentes_Robles_code.cpp -o CS162A_Project1_Fuentes_Robles_code)
After compiling and running the exe, it takes in an int input which will be the number of cases to be inputted. 
Each case will require you to first input an int, which will be the number of processes and a string for the scheduling algorithm to be used (FCFS, SJF, NPP, SRTF, PP, or RR).
Each process will require 3 int inputs which will be the arrival time, burst time, and priority of that process.
It will continue to take inputs until enough test cases are provided.

After receving all the inputs, program will output the number of the current test case and the gantt chart of the processes according to the inputted scheduling algorithm 


What are its functions and operations?

void swap
The swap function takes in two integers and uses a temp variable to store the first integer and swap the positions of the two.

deque<process> sortAscendingDeck: 
sortAscendingDeck takes the deque of processes, the size of the deque, and a string sortBy in order to sort all the processes in the deque.
If sortBy is arrivalTime, it will sort the processes according to ascending arrival time by checking the current minimum arrival time and comparing it to the arrival time of the next processes then swapping the position of the two if the next process has a smaller arrival time than the current minimum.
If sortBy is burstTime, it will sort the processes according to ascending burst time by checking the current minimum burst time and comparing it to the burst time of the next processes then swapping the position of the two if the next process has a smaller burst time than the current minimum.
If sortBy is priority, it will sort the processes according to ascending priority

string output:
the output function takes in the scheduling algorithm to be used, the number of processes to be scheduled, and the quantum time that is used for RR 
We initialize a string chart for the output of the gantt chart, a deque of processes, and integers for the arrival time, burst time, and priority of the processes 
There is a loop to get the arrival time, burst time, and priority of each of the processes and the index of the processes starts at 1 
The if-else statements check which scheduling algorithm to follow, and how this is done will be explained further in the video.
This function returns the gantt chart to be printed

int main:
We initialize an int for the number of test cases and get the input for this, and we also initialize a string answer which will be used to output the Gantt charts of each test case.
For each test case, we have the number of processes and the algorithm to be used. If RR is the inputted algorithm, it also asks for the input of quantum time, otherwise quantum time is always set to 0
For each test case, we then call the output function to get each Gantt chart, and in the end all of them are printed.

