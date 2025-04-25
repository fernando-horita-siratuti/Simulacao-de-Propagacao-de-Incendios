#include "ModuloArvoreQueimada.hpp"
#include <iostream>

ModuloArvoreQueimada::ModuloArvoreQueimada(char tipo) : Modulo(tipo){}
ModuloArvoreQueimada::ModuloArvoreQueimada(){}

char ModuloArvoreQueimada::getTipo() const{
    return tipo;
}

bool ModuloArvoreQueimada::podeAcessar() const{
    return true;
}

void ModuloArvoreQueimada::setTipo(char tipo){
    this->tipo = tipo;
}