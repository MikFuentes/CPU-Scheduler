# Scheduling Algorithms Program

This program outputs the Gantt charts of various scheduling algorithm given the arrival time, burst time, and priority of an inputted number of processes. 
It contains scheduling algorithms such as: 
- **First Come First Served (FCFS)**
- **Shortest Job First (SJF)**
- **Non-preemptive Priority (NPP)**
- **Shortest Remaining Time First (SRTF)**
- **Preemptive Priority (PP)**
- **Round Robin (RR)**

## Building

Compile `main.cpp` from the command line using:
```
g++ main.cpp -o main
```

Some devices may require you to compile using a different C++ version. You can specify which version to use using the `std` flag. For example, to compile `main.cpp` using C++11, you would use the command below:
```
g++ -std=c++11 main.cpp -o main
```

After successfully compiling, open `main.exe` to run the program.

## Input
The program first takes an `int` value representing the number of cases to test.

### Test Cases
Each test case requires two inputs:
1. An `int` value representing the number of processes to test
2. A `string` value which specifies which scheduling algorithm to use
   - e.g. `FCFS, SJF, NPP, SRTF, PP, or RR`

### Processes
Each process requires three `int` values to represent the following information for each process:
1. **Arrival time**, the time the process enters the ready queue
2. **Burst time**, the amount of CPU time required for the process to complete its execution
3. **Priority**, the 'importance' of each process

The program will continue to take inputs until enough test cases are provided.

After receving all the inputs, the program will output each test case and the Gantt chart of the processes according to the inputted scheduling algorithm. 

## What are the program's functions and operations?

### `swap()`
- Parameters
  - `int` pointer
  - `int` pointer
- Returns nothing
The swap function takes in two integers and uses a temp variable to store the first integer and swap the positions of the two.

### deque<process> `sortAscendingDeck()`: 

Takes the deque of processes, the size of the deque, and a string sortBy in order to sort all the processes in the deque.

- Parameters
- `deque dp` - Deque of processes
- `int size` - Size of the deque
- `string sortBy` - Specifies the method of sorting

   - `arrivalTime`: Sorts the processes according to ascending arrival time by 

   - If `sortBy` is `burstTime`, it will sort the processes according to ascending burst time by checking the current minimum burst time and comparing it to the burst time of the next processes then swapping the position of the two if the next process has a smaller burst time than the current minimum.

   - If `sortBy` is `priority`, it will sort the processes according to ascending priority

### string output:
the output function takes in the scheduling algorithm to be used, the number of processes to be scheduled, and the quantum time that is used for RR 
We initialize a string chart for the output of the gantt chart, a deque of processes, and integers for the arrival time, burst time, and priority of the processes 
There is a loop to get the arrival time, burst time, and priority of each of the processes and the index of the processes starts at 1 
The if-else statements check which scheduling algorithm to follow, and how this is done will be explained further in the video.
This function returns the gantt chart to be printed

### int main:
We initialize an int for the number of test cases and get the input for this, and we also initialize a string answer which will be used to output the Gantt charts of each test case.
For each test case, we have the number of processes and the algorithm to be used. If RR is the inputted algorithm, it also asks for the input of quantum time, otherwise quantum time is always set to 0
For each test case, we then call the output function to get each Gantt chart, and in the end all of them are printed.
