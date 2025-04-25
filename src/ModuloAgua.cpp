#include "ModuloAgua.hpp"
#include <iostream>

ModuloAgua::ModuloAgua(char tipo) : Modulo(tipo){}
ModuloAgua::ModuloAgua(){}

char ModuloAgua::getTipo() const{
    return tipo;
}

bool ModuloAgua::podeAcessar() const{
    return true;
}

void ModuloAgua::setTipo(char tipo){
    this->tipo = tipo;
}