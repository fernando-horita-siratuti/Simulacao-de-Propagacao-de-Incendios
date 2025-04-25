#pragma once
#include <string>

class Modulo{
    protected:
        char tipo;

    public:
        Modulo(char tipo);
        Modulo();

        virtual char getTipo() const = 0;
        virtual bool podeAcessar() const = 0;
        virtual void setTipo(char tipo) = 0;
};