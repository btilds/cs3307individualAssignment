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
// My variation of the linux command diff
// 3 October 2019

using namespace std;

int main (int argc, char *argv[]){
	// You need 3 arguments for mycat
	// First will be the call
	// Second will be file path of the first file you want to compare
	// Third will be the file path of the second file you want to compare

	
	// Ex) ./a.out /home/pi/Desktop/file.txt /home/pi/Desktop/file2.txt
	if(argc > 3 || argc < 3){
		cout << "Two file paths required" << endl;
		return -1;
	}
	
	FileManager fm1(argv[1]);
	FileManager fm2(argv[2]);
	if(fm1.compareFile(fm2) == true){
		cout << "Files same" << endl;
	}
	else{
		cout << "Files different" << endl;
	}
	return 0;
}
