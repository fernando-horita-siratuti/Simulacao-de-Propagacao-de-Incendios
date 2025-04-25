#pragma once
#include "Modulo.hpp"

class ModuloArvoreSaudavel : public Modulo{
    public:
        ModuloArvoreSaudavel(char tipo);
        ModuloArvoreSaudavel();

        char getTipo() const override;
        bool podeAcessar() const override;
        void setTipo(char tipo) override;
};