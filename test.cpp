#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]){

    int number_to_show;
    
    std::ifstream infile(argv[1]);
    std::string line;

    std::getline(infile, line);
    
    std::stringstream data(line);
    data >> number_to_show;

    cout << number_to_show << endl;
    /*while (std::getline(infile, line)){
    }*/
    
    return 0;
}