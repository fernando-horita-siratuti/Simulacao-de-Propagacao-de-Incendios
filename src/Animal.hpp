#pragma once
#include <string>
#include <vector>
#include <utility>
#include "Modulo.hpp"
#include "Matriz.hpp"

class Animal{
    protected:
        int linhaAnimal, colunaAnimal;
        static int animalNoZero;
        Matriz& matriz;
        Config config;
        struct Posicao{
            int x, y;
        };

    public:
        Animal(int linhaAnimal, int colunaAnimal, Matriz& matriz, Config config);

        void iniciarJogo();
        bool buscarAgua();
        bool buscarVazioArvoreSaudavel();
        bool buscarArvoreQueimada();
        void jogaUmidade(int coluna, int linha);
        bool estaPreso(int linha, int coluna);
        void setPosicao(int linha, int coluna);
        int getAnimalNoZero();
        void addAnimalNoZero();
        int getLinha();
        int getColuna();
};