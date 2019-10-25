#include <iostream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <pwd.h>
#include <cerrno>
#include <grp.h>
#include <ctime>
#include <cstdio>
#include <dirent.h>
#include <vector>
#include <string.h>
#include <fcntl.h>
#include "FileManager.h"

// Ben Tilden
// File Manager Constructor with implemented methods
// 3 October 2019

using namespace std;

// Constructor
// Initializes all file attributes using stat
// Take parameter of a file path
// Crates FileManager object

FileManager::FileManager(const char *file){

    struct stat s;
    if(stat(file, &s) != 0){
        errorNumber = errno;
        cout << "Stat failed\n" << endl;
        perror(strerror(errorNumber));
    };

    struct passwd *p = getpwuid(s.st_uid);
    struct group *g = getgrgid(s.st_gid);
    
    // Setting attributes
    
    fileName = file;
    fileType = (unsigned long) s.st_mode;
    fileSize = (long long) s.st_size;
    fileOwnerId = (long) s.st_uid;
    fileOwnerUsername =  &*p->pw_name;
    fileGroupId = (long) s.st_gid;
    fileGroupName =  g->gr_name;
    
    // Checking permissions
    
    if (S_ISDIR(s.st_mode)) { filePermissions.append("d"); } else { filePermissions.append("-"); }
    if (S_IRUSR & s.st_mode) { filePermissions.append("r"); } else { filePermissions.append("-"); }
    if (S_IWUSR & s.st_mode) { filePermissions.append("w"); } else { filePermissions.append("-"); }
    if (S_IXUSR & s.st_mode) { filePermissions.append("x"); } else { filePermissions.append("-"); }
    if (S_IRGRP & s.st_mode) { filePermissions.append("r"); } else { filePermissions.append("-"); }
    if (S_IWGRP & s.st_mode) { filePermissions.append("w"); } else { filePermissions.append("-"); }
    if (S_IXGRP & s.st_mode) { filePermissions.append("x"); } else { filePermissions.append("-"); }
    if (S_IROTH & s.st_mode) { filePermissions.append("r"); } else { filePermissions.append("-"); }
    if (S_IWOTH & s.st_mode) { filePermissions.append("w"); } else { filePermissions.append("-"); }
    if (S_IXOTH & s.st_mode) { filePermissions.append("x"); } else { filePermissions.append("-"); }
    
    // Getting last time attributes
    
    fileLastAccess =  ctime(&s.st_atime);
    fileLastModification = ctime(&s.st_mtime);
    fileLastStatusChange = ctime(&s.st_ctime);
    
    fileBlockSize = (long) s.st_blksize;
    errorNumber = 0;
}

// Destructor
// Destructs a FileManager object and deletes any children the object
// may have
// No parameters needed
// No return

FileManager::~FileManager() {
    
    if(children.size() > 0){
        for(auto x : children){
            delete x;
        }
        children.clear();
    }
}

// Getter methods
// Used to retreive all file attributes
// No parameters
// Returns requested attribute

const char* FileManager::getFileName() {  return fileName; }
unsigned long FileManager::getFileType() { return fileType; }
long long FileManager::getFileSize() { return fileSize; }
long FileManager::getFileOwnerId() { return fileOwnerId; }
char * FileManager::getFileOwnerUsername() { return fileOwnerUsername; }
long FileManager::getFileGroupId() { return fileGroupId; }
char * FileManager::getFileGroupName() { return fileGroupName; }
std::string FileManager::getFilePermissions() { return filePermissions; }
char* FileManager::getFileLastAccess() { return fileLastAccess; }
char* FileManager::getFileLastModified() { return fileLastModification; }
char* FileManager::getFileLastStatusChange() { return fileLastStatusChange; }
long FileManager::getFileBlockSize() { return fileBlockSize; }
int FileManager::getErrorNumber() { return errorNumber; }
char * FileManager::getErrorString() { return strerror(errorNumber); }

// Dump
// Copies the current FileManager object into an input ostream
// Take parameter of an ostream
// No return

void FileManager::dumpFile(std::ostream& inputStream) {
    
    if(!S_ISREG(fileType)){
        errorNumber = ENOTSUP;
        perror(strerror(errorNumber));
    }
    
    // Copy ifstream of file to input ostream
    
    char buf[fileBlockSize];
    ifstream fileStreamer(fileName);
    while(!fileStreamer.eof()){
        fileStreamer.getline(buf, fileBlockSize);
        inputStream << buf << endl;
    }
    fileStreamer.close();
    errorNumber = 0;
}

// Rename file
// Renames a file by changing its path directly
// Take parameter of the new file path
// No return value

void FileManager::renameFile(const char *newFileName) {
    
    if(rename(fileName, newFileName) == 0){
        fileName = newFileName;
        errorNumber = 0;
    }
    else{
        errorNumber = ENOENT;
        perror(strerror(errorNumber));
    }
}
// Remove file
// Removes a file using the remove function which
// in turn will call unlink() if needed to remove a file
// from the system
// Takes parameter of a file path
// No return

void FileManager::removeFile(const char *fileToRemove){
    
    if(remove(fileToRemove) == 0){
        errorNumber = 0;
    }
    else {
        errorNumber = ENOENT;
        perror(strerror(errorNumber));
    }
}

// Compare File
// Compares 2 files char by char to determine similarity
// Take parameter of another FileManager object to compare
// Return true if files are the same
// Return false if files are different

bool FileManager::compareFile(FileManager fileObject) {
    
    if(S_ISREG(fileType) && S_ISREG(fileObject.getFileType())){
        fstream file1, file2;
        
        file1.open(fileName, ios::in);
        file2.open(fileObject.getFileName(), ios::in);
        
        char char1, char2;
        // Compare files by character
        while(true){
            char1 = file1.get();
            char2 = file2.get();
            if(char1 != char2){
                return false;
            }
            if((char1==EOF) || (char2==EOF)){
                break;
            }
        }
        file1.close();
        file2.close();
        return true;
        errorNumber = 0;
    }
    
    else{
        errorNumber = EINVAL;
        perror(strerror(errorNumber));
        return false;
    }
    return false;
}

// Expand File
// Opens a directory and creates FileManager objects for all files
// and directories inside the directory and adds them to the directory
// children vector attribute
// No parameter
// No return, however it outputs a list of children

void FileManager::expandFile() {

    if(S_ISDIR(fileType)) {
        
        DIR * directory = opendir(fileName);
        
        if(directory == NULL) {
            errorNumber = errno;
            perror(strerror(errorNumber));
        }
        
        std::vector<string> ls;
        struct dirent *directoryEntry;
        while((directoryEntry = readdir(directory)) != NULL) {
            
            // Getting the file path for all files in directory
            
            std::string tempPath(fileName);
            std::string slash("/");
            tempPath += slash;
            tempPath += directoryEntry->d_name;
            
            // Add all names of files to temp string vector
            
            if((strcmp(directoryEntry->d_name, ".") != 0) && (strcmp(directoryEntry->d_name, ".."))) {
                ls.push_back(directoryEntry->d_name);
            }
            
            // Create new FileManager object for each file in directory
            
            FileManager *temp;
            temp = new FileManager(tempPath.c_str());
            children.push_back(temp);
        }
        
        // Iterate through file string vector and display all files
        
        for(auto t=ls.begin(); t!=ls.end(); ++t){
            cout << *t << endl;
        }
        closedir(directory);
        errorNumber = 0;
    }
    else{
        cout << fileName << endl;
        errorNumber = ENOTDIR;
        perror(strerror(errorNumber));
    }
}


    



