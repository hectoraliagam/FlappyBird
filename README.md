# Flappy Bird (C++ / SFML)

![Flappy Bird Screenshot](./screenshot.png)

Implementación de **Flappy Bird** desarrollada en **C++ (GNU++17)** utilizando la librería **SFML 3.x**.  
El objetivo de este proyecto es servir como **juego funcional**, **ejercicio de arquitectura** y **base educativa** para el desarrollo de aplicaciones gráficas interactivas en C++ sin depender inicialmente de CMake.

---

## 📌 Características

- Motor simple en C++ puro
- Renderizado gráfico con SFML
- Bucle principal estructurado (game loop)
- Separación clara entre lógica y punto de entrada (`main.cpp`)
- Soporte para compilación **Debug** y **Release**
- Integración directa con **Visual Studio Code (tasks.json)**

---

## 📁 Estructura del proyecto

```yaml
project/
├── src/
│ ├── main.cpp
├── bin/
│ ├── app_debug.exe
│ ├── app_release.exe
│ ├── sfml-system-3.dll
│ ├── sfml-window-3.dll
│ └── sfml-graphics-3.dll
├── .vscode/
│ └── tasks.json
├── README.md
└── LICENSE
```

---

## 🛠 Requisitos

### Sistema
- Windows 10 / 11 (64-bit)

### Herramientas
- **MinGW-w64 (GCC)**  

Recomendado:
```yaml
C:\mingw64\bin\g++.exe
```

- **SFML 3.x (MinGW 64-bit)**  

Instalación esperada:
```yaml
C:\SFML-3.0.2\
```

- **Visual Studio Code**

- Extensión: *C/C++ (Microsoft)*

---

## ⚙️ Configuración de SFML

Asegúrate de que los siguientes archivos estén en la carpeta `bin/` junto al ejecutable:

```yaml
sfml-system-3.dll
sfml-window-3.dll
sfml-graphics-3.dll
```

Sin estos archivos, el programa **no podrá ejecutarse**.

---

## ▶️ Compilación y ejecución

El proyecto utiliza **tasks de VS Code** para facilitar la compilación.

### Ejecutar desde VS Code

1. Abre el proyecto en VS Code
2. Presiona:

```yaml
Ctrl + Shift + P
→ Run Task
```

3. Selecciona una de las siguientes opciones:

| Task | Descripción |
|----|----|
| Build Debug (SFML) | Compila en modo debug (`-g -O0`) |
| Build Release (SFML) | Compila en modo optimizado (`-O2`) |
| Build + Run Debug (SFML) | Compila y ejecuta (debug) |
| Build + Run Release (SFML) | Compila y ejecuta (release) |

---

## 🧪 Modo Debug vs Release

### Debug
- Símbolos de depuración activados
- Logs disponibles
- Ideal para desarrollo y pruebas

### Release
- Código optimizado
- Sin asserts ni logs de debug
- Ideal para builds finales

---

## 🧠 Notas de desarrollo

- El archivo `main.cpp` se mantiene **minimalista**

---

## 📜 Licencia

Este proyecto está licenciado bajo la:

**GNU AFFERO GENERAL PUBLIC LICENSE (AGPL v3)**

Esto implica que:
- Cualquier modificación o uso en red debe mantener el código abierto
- Las mejoras deben compartirse bajo la misma licencia

Consulta el archivo `LICENSE` para más detalles.

---

## 👤 Autor

**Hector Aliaga Medina**  
Desarrollado como proyecto educativo y técnico en C++ / SFML.  
Pensado para aprendizaje serio, arquitectura limpia y base reutilizable.

---

## 🚀 Estado del proyecto

🔧 En desarrollo  
📌 Base estable para expansión futura
