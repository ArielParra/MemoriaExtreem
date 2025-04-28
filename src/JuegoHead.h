/* Ariel Emilio Parra Martinez ID:280862*/
/* Miguel Angel Batres Luna ID:350553*/
#ifndef Juegohead
#define Juegohead

/*librerias propias*/
#include "FuncionesGen.h"

/*librerias c++*/
#include <cstdio>

/*librerias c*/
#include <cmath>//sqrt(),ceil()
#include <cstring>//strcpy()

/*Definiciones*/
using std::left;using std::setw;//<iomanip>

/*Estructuras*/
struct carta {
  string palabra;
  bool descubierta;
  int longitud;
  int fila;
  int columna;
  bool par;
  int posicion; //Usado solamente en juego simulado
  // Ya que optimiza mucho la logica de esa funcion
};
struct registrojuego {
  char alias[50];
  char fecha[11];
  char categoria[50];
  float tiempo_logrado;
  int filas;
  int columnas;
};

/*Prototipos/Funciones*/
inline void registrarJuego(int filas, int columnas, const string alias,float elapsed_time, const string categoria,const string fecha) {
  const string registros="registros.dat";
  ofstream archivo(registros, ios::binary | ios::out | ios::app);
  if (!archivo) {
    clearScreen();
    fflush(stdout);
    cout<<ROJO;recuadro();
    Play_Sound("error.wav");
    gotoxy(win_size_x()/2 -30,win_size_y()/2-1);
    cerr <<ROJO<< "ERROR: No se pudo abrir el archivo binario '"<<registros<<"'" <<CLR_RST;
    PresioneTecla();
    return;
  }

  registrojuego registro;
  strcpy(registro.alias, alias.c_str());
  strcpy(registro.fecha, fecha.c_str());
  strcpy(registro.categoria, categoria.c_str());
  registro.tiempo_logrado = elapsed_time;
  registro.filas = filas;
  registro.columnas = columnas;
  archivo.write(reinterpret_cast<const char *>(&registro),sizeof(registrojuego));
  archivo.close();
}
inline void imprimirMatriz(carta **matriz, int filas, int columnas,int fila_actual, int columna_actual, int pares,float elapsed_time,string alias,int modo) {
  int x = win_size_x() / 2 - (columnas * 10) / 2,y = win_size_y() / 2 - filas / 2; // 9 es el tamano de la casilla
  clearScreen();
  gotoxy(3, 2);
  cout << "Alias: " << alias;
  gotoxy(3, 3);
  cout << "Total de pares: " << pares;
  gotoxy(win_size_x() - 18, 2);
  cout << "Fecha: " << Fecha_actual();
  gotoxy(win_size_x() - 18, 3);
  cout << "Hora:  " << Hora_actual() << " hrs";
  /*if(pares == ((filas * columnas) / 2)){
  }*/
  if(modo==1){
    x-=20;
  }
  const int setwidth=19;
  if(modo==1){gotoxy(x+6, y-3);
  cout<<CYAN<<"Juego Simulado"<<CLR_RST;
  }
  if(modo==0){
  gotoxy(x, y++);
  cout<<setw(5);
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      if (matriz[i][j].descubierta == true) {
        if (fila_actual == i && columna_actual == j) {
          cout << AMARILLO << matriz[i][j].palabra <<setw(setwidth-matriz[i][j].longitud)<<CLR_RST;
        } else {
          cout << CYAN << matriz[i][j].palabra <<setw(setwidth-matriz[i][j].longitud)<<CLR_RST;
        }
      } else {
        if (fila_actual == i && columna_actual == j) {
          cout << AMARILLO << "█████████████  " << CLR_RST;//seleccionada
        } else {
          cout << "█████████████  ";
        }
      }
    } // j
    gotoxy(x, y++);
    gotoxy(x, y++);
  } // i
  }else{
    gotoxy(x, y++);
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      if (matriz[i][j].descubierta == true) {
          cout << AZUL << matriz[i][j].palabra <<setw(setwidth-matriz[i][j].longitud)<<CLR_RST;
        } else {
          cout << "█████████████  ";
        }
      }
    gotoxy(x, y++);
    gotoxy(x, y++);
    }
  } // i
  if(modo ==1){
  const int setwidth=19;
  x+=45;
  y = win_size_y() / 2 - filas / 2;
  gotoxy(x+3, y-3);
  cout<<VERDE<<"Juego Soucionado"<<CLR_RST;

  gotoxy(x,y++);
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      cout << AZUL << matriz[i][j].palabra <<setw(setwidth-matriz[i][j].longitud)<<CLR_RST;
    } // j
    gotoxy(x, y++);
    gotoxy(x, y++);
  } // i
  }
  fflush(stdout);
}

inline void ImprimirJuegoEntexto(carta **matriz,int filas,int columnas,string alias,string categoria){
   ofstream archivo("matrices.txt",ios::app);
   archivo << "----------------------------------------------------------------";
   archivo << "\n\n";
   archivo << "Alias: " << alias;
   archivo << "\n";
   archivo << "Fecha: " << Fecha_actual();
   archivo << "\n";
   archivo << "Hora:  " << Hora_actual() << " hrs";
   archivo << "\n";
   archivo << "Categoria: " << categoria;
   archivo << "\n";
   archivo << "Filas: "<<filas;
   archivo << "\t";
   archivo << "Columnas: "<<columnas;
   archivo << "\n\n";
    // Imprimir la matriz en el archivo
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            archivo <<left<<setw(15) << matriz[i][j].palabra;
        }
        archivo << "\n";
    }
    archivo << "\n";
    archivo.close();
}
inline void juego(carta **matriz, int filas, int columnas, string categoria,string alias) {
  int fila_actual = 0, columna_actual = 0;
  bool carta_uno_elejida = false, partida_ganada = false;  bool salir_juego=false;
  carta uno, dos;
  int pares = 0;//int errores=0;
  time_t start_time, current_time;
  double elapsed_time;
  const string fecha_actual = Fecha_actual();
  const string categoriaconst = categoria;
  start_time = time(NULL);
  while (salir_juego!=true) {
    current_time = time(NULL); // Obtener el tiempo actual
    elapsed_time = difftime(current_time, start_time);

    imprimirMatriz(matriz, filas, columnas, fila_actual, columna_actual, pares,elapsed_time,alias,0); // primer

    switch (getch()) {
    case KEY_UP:
      if (fila_actual > 0) {
        Play_Sound("pop.wav");
        fila_actual--;
      }
      break;
    case KEY_DOWN:
      if (fila_actual < filas - 1) {
        Play_Sound("pop.wav");
        fila_actual++;
      }
      break;
    case KEY_LEFT:
      if (columna_actual > 0) {
        Play_Sound("pop.wav");
        columna_actual--;
      }
      break;
    case KEY_RIGHT:
      if (columna_actual < columnas - 1) {
        Play_Sound("pop.wav");
        columna_actual++;
      }
      break;
    case KEY_ENTER: // windows
    case '\n':      // nix
      if (matriz[fila_actual][columna_actual].par == false) {
        if (carta_uno_elejida == true) {
          if (fila_actual == uno.fila && columna_actual == uno.columna) {
          } else {
            matriz[fila_actual][columna_actual].descubierta = true;

            imprimirMatriz(matriz, filas, columnas, fila_actual, columna_actual,pares,elapsed_time,alias,0); // imprimir la segunda carta volteada

            dos.palabra = matriz[fila_actual][columna_actual].palabra;
            // comprobacion de pares
            if (dos.palabra == uno.palabra) {
              pares++;
              Play_Sound("exito.wav");
              matriz[uno.fila][uno.columna].descubierta = true;
              matriz[fila_actual][columna_actual].descubierta = true;
              matriz[uno.fila][uno.columna].par = true;
              matriz[fila_actual][columna_actual].par = true;
              carta_uno_elejida = false;
              if (pares == ((filas * columnas) / 2)) {
                partida_ganada = true;
                salir_juego = true;
              }
            } else { // pares distintos
              //errores++;  //no se piden los errores
              Play_Sound("error.wav");
              matriz[uno.fila][uno.columna].descubierta = false;
              matriz[fila_actual][columna_actual].descubierta = false;
              carta_uno_elejida = false;
            }

            usleep(600000); // para para hacer ver la comprabacion se esperan 600 ms (600000 useconds)
          }
        } else { // carta uno elegida == false
          matriz[fila_actual][columna_actual].descubierta = true;
          uno.palabra = matriz[fila_actual][columna_actual].palabra;
          uno.fila = fila_actual;
          uno.columna = columna_actual;
          carta_uno_elejida = true;
        }
      } // if matriz[fila_actual][columna_actual].par == false
      break;
      case 113://salir con la letra q
      salir_juego=true;
      break;
    } // switch getch
  }   // while juego
  if (partida_ganada) {
    ImprimirJuegoEntexto(matriz,filas,columnas,alias,categoria);
    registrarJuego(filas, columnas, alias, elapsed_time, categoriaconst,fecha_actual);

    ganaste(alias,elapsed_time,pares);
    PresioneTecla();
  }
}
//Funcion que simula un juego con una matriz de 3x2
inline void juegoSimulado(carta **matriz, int filas, int columnas) {
  //declaracion de variables iniciales
  int x = win_size_x()/2-(35/2);int y = win_size_y()/2-1;
  int pares = 0,k=0;
  int columna1=0, fila1=0, columna2=0, fila2=0;
  bool partida_ganada = false;
  time_t start_time, current_time;
  double elapsed_time;
  const string fecha_actual = Fecha_actual();
  const string alias = "Computadora";
  start_time = time(NULL);


  //for que llena el .posicion de cada casilla de la matriz
  for(int i=0;i<3;i++){
    for(int j=0;j<2;j++){
      matriz[i][j].posicion=k;
      k++;
    }
  }

  //vector booleano que identifica las combinaciones fallidas como true, se inicializa
  //en falso cada casilla con un for
  bool combinacionesFallidas[6][6];
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 6; j++) {
       combinacionesFallidas[i][j] = false;
    }
  }

  //Mientras la partida no este ganada, se continuara el programa
  while (partida_ganada == false) {
    current_time = time(NULL); // Obtener el tiempo actual
    elapsed_time = difftime(current_time, start_time);

    //Primer casilla, la randomiza siempre y cuando el .par no sea true
    //(es decir) siempre que sea una carta que no haya sido par
    do {
      columna1 = rand() % 2;
      fila1 = rand() % 3;
    } while (matriz[fila1][columna1].par==true);


    //realizacion de los sleeps para que se vea como una "simulacion" //carta 1
    imprimirMatriz(matriz, filas, columnas, fila1, columna1, pares,elapsed_time,alias,1);
    usleep(700000);
    matriz[fila1][columna1].descubierta = true;
    imprimirMatriz(matriz, filas, columnas, fila1, columna1, pares, elapsed_time,alias,1);
    usleep(700000);

    //Segunda casilla, la randomiza siempre y cuando no sea igual a la otra casilla
    //o sea par, o la combinacion de esta casilla con la otra sea fallida (true)

    do {
      columna2 = rand() % 2;
      fila2 = rand() % 3;
    } while ((columna1 == columna2 && fila1 == fila2) ||
             (matriz[fila2][columna2].par == true)||
      (combinacionesFallidas[matriz[fila1][columna1].posicion][matriz[fila2][columna2].posicion] == true));

    //Sleeps de simulacion //carta 2
    matriz[fila2][columna2].descubierta = true;
    imprimirMatriz(matriz, filas, columnas, fila2, columna2, pares,elapsed_time,alias,1);
    usleep(700000);

    //Comprobacion de si son iguales las cartas
    if (matriz[fila1][columna1].palabra == matriz[fila2][columna2].palabra) {
      Play_Sound("exito.wav");
      matriz[fila1][columna1].par = true;
      matriz[fila2][columna2].par = true;
      matriz[fila1][columna1].descubierta = true;
      matriz[fila2][columna2].descubierta = true;
      pares += 1;
    } else {
      Play_Sound("error.wav");
      matriz[fila1][columna1].descubierta = false;
      matriz[fila2][columna2].descubierta = false;
      combinacionesFallidas[matriz[fila1][columna1].posicion][matriz[fila2][columna2].posicion] = true;
      combinacionesFallidas[matriz[fila2][columna2].posicion][matriz[fila1][columna1].posicion] = true;
    }
    if (pares == 3) {
    ganaste(alias,elapsed_time,pares);
    PresioneTecla();
    partida_ganada = true;
  }
  }//while
}

// Funcion que lee desde el archivo de texto las palabras y posteriormente crea
// un arreglo del tamaño maximo de palabras que quiso el usuario
inline void leerPalabras(string palabras[], int MAX_PALABRAS,string categoria) {
  int contador = 0;
  ifstream archivo(categoria);
  if (!archivo) {
    string error = "ERROR: Hubo un error al leer el archivo de palabras '" + categoria + "', no se puede jugar";
    Play_Sound("error.wav");
    cout << ROJO;
    salir_programa(error.c_str());
  } else {
    srand(time(nullptr));  // Semilla para generar números aleatorios
    string palabra;
    int totalPalabras = 0; // Contador de palabras totales en el archivo

    // Contar el número total de palabras en el archivo
    while (archivo >> palabra) {
      totalPalabras++;
    }

    // Verificar que el número total de palabras sea mayor o igual a MAX_PALABRAS
    if (totalPalabras < MAX_PALABRAS  && !categoria.empty()) {
      string error = "ERROR: El archivo '"+categoria+"' no contiene suficientes palabras, no se puede jugar";
      Play_Sound("error.wav");
      cout << ROJO;
      salir_programa(error.c_str());
    } else{
      archivo.clear();
      archivo.seekg(0); // Regresar al inicio del archivo

      // Saltar aleatoriamente a una posición dentro del archivo
      int posicionInicial = rand() % (totalPalabras - MAX_PALABRAS + 1);
      for (int i = 0; i < posicionInicial; i++) {
        archivo >> palabra;
      }

      // Leer las palabras aleatoriamente hasta alcanzar MAX_PALABRAS
      while (archivo >> palabra && contador < MAX_PALABRAS) {
        palabras[contador] = palabra;
        contador++;
      }
    }
    archivo.close();
  }
}

// Funcion que Crea una string dinamica donde estan 2 veces cada palabra
inline string *duplicarPalabras(string palabras[], int tamanoriginal) {
  int tamanoNuevoArreglo = tamanoriginal * 2;
  string *nuevoArreglo = new string[tamanoNuevoArreglo];
  for (int i = 0; i < tamanoriginal; i++) {
    nuevoArreglo[i * 2] = palabras[i];
    nuevoArreglo[i * 2 + 1] = palabras[i];
  }
  return nuevoArreglo;
}
// Funcion que DESORDENA las palabras (shuffle)
inline void desordenarPalabras(string *palabras, int tamanoNuevoArreglo) {
  for (int i = 0; i < tamanoNuevoArreglo - 1; i++) {
    int j = i + rand() / (RAND_MAX / (tamanoNuevoArreglo - i) + 1);
    string p = palabras[j];
    palabras[j] = palabras[i];
    palabras[i] = p;
  }
}
// Funcion que crea una matriz dinamica y posteriormente añade el vector a la
// matriz

inline carta **crearMatriz(string *nuevoArreglo, int filas, int columnas) {
  carta **matriz = new carta *[filas];
  for (int i = 0; i < filas; i++) {
    matriz[i] = new carta[columnas];
  }
  int k = 0;
  for (int i = 0; i < filas; i++) {
    for (int j = 0; j < columnas; j++) {
      matriz[i][j].palabra = nuevoArreglo[k];
      matriz[i][j].descubierta = false;
      matriz[i][j].par = false;
      matriz[i][j].longitud = matriz[i][j].palabra.length();
      k++;
    }
  }
  return matriz;
}
inline void mostrarRegistros(const string &archivo) {
  clearScreen();
  bool encontrado=false,titulo=true;
  int x=win_size_x()/2-(35/2);
  int y=win_size_y()/2-1;
  string alias;
  ifstream inputFile(archivo, ios::binary | ios::in);
  if (!inputFile.is_open()) {
    clearScreen();
    fflush(stdout);
    cout<<ROJO;recuadro();
    Play_Sound("error.wav");
    gotoxy(win_size_x()/2 -30,win_size_y()/2-1);
    cerr << ROJO<< "ERROR: No se pudo abrir el archivo binario '"<<archivo<<"'"<<CLR_RST;
    PresioneTecla();
    return;
  }
  gotoxy(x,y);
  cout <<"Escribe tu alias: ";
  alias=validacion(x,y,ALIAS);
  clearScreen();

   x = win_size_x() / 2 - 30;
   y = win_size_y() / 2 - 5;

  registrojuego registro;

  while (inputFile.read(reinterpret_cast<char *>(&registro),sizeof(registrojuego))){
    if(registro.alias==alias){
    encontrado=true;
      if(titulo){
        titulo=false;
        gotoxy(x, y++);
        cout << left << setw(15) << "Alias" << setw(12) << "Fecha" << setw(8) << "Tiempo"
            << setw(16) << "Categoría" << setw(6) << "Filas" << setw(9) << "Columnas";gotoxy(x, y++);
        cout<< "--------------------------------------------------------------------";gotoxy(x, y++);
      }
        cout << left << setw(15) << registro.alias << setw(12) << registro.fecha
         << setw(8) << fixed << setprecision(0) << registro.tiempo_logrado
         << setw(16) << registro.categoria << setw(6) << registro.filas
         << setw(9) << registro.columnas;
        gotoxy(x, y++);
    }
  }

  if(!encontrado){
    clearScreen();
    fflush(stdout);
    cout<<AMARILLO;recuadro();
    Play_Sound("error.wav");
    gotoxy(win_size_x()/2-15,win_size_y()/2-1);
    cerr<<AMARILLO<<"ERROR: Alias '"<<alias<<"' no encontrado"<<CLR_RST;
  }

  inputFile.close();
  fflush(stdout);
  PresioneTecla();
}
inline void mostrarRegistrosPorcategoria(const string &archivo,string categoria) {
  int x = win_size_x() / 2 - 30;
  int y = win_size_y() / 2 - 5;
  bool encontrado=false,titulo=true;
  ifstream inputFile(archivo, ios::binary | ios::in);
  if (!inputFile.is_open()) {
    clearScreen();
    fflush(stdout);
    cout<<ROJO;recuadro();
    Play_Sound("error.wav");
    gotoxy(win_size_x()/2 -30,win_size_y()/2-1);
    cerr <<ROJO<< "ERROR: No se pudo al abrir el archivo binario '"+ archivo +"'"<<CLR_RST;
    PresioneTecla();
    return;
  }

  registrojuego registro;

  while (inputFile.read(reinterpret_cast<char *>(&registro),sizeof(registrojuego))) {
    if (registro.categoria == categoria) {
      encontrado=true;
      if(titulo){
        gotoxy(x, y++);
        cout << left << setw(15) << "Alias" << setw(12) << "Fecha" << setw(8)
            << "Tiempo" << setw(16) << "Categoría" << setw(6) << "Filas" << setw(9)
            << "Columnas";
        gotoxy(x, y++);
        cout<< "--------------------------------------------------------------------",
        gotoxy(x, y++);
        titulo=false;
      }
      cout << left << setw(15) << registro.alias << setw(12) << registro.fecha
           << setw(8) << fixed << setprecision(0) << registro.tiempo_logrado
           << setw(16) << registro.categoria << setw(6) << registro.filas
           << setw(9) << registro.columnas;
      gotoxy(x, y++);
    }
  }

  if(!encontrado){
    clearScreen();
    fflush(stdout);
    cout<<AMARILLO;recuadro();
    Play_Sound("error.wav");
    gotoxy(win_size_x()/2-15,win_size_y()/2-1);
    cerr<<AMARILLO<<"ERROR: aun no has jugado con esta categoria"<<CLR_RST;
  }

  inputFile.close();
  fflush(stdout);
  PresioneTecla();
}
inline void mostrarRegistrosPorDimension(const string &archivo, int filas,int columnas) {
  int x = win_size_x() / 2 - 30;
  int y = win_size_y() / 2 - 5;
  bool titulo=true,encontrado=false;
  ifstream inputFile(archivo, ios::binary | ios::in);
  if (!inputFile.is_open()) {
    clearScreen();
    fflush(stdout);
    cout<<ROJO;recuadro();
    Play_Sound("error.wav");
    gotoxy(win_size_x()/2 -30,win_size_y()/2 -1);
    cerr <<ROJO<< "ERROR: No se pudo abrir el archivo binario '"+archivo+"'"<<CLR_RST;
    PresioneTecla();
    return;
  }


  registrojuego registro;

  while (inputFile.read(reinterpret_cast<char *>(&registro),sizeof(registrojuego))) {
    if (registro.columnas == columnas && registro.filas == filas) {
      encontrado=true;
      if(titulo){
        gotoxy(x, y++);
        cout << left << setw(15) << "Alias" << setw(12) << "Fecha" << setw(8)
        << "Tiempo" << setw(16) << "Categoría" << setw(6) << "Filas" << setw(9)
        << "Columnas";
        gotoxy(x, y++);
        cout<< "--------------------------------------------------------------------",
        gotoxy(x, y++);
        titulo=false;
      }
      cout << left << setw(15) << registro.alias << setw(12) << registro.fecha
           << setw(8) << fixed << setprecision(0) << registro.tiempo_logrado
           << setw(16) << registro.categoria << setw(6) << registro.filas
           << setw(9) << registro.columnas;
      gotoxy(x, y++);
    }
  }
  if(!encontrado){
    clearScreen();
    fflush(stdout);
    cout<<AMARILLO;recuadro();
    Play_Sound("error.wav");
    gotoxy(win_size_x()/2-15,win_size_y()/2-1);
    cerr<<AMARILLO<<"ERROR: Aun no juega con esta dimension"<<CLR_RST;
  }
  inputFile.close();
  fflush(stdout);
  PresioneTecla();
}

#endif // juegoHead.h
