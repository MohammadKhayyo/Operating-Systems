# Disk File System Simulation

## Background
The project focuses on simulating a disk file system, a system that manages data on permanent storage devices. It's an emulation of how data is arranged, sent, and received on a hard drive. One of the key features is its utilization of the indexed allocation scheme.

## Description

### Overview
The simulation provides an insight into the functioning of a disk file system. The key emphasis is on the indexed allocation scheme where all pointers related to a file's data are stored in a special indexed block, eliminating the need for the block itself to store the actual file data.

### Classes

1. **fsDisk:** Represents the disk. 
   - `BitVector`: Checks block usage.
   - `BitVectorSize`: Size of the `BitVector`.
   - `is_formated`: Indicates if the disk is formatted.
   - `sim_disk_fd`: Points to the simulated disk file.
   - `OpenFileDescriptors`: Tracks opened file descriptors.
   - `MainDir`: Links file names with their respective `FsFile` pointers.
   
2. **FileDescriptor:** Manages file linkage information.
   - Tracks the link between a file name and its `FsFile`.
   - `inUse`: Indicates file open status.

3. **fsFile:** Holds file information.
   - `Block_size`: Cells count in each block.
   - `Index_block`: Position of the block index.
   - `File_size`: File's size.
   - `Block_in_use`: Count of blocks in use.

### Functions
The system incorporates various functions to:
- Convert binary to decimal and vice versa.
- Print a list of files on the disk.
- Format the disk.
- Create, open, close, write to, read from, and delete files.

## Usage

### Compilation
To utilize the simulation:

1. Compile the code:
   ```
   g++ ex7_final_proj.2021.cpp -o ex7_final_proj.2021
   ```

### Sample Sequence
Run the compiled program:
   ```
   ./ex7_final_proj.2021
   ```

Follow on-screen prompts or refer to the provided input/output example for specific operations.

## Program Files
The project consists of the following main files:
- **ex7_final_proj.2021.cpp:** Contains the main functions, class definitions, and implementations.
- **README.md:** This documentation.