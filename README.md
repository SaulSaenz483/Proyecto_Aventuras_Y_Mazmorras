# Adventures & Dungeons — Motor de Simulación

**Curso:** EIF204 - Programación II  
**Universidad Nacional de Costa Rica — Escuela de Informática**  
**Periodo:** I Ciclo 2026

---

## Descripción

Adventures & Dungeons es un motor de simulación de aventuras en consola desarrollado en C++. El jugador controla a un héroe que explora una mazmorra, interactúa con NPCs, recoge ítems, combate enemigos y debe derrotar al jefe final para ganar.

El sistema carga el mundo desde archivos de texto, ejecuta una simulación con cambios de estado reales y genera una bitácora y reporte final al terminar.

---

## Estructura del proyecto

```
Proyecto_Aventuras_Y_Mazmorras/
├── main.cpp
├── CMakeLists.txt
├── data/
│   ├── map.txt           # Estructura del mapa (paredes y posición inicial)
│   ├── enemies.txt       # Enemigos y su posición en el mapa
│   ├── items.txt         # Ítems (armas y pociones) y su posición
│   └── npcs.txt          # NPCs, diálogo, acción y valor
├── include/
│   ├── domain/           # Entidades del dominio (Hero, Enemy, NPC, Item...)
│   ├── simulation/       # Motor de simulación y sistema de combate
│   └── output/           # Logger y generador de reporte
└── src/
    ├── domain/
    ├── simulation/
    └── output/
```

Los archivos de salida se generan en `cmake-build-debug/data/`:
- `adventure_log.txt` — bitácora de todos los eventos
- `final_report.txt` — reporte final con estado del héroe y resultado

---

## Compilación

### Requisitos

- CMake 3.16 o superior
- Compilador C++20 (GCC, Clang o MSVC)
- CLion (recomendado) o cualquier entorno con CMake

---

## Ejecución

### Desde CLion

Presionar el botón **Run** o `Shift+F10`. El programa se ejecuta en la terminal integrada de CLion.

> **Nota:** La terminal de CLion no soporta limpieza de pantalla. El mapa se imprime de forma continua hacia abajo. Para una experiencia visual óptima, ejecutar desde CMD o PowerShell en Windows.


---

## Controles

| Tecla | Acción                 |
|-------|------------------------|
| W     | Moverse hacia arriba   |
| S     | Moverse hacia abajo    |
| A     | Moverse a la izquierda |
| D     | Moverse a la derecha   |
| I     | Ver inventario         |
| Q     | Salir                  |

En combate:

| Tecla | Acción      |
|-------|-------------|
| 1     | Atacar      |
| 2     | Usar poción |
| 3     | Huir        |

---

## Simbología del mapa

| Símbolo | Significado |
|---------|-------------|
| `@`     | Héroe       |
| `E`     | Enemigo     |
| `B`     | Boss        |
| `N`     | NPC         |
| `$`     | Ítem        |
| `#`     | Pared       |
| `.`     | Suelo       |

---

## Formato de archivos de entrada

### `map.txt`
```
WIDTH|HEIGHT
<filas del mapa usando # . @>
```

### `enemies.txt`
```
# col|row|name|type|hp|damage
```
El tipo `Boss` es obligatorio (exactamente uno). Los demás tipos pueden ser cualquier string.

### `items.txt`
```
# type|col|row|name|description|weight|rarity|stat|effect
```
Tipos válidos: `W` (arma), `P` (poción). El efecto de pociones debe ser `Heal`.

### `npcs.txt`
```
# col|row|name|dialogue|action|value
```
Acciones válidas: `heal` (restaura HP), `give_potion` (entrega una poción), `none`.

---

## La aventura

El héroe elegido por el jugador despierta en una mazmorra oscura. Su misión: derrotar al Lich King **Malachar** que aguarda en el extremo noreste del mapa.

**Estrategia recomendada:**
1. Bajar a la fila 6 y recoger la **Sword of Light** — está cerca del inicio
2. Hablar con el **Wounded Knight** (fila 5) — entrega una poción
3. Explorar el mapa y eliminar enemigos menores
4. Hablar con el **Old Sage** (fila 6, lado derecho) — restaura HP antes del final
5. Enfrentar a **Malachar** en la esquina noreste con el arma equipada

> Sin el arma, el héroe hace 18 de daño por turno. Con ella, hace 38. Malachar tiene 120 HP y hace 22 de daño — la diferencia es determinante.

---

## Archivos de salida

Al terminar la partida (victoria, derrota o salida) el programa genera:

- **`data/adventure_log.txt`** — registro cronológico de todos los eventos
- **`data/final_report.txt`** — resumen final con HP del héroe, inventario, celdas exploradas y resultado

---