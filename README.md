Adventures & Dungeons — Motor de Simulación
Curso: EIF204 - Programación II  
Universidad Nacional de Costa Rica — Escuela de Informática  
Periodo: I Ciclo 2026
---
Descripción
Adventures & Dungeons es un motor de simulación de aventuras en consola desarrollado en C++. El jugador controla a un héroe que explora una mazmorra, interactúa con NPCs, recoge ítems, combate enemigos y debe derrotar al jefe final para ganar.
El sistema carga el mundo desde archivos de texto, ejecuta una simulación con cambios de estado reales y genera una bitácora y reporte final al terminar.
---
Estructura del proyecto
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
`adventure_log.txt` — bitácora de todos los eventos
`final_report.txt` — reporte final con estado del héroe y resultado
---
Compilación
Requisitos
CMake 3.16 o superior
Compilador C++20 (GCC, Clang o MSVC)
CLion (recomendado) o cualquier entorno con CMake
Con CLion
Abrir la carpeta del proyecto en CLion
CLion detecta el `CMakeLists.txt` automáticamente
Hacer clic en Build > Build Project o presionar `Ctrl+F9`
El ejecutable se genera en `cmake-build-debug/`
Los archivos de `data/` se copian automáticamente al directorio de build
Con línea de comandos
```bash
mkdir build && cd build
cmake ..
cmake --build .
```
---
Ejecución
Desde CLion
Presionar el botón Run o `Shift+F10`. El programa se ejecuta en la terminal integrada de CLion.
> **Nota:** La terminal de CLion no soporta limpieza de pantalla (`system("cls")`). El mapa se imprime de forma continua hacia abajo. Para una experiencia visual óptima, ejecutar desde CMD o PowerShell en Windows.
Desde CMD o PowerShell (Windows)
```bat
cd cmake-build-debug
.\Proyecto_Aventuras_Y_Mazmorras.exe
```
Desde terminal (Linux/macOS)
```bash
cd build
./Proyecto_Aventuras_Y_Mazmorras
```
---
Controles
Tecla	Acción
W	Moverse hacia arriba
S	Moverse hacia abajo
A	Moverse a la izquierda
D	Moverse a la derecha
I	Ver inventario
Q	Salir
En combate:
Tecla	Acción
1	Atacar
2	Usar poción
3	Huir
---
Simbología del mapa
Símbolo	Significado
`@`	Héroe
`E`	Enemigo
`B`	Boss
`N`	NPC
`$`	Ítem
`#`	Pared
`.`	Suelo
---
Formato de archivos de entrada
`map.txt`
```
ANCHO|ALTO
<filas del mapa usando # . @>
```
`enemies.txt`
```
# col|row|nombre|tipo|hp|damage
```
El tipo `Boss` es obligatorio (exactamente uno). Los demás tipos pueden ser cualquier string.
`items.txt`
```
# tipo|col|row|nombre|descripcion|peso|rareza|stat|efecto
```
Tipos válidos: `W` (arma), `P` (poción). El efecto de pociones debe ser `Heal`.
`npcs.txt`
```
# col|row|nombre|dialogo|accion|valor
```
Acciones válidas: `heal` (restaura HP), `give_potion` (entrega una poción), `none`.
---
La aventura
El héroe Aldric despierta en una mazmorra oscura. Su misión: derrotar al Lich King Malachar que aguarda en el extremo noreste del mapa.
Estrategia recomendada:
Explorar el mapa antes de enfrentar al Boss
Hablar con el Wounded Knight (fila 5) — entrega una poción
Recoger la Sword of Light (fila 6) — aumenta el ATK considerablemente
Hablar con el Old Sage (fila 6) — restaura HP antes del combate final
Enfrentar a Malachar con el arma equipada y pociones disponibles
> Sin el arma, el héroe hace 18 de daño por turno. Con ella, hace 38. Malachar tiene 120 HP y hace 22 de daño — la diferencia es determinante.
---
Archivos de salida
Al terminar la partida (victoria, derrota o salida) el programa genera:
`data/adventure_log.txt` — registro cronológico de todos los eventos
`data/final_report.txt` — resumen final con HP del héroe, inventario, celdas exploradas y resultado
---
Notas técnicas
El proyecto usa rutas relativas — no depende de la máquina del desarrollador
Los archivos de `data/` se copian automáticamente al directorio de build en cada compilación mediante `add_custom_command` en `CMakeLists.txt`
Para modificar el mundo, editar los archivos en `data/` de la raíz del proyecto y recompilar
El ejecutable es estático (`-static`) — no requiere DLLs externas para ejecutarse fuera de CLion
