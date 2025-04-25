#include "ModuloArvoreFogo.hpp"
#include <iostream>

ModuloArvoreFogo::ModuloArvoreFogo(char tipo) : Modulo(tipo){}
ModuloArvoreFogo::ModuloArvoreFogo(){}

char ModuloArvoreFogo::getTipo() const{
    return tipo;
}

bool ModuloArvoreFogo::podeAcessar() const{
    return false;
}

void ModuloArvoreFogo::setTipo(char tipo){
    this->tipo = tipo;
}