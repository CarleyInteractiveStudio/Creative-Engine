Creative Engine 2 estará desarrollado en C++ y será un motor potente y robusto que utilizará diversas librerías. Funcionará a partir de materias y leyes; las materias serán cualquier objeto, y las leyes serán todo lo que le da sentido y reglas, incluidos los scripts. Creative Engine estará diseñado para ser compatible con múltiples lenguajes (Python, Lua, C#, C++, Orion — un lenguaje que estamos desarrollando).

El motor contará con un launcher que será una aplicación aparte, capaz de detectar el motor, similar a Unity y Unity Hub. Este launcher tendrá una interfaz atractiva que incluirá una pantalla de bienvenida, opción de inicio de sesión, gestión de proyectos, selección de versiones del motor y acceso rápido a documentación y tutoriales.

El launcher facilitará la administración de múltiples instalaciones del motor, permitiendo actualizar, instalar o eliminar versiones fácilmente. También ofrecerá integración con servicios en la nube para sincronización de proyectos y configuraciones.

El motor estará dividido en varias partes conectadas entre sí. Las librerías no estarán integradas directamente en el motor, pero sí conectadas a través del sistema de componentes.

Cada componente o ley debe estar disponible no solo en el inspector, sino también mediante una API de librería que pueda ser llamada a través de código. Lo primero que se podrá crear será una materia vacía, similar a un "empty" en Unity. Estas materias vacías serán importantes porque, al crear la mayoría de las cosas, solo será necesario agregar una materia vacía y los componentes correspondientes.

El motor contará con sistemas de prefabs, editor de sprites, etc. Soportará 2D, 2.5D y 3D, permitiendo flexibilidad para proyectos con diferentes necesidades visuales y de rendimiento. Los builds deberán ser compatibles con consola, Android, iOS, Mac, Windows y Linux, siendo estas las plataformas iniciales para el motor.

Descripción de un sistema de ventanas modular

Contenedores principales (Dock Areas): El sistema debe tener áreas contenedoras que puedan dividirse en secciones horizontales o verticales. Cada sección puede alojar una o varias ventanas.

Ventanas intercambiables (Editor Windows): Cada ventana es un módulo independiente que puede insertarse, quitarse o moverse entre contenedores sin afectar al resto del sistema.

Deben poder reemplazar a otra ventana en el mismo espacio.

Deben poder coexistir varias en un mismo contenedor como pestañas.

Gestión de pestañas (Tabbed Windows): En un mismo espacio, el sistema debe permitir agrupar múltiples ventanas en forma de pestañas, para que el usuario pueda alternar entre ellas sin necesidad de abrir nuevas áreas.

Redistribución automática: Cuando una ventana se elimina, el sistema debe ajustar el espacio restante para que no queden huecos vacíos. Cuando se añade una nueva ventana, debe acoplarse automáticamente en el área disponible o en una pestaña.

Layouts personalizables: El sistema debe permitir guardar y cargar configuraciones completas de ventanas (posición, tamaño, agrupación). Así, el usuario puede restaurar su entorno de trabajo fácilmente.

Persistencia de estado: Cada ventana debe recordar su contenido y configuración interna, incluso si se mueve o se reemplaza. El sistema debe restaurar este estado al reiniciar.

Extensibilidad: Debe ser posible crear nuevas ventanas personalizadas que se integren en el sistema, usando la misma lógica de acoplamiento, pestañas y persistencia.

En resumen, un sistema de ventanas modular debe estar basado en contenedores dinámicos que soporten acoplamiento, división y pestañas, con redistribución automática del espacio, layouts personalizables y persistencia de estado. Esto garantiza que las ventanas puedan reemplazarse, agruparse y organizarse de manera flexible sin romper la experiencia del usuario.

Concepto de los prefabs visuales del editor

Prefab estándar estilo Unity

Jerarquía (Hierarchy):

Ocupa la parte izquierda superior.

Sirve para mostrar la estructura de objetos/nodos de la escena.

Escena (Scene View):

Ocupa el área central.

Es el espacio principal de trabajo visual donde se manipulan los objetos.

Inspector:

Ocupa toda la parte derecha.

Muestra y permite editar las propiedades del objeto seleccionado.

Navegador de archivos (Project/Assets):

Se ubica en la parte inferior, extendiéndose bajo la Jerarquía y la Escena.

Permite acceder a recursos, scripts, imágenes, prefabs, etc.

Este layout es el clásico estilo Unity, con jerarquía a la izquierda, escena al centro, inspector a la derecha y navegador abajo.

Prefab alternativo

Jerarquía:

Ocupa la parte izquierda inferior.

Se coloca debajo del navegador de archivos.

Navegador de archivos:

Ocupa la parte izquierda superior.

Se convierte en la primera sección de la columna izquierda.

Escena:

Ocupa todo el área central.

Se mantiene como el espacio principal de trabajo.

Inspector:

Ocupa toda la parte derecha.

Igual que en el prefab estándar, dedicado a propiedades y ajustes.

Este layout es más vertical: primero el navegador de archivos arriba a la izquierda, luego la jerarquía debajo, y la escena sigue dominando el centro con el inspector a la derecha.

⚙️ Funcionalidades clave que debe tener el sistema

Ajuste libre: El usuario puede mover, redimensionar y reorganizar las ventanas según su gusto.

Guardado de layouts: El sistema debe permitir guardar la configuración actual en un archivo (JSON/XML) para restaurarla después.

Prefabs iniciales: Se ofrecen estos dos layouts como base, pero el usuario puede modificarlos y crear nuevos.

Persistencia: Al abrir el editor, se carga el último layout usado o uno de los prefabs por defecto.

Requisitos y detalles adicionales para el motor Creative Engine 2

Para que el motor Creative Engine 2 funcione de manera óptima y cumpla con las expectativas de robustez y flexibilidad, se requieren varios elementos y características clave:

Lista de componentes y sus tipos

¡Absolutamente! Con estos ajustes, simplificamos los nombres esenciales del motor, haciéndolos más concisos y potentes. Aquí tienes la lista final y completa de los componentes de tu motor (estos nombres aún no son oficiales):

Componentes de Lógica y Materia 🦠

Componente Final

Nombre de Unity (Original)

Función

Ley

MonoBehaviour / Script

Define la lógica, reglas y comportamiento.

Fisica

Rigidbody

Aplica las leyes de movimiento y las fuerzas.

Posicion

Transform

Define la ubicación, rotación y escala en el mundo.

ControladorDePersonaje

CharacterController

Manejo de movimiento cinemático.

Componentes de Colisión (Áreas) 📦

Componente Final

Nombre de Unity (Original)

Función

CajaDeArea

BoxCollider

Volumen de colisión en forma de caja.

EsferaDeArea

SphereCollider

Volumen de colisión en forma de esfera.

CapsulaDeArea

CapsuleCollider

Volumen de colisión en forma de cápsula.

MallaDeArea

MeshCollider

Volumen de colisión basado en la geometría 3D.

MaterialDeFisica

PhysicMaterial

Propiedades de superficie (fricción y rebote).

ArticulacionDeCuerpo

Joint

Conexión y restricción entre dos cuerpos físicos.

Componentes Visuales y Gráficos 🌟

Componente Final

Nombre de Unity (Original)

Función

Vision

Camera

Punto de vista para el renderizado de la escena.

Luz

Light

Emisor de iluminación en la escena.

Proyector

Projector

Proyección de textura sobre geometría.

FiltroDeMalla

MeshFilter

Almacena los datos de la geometría de la malla.

RenderizadorDeMalla

MeshRenderer

Dibuja la malla con sus materiales y texturas.

RenderizadorDePiel

SkinnedMeshRenderer

Dibuja la malla con deformación por huesos (animación).

SistemaDeParticulas

ParticleSystem

Gestión de efectos visuales (fuego, humo, chispas).

RenderizadorDeLinea

LineRenderer

Dibuja líneas o curvas.

Cielo

Skybox

Textura ambiental envolvente.

Componentes de Animación y Audio 🎧

Componente Final

Nombre de Unity (Original)

Función

Animacion

Animator / Animation

Máquina de estados para controlar la reproducción de clips.

Hueso

Avatar

Mapeo del esqueleto para reorientar animaciones.

FuenteDeSonido

AudioSource

Emite un clip de sonido.

ReceptorDeSonido

AudioListener

Escucha los sonidos en la escena.

Componentes de Interfaz y Navegación 📝

Componente Final

Nombre de Unity (Original)

Función

Lienzo

Canvas

Contenedor principal para todos los elementos de UI.

PosicionDeInterfaz

RectTransform

Maneja la posición, tamaño y anclajes de los elementos 2D.

AgenteDeNavegacion

NavMeshAgent

Entidad que calcula y sigue rutas en la superficie de navegación.

SuperficieDeNavegacion

NavMesh

Datos precalculados para el pathfinding (cálculo de rutas).

aun no son nombres oficiales

Lenguajes y compatibilidad

Soporte para múltiples lenguajes de scripting: Python, Lua, C#, C++, y el lenguaje propio Orion.

Interoperabilidad entre componentes escritos en diferentes lenguajes.

Arquitectura modular

Sistema de componentes desacoplados que permitan agregar, quitar o modificar funcionalidades sin afectar el núcleo.

API clara y accesible para manipulación de materias y leyes desde código.

Sistema de materias y leyes

Materias: objetos base que pueden ser vacíos o contener componentes.

Leyes: reglas y scripts que definen comportamientos y lógica.

Capacidad para crear materias vacías y agregar componentes dinámicamente.

Editor y herramientas

Launcher independiente con interfaz amigable para gestionar proyectos y versiones del motor.

Editor visual con soporte para 2D, 2.5D y 3D, permitiendo flexibilidad para distintos tipos de proyectos.

Sistemas de prefabs, editor de sprites, y herramientas para manipulación de assets.

Plataforma y despliegue

Soporte para builds multiplataforma: consolas, Android, iOS, Mac, Windows y Linux.

Optimización para rendimiento en cada plataforma.

Sistema de ventanas modular

Contenedores dinámicos con soporte para acoplamiento, división, pestañas y layouts personalizables.

Persistencia de estado y configuración de ventanas.

Extensibilidad para crear nuevas ventanas personalizadas.

Seguridad y rendimiento

Gestión eficiente de memoria y recursos.

Seguridad en la ejecución de scripts y componentes.

Herramientas para depuración y profiling.

Documentación y soporte

Documentación completa para desarrolladores y usuarios.

Ejemplos y plantillas para acelerar el desarrollo.

Nuevas funcionalidades y mejoras sugeridas

Para hacer el motor aún más robusto y competitivo, se incorporan las siguientes características adicionales:

Sistema de eventos y mensajería interna: Un sistema eficiente para que componentes y sistemas se comuniquen sin acoplamiento fuerte, facilitando extensibilidad y modularidad.

Sistema de scripting en tiempo real: Capacidad para recargar scripts sin reiniciar el motor, para acelerar el desarrollo iterativo.

Herramientas de profiling y análisis de rendimiento: Para que los desarrolladores puedan identificar cuellos de botella y optimizar sus proyectos.

Sistema de físicas avanzado: Soporte para físicas de colisiones complejas, físicas de vehículos, fluidos o soft bodies, si el motor apunta a proyectos más complejos.

Soporte para realidad aumentada (AR) y realidad virtual (VR): Si planeas que el motor sea competitivo en estas áreas emergentes.

Sistema de animación avanzado: Blend trees, animaciones por estado, IK (cinemática inversa), y soporte para animaciones faciales.

Sistema de materiales y shaders: Editor visual para materiales, soporte para shaders personalizados y pipeline gráfico moderno (Vulkan, DirectX 12, Metal).

Sistema de networking: Para juegos o aplicaciones multijugador, con sincronización, replicación y latencia controlada.

Sistema de gestión de recursos: Carga y descarga dinámica de assets, streaming de texturas y modelos para optimizar memoria.

Documentación y comunidad: Sistema de tutoriales interactivos, ejemplos de proyectos y comunidad activa para soporte y crecimiento.

Integración con sistemas de control de versiones: Para facilitar el trabajo en equipo y manejo de proyectos.

Soporte para plugins y extensiones: Que permita a terceros ampliar el motor sin modificar el núcleo.

Funcionalidades adicionales integradas según solicitud:

Inteligencia Artificial "Carl IA": Un sistema de IA integrado que asistirá en la creación de juegos mediante una API avanzada que permite manipular la escena y sus elementos. Carl IA podrá crear, modificar y eliminar objetos en la escena, gestionar archivos y recursos, crear y editar escenas completas, y automatizar tareas complejas de diseño y desarrollo. Su API ofrece funciones para:

Generación y modificación dinámica de contenido en tiempo real.

Control y manipulación de objetos y componentes dentro de la escena.

Creación, carga y guardado de escenas y proyectos.

Gestión avanzada de archivos y recursos asociados.

Integración con sistemas de scripting para personalización y extensión.

Asistencia inteligente en optimización y diseño de niveles.

Sistema de librerías con API amplia: Inspirado en Python, permitirá crear y conectar librerías para casi cualquier funcionalidad, ampliando enormemente la flexibilidad y personalización del motor.

Herramientas de colaboración: Funcionalidades para trabajo en equipo en tiempo real, facilitando la edición conjunta, sincronización de proyectos y comunicación integrada.

Sistema avanzado de iluminación y filtros: Soporte para técnicas modernas de iluminación global, filtros visuales, efectos gráficos avanzados y postprocesamiento.

Soporte de audio 3D: Audio espacial avanzado para mejorar la inmersión y realismo en juegos y aplicaciones, con soporte para efectos dinámicos y posicionamiento preciso.

Sistema de animación procedural: Generación dinámica de animaciones adaptativas sin necesidad de clips predefinidos, permitiendo movimientos más naturales y reactivos.

Optimización y simulación para hardware: Soporte para optimizar el rendimiento en hardware específico, simulación de hardware para pruebas y desarrollo, y adaptación automática a diferentes arquitecturas.

Soporte para múltiples idiomas: Internacionalización y localización para interfaces y contenido, facilitando la creación de proyectos multilingües y accesibles globalmente.

Seguridad avanzada: Protección contra exploits, integridad de datos, cifrado y sistemas de autenticación para garantizar la seguridad en proyectos sensibles y colaborativos.

Sistema de extensiones para Creative Engine: El motor contará con un sistema robusto y unificado que permitirá a desarrolladores y terceros crear librerías y extensiones (plugins y módulos) para ampliar las funcionalidades del motor sin modificar su núcleo. Este sistema estará ligado y será coherente, facilitando la creación, integración y gestión de nuevas herramientas, componentes, sistemas y flujos de trabajo, manteniendo la estabilidad y modularidad del motor. Las librerías y extensiones podrán ser distribuidas y gestionadas fácilmente a través del launcher, promoviendo una comunidad activa y un ecosistema en crecimiento.
