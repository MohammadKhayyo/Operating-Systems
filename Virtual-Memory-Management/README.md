# Virtual Memory Management

### Authored by : Mohammad Khayyo

## Description
This exercise is a simulator of the memory and CPU methods, we use the paging mechanism, and virtual memory is paged out and fetched into main memory as needed.
The exercise has a storage and loading function to simulate a CPU read/write, and the exercise uses a page table that defines the logic of the physical pages.

## Functions
This project includes the following functions:
1. `load`
2. `store`
3. `repetition_count`
4. `WriteThePageToSwap`
5. `EmptyPlace`
6. `print_memory`
7. `print_swap`
8. `print_page_table`

## Program Files
- `sim_mem.h`: Contains the header 
- `sim_mem.cpp`: Contains the functions 
- `main.cpp`: Contains the main function

## Compilation Steps
1. Compile: `g++ sim_mem.cpp main.cpp -o main`
2. Run: `./main`

## Output
Output includes physical memory, swap memory, and page table information. 


 Physical memory
[P]
[Q]
[P]
[P]
[P]
[c]
[c]
[c]
[c]
[c]

 Swap memory
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	

 page table 
Valid	 Dirty	 Permission 	 Frame	 Swap index
[0]		[0]			[0]			[-1]		[-1]
[0]		[0]			[0]			[-1]		[-1]
[1]		[1]			[1]			[0]		[-1]
[1]		[0]			[1]			[1]		[-1]
[0]		[0]			[1]			[-1]		[-1]
[0]		[0]			[1]			[-1]		[-1]
[0]		[0]			[1]			[-1]		[-1]

 Physical memory
[0]
[0]
[k]
[0]
[0]
[0]
[0]
[X]
[0]
[0]

 Swap memory
0 - [P]	1 - [Q]	2 - [P]	3 - [P]	4 - [P]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	

 page table 
Valid	 Dirty	 Permission 	 Frame	 Swap index
[0]		[0]			[0]			[-1]		[-1]
[0]		[0]			[0]			[-1]		[-1]
[0]		[1]			[1]			[-1]		[0]
[0]		[0]			[1]			[-1]		[-1]
[0]		[0]			[1]			[-1]		[-1]
[1]		[1]			[1]			[1]		[-1]
[1]		[1]			[1]			[0]		[-1]

 Physical memory
[b]
[b]
[b]
[b]
[b]
[P]
[Q]
[P]
[P]
[P]

 Swap memory
0 - [0]	1 - [0]	2 - [X]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [k]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	

 page table 
Valid	 Dirty	 Permission 	 Frame	 Swap index
[0]		[0]			[0]			[-1]		[-1]
[1]		[0]			[0]			[0]		[-1]
[1]		[1]			[1]			[1]		[-1]
[0]		[0]			[1]			[-1]		[-1]
[0]		[0]			[1]			[-1]		[-1]
[0]		[1]			[1]			[-1]		[0]
[0]		[1]			[1]			[-1]		[1]

 Physical memory
[0]
[0]
[k]
[0]
[k]
[0]
[0]
[x]
[0]
[0]

 Swap memory
0 - [P]	1 - [Q]	2 - [P]	3 - [P]	4 - [P]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	

 page table 
Valid	 Dirty	 Permission 	 Frame	 Swap index
[0]		[0]			[0]			[-1]		[-1]
[0]		[0]			[0]			[-1]		[-1]
[0]		[1]			[1]			[-1]		[0]
[0]		[0]			[1]			[-1]		[-1]
[0]		[0]			[1]			[-1]		[-1]
[1]		[1]			[1]			[1]		[-1]
[1]		[1]			[1]			[0]		[-1]

 Physical memory
[b]
[b]
[b]
[b]
[b]
[P]
[Q]
[P]
[P]
[P]

 Swap memory
0 - [0]	1 - [0]	2 - [x]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [k]	3 - [0]	4 - [k]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	
0 - [0]	1 - [0]	2 - [0]	3 - [0]	4 - [0]	

 page table 
Valid	 Dirty	 Permission 	 Frame	 Swap index
[0]		[0]			[0]			[-1]		[-1]
[1]		[0]			[0]			[0]		[-1]
[1]		[1]			[1]			[1]		[-1]
[0]		[0]			[1]			[-1]		[-1]
[0]		[0]			[1]			[-1]		[-1]
[0]		[1]			[1]			[-1]		[0]
[0]		[1]			[1]			[-1]		[1]


