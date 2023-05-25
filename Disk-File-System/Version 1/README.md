# Disk File System

Authored By: Mohammad Khayyo

## Description

In this exercise, we are doing a simulation of how the disk loads, saves, writes, reads the information into it. We are simulating indexed allocation and demonstrating the mechanism of how this method controls the disk system. The file has 3 classes: `fsFile`, `fsDisk`, and `FileDescriptor`.

- `fsFile`: A data structure that saves and stores the info of the file in the indexed allocation mechanism.
- `FileDescriptor`: A class that contains the info of the file, filename, and a pointer of `fsFile` type for knowing info of the file, and a boolean variable that tells if the file is opened or closed.
- `fsDisk`: This class simulates the disk itself and saves all the info. This class contains two main variables: `mainDir` and `OpenFileDescriptors`.

## Functions

This project contains numerous functions for the operation of the disk file system. Please see the source code for detailed information on each function's operation, inputs, and outputs.

## Program Files

- `ex7_final_proj.2021.cpp`: Contains the implementations for function's and main.

## How to Compile

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
6
0
ABCDABCDABCD
Writed: 12 Char's into File Descriptor #: 0
6
0
YES
Writed: 3 Char's into File Descriptor #: 0
1
index: 0: FileName: A , isInUse: 1
index: 1: FileName: B , isInUse: 1
index: 2: FileName: C , isInUse: 1
Disk content: 'ABCDABCDABCDYES'
6
2
QWERT
Writed: 5 Char's into File Descriptor #: 2
1
index: 0: FileName: A , isInUse: 1
index: 1: FileName: B , isInUse: 1
index: 2: FileName: C , isInUse: 1
Disk content: 'ABCDABCDABCDYESQWERT'
5
1
CloseFile: 1 with File Descriptor #: 1
1
index: 0: FileName: A , isInUse: 1
index: 1: FileName: B , isInUse: 0
index: 2: FileName: C , isInUse: 1
Disk content: 'ABCDABCDABCDYESQWERT'
5
2
CloseFile: 1 with File Descriptor #: 2
1
index: 0: FileName: A , isInUse: 1
index: 1: FileName: B , isInUse: 0
index: 2: FileName: C , isInUse: 0
Disk content: 'ABCDABCDABCDYESQWERT'
8
B
DeletedFile: B with File Descriptor #: 1
1
index: 0: FileName: A , isInUse: 1
index: 1: FileName: C , isInUse: 0
Disk content: 'ABCDABCDABCDYESQWERT'
8
C
DeletedFile: C with File Descriptor #: 1
1
index: 0: FileName: A , isInUse: 1
Disk content: 'ABCDABCDABCDYES'
7
0
50
ReadFromFile: ABCDABCDABCDYES
0
