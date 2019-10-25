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
// My variation of the linux command cp
// 3 October 2019

using namespace std;

int main (int argc, char *argv[]){
	// You need 3 arguments for mycp
	// First will be the call (./a.out)
	// Second is the path to the file you want to copy from
	// Third is the path of the file you want to copy to
	// Note that both files must already exist
	
	// Ex) ./a.out /home/pi/Desktop/file1.txt /home/pi/Desktop/file2.txt
	
	if(argc != 3){
		cout << "Missing file operand" << endl;
		exit(1);
	}
	
	ofstream source(argv[1]);
	FileManager destination(argv[2]);
	destination.dumpFile(source);
	return 0;
}
