# CPU Scheduling Simulator

This program outputs the Gantt charts of various scheduling algorithms given the arrival time, burst time, and priority of an inputted number of processes. 
It can simulate scheduling algorithms such as: 
- **First Come First Served (FCFS)**
- **Shortest Job First (SJF)**
- **Non-preemptive Priority (NPP)**
- **Shortest Remaining Time First (SRTF)**
- **Preemptive Priority (PP)**
- **Round-Robin (RR)**

---
# Building

Compile `main.cpp` from the command line using:
```
g++ main.cpp -o main
```

Some devices may require you to compile using a different C++ version. You can specify which version to use using the `std` flag. For example, to compile `main.cpp` using C++11, you would use the command below:
```
g++ -std=c++11 main.cpp -o main
```

---
# Running the Program
To run the program, type the name of the program using the command:
```
main
```

## Using Input/Output Files
If you want to use an input file to run the program, follow the command template below:
```
main < input_file
```

If you would like to use an input and output file to run the program, use the command template below:
```
main < input_file > output_file
```

---
# Input
The program first takes an `int` value representing the number of cases to test. 

The program will then loop through every test case asking for input.

## Test Cases
Each test case requires two inputs:
1. An `int` value representing the number of processes to test
2. A `string` value which specifies which scheduling algorithm to use
   - e.g. `FCFS, SJF, NPP, SRTF, PP, or RR`
3. (optional) An `int` value representing quantum time, the amount of time each process is permitted to run at a given time when using the Round-Robin scheduling algorithm

The program will then loop through every process in the test case, with each loop asking input.

### Processes
Each process requires three `int` values to represent the following information for each process:
1. **Arrival time**, the time the process enters the ready queue
2. **Burst time**, the amount of CPU time required for the process to complete its execution
3. **Priority**, the 'importance' of each process

The program will continue to take inputs until enough information for the test cases and its processes are provided.

After receving all the inputs, the program will output each test case and the Gantt chart of the processes according to the inputted scheduling algorithm. 

---
# What are the program's functions and operations?

## `swap()`
Swaps the places of two processes in a deque (via pass by reference)
- Parameters
  - `xp` - The process x
  - `yp` - The process y
- Returns nothing

## `sortAscendingDeque()`: 
Sorts a deque in ascending order according to the given string
- Parameters
   - `dp` - Deque of processes
   - `size` - Size of the deque
   - `sortBy` - Specifies the method of sorting
      - `arrivalTime` - Sorts the processes according to ascending arrival time
      - `burstTime` - Sorts the processess according to ascending burst time
      - `priority` - Sorts the processes according to ascending priority
- Returns
   -  `dp` - The sorted deque of processes

## `output()`:
Generates a Gantt chart of the processes based on the given scheduling algorithim
- Parameters
   - `algorithm` - Scheduling algorithm to use
   - `numProcesses` - Number of processes to be scheduled
   - `Q` - Quantum time (used for Round-Robin)
- Returns
   - `chart` - A Gantt chart of the processes

## `main()`:
The main method of the program. Refer to the input section above for more information.
