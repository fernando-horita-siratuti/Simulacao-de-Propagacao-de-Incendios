#pragma once
#include "Config.hpp"
#include <string>
#include <vector>

class Arquivo{
    private:
        std::string nomeArq;
        Config config;

    public:
        Arquivo(std::string nomeArq, Config config);

        void lerArq(Arquivo arq);
        std::string getNome();
};