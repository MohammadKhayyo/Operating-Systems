# Virtual Memory Management

## Background

Virtual Memory Management is a memory and CPU simulation program that emulates the paging mechanism. Authored by Mohammad Khayyo, this simulator aims to showcase the process of paging out and fetching virtual memory into main memory based on the demands of the CPU.

## Description

The program comprises storage and loading functions that simulate a CPU's read/write mechanism. This simulation utilizes a page table that defines the logic of the physical pages. 

### Key Features:
- **Valid column** in the page table indicates if a particular page is present in memory.
- **Dirty column** is an indicator of whether the page has been modified.
- **Permission column** is used to denote if a page is readable or writable.
- **Frame column** shows the location of the page in the main memory.
- **Swap pointer column** is used to determine where to position the page in the swap file.

The logical address produced by the CPU is separated into two components:
1. Page number
2. Page offset 

Calculations for determining the page size and offset are based on the following formulas respectively:
``` 
page_size = size address / page_size
offset = address % page_size
```

The program functions mainly in the paging style, employing a page table containing five main elements: (V) for Valid, (D) for Dirty, (P) for Permission, (F) for Frame, and (S) for Swap.

## Usage

The following functions are essential for the operation of the simulator:
1. **load()** - Retrieves data from the logical memory to main memory for reading.
2. **store()** - Fetches data from the logical memory to main memory to modify the value.
3. **repetition_count()** - Searches for a page in a non-empty queue and deletes it if found.
4. **WriteThePageToSwap()** - Transfers the page to the swap using the Least Recently Used (LRU) algorithm.
5. **EmptyPlace()** - Returns an empty frame.
6. **print_memory()** - Displays the memory's contents.
7. **print_swap()** - Shows the contents of the swap.
8. **print_page_table()** - Outputs the page table.

A constructor (`sim_mem`) and a destructor (`~sim_mem`) are also provided for managing the simulator's lifecycle.

### Compiling and Running:
To compile and run the program:
```
g++ sim_mem.cpp main.cpp -o main
./main
```

## Program Files

- **sim_mem.h**: Contains the header definitions.
- **sim_mem.cpp**: Houses the implementations of the functions.
- **main.cpp**: The main driver code for the simulator.
