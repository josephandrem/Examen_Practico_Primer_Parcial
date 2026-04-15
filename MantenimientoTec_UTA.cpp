#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <limits>

using namespace std;

// --- FUNCIONES DE VALIDACIÓN ---

// Valida que la entrada sea un número entero positivo
int leerEntero(string mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor && valor >= 0) {
            return valor;
        }
        cout << "[!] Error: Ingrese un numero entero valido y positivo." << endl;
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    }
}

// Valida que la entrada sea un número decimal positivo
double leerDouble(string mensaje) {
    double valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor && valor >= 0.0) {
            return valor;
        }
        cout << "[!] Error: Ingrese un valor numerico positivo." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

int main() {
    srand(time(NULL));

    cout << "==========================================" << endl;
    cout << "   SISTEMA DE MANTENIMIENTO TECNICO UTA   " << endl;
    cout << "          ESTRUCTURA INICIAL              " << endl;
    cout << "==========================================" << endl;
    
    cout << "\n[Info] Estructura base cargada correctamente." << endl;
    cout << "[Info] Validaciones de usuario listas." << endl;

    return 0;
}