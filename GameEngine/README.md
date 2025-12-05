# Creative Engine 2 - Motor de Videojuegos 2D

## Objetivo del Proyecto

Construir un motor de videojuegos 2D potente, ligero y modular, con capacidades multiplataforma (Windows, macOS, Linux, iOS, Android) y una fuerte orientación a la creación de juegos tipo "maker" con un editor visual intuitivo y herramientas de diseño eficientes.

El motor buscará ofrecer un rendimiento óptimo con un runtime mínimo, un editor desacoplado del runtime del juego, y un pipeline de assets robusto.

## Visión del Editor

El editor permitirá un flujo de trabajo similar a Unity, con:
- Un sistema de ventanas prefabricadas, arrastrables y divisibles (docking).
- Paneles de Inspector para edición de propiedades en tiempo real.
- Navegador de archivos y assets.
- Herramientas visuales para diseño de escenas y niveles.

## Stack Tecnológico Confirmado (MVP C++ Core)

El núcleo del motor se desarrollará en C++ y estará preparado para la futura integración de múltiples lenguajes de scripting (Python, JavaScript, C#, Lua).

-   **Ventana, Input y Gestión Multimedia:** SDL2 (Simple DirectMedia Layer) - Base multiplataforma sólida para gráficos, audio, input y ventana.
-   **Renderizado 2D:** OpenGL 3.3+ Core Profile - Renderizado acelerado por GPU, con enfoque en batching de sprites y optimización.
-   **Carga de Extensiones OpenGL:** glad.
-   **Carga de Imágenes:** stb_image - Librería ligera para cargar formatos de imagen.
-   **Interfaz de Usuario del Editor:** ImGui (Dear ImGui) - Para el sistema de docking y herramientas visuales del editor.
-   **Física 2D:** Box2D - Motor de física 2D robusto y ligero.
-   **Audio:** miniaudio - Para reproducción de sonido y música de manera eficiente.
-   **Scripting:** Preparación para Python, JavaScript, C#, Lua (integración en fases futuras).

## Próximos Pasos Inmediatos

Actualmente, el motor tiene una ventana SDL2 con un contexto OpenGL 3.3 Core Profile inicializado correctamente. Hemos completado la descarga de todas las librerías necesarias (SDL2, glad, stb_image, Box2D, miniaudio, ImGui, Lua).

El siguiente objetivo es integrar las librerías restantes en CMake y nuestro código, empezando por Box2D, para luego implementar un sistema ECS mínimo y el renderizado de sprites con OpenGL. Esto nos acercará a un motor funcional y visual.
