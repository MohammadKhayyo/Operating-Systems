#ifndef SIM_MEM_H
#define SIM_MEM_H
#include <deque>
#include <stack>
#define MEMORY_SIZE 10
using namespace std;
extern char main_memory[MEMORY_SIZE];
class sim_mem {
    int swapfile_fd; //swap file fd
    int program_fd; //executable file fd
    int text_size;
    int data_size;
    int bss_size;
    int heap_stack_size;
    int num_of_pages;
    int page_size;

public:
    sim_mem(char exe_file_name[], char swap_file_name[], int text_size, int data_size, int bss_size,int heap_stack_size, int num_of_pages, int page_size);
    ~sim_mem();
    char load(int address);//bring from the logical memory to main memory for reading it
    void store(int address, char value);//bring from the logical memory to main memory for change the value.
    static void print_memory();
    void print_swap() const ;
    void print_page_table() const;
    void repetition_count(int page_place );  // if the queue is not empty search the page if its found in the queue , if found , deleting it
    int WriteThePageToSwap();//sending the page to the swap during the use of LUR
    int EmptyPlace(int page);

    typedef struct page_descriptor {
        int V; // valid
        int D; // dirty
        int P; // permission
        int frame; // where its placed in the mau=in memory
        int swap_index; // where its located in swap file .
    } page_descriptor;
// creating queue
    page_descriptor *page_table;
    deque<int> deque_swap;// creating queue
    stack<int> stack_swap; // creating stack
    int* array_swap; // swap helper
};
#endif //SIM_MEM_H
