#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]){

	FILE *file;
	int get_data;
   	file = fopen(argv[1], "r");
   	int n_trucks;
   	int n_milk_types;
   	int n_nodes;
   	char word[1024];

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

   	for (int i = 0; i < n_nodes; ++i)
	{
	   	for (int j = 0; j < 5; ++j)
	   	{
	   		fscanf(file, " %1023s", word);
	 		nodes_info[i][j] = atoi(word);
	   	}
	}

	printf("%d %d %d %d %d\n",nodes_info[4][0],nodes_info[4][1],nodes_info[4][2],nodes_info[4][3],nodes_info[4][4]);
   		
	return 0;
}
