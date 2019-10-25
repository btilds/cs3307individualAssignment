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
#include <fcntl.h>
#include "FileManager.h"

// Ben Tilden
// My variation of the linux command stat
// 3 October 2019

using namespace std;

int main (int argc, char *argv[]){
	// You need 2 arguments for mystat
	// First will be the call
	// Second is the path to the file you want to see info about
	
	// Ex) ./a.out /home/pi/Desktop/Folder
	
	if(argc < 2 || argc > 2){
		cout << "Specify 1 file for display info" << endl;
		exit(1);
	}
	
	const char* tempFileName = argv[1];
	FileManager temp(tempFileName);
	
	printf("File:         %s\n", temp.getFileName());
	printf("Type:		  %lu\n", temp.getFileType());
	printf("Size:         %lld bytes\n", temp.getFileSize());
	printf("OwnerId:      %ld\n", temp.getFileOwnerId());
	printf("Owner Name:   &s\n", temp.getFileOwnerUsername());
	printf("GroupId:      %ld\n", temp.getFileGroupId());
	printf("Group Name:   %s\n", temp.getFileGroupName());
	printf("Permissions:  %s\n", temp.getFilePermissions().c_str());
	printf("Access:       %s", temp.getFileLastAccess());
	printf("Modify:       %s", temp.getFileLastModified());
	printf("Change:       %s", temp.getFileLastStatusChange());
	
	return 0;
}
