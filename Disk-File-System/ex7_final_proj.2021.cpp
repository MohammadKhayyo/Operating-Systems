

// the includes I used
#include <iostream>

#include <vector>

#include <map>

#include <cassert>

#include <fcntl.h>

#include <cstdio>

#include <cstdlib>

#include <cstring>

#include <cmath>

using namespace std;
// the size o the disk
#define DISK_SIZE 256

int Power(int x, int y) { // power function (x^y)
    int H;
    int pow = 1;
    for (H = 1; H <= y; H++)
        pow = pow * x;
    return pow;
}
int ReadFromIndexBlock(char & c) { //convert from binary to decimal
    int decimal = 0;
    int SavePow = 0;
    int SaveTwo = 2;
    char save = 1u;
    int size = Power(SaveTwo, 3);
    for (int H = 0; H < size; H++) {
        SavePow = Power(SaveTwo, H);
        decimal += (save & (c >> H)) * SavePow;
    }
    return decimal;
}
char decToBinary(int n, char & c) { //Convert from Decimal To Binary
    // array to store binary number
    int binaryNum[8];
    // counter for binary array
    int H = 0;
    while (n > 0) {
        // storing remainder in binary array
        binaryNum[H] = n % 2;
        n = n / 2;
        H++;
    }
    c = c & 0;
    // printing binary array in reverse order
    for (int K = H - 1; K >= 0; K--) {
        if (binaryNum[K] == 1)
            c = c | 1u << K;
    }
    return c;
}
// ============================================================================

class FsFile {

    int file_size;

    int block_in_use;

    int index_block;

    int block_size;

public:

    FsFile(int _block_size) { // constructor

        file_size = 0;

        block_in_use = 0;

        block_size = _block_size;

        index_block = -1;

    }
    // setters and getters functions
    void _SetFileSize(int _FileSize) {
        this -> file_size = _FileSize;
    }

    int getfile_size() {
        return file_size;
    }

    int _GetBlockInUse() {
        return block_in_use;
    }
    void _SetBlockInUse(int _BlockInUse) {
        this -> block_in_use = _BlockInUse;
    }

    int _GetBlockSize() {
        return block_size;
    }

    void _SetBlockSize(int _BlockSize) {
        this -> block_size = _BlockSize;
    }

    int _GetIndexBlock() {
        return this -> index_block;
    }

    void _SetIndexBlock(int _IndexBlock) {
        this -> index_block = _IndexBlock;
    }

};

// ============================================================================

class FileDescriptor {

    string file_name;

    FsFile * fs_file;

    bool inUse;

public:

    FileDescriptor(string FileName, FsFile * fsi) { // constructor

        file_name = FileName;

        fs_file = fsi;

        inUse = true;
    }
    // setters and getters functions
    FsFile * Get_fs_file() {
        return fs_file;
    }

    void _Set_fs_file(FsFile * _Fsi) {
        fs_file = _Fsi;
    }

    string getFileName() {

        return file_name;

    }

    void _SetFileName(string _File_Name) {
        file_name = _File_Name;
    }

    bool Get_In_Use() {
        return inUse;
    }

    void _Set_In_Use(bool _InUse) {
        inUse = _InUse;
    }

};
// disks file name
#define DISK_SIM_FILE "DISK_SIM_FILE.txt"

// ============================================================================

class fsDisk {

    FILE * sim_disk_fd;

    bool is_formated;

    // BitVector - "bit" (int) vector, indicate which block in the disk is free

    //              or not.  (i.e. if BitVector[0] == 1 , means that the

    //             first block is occupied.

    int BitVectorSize;

    int * BitVector;

    // MainDir;
    FileDescriptor ** MainDir;

    // OpenFileDescriptors --  when you open a file,
    FileDescriptor ** OpenFileDescriptors;
    // the operating system creates an entry to represent that file

    // This entry number is the file descriptor.

    // OpenFileDescriptors;

    int block_size;

    int maxSize;

    int freeBlocks;

    // ------------------------------------------------------------------------
public:
    int MainDir_Size = 0; // mainDir array size
    int OpenFileDescriptors_Size = 0; // OpenFileDescriptors array size

    fsDisk() {

        MainDir = NULL; // starting the pointer with null
        OpenFileDescriptors = NULL; //  starting the pointer with null

        sim_disk_fd = fopen(DISK_SIM_FILE, "r+"); // opening the file for reading

        assert(sim_disk_fd);

        for (int H = 0; H < DISK_SIZE; H++) {

            int ret_val = fseek(sim_disk_fd, H, SEEK_SET);

            ret_val = fwrite("\0", 1, 1, sim_disk_fd); // filling all the disk with /0

            assert(ret_val == 1);
        }
        //  initialization of the variables
        fflush(sim_disk_fd);
        is_formated = false;
        block_size = maxSize = freeBlocks = 0;
    }
    // part of the destructor of the fsDisk class that delete the pointers
    void destructor() {
        for (int H = 0; H < MainDir_Size; H++) {
            delete(MainDir[H] -> Get_fs_file());
            delete(MainDir[H]);
        }
        delete[] BitVector;
        OpenFileDescriptors_Size = 0;
        MainDir_Size = 0;
    }
    int ReturnIndexBlock(int fd) { // method that choose the block for indexed allocation
        int The_Index_Of_Index_Block = -1;
        for (int H = 0; H < BitVectorSize; H++) {
            if (BitVector[H] == 0) {
                OpenFileDescriptors[fd] -> Get_fs_file() -> _SetIndexBlock(H);
                freeBlocks--;
                BitVector[H] = 1;
                The_Index_Of_Index_Block = H;
                break;
            }
        }
        return The_Index_Of_Index_Block;
    }
    int Delete(const string & File_Name, int MainDir_Index) { // delete the close file and remove it form mainDir
        FileDescriptor * temp_Main_Dir = MainDir[MainDir_Index];
        for (int H = MainDir_Index; H < MainDir_Size - 1; ++H) {
            MainDir[H] = MainDir[H + 1];
        }
        MainDir[MainDir_Size - 1] = temp_Main_Dir;
        delete(temp_Main_Dir -> Get_fs_file());
        MainDir_Size--;
        MainDir = (FileDescriptor ** ) realloc((void * ) MainDir, MainDir_Size * sizeof(FileDescriptor * ));
        if (MainDir_Size != 0 && MainDir == NULL) { // check if the realloc is failed
            MainDir_Size = 0;
            exit(EXIT_FAILURE);
        }
        if (MainDir_Size == 0 && MainDir != NULL) { // check if the realloc is failed
            free(MainDir);
            MainDir = NULL;
        }
        delete(temp_Main_Dir);
        return 1;
    }
    void write_BackSlash_Zero(int _from, int _to, int From_where) { // filling the ordered part from the disk with /0
        for (int H = _from; H < _to; H++) {
            fseek(sim_disk_fd, From_where + H, SEEK_SET);
            fwrite("\0", 1, 1, sim_disk_fd);
        }
    }
    // ------------------------------------------------------------------------
    ~fsDisk() { // deletes the disk and the remainder of the open ojects

        destructor(); // calling the destructor method
        if (OpenFileDescriptors != NULL) free(OpenFileDescriptors);
        if (MainDir != NULL) free(MainDir);
        fclose(sim_disk_fd);
    }
    void listAll() { // method that prints  all the files in the disk and also all the info of it

        int H;

        for (H = 0; H < MainDir_Size; H++) {

            cout << "index: " << H << ": FileName: " << MainDir[H] -> getFileName() << " , isInUse: " <<
            MainDir[H] -> Get_In_Use() << endl;
        }
        char bufy;

        cout << "Disk content: '";

        for (H = 0; H < DISK_SIZE; H++) {

            fseek(sim_disk_fd, H, SEEK_SET);

            fread( & bufy, 1, 1, sim_disk_fd);

            cout << bufy;

        }
        cout << "'" << endl;
    }
    // ------------------------------------------------------------------------
    void fsFormat(int blockSize) { // method that formatting the disk  by filling it with /0
        if (is_formated) {
            destructor();
            MainDir = (FileDescriptor ** ) realloc((void * ) MainDir, 0); //this means MainDir=NULL
            if (MainDir != NULL) { // the realloc is Failed
                free(MainDir);
                MainDir = NULL;
            }
            OpenFileDescriptors = (FileDescriptor ** ) realloc((void * ) OpenFileDescriptors, 0); //this means OpenFileDescriptors=NULL
            if (OpenFileDescriptors != NULL) { // the realloc is Failed
                free(OpenFileDescriptors);
                OpenFileDescriptors = NULL;
            }
            MainDir_Size = 0;
            OpenFileDescriptors_Size = 0;
        }
        is_formated = true;
        BitVectorSize = DISK_SIZE / blockSize;
        write_BackSlash_Zero(0, DISK_SIZE, 0);
        BitVector = new int[BitVectorSize];
        for (int H = 0; H < BitVectorSize; ++H) { // updating the BitVector for the blocks

            BitVector[H] = 0;
        }
        freeBlocks = BitVectorSize;
        block_size = blockSize;
        maxSize = Power(blockSize, 2);
    }
    // ------------------------------------------------------------------------
    int CreateFile(string fileName) { // creating new file, and for each new file we create a mainDir, openFileDescriptor arrays
        if (sim_disk_fd == NULL || !is_formated) {
            return -1;
        }
        int H;
        for (H = 0; H < MainDir_Size; H++) { // checking if the name has been used before
            if (MainDir[H] -> getFileName() == fileName) {
                return -1;
            }
        }
        if (freeBlocks == 0) { // checks if the disk is full
            return -1;
        }
        FsFile * Create_File;
        Create_File = new FsFile(block_size);
        MainDir_Size++;
        MainDir = (FileDescriptor ** ) realloc((void * ) MainDir, MainDir_Size * sizeof(FileDescriptor * )); // maximizing the mainDir array length
        if (MainDir == NULL) { // the realloc is Failed
            exit(EXIT_FAILURE);
        }
        MainDir[MainDir_Size - 1] = new FileDescriptor(fileName, Create_File);
        for (H = 0; H < OpenFileDescriptors_Size; H++) { // checks if one of the cells is equal to Null and placing it with the file
            if (OpenFileDescriptors[H] == NULL) {
                OpenFileDescriptors[H] = MainDir[MainDir_Size - 1];
                return H;
            }
        }
        OpenFileDescriptors_Size++;
        OpenFileDescriptors = (FileDescriptor ** ) realloc((void * ) OpenFileDescriptors, OpenFileDescriptors_Size * sizeof(FileDescriptor * )); // maximizing the OpenFileDescriptors array length
        if (OpenFileDescriptors == NULL) {
            exit(EXIT_FAILURE);
        }
        OpenFileDescriptors[OpenFileDescriptors_Size - 1] = MainDir[MainDir_Size - 1];
        return OpenFileDescriptors_Size - 1;
    }
    // ------------------------------------------------------------------------
    int OpenFile(string fileName) { // opening the file if its closed
        if (sim_disk_fd == NULL || !is_formated) {
            return -1;
        }
        for (int H = 0; H < MainDir_Size; H++) {
            if (MainDir[H] -> getFileName() == fileName && !MainDir[H] -> Get_In_Use()) { // if found the file and it was closed then add it to the file descriptor
                MainDir[H] -> _Set_In_Use(true);
                for (int K = 0; K < OpenFileDescriptors_Size; K++) {
                    if (OpenFileDescriptors[K] == NULL) { // if found a NUll in openFileDescriptor then place it with a pointer
                        OpenFileDescriptors[K] = MainDir[H];
                        return K;
                    }
                }
                OpenFileDescriptors_Size++;
                OpenFileDescriptors = (FileDescriptor ** ) realloc((void * ) OpenFileDescriptors, OpenFileDescriptors_Size * sizeof(FileDescriptor * )); // maximizing the OpenFileDescriptors array length
                if (OpenFileDescriptors == NULL) {
                    exit(EXIT_FAILURE);
                }
                OpenFileDescriptors[OpenFileDescriptors_Size - 1] = MainDir[H];
                return OpenFileDescriptors_Size - 1;
            }
            if (MainDir[H] -> getFileName() == fileName && MainDir[H] -> Get_In_Use()) { // if found the file and it was open .. throw an error
                return -1;
            }
        }
        return -1;
    }
    // ------------------------------------------------------------------------
    string CloseFile(int fd) { // closing the file if it was open
        if (sim_disk_fd == NULL || !is_formated) {
            return "-1";
        }
        if (fd >= OpenFileDescriptors_Size || fd < 0) {
            return "-1";
        }
        if (OpenFileDescriptors[fd] == NULL) {
            return "-1";
        }
        OpenFileDescriptors[fd] -> _Set_In_Use(false);
        OpenFileDescriptors[fd] = NULL; // removing the file from the OpenFileDescriptors and placing it with null
        return "1";
    }
    // ------------------------------------------------------------------------
    int WriteToFile(int fd, char * buf, int len) { // writes the string that receives it to the file i the file already opened by writing into the blocks
        if (sim_disk_fd == NULL || !is_formated || fd >= OpenFileDescriptors_Size || len <= 0 || OpenFileDescriptors[fd] == NULL) { // conditions that we dont write into the file while them succeed
            return -1;
        }
        bool isNoSpace= false;
        if (len > maxSize - OpenFileDescriptors[fd] -> Get_fs_file() -> getfile_size()) {
            len = maxSize - OpenFileDescriptors[fd] -> Get_fs_file() -> getfile_size();
            isNoSpace= true;
        }
        int len_Blocks = 0;
        len_Blocks = ceil((double)((double) len / (double) block_size)) + 1; // giving the num of blocks that needed of writing + index block
        int The_Index_Of_Index_Block = 0, Block_In_The_File = 0;
        char Char;
        int Index = 0;
        if (OpenFileDescriptors[fd] -> Get_fs_file() -> _GetIndexBlock() != -1) { // if the file has been written on it before then continue to write in the empty place
            int Used_block = ceil((double)((double) OpenFileDescriptors[fd] -> Get_fs_file() -> getfile_size() / (double) block_size)); // num of the blocks that have been used
            int Remainder = OpenFileDescriptors[fd] -> Get_fs_file() -> getfile_size() % block_size; // return the num of how much has been written in the final block of the file
            if (Remainder == 0) { // the final block is full
                len_Blocks = ceil((double)((double) len / (double) block_size)); // giving the num of blocks that needed of writing
            } else {
                if ((len - (block_size - Remainder)) <= 0) { // if the info i want to write is less or equal to the space of the final block then we dont need more  blocks
                    len_Blocks = 0;
                } else { // if the info i want to write is larger than the space of the final block then we  need more  blocks
                    len_Blocks = ceil(double((double)(len - (block_size - Remainder)) / (double) block_size));
                }
            }
            Index = 0;
            int HowMuchIsLeftToWrite = len;
            if (Remainder != 0) { // if i have an empty space on the final block then use it
                fseek(sim_disk_fd, OpenFileDescriptors[fd] -> Get_fs_file() -> _GetIndexBlock() * block_size + Used_block - 1, SEEK_SET);
                fread( & Char, 1, 1, sim_disk_fd);
                int position = ReadFromIndexBlock(Char);
                fseek(sim_disk_fd, position * block_size + Remainder, SEEK_SET);
                if (len_Blocks == 0) { // if the empty space bigger than the info i want to write then write it all at the final block
                    fwrite( & buf[Index], len, 1, sim_disk_fd);
                    Index = len;
                    HowMuchIsLeftToWrite = 0;
                } else {
                    fwrite( & buf[Index], block_size - Remainder, 1, sim_disk_fd);
                    Index = block_size - Remainder;
                    HowMuchIsLeftToWrite = len - Index;
                }
            }
            if (HowMuchIsLeftToWrite > freeBlocks * block_size) { // if the num of the blocks that I need is bigger than the empty block i have now, then we cant write
                len = freeBlocks * block_size + len - HowMuchIsLeftToWrite;
                isNoSpace= true;
            }
            if (Index != len) { // if i have more info to write
                for (int H = 0; H < BitVectorSize; H++) {
                    if (Used_block >= block_size || Index == len) break;
                    if (BitVector[H] == 0) {
                        BitVector[H] = 1;
                        fseek(sim_disk_fd, OpenFileDescriptors[fd] -> Get_fs_file() -> _GetIndexBlock() * block_size + Used_block, SEEK_SET);
                        Used_block++;
                        freeBlocks--;
                        Char = decToBinary(H, Char);
                        fwrite( & Char, 1, 1, sim_disk_fd);
                        if (len - Index < block_size) { //  if the empty space bigger than the info i want to write then write it all at the  block
                            fseek(sim_disk_fd, (H * block_size), SEEK_SET);
                            fwrite( & buf[Index], len - Index, 1, sim_disk_fd);
                            Index = len;
                            break;
                        } else { // write with block size length
                            fseek(sim_disk_fd, (H * block_size), SEEK_SET);
                            fwrite( & buf[Index], block_size, 1, sim_disk_fd);
                            Index = Index + block_size;
                        }
                    }
                }
            }
        }
        if (OpenFileDescriptors[fd] -> Get_fs_file() -> _GetIndexBlock() == -1) { // if I don't have an index block
            if (len_Blocks > freeBlocks) { // if the num of the blocks that I need is bigger than the empty block i have now, then we cant write
                len_Blocks = freeBlocks;
                len = (freeBlocks - 1) * block_size;
                isNoSpace= true;
            }
            The_Index_Of_Index_Block = ReturnIndexBlock(fd);
            len_Blocks--; // decreasing the needed block with 1 because i found an indexed block
            for (int H = 0; H < BitVectorSize; H++) {
                if (Block_In_The_File >= len_Blocks || Index == len) break;
                if (BitVector[H] == 0) {
                    BitVector[H] = 1;
                    fseek(sim_disk_fd, The_Index_Of_Index_Block * block_size + Block_In_The_File, SEEK_SET);
                    Char = decToBinary(H, Char);
                    fwrite( & Char, 1, 1, sim_disk_fd);
                    freeBlocks--;
                    Block_In_The_File++;
                    if (len - Index < block_size) { //  if the empty space bigger than the info N want to write then write it all at the  block
                        fseek(sim_disk_fd, (H * block_size), SEEK_SET);
                        fwrite( & buf[Index], len - Index, 1, sim_disk_fd);
                        Index = len;
                        break;
                    } else { // write with block size length
                        fseek(sim_disk_fd, (H * block_size), SEEK_SET);
                        fwrite( & buf[Index], block_size, 1, sim_disk_fd);
                        Index = Index + block_size;
                    }
                }
            }
        }
        OpenFileDescriptors[fd] -> Get_fs_file() -> _SetFileSize(len + OpenFileDescriptors[fd] -> Get_fs_file() -> getfile_size()); // updating the file size after writing
        int FullBlockFinal = ceil((double)((double) OpenFileDescriptors[fd] -> Get_fs_file() -> getfile_size() / (double) block_size)); // num of the blocks that the file used  without index block
        OpenFileDescriptors[fd] -> Get_fs_file() -> _SetBlockInUse(FullBlockFinal); // updating the num of the blocks that the file used
        if(len==0||isNoSpace) return -1;
        return len;
    }
    // ------------------------------------------------------------------------
    int DelFile(string FileName) { // deleting the file from the disk if the file was closed
        if (sim_disk_fd == NULL || !is_formated) {
            return -1;
        }
        int MainDir_Index = -1, OpenFileDescriptors_Index = 0;
        int Index = 0;
        while (Index < MainDir_Size) { // looking for the name if found in the mainDir
            if (MainDir[Index] -> getFileName() == FileName) {
                MainDir_Index = Index;
                break;
            }
            Index++;
        }
        if (MainDir_Index == -1) { // name not found at mainDir
            return -1;
        }
        if (MainDir[MainDir_Index] -> Get_In_Use()) { // if the file is opened
            return -1;
        }
        if (MainDir[MainDir_Index] -> Get_fs_file() -> _GetIndexBlock() == -1) { // if i dont have an index block then delete
            OpenFileDescriptors_Index = Delete(FileName, MainDir_Index);
            return OpenFileDescriptors_Index;
        }
        int Used_block = ceil((double)((double) MainDir[MainDir_Index] -> Get_fs_file() -> getfile_size() / (double) block_size)); // num of the blocks the the file use without index blocks
        char Char;
        for (int H = 0; H < Used_block; H++) { // filling the file and the index blocks with /0
            fseek(sim_disk_fd, MainDir[MainDir_Index] -> Get_fs_file() -> _GetIndexBlock() * block_size + H, SEEK_SET);
            fread( & Char, 1, 1, sim_disk_fd);
            int position = ReadFromIndexBlock(Char);
            freeBlocks++;
            BitVector[position] = 0;
            write_BackSlash_Zero(0, block_size, (position * block_size));
        }
        write_BackSlash_Zero(0, block_size, (MainDir[MainDir_Index] -> Get_fs_file() -> _GetIndexBlock() * block_size));
        freeBlocks++;
        BitVector[MainDir[MainDir_Index] -> Get_fs_file() -> _GetIndexBlock()] = 0;
        OpenFileDescriptors_Index = Delete(FileName, MainDir_Index);
        return OpenFileDescriptors_Index;
    }
    // ------------------------------------------------------------------------
    int ReadFromFile(int fd, char * buf, int len) { // read from the file if it was opened
        if (sim_disk_fd == NULL || !is_formated || len < 0 || fd >= OpenFileDescriptors_Size || OpenFileDescriptors[fd] == NULL) { // conditions that we dont write into the file while them succeed
            buf[0] = '\0';
            return -1;
        }
        if (len > OpenFileDescriptors[fd] -> Get_fs_file() -> getfile_size()) { // read only as the giving size
            len = OpenFileDescriptors[fd] -> Get_fs_file() -> getfile_size();
        }
        if (len == 0) { // to not read anything at all
            buf[0] = '\0';
            return 0;
        }
        int len_Blocks = ceil((double)((double) len / (double) block_size)); // num of the blocks that the len reads of it
        int Index = 0;
        char Char;
        for (int H = 0; H < len_Blocks; H++) {
            fseek(sim_disk_fd, OpenFileDescriptors[fd] -> Get_fs_file() -> _GetIndexBlock() * block_size + H, SEEK_SET);
            fread( & Char, 1, 1, sim_disk_fd);
            int position = ReadFromIndexBlock(Char);
            fseek(sim_disk_fd, position * block_size, SEEK_SET);
            if (len - Index < block_size) { //   if the empty space bigger than the info i want to write then write it all at the  block
                fread( & buf[Index], len - Index, 1, sim_disk_fd);
                Index = len;
                break;
            } else { // write with block size length
                fread( & buf[Index], block_size, 1, sim_disk_fd);
                Index = Index + block_size;
            }
        }
        buf[Index] = '\0';
        return 0;
    }
};
int main() {
    int blockSize;
    string fileName;
    char str_to_write[DISK_SIZE];
    char str_to_read[DISK_SIZE];
    int size_to_read;
    int _fd;
    int Write;

    fsDisk * fs = new fsDisk();
    int cmd_;
    while (1) {
        cin >> cmd_;

        switch (cmd_) {
            case 0: // exit
            delete fs;
            exit(0);
            break;

            case 1: // list-file
            fs -> listAll();
            break;

            case 2: // format
            cin >> blockSize;
            fs -> fsFormat(blockSize);
            break;

            case 3: // creat-file
            cin >> fileName;
            _fd = fs -> CreateFile(fileName);
            cout << "CreateFile: " << fileName << " with File Descriptor #: " << _fd << endl;
            break;

            case 4: // open-file
            cin >> fileName;
            _fd = fs -> OpenFile(fileName);
            cout << "OpenFile: " << fileName << " with File Descriptor #: " << _fd << endl;
            break;

            case 5: // close-file
            cin >> _fd;
            fileName = fs -> CloseFile(_fd);
            cout << "CloseFile: " << fileName << " with File Descriptor #: " << _fd << endl;
            break;

            case 6: // write-file
            cin >> _fd;
            cin >> str_to_write;
            // fs->WriteToFile(_fd, str_to_write, strlen(str_to_write));
            Write = fs -> WriteToFile(_fd, str_to_write, strlen(str_to_write));
            cout << "Writed: " << Write << " Char's into File Descriptor #: " << _fd << endl;
            break;

            case 7: // read-file
            cin >> _fd;
            cin >> size_to_read;
            fs -> ReadFromFile(_fd, str_to_read, size_to_read);
            cout << "ReadFromFile: " << str_to_read << endl;
            break;

            case 8: // delete file
            cin >> fileName;
            _fd = fs -> DelFile(fileName);
            cout << "DeletedFile: " << fileName << " with File Descriptor #: " << _fd << endl;
            break;
            default:
                break;
        }
    }
}
