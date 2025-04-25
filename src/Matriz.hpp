#pragma once
#include <string>
#include <vector>
#include "Modulo.hpp"
#include "ModuloArvoreFogo.hpp"
#include "ModuloArvoreSaudavel.hpp"
#include "ModuloArvoreQueimada.hpp"
#include "ModuloAreaVazia.hpp"
#include "ModuloAgua.hpp"
#include "Config.hpp"


class Matriz{
    protected:
        std::vector<std::vector<Modulo*>> matriz;
        int linhas, colunas, linhaAnimal = 0, colunaAnimal = 0;
        Config config;
        short aguasEncontradas = 0, passos = 0;
        std::vector<std::pair<int, int>> caminho = {};
        std::vector<int> naoMoveu = {};

    public:
        Matriz(int linhas, int colunas, Config config);

        void addModulo(int linhas, int colunas, char modulo);
        std::vector<std::vector<Modulo*>> getMatriz();
        void imprimirMatriz();
        bool verificaParadaFloresta();
        bool verificaParadaIteracao();
        void registraResumo();
        // bool podeIr(int linha, int coluna, bool todos, bool norte, bool leste, bool sul, bool oeste);
        int getLinhas();
        int getColunas();
        int getLinhaAnimal();
        int getColunaAnimal();
        short addAguasEncontradas();
        void setPassos(int passosAtualizados);
        void setLinhaAnimal(int linhaAnimalNova);
        void setColunaAnimal(int colunaAnimalNova);
        void addCaminho(int linha, int coluna);
        void addNaoMoveu(int interacao);
};