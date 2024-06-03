#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
#include <cmath>

#define IZQUIERDA 75
#define DERECHA 77
#define ARRIBA 72
#define ABAJO 80
#define ENTER 13
#define F12 123

using namespace std;

COORD coord = {0, 0};
const int MARGEN = 2;
const int ANCHO = 100;
const int ALTO = 24;
const int MENSAJE_X = 0;
const int MENSAJE_Y = ALTO + 2; 

void gotoxy(int x, int y) {
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void OcultarCursor() {
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 50;
    cci.bVisible = false;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void MostrarCursor() {
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize = 50;
    cci.bVisible = true;
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void LimpiarAreaMensajes() {
    gotoxy(MENSAJE_X, MENSAJE_Y);
    for (int i = 0; i < 5; ++i) { 
        cout << string(ANCHO, ' ');
    }
    gotoxy(MENSAJE_X, MENSAJE_Y);
}

void DibujaCaracter(int x, int y, char c) {
    if (x < MARGEN) {
        x = ANCHO - MARGEN + (x - MARGEN);
    } else if (x >= ANCHO - MARGEN) {
        x = MARGEN + (x - (ANCHO - MARGEN));
    }

    if (y < MARGEN) {
        y = ALTO - MARGEN + (y - MARGEN);
    } else if (y >= ALTO - MARGEN) {
        y = MARGEN + (y - (ALTO - MARGEN));
    }

    gotoxy(x, y);
    cout << c;
}

void DibujaTriangulo(int x, int y, int base) {
    int altura = (base + 1) / 2;
    for (int i = 0; i < altura; ++i) {
        for (int j = 0; j <= 2 * i; ++j) {
            if (i == altura - 1 || j == 0 || j == 2 * i) {
                DibujaCaracter(x - i + j, y + i, 'X');
            }
        }
        if (y + i >= ALTO - MARGEN) {
            break;
        }
    }
}

void DibujaCuadrado(int x, int y, int lado) {
    for (int i = 0; i < lado; ++i) {
        for (int j = 0; j < lado; ++j) {
            if (i == 0 || i == lado - 1 || j == 0 || j == lado - 1) {
                DibujaCaracter(x + j, y + i, 'X');
            }
        }
    }
}

void DibujaRectangulo(int x, int y, int ancho, int alto) {
    for (int i = 0; i < alto; ++i) {
        for (int j = 0; j < ancho; ++j) {
            if (i == 0 || i == alto - 1 || j == 0 || j == ancho - 1) {
                DibujaCaracter(x + j, y + i, 'X');
            }
        }
    }
}

void DibujaCirculo(int x, int y, int radio) {
    for (int i = -radio; i <= radio; ++i) {
        for (int j = -radio; j <= radio; ++j) {
            if (abs(i * i + j * j - radio * radio) <= radio) {
                DibujaCaracter(x + j, y + i, 'X');
            }
        }
    }
}

void DibujaLinea(int x, int y, int longitud, int orientacion) {
    switch (orientacion) {
        case 1: 
            for (int i = 0; i < longitud; ++i) {
                DibujaCaracter(x, y - i, 'X');
            }
            break;
        case 2: 
            for (int i = 0; i < longitud; ++i) {
                DibujaCaracter(x, y + i, 'X');
            }
            break;
        case 3: 
            for (int i = 0; i < longitud; ++i) {
                DibujaCaracter(x + i, y, 'X');
            }
            break;
        case 4: 
            for (int i = 0; i < longitud; ++i) {
                DibujaCaracter(x - i, y, 'X');
            }
            break;
        case 5: 
            for (int i = 0; i < longitud; ++i) {
                DibujaCaracter(x + i, y - i, 'X');
            }
            break;
        case 6: 
            for (int i = 0; i < longitud; ++i) {
                DibujaCaracter(x + i, y + i, 'X');
            }
            break;
        case 7: 
            for (int i = 0; i < longitud; ++i) {
                DibujaCaracter(x - i, y - i, 'X');
            }
            break;
        case 8: 
            for (int i = 0; i < longitud; ++i) {
                DibujaCaracter(x - i, y + i, 'X');
            }
            break;
    }
}

void DibujaRombo(int x, int y, int lado, int orientacion) {
    int altura = lado / 2;
    if (orientacion == 1) { 
        for (int i = 0; i <= altura; ++i) {
            DibujaCaracter(x - i, y + i, 'X');
            DibujaCaracter(x + i, y + i, 'X');
        }
        for (int i = altura - 1; i >= 0; --i) {
            DibujaCaracter(x - i, y + (lado - i - 1), 'X');
            DibujaCaracter(x + i, y + (lado - i - 1), 'X');
        }
    } else if (orientacion == 2) { 
        for (int i = altura; i >= 0; --i) {
            DibujaCaracter(x - i, y + (altura - i), 'X');
            DibujaCaracter(x + i, y + (altura - i), 'X');
        }
        for (int i = 1; i <= altura; ++i) {
            DibujaCaracter(x - i, y + (lado - i - 1), 'X');
            DibujaCaracter(x + i, y + (lado - i - 1), 'X');
        }
    }
}

void DibujaHexagono(int x, int y, int lado, int orientacion) {
    int altura = lado / 2;
    if (orientacion == 1) { 
        for (int i = 0; i < altura; ++i) {
            DibujaCaracter(x - i, y + i, 'X');
            DibujaCaracter(x + i, y + i, 'X');
        }
        for (int i = 0; i < lado; ++i) {
            DibujaCaracter(x - altura, y + altura + i, 'X');
            DibujaCaracter(x + altura, y + altura + i, 'X');
        }
        for (int i = altura - 1; i >= 0; --i) {
            DibujaCaracter(x - i, y + lado + altura - i, 'X');
            DibujaCaracter(x + i, y + lado + altura - i, 'X');
        }
    } else if (orientacion == 2) { 
        for (int i = 0; i < altura; ++i) {
            DibujaCaracter(x + i, y - i, 'X');
            DibujaCaracter(x + i, y + i, 'X');
        }
        for (int i = 0; i < lado; ++i) {
            DibujaCaracter(x + altura + i, y - altura, 'X');
            DibujaCaracter(x + altura + i, y + altura, 'X');
        }
        for (int i = altura - 1; i >= 0; --i) {
            DibujaCaracter(x + lado + altura + i, y - i, 'X');
            DibujaCaracter(x + lado + altura + i, y + i, 'X');
        }
    }
}

void MostrarMenu() {
    LimpiarAreaMensajes();
    gotoxy(MENSAJE_X, MENSAJE_Y);
    cout << "Menu de Figuras:" << endl;
    cout << "1. Triangulo" << endl;
    cout << "2. Cuadrado" << endl;
    cout << "3. Rectangulo" << endl;
    cout << "4. Circulo" << endl;
    cout << "5. Linea" << endl;
    cout << "6. Rombo" << endl;
    cout << "7. Hexagono" << endl;
}

void SeleccionarLugar(int &x, int &y) {
    OcultarCursor();
    gotoxy(x, y);
    cout << "*";
    bool continuar = true;
    while (continuar) {
        if (_kbhit()) {
            char tecla = _getch();
            gotoxy(x, y);
            cout << " ";
            switch (tecla) {
                case IZQUIERDA:
                    x = max(MARGEN, x - 1);
                    break;
                case DERECHA:
                    x = min(ANCHO - MARGEN, x + 1);
                    break;
                case ARRIBA:
                    y = max(MARGEN, y - 1);
                    break;
                case ABAJO:
                    y = min(ALTO - MARGEN, y + 1);
                    break;
                case ENTER:
                    continuar = false;
                    break;
            }
            gotoxy(x, y);
            cout << "*";
        }
    }
    MostrarCursor();
}

bool DetectarF12() {
    if (GetAsyncKeyState(F12) & 0x8000) {
        return true;
    }
    return false;
}

int main() {
    int opcion;
    int x = 10, y = 10;

    while (true) {
        LimpiarAreaMensajes();
        gotoxy(MENSAJE_X, MENSAJE_Y);
        cout << "Presiona F12 para iniciar" << endl;
        while (!DetectarF12()) {
            Sleep(100);
        }
        LimpiarAreaMensajes();
        MostrarMenu();
        SeleccionarLugar(x, y);
        LimpiarAreaMensajes();
        gotoxy(MENSAJE_X, MENSAJE_Y);
        cout << "SELECCIONA LA FIGURA A DIBUJAR: ";
        cin >> opcion;

        LimpiarAreaMensajes();

        switch (opcion) {
            case 1: {
                int base;
                gotoxy(MENSAJE_X, MENSAJE_Y);
                cout << "Ingrese la base del triangulo: ";
                cin >> base;
                DibujaTriangulo(x, y, base);
                break;
            }
            case 2: {
                int lado;
                gotoxy(MENSAJE_X, MENSAJE_Y);
                cout << "Ingrese el lado del cuadrado: ";
                cin >> lado;
                DibujaCuadrado(x, y, lado);
                break;
            }
            case 3: {
                int ancho, alto;
                gotoxy(MENSAJE_X, MENSAJE_Y);
                cout << "Ingrese el ancho del rectangulo: ";
                cin >> ancho;
                gotoxy(MENSAJE_X, MENSAJE_Y + 1);
                cout << "Ingrese el alto del rectangulo: ";
                cin >> alto;
                DibujaRectangulo(x, y, ancho, alto);
                break;
            }
            case 4: {
                int radio;
                gotoxy(MENSAJE_X, MENSAJE_Y);
                cout << "Ingrese el radio del circulo: ";
                cin >> radio;
                DibujaCirculo(x, y, radio);
                break;
            }
            case 5: {
                int longitud, orientacion;
                gotoxy(MENSAJE_X, MENSAJE_Y);
                cout << "Ingrese la longitud de la linea: ";
                cin >> longitud;
                gotoxy(MENSAJE_X, MENSAJE_Y + 1);
                cout << "Seleccione la orientacion (1. Arriba, 2. Abajo, 3. Derecha, 4. Izquierda, 5. Diagonal Derecha Arriba, 6. Diagonal Derecha Abajo, 7. Diagonal Izquierda Arriba, 8. Diagonal Izquierda Abajo): ";
                cin >> orientacion;
                DibujaLinea(x, y, longitud, orientacion);
                break;
            }
            case 6: {
                int lado, orientacion;
                gotoxy(MENSAJE_X, MENSAJE_Y);
                cout << "Ingrese el lado del rombo: ";
                cin >> lado;
                gotoxy(MENSAJE_X, MENSAJE_Y + 1);
                cout << "Seleccione la orientacion (1. Arriba, 2. Abajo): ";
                cin >> orientacion;
                DibujaRombo(x, y, lado, orientacion);
                break;
            }
            case 7: {
                int lado, orientacion;
                gotoxy(MENSAJE_X, MENSAJE_Y);
                cout << "Ingrese el lado del hexagono: ";
                cin >> lado;
                gotoxy(MENSAJE_X, MENSAJE_Y + 1);
                cout << "Seleccione la orientacion (1. Vertical, 2. Horizontal): ";
                cin >> orientacion;
                DibujaHexagono(x, y, lado, orientacion);
                break;
            }
            default:
                gotoxy(MENSAJE_X, MENSAJE_Y);
                cout << "Opcion no valida" << endl;
                break;
        }

        gotoxy(MENSAJE_X, MENSAJE_Y + 3);
        cout << "Presione cualquier tecla para volver al menu o F12 para dibujar otra figura..." << endl;
        if (_getch() == F12) {
            continue;
        } else {
            LimpiarAreaMensajes();
            MostrarMenu();
        }
    }

    return 0;
}
