# so_long

O **so_long** é um mini-jogo 2D desenvolvido em C utilizando a **MiniLibX**, onde o jogador deve recolher todos os colecionáveis do mapa e alcançar a saída. Este projeto introduz conceitos de renderização gráfica simples, manipulação de eventos, parsing de mapas e interação com o ambiente.

---

## 🎮 Objetivo

- Controlar o jogador num mapa definido em ficheiro `.ber`
- Recolher todos os colecionáveis (`C`)
- Chegar à saída (`E`) após recolher todos os itens
- Evitar inimigos (`N`) na versão bônus

---

## 🗺️ Formato do Mapa

O mapa deve seguir as seguintes regras:

- Ser retangular  
- Estar totalmente rodeado por paredes (`1`)  
- Conter apenas um jogador (`P`)  
- Ter pelo menos um colecionável (`C`)  
- Ter pelo menos uma saída (`E`)  
- Caracteres permitidos:  
  - `0` chão  
  - `1` parede  
  - `P` jogador  
  - `C` colecionável  
  - `E` saída  
  - `N` inimigo (bônus)
 
  ## ⌨️ Controles

| Tecla | Ação |
|------|-------|
| W / ↑ | Mover para cima |
| A / ← | Mover para a esquerda |
| S / ↓ | Mover para baixo |
| D / → | Mover para a direita |
| ESC   | Fechar o jogo |

Cada movimento incrementa um contador de passos mostrado no terminal.

---

## ⭐ Bônus (Opcional)

- Animações (sprites animados)  
- Inimigos com movimento simples  
- Sprites diferentes conforme a direção ou estado  
- Mapa maior e mais dinâmico

## 🛠️ Tecnologias

- C  
- MiniLibX (mlx)  
- Imagens `.xpm`  
- Eventos de teclado e janela  

### Exemplo:

