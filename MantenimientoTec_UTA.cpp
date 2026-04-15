#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include <limits>
#include <vector>

using namespace std;

// --- FUNCIONES DE VALIDACIÓN (V1) ---
int leerEntero(string mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor && valor >= 0) return valor;
        cout << "[!] Error: Ingrese un numero entero valido.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double leerDouble(string mensaje) {
    double valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor && valor >= 0) return valor;
        cout << "[!] Error: Ingrese un valor numerico positivo.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// --- CLASES (V2) ---
class Tecnico {
private:
    string codigo, nombre;
public:
    Tecnico(string c = "", string n = "") : codigo(c), nombre(n) {}
    string getNombre() { return nombre; }
};

class Mantenimiento {
private:
    string codigoOrden, codigoEquipo, tipo, tecnico, estado;
    int fechaReporte, fechaInicio, fechaCierre;
    double costoEstimado, costoRepuestos, costoManoObra;

public:
    Mantenimiento(string co, string ce, int fr, string t, string tec, double cEst) 
        : codigoOrden(co), codigoEquipo(ce), fechaReporte(fr), tipo(t), tecnico(tec), 
          costoEstimado(cEst), estado("Pendiente"), fechaInicio(0), fechaCierre(0), 
          costoRepuestos(0), costoManoObra(0) {}

    // LÓGICA DE DÍAS (V3 - Corregida)
    int calcularDias() {
        if (fechaCierre == 0 || fechaCierre < fechaInicio) return 0;
        return fechaCierre - fechaInicio; 
    }

    string getCodigo() { return codigoOrden; }
    double getCostoTotal() { return costoEstimado + costoRepuestos + costoManoObra; }

    void finalizarOrden(int fCierre, double rep, double mano) {
        fechaInicio = fechaReporte + 1;
        fechaCierre = fCierre;
        costoRepuestos = rep;
        costoManoObra = mano;
        estado = "Completado";
    }

    void mostrarFila() {
        cout << left << setw(10) << codigoOrden << setw(10) << codigoEquipo 
             << setw(12) << estado << setw(12) << tecnico 
             << "$" << fixed << setprecision(2) << setw(10) << getCostoTotal() 
             << " Dias: " << calcularDias() << endl;
    }
};

// --- SISTEMA PRINCIPAL (V4) ---
class SistemaMantenimiento {
private:
    Mantenimiento* ordenes[100];
    int cont;
    string vocabulario[10] = {"FALLA", "DIAGNOSTICO", "REPUESTOS", "TECNICO", "HERRAMIENTA", 
                               "MANTENIMIENTO", "REPARACION", "CIRCUITO", "VOLTAJE", "INSTITUCIONAL"};

    // RECURSIVIDAD PARA EL JUEGO (V4)
    bool buscarLetraRecursiva(string palabra, char letra, int index) {
        if (index >= (int)palabra.length()) return false;
        if (palabra[index] == letra) return true;
        return buscarLetraRecursiva(palabra, letra, index + 1);
    }

public:
    SistemaMantenimiento() : cont(0) {}

    void registrar() {
        if (cont >= 100) { cout << "Limite alcanzado.\n"; return; }
        string co, ce, t, tec;
        cout << "ID Orden: "; cin >> co;
        cout << "ID Equipo: "; cin >> ce;
        int fr = leerEntero("Fecha Reporte (AAAAMMDD): ");
        cout << "Tipo (P-Preventivo/C-Correctivo): "; cin >> t;
        cout << "ID Tecnico: "; cin >> tec;
        double cost = leerDouble("Costo Estimado: ");
        ordenes[cont++] = new Mantenimiento(co, ce, fr, t, tec, cost);
    }

    void completarOrden() {
        string id;
        cout << "Ingrese ID de Orden a completar: "; cin >> id;
        for (int i = 0; i < cont; i++) {
            if (ordenes[i]->getCodigo() == id) {
                int fc = leerEntero("Fecha Cierre (AAAAMMDD): ");
                double cr = leerDouble("Costo Repuestos: ");
                double cm = leerDouble("Costo Mano de Obra: ");
                ordenes[i]->finalizarOrden(fc, cr, cm);
                cout << "Orden actualizada.\n";
                return;
            }
        }
        cout << "Orden no encontrada.\n";
    }

    // ORDENAMIENTO BURBUJA (V4)
    void ordenarPorCosto() {
        for (int i = 0; i < cont - 1; i++) {
            for (int j = 0; j < cont - i - 1; j++) {
                if (ordenes[j]->getCostoTotal() < ordenes[j+1]->getCostoTotal()) {
                    Mantenimiento* temp = ordenes[j];
                    ordenes[j] = ordenes[j+1];
                    ordenes[j+1] = temp;
                }
            }
        }
        cout << "[!] Reporte ordenado por Costo Total (Descendente).\n";
    }

    void mostrarReporte() {
        cout << "\n" << string(70, '-') << "\n";
        cout << left << setw(10) << "ORDEN" << setw(10) << "EQUIPO" 
             << setw(12) << "ESTADO" << setw(12) << "TECNICO" << setw(11) << "COSTO" << "TIEMPO\n";
        for (int i = 0; i < cont; i++) ordenes[i]->mostrarFila();
        cout << string(70, '-') << "\n";
    }

    void jugarAhorcado() {
        string palabra = vocabulario[rand() % 10];
        string oculta(palabra.length(), '_');
        int intentos = 6;
        char l;

        cout << "\n--- JUEGO DE AHORCADO TECNICO ---\n";
        while (intentos > 0 && oculta != palabra) {
            cout << "\nPalabra: " << oculta << " | Intentos: " << intentos << "\nLetra: ";
            cin >> l; l = toupper(l);

            if (buscarLetraRecursiva(palabra, l, 0)) {
                for (int i = 0; i < (int)palabra.length(); i++) 
                    if (palabra[i] == l) oculta[i] = l;
            } else {
                intentos--;
                cout << "¡Incorrecto!\n";
            }
        }
        if (oculta == palabra) cout << "\n¡GANASTE! La palabra es: " << palabra << endl;
        else cout << "\nPERDISTE. La palabra era: " << palabra << endl;
    }

    void menu() {
        int op;
        do {
            cout << "\n--- SISTEMA MANTENIMIENTO UTA (FINAL) ---\n";
            cout << "1. Registrar Orden\n2. Completar Orden\n3. Reporte Ordenado\n4. Jugar Ahorcado\n0. Salir\nOpcion: ";
            if (!(cin >> op)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
            switch(op) {
                case 1: registrar(); break;
                case 2: completarOrden(); break;
                case 3: ordenarPorCosto(); mostrarReporte(); break;
                case 4: jugarAhorcado(); break;
            }
        } while (op != 0);
    }
};

int main() {
    srand(time(NULL));
    SistemaMantenimiento sistema;
    sistema.menu();
    return 0;
}