//
// Created by J on 25-Nov-19.
//

#ifndef INTENTOLOCURA_INPUTOUTPUT_H
#define INTENTOLOCURA_INPUTOUTPUT_H

#include "Clases.h"
#include "Tipos.h"
void titulo(){
    cout << "LOCURA INSTANTANEA" << endl;
    cout << "Siga las instrucciones para ingresar los datos:" << endl << endl;
    cout << "Ingresar las siguientes letras para referirse al color deseado:" << endl;
    cout << "Azul - A" << endl << "Rojo - R" << endl << "Verde - V" << endl <<"Amarillo - M" << endl << endl;
    cout << "Por favor ingresar una sola letra por espacio." << endl;
}

bool validarLetra(char escogida){
    return escogida == 'A' || escogida == 'R' || escogida == 'V' || escogida == 'M' || escogida == 'a' || escogida == 'r' || escogida == 'v' || escogida == 'm';
}

string colour(const char &col){
    if(col == 'A' || col == 'a')
        return "azul";
    else if(col == 'R' || col == 'r')
        return "rojo";
    else if(col == 'V' || col == 'v')
        return "verde";
    else
        return "negro";
}

Cubo pedirCubo(int numero_cubo){
    cout << "Ingrese los colores de las caras del cubo "  << numero_cubo << ":" << endl;
    char matriz[4][3] = {{char(254), '1', char(254)}, {'5', '3', '6'}, {char(254), '2', char(254)}, {char(254), '4', char(254)}};
    for(auto & i : matriz){
        for(const auto & j : i){
            cout << '|' << j  <<'|'<< "\t";
        }
        cout << endl;
    }
    vector<string>caras;
    char co;
    cout << endl;
    for(int i = 0; i < 6; i++){
        do {
            cout << i + 1 << ".--->";
            cin >> co;

        }while(!validarLetra(co));
        string col = colour(co);
        caras.emplace_back(col);
    }
    Cubo cubo(caras);
    return cubo;

}


#endif //INTENTOLOCURA_INPUTOUTPUT_H
