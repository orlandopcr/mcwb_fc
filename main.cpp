#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <vector>

using namespace std;

int main(int argc, char* argv[]){

    int number_to_show;
    
    std::ifstream infile(argv[1]);
    std::string line;
    std::getline(infile, line);
    std::stringstream data(line);

    int n_trucks;
    data >> n_trucks;

    int trucks_capacity [n_trucks];
    std::getline(infile, line);
    std::string capacity_string = line;

    std::stringstream capacity_data(capacity_string);

    string token;

    int count = 0 ;
    while (std::getline(capacity_data, token, ' '))
    {

        if (token.length() > 0){

            trucks_capacity[count] = std::stoi(token);
            count += 1;
        }


    }

    std::getline(infile, line);
    std::getline(infile, line);




    return 0;
}