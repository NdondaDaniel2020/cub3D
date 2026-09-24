# Cub3D - Raycaster Engine 🎮

> **Motor Gráfico 3D Raycasting em C com MiniLibX, Áudio BASS e Combate em Primeira Pessoa**

O **cub3D** é um projeto desenvolvido como parte do currículo da **Escola 42**. Trata-se de um motor de jogo 3D em primeira pessoa inspirado no clássico *Wolfenstein 3D* (1992). O projeto utiliza a técnica de **Raycasting** (Projeção de Raios) via algoritmo **DDA** (*Digital Differential Analysis*) para projetar uma perspetiva tridimensional imersiva a partir de uma grelha bidimensional.

---

## 🌟 Showcase & Portfólio

Este repositório segue o padrão modular do ecossistema de portfólio (`.portfolio/`):

* **Capa em Alta Definição:** [`.portfolio/cover.webp`](.portfolio/cover.webp)
* **Demonstração em Vídeo:** [`.portfolio/gallery/demo.mp4`](.portfolio/gallery/demo.mp4)
* **Metadados e Especificações:** [`.portfolio/details.json`](.portfolio/details.json)

---

## 🚀 Funcionalidades

### 1. Versão Obrigatória (Mandatory)
* **Motor Raycasting (DDA):** Implementação matemática precisa do algoritmo DDA para cálculo de interseções dos raios com as paredes em tempo real sem distorção olho-de-peixe (*fisheye correction*).
* **Texturização Direcional:** Renderização e mapeamento de texturas XPM diferenciadas conforme a orientação cardeal da parede (Norte, Sul, Este, Oeste).
* **Superfícies Coloridas:** Definição livre das cores do teto e do chão através de valores RGB declarados no ficheiro do mapa (`.cub`).
* **Movimentação do Jogador:** Movimentação em 4 eixos (`W`, `A`, `S`, `D`) e rotação contínua da câmera (setas direcionais).
* **Parser e Validação Estrita:** Verificação completa da integridade do mapa com algoritmo *flood fill*, garantindo perímetro estanque cercado por paredes, posição inicial única e ficheiros de textura válidos.

### 2. Versão Bónus (Odyssey 2.0) ⚡
* **Controle Livre pelo Rato (Mouse Look):** Rotação horizontal e inclinação vertical suave da câmera com captura do rato.
* **Portas Dinâmicas:** Portas deslizantes com verificação de colisão, animação por sprites e efeitos sonoros sincronizados (`E` ou `Espaço`).
* **Renderização de Teto e Chão Texturizados:** Mapeamento de texturas contínuas por scanline com projeção de perspectiva.
* **Arsenal de Armas com Ciclos Completos de Sprites:** 5 armas distintas (Escopeta, Lupara, Pistola, Metralhadora, Revólver) com animações fluidas para estados de repouso (Idle), deslocamento (Walk) e disparo (Fire).
* **Engine de Áudio Integrada (BASS Audio):** Som multicanal imersivo incluindo banda sonora em loop contínuo, passos dinâmicos, disparos de armas e abertura/fecho de portas.
* **Minimapa 2D Interativo (HUD Radar):** Radar em tempo real no canto da tela exibindo as paredes, portas dinâmicas e o cone de visão do jogador.
* **Telas de Carregamento e Preload:** Apresentação visual da barra de progresso durante o carregamento assíncrono dos recursos gráficos.

---

## 📁 Estrutura do Projeto

```text
cub3D/
├── assets/                         # 📁 Todos os recursos estáticos e dados do jogo
│   ├── textures/                   # Texturas gráficas (XPM / PNG)
│   │   ├── walls/                  # Texturas das paredes (brick, stone, tatame...)
│   │   ├── weapons/                # Sprites das armas (escopeta, lupara, revolver)
│   │   ├── doors/                  # Animações de portas abrindo/fechando
│   │   └── ui/                     # Telas de preload, mira (crosshair) e logos
│   ├── sounds/                     # Áudios e efeitos sonoros (SFX, passos, tiros, BGM)
│   └── maps/                       # Mapas de fases (.cub)
│
├── libs/                           # 📚 Todas as bibliotecas externas e utilitárias
│   ├── libft/                      # Biblioteca padrão em C da 42
│   ├── mlx/                        # MiniLibX (Linux/X11)
│   └── bass/                       # BASS Audio Engine (headers + libbass.so)
│
├── include/                        # 📄 Arquivos de cabeçalho (.h)
│   ├── cub3d.h                     # Header principal
│   ├── cub3d_bonus.h               # Header das extensões bônus
│   └── defines.h                   # Constantes de tela, FOV, teclas e velocidade
│
├── src/                            # 💻 Código-fonte em C modularizado
│   ├── core/                       # Inicialização, game loop, hooks e limpeza
│   ├── parser/                     # Leitura do .cub, validação de paredes e flood fill
│   ├── raycaster/                  # Algoritmo DDA, projeção de raios e cálculo de distâncias
│   ├── render/                     # Renderização de paredes, teto, chão e minimapa
│   ├── player/                     # Movimentação, colisão, física e mira pelo rato (mouse)
│   └── bonus/                      # Módulos de áudio (BASS), portas dinâmicas e sprites
│
├── .portfolio/                     # 🌟 Showcase para o seu Portfólio
│   ├── cover.webp                  # Capa do jogo em alta definição (1080p)
│   ├── details.json                # Metadados e highlights de engenharia
│   └── gallery/                    # Vídeo gameplay (demo.mp4) + capturas WebP
│
├── build/                          # ⚙️ Diretório unificado de objetos compilados (.o)
├── Makefile                        # Build system atualizado e limpo
└── README.md                       # Documentação técnica com showcase e instruções
```

---

## 💻 Compilação e Execução

### Pré-requisitos
* Sistema Operativo Linux (Ubuntu/Debian)
* Compilador C (`gcc` ou `clang`) e `make`
* Bibliotecas X11 do sistema (`libx11`, `libxext`)

### Compilação

Para compilar a **versão obrigatória**:
```bash
make
```

Para compilar a **versão bónus**:
```bash
make bonus
```

Os ficheiros objeto (`.o`) são centralizados de forma organizada dentro do diretório `build/`.

### Execução

```bash
# Versão Obrigatória
./cub3D assets/maps/test.cub

# Versão Bónus (com Áudio BASS e Armas)
./cub3D_bonus assets/maps/bridge.cub
```

Também é possível utilizar os atalhos do Makefile:
```bash
make run    # Compila e roda a versão obrigatória
make brun   # Compila e roda a versão bónus
```

### Parâmetros Customizáveis no Make

É possível customizar a resolução e velocidade do jogo durante o build:
```bash
make bonus W=1280 H=720 S=0.06
```
* `W` - Largura da janela (Window Width)
* `H` - Altura da janela (Window Height)
* `S` - Velocidade de deslocação (Speed)
* `PX` - Tamanho da amostragem em pixéis

---

## 🎮 Comandos do Jogo

| Tecla / Ação | Função |
| :--- | :--- |
| `W` / `A` / `S` / `D` | Mover para a Frente / Esquerda / Trás / Direita |
| `Setas ← / →` | Rodar a câmera para a esquerda / direita |
| `Rato (Mouse)` | Mira livre e rotação da câmera (Bónus) |
| `Botão Esquerdo` | Disparar a arma selecionada (Bónus) |
| `1` até `5` | Trocar de arma no arsenal (Bónus) |
| `E` ou `Espaço` | Abrir / Fechar portas interativas (Bónus) |
| `ESC` ou `Cruz [X]` | Sair do jogo com libertação limpa de memória |

---

## 👥 Autores

* **Ndonda Daniel** ([@NdondaDaniel2020](https://github.com/NdondaDaniel2020))
* **Aquissan** ([@aquissan](https://github.com/aquissan))
