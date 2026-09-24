# Cub3D - Raycaster Engine 🎮

O **cub3D** é um projeto desenvolvido como parte do currículo da Escola 42. Trata-se de um motor de jogo 3D em primeira pessoa inspirado no clássico de 1992 *Wolfenstein 3D*. O projeto utiliza a técnica de **Raycasting** (Projeção de Raios) para criar uma perspetiva tridimensional a partir de um mapa bidimensional, desenvolvido em linguagem C utilizando a biblioteca gráfica **MiniLibX**.

---

## 🚀 Funcionalidades

Este projeto está estruturado em duas partes: a versão obrigatória (básica) e a versão bónus (com melhorias avançadas).

### 1. Versão Obrigatória (Mandatory)
* **Motor Raycasting (DDA):** Implementação eficiente do algoritmo DDA (Digital Differential Analysis) para cálculo das distâncias e colisões dos raios com as paredes.
* **Texturização Direcional:** Renderização de texturas específicas para as paredes dependendo da orientação geográfica (Norte, Sul, Leste, Oeste).
* **Cores Customizadas:** Definição livre das cores do teto e do chão através de valores RGB no ficheiro do mapa.
* **Movimentação do Jogador:** Movimentação em 4 direções (`W`, `A`, `S`, `D`) e rotação da câmera (setas esquerda e direita).
* **Validação de Mapas:** Parsing rigoroso e verificação de integridade do mapa (`.cub`), garantindo que o jogador esteja cercado por paredes e que os caminhos das texturas e cores sejam válidos.

### 2. Versão Bónus 🌟
O projeto vai muito além do básico com as seguintes implementações:
* **Salto e Gravidade (Jump & Gravity):** Sistema dinâmico que permite ao jogador saltar (`Espaço`). A física de salto e a gravidade afetam diretamente a projeção das paredes, teto, chão e portas, conferindo realismo de altura.
* **Câmera Livre com Rato (Mouse Look):** Suporte para olhar em todas as direções (esquerda/direita e cima/baixo) simplesmente movendo o rato. A inclinação vertical da câmera altera o horizonte de renderização.
* **Portas Animadas:** Portas interativas espalhadas pelo mapa que podem ser abertas ou fechadas dinamicamente pressionando a tecla `E` ou `Espaço`. As portas possuem animações de abertura/fecho gerais.
* **Minimapa 2D Interativo:** Um pequeno mapa no canto do ecrã mostrando o layout do labirinto (paredes, portas) e a posição/direção do jogador em tempo real.
* **Sistema de Armas e Animações:** 6 tipos de armas diferentes (Pistola, Caçadeira/Shotgun, Revólver, Laser, etc.) com sprites animados completos para quando o jogador está parado (Idle), a correr (Walk) ou a disparar (Fire).
* **Efeitos de Áudio (BASS Library):** Áudio imersivo que inclui música de fundo contínua (looping), sons de tiros específicos para cada arma, barulho de passos ao correr e som das portas a abrir/fechar.
* **Variáveis de Compilação Customizáveis:** Resolução do ecrã, velocidade e tamanho dos pixéis definíveis diretamente nos argumentos do `make`.

---

## 🛠️ Estrutura do Projeto

A estrutura de ficheiros está organizada da seguinte forma:

* `sources/` - Ficheiros fonte C da versão básica (mandatória).
* `source_bonus/` - Ficheiros fonte C com a lógica da versão bónus.
* `includes/` - Cabeçalhos (`cub3D.h` e `cub3D_bonus.h`).
* `libft/` - Biblioteca auxiliar de funções genéricas em C da 42.
* `sound/` - Ficheiros de som (.mp3) utilizados para os efeitos sonoros e música de fundo.
* `textures/` - Pastas contendo os ficheiros de texturas das paredes, teto, chão, portas e animações das armas.
* `maps/` - Ficheiros de mapa com extensão `.cub` (ex. `bridge.cub`, `test.cub`).
* `bass/` - A biblioteca e cabeçalhos do BASS audio library.

---

## 💻 Como Compilar e Executar

### Pré-requisitos
* Sistema Operativo Linux.
* Bibliotecas de desenvolvimento X11 (`libx11-dev`, `libxext-dev`).
* MiniLibX de Linux (incluída no subdiretório `minilibx-linux`).
* Biblioteca BASS instalada/linkada no sistema para o suporte a som (incluída no diretório `bass/`).

### Compilação

Para compilar a **versão básica**:
```bash
make
```

Para compilar a **versão bónus**:
```bash
make bonus
```

#### Parâmetros Customizados no Makefile
O Makefile permite customizar a largura, altura, velocidade e tamanho de pixel em tempo de compilação:
* `W` - Largura da janela (Padrão: `1200`)
* `H` - Altura da janela (Padrão: `800`)
* `S` - Velocidade de movimentação (Padrão: `0.05`)
* `PX` - Tamanho do pixel (Padrão: `14`)

Exemplo de compilação customizada para alta resolução:
```bash
make bonus W=1920 H=1080 S=0.08
```

### Execução

Para iniciar o jogo, passe o caminho de um mapa válido `.cub` como argumento:

**Versão Básica:**
```bash
./cub3D maps/test.cub
```

**Versão Bónus:**
```bash
./cub3D_bonus maps/bridge.cub
```

#### Atalhos do Makefile (Run)
Você também pode compilar e executar diretamente usando os comandos do Makefile:
```bash
# Executa a versão básica com o mapa test.cub
make run

# Executa a versão bónus com o mapa bridge.cub
make brun
```

---

## 🎮 Controlos

### Versão Básica (Mandatória)
| Tecla | Ação |
| :--- | :--- |
| `W` / `A` / `S` / `D` | Mover para a frente, esquerda, trás e direita |
| `<-` / `->` (Setas) | Rodar a câmera para a esquerda ou direita |
| `ESC` | Fechar o jogo |

### Versão Bónus (Adicionais)
| Tecla / Evento | Ação |
| :--- | :--- |
| **Movimento do Rato** | Rotação horizontal e inclinação vertical da câmera |
| **Clique Esquerdo Rato** | Disparar a arma selecionada |
| `Espaço` | Saltar (Jump) |
| `E` ou `Espaço` (perto de portas) | Abrir ou fechar portas |
| `1` a `6` (Teclado) | Alternar entre os diferentes tipos de armas |
| `L-CTRL` / `CTRL` | Agachar ou interação adicional |

---

## 🗺️ Configuração de Mapas (`.cub`)

Os mapas são configurados utilizando ficheiros de texto plano com a extensão `.cub`. Exemplo de estrutura:

```text
NO ./textures/comb1/tatame_north_texture.xpm
SO ./textures/comb1/tatame_south_texture.xpm
EA ./textures/comb1/tatame_east_texture.xpm
WE ./textures/comb1/tatame_west_texture.xpm

F 49,45,21
C 135,206,225

111111111111111111111111
100000000000000000000001
101111100111110011111001
101000100100010010001001
1010N010010D010010001001
101111100111110011111001
100000000000000000000001
111111111111111111111111
```

* **`NO`, `SO`, `EA`, `WE`:** Caminhos relativos para as texturas das paredes Norte, Sul, Leste e Oeste, respetivamente.
* **`F` / `C`:** Cor do chão (Floor) e teto (Ceiling) em formato RGB separados por vírgula.
* **Grelha de Mapa:**
  * `1` - Parede
  * `0` - Espaço vazio
  * `D` - Porta (apenas no Bónus)
  * `N`, `S`, `E`, `W` - Posição inicial do jogador e a sua respetiva orientação de partida.

---

## 👥 Autores

Este projeto foi desenvolvido e enriquecido por:
* **Angelo Quissanga** (`aquissan`)
* **Nd Daniel** (`NdondaDaniel2020`)
