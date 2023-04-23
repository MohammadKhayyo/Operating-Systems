Mini shell
Authored by : Mohammad Khayyo

==Description==
ex2a
Whats is shel?
An interface program that reads commands from the user and transmits them In a format suitable for the operating system To perform.
The first part:
In this exercise implement a mini shell In the language C Under the operating system linux,
the shell will display prompt for user And Read the commands then send them to the operating system To execute.
ex2b
The second part:
They worked like the one before it,but in addition before each command must be printed to Screen the scheduler information for the same process Who runs it.


functions:
the program have 5 function:
1: howManyWords: the method will calculate how many words we entered through the string.
2: TheNumberOfLettersInEachWord: this method will cut the sentence into words and calculate how many letters are in them.
3: freeDynamicAllocation: this method free's the memory of all alloc.
4: Process: this method will take the Shell command and activate it.
5: Prompt: this method will get the Prompt.

==Program Files==

ex2a.c : the first part , they contain the main only and the functions.

ex2b.c : the second part , they contain the main only and the functions.

==How to compile?==

(the first part):
compile: gcc ex2a.c -o ex2a
run: ./ex2a

(the second part):

compile: gcc ex2b.c -o ex2b
run: ./ex2b

=======Input int the first part (ex2a)==========

echo Hello,it's me

==========Output in the first part (ex2a)=============

Hello,it's me

=======Input int the second part (ex2b)==========

echo Hello,it's me

==========Output in the second part (ex2b)=============

memcheck-amd64- (8814, #threads: 1)
-------------------------------------------------------------------
se.exec_start                                :      10677793.083491
se.vruntime                                  :        922574.952583
se.sum_exec_runtime                          :            10.497828
se.nr_migrations                             :                    1
nr_switches                                  :                    3
nr_voluntary_switches                        :                    1
nr_involuntary_switches                      :                    2
se.load.weight                               :              1048576
se.runnable_weight                           :              1048576
se.avg.load_sum                              :                46696
se.avg.runnable_load_sum                     :                46696
se.avg.util_sum                              :             26556984
se.avg.load_avg                              :                 1023
se.avg.runnable_load_avg                     :                 1023
se.avg.util_avg                              :                  568
se.avg.last_update_time                      :       10677793083392
se.avg.util_est.ewma                         :                  142
se.avg.util_est.enqueued                     :                  569
policy                                       :                    0
prio                                         :                  120
clock-delta                                  :                   21
mm->numa_scan_seq                            :                    0
numa_pages_migrated                          :                    0
numa_preferred_nid                           :                   -1
total_numa_faults                            :                    0
current_node=0, numa_group_id=0
numa_faults node=0 task_private=0 task_shared=0 group_private=0 group_shared=0
Hello,it's me
