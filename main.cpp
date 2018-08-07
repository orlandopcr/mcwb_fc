#include "includes.h"
#include "globales.h"

string archivo_configuracion;
int indice = 0;
int numero_vehiculos_minimo = 0;

void funcionMiope(int *visitado, int *costos_cliente_ahora, int *cliente_actual, int *cliente_siguiente, int *costo_visita, int *tiempo_viajando){ // encuentra el siguiente cliente mas cercano
	int costo_mas_barato = MAX;
	int cliente_seleccionado;

	for (int i=0;i<numero_de_clientes;i++){
		bool vis = false;
		if (visitado[i] == 1){
			vis = true;
		}
		if (costo_mas_barato>costos_cliente_ahora[i] && (i!=*cliente_actual) && !vis){
			costo_mas_barato = costos_cliente_ahora[i]; // elijo costo mas barato de los vistos en la iteracion.
			cliente_seleccionado = i; // cliente siguiente elegido.
		}
		*cliente_siguiente = cliente_seleccionado; 
		*costo_visita = costo_mas_barato;	
	}
	*cliente_actual = cliente_seleccionado;
	*tiempo_viajando = costos_cliente_ahora[cliente_seleccionado]+tiempo_atencion;
}

void funcionMiope1(int *visitado, int *costos_cliente_ahora, int *cliente_actual, int *cliente_siguiente, int *costo_visita, int *tiempo_viajando){ // encuentra el siguiente cliente mas cercano
	int costo_mas_barato = MAX;
	int cliente_seleccionado;

	for (int i=0;i<numero_de_clientes;i++){
		bool vis = false;
		if (visitado[i] == 1){
			vis = true;
		}

		if (costo_mas_barato>costos_cliente_ahora[*cliente_actual+numero_de_clientes*i] && (i!=*cliente_actual) && !vis){
			costo_mas_barato = costos_cliente_ahora[*cliente_actual+numero_de_clientes*i]; // elijo costo mas barato de los vistos en la iteracion.
			cliente_seleccionado = i; // cliente siguiente elegido.
		}
		*cliente_siguiente = cliente_seleccionado; 
		*costo_visita = costo_mas_barato;		
	}
	*cliente_actual = cliente_seleccionado;
	*tiempo_viajando = costos_cliente_ahora[cliente_seleccionado]+tiempo_atencion;
}

void greedy(int n_veh_min,int *costo_dep_pCl, int *visitado, int *recorrido_vehiculos, int *arreglo_costo_viajes, int *demanda_clientes, int capacidad_vehiculos, int *rutas, int *costo_greedy){
	int costo_visita = 0; // declaramos 
	int cliente_actual = 0; // declaramos
	int cliente_siguiente = 0; // declaramos
	int demanda_cubierta_por_vehiculo = 0; // declaramos
	int clientes_atendidos = 0;
	int tiempo_viajando = 0;
	int COSTO_TOTAL = 0;
	int posicion = 0;

	for (int vehiculo = 0;vehiculo < n_veh_min;vehiculo++){ 

		funcionMiope(visitado, costo_dep_pCl, &cliente_actual, &cliente_siguiente, &costo_visita, &tiempo_viajando); // encuentra siguiente cliente a visitar por vehiculo
		visitado[cliente_siguiente] = 1;
		demanda_cubierta_por_vehiculo += demanda_clientes[cliente_siguiente];
		recorrido_vehiculos[cliente_siguiente+vehiculo*numero_de_clientes] = 1; // marcamos en arreglo recorrido_vehiculos que cliente fue visitado
		clientes_atendidos += 1;
		COSTO_TOTAL += costo_visita;
		rutas[posicion+vehiculo*numero_de_clientes] = cliente_siguiente+1;
		posicion++;

		while(demanda_cubierta_por_vehiculo <= capacidad_vehiculos && clientes_atendidos < numero_de_clientes && tiempo_viajando <= tiempo_max_ruta){
			funcionMiope1(visitado, arreglo_costo_viajes, &cliente_actual, &cliente_siguiente, &costo_visita, &tiempo_viajando);
			visitado[cliente_siguiente] = 1;
			demanda_cubierta_por_vehiculo += demanda_clientes[cliente_siguiente];
			recorrido_vehiculos[cliente_siguiente+vehiculo*numero_de_clientes] = 1; // marcamos en arreglo recorrido_vehiculos que cliente fue visitado
			clientes_atendidos += 1;
			COSTO_TOTAL += costo_visita;
			rutas[posicion+vehiculo*numero_de_clientes] = cliente_siguiente+1;
			posicion++;
		}
		tiempo_viajando = 0;
		demanda_cubierta_por_vehiculo = 0;
		cliente_actual = 0; //volvemos al deposito para el siguiente vehiculo recorra su ruta
		posicion = 0;
		//cout << endl;
	}
	cout << "Solucion encontrada mediante GREEDY:" << endl;
	cout << endl;

	for (int i=0;i<n_veh_min;i++){
		cout << "ROUTE #" << i+1 << " : ";
		for(int j=0;j<numero_de_clientes;j++){
			int recorrido = rutas[j+i*numero_de_clientes]; //se revisa el cliente
			if (recorrido!=0){
				cout << recorrido << " ";
			}		
		}
		cout << endl;
	}
	cout << "COST: " << COSTO_TOTAL << endl;
	cout << endl;
	*costo_greedy = COSTO_TOTAL;
}

void Movimiento_Swap_clientes(int *solucion_actual, int *nueva_solucion){ 
	// Movimiento: elegir aleatoriamente 2 clientes en 1 o 2 rutas, luego hacer swap donde entre la posicion de los 2 clientes.
	int ruta1 = rand() % numero_vehiculos_minimo;
	int ruta2 = rand() % numero_vehiculos_minimo;
	int largo1 = 0;
	int largo2 = 0;
	int pos_cliente1 = 0;
	int pos_cliente2 = 0;
	int c1_swap = 0;
	int c2_swap = 0;

	for (int i=0;i<numero_de_clientes;i++){
		if (nueva_solucion[i+ruta1*numero_de_clientes]!=0){
			largo1+=1;
		}
		if (nueva_solucion[i+ruta2*numero_de_clientes]!=0){
			largo2+=1;
		}
	}
	pos_cliente1 = rand() % largo1;
	pos_cliente2 = rand() % largo2;

	for (int i=0;i<numero_de_clientes;i++){
		if (i==pos_cliente1 && i<largo1){
			c1_swap = solucion_actual[i+ruta1*numero_de_clientes];
			nueva_solucion[i+ruta2*numero_de_clientes] = c1_swap;
		}
		if (i==pos_cliente2 && i<largo2){
			c2_swap = solucion_actual[i+ruta2*numero_de_clientes];
			nueva_solucion[i+ruta1*numero_de_clientes] = c2_swap;
		}
	}
}

bool solucion_valida_capacidad(int *nueva_solucion,int *demanda_clientes){ 
	bool valida = true;
	int demanda_cubierta_por_vehiculo = 0;
	for (int i = 0;i<numero_vehiculos_minimo;i++){ 
		for (int j = 0;j<numero_de_clientes;j++){
			int posicion = j+i*numero_de_clientes;

			if (nueva_solucion[posicion]!=0){

				int cliente = nueva_solucion[posicion];
				demanda_cubierta_por_vehiculo += demanda_clientes[cliente];

				if (demanda_cubierta_por_vehiculo>capacidad_vehiculos){
					valida = false;
					return valida;
				}
			}
		demanda_cubierta_por_vehiculo = 0;	
		}
	}
	return valida;
}

bool solucion_valida_tiempo(int *nueva_solucion, int *costo_dep_pCl, int *arreglo_costo_viajes){
	bool valida = true;
	int tiempo = 0;
	int cliente_i = 0;
	int cliente_j = 0;
	for (int i = 0;i<numero_vehiculos_minimo;i++){ 
		cliente_i = 0;
		for (int j = 0;j<numero_de_clientes;j++){
			int posicion = j+i*numero_de_clientes;
			cliente_j = nueva_solucion[posicion];
			if (cliente_j!=0){
				if (cliente_i==0){
					tiempo += costo_dep_pCl[cliente_j] + tiempo_atencion;
				}
				else if (cliente_i!=0){
					tiempo += arreglo_costo_viajes[cliente_j+cliente_i*numero_de_clientes] + tiempo_atencion;
				}
				cliente_i = cliente_j; //avanzamos en 1 posicion del arreglo nueva_solucion
			}
		if (tiempo>tiempo_max_ruta){
			valida = false;
			return valida;
		}
		}
		tiempo = 0;
	}
	return valida;
}

int funcionEvaluacion(int *nueva_solucion, int *costo_dep_pCl, int *arreglo_costo_viajes){
	int costo = 0;
	int cliente_i = 0;
	int cliente_j = 0;
	for (int i = 0;i<numero_vehiculos_minimo;i++){ 
		cliente_i = 0;
		for (int j = 0;j<numero_de_clientes;j++){
			int posicion = j+i*numero_de_clientes;
			cliente_j = nueva_solucion[posicion];
			if (cliente_j!=0){
				if (cliente_i==0){
					costo += costo_dep_pCl[cliente_j];
				}
				else if (cliente_i!=0){
					costo += arreglo_costo_viajes[cliente_j+cliente_i*numero_de_clientes];
				}
				cliente_i = cliente_j; //avanzamos en 1 posicion del arreglo nueva_solucion
			}
		}
	}
	return costo;
}

void SA(int *solucion_inicial, int costo_inicial, int temperatura_inicial, float alpha, int maximos_pasos, int maxima_iteracion, int semilla, int *costo_dep_pCl, int *arreglo_costo_viajes, int *demanda_clientes){
	int solucion_candidata[numero_vehiculos_minimo*numero_de_clientes]; //arreglo donde guardademos solucion escojida de manera aleatoria
	int costo_solucion_candidata = costo_inicial;
	int solucion_nueva[numero_vehiculos_minimo*numero_de_clientes]; 
	int costo_solucion_nueva = costo_inicial;
	int mejor_solucion[numero_vehiculos_minimo*numero_de_clientes];
	int mejor_costo = costo_inicial;
	srand48(semilla);
	float probabilidad;
	float temperatura = temperatura_inicial;

	cout << "Parametros entrada SA - Temperatura Inicial: " << temperatura_inicial << " - Alpha: " << alpha << endl;
	cout << "Parametros entrada SA - Cantidad de veces en disminuir temperatura: " << maximos_pasos << " - Iteraciones manteniendo temperatura: " << maxima_iteracion << endl;
	cout << "Parametros entrada SA - Valor semilla usada para random: " << semilla << endl;
	cout << endl;

	for (int i = 0;i<numero_vehiculos_minimo;i++){ 
		for (int j =0;j<numero_de_clientes;j++){
			int posicion = j+i*numero_de_clientes;
			mejor_solucion[posicion] = solucion_inicial[posicion];
			solucion_candidata[posicion] = solucion_inicial[posicion];
			solucion_nueva[posicion] = solucion_inicial[posicion]; 
		}
	}

	for (int paso = 0;paso < maximos_pasos;paso++){
		for (int iteracion=0;iteracion<maxima_iteracion;iteracion++){
			Movimiento_Swap_clientes(solucion_candidata,solucion_nueva); //Movimiento utilizado
			if (solucion_valida_capacidad(solucion_nueva,demanda_clientes) && solucion_valida_tiempo(solucion_nueva,costo_dep_pCl,arreglo_costo_viajes)){ 
				costo_solucion_nueva = funcionEvaluacion(solucion_nueva, costo_dep_pCl, arreglo_costo_viajes);
				if (costo_solucion_nueva < mejor_costo){
					mejor_costo = costo_solucion_nueva;
					costo_solucion_candidata = costo_solucion_nueva;
					for (int i = 0;i<numero_vehiculos_minimo;i++){ 
						for (int j = 0;j<numero_de_clientes;j++){
							int posicion = j+i*numero_de_clientes;
							mejor_solucion[posicion] = solucion_nueva[posicion]; //actualizamos mejor solucion
							solucion_candidata[posicion] = solucion_nueva[posicion]; //actualizamos mejor solucion para iteracion siguiente
						}
					}
				}
				else{ // Condicion de aceptar peores soluciones con la funcion de probabilidad
					probabilidad = exp(((costo_solucion_nueva - costo_solucion_candidata)/temperatura));
					float aleatorio = drand48();
					if (aleatorio < probabilidad){
					costo_solucion_candidata = costo_solucion_nueva;	
						for (int i = 0;i<numero_vehiculos_minimo;i++){ 
							for (int j = 0;j<numero_de_clientes;j++){
								int posicion = j+i*numero_de_clientes;
								solucion_candidata[posicion]  = solucion_nueva[posicion]; //actualizamos mejor solucion para iteracion siguiente
							}
						}
					}
				}
			}
		}
		temperatura = alpha*temperatura;
	}
	cout << "Simulated Annealing termino de ejecutar y esta es la mejor solucion encontrada:" << endl;
	cout << endl;

	for (int i=0;i<numero_vehiculos_minimo;i++){
		cout << "ROUTE #" << i+1 << " : ";
		for(int j=0;j<numero_de_clientes;j++){
			int recorrido = mejor_solucion[j+i*numero_de_clientes]; //se revisa el cliente
			if (recorrido!=0){
				cout << recorrido << " ";
			}		
		}
		cout << endl;
	}
	cout << "COST: " << mejor_costo << endl;
	cout << endl;
}

int Leer_entradas(int argc, char **argv){
  //archivo con la instancia del problema
  archivo_configuracion = (char *)(argv[1]);
  
  //PARAMETROS
  Ti = atoi(argv[2]); //temperatura inicial
  alpha = atof(argv[3]); //alpha
  Mi = atoi(argv[4]); 
  Mp = atoi(argv[5]);

  //SEMILLA
  semilla = atoi (argv[6]);
  return 1;
}


int main(int argc, char *argv[]){

	if(!Leer_entradas(argc,argv))
    {
      cout<<"Problemas en la lectura de los parametros";
      exit(1);
    }

	const string nfichero = archivo_configuracion;
	char cadena[10];
	ifstream fichero;
	fichero.open(nfichero.c_str());
	if (!fichero.fail()){
		fichero.getline(cadena, 10, ' ');
		fichero.getline(cadena, 10, ' ');
		sscanf(cadena,"%d",&numero_de_clientes);
		fichero.getline(cadena, 10, ' ');
		sscanf(cadena,"%d",&capacidad_vehiculos);
		fichero.getline(cadena, 10, ' ');
		sscanf(cadena,"%d",&tiempo_max_ruta);
		fichero.getline(cadena, 10, ' ');
		sscanf(cadena,"%d",&tiempo_atencion);
		fichero.getline(cadena, 10, ' ');
		sscanf(cadena,"%d",&coordenadas_deposito[0]);
		fichero.getline(cadena, 10, ' ');
		sscanf(cadena,"%d",&coordenadas_deposito[1]);
		
		int coor_x_clientes[numero_de_clientes];
		int coor_y_clientes[numero_de_clientes];
		int demanda_clientes[numero_de_clientes];

	while (!fichero.eof()){
		fichero.getline(cadena, 10, ' ');
		sscanf(cadena,"%d",&coor_x_clientes[indice]);
		fichero.getline(cadena, 10, ' ');
		sscanf(cadena,"%d",&coor_y_clientes[indice]);
		fichero.getline(cadena, 10, ' ');
		sscanf(cadena,"%d",&demanda_clientes[indice]);
		indice++;
	}

	int demanda;
	int a1,b1,a2,b2;
	int tam = pow(numero_de_clientes,2);
	int arreglo_costo_viajes[tam]; // Arreglo de N*N
	int posicion = 0;

	for (int fila = 0;fila<numero_de_clientes;fila++){
		for (int columna = 0;columna<numero_de_clientes;columna++){
			a1 = coor_x_clientes[fila];
			b1 = coor_y_clientes[fila];
			a2 = coor_x_clientes[columna];
			b2 = coor_y_clientes[columna];
			posicion = columna+fila*numero_de_clientes;
			arreglo_costo_viajes[posicion] = round(sqrt(pow((a1 - a2),2) + pow((b1 - b2),2)));
		}
	}

	int demanda_total = 0;
	for (int i = 0;i<numero_de_clientes;i++){
		demanda_total = demanda_total + demanda_clientes[i];
	fichero.close();
	}
	numero_vehiculos_minimo = (((double) demanda_total)/capacidad_vehiculos)+1;

	int t_recorrido_vehiculos = numero_vehiculos_minimo*numero_de_clientes;
	int recorrido_vehiculos[t_recorrido_vehiculos]; // Arreglo de K*N

	for (int i = 0;i<numero_vehiculos_minimo;i++){ // llenamos la matriz recorrido_vehiculos de 0s
		for (int j =0;j<numero_de_clientes;j++){
			int posicion = j+i*numero_de_clientes;
			recorrido_vehiculos[posicion] = 0;
		}
	}

	int visitado[numero_de_clientes];
	for (int i=0;i<numero_de_clientes;i++){
		visitado[i] = 0; //lleno de 0s a los clientes no visitados
	}

	//comienzo algoritmo GREEDY

	int demanda_cubierta_por_vehiculo = 0;
	int tiempo_viajando = 0;
	int COSTO_TOTAL = 0;
	int siguiente_cliente = numero_de_clientes+1;
	int clientes_atendidos = 0;
	int costo_deposito_primerCliente[numero_de_clientes];
	int depot_x;
	int depot_y;
	depot_x = coordenadas_deposito[0];
	depot_y = coordenadas_deposito[1];

	for (int i=0;i<numero_de_clientes;i++){
		a1 = coor_x_clientes[i];
		b1 = coor_y_clientes[i];
		costo_deposito_primerCliente[i] = round(sqrt(pow((depot_x - a1),2) + pow((depot_y - b1),2)));
	}

	int rutas[numero_vehiculos_minimo*numero_de_clientes]; //arreglo donde guardademos orden en que fueron recorridas las rutas

	for (int i = 0;i<numero_vehiculos_minimo;i++){ // llenamos la matriz rutas de 0s
		for (int j =0;j<numero_de_clientes;j++){
			int posicion = j+i*numero_de_clientes;
			rutas[posicion] = 0;
		}
	}
	cout << "Archivo de entrada: " << archivo_configuracion << endl;
	cout << endl;
	cout << "Iniciamos el algoritmo construyendo la primera solucion mediante GREEDY." << endl;
	cout << endl;
	int costo_greedy = 0;
	clock_t tStart = clock();
	greedy(numero_vehiculos_minimo,costo_deposito_primerCliente,visitado,recorrido_vehiculos,arreglo_costo_viajes,demanda_clientes,capacidad_vehiculos,rutas,&costo_greedy);
	// Aplicamos SA utilizando como solucion inicial la obtenida por greedy.
	SA(rutas,costo_greedy,Ti,alpha,Mp,Mi,semilla,costo_deposito_primerCliente,arreglo_costo_viajes,demanda_clientes);
	} // end fichero
	double tiempo_ejecucion = (double)(clock()-tStart)/CLOCKS_PER_SEC;
	cout << "Tiempo ejecucion Greedy+SA: " << tiempo_ejecucion << " segundos" << endl;
	return 0;
} // end main