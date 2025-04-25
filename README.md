
# 📄 README - PROJETO DE SIMLUAÇÃO DE PROPAGAÇÃO DE INCÊNCIOS

<div align="center">
    <img src="thisIsFine.jpg" width="200" height="200">
</div>

<div align="center">

##  Simulação de Propagação de Incêndios

</div>

## ☕ Introdução
O projeto "Simulação de Propagação de Incêndios" foi proposto como o trabalho de aquecimento da disciplina de Algoritmo e Estrutura de Dados (AEDS) pelo Prof. Mestre Michel Pires Da Silva. Tal atividade propôs a criação de um código (em C ou C++) que possa implementar tal simulação e também exigiu uma documentação detalhada sobre o algoritmo. Ademais, o código consiste em um simulador que propaga um incêndio em uma floresta, uma matriz, na qual há um animal que deve se mover por ela. Além disso, cada célula da matriz tem sua devida representação, sendo 0: Área vazia, 1: Árvore saudável, 2: Árvore em chamas, 3: Árvore queimada e 4: Água.

## 🎯 Objetivos
O objetivo principal consiste em modelar a propagação do fogo em uma matriz, o qual pode evoluir ao longo da execução, conforme as interações de propagação de incêndio. A implementação deverá permitir a utilização de diferentes estratégias computacionais para a propagação do fogo, proporcionando uma análise comparativa do desempenho e da eficiência do código.


## 🖥️ Ambiente de Criação
- ![C++](https://img.shields.io/badge/Linguagem-C++-blue?logo=c%2B%2B&logoColor=white)
- ![VS Code](https://img.shields.io/badge/IDE-VS%20Code-007ACC?logo=visual-studio-code&logoColor=white)
- ![Ubuntu](https://img.shields.io/badge/SO-Ubuntu%20(WSL)-E95420?logo=ubuntu&logoColor=white)

O trabalho inteiro foi feito em C++. Além do mais, a IDE utilizada foi o Visual Studio Code (VS Code), no qual foi utilizado o ambiente de desenvolvimento WSL Ubuntu. No entanto, o sistema operacional principal utilizado foi o Windows.

## 📂 Organização dos Arquivos
Os arquivos de entrada e saída (input.dat e output.dat, respectivamente) estão na pasta "AEDS", juntamente com o Makefile, já os arquivos cpp e hpp estão em uma subpasta chamada "src" dentro da pasta "AEDS".
```
AEDS/
├── .vscode/
├── build/
├── src/
│   ├── Animal.cpp
│   ├── Animal.hpp
│   ├── Arquivo.cpp
│   ├── Arquivo.hpp
│   ├── Config.cpp
│   ├── Config.hpp
│   ├── Incendio.cpp
│   ├── Incendio.hpp
│   ├── Main.cpp
│   ├── Matriz.cpp
│   ├── Matriz.hpp
│   ├── Modulo.cpp
│   ├── Modulo.hpp
│   ├── ModuloAgua.cpp
│   ├── ModuloAgua.hpp
│   ├── ModuloAreaVazia.cpp
│   ├── ModuloAreaVazia.hpp
│   ├── ModuloArvoreFogo.cpp
│   ├── ModuloArvoreFogo.hpp
│   ├── ModuloArvoreQueimada.cpp
│   ├── ModuloArvoreQueimada.hpp
│   ├── ModuloArvoreSaudavel.cpp
│   ├── ModuloArvoreSaudavel.hpp
├── dataset/
|   ├── input.dat
│   ├── output.dat
├── Makefile
├── Makefile :Zone.Identifier
```

## 💡 Implementação
### Funções:
## - [`lerArq (Tipo: void, Parâmetro: Arquivo arquivo)`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Arquivo.cpp#L15-L109)  
    
    Essa função é responsável por ler o arquivo de entrada contendo os dados da matriz. A leitura e a validação do conteúdo do arquivo são fundamentais para a inicialização correta dos objetos da simulação.

#### 📁 Formato esperado do arquivo
- Primeira linha: `N M linha coluna`, onde:
  - `N`: número de linhas da matriz.
  - `M`: número de colunas da matriz.
  - `linha`: linha onde o incêndio começa (iniciando em 0).
  - `coluna`: coluna onde o incêndio começa (iniciando em 0).
- Linhas seguintes: N linhas com M colunas separadas por espaços, contendo valores de `0` a `4`:
  - `0`: área vazia (onde o animal pode começar).
  - `1`: árvore saudável.
  - `2`: início do fogo (**deve haver apenas um**).
  - `3`: árvore queimada (aparece posteriormente na matriz).
  - `4`: ponto de água.

#### ✅ Validações realizadas
- Verifica se o arquivo de entrada foi aberto corretamente.
- Garante que a direção do vento não seja definida como "todas as direções" ao mesmo tempo que direções específicas.
- Confirma que a quantidade de linhas e colunas corresponde ao valor declarado.
- Verifica se existe **apenas um ponto de fogo (`2`)** e se ele está na coordenada indicada no início do arquivo.
- Verifica se existe pelo menos **um local seguro (`0`)** para posicionar o animal.
- Garante que todos os caracteres da matriz sejam válidos (`0`, `1`, `2` e `4`).
- Registra mensagens de erro detalhadas no arquivo `./dataset/output.dat` e encerra o programa em caso de falhas.

#### ⚙️ Processos após a leitura
- Inicializa o objeto `Matriz` com os dados validados.
- Posiciona o `Animal` no primeiro `0` encontrado.
- Inicializa o objeto `Incendio` com a posição inicial do fogo.
- Chama [`incendio.espalharFogo(config)`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Incendio.cpp#L39-L61) para iniciar a simulação da propagação do incêndio.

## - [`addModulo(int linha, int coluna, char modulo)`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Matriz.cpp#L11-L27)

### Função `Matriz::addModulo(int linha, int coluna, char modulo)`

    Essa função é responsável por inserir dinamicamente um objeto do tipo `Modulo` na matriz de simulação com base no caractere lido do arquivo de entrada. Cada caractere representa um tipo diferente de célula.

#### 🧠 Funcionamento
De acordo com o caractere fornecido (`modulo`), a função cria dinamicamente o objeto correspondente e o armazena na posição `[linha][coluna]` da matriz.

#### 🔤 Tipos de módulos aceitos
| Caractere | Tipo de Módulo              | Descrição                                  |
|-----------|------------------------------|--------------------------------------------|
| `'0'`     | `ModuloAreaVazia`            | Representa uma área vazia.        |
| `'1'`     | `ModuloArvoreSaudavel`       | Representa uma árvore saudável.            |
| `'2'`     | `ModuloArvoreFogo`           | Representa uma árvore em chamas.    |
| `'3'`     | `ModuloArvoreQueimada`       | Representa uma árvore que já queimou.      |
| `4` | `ModuloAgua`            | Representa um ponto d'água.    |

## - [`imprimirMatriz (Tipo: void)`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Matriz.cpp#L33-L101)  

    Essa função é responsável por imprimir o estado atual da matriz da simulação no arquivo de saída a cada iteração da propagação do incêndio. Além disso, ela verifica se o animal foi atingido pelo fogo e, se necessário, executa um "teletransporte" para mantê-lo vivo.

#### 🧠 Funcionamento
- Verifica se o animal está sobre uma célula em chamas (`'2'`).
- Se estiver, tenta movê-lo automaticamente para uma das células adjacentes (`cima`, `direita`, `baixo`, `esquerda`) que seja segura (`'1'`).
- Se uma movimentação for realizada, a posição do animal é atualizada e o caminho percorrido é registrado no fim do arquivo.
- Após percorrer toda a matriz, imprime o estado atual da simulação.
- Ao final, registra se o animal foi "teletransportado" por ter sido atingido pelo fogo.

#### 📝 Saída gerada
- Cada iteração é precedida por um cabeçalho, onde `N` representa o número da rodada atual da simulação.
- A matriz é impressa com os tipos de cada célula (`0`, `1`, `2`, `3`, `4`), separadas por espaços.
- Se o animal for atingido pelo fogo, uma mensagem como a seguinte é adicionada: "O animal pegou fogo! Teletransporte ativado, posição teletransportada: (linha, coluna)."

#### ⚙️ Observações
- O número da iteração é obtido por meio de [`config.getVezesRodadas()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Config.cpp#L45-L47) e incrementado com [`config.addVezesRodadas()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Config.cpp#L49-L51).
- A função também atualiza internamente o caminho do animal via [`addCaminho(int linha, int coluna)`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Matriz.cpp#L271-L273).
- Caso o arquivo de saída não possa ser aberto, um erro é exibido no `std::cerr` e a execução da função é interrompida.
    
## - [`verificaParadaFloresta (Tipo: bool)`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Matriz.cpp#L103-L132)  

    Essa função verifica se a simulação do incêndio pode ser encerrada, ou seja, se o fogo não tem mais para onde se espalhar, considerando as direções permitidas pelo vento.

#### 🧠 Funcionamento
- Itera por toda a matriz.
- Para cada célula que contenha uma árvore saudável (`'1'`) ou a posição atual do animal:
  - Verifica as **quatro direções adjacentes**.
  - Se houver uma célula em chamas (`'2'`) em uma direção na qual o vento permite a propagação, a simulação **ainda deve continuar**.
- Se nenhuma propagação possível for detectada, a simulação pode parar.

#### 💨 Direções do vento
A propagação do fogo depende das configurações do vento definidas na classe `config.cpp`:
- [`config.getDirecaoVentoTodos()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Config.cpp#L6-L11)
- [`config.getDirecaoVentoNorte()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Config.cpp#L13-L18)
- [`config.getDirecaoVentoSul()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Config.cpp#L20-L25)
- [`config.getDirecaoVentoLeste()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Config.cpp#L27-L32)
- [`config.getDirecaoVentoOeste()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Config.cpp#L34-L39)

#### 🔁 Retorno
- `true`: o fogo não pode mais se espalhar (simulação encerra).
- `false`: ainda é possível que o fogo se propague (simulação continua).

#### ⚙️ Observação
- A verificação de limites da matriz é feita corretamente para evitar acessos inválidos.

## - [`verificaParadaIteracao (Tipo: bool)`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Matriz.cpp#L134-L139)  

    Essa função verifica se a quantidade máxima de iterações da simulação foi atingida.

#### 🧠 Funcionamento
- Compara o número atual de iterações realizadas ([`config.getVezesRodadas()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Config.cpp#L45-L47)) com o limite máximo permitido ([`config.getQntIteracoes()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Config.cpp#L41-L43)).

#### 🔁 Retorno
- `true`: o número máximo de iterações foi alcançado (simulação encerra).
- `false`: ainda há iterações restantes para executar (simulação continua).

#### ⚙️ Observações
- O controle de iterações é feito inteiramente a partir da estrutura `config`, que armazena a contagem e o limite.

## - [`registraResumo (Tipo: void)`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Matriz.cpp#L141-L236)  

    Essa função gera e escreve um resumo detalhado sobre a simulação no arquivo de saída. Ela fornece informações sobre o estado do jogo, o status do animal, o caminho percorrido e outros detalhes relevantes após o término da simulação.

#### 🧠 Funcionamento
1. **Verificação de Terminação**: A função verifica se a simulação terminou com base em três critérios:
   - **Fim do incêndio**: Não há mais árvores a serem queimadas.
   - **Limite de iterações**: A quantidade máxima de iterações foi atingida.
   - **Animal morto**: O animal foi cercado pelo fogo durante a simulação.
   
2. **Registro de Resumo**: Após verificar as condições de parada, a função escreve um resumo no arquivo de saída, incluindo:
   - O número de pontos de água encontrados.
   - O número de passos dados pelo animal.
   - O caminho percorrido pelo animal durante cada iteração.
   - A iteração em que o animal pegou fogo (se aplicável).
   - O status do animal (vivo ou morto).

3. **Finalização**: Após o resumo ser gerado, o estado das variáveis de caminho e de iterações é limpo, e o programa é encerrado.

#### ⚙️ Observações
- **Arquivo de Saída**: A função abre o arquivo `output.dat` para append, garantindo que o conteúdo seja adicionado ao final sem sobrescrever dados anteriores.
- **Estrutura de Dados**: Utiliza o vetor `caminho` para registrar os passos e a lista `naoMoveu` para indicar se o animal não se moveu durante uma iteração específica.
- **Encerramento**: Após gerar o resumo, a função encerra o programa chamando `exit(0)`.
    
## - [`viraFogo (Tipo: void, Parâmetros: std::vector<std::pair<int, int>> arvoresFogo, bool todos, bool norte, bool leste, bool sul, bool oeste)`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Incendio.cpp#L13-L37)

    Essa função é responsável por espalhar o fogo para as árvores saudáveis ('1') adjacentes às árvores em chamas ('2'), com base nas direções do vento e nas configurações do mapa.

#### 🧠 Funcionamento
1. **Entrada de Dados**:
   - A função recebe uma lista de **arvoresFogo**, que são as coordenadas das árvores que estão em chamas.
   - Recebe também os parâmetros relacionados ao vento: 
     - `todos`: se o vento afeta todas as direções (norte, sul, leste, oeste).
     - `norte`, `leste`, `sul`, `oeste`: indica se o vento afeta essas direções específicas.

2. **Alastramento do Fogo**:
   - Para cada árvore em chamas (nas coordenadas fornecidas em `arvoresFogo`), a função verifica as árvores vizinhas (nas direções especificadas pelo vento):
     - Se a árvore vizinha está saudável ('1') e o vento está permitindo a propagação do fogo naquela direção, a árvore vizinha é convertida para '2'.
   
3. **Atualização do Mapa**:
   - O mapa é atualizado com a propagação do fogo, e a função [`matriz.imprimirMatriz()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Matriz.cpp#L33-L102) é chamada para imprimir as mudanças no arquivo de saída.

## - [`espalharFogo (Tipo: void, Parâmetros: Config config)`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Incendio.cpp#L39-L61)  

    Essa função é responsável por controlar o ciclo do incêndio na floresta, espalhando o fogo e realizando verificações contínuas até que uma das condições de parada seja atendida. Além disso, ela gerencia o movimento do animal e a atualização do mapa após cada iteração.

#### 🧠 Funcionamento
1. **Ciclo de Propagação do Fogo**:
   - A função entra em um loop que continua enquanto nenhuma das condições de parada for atendida:
     - A floresta ainda tem árvores para queimar ([`verificaParadaFloresta()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Matriz.cpp#L104-L133)).
     - A quantidade máxima de iterações não foi alcançada ([`verificaParadaIteracao()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Matriz.cpp#L135-L140)).
     - O animal não está cercado de fogo ([`animal.estaPreso()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Animal.cpp#L276-L309)).
   
2. **Propagação do Fogo**:
   - Para cada célula da matriz, a função verifica se a célula contém uma árvore em chamas ('2').
   - Se sim, adiciona a árvore à lista de árvores em fogo e à lista de árvores a serem queimadas.
   
3. **Movimento do Animal**:
   - Após verificar todas as árvores em fogo, a função chama [`animal.iniciarJogo()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Animal.cpp#L15-L39) para processar o movimento do animal na matriz.
   
4. **Espalhamento do Fogo**:
   - A função [`viraFogo()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Incendio.cpp#L13-L37) é chamada para espalhar o fogo para as árvores vizinhas, com base nas direções do vento especificadas na configuração (`config`).
   
5. **Atualização do estado das Árvores**:
   - Após a propagação do fogo, a função [`viraQueimada()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Incendio.cpp#L63-L72) é chamada para marcar as árvores que foram queimadas.
   
6. **Limpeza das Listas**:
   - Após a iteração, as listas de árvores em fogo e árvores queimadas são limpas para a próxima rodada.

7. **Resumo**:
   - Após o fim do ciclo, a função [`matriz.registraResumo()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Matriz.cpp#L142-L237) é chamada para registrar o resumo final do jogo.

## - [`viraQueimada (Tipo: void, Parâmetros: std::vector<std::pair<int, int>> arvoresQueimadas)`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Incendio.cpp#L63-L72)  
    
    Essa função é responsável por atualizar o estado das árvores que foram queimadas no mapa, alterando o tipo da célula correspondente para indicar que a árvore foi destruída pelo fogo.

#### 🧠 Funcionamento
- A função recebe um vetor de coordenadas (`arvoresQueimadas`) que contém as posições das árvores que foram queimadas.
- Para cada posição no vetor, a função acessa a célula correspondente no mapa e altera seu tipo de '2' para '3', indicando que o fogo destruiu a árvore.
- O tipo da célula é atualizado usando o método `setTipo('3')`, que marca a árvore como queimada.

## - [`iniciarJogo (Tipo: void)`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Animal.cpp#L15-L39)  
    
    Essa função é responsável por gerenciar o ciclo de movimentação e ações do animal durante o jogo. Ela coordena as interações do animal com o ambiente e controla seu progresso através da matriz.

#### 🧠 Funcionamento
1. **Primeira até a Terceira Rodada**:
    - O animal permanece estático, pois se encontra em uma área vazia (célula em que o animal pode permanecer por até 3 iterações)
    - Atualiza a quantidade de rodadas no jogo com [`config.addVezesRodadas()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Config.cpp#L49-L51).
   
2. **Rodadas Subsequentes**:
   - Se necessário, ajusta a variável `animalNoZero` de acordo com o valor atual, reiniciando para zero quando necessário.
   - A posição do animal no mapa é atualizada.
   - Se o animal não se moveu, o movimento é registrado com [`matriz.addNaoMoveu()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Matriz.cpp#L275-L277).

3. **Atualização da Posição**:
   - O animal realiza a atualização de sua posição no mapa através das funções `setLinhaAnimal()` e `setColunaAnimal()`.

#### ⚙️ Observações
- **Ações no Jogo**: O animal pode interagir com o ambiente, como buscar água, mover-se por áreas vazias ou árvores saudáveis, ou buscar árvores queimadas, dependendo das condições do mapa.

## - [`buscarAgua (Tipo: bool)`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Animal.cpp#L41-L107)  
    
    Essa função é responsável por buscar a água mais próxima no mapa, utilizando uma abordagem de busca em largura (BFS). Quando o animal encontra uma posição com água, ele se move para essa posição, registra o movimento e atualiza o estado do jogo.

#### 🧠 Funcionamento
1. **Configuração Inicial**:
   - A função começa pegando as dimensões do mapa e a posição atual do animal.
   - Utiliza a técnica de busca em largura (BFS) para explorar as células vizinhas a partir da posição inicial do animal.

2. **BFS**:
   - A busca começa na posição do animal (`iniLinha`, `iniColuna`) e explora as células vizinhas (cima, baixo, esquerda, direita).
   - A cada célula visitada, é registrado o caminho e o estado de visitação da célula.
   - Se uma célula com água ('4') for encontrada, o animal se move para essa célula, a célula é marcada como '0', e o movimento do animal é registrado.
   
3. **Atualização do Jogo**:
   - Quando a água é encontrada, a função registra a posição do animal, torna as células adjacentes em `'1'` com a função [`jogaUmidade(linha, coluna)`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Animal.cpp#L257-L274) e atualiza o estado do mapa.
   - A função também registra o caminho percorrido pelo animal até a água, e incrementa o número de passos dados e o número de águas encontradas.

#### 🔁 Retorno
- `true`: Quando o animal encontra a água, se move para essa posição e atualiza o estado do jogo.
- `false`: Se o animal não consegue encontrar a água após explorar todas as possibilidades.

## - [`buscarVazioArvoreSaudavel (Tipo: bool)`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Animal.cpp#L109-L191)  
    
    Essa função funciona exatamente da mesma maneira como a anterior. No entanto, esta busca uma área vazia ('0') ou uma árvore saudável ('1'). Ademais, "buscarVazioArvoreSaudavel" também não espalha umidade já que não encontra pontos d'água como em buscarAgua. Além disso, caso o animal pare em uma área vazia, a função "addAnimalNoZero()" é acionada para registrar que o animal pode ficar lá por até 3 iterações. Logo, "buscarVazioArvoreSaudavel" possui praticamente as mesmas funcionalidades citadas previamente.

## - [`buscarArvoreQueimada (Tipo: bool)`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Animal.cpp#L193-L255)  
    
    Essa função funciona praticamente da mesma maneira como "buscarVazioArvoreSaudavel". Entretanto, esta busca árvores queimadas ('3'). Assim, a função "addAnimalNoZero()" não está presente na função "buscarArvoreQueimada".

## - [`jogaUmidade (Tipo: void, Parâmetros: int linha, int coluna)`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Animal.cpp#L257-L274)  
    
    Essa função é chamada quando o animal encontra e consome um ponto de água. Ela tem como objetivo "umidificar" as células adjacentes ao ponto onde a água foi encontrada, transformando essas células em áreas com árvores saudáveis ('1').

#### 🧠 Funcionamento
- A função recebe como parâmetros a **linha** e a **coluna** do ponto de água que foi consumido.
- Verifica cada uma das quatro direções adjacentes (cima, baixo, esquerda e direita).
- Se a célula vizinha estiver dentro dos limites do mapa, seu tipo é alterado para `'1'`, representando uma árvore saudável.

#### 🧾 Efeito no Jogo
Essa função ajuda o animal a conter o fogo indiretamente, tornando o ambiente ao redor mais resistente ao incêndio (ao transformar áreas vazias ou queimadas novamente em árvores saudáveis).

## - [`estaPreso (Tipo: bool, Parâmetros: int linha, int coluna)`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Animal.cpp#L276-L309)  
    
    Essa função verifica se o animal está preso, ou seja, cercado por células em chamas ('2') e sem possibilidade de movimento para uma célula segura.

#### 🧠 Funcionamento
- A função analisa as 4 direções possíveis (cima, baixo, esquerda, direita) ao redor da posição atual do animal para saber se ele está cercado ou não.
- Conta apenas as células vizinhas válidas (dentro do mapa).
- Verifica se existe pelo menos uma célula vizinha que **não** seja do tipo `'2'`.
- Caso não exista nenhuma rota viável e existam vizinhos, considera o animal preso.

#### 🔁 Retorno
- `true`: Se o animal possui todas células ortogonalmente adjacentes registradas como `'2'`.
- `false`: Se o animal possui pelo menos uma célula ortogonalmente adjacente registrada diferente de `'2'`.

#### 🧾 Efeito no Jogo
Serve como condição de parada na simulação. Se o animal estiver preso, a função [`espalharFogo()`](https://github.com/fernando-horita-siratuti/Simulacao-de-Propagacao-de-Incendios/blob/main/src/Incendio.cpp#L39-L61) interrompe a simulação e chama o encerramento da partida.

## 🧪 Casos de Teste
#### - Impressão da matriz quando o animal é atingido pelo fogo: 
    Iteração 6:
    3 3 3 3 3 2 2 1 1 1 
    3 3 3 3 2 2 1 1 1 1 
    3 3 3 2 2 1 1 1 1 1 
    3 3 2 2 1 1 1 1 1 1 
    3 2 2 1 1 1 1 1 1 1 
    2 2 1 1 1 0 1 1 1 1 
    2 1 1 1 1 1 1 1 1 1 
    1 1 1 1 1 1 1 1 1 1 
    1 1 1 1 1 1 1 1 1 1 
    1 1 1 1 1 1 1 1 1 1 
    O animal pegou fogo! Teletransporte ativado, posição teletransportada: (4, 3).

#### - Mensagem de erro para casos sem registro de incêndio inicial:
    Erro: nenhum ponto de incêndio foi registrado na matriz. Encerrando o programa.

#### - Mensagem de erro para casos com dimensões incorretas da matriz:
    Erro: número de colunas incorreto na linha 2 do arquivo ./dataset/input.dat. Encerrando o programa.

#### - Impressão do resumo final:
    - - - - - Resumo geral: - - - - -

    - Pontos de água encontrados: 0.
    - Passos dados: 28.
    - Caminho feito na 1ª iteração: Animal não se moveu na 1ª iteração.
    - Caminho feito na 2ª iteração: Animal não se moveu na 2ª iteração.
    - Caminho feito na 3ª iteração: Animal não se moveu na 3ª iteração.
    - Caminho feito na 4ª iteração: (5, 5) -> (4, 5) -> (4, 4) -> Fim da iteração 4
    - Caminho feito na 5ª iteração: (4, 4) -> (3, 4) -> (3, 3) -> Fim da iteração 5
    - Caminho feito na 6ª iteração: (3, 3) -> (4, 3) -> (4, 2) -> (4, 3) -> Fim da iteração 6
    - Caminho feito na 7ª iteração: (4, 3) -> (5, 3) -> (5, 2) -> (5, 3) -> Fim da iteração 7
    - Caminho feito na 8ª iteração: (5, 3) -> (6, 3) -> (6, 2) -> (6, 3) -> Fim da iteração 8
    - Caminho feito na 9ª iteração: (6, 3) -> (7, 3) -> (7, 2) -> (7, 3) -> Fim da iteração 9
    - Caminho feito na 10ª iteração: (7, 3) -> (8, 3) -> (8, 2) -> (8, 3) -> Fim da iteração 10
    - Caminho feito na 11ª iteração: (8, 3) -> (9, 3) -> (9, 2) -> (9, 3) -> Fim da iteração 11
    - Caminho feito na 12ª iteração: (9, 3) -> (9, 4) -> (8, 4) -> (8, 5) -> Fim da iteração 12
    - Caminho feito na 13ª iteração: (8, 5) -> (9, 5) -> (9, 4) -> (9, 5) -> Fim da iteração 13
    - Caminho feito na 14ª iteração: (9, 5) -> (9, 6) -> (8, 6) -> (8, 7) -> Fim da iteração 14
    - Caminho feito na 15ª iteração: (8, 7) -> (9, 7) -> (9, 6) -> (9, 7) -> Fim da iteração 15
    - Caminho feito na 16ª iteração: (9, 7) -> (9, 8) -> (8, 8) -> (8, 9) -> Fim da iteração 16
    - Caminho feito na 17ª iteração: (8, 9) -> (9, 9) -> (9, 8) -> (9, 9) -> Fim da iteração 17
    - Animal pegou fogo na 17ª iteração.
    - Status do animal: morto.
    (Coordenadas em formato de '(linha, coluna)')

## 👨🏻‍🔬 Ambiente de Teste
- **Sistema Operacional:** WSL 2 - Ubuntu 22.04 LTS (base Windows 11)
- **Compilador:** g++ (GCC) 11.4.0
- **Hardware:**
  - Notebook: Acer Predator Helios 300
  - CPU: Intel Core i7-11800H (8 núcleos, 16 threads)
  - RAM: 16 GB DDR4

## 👨🏻‍💻 Compilação e Execução
### ✅ Pré-requisitos

Antes de compilar, certifique-se de que você possui os seguintes pacotes instalados no Ubuntu (via WSL):

```bash
sudo apt update
sudo apt install build-essential
```
Use o comando abaixo para limpar, compilar e executar tudo de uma vez:
```bash
make r
```
Ou se preferir pode fazer esses comandos para limpar, compilar e executar, respectivamente:
```bash
make clean
make
make run
```

## 🔚 Conclusão 
Em suma, é possível concluir que o algoritmo aplicado (BFS) não é o melhor a ser utilizado em prol da sobrevivência do animal, por mais que ele permita encontrar os destinos viáveis mais próximos, não necessariamente para tal ocasião ele será a célula mais eficiente para manter o animal vivo. Logo, para futuras melhorias, seria interessante aplicar outro algoritmo visando uma maior eficiência na sobrevivência do animal. Além disso, é notoório que esse projeto pode ser aplicado para desafiar alunos da área da programação a fim de transmitir aprendizados a cerca de alguns tópicos, como: capacidade de manipulação de ponteiros, matrizes, vetores, algoritmos de busca em C/C++, etc. Dessa maneira, durante o decorrer do projeto foi possível notar alguns aprendizados adquiridos/reforçados, como: organização em porgramação orientada a objetos (POO), incluindo encapsulamento, herança e polimorfismo; lógica algorítmica, por meio da implementação de algoritmos de busca e simulação de propagação de eventos; manipulação de estruturas de dados (vector, queue, pair) etc.

## 💭 Créditos
Agradeço o professor Michel Pires Silva por fornecer o Makefile que facilitou na execução e compilação do trabalho. Além disso, gostaria de demonstrar minha gratidão ao monitor Matheus que me ajudou em meu trabalho durante as suas monitorias.

## 📪 Contato
- Email: [siratutifernando@gmail.com]
- LinkedIn: [https://www.linkedin.com/in/fernando-siratuti-503ba8301/]
- GitHub: [https://github.com/fernando-horita-siratuti]
- Instagram: [https://www.instagram.com/siratuti_/]
