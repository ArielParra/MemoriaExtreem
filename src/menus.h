/* Ariel Emilio Parra Martinez ID:280862*/
/* Miguel Angel Batres Luna ID:350553*/
#ifndef menus
#define menus

/*librerias propias*/
#include "JuegoHead.h"

/*Prototipos/Funciones*/
inline string menuPalabras() {
  clearScreen();
  int seleccion=0;
  bool salida = false;
  string BM_Bands= "BMBANDS.txt";
  string linuxdistro="linuxdistro.txt";
  string colorestext = "colores.txt";
  string salidaP;

  while (salida == false) {
    const char *colores[4] = {CYAN, MAGENTA, AZUL, AMARILLO};
    const char *opciones[4]  ={"█▄▄ █▀▄▀█   █▄▄ ▄▀█ █▄ █ █▀▄ █▀","█▀▀ █▀█ █   █▀█ █▀█ █▀▀ █▀","█   █ █▄ █ █ █ ▀▄▀   █▀▄ █ █▀ ▀█▀ █▀█ █▀█ █▀","█▀ ▄▀█ █   █ █▀█"};
    const char *opciones2[4] ={"█▄█ █ ▀ █   █▄█ █▀█ █ ▀█ █▄▀ ▄█","█▄▄ █▄█ █▄▄ █▄█ █▀▄ ██▄ ▄█","█▄▄ █ █ ▀█ █▄█ █ █   █▄▀ █ ▄█  █  █▀▄ █▄█ ▄█","▄█ █▀█ █▄▄ █ █▀▄"};
  const int altura_grafico = 10, ancho_grafico = 58;
  int x = (win_size_x() / 2) - (ancho_grafico / 2), y = (win_size_y() / 2) - (altura_grafico/2);
  gotoxy(x, y++);
  for (int i = 0; i < 4; i++) {
    cout<<colores[i];
    if (i == seleccion) {
      cout << "    ▀▄  " << opciones[i];gotoxy(x,y++);
      cout << "▀▀▀▀▀█▀ " << opciones2[i];gotoxy(x, y++);
      cout << "    ▀   "<<CLR_RST;gotoxy(x,y++);
    } else {
      cout << "        " << opciones[i];gotoxy(x,y++);
      cout << "        " <<opciones2[i];gotoxy(x, y++);
      cout << "        "<<CLR_RST;gotoxy(x,y++);
    }
  }
  fflush(stdout);
    switch (getch()) {
    case KEY_UP:
      if (seleccion > 0) {
        Play_Sound("pop.wav");
        seleccion--;
      }
      break;
    case KEY_DOWN:
      if (seleccion < 3) {
        Play_Sound("pop.wav");
        seleccion++;
      }
      break;
    case KEY_ENTER: //windows
    case '\n': //nix
      switch (seleccion) {
      case 0:
        salidaP = BM_Bands;
        salida = true;
        break;
      case 1:
        salidaP = colorestext;
        salida = true;
        break;
      case 2:
        salidaP = linuxdistro;
        salida = true;
        break;
      case 3:
        salida = true; 
        break;
      }
      break;
    }//switch
  }
  clearScreen();
  return salidaP;
}
inline void menuMantenimiento(int seleccion) {
  clearScreen();
  const char *colores[4] = {CYAN, MAGENTA, AZUL, AMARILLO};
  const char *opciones[4]  = {"▄▀█ █   ▀█▀ ▄▀█ █▀","█▄▄ ▄▀█   █ ▄▀█ █▀","█▀▄▀█ █▀█ █▀ ▀█▀ █▀█ ▄▀█ █▀█","█▀ ▄▀█ █   █ █▀█"};
  const char *opciones2[4] = {"█▀█ █▄▄  █  █▀█ ▄█","█▄█ █▀█ █▄█ █▀█ ▄█","█ ▀ █ █▄█ ▄█  █  █▀▄ █▀█ █▀▄","▄█ █▀█ █▄▄ █ █▀▄"};
  const int altura_grafico = 10, ancho_grafico = 36;
  int x = (win_size_x() / 2) - (ancho_grafico / 2), y = (win_size_y() / 2) - (altura_grafico/2);
  gotoxy(x, y++);
  for (int i = 0; i < 4; i++) {
    cout<<colores[i];
    if (i == seleccion) {
      cout << "    ▀▄  " << opciones[i];gotoxy(x,y++);
      cout << "▀▀▀▀▀█▀ " << opciones2[i];gotoxy(x, y++);
      cout << "    ▀   " <<CLR_RST;gotoxy(x,y++);
    } else {
      cout << "        " << opciones[i];gotoxy(x,y++);
      cout << "        " <<opciones2[i];gotoxy(x, y++);
      cout << "        " <<CLR_RST;gotoxy(x,y++);
    }
  }
  fflush(stdout);
}

inline void Mantenimiento(){
  int seleccion = 0;
  bool salida = false;
  string categoria,elemento;
  int x=(win_size_x()/2 -(30/2));
  int y=(win_size_y()/2 -1);
  while (salida == false) {
    menuMantenimiento(seleccion);
    switch (getch()) {
    case KEY_UP:
      if (seleccion > 0) {
        Play_Sound("pop.wav");
        seleccion--;
      }
      break;
    case KEY_DOWN:
      if (seleccion < 3) {
        Play_Sound("pop.wav");
        seleccion++;
      }
      break;
    case KEY_ENTER: //windows
    case '\n': //nix
      switch (seleccion) {
      case 0:
        categoria = menuPalabras();
        if(categoria.empty()){
          break;
        }else{
        clearScreen();
        gotoxy(x,y);
        cout<<"Dame la palabra a añadir: ";
        elemento=validacion(x,y,ALTASBAJAS);
        altas(categoria,elemento);}
        break;
      case 1:
        categoria = menuPalabras();
        if(categoria.empty()){
          break;
        }else{
        clearScreen();
        gotoxy(x,y);
        cout<<"Dame la palabra a eliminar: ";
        elemento=validacion(x,y,ALTASBAJAS);
        bajas(categoria,elemento);
        }
        break;
      case 2:
        categoria = menuPalabras();
        if(categoria.empty()){
          break;
        }else{
        mostrar(categoria);
        }
        break;
      case 3:
        salida = true; 
        break;
      }
      break;
    }//switch
  }
  
}
inline void MenuCantidadPalabras(int seleccion) {
  clearScreen();
  cout<<AZUL;
  MenuCantidadPalabras_G(seleccion);
int x=0,y=0;
  switch (seleccion) {
  case 0:
    x=win_size_x() / 2 - 14;y= win_size_y() / 2 + 7;
    break;
  case 1:
    x=win_size_x() / 2;y= win_size_y() / 2 + 7;
    break;
  case 2:
    x=win_size_x() / 2 + 14; y=win_size_y() / 2 + 7;
    break;
  }
  MenuCantidadPalabras_F(x,y);
  fflush(stdout);
}


inline void simulacion(){
  string palabras[3];
  string categoria;
  int categoriaAleatoria = rand() % 3;
  switch(categoriaAleatoria){
    case 0:categoria = "BMBANDS.txt";break;
    case 1:categoria = "colores.txt";break;
    case 2:categoria = "linuxdistro.txt";break;
  }
  leerPalabras(palabras,3,categoria);

  int tamanoriginal = sizeof(palabras) / sizeof(palabras[0]);
  string *nuevoArreglo = duplicarPalabras(palabras, tamanoriginal);
  int tamanoNuevoArreglo = tamanoriginal * 2;

  desordenarPalabras(nuevoArreglo, tamanoNuevoArreglo);

  int filas=0, columnas=0;
  filas = static_cast<int>(ceil(sqrt(tamanoNuevoArreglo)));
  columnas = static_cast<int>(ceil(tamanoNuevoArreglo / filas));
  carta **matriz = crearMatriz(nuevoArreglo, filas, columnas);
  
  juegoSimulado(matriz, filas, columnas); // con las variables creadas se inicia el juego

  for (int i = 0; i < filas; i++) {
    delete[] matriz[i];
  }
  delete[] matriz;
  delete[] nuevoArreglo;
}

inline void registrocolumnas(){
int seleccion2 = 0, MAX_PALABRAS = 0;
  bool salida = false;
  string archivo = "registros.dat";
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
  int filas,columnas;
  if(MAX_PALABRAS==3){
    filas = 3;
    columnas = 2;
  }
  if(MAX_PALABRAS==6){
    filas = 4;
    columnas = 3;
  }
  if(MAX_PALABRAS==8){
    filas = 4;
    columnas = 4; 
  }

  mostrarRegistrosPorDimension(archivo,filas,columnas);
}
inline void reportes(){
int seleccion = 0;
  bool salida = false;
  string categoria;
  string archivo = "registros.dat";

  while (salida == false) {
    reporteMenu(seleccion);
    switch (getch()) {
    case KEY_UP:
      if (seleccion > 0) {
        Play_Sound("pop.wav");
        seleccion--;
      }
      break;
    case KEY_DOWN:
      if (seleccion < 3) {
        Play_Sound("pop.wav");
        seleccion++;
      }
      break;
    case KEY_ENTER: //windows
    case '\n': //nix
      switch (seleccion) {
      case 0:
        categoria = menuPalabras();
        if(categoria.empty()){
          salida = true;
        }else{
        mostrarRegistrosPorcategoria(archivo,categoria);}

        break;
      case 1: 
        mostrarRegistros(archivo);
        break;
      case 2:
        registrocolumnas();
        break;
      case 3:
        salida = true; 
        break;
      }
      break;
    }//switch
  }
}

#endif //menus.h