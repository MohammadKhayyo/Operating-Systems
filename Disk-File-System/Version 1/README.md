# Disk File System Simulation

## Background:
Authored by Mohammad Khayyo, this project aims to provide a simplified simulation of a file system. It especially emphasizes on the understanding and implementation of the indexed allocation strategy commonly used in file systems.

## Description:

### Overview:
- **Indexed Allocation Simulation**: This project demonstrates the inner workings of a file system that operates using an indexed allocation strategy.
- **Core Components**: The simulation operates using three primary classes: `fsFile`, `FileDescriptor`, and `fsDisk`.

### Classes:
1. **`fsFile`**: Represents the data structure of a file stored using indexed allocation.
2. **`FileDescriptor`**: Contains metadata about a file, such as its name, a pointer to its `fsFile` representation, and its status (open or closed).
3. **`fsDisk`**: Emulates the entire file system. It includes two primary data structures: `MainDir` (representing the file table linking file names to their data) and `OpenFileDescriptors` (an array that monitors the currently open files).

### Functions:
The project consists of various utility functions to help in tasks like binary-to-decimal conversion and index block selection. Essential functions for the file system operations include:

- `listAll()`: Lists all the files and their details in the disk.
- `fsFormat(int blockSize)`: Formats the disk.
- `CreateFile(string fileName)`: Generates a new file.
- `OpenFile(string fileName)`: Accesses an existing file.
- `CloseFile(int fd)`: Shuts an opened file.
- `WriteToFile(int fd, char *buf, int len)`: Records data to an open file.
- `DelFile(string FileName)`: Erases a file.
- `ReadFromFile(int fd, char *buf, int len)`: Fetches data from an open file.

For better object management, setters and getters exist for both `fsFile` and `FileDescriptor`.

## Usage:

### Compilation:
To compile the program, utilize the following command:
```
g++ ex7_final_proj.2021.cpp -o ex7_final_proj.2021
```
For executing the compiled program:
```
./ex7_final_proj.2021
```

### Sample Sequence:
The simulation allows users to:

1. Format the disk.
2. Construct three files: A, B, and C.
3. Record data into file A.
4. Enumerate all the files.
5. Close and obliterate files.
6. Extract data from file A.

## Program Files:

- **ex7_final_proj.2021.cpp**: Contains the implementations for the function's and main.
