#pragma once
#include <string>
#include <vector>

class Config{
    int qntIteracoes, vezesRodadas = 1;
    bool todos, norte, leste, sul, oeste;

    public:
        Config(int qntInteracoes, bool todos, bool norte, bool leste, bool sul, bool oeste);

        bool getDirecaoVentoTodos() const;
        bool getDirecaoVentoNorte() const;
        bool getDirecaoVentoLeste() const;
        bool getDirecaoVentoSul() const;
        bool getDirecaoVentoOeste() const;
        int getQntIteracoes() const;
        int getVezesRodadas() const;
        void addVezesRodadas();
};