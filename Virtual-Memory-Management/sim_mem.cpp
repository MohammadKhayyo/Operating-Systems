

// libraries that used in this exercise
#include <iostream>
#include <fstream>
#include <fcntl.h>
#include "sim_mem.h"
#include <unistd.h>
#include <stack>
#define MEMORY_SIZE 10
using namespace std;
// constructor form the header
sim_mem::sim_mem(char exe_file_name[], char swap_file_name[], int text_size, int data_size, int bss_size,int heap_stack_size, int num_of_pages, int page_size) {
    this->text_size=text_size;
    this->data_size=data_size;
    this->bss_size=bss_size;
    this->heap_stack_size=heap_stack_size;
    this->num_of_pages=num_of_pages;
    this->page_size=page_size;
    int page_text=text_size/page_size; // pages of the text
    int swap_size=page_size*(num_of_pages-page_text); // the swap size
    int page_swap=(swap_size/page_size); // pages of the swap
    // opening the executable file
    if((this->program_fd = open(exe_file_name,O_RDONLY)) == -1){
        perror( "open executable file Failed");
       // calling discractor
        this -> sim_mem::~sim_mem();
        exit(EXIT_FAILURE);
    }
    //opening the swap file
    if((this->swapfile_fd= open(swap_file_name, O_CREAT| O_RDWR|O_TRUNC, 0666)) == -1){
        perror( "open swap file Failed");
        // calling discractor
        this -> sim_mem::~sim_mem();
        exit(EXIT_FAILURE);
    }
    int i;
    // zeros in memory
    for(i=0; i<MEMORY_SIZE ;i++){
        main_memory[i]='0';
    }
    // zeros in swap file
    for(i = 0; i < swap_size ; i++) {
        if (write(this->swapfile_fd, "0", 1) == -1) {
            perror( "Write Failed");
            this ->  sim_mem::~sim_mem();
            exit(EXIT_FAILURE);
        }
    }
    // creating the page table
    page_table = new page_descriptor [num_of_pages];
    // creating the array swap
    array_swap = new int [page_swap];
    // making default to all the pages
    for(i=0;i<num_of_pages;i++){
        page_table[i].V=0;
        page_table[i].D = 0;
        page_table[i].frame = -1;
        page_table[i].swap_index = -1;
        if(i<page_text)
            page_table[i].P = 0;
        else
            page_table[i].P = 1;
    }
    // each swap file is empty
    for (i=0; i <page_swap ;i++) {
        array_swap[i] = -1;
    }
}
// discractor
sim_mem::~sim_mem(){
    if(close(swapfile_fd)==-1 || close(program_fd)==-1) {
        perror("close Filed");
        exit(EXIT_FAILURE);
    }
    delete [] page_table;
    delete [] array_swap;
}
// adding the page to the queue
void sim_mem::repetition_count(int page){
    // if the queue is not empty search the page if its found in the queue , if found , deleting it
    while (!deque_swap.empty()) {
        if(page == deque_swap.front()){
            deque_swap.pop_front();
            deque_swap.push_back(page);
            while(!stack_swap.empty()){
                deque_swap.push_front(stack_swap.top());
                stack_swap.pop();
            }
            return;
        }
        stack_swap.push( deque_swap.front());
        deque_swap.pop_front();
    }
    // push to the page and adding to the queue
    deque_swap.push_front(page);
    // add the values  while the stack is not empty to the queue
    while(!stack_swap.empty()){
        deque_swap.push_front(stack_swap.top());
        stack_swap.pop();
    }
}
// sending the page to the swap during the use of LUR
int sim_mem::WriteThePageToSwap(){
    char tmp_ForSwap[page_size];
    int page = deque_swap.front(); // oldest page
    int page_text=text_size/page_size; // number of the pages of the text
    int swap_size=page_size*(num_of_pages-page_text); // size of the swap
    int page_swap=(swap_size/page_size); // number of the pages of the swap
    int i ,j, Empty_Place = 0; // saving the empty place of the swap
    int page_frame =  page_table[page].frame;//save the page value in the frame
    if(page_table[page].V == 0 ) {//if the v was 0 we return to first one of them that has the valid is 1
        while (!deque_swap.empty()) {// if the queue is not empty search the page if its found in the queue , if found , deleting it
            if (page_table[deque_swap.front()].V == 1) {
                page = deque_swap.front();
                page_frame = page_table[page].frame;
                deque_swap.pop_front();
                while (!stack_swap.empty()) {
                    deque_swap.push_front(stack_swap.top());
                    stack_swap.pop();
                }
                break;
            }
            stack_swap.push(deque_swap.front());
            deque_swap.pop_front();
        }
    }if(page_table[page].V == 1 && page_table[page].D == 1 ){//if it was in the memory and also from the store there is a possibility to put it in the swap
        for( i = page_size * page_frame,j=0 ;j<page_size ; i++,j++) {//save inside the page in string
            tmp_ForSwap[j] = main_memory[i];
        }
        tmp_ForSwap[j]='\0';
        for( i = page_size * page_frame ; i < (page_size * page_frame ) + page_size ; i++) {//deleting what is inside the frame
            main_memory[i]='0';
        }
        for ( i = 0; i < page_swap ; i++) {//finding an empty space in the swap
            if(array_swap[i] == -1){
                page_table[page].swap_index=i;//save the index
                Empty_Place=i;
                break;
            }
        }
        lseek(swapfile_fd, page_size * Empty_Place, SEEK_SET);//reposition read or write file offset
        if(write(swapfile_fd, tmp_ForSwap , page_size ) != page_size){//write the page inside the swap
            perror("Write Failed");
            return -1;
        }
        array_swap[Empty_Place] = page;
        page_table[page].V = 0;
        page_table[page].frame= -1;
    }else if (page_table[page].V == 1 && page_table[page].D == 0) {//if the page was inside the main memory and came from the load we can removing from the main memory
        for (i = page_size * page_frame; i < (page_size * page_frame ) + page_size; i++) {//deleting what is inside the frame
            main_memory[i] = '0';
        }
        page_table[page].V = 0;
        page_table[page].frame = -1;
        page_table[page].swap_index = -1;
    }
    return page_frame;
}
char sim_mem::load( int address){//bring from the logical memory to main memory for reading it
    if(address<0) return '\0';
    int page = address / page_size;
    int offset = address % page_size;
    int physical_address = -1;
    int page_frame;
    int page_text=text_size/page_size;// number of the pages of the text
    int page_data=data_size /page_size;// number of the pages of the data
    if(page >=num_of_pages){//if the page size is bigger than the num of pages ,print out of range and continue
        fprintf(stderr , "out of range\n");
        return '\0';
    }
    if(page_table[page].V ==0 && page_table[page].D ==0 && page >= (page_text+page_data)){//if the page was from stack type or bss or heap and it was the first time we bringing it we put an error
        fprintf(stderr,"is not allow to use load");
        return '\0';
    }
    repetition_count(page);
    if(page_table[page].V == 1){
        page_frame = page_table[page].frame;
        physical_address = (page_frame * page_size) + offset;
    }else if(page_table[page].V == 0 && page < (page_text+page_data) && page_table[page].D == 0) { // if not found in main memory and it is text
        char tmp_ForExecutable [page_size];
        lseek(program_fd, page_size * page, SEEK_SET);
        if (read(program_fd, tmp_ForExecutable, page_size) != page_size) {
            perror("Read From executable File Is Failed");
            return '\0';
        }
        int i ,Empty_Place= EmptyPlace(page);
        page_frame = page_table[page].frame;
        for (i=0; i < page_size; Empty_Place++,i++) { // fill in main memory
            main_memory[Empty_Place] = tmp_ForExecutable[i];
        }
        page_table[page].V = 1;
        page_table[page].swap_index = -1;
        physical_address = (page_frame * page_size) + offset;
    }else if(page_table[page].V ==0 && page_table[page].D == 1 ){//bring the page from the swap
        char tmp_ForSwap [page_size];
        int i, Save_Index = 0;
        int page_swap = num_of_pages-(text_size/page_size );
        for(i=0;i<page_swap;i++){//find the page place in the swap
            if(array_swap[i]==page){
                array_swap[i] = -1;
                Save_Index=i;
                break;
            }
        }
        page_table[page].swap_index=-1;
        lseek(swapfile_fd, page_size * Save_Index, SEEK_SET);//reposition read or write file offset
        if(read(swapfile_fd, tmp_ForSwap, this->page_size) != this->page_size){
            perror("Read From Swap File Is Failed");
            return '\0';
        }
        lseek(swapfile_fd, page_size * Save_Index, SEEK_SET);//reposition read or write file offset
        for(i=0;i<page_size;i++) {
            if (write(this->swapfile_fd, "0", sizeof (char) == -1)) {
                perror("Write to Swap File Is Failed");
                return '\0';
            }
        }
        int Empty_Place= EmptyPlace(page);//save the empty frame
        for(i=0; i < page_size; Empty_Place++,i++) { // fill in main memory
            main_memory[Empty_Place] = tmp_ForSwap[i];
        }
        page_table[page].V = 1;
        page_table[page].swap_index=-1;
        page_frame = page_table[page].frame;
        physical_address = (page_frame * page_size) + offset;
    }
    return main_memory[physical_address];
}
void sim_mem::store(int address, char value){//bring from the logical memory to main memory for change the value.
    if(address<0) return;
    int page = address / page_size;
    int offset = address % page_size;
    int physical_address;
    int page_frame;
    int page_text=text_size/page_size;// number of the pages of the text
    int page_data=data_size /page_size;// number of the pages of the data
    if(page >=num_of_pages){//if the page size is bigger than the num of pages ,print out of range and continue
        fprintf(stderr , "out of range\n");
        return;
    }
    if(page_table[page].P == 0){//if the permission for the page was read so we can not bring the page to write
        fprintf(stderr,"This page does not have write permissions");
        return;
    }
    repetition_count(page);
    if(page_table[page].V == 1){//if it was in the main memory , put the valid value in the physical address
        page_frame = page_table[page].frame;
        physical_address = (page_frame * page_size) + offset;
        main_memory[physical_address] = value;
    }else if(page_table[page].V == 0 && page_table[page].D == 0 && (page<(page_text+page_data))){//bring the page from the executable
        char tmp_ForExecutable [page_size];
        lseek(program_fd, page_size * page, SEEK_SET);//reposition read or write file offset
        if (read(program_fd, tmp_ForExecutable, page_size) != page_size) {
            perror("Read From executable File Is Failed");
            return;
        }
        int i ,Empty_Place = EmptyPlace(page);//save the empty frame
        for (i=0; i < page_size; Empty_Place++,i++) { // fill in main memory
            main_memory[Empty_Place] = tmp_ForExecutable[i];
        }
        page_table[page].D= 1;
        page_table[page].V = 1;
        page_frame = page_table[page].frame;
        physical_address = (page_frame * page_size) + offset;
        main_memory[physical_address] = value;
    }else if(page_table[page].V ==0 && page_table[page].D == 1 ){//bring the page from the swap file
        char tmp_ForSwap [page_size];
        int i, Save_Index = 0;
        int page_swap = num_of_pages-(text_size/page_size );
        for(i=0;i<page_swap;i++){
            if(array_swap[i]==page){
                Save_Index=i;
                array_swap[i] = -1;
                break;
            }
        }
        page_table[page].swap_index=-1;
        lseek(swapfile_fd, page_size * Save_Index, SEEK_SET);//reposition read or write file offset
        if(read(swapfile_fd, tmp_ForSwap,page_size) != page_size){
            perror("Read From Swap File Is Failed");
            return;
        }
        lseek(swapfile_fd, page_size * Save_Index, SEEK_SET);//reposition read or write file offset
        for(i=0;i<page_size;i++) {
            if (write(this->swapfile_fd, "0", sizeof(char)) == -1) {
                perror("Write to Swap File Is Failed");
                return;
            }
        }
        int Empty_Place= EmptyPlace(page);//save the empty frame
        for(i=0; i < page_size; Empty_Place++,i++) { // fill in main memory
            main_memory[Empty_Place] = tmp_ForSwap[i];
        }
        page_table[page].V = 1;
        page_table[page].swap_index=-1;
        page_frame = page_table[page].frame;
        physical_address = (page_frame * page_size) + offset;
        main_memory[physical_address] = value;
    }else if(page_table[page].V ==0 && page_table[page].D ==0 && page>=(page_text+page_data)){//if the page was from stack type or bss or heap and it was the first time we bringing it we put a page with zeros and replace it with the value
        int i,Empty_Place= EmptyPlace(page);
        for(i=0; i < page_size; Empty_Place++,i++) { // fill in main memory
            main_memory[Empty_Place] = '0';
        }
        page_table[page].V = 1;
        page_table[page].D= 1;
        page_frame = page_table[page].frame;
        physical_address = (page_frame * page_size) + offset;
        main_memory[physical_address] = value;
    }
}
int sim_mem::EmptyPlace(int page){//return empty frame
    int i,Empty_Place,empty = 0;
    for( i = 0; i < MEMORY_SIZE; i = i + page_size) { // empty place in main memory
        if(  main_memory[i]== '0'){
            for (int j = i; j < page_size+i; j++) {
                if(main_memory[j] != '0'){
                    empty =1;
                    break;
                }else{
                    empty = 0;
                }
            }
            break;
        }
    }
    for( i = 0; i < MEMORY_SIZE; i += page_size) { // empty place in main memory
        if( main_memory[i]== '0'&& page_table[i/page_size].V==0){
            break;
        }
    }
    if(i == MEMORY_SIZE||empty==1){//if the main memory was full
        page_table[page].frame  = WriteThePageToSwap();
        Empty_Place = page_table[page].frame * page_size;
    }else {
        page_table[page].frame = i / page_size;
        Empty_Place = i;
    }
    return Empty_Place;
}
// printing the memory
void sim_mem::print_memory() {
    int i;
    printf("\n Physical memory\n");
    for(i = 0; i < MEMORY_SIZE; i++) {
        printf("[%c]\n", main_memory[i]);
    }
}
// printing the swap
void sim_mem::print_swap() const {
    char* str = static_cast<char *>(malloc(this->page_size * sizeof(char)));
    int i;
    printf("\n Swap memory\n");
    lseek(swapfile_fd, 0, SEEK_SET); // go to the start of the file
    while(read(swapfile_fd, str, this->page_size) == this->page_size) {
        for(i = 0; i < page_size; i++) {
            printf("%d - [%c]\t", i, str[i]);
        }
        printf("\n");
    }
    free(str);
}
//printing the page table
void sim_mem::print_page_table() const {
    int i;
    printf("\n page table \n");
    printf("Valid\t Dirty\t Permission \t Frame\t Swap index\n");
    for (i = 0; i < num_of_pages; i++) {
        printf("[%d]\t\t[%d]\t\t\t[%d]\t\t\t[%d]\t\t\t[%d]\n",
               page_table[i].V,
               page_table[i].D,
               page_table[i].P,
               page_table[i].frame,
               page_table[i].swap_index);
    }

}
