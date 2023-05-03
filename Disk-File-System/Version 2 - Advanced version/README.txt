Disk File System 




	===================Description===================

Disk file systems are file systems which manage data on permanent storage devices.
The disk file system takes advantage of the disk storage media's ability to process data randomly in a short period of time. Additional considerations include the speed of data access after that initially required
This project based on the idea of the File systems and how data is arranged, sent, and received to a hard drive.
We will manage the disk file system using indexed allocation Scheme.

Indexed allocation scheme stores all the disk pointers in one of the blocks called as indexed block. Indexed block doesn't hold the file data, but it holds the pointers to all the disk blocks allocated to that file. Directory entry will only contain the index block address.
the project will contain three major classes: fsDisk, FileDescriptor, fsFile and they will be explained below, these 3 classes will help us to build the simulation of the disk file system using the indexed allocation scheme.


The three major classes minutely:

1-) fsDisk: it simulates the disk itself that save all the data of the disk, this class has six fields:

· BitVector: an array of type int that checks if blocks are in use or not.

· BitVectorSize: the size of the BitVector array.

· is_formated: Boolean variable that check if the disk has been formatted or not. 

· sim_disk_fd: pointer of type *FILE points at the file, the disk to be used by us for simulation.

· OpenFileDescriptors: it’s a data structure of file descriptor that include all the opened file that been done in our simulation, that help us to know what file descriptors are opened/closed and how many file descriptors we must allocate in condition of opening a new file.

· MainDir: a data structure that simulate a table that links between the name of the file and its FsFile, it holds the file name as a string and the pointer of at FsFile of the file.



2-) FileDescriptor: the job is to store the linked information of a file name and points to the FsFile of the file. In addition, it has a variable called inUse that investigate the status of the file if its opened or closed.



3-) fsFile: the job is to store information about the file, it’s a kind of data structure that used to store the information in indexed allocation scheme and in our simulation will have four fields 

· Block_size: The number of cells that can be saved in each block

· Index_block: saves the position of the block_index 

· File_size: the size of the file 

· Block_in_use: number of blocks in use 



	===================Functions===================

1· int TOINT(char &c): helping function from the type int that receives a pointer from the type char as a parameter, its job is to Convert numbers from binary to decimal.

2· char decToBinary(int n , char &c): helping function from the type char that receives an integer “n” and a pointer from the type char as a parameters, its job is to Convert numbers from decimal to binary.

3· void listAll():function from the type void that receives nothing as a parameter, its job is to print the list of the files that created on the disk and the contents of the disk as well. 

4· void fsFormat(int blockSize): function from the type void that receives the block size from the type int as a parameter, its job to fill the disk with zeros “/0” (to format the disk)

5· int CreateFile(string fileName): function from the type int that receives the file name as a string, its job to create a new file and it builds for each file a new main directory/open_file_descriptor array, if the file is already created it throw an error(-1). 

6· int OpenFile(string fileName): function from the type int that receives the file name that we want to open as a string, its job is to open the file when its closed and if the file is already opened it throw an error(-1). 

7· string CloseFile(int fd): function from the type string that receives integer of the file descriptor, its job is to close the file when its opened, and if the file is already closed it throw an error(-1). 

8· int WriteToFile(int fd, char *buf, int len ): function from the type int that receives integer of the file descriptor, buffer array and its length, its job is to write the info the receives in the buffer into the file or the blocks when the file is already opened, if we couldn’t find the file at the file descriptor or if the file is closed it will throw an error(-1).

9· int DelFile( string FileName ): function from the type int that receives the file name as a string, its job is to delete the file from the disk and only when the file is closed. If the file is open or file is not found it will throw an error(-1).

10· int ReadFromFile(int fd, char *buf, int len ): function from the type int that receives integer of the file descriptor, buffer array and its length, its job is to read from the file and only when the file is open, if we couldn’t find the file at the file descriptor or if the file is closed or if the buffer is empty it will throw an error (-1).

** the program also includes setters and getters functions and a destructor.



		==========Program Files==============

this program has only two files : "the main file" that called "ex7_final_proj.2021.cpp", and the Read_Me.txt file.

the file includes:

.fileDescriptor class and its implementation, its setters and getters functions,features and variables initialization .

.FsFile class and its implementation, its setters and getters functions,features and variables initialization .

.fsDisk class and its implementation, its setters and getters functions,features and variables initialization, this class include also all the function that have been mentioned above "without the helping methods", simulation of the disk itself,and two maps that implement the mainDir and the OpenFileDescriptors

·the main "tester" of the project.



	=================compiling steps===================

g++ ex7_final_proj.2021.cpp -o ex7_final_proj.2021

run: ./ex7_final_proj.2021




	================= input/Output ===================

"the same tester that the lecturer used "

2
4
3
A
CreateFile: A with File Descriptor #: 0
3
B
CreateFile: B with File Descriptor #: 1
3
C
CreateFile: C with File Descriptor #: 2
5
2
CloseFile: 1 with File Descriptor #: 2
6
1
ABCDEFG
Writed: 7 Char's into File Descriptor #: 1
1
index: 0: FileName: A , isInUse: 1
index: 1: FileName: B , isInUse: 1
index: 2: FileName: C , isInUse: 0
Disk content: 'ABCDEFG'
6
0
QWERQWER
Writed: 8 Char's into File Descriptor #: 0
1
index: 0: FileName: A , isInUse: 1
index: 1: FileName: B , isInUse: 1
index: 2: FileName: C , isInUse: 0
Disk content: 'ABCDEFGQWERQWER'
7
1
4
ReadFromFile: ABCD
7
0
8
ReadFromFile: QWERQWER
4
C
OpenFile: C with File Descriptor #: 2
6
2
AZXSWEDCFRTG
Writed: 12 Char's into File Descriptor #: 2
1
index: 0: FileName: A , isInUse: 1
index: 1: FileName: B , isInUse: 1
index: 2: FileName: C , isInUse: 1
Disk content: 'ABCDEFGQWERQWER  AZXSWEDCFRTG'
7
2
12
ReadFromFile: AZXSWEDCFRTG



