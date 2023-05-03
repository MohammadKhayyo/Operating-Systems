

/*********************************************************** LIBRARIES *********************************************************************/
// libraries that I used for this project
#include <iostream>

#include <vector>

#include <map>

#include <assert.h>

#include <string.h>

#include <math.h>

#include <fcntl.h>

using namespace std;

#define DISK_SIZE 256

#define DISK_SIM_FILE "DISK_SIM_FILE.txt"
/*********************************************************** HELPING METHODS *********************************************************************/

// this helping method is used to convert the number from binary to decimal
int TOINT(char & c) {
    int toINT = 0;
    int Const = 2;
    int Const1;
    Const1 = pow(Const, 3);
    int Save, Save1, Save2;
    for (int R = 0; R < Const1; ++R) {
        Save = (c >> R);
        Save1 = (1u & Save);
        Save2 = pow(Const, R);
        toINT += (Save1 * Save2);
    }
    return toINT;
}

// this helping method is used to convert a number from decimal to binary
char decToBinary(int n, char & c) {
    // array to store binary number
    int binaryNum[8];
    // counter for binary array
    int i = 0;
    while (n > 0) {
        // storing remainder in binary array
        binaryNum[i] = n % 2;
        n = n / 2;
        i++;
    }
    c = c & 0;
    // printing binary array in reverse order
    for (int j = i - 1; j >= 0; j--) {
        if (binaryNum[j] == 1)
            c = c | 1u << j;
    }
    return c;
}

/*********************************************************** CLASSES DEFINITION *********************************************************************/
class FsFile {
    // features of FsFile class
    int file_size;

    int block_in_use;

    int index_block;

    int block_size;

public:
    FsFile(int _block_size) {
        // FsFile variables initialization
        file_size = 0;

        block_in_use = 0;

        block_size = _block_size;

        index_block = -1;

    }
    //setters and getters
    int getfile_size() {
        return file_size;
    }
    void setfile_size(int fileSize) {
        file_size = fileSize;
    }
    int getblock_in_use() {
        return block_in_use;
    }
    void setblock_in_use(int blockinuse) {
        block_in_use = blockinuse;
    }
    int getblocksize() {
        return block_size;
    }
    void setblocksize(int blocksize) {
        block_size = blocksize;
    }
    int getindexblock() {
        return index_block;
    }
    void setindexblock(int indexblock) {
        index_block = indexblock;
    }

};

class FileDescriptor {
    // features of FileDescriptor class

    string file_name;
    FsFile * fs_file;
    bool inUse;
public:
    FileDescriptor(string FileName, FsFile * fsi) {
        //// FsFile variables initialization
        file_name = FileName;
        fs_file = fsi;
        inUse = true;
    }
    //setters and getters
    string getFileName() {
        return file_name;
    }
    void setFileName(string FileName) {
        file_name = FileName;
    }

    FsFile * getfsfile() {
        return fs_file;
    }
    int getinuse() {
        return inUse;
    }
    void setinuse(bool inuse) {
        inUse = inuse;
    }
};

class fsDisk {
    // features of fsDisk class
    FILE * sim_disk_fd;
    bool is_formated;
    // BitVector - "bit" (int) vector, indicate which block in the disk is free

    //              or not.  (i.e. if BitVector[0] == 1 , means that the

    //             first block is occupied.
    int BitVectorSize;

    int * BitVector;

    // filename and one fsFile.

    // MainDir;
    // Unix directories are lists of association structures,
    // each of which contains one filename and one inode number.
    // creating a map for MainDir (map is the data structure that I chose for this project)
    map < string, FileDescriptor * > MainDir;

    // OpenFileDescriptors --  when you open a file,

    // the operating system creates an entry to represent that file

    // This entry number is the file descriptor.

    // OpenFileDescriptors;
    // OpenFileDescriptors --  when you open a file,
    // the operating system creates an entry to represent that file
    // This entry number is the file descriptor.
    // creating a map for OpenFileDescriptors (map is the data structure that I chose for this project)
    map < int, FileDescriptor * > OpenFileDescriptors;

    int block_size;

    int maxSize;

    int freeBlocks;

    // functions that has been used in the class
public:
    // initialize the class so we could start
    fsDisk() {
        sim_disk_fd = fopen(DISK_SIM_FILE, "w+");

        assert(sim_disk_fd);

        for (int i = 0; i < DISK_SIZE; i++) {

            int ret_val = fseek(sim_disk_fd, i, SEEK_SET);

            ret_val = fwrite("\0", 1, 1, sim_disk_fd);

            assert(ret_val == 1);

        }

        fflush(sim_disk_fd);

        block_size = 0;

        is_formated = false;

    }
    // destructor of the class that reached when we  delete any objects "of type fsDisk"
    ~fsDisk() {
        for (auto iterator = MainDir.cbegin(); iterator != MainDir.cend(); ++iterator) {
            delete(iterator -> second -> getfsfile());
            delete(iterator -> second);
        }
        MainDir.clear();
        OpenFileDescriptors.clear();
        delete[] BitVector;
        fclose(sim_disk_fd);
    }
    /*********************************************************** FS_DISK MAIN METHODS *********************************************************************/

    /*********************************************************** Method 1 *********************************************************************/
    //print the list of the files that created on the disk and the contents of the disk as well
    void listAll() {
        int i = 0;
        // printing the mainDir
        for (auto iterator = MainDir.cbegin(); iterator != MainDir.cend(); ++iterator) {
            cout << "index: " << i << ": FileName: " << iterator -> first << " , isInUse: " << iterator -> second -> getinuse() << endl;
            i++;
        }
        char bufy;
        cout << "Disk content: '";
        for (i = 0; i < DISK_SIZE; i++) {
            int ret_val = fseek(sim_disk_fd, i, SEEK_SET);
            ret_val = fread( & bufy, 1, 1, sim_disk_fd);
            cout << bufy;
        }
        cout << "'" << endl;
    }
    /*********************************************************** Method 2 *********************************************************************/
    //to fill the disk with zeros “/0” (to format the disk)
    void fsFormat(int blockSize) {
        // if the disk pass format before
        if (is_formated) {
            // deleting the pointers on files
            for (auto iterator = MainDir.cbegin(); iterator != MainDir.cend(); ++iterator) {
                delete(iterator -> second -> getfsfile());
                delete(iterator -> second);
            }
            MainDir.clear();
            OpenFileDescriptors.clear();
        }
        this -> is_formated = true;
        this -> block_size = blockSize;
        this -> BitVectorSize = DISK_SIZE / blockSize;
        this -> BitVector = new int[BitVectorSize];
        freeBlocks = DISK_SIZE / blockSize;
        // filling the bit vector with zeros
        for (int i = 0; i < BitVectorSize; i++) {
            BitVector[i] = 0;
        }
        maxSize = blockSize * block_size;
    }
    /*********************************************************** Method 3 *********************************************************************/

    //create a new file, and it builds for each file a new main directory/open_file_descriptor array, if the file is already created it throw an error(-1).
    int CreateFile(string fileName) {
        // checks if the file doesn't formatted
        if (!is_formated)
            return -1;
        // build an iterator form the type map
        std::map < string, FileDescriptor * > ::iterator firstIterator;
        // variable that looking for the file
        firstIterator = MainDir.find(fileName);
        // checks if the file is already created
        if (firstIterator != MainDir.end()) {
            return -1;
        }
        FsFile * fs = new FsFile(block_size);
        // new file creation
        FileDescriptor * fd = new FileDescriptor(fileName, fs);
        // mainDir array insertion
        MainDir.insert(std::pair < string, FileDescriptor * > (fileName, fd));
        int tempInd = 0;
        bool ISNull = false;
        // build an iterator form the type map
        std::map < int, FileDescriptor * > ::iterator secondIterator;

        for (auto iterator = OpenFileDescriptors.cbegin(); iterator != OpenFileDescriptors.cend(); ++iterator) {
            // looking for values equal tu NULL
            if (iterator -> second == NULL) {
                ISNull = true;
                break;
            }
            tempInd++;
        }
        // if we find a place is equal to null then we insert the fd
        if (ISNull) {
            secondIterator = OpenFileDescriptors.find(tempInd);
            secondIterator -> second = fd;
            return tempInd;
        }
        // OpenFileDescriptors array insertion
        OpenFileDescriptors.insert(std::pair < int, FileDescriptor * > (OpenFileDescriptors.size(), fd));
        return OpenFileDescriptors.size() - 1;
    }
    /*********************************************************** Method 4 *********************************************************************/
    //opening the file when its closed and if the file is already opened then throw an error(-1).
    int OpenFile(string fileName) {
        // checks if the file doesn't formatted
        if (!is_formated)
            return -1;
        // build an iterator form the type map
        std::map < string, FileDescriptor * > ::iterator firstIterator;
        // finding the file wa wanna delete
        firstIterator = MainDir.find(fileName);
        // if the file is not found
        if (firstIterator == MainDir.end()) {
            return -1;
        }
        // if the file is already opened
        if (firstIterator -> second -> getinuse()) {
            return -1;
        }
        int tempInd = 0;
        bool ISNull = false;
        firstIterator -> second -> setinuse(true);
        // build an iterator form the type map
        std::map < int, FileDescriptor * > ::iterator secondIterator;

        for (auto iterator = OpenFileDescriptors.cbegin(); iterator != OpenFileDescriptors.cend(); ++iterator) {
            // looking for values equal tu NULL
            if (iterator -> second == NULL) {
                ISNull = true;
                break;
            }
            tempInd++;
        }
        // if we find a place is equal to null then we insert the fd
        if (ISNull) {
            secondIterator = OpenFileDescriptors.find(tempInd);
            secondIterator -> second = firstIterator -> second;
            return tempInd;
        }
        // OpenFileDescriptors insertion
        OpenFileDescriptors.insert(std::pair < int, FileDescriptor * > (OpenFileDescriptors.size(), firstIterator -> second));
        return OpenFileDescriptors.size() - 1;
    }
    /*********************************************************** Method 5 *********************************************************************/

    //closing the file when its opened, and if the file is already closed it throw an error(-1).
    string CloseFile(int fd) {
        // checks if the file doesn't formatted
        if (!is_formated)
            return "-1";

        // build an iterator form the type map
        std::map < int, FileDescriptor * > ::iterator secondIterator;
        // finding the file we want to delete
        secondIterator = OpenFileDescriptors.find(fd);
        // if the file is not found
        if (secondIterator == OpenFileDescriptors.end()) {
            return "-1";
        }
        // checks if the file is already closed
        if (secondIterator -> second == NULL) {
            return "-1";
        }
        // we give the permission to file the open
        if (secondIterator -> second != NULL) {
            secondIterator -> second -> setinuse(false);
            secondIterator -> second = NULL;
        }
        return "1";
    }
    /*********************************************************** Method 6 *********************************************************************/

    // write the info the receives in the buffer into the file or the blocks when the file is already opened,
    // if we couldn't find the file at the file descriptor or if the file is closed it will throw an error(-1).
    int WriteToFile(int fd, char * buf, int len) {
        // checks if the file doesn't formatted
        if (!is_formated)
            return -1;
        // build an iterator form the type map
        std::map < int, FileDescriptor * > ::iterator secondIterator;
        // finding the file we want to delete
        secondIterator = OpenFileDescriptors.find(fd);
        // File Is Not IN OpenFileDescriptors
        if (secondIterator == OpenFileDescriptors.end()) {
            return -1;
        }
        // File Is already closed
        if (secondIterator -> second == NULL) {
            return -1;
        }
        // File Is Full
        if (block_size - secondIterator -> second -> getfsfile() -> getfile_size() == maxSize) {
            return -1;
        }
        //there is no space
        if (block_size * block_size - secondIterator -> second -> getfsfile() -> getfile_size() < len) {
            len = block_size * block_size - secondIterator -> second -> getfsfile() -> getfile_size();
        }
        char d;
        int Iwrite = 0;
        int i;
        bool isEmpty = false;
        // if we don't have an indexed block
        if (secondIterator -> second -> getfsfile() -> getindexblock() == -1) {
            for (i = 0; i < BitVectorSize; ++i) {
                if (BitVector[i] == 0) {
                    BitVector[i] = 1;
                    freeBlocks--;
                    secondIterator -> second -> getfsfile() -> setindexblock(i);
                    isEmpty = true;
                    break;
                }
            }
            // if there is no space
            if (!isEmpty) {
                return -1;
            }
            // number of blocks larger than the number of the empty blocks, there is no space to write
            if (len > freeBlocks * block_size) {
                len = freeBlocks * block_size;
            }
            // loop that used to write on the file
            for (i = 0;; i++) {
                if (len == Iwrite) break;
                if (BitVector[i] == 0) {
                    BitVector[i] = 1;
                    freeBlocks--;
                    fseek(sim_disk_fd, (secondIterator -> second -> getfsfile() -> getindexblock() * block_size) + secondIterator -> second -> getfsfile() -> getblock_in_use(), SEEK_SET);
                    d = decToBinary(i, d);
                    fwrite( & d, 1, 1, sim_disk_fd);
                    secondIterator -> second -> getfsfile() -> setblock_in_use(secondIterator -> second -> getfsfile() -> getblock_in_use() + 1);
                    fseek(sim_disk_fd, (i * block_size), SEEK_SET);
                    for (int j = 0; j < block_size; ++j) {
                        if (len == Iwrite) break;
                        fwrite( & buf[Iwrite], 1, 1, sim_disk_fd);
                        Iwrite++;
                    }
                }
            }
            secondIterator -> second -> getfsfile() -> setfile_size(len);
        }
        // if we have an indexed block
        else {
            Iwrite = 0;
            // if we still have a space at the final block
            if (secondIterator -> second -> getfsfile() -> getfile_size() != (secondIterator -> second -> getfsfile() -> getblock_in_use() * block_size)) {
                fseek(sim_disk_fd, secondIterator -> second -> getfsfile() -> getindexblock() * block_size + secondIterator -> second -> getfsfile() -> getblock_in_use() - 1, SEEK_SET);
                fread( & d, 1, 1, sim_disk_fd);
                int location = TOINT(d);
                fseek(sim_disk_fd, location * block_size + secondIterator -> second -> getfsfile() -> getfile_size() % block_size, SEEK_SET);
                fwrite( & buf[Iwrite], block_size - (secondIterator -> second -> getfsfile() -> getfile_size() % block_size), 1, sim_disk_fd);
                Iwrite += block_size - (secondIterator -> second -> getfsfile() -> getfile_size() % block_size);
            }
            if (len - Iwrite > freeBlocks * block_size) {
                len = freeBlocks * block_size + Iwrite;
            }
            // writing for the new blocks
            for (i = 0;; i++) {
                if (len == Iwrite) break;
                if (BitVector[i] == 0) {
                    BitVector[i] = 1;
                    freeBlocks--;
                    fseek(sim_disk_fd, (secondIterator -> second -> getfsfile() -> getindexblock() * block_size) + secondIterator -> second -> getfsfile() -> getblock_in_use(), SEEK_SET);
                    d = decToBinary(i, d);
                    fwrite( & d, 1, 1, sim_disk_fd);
                    secondIterator -> second -> getfsfile() -> setblock_in_use(secondIterator -> second -> getfsfile() -> getblock_in_use() + 1);
                    fseek(sim_disk_fd, (i * block_size), SEEK_SET);
                    for (int j = 0; j < block_size; ++j) {
                        if (len == Iwrite) {
                            break;
                        }
                        fwrite( & buf[Iwrite], 1, 1, sim_disk_fd);
                        Iwrite++;
                    }
                }
            }
            secondIterator -> second -> getfsfile() -> setfile_size(secondIterator -> second -> getfsfile() -> getfile_size() + len);
        }
        return len;
    }
    /*********************************************************** Method 7 *********************************************************************/

    //to delete the file from the disk and only when the file is closed. If the file is open or file is not found it will throw an error(-1).
    int DelFile(string FileName) {
        // checks if the file doesn't formatted
        if (!is_formated)
            return -1;
        char d;
        // building an iterator form the type map
        std::map < string, FileDescriptor * > ::iterator secondIterator;
        // finding the file we wanna delete
        secondIterator = MainDir.find(FileName);
        // file is not found
        if (secondIterator == MainDir.end()) {
            return -1;
        }
        // if the file is already opened
        if (secondIterator -> second -> getinuse()) {
            return -1;
        }
        // deleting the file that hasn't indexed block
        if (secondIterator -> second -> getfsfile() -> getindexblock() == -1) {
            delete(secondIterator -> second -> getfsfile());
            delete(secondIterator -> second);
            MainDir.erase(secondIterator);
        }
        // if it has an indexed block
        else {
            // filling the blocks with /0
            for (int i = 0; i < secondIterator -> second -> getfsfile() -> getblock_in_use(); ++i) {
                fseek(sim_disk_fd, secondIterator -> second -> getfsfile() -> getindexblock() * block_size + i, SEEK_SET);
                fread( & d, 1, 1, sim_disk_fd);
                int location = TOINT(d);
                BitVector[location] = 0;
                fseek(sim_disk_fd, location * block_size, SEEK_SET);
                for (int j = 0; j < block_size; ++j) {
                    fwrite("\0", 1, 1, sim_disk_fd);
                }
            }
            // filing the indexed blocks with /0
            for (int i = 0; i < block_size; i++) {
                BitVector[secondIterator -> second -> getfsfile() -> getindexblock()] = 0;
                fseek(sim_disk_fd, secondIterator -> second -> getfsfile() -> getindexblock() * block_size + i, SEEK_SET);
                fwrite("\0", 1, 1, sim_disk_fd);
            }
            delete(secondIterator -> second -> getfsfile());
            delete(secondIterator -> second);
            MainDir.erase(secondIterator);
        }
        return 1;
    }
    /*********************************************************** Method 8 *********************************************************************/

    // to read from the file and only when the file is open,
    // if we couldn’t find the file at the file descriptor or if the file is closed or if the buffer is empty it will throw an error (-1).
    int ReadFromFile(int fd, char * buf, int len) {
        // checks if the file doesn't formatted
        if (!is_formated) {
            buf[0] = '\0';
            return -1;
        }
        // there is nothing to read
        if (len < 0) {
            buf[0] = '\0';
            return -1;
        }
        // building an iterator form the type map
        std::map < int, FileDescriptor * > ::iterator secondIterator;
        // finding the file we wanna delete
        secondIterator = OpenFileDescriptors.find(fd);
        // file doesn't found at the OpenFileDescriptors
        if (secondIterator == OpenFileDescriptors.end()) {
            return -1;
        }
        // if the length is equal to 0
        if (len == 0) {
            buf[0] = '\0';
            return 0;
        }
        int tempInd = 0;
        char d;
        // reading from the blocks
        for (int j = 0; j < secondIterator -> second -> getfsfile() -> getblock_in_use() && tempInd < len; j++) {
            fseek(sim_disk_fd, (secondIterator -> second -> getfsfile() -> getindexblock() * block_size) + j, SEEK_SET);
            fread( & d, 1, 1, sim_disk_fd);
            int location = TOINT(d);
            fseek(sim_disk_fd, location * block_size, SEEK_SET);
            for (int i = 0; i < block_size; ++i) {
                if (tempInd == len) break;
                fread( & buf[tempInd], 1, 1, sim_disk_fd);
                tempInd++;
            }
        }
        buf[tempInd] = '\0';
        return fd;
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
/*********************************************************** END O THE PROJECT  *********************************************************************/