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
// My variation of the linux command cat
// 3 October 2019

using namespace std;

int main(int argc, char *argv[]) {
	// You need 2 or more arguments for mycat
	// First will be the call
	// Second+ will be file paths of files you want to display
	
	// This function will iterate through all of the files and
	// display them to the terminal
	
	// Ex) ./a.out /home/pi/Desktop/file.txt /home/pi/Desktop/file2.txt
	
	if(argc < 2){
		cout << "Specify at least 1 file to display" << endl;
		return -1;
	}
	
	// Print out all file data line by line
	
	for (int i = 1; i < argc; i++){
		cout << ifstream(argv[i]).rdbuf();
		cout << "\n" << endl;
	}
	return 0;
}
