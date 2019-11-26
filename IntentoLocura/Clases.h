//
// Created by J on 19-Nov-19.
//

#ifndef INTENTOLOCURA_CLASES_H
#define INTENTOLOCURA_CLASES_H

#include "Tipos.h"
class Tupla {
public:
    string pos_0, pos_1;

    Tupla(){
        pos_0 = pos_1 = ",,,";
    }
    Tupla(string pos0, string pos1) {
        this->pos_0 = std::move(pos0);
        this->pos_1 = std::move(pos1);
    }

    string operator[](int posicion){
        if(posicion == 0)
            return pos_0;
        else
            return pos_1;
    }

    bool vacio(){
        return pos_0 == " " && pos_1 == " ";
    }



};

class Cubo{
public:
    vector<Tupla> relaciones;
    Cubo(vector<string>&caras){
        Tupla opuestos1(caras[0], caras[1]);
        Tupla opuestos2(caras[2], caras[3]);
        Tupla opuestos3(caras[4], caras[5]);
        this->relaciones.emplace_back(opuestos1);
        this->relaciones.emplace_back(opuestos2);
        this->relaciones.emplace_back(opuestos3);
    }

    Tupla operator[](int posicion)
    {
        if(posicion == 0)
            return relaciones[0];
        else if(posicion == 1)
            return relaciones[1];
        else
            return relaciones[2];
    }

    void eliminar(int posicion){
        relaciones.erase(relaciones.begin() + posicion);
    }
    ~Cubo(){
        relaciones.clear();
    }
};



#endif //INTENTOLOCURA_CLASES_H
