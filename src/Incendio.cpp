#include "Incendio.hpp"
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>

Incendio::Incendio(int iniLinha, int iniColuna, Matriz& matriz, Animal animal) : iniLinha(iniLinha), iniColuna(iniColuna), matriz(matriz), animal(animal){}

void Incendio::viraFogo(std::vector<std::pair<int, int>> arvoresFogo, bool todos, bool norte, bool leste, bool sul, bool oeste){
    auto mapa = matriz.getMatriz();
    int qntLinhas = matriz.getLinhas();
    int qntColunas = matriz.getColunas();

    for(std::pair<int, int> arvore : arvoresFogo){
        int linha = arvore.first;
        int coluna = arvore.second;

        if(linha - 1 >= 0 && mapa[linha - 1][coluna]->getTipo() == '1' && (norte || todos)){
            mapa[linha - 1][coluna]->setTipo('2');
        }
        if(coluna + 1 < qntColunas && mapa[linha][coluna + 1]->getTipo() == '1' && (leste || todos)){
            mapa[linha][coluna + 1]->setTipo('2');
        }
        if(linha + 1 < qntLinhas && mapa[linha + 1][coluna]->getTipo() == '1' && (sul || todos)){
            mapa[linha + 1][coluna]->setTipo('2');
        }
        if(coluna - 1 >= 0 && mapa[linha][coluna - 1]->getTipo() == '1' && (oeste || todos)){
            mapa[linha][coluna - 1]->setTipo('2');
        }
    }

    matriz.imprimirMatriz();
}

void Incendio::espalharFogo(Config config){ 
    auto mapa = matriz.getMatriz();
    int numLinha = matriz.getLinhas();
    int numColuna = matriz.getColunas();
    std::string nomeArquivoSaida = "output.dat";
    std::ofstream saida(nomeArquivoSaida, std::ios::app);

    if(!saida){
        std::cerr << "Erro: falha ao abrir o arquivo de saída: '" << nomeArquivoSaida << "'. Encerrando o programa." << std::endl;
        exit(0);
    }
    
    while(!matriz.verificaParadaFloresta() && !matriz.verificaParadaIteracao() && !animal.estaPreso(matriz.getLinhaAnimal(), matriz.getColunaAnimal())){
        for(int i = 0; i < numLinha; i++){
            for(int j = 0; j < numColuna; j++){
                if(matriz.getMatriz()[i][j]->getTipo() == '2'){
                    addArvoresFogo(std::make_pair(i, j));
                    addArvoresQueimadas(std::make_pair(i, j));
                }
            }
        }
        animal.iniciarJogo();
        viraFogo(getArvoresFogo(), config.getDirecaoVentoTodos(), config.getDirecaoVentoNorte(), config.getDirecaoVentoLeste(), config.getDirecaoVentoSul(), config.getDirecaoVentoOeste());
        viraQueimada(getArvoresQueimadas());
        getArvoresFogo().clear();
        getArvoresQueimadas().clear();
    }
    
    matriz.registraResumo();
}

void Incendio::viraQueimada(std::vector<std::pair<int, int>> arvoresQueimadas){
    auto mapa = matriz.getMatriz();

    for(std::pair<int, int> arvore : arvoresQueimadas){
        int linha = arvore.first;
        int coluna = arvore.second;

        mapa[linha][coluna]->setTipo('3');
    }
}

std::vector<std::pair<int, int>> Incendio::getArvoresFogo(){
    return arvoresFogo;
}

void Incendio::addArvoresFogo(std::pair<int, int> arvoreFogo){
    arvoresFogo.push_back(arvoreFogo);
}

std::vector<std::pair<int, int>> Incendio::getArvoresQueimadas(){
    return arvoresQueimadas;
}

void Incendio::addArvoresQueimadas(std::pair<int, int> arvoreQueimada){
    arvoresQueimadas.push_back(arvoreQueimada);
}