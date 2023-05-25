# Mini Shell

## Authored by: Mohammad Khayyo

## Description

### ex2a: What is a shell?

A shell is an interface program that reads commands from the user and transmits them in a format suitable for the operating system to execute.

In the first part of this exercise, we implement a mini shell in the C language under the Linux operating system. The shell will display a prompt for the user, read the commands, and then send them to the operating system for execution.

### ex2b:

In the second part, the shell operates similarly, but before each command, it prints to the screen the scheduler information for the same process that runs it.

## Functions

The program has 5 functions:

1. `howManyWords`: This method calculates how many words we entered through the string.

2. `TheNumberOfLettersInEachWord`: This method cuts the sentence into words and calculates how many letters are in them.

3. `freeDynamicAllocation`: This method frees the memory of all allocations.

4. `Process`: This method takes the shell command and activates it.

5. `Prompt`: This method gets the prompt.

## Program Files

1. `ex2a.c`: The first part. Contains the main function and other functions.

2. `ex2b.c`: The second part. Contains the main function and other functions.

## How to Compile?

### First Part

Compile: `gcc ex2a.c -o ex2a`
Run: `./ex2a`

### Second Part

Compile: `gcc ex2b.c -o ex2b`
Run: `./ex2b`

## Input

### First Part (ex2a)

Input: `echo Hello,it's me`

Output: `Hello,it's me`

### Second Part (ex2b)

Input: `echo Hello,it's me`

Output:

## memcheck-amd64- (8814, #threads: 1)

se.exec_start : 10677793.083491
se.vruntime : 922574.952583
se.sum_exec_runtime : 10.497828
se.nr_migrations : 1
nr_switches : 3
nr_voluntary_switches : 1
nr_involuntary_switches : 2
se.load.weight : 1048576
se.runnable_weight : 1048576
se.avg.load_sum : 46696
se.avg.runnable_load_sum : 46696
se.avg.util_sum : 26556984
se.avg.load_avg : 1023
se.avg.runnable_load_avg : 1023
se.avg.util_avg : 568
se.avg.last_update_time : 10677793083392
se.avg.util_est.ewma : 142
se.avg.util_est.enqueued : 569
policy : 0
prio : 120
clock-delta : 21
mm->numa_scan_seq : 0
numa_pages_migrated : 0
numa_preferred_nid : -1
total_numa_faults : 0
current_node=0, numa_group_id=0
numa_faults node=0 task_private=0 task_shared=0 group_private=0 group_shared=0
Hello,it's me
