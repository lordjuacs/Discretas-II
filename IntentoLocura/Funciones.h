//
// Created by J on 24-Nov-19.
//

#ifndef INTENTOLOCURA_FUNCIONES_H
#define INTENTOLOCURA_FUNCIONES_H

#include "Clases.h"
#include <SFML/Graphics.hpp>
using namespace sf;


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

bool noEsta(const vector<string>&paquete, const string& yo){
    //si no esta devuelve true
    return !(find(paquete.begin(), paquete.end(), yo) != paquete.end());
}

void reset(int &a, int &b, int &c, int &d){
    a = 0;
    b = 0;
    c = 0;
    d = 0;
}


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
    //el pregrafo queda como = [("", ""), ("", ""), ("", ""), ("", "")]

    //grado de nodos
    int cA = 0, cR = 0, cV = 0, cN = 0;

    for (int i = 0; i < 2; i++) {
        preGrafo[0] = opCadaCubo_menosPrueba[0][i];
        for (int j = 0; j < 2; j++) {
            preGrafo[1] = opCadaCubo_menosPrueba[1][j];
            for (int k = 0; k < 2; k++) {
                preGrafo[2] = opCadaCubo_menosPrueba[2][k];
                for (int h = 0; h < 2; h++) {
                    preGrafo[3] = opCadaCubo_menosPrueba[3][h];
                    for (auto &elemento : preGrafo) {
                        for (int w = 0; w < 2; w++) {
                            string evaluando = elemento[w];
                            if (evaluando == "azul")
                                cA++;
                            else if (evaluando == "rojo")
                                cR++;
                            else if (evaluando == "verde")
                                cV++;
                            else
                                cN++;

                        }
                    }
                    if (cA == 2 && cR == 2 && cV == 2 && cN == 2) {//si el subgrafo 2 cumple con las condiciones,entonces acabar;
                        segundoValido = true;
                        return preGrafo;
                    }
                    else{
                        reset(cA, cV, cR, cN);
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
    int cA = 0, cR = 0, cV = 0, cN = 0;

    for(int i = 0; i < 3; i++){
        preGrafo[0] = opCadaCubo[0][i];
        for(int j = 0; j < 3; j++){
            preGrafo[1] = opCadaCubo[1][j];
            for(int k = 0; k < 3; k++){
                preGrafo[2] = opCadaCubo[2][k];
                for(int h = 0; h < 3; h++) {
                    preGrafo[3] = opCadaCubo[3][h];
                    for(auto  elemento : preGrafo){
                        for (int w = 0; w < 2; w++) {
                            auto evaluando = elemento[w];
                            if (evaluando == "azul")
                                cA++;
                            else if (evaluando == "rojo")
                                cR++;
                            else if (evaluando == "verde")
                                cV++;
                            else
                                cN++;

                        }
                    }
                    if(cA == 2 && cR == 2 && cV == 2 && cN == 2){//si el subgrafo 1 cumple con las condiciones, entonces llamar a la funcion para el subgrafo 2;
                        Cubo cubo1_copia = opCadaCubo[0];
                        Cubo cubo2_copia = opCadaCubo[1];
                        Cubo cubo3_copia = opCadaCubo[2];
                        Cubo cubo4_copia = opCadaCubo[3];

                        cubo1_copia.eliminar(i);
                        cubo2_copia.eliminar(j);
                        cubo3_copia.eliminar(k);
                        cubo4_copia.eliminar(h);

                        vector<Cubo>opCadaCubo_menosPrueba = {cubo1_copia, cubo2_copia, cubo3_copia, cubo4_copia};
                        bool segundoValido = false;
                        vector<Tupla>pregrafo2 = algoritmoInterno(opCadaCubo_menosPrueba, segundoValido);
                        if(segundoValido){
                            vector<vector<Tupla>>Grafo_solucion = {preGrafo, pregrafo2};
                            todoValido = true;
                            return Grafo_solucion;
                        }
                        else{
                            reset(cA, cR, cV, cN);
                        }
                    }
                    else{
                        reset(cA, cR, cV, cN);
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

Color revisar(const string& col){
    if(col == "azul")
        return Color::Blue;
    else if(col == "rojo")
        return Color::Red;
    else if(col == "verde")
        return Color::Green;
    else
        return Color::Yellow;
}
vector<vector<string>> ordenarSubGrafos(const vector<Tupla>&SubGrafoListo) {
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
    cout << endl << "Algoritmo Ejecutado al 100%" << endl;
    if(GrafoListo[0][0][0] == "NO") {
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
void imprimirColumnas(const vector<vector<string>>&columnas,  vector<Cubo> &cubos){
        cout << "\tIzq\t" << "Der\t" << "Del\t" << "Atr\t" << endl;
        for (int i = 0; i < 4; i++) {
            cout << "Cubo " << i + 1 << ":\t";
            for (int j = 0; j < 4; j++) {
                cout << "|";
                if (columnas[j][i] == "azul")
                    cout << "A|" << "\t";
                else if (columnas[j][i] == "rojo")
                    cout << "R|" << "\t";
                else if (columnas[j][i] == "verde")
                    cout << "V|" << "\t";
                else
                    cout << "M|" << "\t";
            }
            cout << endl;
        }

        cout << endl << "GRACIAS" << endl << endl << endl << endl;
        cout << "By: Joaquin Ramirez" << endl;





    RenderWindow window(VideoMode(1000, 1000), "LOCURA INSTANTANEA", Style::Close | Style::Resize);

    Font font;
    if(!font.loadFromFile("canvas.otf"))
    {
        //manejar el error
    }
    Text Titulo;
    Titulo.setFont(font);
    Titulo.setString("Locura Instantanea");
    Titulo.setFillColor(Color::White);
    Titulo.setCharacterSize(100);
    Titulo.setOrigin(50.0f, 50.0f);
    Titulo.setPosition(210.0f, 50.0f);

    Text Cubos;
    Cubos.setFont(font);
    Cubos.setString("Cubos");
    Cubos.setFillColor(Color::White);
    Cubos.setCharacterSize(50);
    Cubos.setOrigin(25.0f, 25.0f);
    Cubos.setPosition(475.0f, 135.0f);


    Text Solucion;
    Solucion.setFont(font);
    Solucion.setString("Solucion");
    Solucion.setFillColor(Color::White);
    Solucion.setCharacterSize(50);
    Solucion.setOrigin(25.0f, 25.0f);
    Solucion.setPosition(450.0f, 600.0f);

    Text Creditos;
    Creditos.setFont(font);
    Creditos.setString("By: Joaquin Ramirez");
    Creditos.setFillColor(Color::White);
    Creditos.setCharacterSize(40);
    Creditos.setPosition(700.0f, 910.0f);

    float posx1 = 100.0f;
    float posy = 200.f;
    RectangleShape cubo1_1(Vector2f(50.0f, 50.0f));
    cubo1_1.setOutlineColor(Color::White);
    cubo1_1.setOutlineThickness(2);
    Color color1_1 = revisar(cubos[0][0][0]);
    cubo1_1.setPosition(posx1, posy);
    cubo1_1.setFillColor(color1_1);

    RectangleShape cubo1_3(Vector2f(50.0f, 50.0f));
    cubo1_3.setOutlineColor(Color::White);
    cubo1_3.setOutlineThickness(2);
    Color color1_3 = revisar(cubos[0][1][0]);
    cubo1_3.setPosition(posx1, posy + 50.0f);
    cubo1_3.setFillColor(color1_3);

    RectangleShape cubo1_2(Vector2f(50.0f, 50.0f));
    cubo1_2.setOutlineColor(Color::White);
    cubo1_2.setOutlineThickness(2);
    Color color1_2 = revisar(cubos[0][0][1]);
    cubo1_2.setPosition(posx1, posy + 100.0f);
    cubo1_2.setFillColor(color1_2);

    RectangleShape cubo1_4(Vector2f(50.0f, 50.0f));
    cubo1_4.setOutlineColor(Color::White);
    cubo1_4.setOutlineThickness(2);
    Color color1_4 = revisar(cubos[0][1][1]);
    cubo1_4.setPosition(posx1, posy + 150.0f);
    cubo1_4.setFillColor(color1_4);

    RectangleShape cubo1_5(Vector2f(50.0f, 50.0f));
    cubo1_5.setOutlineColor(Color::White);
    cubo1_5.setOutlineThickness(2);
    Color color1_5 = revisar(cubos[0][2][0]);
    cubo1_5.setPosition(posx1 - 50, posy + 50.0f);
    cubo1_5.setFillColor(color1_5);

    RectangleShape cubo1_6(Vector2f(50.0f, 50.0f));
    cubo1_6.setOutlineColor(Color::White);
    cubo1_6.setOutlineThickness(2);
    Color color1_6 = revisar(cubos[0][2][1]);
    cubo1_6.setPosition(posx1 + 50, posy + 50.0f);
    cubo1_6.setFillColor(color1_6);

    float posx2 = posx1 + 250;
    RectangleShape cubo2_1(Vector2f(50.0f, 50.0f));
    cubo2_1.setOutlineColor(Color::White);
    cubo2_1.setOutlineThickness(2);
    Color color2_1 = revisar(cubos[1][0][0]);
    cubo2_1.setPosition(posx2, posy);
    cubo2_1.setFillColor(color2_1);

    RectangleShape cubo2_3(Vector2f(50.0f, 50.0f));
    cubo2_3.setOutlineColor(Color::White);
    cubo2_3.setOutlineThickness(2);
    Color color2_3 = revisar(cubos[1][1][0]);
    cubo2_3.setPosition(posx2, posy + 50.0f);
    cubo2_3.setFillColor(color2_3);

    RectangleShape cubo2_2(Vector2f(50.0f, 50.0f));
    cubo2_2.setOutlineColor(Color::White);
    cubo2_2.setOutlineThickness(2);
    Color color2_2 = revisar(cubos[1][0][1]);
    cubo2_2.setPosition(posx2, posy + 100.0f);
    cubo2_2.setFillColor(color2_2);

    RectangleShape cubo2_4(Vector2f(50.0f, 50.0f));
    cubo2_4.setOutlineColor(Color::White);
    cubo2_4.setOutlineThickness(2);
    Color color2_4 = revisar(cubos[1][1][1]);
    cubo2_4.setPosition(posx2,  posy + 150.0f);
    cubo2_4.setFillColor(color2_4);

    RectangleShape cubo2_5(Vector2f(50.0f, 50.0f));
    cubo2_5.setOutlineColor(Color::White);
    cubo2_5.setOutlineThickness(2);
    Color color2_5 = revisar(cubos[1][2][0]);
    cubo2_5.setPosition(posx2 - 50, posy + 50.0f);
    cubo2_5.setFillColor(color2_5);

    RectangleShape cubo2_6(Vector2f(50.0f, 50.0f));
    cubo2_6.setOutlineColor(Color::White);
    cubo2_6.setOutlineThickness(2);
    Color color2_6 = revisar(cubos[1][2][1]);
    cubo2_6.setPosition(posx2 + 50, posy + 50.0f);
    cubo2_6.setFillColor(color2_6);

    float posx3 = posx2 + 250;
    RectangleShape cubo3_1(Vector2f(50.0f, 50.0f));
    cubo3_1.setOutlineColor(Color::White);
    cubo3_1.setOutlineThickness(2);
    Color color3_1 = revisar(cubos[2][0][0]);
    cubo3_1.setPosition(posx3, posy);
    cubo3_1.setFillColor(color3_1);

    RectangleShape cubo3_3(Vector2f(50.0f, 50.0f));
    cubo3_3.setOutlineColor(Color::White);
    cubo3_3.setOutlineThickness(2);
    Color color3_3 = revisar(cubos[2][1][0]);
    cubo3_3.setPosition(posx3, posy + 50.0f);
    cubo3_3.setFillColor(color3_3);

    RectangleShape cubo3_2(Vector2f(50.0f, 50.0f));
    cubo3_2.setOutlineColor(Color::White);
    cubo3_2.setOutlineThickness(2);
    Color color3_2 = revisar(cubos[2][0][1]);
    cubo3_2.setPosition(posx3, posy + 100.0f);
    cubo3_2.setFillColor(color3_2);

    RectangleShape cubo3_4(Vector2f(50.0f, 50.0f));
    cubo3_4.setOutlineColor(Color::White);
    cubo3_4.setOutlineThickness(2);
    Color color3_4 = revisar(cubos[2][1][1]);
    cubo3_4.setPosition(posx3, posy + 150.0f);
    cubo3_4.setFillColor(color3_4);

    RectangleShape cubo3_5(Vector2f(50.0f, 50.0f));
    cubo3_5.setOutlineColor(Color::White);
    cubo3_5.setOutlineThickness(2);
    Color color3_5 = revisar(cubos[2][2][0]);
    cubo3_5.setPosition(posx3 - 50, posy + 50.0f);
    cubo3_5.setFillColor(color3_5);

    RectangleShape cubo3_6(Vector2f(50.0f, 50.0f));
    cubo3_6.setOutlineColor(Color::White);
    cubo3_6.setOutlineThickness(2);
    Color color3_6 = revisar(cubos[2][2][1]);
    cubo3_6.setPosition(posx3 + 50, posy + 50.0f);
    cubo3_6.setFillColor(color3_6);

    float posx4 = posx3 + 250;
    RectangleShape cubo4_1(Vector2f(50.0f, 50.0f));
    cubo4_1.setOutlineColor(Color::White);
    cubo4_1.setOutlineThickness(2);
    Color color4_1 = revisar(cubos[3][0][0]);
    cubo4_1.setPosition(posx4, posy);
    cubo4_1.setFillColor(color4_1);

    RectangleShape cubo4_3(Vector2f(50.0f, 50.0f));
    cubo4_3.setOutlineColor(Color::White);
    cubo4_3.setOutlineThickness(2);
    Color color4_3 = revisar(cubos[3][1][0]);
    cubo4_3.setPosition(posx4, posy + 50.0f);
    cubo4_3.setFillColor(color4_3);

    RectangleShape cubo4_2(Vector2f(50.0f, 50.0f));
    cubo4_2.setOutlineColor(Color::White);
    cubo4_2.setOutlineThickness(2);
    Color color4_2 = revisar(cubos[3][0][1]);
    cubo4_2.setPosition(posx4, posy +100.0f);
    cubo4_2.setFillColor(color4_2);

    RectangleShape cubo4_4(Vector2f(50.0f, 50.0f));
    cubo4_4.setOutlineColor(Color::White);
    cubo4_4.setOutlineThickness(2);
    Color color4_4 = revisar(cubos[3][1][1]);
    cubo4_4.setPosition(posx4, posy + 150.0f);
    cubo4_4.setFillColor(color4_4);

    RectangleShape cubo4_5(Vector2f(50.0f, 50.0f));
    cubo4_5.setOutlineColor(Color::White);
    cubo4_5.setOutlineThickness(2);
    Color color4_5 = revisar(cubos[3][2][0]);
    cubo4_5.setPosition(posx4 - 50, posy + 50.0f);
    cubo4_5.setFillColor(color4_5);

    RectangleShape cubo4_6(Vector2f(50.0f, 50.0f));
    cubo4_6.setOutlineColor(Color::White);
    cubo4_6.setOutlineThickness(2);
    Color color4_6 = revisar(cubos[3][2][1]);
    cubo4_6.setPosition(posx4 + 50, posy + 50.0f);
    cubo4_6.setFillColor(color4_6);


    //SOLUCION
    float nposy = 700;

    Text enu1;
    enu1.setFont(font);
    enu1.setString("1");
    enu1.setFillColor(Color::White);
    enu1.setCharacterSize(40);
    enu1.setPosition(posx1 + 20 , posy - 50);

    Text enu2;
    enu2.setFont(font);
    enu2.setString("2");
    enu2.setFillColor(Color::White);
    enu2.setCharacterSize(40);
    enu2.setPosition(posx2 + 20 , posy - 50);

    Text enu3;
    enu3.setFont(font);
    enu3.setString("3");
    enu3.setFillColor(Color::White);
    enu3.setCharacterSize(40);
    enu3.setPosition(posx3 + 20 , posy - 50);

    Text enu4;
    enu4.setFont(font);
    enu4.setString("4");
    enu4.setFillColor(Color::White);
    enu4.setCharacterSize(40);
    enu4.setPosition(posx4 + 20 , posy - 50);

    Text num1;
    num1.setFont(font);
    num1.setString("Cubo 1");
    num1.setFillColor(Color::White);
    num1.setCharacterSize(30);
    num1.setPosition(posx1 - 85, nposy);

    Text num2;
    num2.setFont(font);
    num2.setString("Cubo 2");
    num2.setFillColor(Color::White);
    num2.setCharacterSize(30);
    num2.setPosition(posx1 - 85, nposy + 50);

    Text num3;
    num3.setFont(font);
    num3.setString("Cubo 3");
    num3.setFillColor(Color::White);
    num3.setCharacterSize(30);
    num3.setPosition(posx1 - 85, nposy + 100);

    Text num4;
    num4.setFont(font);
    num4.setString("Cubo 4");
    num4.setFillColor(Color::White);
    num4.setCharacterSize(30);
    num4.setPosition(posx1 - 85, nposy + 150);

    Text Izq;
    Izq.setFont(font);
    Izq.setString("Izq");
    Izq.setFillColor(Color::White);
    Izq.setCharacterSize(40);
    Izq.setPosition(posx1, nposy - 60);



    //IZQUIERDA
    RectangleShape izquierda_1(Vector2f(50.0f, 50.0f));
    izquierda_1.setOutlineColor(Color::White);
    izquierda_1.setOutlineThickness(2);
    Color izqui_1 = revisar(columnas[0][0]);
    izquierda_1.setPosition(posx1, nposy);
    izquierda_1.setFillColor(izqui_1);

    RectangleShape izquierda_2(Vector2f(50.0f, 50.0f));
    izquierda_2.setOutlineColor(Color::White);
    izquierda_2.setOutlineThickness(2);
    Color izqui_2 = revisar(columnas[0][1]);
    izquierda_2.setPosition(posx1, nposy + 50);
    izquierda_2.setFillColor(izqui_2);

    RectangleShape izquierda_3(Vector2f(50.0f, 50.0f));
    izquierda_3.setOutlineColor(Color::White);
    izquierda_3.setOutlineThickness(2);
    Color izqui_3 = revisar(columnas[0][2]);
    izquierda_3.setPosition(posx1, nposy + 100);
    izquierda_3.setFillColor(izqui_3);

    RectangleShape izquierda_4(Vector2f(50.0f, 50.0f));
    izquierda_4.setOutlineColor(Color::White);
    izquierda_4.setOutlineThickness(2);
    Color izqui_4 = revisar(columnas[0][3]);
    izquierda_4.setPosition(posx1, nposy + 150);
    izquierda_4.setFillColor(izqui_4);


    Text Der;
    Der.setFont(font);
    Der.setString("Der");
    Der.setFillColor(Color::White);
    Der.setCharacterSize(40);
    Der.setPosition(posx2, nposy - 60);

    //DERECHA
    RectangleShape derecha_1(Vector2f(50.0f, 50.0f));
    derecha_1.setOutlineColor(Color::White);
    derecha_1.setOutlineThickness(2);
    Color dere_1 = revisar(columnas[1][0]);
    derecha_1.setPosition(posx2, nposy);
    derecha_1.setFillColor(dere_1);

    RectangleShape derecha_2(Vector2f(50.0f, 50.0f));
    derecha_2.setOutlineColor(Color::White);
    derecha_2.setOutlineThickness(2);
    Color dere_2 = revisar(columnas[1][1]);
    derecha_2.setPosition(posx2, nposy + 50);
    derecha_2.setFillColor(dere_2);

    RectangleShape derecha_3(Vector2f(50.0f, 50.0f));
    derecha_3.setOutlineColor(Color::White);
    derecha_3.setOutlineThickness(2);
    Color dere_3 = revisar(columnas[1][2]);
    derecha_3.setPosition(posx2, nposy + 100);
    derecha_3.setFillColor(dere_3);

    RectangleShape derecha_4(Vector2f(50.0f, 50.0f));
    derecha_4.setOutlineColor(Color::White);
    derecha_4.setOutlineThickness(2);
    Color dere_4 = revisar(columnas[1][3]);
    derecha_4.setPosition(posx2, nposy + 150);
    derecha_4.setFillColor(dere_4);


    Text Del;
    Del.setFont(font);
    Del.setString("Del");
    Del.setFillColor(Color::White);
    Del.setCharacterSize(40);
    Del.setPosition(posx3, nposy - 60);

    //DELANTE

    RectangleShape delante_1(Vector2f(50.0f, 50.0f));
    delante_1.setOutlineColor(Color::White);
    delante_1.setOutlineThickness(2);
    Color del_1 = revisar(columnas[2][0]);
    delante_1.setPosition(posx3, nposy);
    delante_1.setFillColor(del_1);

    RectangleShape delante_2(Vector2f(50.0f, 50.0f));
    delante_2.setOutlineColor(Color::White);
    delante_2.setOutlineThickness(2);
    Color del_2 = revisar(columnas[2][1]);
    delante_2.setPosition(posx3, nposy + 50);
    delante_2.setFillColor(del_2);

    RectangleShape delante_3(Vector2f(50.0f, 50.0f));
    delante_3.setOutlineColor(Color::White);
    delante_3.setOutlineThickness(2);
    Color del_3 = revisar(columnas[2][2]);
    delante_3.setPosition(posx3, nposy + 100);
    delante_3.setFillColor(del_3);

    RectangleShape delante_4(Vector2f(50.0f, 50.0f));
    delante_4.setOutlineColor(Color::White);
    delante_4.setOutlineThickness(2);
    Color del_4 = revisar(columnas[2][3]);
    delante_4.setPosition(posx3, nposy + 150);
    delante_4.setFillColor(del_4);

    Text Atr;
    Atr.setFont(font);
    Atr.setString("Atr");
    Atr.setFillColor(Color::White);
    Atr.setCharacterSize(40);
    Atr.setPosition(posx4, nposy - 60);

    //ATRAS
    RectangleShape atras_1(Vector2f(50.0f, 50.0f));
    atras_1.setOutlineColor(Color::White);
    atras_1.setOutlineThickness(2);
    Color atr_1 = revisar(columnas[3][0]);
    atras_1.setPosition(posx4, nposy);
    atras_1.setFillColor(atr_1);

    RectangleShape atras_2(Vector2f(50.0f, 50.0f));
    atras_2.setOutlineColor(Color::White);
    atras_2.setOutlineThickness(2);
    Color atr_2 = revisar(columnas[3][1]);
    atras_2.setPosition(posx4, nposy + 50);
    atras_2.setFillColor(atr_2);

    RectangleShape atras_3(Vector2f(50.0f, 50.0f));
    atras_3.setOutlineColor(Color::White);
    atras_3.setOutlineThickness(2);
    Color atr_3 = revisar(columnas[3][2]);
    atras_3.setPosition(posx4, nposy + 100);
    atras_3.setFillColor(atr_3);

    RectangleShape atras_4(Vector2f(50.0f, 50.0f));
    atras_4.setOutlineColor(Color::White);
    atras_4.setOutlineThickness(2);
    Color atr_4 = revisar(columnas[3][3]);
    atras_4.setPosition(posx4, nposy + 150);
    atras_4.setFillColor(atr_4);





    while (window.isOpen())
    {
        Event evento{};
        while(window.pollEvent(evento))
        {
            switch(evento.type)
            {
                case Event::Closed:
                    window.close();
                    break;
                //case Event::Resized:
                  //  cout << "New windond width:" << evento.size.width << " New window height:" <<evento.size.height << endl;
                    //break;
                //case Event::TextEntered:
                  //  if(evento.Titulo.unicode < 128)
                    //    cout << char(evento.Titulo.unicode);
            }
            if(evento.type == evento.Closed)
                window.close();

        }


        window.clear();

        window.draw(Titulo);
        window.draw(Cubos);
        window.draw(Solucion);
        window.draw(enu1);
        window.draw(enu2);
        window.draw(enu3);
        window.draw(enu4);
        window.draw(num1);
        window.draw(num2);
        window.draw(num3);
        window.draw(num4);
        window.draw(Creditos);

        window.draw(cubo1_1);
        window.draw(cubo1_3);
        window.draw(cubo1_2);
        window.draw(cubo1_4);
        window.draw(cubo1_5);
        window.draw(cubo1_6);

        window.draw(cubo2_1);
        window.draw(cubo2_3);
        window.draw(cubo2_2);
        window.draw(cubo2_4);
        window.draw(cubo2_5);
        window.draw(cubo2_6);

        window.draw(cubo3_1);
        window.draw(cubo3_3);
        window.draw(cubo3_2);
        window.draw(cubo3_4);
        window.draw(cubo3_5);
        window.draw(cubo3_6);

        window.draw(cubo4_1);
        window.draw(cubo4_3);
        window.draw(cubo4_2);
        window.draw(cubo4_4);
        window.draw(cubo4_5);
        window.draw(cubo4_6);

        window.draw(Izq);
        window.draw(izquierda_1);
        window.draw(izquierda_2);
        window.draw(izquierda_3);
        window.draw(izquierda_4);

        window.draw(Der);
        window.draw(derecha_1);
        window.draw(derecha_2);
        window.draw(derecha_3);
        window.draw(derecha_4);

        window.draw(Del);
        window.draw(delante_1);
        window.draw(delante_2);
        window.draw(delante_3);
        window.draw(delante_4);

        window.draw(Atr);
        window.draw(atras_1);
        window.draw(atras_2);
        window.draw(atras_3);
        window.draw(atras_4);



        window.display();
    }
}

void imprimirSecundario(vector<Cubo>&cubos)
{
    RenderWindow window(VideoMode(1000, 1000), "LOCURA INSTANTANEA", Style::Close | Style::Resize);

    Font font;
    if(!font.loadFromFile("canvas.otf"))
    {
        //manejar el error
    }
    Text Titulo;
    Titulo.setFont(font);
    Titulo.setString("Locura Instantanea");
    Titulo.setFillColor(Color::White);
    Titulo.setCharacterSize(100);
    Titulo.setOrigin(50.0f, 50.0f);
    Titulo.setPosition(210.0f, 50.0f);

    Text Cubos;
    Cubos.setFont(font);
    Cubos.setString("Cubos");
    Cubos.setFillColor(Color::White);
    Cubos.setCharacterSize(50);
    Cubos.setOrigin(25.0f, 25.0f);
    Cubos.setPosition(475.0f, 135.0f);


    Text Solucion;
    Solucion.setFont(font);
    Solucion.setString("Solucion");
    Solucion.setFillColor(Color::White);
    Solucion.setCharacterSize(50);
    Solucion.setOrigin(25.0f, 25.0f);
    Solucion.setPosition(450.0f, 600.0f);

    Text Creditos;
    Creditos.setFont(font);
    Creditos.setString("By: Joaquin Ramirez");
    Creditos.setFillColor(Color::White);
    Creditos.setCharacterSize(40);
    Creditos.setPosition(700.0f, 910.0f);


    float posx1 = 100.0f;
    float posy = 200.f;
    RectangleShape cubo1_1(Vector2f(50.0f, 50.0f));
    cubo1_1.setOutlineColor(Color::White);
    cubo1_1.setOutlineThickness(2);
    Color color1_1 = revisar(cubos[0][0][0]);
    cubo1_1.setPosition(posx1, posy);
    cubo1_1.setFillColor(color1_1);

    RectangleShape cubo1_3(Vector2f(50.0f, 50.0f));
    cubo1_3.setOutlineColor(Color::White);
    cubo1_3.setOutlineThickness(2);
    Color color1_3 = revisar(cubos[0][1][0]);
    cubo1_3.setPosition(posx1, posy + 50.0f);
    cubo1_3.setFillColor(color1_3);

    RectangleShape cubo1_2(Vector2f(50.0f, 50.0f));
    cubo1_2.setOutlineColor(Color::White);
    cubo1_2.setOutlineThickness(2);
    Color color1_2 = revisar(cubos[0][0][1]);
    cubo1_2.setPosition(posx1, posy + 100.0f);
    cubo1_2.setFillColor(color1_2);

    RectangleShape cubo1_4(Vector2f(50.0f, 50.0f));
    cubo1_4.setOutlineColor(Color::White);
    cubo1_4.setOutlineThickness(2);
    Color color1_4 = revisar(cubos[0][1][1]);
    cubo1_4.setPosition(posx1, posy + 150.0f);
    cubo1_4.setFillColor(color1_4);

    RectangleShape cubo1_5(Vector2f(50.0f, 50.0f));
    cubo1_5.setOutlineColor(Color::White);
    cubo1_5.setOutlineThickness(2);
    Color color1_5 = revisar(cubos[0][2][0]);
    cubo1_5.setPosition(posx1 - 50, posy + 50.0f);
    cubo1_5.setFillColor(color1_5);

    RectangleShape cubo1_6(Vector2f(50.0f, 50.0f));
    cubo1_6.setOutlineColor(Color::White);
    cubo1_6.setOutlineThickness(2);
    Color color1_6 = revisar(cubos[0][2][1]);
    cubo1_6.setPosition(posx1 + 50, posy + 50.0f);
    cubo1_6.setFillColor(color1_6);

    float posx2 = posx1 + 250;
    RectangleShape cubo2_1(Vector2f(50.0f, 50.0f));
    cubo2_1.setOutlineColor(Color::White);
    cubo2_1.setOutlineThickness(2);
    Color color2_1 = revisar(cubos[1][0][0]);
    cubo2_1.setPosition(posx2, posy);
    cubo2_1.setFillColor(color2_1);

    RectangleShape cubo2_3(Vector2f(50.0f, 50.0f));
    cubo2_3.setOutlineColor(Color::White);
    cubo2_3.setOutlineThickness(2);
    Color color2_3 = revisar(cubos[1][1][0]);
    cubo2_3.setPosition(posx2, posy + 50.0f);
    cubo2_3.setFillColor(color2_3);

    RectangleShape cubo2_2(Vector2f(50.0f, 50.0f));
    cubo2_2.setOutlineColor(Color::White);
    cubo2_2.setOutlineThickness(2);
    Color color2_2 = revisar(cubos[1][0][1]);
    cubo2_2.setPosition(posx2, posy + 100.0f);
    cubo2_2.setFillColor(color2_2);

    RectangleShape cubo2_4(Vector2f(50.0f, 50.0f));
    cubo2_4.setOutlineColor(Color::White);
    cubo2_4.setOutlineThickness(2);
    Color color2_4 = revisar(cubos[1][1][1]);
    cubo2_4.setPosition(posx2,  posy + 150.0f);
    cubo2_4.setFillColor(color2_4);

    RectangleShape cubo2_5(Vector2f(50.0f, 50.0f));
    cubo2_5.setOutlineColor(Color::White);
    cubo2_5.setOutlineThickness(2);
    Color color2_5 = revisar(cubos[1][2][0]);
    cubo2_5.setPosition(posx2 - 50, posy + 50.0f);
    cubo2_5.setFillColor(color2_5);

    RectangleShape cubo2_6(Vector2f(50.0f, 50.0f));
    cubo2_6.setOutlineColor(Color::White);
    cubo2_6.setOutlineThickness(2);
    Color color2_6 = revisar(cubos[1][2][1]);
    cubo2_6.setPosition(posx2 + 50, posy + 50.0f);
    cubo2_6.setFillColor(color2_6);

    float posx3 = posx2 + 250;
    RectangleShape cubo3_1(Vector2f(50.0f, 50.0f));
    cubo3_1.setOutlineColor(Color::White);
    cubo3_1.setOutlineThickness(2);
    Color color3_1 = revisar(cubos[2][0][0]);
    cubo3_1.setPosition(posx3, posy);
    cubo3_1.setFillColor(color3_1);

    RectangleShape cubo3_3(Vector2f(50.0f, 50.0f));
    cubo3_3.setOutlineColor(Color::White);
    cubo3_3.setOutlineThickness(2);
    Color color3_3 = revisar(cubos[2][1][0]);
    cubo3_3.setPosition(posx3, posy + 50.0f);
    cubo3_3.setFillColor(color3_3);

    RectangleShape cubo3_2(Vector2f(50.0f, 50.0f));
    cubo3_2.setOutlineColor(Color::White);
    cubo3_2.setOutlineThickness(2);
    Color color3_2 = revisar(cubos[2][0][1]);
    cubo3_2.setPosition(posx3, posy + 100.0f);
    cubo3_2.setFillColor(color3_2);

    RectangleShape cubo3_4(Vector2f(50.0f, 50.0f));
    cubo3_4.setOutlineColor(Color::White);
    cubo3_4.setOutlineThickness(2);
    Color color3_4 = revisar(cubos[2][1][1]);
    cubo3_4.setPosition(posx3, posy + 150.0f);
    cubo3_4.setFillColor(color3_4);

    RectangleShape cubo3_5(Vector2f(50.0f, 50.0f));
    cubo3_5.setOutlineColor(Color::White);
    cubo3_5.setOutlineThickness(2);
    Color color3_5 = revisar(cubos[2][2][0]);
    cubo3_5.setPosition(posx3 - 50, posy + 50.0f);
    cubo3_5.setFillColor(color3_5);

    RectangleShape cubo3_6(Vector2f(50.0f, 50.0f));
    cubo3_6.setOutlineColor(Color::White);
    cubo3_6.setOutlineThickness(2);
    Color color3_6 = revisar(cubos[2][2][1]);
    cubo3_6.setPosition(posx3 + 50, posy + 50.0f);
    cubo3_6.setFillColor(color3_6);

    float posx4 = posx3 + 250;
    RectangleShape cubo4_1(Vector2f(50.0f, 50.0f));
    cubo4_1.setOutlineColor(Color::White);
    cubo4_1.setOutlineThickness(2);
    Color color4_1 = revisar(cubos[3][0][0]);
    cubo4_1.setPosition(posx4, posy);
    cubo4_1.setFillColor(color4_1);

    RectangleShape cubo4_3(Vector2f(50.0f, 50.0f));
    cubo4_3.setOutlineColor(Color::White);
    cubo4_3.setOutlineThickness(2);
    Color color4_3 = revisar(cubos[3][1][0]);
    cubo4_3.setPosition(posx4, posy + 50.0f);
    cubo4_3.setFillColor(color4_3);

    RectangleShape cubo4_2(Vector2f(50.0f, 50.0f));
    cubo4_2.setOutlineColor(Color::White);
    cubo4_2.setOutlineThickness(2);
    Color color4_2 = revisar(cubos[3][0][1]);
    cubo4_2.setPosition(posx4, posy +100.0f);
    cubo4_2.setFillColor(color4_2);

    RectangleShape cubo4_4(Vector2f(50.0f, 50.0f));
    cubo4_4.setOutlineColor(Color::White);
    cubo4_4.setOutlineThickness(2);
    Color color4_4 = revisar(cubos[3][1][1]);
    cubo4_4.setPosition(posx4, posy + 150.0f);
    cubo4_4.setFillColor(color4_4);

    RectangleShape cubo4_5(Vector2f(50.0f, 50.0f));
    cubo4_5.setOutlineColor(Color::White);
    cubo4_5.setOutlineThickness(2);
    Color color4_5 = revisar(cubos[3][2][0]);
    cubo4_5.setPosition(posx4 - 50, posy + 50.0f);
    cubo4_5.setFillColor(color4_5);

    RectangleShape cubo4_6(Vector2f(50.0f, 50.0f));
    cubo4_6.setOutlineColor(Color::White);
    cubo4_6.setOutlineThickness(2);
    Color color4_6 = revisar(cubos[3][2][1]);
    cubo4_6.setPosition(posx4 + 50, posy + 50.0f);
    cubo4_6.setFillColor(color4_6);

    Text enu1;
    enu1.setFont(font);
    enu1.setString("1");
    enu1.setFillColor(Color::White);
    enu1.setCharacterSize(40);
    enu1.setPosition(posx1 + 20 , posy - 50);

    Text enu2;
    enu2.setFont(font);
    enu2.setString("2");
    enu2.setFillColor(Color::White);
    enu2.setCharacterSize(40);
    enu2.setPosition(posx2 + 20 , posy - 50);

    Text enu3;
    enu3.setFont(font);
    enu3.setString("3");
    enu3.setFillColor(Color::White);
    enu3.setCharacterSize(40);
    enu3.setPosition(posx3 + 20 , posy - 50);

    Text enu4;
    enu4.setFont(font);
    enu4.setString("4");
    enu4.setFillColor(Color::White);
    enu4.setCharacterSize(40);
    enu4.setPosition(posx4 + 20 , posy - 50);

    Text NoHay;
    NoHay.setFont(font);
    NoHay.setString("No Existe :(");
    NoHay.setFillColor(Color::Red);
    NoHay.setCharacterSize(80);
    NoHay.setPosition(350.0f, 700.0f);


    while (window.isOpen())
    {
        Event evento{};
        while(window.pollEvent(evento))
        {
            switch(evento.type)
            {
                case Event::Closed:
                    window.close();
                    break;
                    //case Event::Resized:
                    //  cout << "New windond width:" << evento.size.width << " New window height:" <<evento.size.height << endl;
                    //break;
                    //case Event::TextEntered:
                    //  if(evento.Titulo.unicode < 128)
                    //    cout << char(evento.Titulo.unicode);
            }
            if(evento.type == evento.Closed)
                window.close();

        }


        window.clear();

        window.draw(Titulo);
        window.draw(Cubos);
        window.draw(Solucion);
        window.draw(enu1);
        window.draw(enu2);
        window.draw(enu3);
        window.draw(enu4);
        window.draw(NoHay);
        window.draw(Creditos);


        window.draw(cubo1_1);
        window.draw(cubo1_3);
        window.draw(cubo1_2);
        window.draw(cubo1_4);
        window.draw(cubo1_5);
        window.draw(cubo1_6);

        window.draw(cubo2_1);
        window.draw(cubo2_3);
        window.draw(cubo2_2);
        window.draw(cubo2_4);
        window.draw(cubo2_5);
        window.draw(cubo2_6);

        window.draw(cubo3_1);
        window.draw(cubo3_3);
        window.draw(cubo3_2);
        window.draw(cubo3_4);
        window.draw(cubo3_5);
        window.draw(cubo3_6);

        window.draw(cubo4_1);
        window.draw(cubo4_3);
        window.draw(cubo4_2);
        window.draw(cubo4_4);
        window.draw(cubo4_5);
        window.draw(cubo4_6);



        window.display();
    }

}

#endif //INTENTOLOCURA_FUNCIONES_HZZ
