#include <iostream>
#include "sim_mem.h"


char main_memory[MEMORY_SIZE];
int main() {
    sim_mem mem_sm((char*) "exec_file.txt", (char*) "swap_file.txt" ,10, 10, 5,10, 7, 5);

    mem_sm.store(11, 'Q');
    mem_sm.load(17);
    mem_sm.print_memory();
    mem_sm.print_swap();
    mem_sm.print_page_table();

    mem_sm.store(32, 'k');
    mem_sm.store(27, 'X');
    mem_sm.print_memory();
    mem_sm.print_swap();
    mem_sm.print_page_table();

    mem_sm.load(6);
    mem_sm.load(12);
    mem_sm.print_memory();
    mem_sm.print_swap();
    mem_sm.print_page_table();

    mem_sm.store(34, 'k');
    mem_sm.store(27, 'x');
    mem_sm.print_memory();
    mem_sm.print_swap();
    mem_sm.print_page_table();

    mem_sm.load(5);
    mem_sm.load(10);
    mem_sm.print_memory();
    mem_sm.print_swap();
    mem_sm.print_page_table();
    return 0;
}