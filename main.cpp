/*librerias propias*/
//[x]Dos
#include "menus.h"
//#include "JuegoHead.h" //omitido,incluido en menus.h
// #include "FuncionesGen.h"//omitido,incluido en JuegoHead.h

/*librerias c++*/
//#include <iostream>//omitido,incluido en FuncionesGen.h
//#include <string>//omitido,incluido en FuncionesGen.h
//#include <fstream>//omitido,incluido en FuncionesGen.h
//#include <iomanip>//omitido,incluido en FuncionesGen.h

/*librerias c*/
//#include <cstdlib>//omitido,incluido en FuncionesGen.h
//#include <ctime>//omitido,incluido en FuncionesGen.h
//#include <cmath>//omitido,incluido en JuegoHead.h
//#include <cstring>//omitido,incluido en JuegoHead.h
//#include <unistd.h>//omitido,incluido en FuncionesGen.h

/*Estructuras*/
// struct carta //incluido en JuegoHead.h
//struct registrojuego //incluido en JuegoHead.h


/*Prototipos/Funciones*/
/*caso 1*/
void iniciar_juego();
void pantallas();
void primer_pantalla();
void segunda_pantalla();
  /*menus.h*/
    //void Mantenimiento();
    //void simulacion();
    //void registrocolumnas();
    //void reportes();
  /*FuncionesGen.h*/
    //void clearScreen();
    //void Stop_Sound();
    //void Pantalla_Completa();
    //void recuadro();
    //void logouaa();
    //void flecha_derecha();
    //void flecha_izquierda();
    //void logojuego2();
    //void PresioneTecla();

/*caso 2*/
void menu(int seleccion);
void MenuCantidadPalabras(int seleccion);
void menuMantenimiento(int seleccion);
void reporteMenu(int seleccion);
  /*menus.h*/
    //void menuMantenimiento(int seleccion);
    //void MenuCantidadPalabras(int seleccion);
  /*JuegoHead.h*/
    //void registrarJuego(int filas, int columnas, const string alias,float elapsed_time, const string categoria,const string fecha);
    //void imprimirMatriz(carta **matriz, int filas, int columnas,int fila_actual, int columna_actual, int pares,float elapsed_time,string alias,int modo);
    //void ImprimirJuegoEntexto(carta **matriz,int filas,int columnas,string alias);
    //void juego(carta **matriz, int filas, int columnas, string categoria,string alias);
    //void juegoSimulado(carta **matriz, int filas, int columnas);
    //void leerPalabras(string palabras[], int MAX_PALABRAS,string categoria);
    //void desordenarPalabras(string *palabras, int tamanoNuevoArreglo);
    //void mostrarRegistros(const string &archivo);
    //void mostrarRegistrosPorcategoria(const string &archivo,string categoria);
    //void mostrarRegistrosPorDimension(const string &archivo, int filas,int columnas);
  /*FuncionesGen.h*/
    //void gotoxy(int x, int y);
    //void Play_Sound(string archivo);
    //void salir_programa(string error);
    //void MenuCantidadPalabras_G(int seleccion);
    //void MenuCantidadPalabras_F(int x, int y);
    //void bajas(string nombreArchivo,string elemento);
    //void altas(string nombreArchivo,string elemento);
    //void mostrar(string nombreArchivo);
    //void reporteMenu(int seleccion);
    //void ganaste(string alias,float elapsed_time, int pares);
  
/*caso 3*/
// int main(); //implicito
  /*FuncionesGen.h*/
    //int win_size_x();
    //int win_size_y()
    //string menuPalabras();
    //string Fecha_actual_letras();
    //string Fecha_actual();
    //string Hora_actual();

/*caso 4*/
  /*FuncionesGen.h*/
    //string validacion(int x,int y,int TIPO);
  /*JuegoHead.h*/
    //string *duplicarPalabras(string palabras[], int tamanoriginal);
    //carta **crearMatriz(string *nuevoArreglo, int filas, int columnas);


int main() {
#if defined(_WIN32)
  SetConsoleOutputCP(CP_UTF8); // deja utilizar caracteres unicode
  clearScreen();
  gotoxy(win_size_x()/2 -15 ,win_size_y()/2);
  cout<<"Para empezar ponga pantalla completa";
  gotoxy(win_size_x()/2 -13 ,win_size_y()/2 +1);
  cout<<"y presione cualquier tecla";
  getch();
#else                          // funciones ncurses
  initscr();            // Start curses mode
  raw();                // Line buffering disabled
  keypad(stdscr, TRUE); // obtener estado del teclado
  noecho();             // sin echo() output of getch()
  refresh();            // para que se vea la primer pantalla
#endif
  Pantalla_Completa();
  Play_Sound("song.wav");
  srand(time(NULL));
  cout << HIDE_CRSR;
  pantallas();
  return 0;
}

void pantallas() {
  int pantalla = 1, seleccion = 0;
  bool salir = false;
  string archivo = "registros.dat";
  while (salir == false) {

    switch (pantalla) {
    case 1:
      primer_pantalla();
      break;
    case 2:
      segunda_pantalla();
      break;
    case 3:
      menu(seleccion);
      break;
    }
    switch (getch()) {
    case KEY_LEFT:
      if (pantalla > 1) {
        Play_Sound("pop.wav");
        pantalla--;
      }
      break;
    case KEY_RIGHT:
      if (pantalla < 3) {
        Play_Sound("pop.wav");
        pantalla++;
      }
      break;
    case KEY_UP:
      if (pantalla == 3 && seleccion > 0) {
        Play_Sound("pop.wav");
        seleccion--;
      }

      break;
    case KEY_DOWN:
      if (pantalla == 3 && seleccion < 4) {
        Play_Sound("pop.wav");
        seleccion++;
      }
      break;
    case KEY_ENTER: // windows
    case '\n':      // linux
      if (pantalla == 3) {
        switch (seleccion) {
        case 0: // jugar
          Stop_Sound();
          iniciar_juego();
          break;
        case 1: // Reporte
          reportes();
          break;
        case 2: // Simulacion
          Stop_Sound();
          simulacion();
          break;
        case 3: // Mantenimiento
          Mantenimiento(); 
          break;
        case 4: // Salir
          Stop_Sound();
          cout<<AZUL;
          salir_programa("Se salio del programa al precionar el boton de salir");
          break;
        }
      }
      break;
    } // switch
  }
  // si se sale del while selectivo inicia juego
}

void iniciar_juego() {
  int seleccion2 = 0, MAX_PALABRAS = 0;
  bool salida = false;
  string alias;
  clearScreen();
  int x=win_size_x()/2-(35/2);
  int y=win_size_y()/2-1;
  //reset_shell_mode();//<--------------------------------------------------------------------------
  gotoxy(x,y);
  cout<<"Escribe tu alias: ";
  alias=validacion(x,y,ALIAS);
  //reset_prog_mode();//<--------------------------------------------------------------------------
  while (salida == false) {
    MenuCantidadPalabras(seleccion2);
    switch (getch()) {
    case KEY_LEFT:
      if (seleccion2 > 0) {
        Play_Sound("pop.wav");
        seleccion2--;
      }
      break;
    case KEY_RIGHT:
      if (seleccion2 < 2) {
        Play_Sound("pop.wav");
        seleccion2++;
      }
      break;
    case KEY_ENTER: //windows
    case '\n': //nix
      switch (seleccion2) {
      case 0:
        MAX_PALABRAS = 3;
        salida = true;
        break;
      case 1:
        MAX_PALABRAS = 6;
        salida = true;
        break;
      case 2:
        MAX_PALABRAS = 8;
        salida = true;
        break;
      }//seleccion
      clearScreen();//arregla un error
      break;
    }//switch
  }
  string categoria = menuPalabras();
  if(!categoria.empty()){
  string palabras[MAX_PALABRAS];

  leerPalabras(palabras, MAX_PALABRAS, categoria);

  int tamanoriginal = sizeof(palabras) / sizeof(palabras[0]);
  string *nuevoArreglo = duplicarPalabras(palabras, tamanoriginal);
  int tamanoNuevoArreglo = tamanoriginal * 2;

  desordenarPalabras(nuevoArreglo, tamanoNuevoArreglo);

  int filas=0, columnas=0;
  filas = static_cast<int>(ceil(sqrt(tamanoNuevoArreglo)));
  columnas = static_cast<int>(ceil(tamanoNuevoArreglo / filas));
  carta **matriz = crearMatriz(nuevoArreglo, filas, columnas);
  
  juego(matriz, filas, columnas,categoria,alias); // con las variables creadas se inicia el juego

  for (int i = 0; i < filas; i++) {
    delete[] matriz[i];
  }
  delete[] matriz;
  delete[] nuevoArreglo;
  }//si categoria empty no se juega
}

/*menus*/
void primer_pantalla() {
  //   Pantalla_Completa();

  /*Primer Pantalla*/
  //[x]Colores
  //[x]Gotoxy
  //[x]sonidos
  clearScreen();
  flecha_derecha();
  const int altura_grafico = 16, ancho_grafico = 43;
  int x = (win_size_x() / 3) + (ancho_grafico / 3), y = (win_size_y() / 2) - (altura_grafico / 3);
  logouaa();
  gotoxy(x, y++);
  cout << AZUL << "UAA, Carrera: ISC,";  gotoxy(x, y++);
  cout << ROJO << "Materia: Programacion 1,";  gotoxy(x, y++);
  cout << VERDE << "Nombre del sistema: Memoria Extreeem,";  gotoxy(x, y++);
  cout << MAGENTA << "Nombre del Profesor: ";gotoxy(x, y++);
  /*Nombres de estudiantes y profesores ocultos para proteger la privacidad*/
  cout << CYAN << "Fecha: "<< Fecha_actual_letras() << CLR_RST;
  fflush(stdout);
}

void segunda_pantalla() {
  /*Segunda Pantalla*/
  //[x]Colores
  //[x]Gotoxy
  //[x]sonidos
  clearScreen();
  flecha_izquierda();
  flecha_derecha();
  logojuego2();
}

void menu(int seleccion) {
  /*Tercera Pantalla*/
  //[x]Gotoxy
  //[x]Colores
  //[x]recuadro y/o algo que lo diferencie (flecha)
  clearScreen();
  flecha_izquierda();
  const char *colores[5] = {CYAN, MAGENTA, AZUL, AMARILLO, VERDE};
  const char *opciones[5]  ={"  █ █ █ █▀▀ ▄▀█ █▀█","█▀█ █▀▀ █▀█ █▀█ █▀█ ▀█▀ █▀▀ █▀","█▀ █ █▀▄▀█ █ █ █   ▄▀█ █▀▀ █ █▀█ █▄ █","█▀▄▀█ ▄▀█ █▄ █ ▀█▀ █▀▀ █▄ █ █ █▀▄▀█ █ █▀▀ █▄ █ ▀█▀ █▀█","█▀ ▄▀█ █   █ █▀█"};
  const char *opciones2[5] ={"█▄█ █▄█ █▄█ █▀█ █▀▄","█▀▄ ██▄ █▀▀ █▄█ █▀▄  █  ██▄ ▄█","▄█ █ █ ▀ █ █▄█ █▄▄ █▀█ █▄▄ █ █▄█ █ ▀█","█ ▀ █ █▀█ █ ▀█  █  ██▄ █ ▀█ █ █ ▀ █ █ ██▄ █ ▀█  █  █▄█","▄█ █▀█ █▄▄ █ █▀▄"};

  const int altura_grafico = 10, ancho_grafico = 58;
  int x = (win_size_x() / 2) - (ancho_grafico / 2),y = (win_size_y() / 2) - (altura_grafico/2);
  gotoxy(x, y++);
  for (int i = 0; i < 5; i++) {
    cout<<colores[i];
    if (i == seleccion) {
      cout << "    ▀▄  " << opciones[i];gotoxy(x,y++);
      cout << "▀▀▀▀▀█▀ " << opciones2[i];gotoxy(x, y++);
      cout << "    ▀   " <<CLR_RST;gotoxy(x,y++);
    } else {
      cout << "        " << opciones[i]; gotoxy(x,y++);
      cout << "        " <<opciones2[i];gotoxy(x, y++);
      cout << "        " <<CLR_RST;gotoxy(x,y++);
    }
  }
  fflush(stdout);
}
