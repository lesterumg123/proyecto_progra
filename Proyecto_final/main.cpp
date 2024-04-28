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

using namespace std;

COORD coord = {0, 0};
const int MARGEN = 2;

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

void LimpiarPantalla() {
    system("cls");
}

int main() {
    cout << "PARA INICIAR DEBE SELECCIONAR EL CODIGO F12" << endl;

    while (true) {
        if (kbhit()) {
            char inicio = getch();
            if (GetAsyncKeyState(VK_F12) & 0x8000) {
                LimpiarPantalla();
                break;
            }
        }
    }

    int numero;
    float base;
    cout << "BIENVENIDOS SELECCIONA LA FIGURA A DIBUJAR" << endl;
    cout << "1.- TRIANGULO" << endl;
    cout << "2.- CUADRADO" << endl;
    cout << "3.- RECTANGULO" << endl;
    cout << "4.- CIRCULO" << endl;
    cin >> numero;
    cin.ignore();

    LimpiarPantalla();
    switch (numero) {
        case 1:
            cout << "Coloque el puntero donde iniciara el triángulo deseado y presione Enter" << endl;
            OcultarCursor();
            int x = 10 + MARGEN, y = 10 + MARGEN;
            gotoxy(x, y); printf(".");
            bool cursor_movido = false;

            while (true) {
                if (kbhit()) {
                    char tecla = getch();
                    gotoxy(x, y); printf(" ");

                    if (!cursor_movido) {
                        if (tecla == IZQUIERDA && x > MARGEN) x--;
                        if (tecla == DERECHA && x < 79 - MARGEN) x++;
                        if (tecla == ARRIBA && y > MARGEN) y--;
                        if (tecla == ABAJO && y < 24 - MARGEN) y++;

                        if (x <= MARGEN) x = 79 - MARGEN;
                        if (x >= 79 - MARGEN) x = MARGEN;
                        if (y <= MARGEN) y = 24 - MARGEN;
                        if (y >= 24 - MARGEN) y = MARGEN;

                        gotoxy(x, y); printf(".");

                        if (tecla != ENTER)
                            continue;

                        cursor_movido = true;
                    }

                    if (tecla == ENTER) {
                        cout << "Ingrese la base del triángulo: "<< endl;
                        cin >> base;
                        cin.ignore();
                        LimpiarPantalla();
                        gotoxy(x, y);
                        for (int i = 0; i < base; ++i) {
                            for (int j = 0; j <= base - i; ++j) {
                                cout << " ";
                            }
                            for (int j = 0; j <= i * 2; ++j) {
                                if (i == base - 1 || j == 0 || j == i * 2) {
                                    cout << "X";
                                } else {
                                    cout << " ";
                                }
                            }
                            cout << endl;
                            ++y;
                            if (y == 24 - MARGEN + 1) y = MARGEN;
                            gotoxy(x, y);
                        }
                        break;
                    }
                }

                Sleep(30);
            }
            break;
    }
    return 0;
}
