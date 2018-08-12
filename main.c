#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]){

	FILE *file;
	int get_data;
   	file = fopen(argv[1], "r");
   	int n_trucks;
   	int n_milk_types;
   	int n_nodes;
   	char word[1024];
   	char copy_word;

   	fscanf(file, "%d", &n_trucks);
   	int trucks_capacity[n_trucks];

   	for (int i = 0; i < n_trucks; ++i)
   	{
   		fscanf(file, " %1023s", word);
   		trucks_capacity[i] = atoi(word);
   	}

   	fscanf(file, "%d", &n_milk_types);
   	int milk_quotas[n_milk_types];

	for (int i = 0; i < n_milk_types; ++i)
	{
	   	fscanf(file, " %1023s", word);
	   	milk_quotas[i] = atoi(word);
	}

	float milk_values[n_milk_types];
	for (int i = 0; i < n_milk_types; ++i)
	{
	   	fscanf(file, " %1023s", word);
	   	milk_values[i] = atof(word);
	}

	fscanf(file, "%d", &n_nodes);
   	int nodes_info[n_nodes][5];
   	char type_char;

   	for (int i = 0; i < n_nodes; ++i)
	{
	   	for (int j = 0; j < 5; ++j)
	   	{
	   		if ( j == 3)
	   		{
	   			fscanf(file, " %1s", word);
	   			type_char = word[0];  //will code and store type as ascii 
	   			nodes_info[i][j] = type_char; 
	   			
	   		}
	   		else{
	   			fscanf(file, " %1023s", word);
	   			nodes_info[i][j] = atoi(word);
	   		}
	   		
	   	}
	}

	/*for (int i = 0; i < 20; ++i)
	{
		printf("%d - %d - %d - %d - %d \n",nodes_info[i][0] ,nodes_info[i][1] ,nodes_info[i][2] ,nodes_info[i][3] ,nodes_info[i][4] );
	}*/


	return 0;
}
