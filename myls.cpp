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
// My variation of the linux command ls
// 3 October 2019

using namespace std;

int main (int argc, char *argv[]){
	// You need 1 or 2 arguments for myls
	// First will be the call
	// Second is the path to the dir you want to expand (optional)
	// If second argument is not provided, ls will return an expansion
	// of the current directory 
	
	// Ex) ./a.out /home/pi/Desktop/Folder
	
	if(argc > 2){
		cout << "Enter one or none file paths" << endl;
		return -1;
	}
	else if(argc == 2 && (strcmp(argv[1], "-l") != 0)){
		FileManager fm1(argv[1]);
		fm1.expandFile();
		return 0;
	}
	//else if(argc == 2 && (strcmp(argv[2], "-l") == 0)){
	
	// Here I would have added some sort of combination or reduction
	// of the stat and expand methods however I was unsure how to do
	// so and ran out of time
	
	//}
	else{
		FileManager fm2(".");
		fm2.expandFile();
		return 0;
	}
}
