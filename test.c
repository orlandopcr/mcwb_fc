
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <cstring>


using namespace std;


int main (int argc, char* argv[]) {
	string line;
	string delim = " ";

	ifstream myfile (argv[1]);
	
	if (myfile.is_open()){

		while ( getline (myfile,line) ){
			
			string *token = strtok(line,delim);
			while (token){
        		cout << token << endl;
        		token = strtok(NULL,delim);
    		}
		}
		myfile.close();
	}

	else cout << "Unable to open file"; 
	return 0;
}

