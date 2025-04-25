#pragma once
#include "Modulo.hpp"

class ModuloArvoreFogo : public Modulo{
    public:
        ModuloArvoreFogo(char tipo);
        ModuloArvoreFogo();

        char getTipo() const override;
        bool podeAcessar() const override;
        void setTipo(char tipo) override;
};