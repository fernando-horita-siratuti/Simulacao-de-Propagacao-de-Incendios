#include "ModuloAreaVazia.hpp"
#include <iostream>

ModuloAreaVazia::ModuloAreaVazia(char tipo) : Modulo(tipo){}
ModuloAreaVazia::ModuloAreaVazia(){}

char ModuloAreaVazia::getTipo() const{
    return tipo;
}

bool ModuloAreaVazia::podeAcessar() const{
    return true;
}

void ModuloAreaVazia::setTipo(char tipo){
    this->tipo = tipo;
}