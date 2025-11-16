# so_long

**so_long** is a 2D mini-game developed in C using **MiniLibX**, where the player must collect all collectibles in the map and reach the exit. This project introduces concepts such as simple graphical rendering, event handling, map parsing, and interaction with the environment.

---

## 🎮 Objective

- Control the player in a map loaded from a `.ber` file  
- Collect all collectibles (`C`)  
- Reach the exit (`E`) after collecting all items  
- Avoid enemies (`N`) in the bonus version  

---

## 🗺️ Map Format

The map must follow these rules:

- It must be rectangular  
- It must be completely surrounded by walls (`1`)  
- It must contain exactly one player (`P`)  
- It must contain at least one collectible (`C`)  
- It must contain at least one exit (`E`)  
- Allowed characters:  
  - `0` floor  
  - `1` wall  
  - `P` player  
  - `C` collectible  
  - `E` exit  
  - `N` enemy (bonus)

---

## ⌨️ Controls

| Key | Action |
|------|--------|
| W / ↑ | Move up |
| A / ← | Move left |
| S / ↓ | Move down |
| D / → | Move right |
| ESC   | Close the game |

Each movement increases a step counter printed in the terminal.

---

## ⭐ Bonus (Optional)

- Animations (animated sprites)  
- Enemies with simple movement  
- Different sprites depending on direction or state  
- Larger and more dynamic maps  

---

## 🛠️ Technologies

- C  
- MiniLibX (mlx)  
- `.xpm` image files  
- Keyboard and window event handling  

