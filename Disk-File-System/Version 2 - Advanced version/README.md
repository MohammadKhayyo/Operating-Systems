# Disk File System

## Description

Disk file systems manage data on permanent storage devices. This project is based on the idea of how data is arranged, sent, and received on a hard drive. We manage the disk file system using an indexed allocation scheme.

Indexed allocation scheme stores all the disk pointers in one of the blocks called as indexed block. The project contains three major classes: `fsDisk`, `FileDescriptor`, `fsFile`.

### fsDisk

This class simulates the disk itself that save all the data of the disk. It has six fields including a bit vector for block usage, a boolean variable to check if the disk has been formatted, and various structures to simulate directories and file descriptors.

### FileDescriptor

This class stores the linked information of a file name and points to the `fsFile` of the file. In addition, it has a variable called `inUse` that investigates the status of the file if it's opened or closed.

### fsFile

This class stores information about the file, it's used to store the information in the indexed allocation scheme. It has fields for the block size, index block, file size, and number of blocks in use.

## Functions

- `TOINT(char &c)`: Convert numbers from binary to decimal.
- `decToBinary(int n , char &c)`: Convert numbers from decimal to binary.
- `listAll()`: Print the list of the files created on the disk and the contents of the disk.
- `fsFormat(int blockSize)`: Format the disk by filling it with zeros.
- `CreateFile(string fileName)`: Create a new file and return a file descriptor. If the file already exists, it returns an error.
- `OpenFile(string fileName)`: Open a file. If the file is already open, it returns an error.
- `CloseFile(int fd)`: Close a file. If the file is already closed, it returns an error.
- `WriteToFile(int fd, char *buf, int len )`: Write to a file. If the file is not open or doesn't exist, it returns an error.
- `DelFile( string FileName )`: Delete a file. If the file is open or doesn't exist, it returns an error.
- `ReadFromFile(int fd, char *buf, int len )`: Read from a file. If the file is not open, the buffer is empty, or the file doesn't exist, it returns an error.

In addition, the program includes various setters and getters functions and a destructor.

## Program Files

- `ex7_final_proj.2021.cpp`: Contains the implementation of `fsDisk`, `FileDescriptor`, `fsFile` classes, and the main tester.
- `README.txt`: This file.

## Compiling Steps

Compile: `g++ ex7_final_proj.2021.cpp -o ex7_final_proj.2021`
Run: `./ex7_final_proj.2021`

## Input and Output

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
Disk content: 'ABCDEFGQWERQWER AZXSWEDCFRTG'
7
2
12
ReadFromFile: AZXSWEDCFRTG
