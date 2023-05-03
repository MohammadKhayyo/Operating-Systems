Disk File System
Authored By: Mohammad Khayyo 



===================Description===================

In this exercise we are doing a simulation of how the disk load, save, write, read the information into it.
We are doing a simulation of indexed allocation and show the mechanism of how this method control the disk system.  
The file has 3 several classes: fsFile, fsDisk, FileDescriptor

- fsFile: Is a data structure that save, stores the info o the file in indexed allocation mechanism 

- FileDescriptor: The class that contain the info of the file, file name and pointer form fsFile type for knowing info of the file and a Boolean variable that tells if the file is opened or closed .

- fsDisk: this fsDisk simulate the disk itself and saves all the info, this class contain 2 main variables : MainDir, OpenFileDescriptors.
  
= mainDir it’s a data structure that simulate a table and it’s the main directory, links the file name to its FSFile and they have all files in disk and it’s done by arrays using re/malloc function. 
= OpenFileDescriptors : its an array of File Descriptor type, they have all open files and its done by arrays using re/malloc function.  .


===================functions===================

int Power (int x, int y):receives two integers x, and y and return the power between them (x^y)

int ReadFromIndexBlock (char &c): receives a pointer of the char type,convert from binary to decimal

char decToBinary (int n , char &c): receives an integer and a pointer of the char type,Convert from Decimal To Binary
void destructor ():part of the destructor of the fsDisk class that delete the pointers

int ReturnIndexBlock(int fd): receives an integer, choose the block for indexed allocation 

int Delete (const string& File_Name,int MainDir_Index): receives a string by reference, and an integer, delete the close file and remove it form mainDir. 
void write_BackSlash_Zero(int _from,int _to,int From_where): receives two integers, and filling the ordered part from the disk with /0 from “form_where”to “to”.

void listAll():method that prints  all the files in the disk and also all the info of it

void fsFormat(int blockSize):receives an integer, method that formatting the disk  by filling it with /0

int CreateFile(string fileName):receives a string of the file name, creating new file, and for each new file we create a mainDir, openFileDescriptor arrays.

int OpenFile(string fileName): receives a string of the file name that want to open, and its opening the file if its closed

string CloseFile(int fd):receives an integer o the file descriptor, closing the file if it was open

int WriteToFile(int fd, char *buf, int len):receives an integer of the file descriptor, and an array of chars and the length, writes the string that receives it to the file i the file already opened by writing into the blocks

int DelFile(string FileName): receives a string as a file name, deleting the file from the disk if the file was closed.

int ReadFromFile(int fd, char *buf, int len): receives integer of the file descriptor, array of chars and the length, read from the file if it was opened.

Setters and getters(fsFile):
•	void _SetFileSize(int _FileSize)
•	int getfile_size()
•	int _GetBlockInUse()
•	void _SetBlockInUse(int _BlockInUse)
•	int _GetBlockSize() 
•	void _SetBlockSize(int _BlockSize)
•	int _GetIndexBlock() 
•	void _SetIndexBlock(int _IndexBlock)

Setters and getters(fileDiscriptor):

•	FsFile *Get_fs_file()
•	void _Set_fs_file(FsFile *_Fsi)
•	void _SetFileName(string _File_Name) 
•	bool Get_In_Use() 
•	void _Set_In_Use(bool _InUse) 

distructor of fsDisk class 
~fsDisk(): deletes the disk and the remainder of the open objects



==========Program Files==============

ex7_final_proj.2021.cpp : they contain  The implementations for function's and main

=================How to compile?===================
compile: g++ ex7_final_proj.2021.cpp -o ex7_final_proj.2021

run: ./ex7_final_proj.2021


================= Input and Output ===================

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
