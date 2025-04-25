#include <iostream>
#include "Arquivo.hpp"
#include "Matriz.hpp"
#include "Config.hpp"

int main(){
    Config config(1000, 1, 0, 0, 0, 0); // Número de interações possíveis, direção do vento para todos os lados, norte, leste, sul e oeste, respectivamente.
    Arquivo arquivo("./dataset/input.dat", config);

    arquivo.lerArq(arquivo);

    return 0;
}