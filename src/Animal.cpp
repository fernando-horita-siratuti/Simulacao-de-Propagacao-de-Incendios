#include "Animal.hpp"
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>

Animal::Animal(int linhaAnimal, int colunaAnimal, Matriz& matriz, Config config) : linhaAnimal(linhaAnimal), colunaAnimal(colunaAnimal), matriz(matriz), config(config){}

int Animal::animalNoZero = 1;  

void Animal::iniciarJogo(){ 
    if(getAnimalNoZero() == 0){
        config.addVezesRodadas();
        setPosicao(matriz.getLinhaAnimal(), matriz.getColunaAnimal());
        if(buscarAgua()){
            return;
        }
        if(buscarVazioArvoreSaudavel()){
            return;
        }
        if(buscarArvoreQueimada()){
            return;
        }
    }
    if(config.getVezesRodadas() != 1){
        addAnimalNoZero();
    }
    if(getAnimalNoZero() == 3){
        this->animalNoZero = 0;
    }
    matriz.setLinhaAnimal(this->linhaAnimal);
    matriz.setColunaAnimal(this->colunaAnimal);
    matriz.addNaoMoveu(config.getVezesRodadas());
    config.addVezesRodadas();
}

bool Animal::buscarAgua(){
    int linhas = matriz.getLinhas();
    int colunas = matriz.getColunas();
    int iniLinha = this->linhaAnimal;
    int iniColuna = this->colunaAnimal;
    auto mapa = matriz.getMatriz();
    bool encontrado = false;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while(true){
        std::vector<Posicao> caminho = {};
        std::vector<std::vector<Posicao>> anterior(linhas, std::vector<Posicao>(colunas, {-1, -1}));
        std::vector<std::vector<bool>> visitado(linhas, std::vector<bool>(colunas, false));
        std::queue<std::pair<int, int>> fila;

        fila.push({iniLinha, iniColuna});
        visitado[iniLinha][iniColuna] = true;
        Posicao destino = {-1, -1};

        while(!fila.empty() && !encontrado){
            int linha = fila.front().first;
            int coluna = fila.front().second;
            int nx, ny;
            fila.pop();

            if(mapa[linha][coluna]->getTipo() == '4'){
                mapa[linha][coluna]->setTipo('0');
                addAnimalNoZero();
                jogaUmidade(linha, coluna);
                matriz.setLinhaAnimal(linha);
                matriz.setColunaAnimal(coluna);
                setPosicao(matriz.getLinhaAnimal(), matriz.getColunaAnimal());
                destino = {linha, coluna};
                for(Posicao p = destino; p.x != -1 && p.y != -1; p = anterior[p.x][p.y]){
                    caminho.push_back(p);
                }
                std::reverse(caminho.begin(), caminho.end());
                for(Posicao p : caminho){
                    matriz.addCaminho(p.x, p.y);
                }
                if(caminho.size() > 1){
                    matriz.setPassos(caminho.size() - 1);
                }
                caminho.clear();
                matriz.addAguasEncontradas();
                
                return true;
            }

            for(int i = 0; i < 4; i++){ 
                nx = linha + dx[i];
                ny = coluna + dy[i];
                
                if(nx >= 0 && nx < linhas && ny >= 0 && ny < colunas && !visitado[nx][ny]){
                    char tipo = mapa[nx][ny]->getTipo();
                    if(tipo != '2'){
                        visitado[nx][ny] = true;
                        anterior[nx][ny] = {linha, coluna};
                        fila.push({nx, ny});
                    }
                }
            }
        }
        return false;
    } 
}

bool Animal::buscarVazioArvoreSaudavel(){
    int linhas = matriz.getLinhas();
    int colunas = matriz.getColunas();
    int iniLinha = this->linhaAnimal;
    int iniColuna = this->colunaAnimal;
    auto mapa = matriz.getMatriz();
    bool encontrado = false;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while(true){
        std::vector<Posicao> caminho = {};
        std::vector<std::vector<Posicao>> anterior(linhas, std::vector<Posicao>(colunas, {-1, -1}));
        std::vector<std::vector<bool>> visitado(linhas, std::vector<bool>(colunas, false));
        std::queue<std::pair<int, int>> fila;

        fila.push({iniLinha, iniColuna});
        visitado[iniLinha][iniColuna] = true;
        Posicao destino = {-1, -1};

        while(!fila.empty() && !encontrado){
            int linha = fila.front().first;
            int coluna = fila.front().second;
            int nx, ny;
            fila.pop();

            if(mapa[linha][coluna]->getTipo() == '0' && linha != iniLinha && coluna != iniColuna){
                addAnimalNoZero();
                matriz.setLinhaAnimal(linha);
                matriz.setColunaAnimal(coluna);
                setPosicao(matriz.getLinhaAnimal(), matriz.getColunaAnimal());
                destino = {linha, coluna};
                for(Posicao p = destino; p.x != -1 && p.y != -1; p = anterior[p.x][p.y]){
                    caminho.push_back(p);
                }
                std::reverse(caminho.begin(), caminho.end());
                for(Posicao p : caminho){
                    matriz.addCaminho(p.x, p.y);
                }
                if(caminho.size() > 1){
                    matriz.setPassos(caminho.size() - 1);
                }
                caminho.clear();
                
                return true;
            }
            else if(mapa[linha][coluna]->getTipo() == '1' && linha != iniLinha && coluna != iniColuna){
                matriz.setLinhaAnimal(linha);
                matriz.setColunaAnimal(coluna);
                setPosicao(matriz.getLinhaAnimal(), matriz.getColunaAnimal());
                destino = {linha, coluna};
                for(Posicao p = destino; p.x != -1 && p.y != -1; p = anterior[p.x][p.y]){
                    caminho.push_back(p);
                }
                std::reverse(caminho.begin(), caminho.end());
                for(Posicao p : caminho){
                    matriz.addCaminho(p.x, p.y);
                }
                if(caminho.size() > 1){
                    matriz.setPassos(caminho.size() - 1);
                }
                caminho.clear();
                
                return true;
            }

            for(int i = 0; i < 4; i++){ 
                nx = linha + dx[i];
                ny = coluna + dy[i];
                
                if(nx >= 0 && nx < linhas && ny >= 0 && ny < colunas && !visitado[nx][ny]){
                    char tipo = mapa[nx][ny]->getTipo();
                    if(tipo != '2'){
                        visitado[nx][ny] = true;
                        anterior[nx][ny] = {linha, coluna};
                        fila.push({nx, ny});
                    }
                }
            }
        }
        return false;
    }
}

bool Animal::buscarArvoreQueimada(){
    int linhas = matriz.getLinhas();
    int colunas = matriz.getColunas();
    int iniLinha = this->linhaAnimal;
    int iniColuna = this->colunaAnimal;
    auto mapa = matriz.getMatriz();
    bool encontrado = false;
    int dx[] = {-1, 1, 0, 0};
    int dy[] = {0, 0, -1, 1};

    while(true){
        std::vector<Posicao> caminho = {};
        std::vector<std::vector<Posicao>> anterior(linhas, std::vector<Posicao>(colunas, {-1, -1}));
        std::vector<std::vector<bool>> visitado(linhas, std::vector<bool>(colunas, false));
        std::queue<std::pair<int, int>> fila;

        fila.push({iniLinha, iniColuna});
        visitado[iniLinha][iniColuna] = true;
        Posicao destino = {-1, -1};

        while(!fila.empty() && !encontrado){
            int linha = fila.front().first;
            int coluna = fila.front().second;
            int nx, ny;
            fila.pop();

            if(mapa[linha][coluna]->getTipo() == '3' && linha != iniLinha && coluna != iniColuna){
                matriz.setLinhaAnimal(linha);
                matriz.setColunaAnimal(coluna);
                setPosicao(matriz.getLinhaAnimal(), matriz.getColunaAnimal());
                destino = {linha, coluna};
                for(Posicao p = destino; p.x != -1 && p.y != -1; p = anterior[p.x][p.y]){
                    caminho.push_back(p);
                }
                std::reverse(caminho.begin(), caminho.end());
                for(Posicao p : caminho){
                    matriz.addCaminho(p.x, p.y);
                }
                if(caminho.size() > 1){
                    matriz.setPassos(caminho.size() - 1);
                }
                caminho.clear();
                
                return true;
            }

            for(int i = 0; i < 4; i++){ 
                nx = linha + dx[i];
                ny = coluna + dy[i];
                
                if(nx >= 0 && nx < linhas && ny >= 0 && ny < colunas && !visitado[nx][ny]){
                    char tipo = mapa[nx][ny]->getTipo();
                    if(tipo != '2'){
                        visitado[nx][ny] = true;
                        anterior[nx][ny] = {linha, coluna};
                        fila.push({nx, ny});
                    }
                }
            }
        }
        return false;
    }
}

void Animal::jogaUmidade(int linha, int coluna){
    auto mapa = matriz.getMatriz();
    int qntLinhas = matriz.getLinhas();
    int qntColunas = matriz.getColunas();

    if(linha - 1 >= 0){
        mapa[linha - 1][coluna]->setTipo('1');
    }
    if(coluna + 1 < qntColunas){
        mapa[linha][coluna + 1]->setTipo('1');
    }
    if(linha + 1 < qntLinhas){
        mapa[linha + 1][coluna]->setTipo('1');
    }
    if(coluna - 1 >= 0){
        mapa[linha][coluna - 1]->setTipo('1');
    }
}
bool Animal::estaPreso(int linha, int coluna){
    auto mapa = matriz.getMatriz();
    int linhas = matriz.getLinhas();
    int colunas = matriz.getColunas();
    int vizinhosValidos = 0;

    for(int i = 0; i < 4; i++){
        int l = linha;
        int c = coluna;

        if(i == 0){
            l--;
        } 
        else if(i == 1){
            l++;
        } 
        else if(i == 2){
            c--;
        } 
        else{
            c++;
        }

        if(l < 0 || l >= linhas || c < 0 || c >= colunas){
            continue;
        }
        vizinhosValidos++;
        if(mapa[l][c]->getTipo() != '2'){
            return false;
        }
    }

    return vizinhosValidos > 0;
}

void Animal::setPosicao(int linha, int coluna){
    this->linhaAnimal = linha;
    this->colunaAnimal = coluna;
}

int Animal::getAnimalNoZero(){
    return animalNoZero;
}

void Animal::addAnimalNoZero(){
    this->animalNoZero += 1;
}

int Animal::getLinha(){
    return this->linhaAnimal;
}

int Animal::getColuna(){
    return this->colunaAnimal;
}
