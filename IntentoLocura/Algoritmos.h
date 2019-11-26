//
// Created by J on 24-Nov-19.
//

#ifndef INTENTOLOCURA_ALGORITMOS_H
#define INTENTOLOCURA_ALGORITMOS_H

#include "Clases.h"
#include "Tipos.h"
#include <chrono>



bool noEsta(const vector<string>&paquete, const string& yo){
    //si no esta devuelve true
    return !(find(paquete.begin(), paquete.end(), yo) != paquete.end());
}


bool validar(vector<Tupla>&preGrafo){
    int cA = 0, cR = 0, cV = 0, cN = 0;
    for (auto &elemento : preGrafo) {
        for (int w = 0; w < 2; w++) {
            string evaluando = elemento[w];
            if (evaluando == "azul")
                cA++;
            else if (evaluando == "rojo")
                cR++;
            else if (evaluando == "verde")
                cV++;
            else if (evaluando == "negro")
                cN++;
            else;

        }
    }
    return cA == 2 && cR == 2 && cV == 2 && cN == 2;
}

bool sigueVivo(vector <Tupla> &preGrafoenConstruccion){
    int cA = 0, cV = 0, cR = 0, cN = 0;
    for (auto &elemento : preGrafoenConstruccion) {
        for (int w = 0; w < 2; w++) {
            string evaluando = elemento[w];
            if (evaluando == "azul")
                cA++;
            else if (evaluando == "rojo")
                cR++;
            else if (evaluando == "verde")
                cV++;
            else if(evaluando == "negro")
                cN++;
            else
                ;

        }
    }
    return cA <= 2 && cV <= 2 && cR <= 2 && cN <= 2;
}

vector<Tupla> algoritmoInterno(vector<Cubo>opCadaCubo_menosPrueba, bool & segundoValido) {
    vector<Tupla> preGrafo;
    Tupla a_0(".", ".");
    Tupla a_1(".", ".");
    Tupla a_2(".", ".");
    Tupla a_3(".", ".");
    preGrafo.emplace_back(a_0);
    preGrafo.emplace_back(a_1);
    preGrafo.emplace_back(a_2);
    preGrafo.emplace_back(a_3);

    //grado de nodos

    for (int i = 0; i < 2; i++) {
        preGrafo[0] = opCadaCubo_menosPrueba[0][i];
        for (int j = 0; j < 2; j++) {
            preGrafo[1] = opCadaCubo_menosPrueba[1][j];
            if(sigueVivo(preGrafo)) {
                for (int k = 0; k < 2; k++) {
                    preGrafo[2] = opCadaCubo_menosPrueba[2][k];
                    if(sigueVivo(preGrafo)) {
                        for (int h = 0; h < 2; h++) {
                            preGrafo[3] = opCadaCubo_menosPrueba[3][h];
                            if(sigueVivo(preGrafo)) {
                                if (validar(preGrafo)) {//si el subgrafo 2 cumple con las condiciones,entonces acabar;
                                    segundoValido = true;
                                    return preGrafo;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vector<Tupla>vacio;
    Tupla no_se_pudo;
    vacio.emplace_back(no_se_pudo);
    segundoValido = false;
    return vacio;
}

vector<vector<Tupla>> algoritmoPrincipal(vector<Cubo> opCadaCubo, bool &todoValido){
    vector<Tupla> preGrafo;
    Tupla a_0("-", "-");
    Tupla a_1("-", "-");
    Tupla a_2("-", "-");
    Tupla a_3("-", "-");
    preGrafo.emplace_back(a_0);
    preGrafo.emplace_back(a_1);
    preGrafo.emplace_back(a_2);
    preGrafo.emplace_back(a_3);

    //grado de nodos

    for(int i = 0; i < 3; i++){
        preGrafo[0] = opCadaCubo[0][i];
        for(int j = 0; j < 3; j++) {
            preGrafo[1] = opCadaCubo[1][j];
            if (sigueVivo(preGrafo)) {
                for (int k = 0; k < 3; k++) {
                    preGrafo[2] = opCadaCubo[2][k];
                    if(sigueVivo(preGrafo)) {
                        for (int h = 0; h < 3; h++) {
                            preGrafo[3] = opCadaCubo[3][h];
                            if(sigueVivo(preGrafo)) {
                                if (validar(preGrafo)) {//si el subgrafo 1 cumple con las condiciones, entonces llamar a la funcion para el subgrafo 2;
                                    Cubo cubo1_copia = opCadaCubo[0];
                                    Cubo cubo2_copia = opCadaCubo[1];
                                    Cubo cubo3_copia = opCadaCubo[2];
                                    Cubo cubo4_copia = opCadaCubo[3];

                                    cubo1_copia.eliminar(i);
                                    cubo2_copia.eliminar(j);
                                    cubo3_copia.eliminar(k);
                                    cubo4_copia.eliminar(h);

                                    vector<Cubo> opCadaCubo_menosPrueba = {cubo1_copia, cubo2_copia, cubo3_copia, cubo4_copia};
                                    bool segundoValido = false;
                                    vector<Tupla> pregrafo2 = algoritmoInterno(opCadaCubo_menosPrueba, segundoValido);
                                    if (segundoValido) {
                                        vector<vector<Tupla>> Grafo_solucion = {preGrafo, pregrafo2};
                                        todoValido = true;
                                        return Grafo_solucion;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    vector<vector<Tupla>>no_se_puede;
    vector<Tupla>pos0;
    Tupla no("NO", "SOLUTION");
    pos0.emplace_back(no);
    no_se_puede.emplace_back(pos0);
    return no_se_puede;
}


vector<vector<string>> ordenarSubGrafos(const vector<Tupla>&SubGrafoListo)  {
    vector<string> columna1_opuestos;
    vector<string> columna2_opuestos;
    for (auto tupla : SubGrafoListo) {
        if (noEsta(columna1_opuestos, tupla[0]) && noEsta(columna2_opuestos, tupla[1])) {
            columna1_opuestos.emplace_back(tupla[0]);
            columna2_opuestos.emplace_back(tupla[1]);
        } else {
            columna1_opuestos.emplace_back(tupla[1]);
            columna2_opuestos.emplace_back(tupla[0]);
        }
    }
    vector<vector<string>> Union = {columna1_opuestos, columna2_opuestos};
    return Union;

}

vector<vector<string>> Bonito(vector<Cubo> opCadaCubo, bool &todoValido){

    vector<vector<Tupla>> GrafoListo = algoritmoPrincipal(std::move(opCadaCubo), todoValido);
    cout << endl << "Algoritmo Ejecutado al 100%" << endl << endl;
    if(!todoValido) {
        cout << "No existe solucion para la Locura Instantanea :(" << endl;
        cout << "Puede tratar con otras combinaciones :)" << endl;
        cout << endl << endl << "By: Joaquin Ramirez"<< endl;
        vector<vector<string>>nola;
        vector<string>pos0 = {"NO"};
        nola.emplace_back(pos0);
        return nola;
    }
    else{
        cout << "Se encontro la siguiente solucion:" << endl << endl;

        vector<vector<string>> perfilIzqDer = ordenarSubGrafos(GrafoListo[0]);
        vector<vector<string>> perfilDelAtr = ordenarSubGrafos(GrafoListo[1]);

        vector<vector<string>>todasColumnas = {perfilIzqDer[0], perfilIzqDer[1], perfilDelAtr[0], perfilDelAtr[1]};
        return todasColumnas;
    }
}


#endif //INTENTOLOCURA_FUNCIONES_HZZ
