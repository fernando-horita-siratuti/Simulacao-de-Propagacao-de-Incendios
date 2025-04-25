#include "Config.hpp"
#include <iostream>

Config::Config(int qntIteracoes, bool todos, bool norte, bool leste, bool sul, bool oeste) : qntIteracoes(qntIteracoes), todos(todos), norte(norte), leste(leste), sul(sul), oeste(oeste){}

bool Config::getDirecaoVentoTodos() const{
    if(todos){
        return true;
    }
    return false;
}

bool Config::getDirecaoVentoNorte() const{
    if(norte){
        return true;
    }
    return false;
}

bool Config::getDirecaoVentoLeste() const{
    if(leste){
        return true;
    }
    return false;
}

bool Config::getDirecaoVentoSul() const{
    if(sul){
        return true;
    }
    return false;
}

bool Config::getDirecaoVentoOeste() const{
    if(oeste){
        return true;
    }
    return false;
}

int Config::getQntIteracoes() const{
    return qntIteracoes;
}

int Config::getVezesRodadas() const{
    return vezesRodadas;
}

void Config::addVezesRodadas(){
    vezesRodadas += 1;
}