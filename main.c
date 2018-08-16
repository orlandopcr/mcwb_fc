#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int get_distance(int node_from , int node_to, int nodes_info[][5], int n_nodes){

	int from_x ,from_y , to_x , to_y;
	for (int i = 0; i < n_nodes; ++i)
	{
		if (nodes_info[i][0] == node_from)
		{
			from_x = nodes_info[i][1];
			from_y = nodes_info[i][2];
		}
		else if (nodes_info[i][0] == node_to)
		{
			to_x = nodes_info[i][1];
			to_y = nodes_info[i][2];
		}
	}

	float x_sustraction, y_sustraction, distance;

	x_sustraction = (from_x - to_x)*(from_x  -  to_x);
	y_sustraction = (from_y - to_y)*(from_y - to_y);
	distance = sqrt(x_sustraction + y_sustraction);

	return distance;
}

void present(int **p,int nf,int nc)
{
  int i=0,j=0;
 
  for(i=0;i<nf;i++)
  {
  	printf("\n");
    for(j=0;j<nc;j++)
       printf("%d",p[i][j] ); 
  }
}

int get_node(int *domain,int n_nodes, int previous_node, int nodes_info[][5]){
	int minimun_distance_node;
	float distance = 9999999999;
	float obtained_distance;
	for (int i = 1; i < n_nodes; ++i)
	{
		if (domain[i]==0)
		{	
			if (previous_node + 1 != i)
			{
				
				obtained_distance = get_distance(previous_node + 1, i , nodes_info, n_nodes);
				if (obtained_distance < distance)
				{
					distance = obtained_distance;
					minimun_distance_node = i;

				}
			}
		}
	}

	if(distance == 0){
		return -1;
	}

	else{
		if (distance <= 0){
			return -1;
		}

		else{
			if(distance > 99999999){
				return -1;
			}
			else{
				return minimun_distance_node;
			}
		}
	}
	
}

int check_forward(int *ptr_capacity,int *ptr_domain,int nodes_info[][5],int actual_truck, int **route_matrix, int node_to_instanciate, int n_nodes){
	ptr_capacity[actual_truck] = ptr_capacity[actual_truck] - nodes_info[node_to_instanciate][4];
	for (int i = 0; i < n_nodes; ++i)
	{
		if (ptr_capacity[actual_truck] - nodes_info[i][4] < 0)
		{
			ptr_domain[i] = 1;
		}
	}
	return 1;
}

int reset_domain(int *ptr_domain, int **route_matrix, int n_nodes){
	int sum_instances;
	int check_reseted = 0;
	for (int i = 0; i < n_nodes; ++i)
	{
		for (int j = 0; j < n_nodes; ++j)
		{
			sum_instances = sum_instances + route_matrix[i][j];
		}

		if (sum_instances == 0)
		{
			ptr_domain[i] = 0;
			check_reseted = 1;
		}
		sum_instances = 0;
	}
	return check_reseted;
}


void clean_matrix(int **route_matrix, int n_nodes){
	int flag_find_it = 0;
	int return_matrix[n_nodes][n_nodes]; 
	for (int i = 0; i < n_nodes; ++i)
	{
		for (int j = 0; j < n_nodes; ++j)
		{
			if (route_matrix[i][j] != 0)
			{
				if (flag_find_it == 0)
				{
					flag_find_it = 1;
				}
				else{
					route_matrix[i][j] = 0;
				}
			}
		}
		flag_find_it = 0;
	}
}

int get_the_route(int trucks_capacity[], int milk_quotas[] , float milk_values[],int nodes_info[][5], int n_trucks, int n_milk_types, int n_nodes ){
	
	int **route_matrix;
	int domain[n_nodes];
	int count_trucks = n_trucks;

	route_matrix =(int**)malloc(n_nodes*sizeof(int*));


	for (int i = 0; i < n_nodes; ++i)
	{
		domain[i]=0;
	}

	int *ptr_domain = &domain[0];
	int *ptr_capacity = &trucks_capacity[0];



	route_matrix = (int **)malloc (n_nodes*sizeof(int *));
	for (int i=0;i<n_nodes;i++)
	route_matrix[i] = (int *) malloc (n_nodes*sizeof(int));
	int actual_truck = 0;
	int previous_node = 0;
	int reseted;

	while(count_trucks !=0){

		int node_to_instanciate = get_node(ptr_domain, n_nodes, previous_node, nodes_info);
		
		if(node_to_instanciate != -1){
			
			ptr_domain[node_to_instanciate]=1;

			int checked = check_forward(ptr_capacity,ptr_domain,nodes_info, actual_truck, route_matrix,node_to_instanciate, n_nodes);
			route_matrix[previous_node][node_to_instanciate] = actual_truck +1 ;
			previous_node = node_to_instanciate;
		}
		else{
			
			int reseted = reset_domain(ptr_domain, route_matrix, n_nodes);
			count_trucks = count_trucks - 1;
			actual_truck = actual_truck + 1;
		}
	}

	clean_matrix(route_matrix, n_nodes);
	present(route_matrix,n_nodes,n_nodes);

	return -1;

}

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

	get_the_route(trucks_capacity, milk_quotas , milk_values, nodes_info, n_trucks, n_milk_types, n_nodes );

	return 0;
}
