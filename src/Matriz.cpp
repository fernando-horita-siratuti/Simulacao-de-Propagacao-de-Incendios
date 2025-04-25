#include "Matriz.hpp"
#include <vector>
#include <iostream>
#include <stdlib.h>
#include <fstream>

Matriz::Matriz(int linhas, int colunas, Config config) : linhas(linhas), colunas(colunas), config(config){
    matriz.resize(linhas, std::vector<Modulo*>(colunas, nullptr));
}

void Matriz::addModulo(int linha, int coluna, char modulo){
    if(modulo == '0'){
        matriz[linha][coluna] = new ModuloAreaVazia(modulo);
    } 
    else if(modulo == '1'){
        matriz[linha][coluna] = new ModuloArvoreSaudavel(modulo);
    }
    else if(modulo == '2'){
        matriz[linha][coluna] = new ModuloArvoreFogo(modulo);
    }
    else if(modulo == '3'){
        matriz[linha][coluna] = new ModuloArvoreQueimada(modulo);
    }
    else{
        matriz[linha][coluna] = new ModuloAgua(modulo);
    }
}

std::vector<std::vector<Modulo*>> Matriz::getMatriz(){
    return matriz;
}

void Matriz::imprimirMatriz(){
    std::string nomeArquivoSaida = "output.dat";
    std::ofstream saida(nomeArquivoSaida, std::ios::app);
    bool pegouFogo = false;

    if(!saida){
        std::cerr << "Erro: falha ao abrir o arquivo de saída: '" << nomeArquivoSaida << "'. Encerrando o programa." << std::endl;
        return;
    }

    saida << "Iteração " << config.getVezesRodadas() << ":\n";
    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            if(i == linhaAnimal && j == colunaAnimal){
                if(matriz[i][j]->getTipo() == '2'){
                    if(i - 1 >= 0){
                        if(matriz[i - 1][j]->getTipo() == '1'){
                            setLinhaAnimal(i - 1);
                            addCaminho(i - 1, j);
                            saida << matriz[i][j]->getTipo() << " ";
                            pegouFogo = true;
                            continue;
                        }
                    }
                    if(j + 1 < colunas){
                        if(matriz[i][j + 1]->getTipo() == '1'){
                            setColunaAnimal(j + 1);
                            addCaminho(i, j + 1);
                            saida << matriz[i][j]->getTipo() << " ";
                            pegouFogo = true;
                            continue;
                        }
                    }
                    if(i + 1 < linhas){
                        if(matriz[i + 1][j]->getTipo() == '1'){
                            setLinhaAnimal(i + 1);
                            addCaminho(i + 1, j);
                            saida << matriz[i][j]->getTipo() << " ";
                            pegouFogo = true;
                            continue;
                        }
                    }
                    if(j - 1 >= 0){
                        if(matriz[i][j - 1]->getTipo() == '1'){
                            setColunaAnimal(j - 1);
                            addCaminho(i, j - 1);
                            saida << matriz[i][j]->getTipo() << " ";
                            pegouFogo = true;
                            continue;
                        }
                    }
                }
                else{
                    saida << "A ";
                }
            }
            else{
                saida << matriz[i][j]->getTipo() << " ";
            }
        }
        saida << "\n";
    }
    if(pegouFogo){
        saida << "O animal pegou fogo! Teletransporte ativado, posição teletransportada: (" << linhaAnimal << ", " << colunaAnimal << ").\n";
        saida.flush();
    }
    saida << "\n";
    config.addVezesRodadas();

    saida.flush();
    saida.close();
}

bool Matriz::verificaParadaFloresta(){
    auto mapa = getMatriz();
    int qntLinhas = getLinhas();
    int qntColunas = getColunas();
    bool todos = config.getDirecaoVentoTodos();
    bool norte = config.getDirecaoVentoNorte();
    bool leste = config.getDirecaoVentoLeste();
    bool sul = config.getDirecaoVentoSul();
    bool oeste = config.getDirecaoVentoOeste();
    std::string nomeArquivoSaida = "output.dat";
    std::ofstream saida(nomeArquivoSaida, std::ios::app);

    if(!saida){
        std::cerr << "Erro: falha ao abrir o arquivo de saída: '" << nomeArquivoSaida << "'. Encerrando o programa." << std::endl;
        exit(0);
    }

    for(int i = 0; i < linhas; i++){
        for(int j = 0; j < colunas; j++){
            if(mapa[i][j]->getTipo() == '1' || (i == linhaAnimal && j == colunaAnimal)){
                if(i - 1 >= 0 && mapa[i - 1][j]->getTipo() == '2' && (norte || todos)){
                    return false;
                }
                if(j + 1 < qntColunas && mapa[i][j + 1]->getTipo() == '2' && (leste || todos)){
                    return false;
                }
                if(i + 1 < qntLinhas && mapa[i + 1][j]->getTipo() == '2' && (sul || todos)){
                    return false;
                }
                if(j - 1 >= 0 && mapa[i][j - 1]->getTipo() == '2' && (oeste || todos)){
                    return false;
                }
            }
        }
    }
    return true;
}

bool Matriz::verificaParadaIteracao(){
    std::string nomeArquivoSaida = "output.dat";
    std::ofstream saida(nomeArquivoSaida, std::ios::app);

    if(!saida){
        std::cerr << "Erro: falha ao abrir o arquivo de saída: '" << nomeArquivoSaida << "'. Encerrando o programa." << std::endl;
        exit(0);
    }

    if(config.getVezesRodadas() == config.getQntIteracoes() + 1){
        return true;
    }
    return false;
}

void Matriz::registraResumo(){ 
    std::string nomeArquivoSaida = "output.dat";
    std::ofstream saida(nomeArquivoSaida, std::ios::app);
    bool estaMorto = false;

    if(!saida){
        std::cerr << "Erro: falha ao abrir o arquivo de saída: '" << nomeArquivoSaida << "'. Encerrando o programa." << std::endl;
        exit(0);
    }
    
    if(verificaParadaFloresta()){
        saida << "Não há mais árvores a serem queimadas. Fim do jogo.\n\n";
        saida.flush();
    }
    else if(verificaParadaIteracao()){
        saida << "Quantidade máxima de interações atingida. Fim do jogo.\n\n";
        saida.flush();
    }
    else{
        saida << "Animal pegou fogo. Fim do jogo.\n\n";
        estaMorto = true;
        saida.flush();
    }
    saida << "- - - - - Resumo geral: - - - - -\n\n";
    saida.flush();
    saida << "- Pontos de água encontrados: " << aguasEncontradas << ".\n";
    saida.flush();
    saida << "- Passos dados: " << passos << ".\n";
    saida.flush();
    if(config.getVezesRodadas() - 1 == 1 && estaMorto){
        saida << "- Animal pegou fogo na " << config.getVezesRodadas() - 1 << "ª iteração.\n";
        saida.flush();
        saida << "- Status do animal: morto.";
        saida.flush();
    }
    else if(config.getVezesRodadas() - 1 == 1 && !estaMorto){
        saida << "- Status do animal: vivo.";
        saida.flush();
    }
    else{
        int cont = 1;

        for(int i = 0; i < config.getVezesRodadas() - 1; i++){
            bool naoSeMoveu = false;

            saida << "- Caminho feito na " << i + 1 << "ª iteração: ";
            for(int iteracao : naoMoveu){
                if(i + 1 == iteracao){
                    saida << "Animal não se moveu na " << i + 1 << "ª iteração.\n";
                    saida.flush();
                    naoSeMoveu = true;
                    break;
                }
            }
            if(naoSeMoveu){
                continue;
            }
            if(cont != 0){
                saida << "(" << caminho[cont - 1].first << ", " << caminho[cont - 1].second << ") -> ";
                saida.flush();
            }
            while(cont + 1 < (int)caminho.size() && (caminho[cont - 1].first != caminho[cont].first || caminho[cont - 1].second != caminho[cont].second)){
                saida << "(" << caminho[cont].first << ", " << caminho[cont].second << ") -> ";
                saida.flush();
                cont++;
            }
            if((i + 2 == naoMoveu[naoMoveu.size() - 1] && naoMoveu[naoMoveu.size() - 1] == config.getVezesRodadas() - 1) || (i + 3 == naoMoveu[naoMoveu.size() - 1] && naoMoveu[naoMoveu.size() - 1] == config.getVezesRodadas() - 1)){
                saida << "(" << linhaAnimal << ", " << colunaAnimal << ") -> ";
                saida.flush();
            }
            if(i + 1 == config.getVezesRodadas() - 1){
                saida << "(" << linhaAnimal << ", " << colunaAnimal << ") -> ";
                saida.flush();
            }
            saida << "Fim da iteração " << i + 1 << "\n";
            saida.flush();
            cont++;
        }
        if(estaMorto){
            saida << "- Animal pegou fogo na " << config.getVezesRodadas() - 1 << "ª iteração.\n";
            saida.flush();
            saida << "- Status do animal: morto.\n";
            saida.flush();
        }
        else{
            saida << "- Status do animal: vivo.\n";
            saida.flush();
        }
        saida << "(Coordenadas em formato de '(linha, coluna)')\n";
    }
    saida.flush();
    saida.close();
    naoMoveu.clear();
    caminho.clear();
    exit(0);
}

// bool Matriz::podeIr(int linha, int coluna, bool todos, bool norte, bool leste, bool sul, bool oeste){
//     auto mapa = getMatriz();
//     int qntLinhas = getLinhas();
//     int qntColunas = getColunas();

//     if(linha - 1 >= 0 && mapa[linha - 1][coluna]->getTipo() == '1' && (norte || todos)){
//         return false;
//     }
//     if(coluna + 1 < qntColunas && mapa[linha][coluna + 1]->getTipo() == '1' && (leste || todos)){
//         return false;
//     }
//     if(linha + 1 < qntLinhas && mapa[linha + 1][coluna]->getTipo() == '1' && (sul || todos)){
//         return false;
//     }
//     if(coluna - 1 >= 0 && mapa[linha][coluna - 1]->getTipo() == '1' && (oeste || todos)){
//         return false;
//     }
//     return true;
// }

int Matriz::getLinhas(){
    return linhas;
}

int Matriz::getColunas(){
    return colunas;
}

int Matriz::getLinhaAnimal(){
    return linhaAnimal;
}

int Matriz::getColunaAnimal(){
    return colunaAnimal;
}

short Matriz::addAguasEncontradas(){
    return aguasEncontradas++;
}

void Matriz::setPassos(int passosAtualizados){
    passos += passosAtualizados;
}

void Matriz::setLinhaAnimal(int linhaAnimalNova){
    this->linhaAnimal = linhaAnimalNova;
}

void Matriz::setColunaAnimal(int colunaAnimalNova){
    this->colunaAnimal = colunaAnimalNova;
}

void Matriz::addCaminho(int linha, int coluna){
    caminho.push_back({linha, coluna});
}

void Matriz::addNaoMoveu(int iteracao){
    naoMoveu.push_back(iteracao);
}