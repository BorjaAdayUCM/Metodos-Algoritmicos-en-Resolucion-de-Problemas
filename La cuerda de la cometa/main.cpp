//Borja Aday Guadalupe Luis

// El problema global se resuelve en varias funciones separadas, cada una de ellas encargada de calcular una de las preguntas.
// Todas las funciones se basan en la programación dinámica para evitar repetir cálculos.
// Se ha optimizado la memoria, en un inicio se realizaron usando una matriz de N*R, luego nos dimos cuenta de que se podía tan solo utilizar
// dos filas y olvidar el resto por lo que pasamos a una matriz de 2*R, por último comprobamos que si rellenabamos la matriz de derecha a izquierda
// podríamos prescindir de una de las filas y acabamos con un vector de tamaño R.

#include <iostream>
#include <algorithm>

using namespace std;

const int MAX = 1000;
const long long int INF = 1e18;

//O(N*R) en tiempo O(N*R) en espacio siendo N el numero de cuerdas y R el tamaño de la cuerda a conseguir.

/*bool esPosible(int longitudes[], int numCuerdas, int tamCuerda) {
    bool tabla[MAX + 1][MAX + 1];
    
    //Si el tamaño de la cuerda es 0 se puede conseguir con cualquier 
    //subconjunto de las cuerdas (no escoger ninguna).
    for (int i = 0; i <= numCuerdas; i++) tabla[i][0] = true;
                                                                                                     
    //Si el tamaño de la cuerda es distinto de 0 y no podemos 
    //usar ninguna cuerda no se puede conseguir.
    for (int i = 1; i <= tamCuerda; i++) tabla[0][i] = false;
    
    //Rellenamos los datos
    for (int i = 1; i <= numCuerdas; i++) {
        for (int j = 1; j <= tamCuerda; j++) {
            if (j < longitudes[i - 1]) tabla[i][j] = tabla[i - 1][j];
            else tabla[i][j] = tabla[i - 1][j] || tabla[i - 1][j - longitudes[i - 1]];
        }
        if (tabla[i][tamCuerda]) return true;
    }
    
    //Si llego aquí significa que no he encontrado solución.
    return false;  
}*/


//O(N*R) en tiempo O(R) en espacio siendo N el numero de cuerdas y R el tamaño de la cuerda a conseguir.

/*bool esPosible(int longitudes[], int numCuerdas, int tamCuerda) {
    bool tabla[2][MAX + 1];

    //Si el tamaño de la cuerda es 0 se puede conseguir con cualquier 
    //subconjunto de las cuerdas (no escoger ninguna).
    tabla[0][0] = true;
    tabla[1][0] = true;

    //Si el tamaño de la cuerda es distinto de 0 y no podemos usar 
    //ninguna cuerda no se puede conseguir.
    for (int i = 1; i <= tamCuerda; i++) tabla[0][i] = false;

    //Rellenamos los datos
    for (int i = 1; i <= numCuerdas; i++) {
        for (int j = 1; j <= tamCuerda; j++) {
            if (j < longitudes[i - 1]) tabla[i % 2][j] = tabla[(i - 1) % 2][j];
            else tabla[i % 2][j] = tabla[(i - 1) % 2][j] || tabla[(i - 1) % 2][j - longitudes[i - 1]];
        }
        if (tabla[i % 2][tamCuerda]) return true;
    }

    return tabla[numCuerdas % 2][tamCuerda];
}*/

//Función que nos devuelve si es posible formar la cuerda del tamaño deseado con las cuerdas dadas.
//El coste en tiempo es O(N*R) y en espacio O(R), donde N es el número de cuerdas dadas y R el tamaño de la cuerda deseada.

bool esPosible(int longitudes[], int numCuerdas, int tamCuerda) {

    bool tabla[MAX + 1];

    //Si el tamaño de la cuerda es 0 se puede conseguir sin coger 
    //ninguna cuerda, por tanto, es posible.
    tabla[0] = true;

    //Si el tamaño de la cuerda es distinto de 0 y no podemos 
    //usar ninguna cuerda no se puede conseguir.
    for (int i = 1; i <= tamCuerda; i++) tabla[i] = false;

    //Rellenamos los datos
    for (int i = 0; i < numCuerdas; i++) {
        for (int j = tamCuerda; j >= 1; j--) {
            if (j < longitudes[i]) tabla[j] = tabla[j];
            else tabla[j] = tabla[j] || tabla[j - longitudes[i]];
            if (tabla[tamCuerda]) return true;
        }
    }

    return tabla[tamCuerda];
}


//Función que nos devuelve de cuantas formas se puede construir la cuerda del tamaño deseado con las cuerdas dadas.
//El coste en tiempo es O(N*R) y en espacio O(R), donde N es el número de cuerdas dadas y R el tamaño de la cuerda deseada.

long long int cuantasFormas(int longitudes[], int numCuerdas, int tamCuerda) {
    
    long long int tabla[MAX + 1];

    //Si el tamaño de la cuerda es 0 se puede conseguir de una sola forma,
    //no escoger ninguna.
    tabla[0] = 1;

    //Si el tamaño de la cuerda es distinto de 0 y no podemos usar ninguna 
    //cuerda no se puede conseguir.
    for (int i = 1; i <= tamCuerda; i++) tabla[i] = 0;

    //Rellenamos los datos
    for (int i = 0; i < numCuerdas; i++) {
        for (int j = tamCuerda; j >= 1; j--) {
            if (j < longitudes[i]) tabla[j] = tabla[j];
            else tabla[j] = tabla[j] + tabla[j - longitudes[i]];
        }
    }

    return tabla[tamCuerda];
}


//Función que nos devuelve el mínimo número de cuerdas a utilizar con las que se puede construir la cuerda del tamaño deseado con las cuerdas dadas.
//El coste en tiempo es O(N*R) y en espacio O(R), donde N es el número de cuerdas dadas y R el tamaño de la cuerda deseada.

long long int minCuerdas(int longitudes[], int numCuerdas, int tamCuerda) {
    
    long long int tabla[MAX + 1];

    //Si el tamaño de la cuerda es 0 se puede conseguir sin escoger ninguna,
    //0 cuerdas.
    tabla[0] = 0;

    //Si el tamaño de la cuerda es distinto de 0 y no podemos usar ninguna 
    //cuerda no se puede conseguir.
    for (int i = 1; i <= tamCuerda; i++) tabla[i] = INF;

    //Rellenamos los datos
    for (int i = 0; i < numCuerdas; i++) {
        for (int j = tamCuerda; j >= 1; j--) {
            if (j < longitudes[i]) tabla[j] = tabla[j];
            else tabla[j] = min(tabla[j], tabla[j - longitudes[i]] + 1);
        }
    }

    return tabla[tamCuerda];
}


//Función que nos devuelve el mínimo coste con el que se puede construir la cuerda del tamaño deseado con las cuerdas dadas.
//El coste en tiempo es O(N*R) y en espacio O(R), donde N es el número de cuerdas dadas y R el tamaño de la cuerda deseada.

long long int minCoste(int longitudes[], int valores[], int numCuerdas, int tamCuerda) {
    
    long long int tabla[MAX + 1];

    //Si el tamaño de la cuerda es 0 se puede conseguir sin escoger ninguna a coste 0.
    tabla[0] = 0;

    //Si el tamaño de la cuerda es distinto de 0 y no podemos usar ninguna cuerda 
    //no se puede conseguir y por tanto el coste es infinito.
    for (int i = 1; i <= tamCuerda; i++) tabla[i] = INF;

    //Rellenamos los datos
    for (int i = 0; i < numCuerdas; i++) {
        for (int j = tamCuerda; j >= 1; j--) {
            if (j < longitudes[i]) tabla[j] = tabla[j];
            else tabla[j] = min(tabla[j], tabla[j - longitudes[i]] + valores[i]);
        }
    }

    return tabla[tamCuerda];
}


//Resuelve un caso de prueba, leyendo de la entrada la configuración, y escribiendo la respuesta.
bool resuelveCaso() {
    
    int numCuerdas, tamCuerda, longitudes[MAX], valores[MAX];

    cin >> numCuerdas;

	if (!std::cin) return false;
	
    cin >> tamCuerda;

	for(int i = 0; i < numCuerdas; i++) {
		cin >> longitudes[i] >> valores[i];
	}

	if(esPosible(longitudes, numCuerdas, tamCuerda)) cout << "SI " << cuantasFormas(longitudes, numCuerdas, tamCuerda) << " " << minCuerdas(longitudes, numCuerdas, tamCuerda) 
                                                          << " " << minCoste(longitudes, valores, numCuerdas, tamCuerda) << '\n';
	else cout << "NO" << '\n';

	return true;
}

int main() {
   
   while (resuelveCaso());

   return 0;
}
