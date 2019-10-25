//
// Created by Ben Tilden on 2019-09-26.
//

#ifndef INC_3307_INDIVIDUAL_ASSIGNMENT_FILEMANAGER_H
#define INC_3307_INDIVIDUAL_ASSIGNMENT_FILEMANAGER_H

#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <cerrno>
#include <grp.h>
#include <ctime>
#include <cstdio>
#include <ftw.h>
#include <fstream>
#include <string.h>
#include <dirent.h>
#include <vector>

#endif //INC_3307_INDIVIDUAL_ASSIGNMENT_FILEMANAGER_H

// Ben Tilden
// File Manager header with private attributes and public methods
// 3 October 2019

class FileManager{

    private:

    //File attributes

    const char * fileName;
    unsigned long fileType;
    long long fileSize;
    long fileOwnerId;
    char * fileOwnerUsername;
    long fileGroupId;
    char * fileGroupName;
    std::string filePermissions;
    char* fileLastAccess;
    char* fileLastModification;
    char* fileLastStatusChange;
    long fileBlockSize;
    std::vector<FileManager*> children;
    int errorNumber;

    public:
    
    // Constructor and destructor

    explicit FileManager(const char * fileName);
    ~FileManager();

    // Getters

    const char* getFileName();
    unsigned long getFileType();
    long long getFileSize();
    long getFileOwnerId();
    char * getFileOwnerUsername();
    long getFileGroupId();
    char * getFileGroupName();
    std::string getFilePermissions();
    char* getFileLastAccess();
    char* getFileLastModified();
    char* getFileLastStatusChange();
    long getFileBlockSize();
    int getErrorNumber();
    char* getErrorString();

    // Functions

    void dumpFile(std::ostream& inputStream);
    void renameFile(const char* newName);
    void removeFile(const char* file);
    bool compareFile(FileManager fileObject);
    void expandFile();

};
