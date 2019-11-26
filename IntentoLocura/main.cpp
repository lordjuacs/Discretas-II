#include "Algoritmos.h"
#include "InputOutput.h"
#include "Grafico.h"

int main() {

    titulo();
    Cubo cubo1 = pedirCubo(1);
    Cubo cubo2 = pedirCubo(2);
    Cubo cubo3 = pedirCubo(3);
    Cubo cubo4 = pedirCubo(4);
    auto start = chrono::steady_clock::now();

    vector<Cubo> opuestosCadaCubo = {cubo1, cubo2, cubo3, cubo4};
    bool todoValido = false;
    vector<vector<string>> Columnas = Bonito(opuestosCadaCubo, todoValido);

    if(todoValido) {
        auto end = chrono::steady_clock::now();
        cout << "Elapsed time in nanoseconds : "
             << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
             << " ns" << endl;
        imprimirColumnas(Columnas, opuestosCadaCubo);

    }
    else {
        auto end = chrono::steady_clock::now();
        cout << "Elapsed time in nanoseconds : "
             << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
             << " ns" << endl;
        imprimirSecundario(opuestosCadaCubo);

    }

    opuestosCadaCubo.clear();
    Columnas.clear();

    return 0;
}
