# Trabajo C - Simulador Artemis - Escenario 4
# Integrantes: 
-Audisio Marcos
-Catuogno German
-Diaz Juan Cruz
-Diaz Lizandro 

Situación - Problema 4: Reingreso Atmosférico, Frenado Aerodinámico y Amerizaje (Trabajo, Energía e Impacto)
Tras completar el sobrevuelo lunar, el módulo de tripulación Orion (m = 10.400,0 kg) se separa del módulo de servicio y reingresa a la atmósfera terrestre a una velocidad hiperveloz de vi = 11,0 km/s (11.000,0 m/s, equivalente a 39.600,0 km/h o Mach 32) a una altitud de h = 120,0 km (120.000,0 m). El escudo térmico disipa la energía cinética mediante el trabajo de la fuerza de resistencia aerodinámica del aire (Froz), reduciendo la rapidez hasta vf = 25,0 m/s al momento de desplegar los paracaídas principales a una altitud de h = 2,50 km (2.500,0 m). Finalmente, la nave impacta en la superficie del Océano Pacífico (amerizaje) a una rapidez final segura de vimpacto = 8,0 m/s.

REGLAS DEL JUEGO

Sos el comandante de la capsula Orion (10400 kg), que vuelve de la Luna.
Entra a la atmosfera a 11000 m/s y 120 km de altura.

FASE 1 - Reingreso: elegis el angulo de entrada.
  - Menor a 5.5 grados: la capsula rebota en la atmosfera y se pierde.
  - Mayor a 7.0 grados: la desaceleracion es excesiva para la tripulacion.
  - Entre 5.5 y 7.0: reingreso seguro. Cuanto mas cerca de 6.25, mas puntos.

FASE 2 - Frenado: el escudo termico frena la capsula hasta 25 m/s.

FASE 3 - Paracaidas: elegis a que altura abrirlos.
  - Por debajo de 1.5 km abren tarde y el impacto es peligroso.
  - Por encima de 3.5 km el viento te aleja del buque de rescate.
  - La altura ideal es 2.5 km.

FASE 4 - Amerizaje: la estructura soporta hasta 5.0 veces su peso.

Puntaje maximo por mision: 100 puntos.

FUNCIONAMIENTO

El jugador comanda la tripulacion Orion en una capsula de 10.400 kg, que vuelve de la Luna y entra a la atmosfera a 11.000 m/s y 120 km de altura, y debe llevarla a salvo hasta el Oceano Pacifico, calculando el angulo de ingreso y la apertura del paracaidas.

las misiones se dividen en fases
1. El reingreso: donde el jugador elige el angulo de entrada
2. El frenado aerodinamico: el escudo termico frena la capsula hasta 25 m/s. El programa calcula la desaceleracion (en m/s^2 y en g) y la energia disipada.
3. Apertura del paracaidas: el jugador elige a que altura abrirlo
4. Amerizaje:4. se calcula la fuerza que ejerce el agua. Donde si supera 5 veces el peso de la capsula, la estructura fallara.

Se pueden jugar hasta 10 misiones por partida, Cada mision exitosa suma hasta 100 puntos: hasta 50 por la precision del angulo (ideal: 6,25 grados) y hasta 50 por la altura de apertura de los paracaidas (ideal: 2,5 km,). Al final de cada mision vas a ver tu puntaje y siempre que quieras podras tambien ver el reporte general de desempeño.

existe un modo analisis
Que permite ingresar datos propios y calcula las cuatro preguntas del escenario: (a) trabajo del rozamiento atmosferico, (b) desaceleracion media, (c) fuerza de impacto en el agua y (d) evaluacion del angulo de reingreso.

INSTRUCCIONES DE COMPILADO Y EJECUCION

Descargar el repositorio en la computadora, abrir la terminal MSYS2 UCRT64 localizarla en la carpeta donde se decargo el repositorio mediante el comando cd "Direccion de la carpeta", y ejecutar el comando "Make". Se crearan los archivos .o necesarios para el compilado junto al .exe donde se abrira la terminal y se podra ejecutar el juego.

USO DE LA IA

La inteligencia artificial nos ayudo tanto en la parte de sintaxis y en el entendimiento de los problemas fisicos, al no tener el suficiente conocimiento con el lenguaje de c, tuvimos varios problemas como con el copilado y el MSYS2, la modularicion y la division de codigo y header, ademas de el tratamiento del lenguaje de c de los array de caracteres para las validacion de entrada.
