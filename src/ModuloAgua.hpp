#pragma once
#include "Modulo.hpp"

class ModuloAgua : public Modulo{
    public:
        ModuloAgua(char tipo);
        ModuloAgua();

        char getTipo() const override;
        bool podeAcessar() const override;
        void setTipo(char tipo) override;
};