#include "ModuloArvoreSaudavel.hpp"
#include <iostream>

ModuloArvoreSaudavel::ModuloArvoreSaudavel(char tipo) : Modulo(tipo){}
ModuloArvoreSaudavel::ModuloArvoreSaudavel(){}

char ModuloArvoreSaudavel::getTipo() const{
    return tipo;
}

bool ModuloArvoreSaudavel::podeAcessar() const{
    return true;
}

void ModuloArvoreSaudavel::setTipo(char tipo){
    this->tipo = tipo;
}