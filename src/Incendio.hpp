#pragma once
#include <string>
#include <vector>
#include <utility>
#include "Modulo.hpp"
#include "Matriz.hpp"
#include "Config.hpp"
#include "Animal.hpp"

class Incendio{
    protected:
        int iniLinha, iniColuna;
        Matriz& matriz;
        std::vector<std::pair<int, int>> arvoresFogo;
        std::vector<std::pair<int, int>> arvoresQueimadas;
        Animal animal;

    public:
        Incendio(int iniLinha, int iniColuna, Matriz& matriz, Animal animal);

        void viraFogo(std::vector<std::pair<int, int>> arvoresFogo, bool todos, bool norte, bool leste, bool sul, bool oeste);
        void espalharFogo(Config config);
        void viraQueimada(std::vector<std::pair<int, int>> arvoresQueimadas);
        std::vector<std::pair<int, int>> getArvoresFogo();
        void addArvoresFogo(std::pair<int, int> arvoreFogo);
        std::vector<std::pair<int, int>> getArvoresQueimadas();
        void addArvoresQueimadas(std::pair<int, int> arvoresQueimadas);
};