#include "Arquivo.hpp"
#include "Matriz.hpp"
#include "Incendio.hpp"
#include "Config.hpp"
#include "Animal.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <sstream>

Arquivo::Arquivo(std::string nomeArq, Config config) : nomeArq(nomeArq), config(config){}

void Arquivo::lerArq(Arquivo arq){
    int numLinha, numColuna, colunaIncendio, linhaIncendio, linha = 0, coluna = 0, fogo = 0, linhasLidas = 0, spaceBar = 0, lugarSeguro = 0, colunaAnimal = 0, linhaAnimal = 0;
    std::string linhaLeitura, nomeArquivo = arq.getNome(), nomeArquivoSaida = "./dataset/output.dat";
    std::ifstream entrada(nomeArquivo);
    std::ofstream saida(nomeArquivoSaida, std::ios::app);
    
    if(!entrada){
        std::cerr << "Erro: falha ao abrir o arquivo de entrada: '" << nomeArquivo << "'. Encerrando o programa.";
        exit(0);
    }
    
    if(config.getDirecaoVentoTodos() && (config.getDirecaoVentoNorte() || config.getDirecaoVentoLeste() || config.getDirecaoVentoSul() || config.getDirecaoVentoOeste())){
        saida << "Erro: vento para todas as direções não pode ser ativado simultaneamente com os outros tipos de direção. Encerrando o programa.";
        saida.flush();
        saida.close();
        exit(0);    
    }

    entrada >> numLinha >> numColuna >> linhaIncendio >> colunaIncendio;
    Matriz matriz(numLinha, numColuna, config);
    
    std::getline(entrada, linhaLeitura);
    
    while(std::getline(entrada, linhaLeitura)){
        if(linhasLidas >= numLinha){
            saida << "Erro: mais linhas encontradas do que o especificado em " << nomeArquivo << ". Encerrando o programa.";
            return;
        }
        for(char ch : linhaLeitura){
            if(ch == ' '){
                spaceBar++;
            }
        }
        if((int)linhaLeitura.length() - spaceBar != numColuna){
            saida << "Erro: número de colunas incorreto na linha " << linhasLidas + 2 << " do arquivo " << nomeArquivo << ". Encerrando o programa.";
            return;
        }
        spaceBar = 0;
        for(char ch : linhaLeitura){
            if(ch == '\n' || ch == ' '){
                continue;
            }
            else if(ch == '2'){
                fogo++;
                if(fogo > 1){
                    saida << "Erro: mais de um ponto de incêndio registrado na matriz. Encerrando o programa.";
                    return;
                }
                if(linha != linhaIncendio || coluna != colunaIncendio){
                    saida << "Erro: ponto de incêndio registrado em (" << linhasLidas << ", " << coluna << ") não condiz com a posição previamente cadastrada. Encerrando o programa.";
                    return;
                }
            }
            else if(ch == '0'){
                lugarSeguro++;
                if(lugarSeguro == 1){
                    linhaAnimal = linhasLidas;
                    colunaAnimal = coluna;
                }
            }
            else if(ch != '0' && ch != '1' && ch != '2' && ch != '4'){
                saida << "Erro: caractere inválido em (" << linhasLidas << ", " << coluna << ") do arquivo " << nomeArquivo << ". Encerrando o programa.";
                return;
            }
            matriz.addModulo(linha, coluna, ch);
            coluna++;
            if(coluna == numColuna){
                coluna = 0;
                linha++;
            }
        }
        linhasLidas++;
    }
    if(linhasLidas != numLinha){
        saida << "Erro: número de linhas lido diferente do especificado no arquivo " << nomeArquivo << ". Encerrando o programa.";
        return;
    }
    if(fogo == 0){
        saida << "Erro: nenhum ponto de incêndio foi registrado na matriz. Encerrando o programa.";
        return;
    }
    if(lugarSeguro == 0){
        saida << "Erro: nenhum lugar seguro foi registrado na matriz. Encerrando o programa.";
        return;
    }
    Animal animal(linhaAnimal, colunaAnimal, matriz, config);
    Incendio incendio(linhaIncendio, colunaIncendio, matriz, animal);
    incendio.espalharFogo(config);
    
    entrada.close();
    saida.flush();
    saida.close();
    
    return;
}

std::string Arquivo::getNome(){
    return nomeArq;
}