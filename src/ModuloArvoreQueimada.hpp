#pragma once
#include "Modulo.hpp"

class ModuloArvoreQueimada : public Modulo{
    public:
        ModuloArvoreQueimada(char tipo);
        ModuloArvoreQueimada();

        char getTipo() const override;
        bool podeAcessar() const override;
        void setTipo(char tipo) override;
};