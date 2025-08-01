# Creative-Engine
Motor de videojuego en desarrollo.

## Progreso Actual (Hasta el 31 de Julio, 2025)

Hemos construido con éxito la base del motor. El estado actual incluye:

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
  - La clase `Window` en `Platform` abstrae la creación de la ventana.
- **Sistema de Compilación `CMake`:**
  - Un `CMakeLists.txt` funcional que compila todos los módulos en una librería estática (`CreativeEngineCore`) y un ejecutable.

El proyecto actualmente compila y ejecuta una aplicación que abre una ventana vacía y se cierra al recibir el evento de salida.

## Problemas Actuales y Próximos Pasos

Actualmente estamos bloqueados por problemas de compilación relacionados con las librerías `Glad` y `ImGui`. A pesar de varios intentos, no hemos podido resolver estos problemas.

### Problemas de Compilación

- **Error de Inclusión de `khrplatform.h`:** La librería `Glad` requiere el archivo de cabecera `khrplatform.h`, que no se encuentra en el entorno de compilación.
- **Intentos de Solución:**
    1.  Se intentó instalar `libgl-dev`, que debería proveer el archivo, pero el problema persistió.
    2.  Se intentó descargar `khrplatform.h` manualmente y ubicarlo en el directorio `Glad/KHR`, pero los problemas con el sistema de archivos impidieron esta acción.
- **Hipótesis:** El problema principal parece ser una configuración incorrecta del entorno de compilación que impide la correcta localización de las dependencias y la manipulación de archivos.

### Plan de Acción

1.  **Resolver el Problema de Compilación:**
    -   **Acción Inmediata:** Subir los cambios actuales al repositorio de Git. Esto permitirá que el entorno se actualice y, con suerte, resuelva los problemas de localización de archivos.
    -   **Si el problema persiste:**
        -   Investigar a fondo la configuración de `CMake` para asegurar que los directorios de inclusión (`include directories`) estén correctamente configurados.
        -   Considerar el uso de un gestor de dependencias como `vcpkg` o `Conan` para manejar las librerías externas de forma más robusta.
2.  **Integrar `ImGui` para la Interfaz del Editor:**
    - Una vez resueltos los problemas de compilación, añadir ImGui como dependencia.
    - Inicializar ImGui en la `Application`.
    - Renderizar una ventana de demostración de ImGui.
3.  **Implementar `InputManager`:**
    - Crear un gestor para procesar eventos de teclado y ratón desde SDL.
4.  **Crear Componentes `Transform`:**
    - Implementar `Transform2DComponent` y/o `Transform3DComponent` para manejar la posición, rotación y escala de los `Objects`.

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
