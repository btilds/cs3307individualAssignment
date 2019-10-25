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
// My variation of the linux command mv
// 3 October 2019

using namespace std;

int main (int argc, char *argv[]){
	// You need 3 arguments for mymv
	// First will be the call
	// Second is the path to the file you want to move
	// Third is the path of where you want to move the file and
	// has a new name
	
	// Ex) ./a.out /home/pi/Desktop/Folder /home/pi/Desktop/NewFolder
	if(argc != 3){
		cout << "Missing file operand" << endl;
		return -1;
	}
	// Tries renaming the file, however, if they are on different
	// file systems it will use the dump and remove methods
	FileManager fm1(argv[1]);
	fm1.renameFile(argv[2]);
	
	if (fm1.getErrorNumber() != 0) {
		
		ofstream source(argv[1]);
		FileManager destination(argv[2]);
		destination.dumpFile(source);
		fm1.removeFile(fm1.getFileName());
		return 0;
		
	}
	return 0;
}
