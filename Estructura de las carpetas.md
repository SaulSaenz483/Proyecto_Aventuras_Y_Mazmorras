DungeonEngine/
├── data/                         # Archivos .txt de configuración de entrada
│   ├── items.txt
│   ├── entities.txt
│   └── map.txt
├── include/                      # Todos los archivos de cabecera (.h)
│   ├── input/
│   │   ├── DungeonLoader.h
│   │   └── ItemFactory.h
│   ├── domain/
│   │   ├── Entity.h              <- Mové el tuyo aquí
│   │   ├── Item.h                <- Mové el tuyo aquí
│   │   ├── Hero.h
│   │   ├── Enemy.h
│   │   ├── Weapon.h
│   │   ├── Potion.h
│   │   ├── Room.h
│   │   └── Inventory.h
│   ├── simulation/
│   │   ├── SimulationEngine.h
│   │   └── CombatSystem.h
│   └── output/
│       ├── Logger.h
│       └── ReportGenerator.h
├── src/                          # Todos los archivos de implementación (.cpp)
│   ├── input/
│   │   ├── DungeonLoader.cpp
│   │   └── ItemFactory.cpp
│   ├── domain/
│   │   ├── Hero.cpp
│   │   ├── Enemy.cpp
│   │   ├── Weapon.cpp
│   │   ├── Potion.cpp
│   │   └── Room.cpp
│   ├── simulation/
│   │   ├── SimulationEngine.cpp
│   │   └── CombatSystem.cpp
│   └── output/
│       ├── Logger.cpp
│       └── ReportGenerator.cpp
├── main.cpp                      # Punto de entrada principal en la raíz
└── CMakeLists.txt                # Configuración de compilación (si usan CMake/CLion)
