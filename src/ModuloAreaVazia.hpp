#pragma once
#include "Modulo.hpp"

class ModuloAreaVazia : public Modulo{
    public:
        ModuloAreaVazia(char tipo);
        ModuloAreaVazia();

        char getTipo() const override;
        bool podeAcessar() const override;
        void setTipo(char tipo) override;
};