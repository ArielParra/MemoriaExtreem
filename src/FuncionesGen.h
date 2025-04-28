/* Ariel Emilio Parra Martinez ID:280862*/
/* Miguel Angel Batres Luna ID:350553*/
#ifndef FuncionesGen
#define FuncionesGen

/*librerias c++*/
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>


/*librerias c*/
#include <cstdlib> //system(),rand()
#include <ctime>//time_t,tm
#include <unistd.h>//usleep(),sleep()


/*Definiciones*/
//using namespace std; //mala practica
using std::cout;using std::cin;using std::cerr;//using std::endl;//<iostream>
using std::string; using std::to_string;//<string>
using std::ifstream;using std::ofstream;using std::fstream;using std::ios;//<fstream>
using std::fixed;using std::setprecision;//<iomanip>


/*constantes ansi*/
#define CLR_RST "\x1b[0m"
#define ROJO "\x1b[31m"
#define VERDE "\x1b[32m"
#define AMARILLO "\x1b[33m"
#define AZUL "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN "\x1b[36m"
#define HIDE_CRSR "\033[?25l"
#define SHOW_CRSR "\033[?25h"

/*constantes teclas*/
#if defined(_WIN32)
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_ENTER 13
#endif

enum TIPO{ALIAS,ALTASBAJAS};

//adapatacion de funciones conforme a los sistemas
#if defined(_WIN32) // si detecta el sistema operativo de windwos
  inline void clearScreen() { system("cls"); }
  #include <conio.h>  //getch()
  #include <windows.h>// ocupa -lwinmm como argumento para compilar
  inline void gotoxy(int x, int y) {COORD coordinate; coordinate.X = x; coordinate.Y = y; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coordinate);}
  inline int win_size_x(){ CONSOLE_SCREEN_BUFFER_INFO csbi; GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); return (csbi.srWindow.Right - csbi.srWindow.Left);}
  inline int win_size_y(){ CONSOLE_SCREEN_BUFFER_INFO csbi; GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); return (csbi.srWindow.Bottom - csbi.srWindow.Top);}
  inline void Play_Sound(string archivo){PlaySound(TEXT(archivo.c_str()), NULL, SND_ASYNC);}
  inline void Stop_Sound(){PlaySound(NULL, 0, 0);}

#elif defined(__unix__)|| defined(__APPLE__) || defined(__MACH__) //si son unices(linux,macos,bsds) -> ncurses
  #include <ncurses.h>//getch() // ocupa -lncurses como argumento para compilar
  #include <cstdio>//printf() //para gotoxy meramente
  inline void clearScreen() { system("clear"); }
  inline void gotoxy(int x, int y) { printf("%c[%d;%df", 0x1B, y, x); }
  inline int win_size_x(){return getmaxx(stdscr);}
  inline int win_size_y(){return getmaxy(stdscr);}

const string async_nohup=">/dev/null 2>&1 &";
/*reproducir sonidos*/
#if defined(__APPLE__) || defined(__MACH__)
  const string SOUND_APP="afplay";
  const string SOUND_APP_KILL=SOUND_APP;
  const string SOUND_APP_ARGS=" ";
#elif defined(__OpenBSD__)
  const string SOUND_APP="aucat";
  const string SOUND_APP_KILL=SOUND_APP;
  const string SOUND_APP_ARGS=" -i ";
#elif defined(__linux__)
inline string getSoundApp(){
    if(std::getenv("WSL_DISTRO_NAME")){//wsl
      return "ffplay";  // al no funcionar aplay o sox se usará ffplay de ffmpeg
    }else{//linux nativo
      return "aplay"; // aplay de alsa-utils
    }
}
inline string getSoundAppArgs() {
    if(std::getenv("WSL_DISTRO_NAME")){//wsl
      return " -nodisp ";
    }else{//linux nativo
      return " ";
    }
}
const string SOUND_APP=getSoundApp();
const string SOUND_APP_KILL=SOUND_APP;
const string SOUND_APP_ARGS=getSoundAppArgs();
#else //cualquier otro sistema operativo unix usara play de sox, y se debera correr el juego en una terminal con shell bash
  const string SOUND_APP="play";
  const string SOUND_APP_ARGS=" ";
  const string SOUND_APP_KILL="sox";
#endif
  inline void Play_Sound(string archivo){string comando= SOUND_APP + SOUND_APP_ARGS + archivo + async_nohup;system(comando.c_str());}
  inline void Stop_Sound(){const string PKILL="pkill "+ SOUND_APP_KILL;system(PKILL.c_str());}
#else // si no se detecta un sistema operatibo unix/macos/windowsNT
  #error "El sistema operativo, no es compatible"
#endif//fin de la deteccion sistemas

/*Prototipos/Funciones*/
inline void salir_programa(string error){
  fflush(stdout);
  clearScreen();
  #if !defined(_WIN32)
  echo();
  endwin();//End curses mode
  #endif
  cout<<SHOW_CRSR;
  cout<<error<<std::endl<<CLR_RST;
  exit(0);//sale del programa
}

inline void Pantalla_Completa(){
  if(win_size_x()<145 || win_size_y()<27){
    string error="ERROR: Debes poner la pantalla completa porfavor";
    cout<<AMARILLO;salir_programa(error);
  }
}

inline string Fecha_actual_letras(){
  time_t now=time(0);
  struct tm tm =*localtime(&now);
  const int fecha_ano=tm.tm_year +1900, fecha_dia=tm.tm_mday;
  string fecha_mes;
  switch(tm.tm_mon+1) {
    case 1:fecha_mes="enero";
    break;
    case 2:fecha_mes="febrero";
    break;
    case 3:fecha_mes="marzo";
    break;
    case 4:fecha_mes="abril";
    break;
    case 5:fecha_mes="mayo";
    break;
    case 6:fecha_mes="junio";
    break;
    case 7:fecha_mes="julio";
    break;
    case 8:fecha_mes="agosto";
    break;
    case 9:fecha_mes="septiembre";
    break;
    case 10:fecha_mes="octubre";
    break;
    case 11:fecha_mes="noviembre";
    break;
    case 12:fecha_mes="diciembre";
    break;
  }
  string fecha= to_string(fecha_dia) + " de " + fecha_mes + " de " + to_string(fecha_ano);
return fecha;
}
inline string Fecha_actual(){
  time_t now=time(0);
  struct tm *time =localtime(&now);
  char  fecha_actual[11];
  strftime(fecha_actual, sizeof(fecha_actual), "%d/%m/%Y", time);
return fecha_actual;
}

inline string Hora_actual(){
  time_t now=time(0);
  struct tm *time =localtime(&now);
  char  fecha_actual[6];
  strftime(fecha_actual, sizeof(fecha_actual), "%H:%M", time);
return fecha_actual;
}

inline void recuadro(){
#if defined(_WIN32)
gotoxy(0,0);cout<<"█";
#endif
int x=win_size_x(),i=0;
int y=win_size_y(),j=0;
  while(i<win_size_x()){
    gotoxy(x,y);cout<<"█";
    gotoxy(x--,0);cout<<"█";
    i++;
  }
  x=win_size_x();
  while(j<win_size_y()){
    gotoxy(x,y);cout<<"█";
    gotoxy(0,y--);cout<<"█";
    j++;
  }
cout<<CLR_RST;
fflush(stdout);
}

inline string validacion(int x,int y,int TIPO){
  string entrada;
  const int ox=x,oy=y;//origin x/y
  int caracter=0;
  bool validado=false,doce=false,cuatro=false,caracteres=false;
  while(true){
    validado=false;doce=false,cuatro=false;caracteres=false;
    #if !defined(_WIN32)
    reset_shell_mode();
    #endif
    //cin.ignore();
    //fflush(stdin);
    getline(cin,entrada);
    #if !defined(_WIN32)
    reset_prog_mode();
    #endif
    if(entrada.length()<4 && TIPO==ALIAS){
      cuatro=true;
      validado=false;
    }else
    if(entrada.length()>12){
      doce=true;
      validado=false;
    }else
    if(entrada.length()<1){
      validado=false;
    }else{
      validado=true;
    }


    if(validado){
      for(string::size_type  i=0;i<entrada.length();i++){//el compilador decia que usar int podria dar error
        if(entrada[i]==' '){//espacio
          validado=false;
          break;//deja de buscar porque no es valido
        }else{validado=true;}
      }//for espacio
    }//para que solo entre si no paso los casos anteriores

    if(TIPO==ALIAS && validado){
      for(string::size_type  i=0;i<entrada.length();i++){
        if ((entrada[i] >= 48 && entrada[i] <= 57) || // Digitos del 0 al 9
            (entrada[i] >= 65 && entrada[i] <= 90) || // Letras mayusculas del A al Z
            (entrada[i] == 95)                     || // guion bajo _
            (entrada[i] >= 97 && entrada[i] <= 122)){ // Letras minusculas del a al z
          validado=true;
        }else{
          caracter=i;
          caracteres=true;
          validado=false;
          break;//deja de buscar porque no es valido
        }
      }//for
    }//if

    if(validado){
      break;
    }else{
      Stop_Sound();
      Play_Sound("error.wav");
      fflush(stdout);
      clearScreen();
      x=ox;y=oy-1;//para que no se baje cada vez
      cout<<ROJO;recuadro();
      gotoxy(x,y++);
      cout<<ROJO;
        if(doce){
          cerr<<"ERROR: Contiene mas de 12 caracteres ";
        }
        if(cuatro){
          cerr<<"ERROR: Contiene menos de 4 caracteres ";
        }
        if(caracteres){
          cerr<<"ERROR: Contiene caracteres invalidos como '"<<entrada[caracter]<<"'";
        }
        if(entrada.length()<1 && TIPO==ALTASBAJAS){
          cerr<<"ERROR: La entrada esta vacia";
        }
      }
      gotoxy(x,y++);
      cout<<CLR_RST<<"intente de nuevo: ";
  }//while
  return entrada;
}//validacion

inline void logouaa(){
const int altura_grafico=16,ancho_grafico=43;
int x=(win_size_x()/4)-(ancho_grafico/2),y=(win_size_y()/2)-(altura_grafico/2);
gotoxy(x, y);
cout<<AZUL<<"█▒  "<< CYAN<<"██████       "<<CYAN<<"██████ "<<AZUL<<"▒▒█████▒▒▒        "; gotoxy(x, y++);
cout<<AZUL<<"███  "<<CYAN<<"███████   "<<CYAN<<"███████ "<<AZUL<<"▒█████████████     "; gotoxy(x, y++);
cout<<AZUL<<"███▒ "<<CYAN<<"███████                      "<<AZUL<<"█████   "; gotoxy(x, y++);
cout<<AZUL<<"███▒ "<<CYAN<<"███████               "<<CYAN<<"███████  "<<AZUL<<"▒███▒ "; gotoxy(x, y++);
cout<<AZUL<<"███▒ "<<CYAN<<"███████        "<<AMARILLO<<"██      "<<CYAN<<"████████ "<<AZUL<<"▒███▒"; gotoxy(x, y++);
cout<<AZUL<<"███▒ "<<CYAN<<"███████       "<<AMARILLO<<"████ "<<ROJO<<"█    "<<CYAN<<"████████ "<<AZUL<<"▒███"; gotoxy(x, y++);
cout<<AZUL<<"███▒ "<<CYAN<<"███████      "<<AMARILLO<<"████ "<<ROJO<<"███    "<<CYAN<<"███████ "<<AZUL<<"▒███"; gotoxy(x, y++);
cout<<AZUL<<"███▒ "<<CYAN<<"███████     "<<AMARILLO<<"████ "<<ROJO<<"█████   "<<CYAN<<"███████ "<<AZUL<<"▒███"; gotoxy(x, y++);
cout<<AZUL<<"███▒ "<<CYAN<<"███████    "<<AMARILLO<<"████ "<<ROJO<<"██████   "<<CYAN<<"███████ "<<AZUL<<"▒███"; gotoxy(x, y++);
cout<<AZUL<<"███▒ "<<CYAN<<"███████    "<<AMARILLO<<"███ "<<ROJO<<"██████    "<<CYAN<<"███████ "<<AZUL<<"▒███"; gotoxy(x, y++);
cout<<AZUL<<"███▒ "<<CYAN<<"███████    "<<AMARILLO<<"██ "<<ROJO<<"█████      "<<CYAN<<"███████ "<<AZUL<<"▒███"; gotoxy(x, y++);
cout<<AZUL<<"████ "<<CYAN<<"████████      "<<ROJO<<"████       "<<CYAN<<"███████ "<<AZUL<<"▒███"; gotoxy(x, y++);
cout<<AZUL<<" ███▒ "<<CYAN<<"████████      "<<ROJO<<"██        "<<CYAN<<"███████ "<<AZUL<<"▒███"; gotoxy(x, y++);
cout<<AZUL<<" ▒████  "<<CYAN<<"███████               ███████ "<<AZUL<<"▒███"; gotoxy(x, y++);
cout<<AZUL<<"   █████                      "<<CYAN<<"███████ "<<AZUL<<"▒███"; gotoxy(x, y++);
cout<<AZUL<<"     ▒████████████▒ "<<CYAN<<"████████   ███████ "<<AZUL<<"███"<<CLR_RST;
fflush(stdout);

}

inline void flecha_derecha() {
  const int altura_grafico=9, ancho_grafico=14;
  int x=win_size_x()-ancho_grafico,y=win_size_y()-altura_grafico;
  gotoxy(x, y++);cout<<AZUL;
  cout << "   ▒▒▒▒▒▒▒▒    "; gotoxy(x, y++);
  cout << "  ▒        ▒   ";  gotoxy(x, y++);
  cout << " ▒      ▒   ▒  ";  gotoxy(x, y++);
  cout << "▒        ▒   ▒ ";  gotoxy(x, y++);
  cout << "▒  ▒▒▒▒▒▒▒▒  ▒ ";  gotoxy(x, y++);
  cout << "▒        ▒   ▒ ";  gotoxy(x, y++);
  cout << " ▒      ▒   ▒  ";  gotoxy(x, y++);
  cout << "  ▒        ▒   ";  gotoxy(x, y++);
  cout << "   ▒▒▒▒▒▒▒▒    "<<CLR_RST;
  fflush(stdout);

}

inline void flecha_izquierda() {
  const int altura_grafico=9;
  int x=1,y=win_size_y()-altura_grafico;
  gotoxy(x, y++);cout<<AZUL;
  cout << "   ▒▒▒▒▒▒▒▒    "; gotoxy(x, y++);
  cout << "  ▒        ▒   ";  gotoxy(x, y++);
  cout << " ▒   ▒      ▒  ";  gotoxy(x, y++);
  cout << "▒   ▒        ▒ ";  gotoxy(x, y++);
  cout << "▒  ▒▒▒▒▒▒▒▒  ▒ ";  gotoxy(x, y++);
  cout << "▒   ▒        ▒ ";  gotoxy(x, y++);
  cout << " ▒   ▒      ▒  ";  gotoxy(x, y++);
  cout << "  ▒        ▒   ";  gotoxy(x, y++);
  cout << "   ▒▒▒▒▒▒▒▒    "<<CLR_RST;
  fflush(stdout);

}

inline void logojuego2(){
const int altura_grafico=7,ancho_grafico=119;
int x=(win_size_x()/2)-(ancho_grafico/2),y=(win_size_y()/2)-altura_grafico;
gotoxy(x,y++);cout<<AZUL;
cout<<"                                                                                                                ";gotoxy(x,y++);
cout<<"███╗░░░███╗███████╗███╗░░░███╗░█████╗░██████╗░██╗░█████╗   ███████╗██╗░░██╗████████╗██████╗░███████╗███████╗███╗░░░███╗";gotoxy(x,y++);
cout<<"████╗░████║██╔════╝████╗░████║██╔══██╗██╔══██╗██║██╔══██╗  ██╔════╝╚██╗██╔╝╚══██╔══╝██╔══██╗██╔════╝██╔════╝████╗░████║";gotoxy(x,y++);
cout<<"██╔████╔██║█████╗░░██╔████╔██║██║░░██║██████╔╝██║███████║  █████╗░░░╚███╔╝░░░░██║░░░██████╔╝█████╗░░█████╗░░██╔████╔██║";gotoxy(x,y++);
cout<<"██║╚██╔╝██║██╔══╝░░██║╚██╔╝██║██║░░██║██╔══██╗██║██╔══██║  ██╔══╝░░░██╔██╗░░░░██║░░░██╔══██╗██╔══╝░░██╔══╝░░██║╚██╔╝██║";gotoxy(x,y++);
cout<<"██║░╚═╝░██║███████╗██║░╚═╝░██║╚█████╔╝██║░░██║██║██║░░██║  ███████╗██╔╝╚██╗░░░██║░░░██║░░██║███████╗███████╗██║░╚═╝░██║";gotoxy(x,y++);
cout<<"╚═╝░░░░░╚═╝╚══════╝╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝╚═╝╚═╝░░╚═╝  ╚══════╝╚═╝░░╚═╝░░░╚═╝░░░╚═╝░░╚═╝╚══════╝╚══════╝╚═╝░░░░░╚═╝";gotoxy(x+5,y+=2);
  cout << "█▄ █ █ █ █▄ █ █▀▀ ▄▀█   █ █ ▄▀█ █▄▄ █ ▄▀█   █▀ █ █▀▄ █▀█   ▀█▀ ▄▀█ █▄ █   █▀▀ ▀▄▀ ▀█▀ █▀█ █▀▀ █▀▀ █▀▄▀█";gotoxy(x+5,y+=1);
  cout << "█ ▀█ █▄█ █ ▀█ █▄▄ █▀█   █▀█ █▀█ █▄█ █ █▀█   ▄█ █ █▄▀ █▄█    █  █▀█ █ ▀█   ██▄ █ █  █  █▀▄ ██▄ ██▄ █ ▀ █ ▄ ▄ ▄";gotoxy(x+5,y++);
fflush(stdout);
}

inline void MenuCantidadPalabras_G(int seleccion){
    int ancho_objeto = 9;
  int espacio_entre_objetos = 5;
  int x = win_size_x() / 2 - ancho_objeto - espacio_entre_objetos -3;
  int y = win_size_y()/2 -3;
  if(seleccion==0){cout<<ROJO;}else{cout<<AZUL;}
  gotoxy(x, y++);
  cout << " ███████ ";gotoxy(x, y++);
  cout << "██     ██";gotoxy(x, y++);
  cout << "       ██";gotoxy(x, y++);
  cout << "  ██████ ";gotoxy(x, y++);
  cout << "       ██";gotoxy(x, y++);
  cout << "██     ██";gotoxy(x, y++);
  cout << " ███████ "<<CLR_RST;
  y = win_size_y()/2 -3;
  x =win_size_x()/2-3;
  if(seleccion==1){cout<<ROJO;}else{cout<<AZUL;}
  gotoxy(x, y++);
  cout << " ███████ ";gotoxy(x, y++);
  cout << "██       ";gotoxy(x, y++);
  cout << "██       ";gotoxy(x, y++);
  cout << " ███████ ";gotoxy(x, y++);
  cout << "██     ██";gotoxy(x, y++);
  cout << "██     ██";gotoxy(x, y++);
  cout << " ███████ "<<CLR_RST;
  y = win_size_y()/2 -3;
  x = win_size_x()/2 + ancho_objeto + espacio_entre_objetos -3;
  if(seleccion==2){cout<<ROJO;}else{cout<<AZUL;}
  gotoxy(x, y++);
  cout << " ███████ ";gotoxy(x, y++);
  cout << "██     ██";gotoxy(x, y++);
  cout << "██     ██";gotoxy(x, y++);
  cout << " ███████ ";gotoxy(x, y++);
  cout << "██     ██";gotoxy(x, y++);
  cout << "██     ██";gotoxy(x, y++);
  cout << " ███████ "<<CLR_RST;
}
inline void MenuCantidadPalabras_F(int x, int y){
  gotoxy(x,y++);cout<<ROJO;
  cout<<"  █  ";gotoxy(x,y++);
  cout<<" ███ ";gotoxy(x,y++);
  cout<<"█ █ █";gotoxy(x,y++);
  cout<<"  █  ";gotoxy(x,y++);
  cout<<"  █  ";gotoxy(x,y++);
  cout<<"  █  " <<CLR_RST;
}

inline void PresioneTecla(){
    gotoxy(win_size_x()/2-16,win_size_y()-2);
    cout<<"Precione cualquier tecla para volver";
    fflush(stdout);
    usleep(50000);
    getch();
}


inline void bajas(string nombreArchivo,string elemento) {
  const int ancho_grafico=30;
  int x=(win_size_x()/2-(ancho_grafico/2)-(elemento.size()));
  int y = (win_size_y() / 2 -1);

   ifstream inputFile(nombreArchivo);
    if (!inputFile.is_open()) {
        clearScreen();
        cout<<ROJO;recuadro();
        Play_Sound("error.wav");
        gotoxy(x,y);
        cerr << "Error: no se pudo abrir el abrir el archivo '"<<nombreArchivo<<"'";
        return;
    }

    string palabra;
    bool elementoEncontrado = false;

    ofstream tempFile("temp.txt");
    if (!tempFile.is_open()) {
        clearScreen();
        cout<<ROJO;recuadro();
        Play_Sound("error.wav");
        gotoxy(x,y);
        cerr << ROJO<<"Error: No se pudo abrir el archivo temporal 'temp.txt'"<<CLR_RST;
        inputFile.close();
        return;
    }

    while (inputFile >> palabra) {
        if (palabra != elemento) {
            tempFile << palabra << " ";
        } else {
            elementoEncontrado = true;
        }
    }

    inputFile.close();
    tempFile.close();

    if (elementoEncontrado) {
        if (remove(nombreArchivo.c_str()) == 0) {
            if (rename("temp.txt", nombreArchivo.c_str()) != 0) {
                clearScreen();
                cout<<ROJO;recuadro();
                Play_Sound("error.wav");
                gotoxy(x,y);
                cerr << ROJO<<"Error: no se pudo renombrar el archivo temporal 'temp.txt'"<<CLR_RST;
            }
            clearScreen();
            cout<<VERDE;recuadro();
            Play_Sound("exito.wav");
            gotoxy(x,y);
            cout << VERDE<<"Elemento '"+ elemento +"' eliminado correctamente"<<CLR_RST;
        } else {
            clearScreen();
            cout<<ROJO;recuadro();
            Play_Sound("error.wav");
            gotoxy(x,y);
            cerr << ROJO<<"Error: no se pudo eliminar el archivo original '"<<nombreArchivo<<"'"<<CLR_RST;
        }
    } else {
        clearScreen();
        cout<<AMARILLO;recuadro();
        Play_Sound("error.wav");
        gotoxy(x,y);
        cerr << AMARILLO<< "ERROR: Elemento '"+ elemento +"' no existe"<<CLR_RST;
        remove("temp.txt");
    }
    fflush(stdout);
    PresioneTecla();
}


inline void altas(string nombreArchivo,string elemento) {
    // Implementa la lógica para añadir algo a un archivo
    bool existe = false;
    const int ancho_grafico=30;
    int x=(win_size_x()/2-(ancho_grafico/2)-(elemento.size()));
    int y=(win_size_y()/2 -1);

    ofstream archivo(nombreArchivo, std::ios::app); // Abrir el archivo en modo de agregar al final
    if (!archivo.is_open()){
        clearScreen();
        cout<<ROJO;recuadro();
        Play_Sound("error.wav");
        gotoxy(x, y++);
        cerr <<ROJO<< "ERROR: No se pudo abrir el archivo '"<<nombreArchivo<<"'"<<CLR_RST;
        return;
    }

    ifstream archivoIn(nombreArchivo);
    if (!archivoIn.is_open()) {
        clearScreen();
        cout<<ROJO;recuadro();
        Play_Sound("error.wav");
        gotoxy(x, y++);
        cerr <<ROJO<< "ERROR: No se pudo abrir el archivo '"<<nombreArchivo<<"'"<<CLR_RST;
        return;
    }

    string linea;
    while (archivoIn>>linea) {
        if (linea == elemento) {
          existe = true;
          break;
        }
    }
    if(existe){
          clearScreen();
          cout<<AMARILLO;recuadro();
          Play_Sound("error.wav");
          gotoxy(x,y++);
          cerr << AMARILLO <<"ERROR: Elemento '"<<elemento<<"' ya existe"<<CLR_RST;
    }else{
          archivo<<" "<<elemento; // Agregar el elemento al archivo
          clearScreen();
          cout<<VERDE;recuadro();
          Play_Sound("exito.wav");
          gotoxy(x,y++);
          cout << VERDE<<"Elemento '"<< elemento <<"' añadido correctamente"<<CLR_RST;
    }
    archivo.close();
    archivoIn.close();
    fflush(stdout);
    PresioneTecla();
}

inline void mostrar(string nombreArchivo) {
    // Implementa la lógica para mostrar el contenido de un archivo
    int ancho_grafico=31,k=0;
    int x=(win_size_x()/2-(ancho_grafico/2)-3);
    int y=(win_size_y()/2-10);
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        clearScreen();
        cout<<ROJO;recuadro();
        Play_Sound("error.wav");
        gotoxy(x,y++);
        cerr <<ROJO<< "ERROR: No se pudo abrir el archivo'"<<nombreArchivo<<"'"<<CLR_RST;
        return;
    }

    string linea;
    while (archivo >> linea ) {
        if(k==15){y=win_size_y()/2-10;x=win_size_x()/2+10;}
        gotoxy(x,y++);
        cout << linea;
        k++;
    }

    archivo.close();
    fflush(stdout);
    PresioneTecla();
}
inline void reporteMenu(int seleccion){
 clearScreen();
  const char *colores[4] = {CYAN, MAGENTA, AZUL, AMARILLO};
  const char *opciones[4]  = {"█▀█ █▀█ █▀█   █▀▀ ▄▀█ ▀█▀ █▀▀ █▀▀ █▀█ █▀█ █ ▄▀█","█▀█ █▀█ █▀█   █▄ █ █▀█ █▀▄▀█ █▄▄ █▀█ █▀▀","█▀█ █▀█ █▀█   █▀▄ █ █▀▄▀█ █▀▀ █▄░█ █▀ █ █▀█ █▄░█","█▀ ▄▀█ █   █ █▀█"};
  const char *opciones2[4] = {"█▀▀ █▄█ █▀▄   █▄▄ █▀█  █  ██▄ █▄█ █▄█ █▀▄ █ █▀█","█▀▀ █▄█ █▀▄   █ ▀█ █▄█ █ ▀ █ █▄█ █▀▄ ██▄","█▀▀ █▄█ █▀▄   █▄▀ █ █░▀░█ ██▄ █░▀█ ▄█ █ █▄█ █░▀█","▄█ █▀█ █▄▄ █ █▀▄"};
  const int altura_grafico = 10, ancho_grafico = 58;
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

inline void ganaste(string alias,float elapsed_time, int pares){
    int x = win_size_x()/2-(35/2);int y = win_size_y()/2-1;
    clearScreen(); 
    const char *opcion1[7] = {"█▀▀ ","▄▀█ ","█▄ █ ","▄▀█ ","█▀ ","▀█▀ ","█▀▀"};
    const char *opcion2[7] = {"█▄█ ","█▀█ ","█ ▀█ ","█▀█ ","▄█ "," █  ","██▄"};
    Play_Sound("win.wav");
    const char *colores[7]= {AZUL,ROJO,MAGENTA,AMARILLO,CYAN,ROJO,VERDE};
    for(int i=0;i<7;i++){
        cout << colores[i];
      recuadro();
      gotoxy(x,y);
      cout << colores[i]<<opcion1[i];
      gotoxy(x,y+1);
      cout << colores[i]<< opcion2[i];
      x+= 6;
       gotoxy(win_size_x() / 2 - ((38+alias.length())/2), y+3);
      cout << "Felicidades " << alias << " terminaste el juego en " << fixed << setprecision(0) << elapsed_time << " Segundos";
      gotoxy(win_size_x()/2-3,y+4);
      cout << "Con "<<pares<<" Pares";
      fflush(stdout);
      usleep(800000);
    }
}


#endif //FuncionesGen.h
