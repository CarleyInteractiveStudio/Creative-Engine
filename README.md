# Creative-Engine
Motor de videojuego en desarrollo.

## Progreso Actual (Hasta el 1 de Agosto, 2025)

Hemos construido con éxito la base del motor y hemos integrado la librería de interfaz gráfica ImGui. El estado actual incluye:

- **Estructura de Proyecto Modular:** Se ha creado la estructura de directorios principal para albergar los diferentes módulos del motor (`Core`, `Engine`, `Object`, `Platform`, etc.).
- **Módulos `Core`:**
  - `Logger`: Un sistema de logging estático para registrar información, advertencias y errores con timestamps.
  - `Time`: Un gestor de tiempo estático para calcular el `deltaTime` y manejar la lógica independiente de los fotogramas.
- **Sistema de `Object`/`Component`:**
  - `Object`: La clase base para todas las entidades del juego.
  - `Component`: La clase base para todos los componentes que se pueden adjuntar a un `Object`.
- **Módulo `Engine`:**
  - `Application`: La clase principal que gestiona el ciclo de vida de la aplicación (Init, Run, Shutdown).
  - `GameLoop`: Estructura básica para el futuro bucle principal.
- **Plataforma y Ventana:**
  - Se ha integrado la librería **SDL2** para la gestión de ventanas y eventos.
  - La clase `Window` en `Platform` abstrae la creación de la ventana y ahora también gestiona un contexto de OpenGL.
- **Sistema de Compilación `CMake`:**
  - Un `CMakeLists.txt` funcional que compila todos los módulos en una librería estática (`CreativeEngineCore`) y un ejecutable.
- **Integración de ImGui:**
  - Se ha integrado **ImGui** para la creación de interfaces de usuario.
  - El motor ahora renderiza la ventana de demostración de ImGui.

El proyecto compila y ejecuta una aplicación que abre una ventana y muestra la interfaz de ImGui.

## Próximos Pasos

Ahora que la base del motor y la interfaz de usuario están funcionando, los siguientes pasos son:

1.  **Implementar `InputManager`:**
    - Crear un gestor para procesar eventos de teclado y ratón desde SDL y proveer una API sencilla para consultar el estado de los inputs.
2.  **Crear Componentes `Transform`:**
    - Implementar `Transform2DComponent` y/o `Transform3DComponent` para manejar la posición, rotación y escala de los `Objects`.
3.  **Desarrollar el Editor:**
    - Empezar a diseñar y construir las ventanas del editor utilizando ImGui.
    - Crear un "Viewport" para visualizar la escena del juego.
    - Implementar un inspector de `Objects` para ver y modificar sus componentes.
4.  **Sistema de Renderizado:**
    - Abstraer el renderizado en una clase `Renderer` para no tener código de OpenGL directamente en la clase `Application`.
    - Empezar a implementar el renderizado de primitivas y, eventualmente, de modelos 3D.

## Estructura de Archivos Actual

```
CreativeEngine/
├── Assets/
├── Audio/
├── Bin/
├── CMakeLists.txt
├── Components/
├── Core/
│   ├── Logger.cpp
│   ├── Logger.h
│   ├── Time.cpp
│   └── Time.h
├── CreativeScripting/
├── Editor/
├── Engine/
│   ├── Application.cpp
│   ├── Application.h
│   ├── GameLoop.cpp
│   └── GameLoop.h
├── External/
├── Input/
├── main.cpp
├── Object/
│   ├── Component.cpp
│   ├── Component.h
│   ├── Object.cpp
│   └── Object.h
├── Physics/
├── Platform/
│   ├── Window.cpp
│   └── Window.h
├── README.md
├── README.txt
├── Renderer/
├── Serialization/
└── Tests/
```
