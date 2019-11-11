# 1. Introducción

La idea detrás del proyecto, recae en la necesidad moderna de proteger
información muy valiosa y confidencial. Para que esta información no
termine en manos de personas que no deberían tener acceso en primer
lugar, se busca crear un modelo eficiente, seguro y confiable para la
protección de datos, garantizando al usuario que sus datos u objetos
serán protegidos.

Por ese motivo llegamos a la idea de elaborar una caja fuerte a la que
se pueda tener acceso mediante una contraseña. Esta misma será elaborada
por el propietario y podrá ser cambiada a gusto siempre que lo disponga.
Además de la contraseña de usuario, la caja fuerte tendrá una contraseña
maestra que quedará en las manos de la empresa (grupo del proyecto) para
poder acceder a el interior de la caja en caso de: una contraseña
olvidada por el usuario y fallas en el sistema que necesiten un
reajuste.

La caja dispondrá de una alarma que se activará al ser introducida una
contraseña errónea un total de tres veces alertando al dueño sobre la
situación de sus pertenencias.

## 2. Contenido:
### 2.1. Descripción abreviada del contenido del proyecto

Una caja fuerte accesible mediante una contraseña creada por el
propietario. La programación se ejecutara mediando Arduino, además se
dispondrá de una pequeña pantalla que facilitara al usuario la
interacción con el software de seguridad y una alarma para más seguridad
tratando de cubrir todas las áreas posibles que brinden seguridad a lo
que se quiera guardar en ella.

### 2.2. Integrantes del equipo
Los integrantes pertenecientes al grupo 3º BG serán los siguientes:
Andrew Gigena, Gastón Cabrera y Richard Correa.

### 2.3. Asignaturas involucradas
Las asignaturas involucradas hasta ahora serán analógica y digital, en
el desarrollo del proyecto se evaluara la idea de incluir más materias o
simplemente dejar las ya involucradas.

### 2.4. Cronología del proyecto
En el comienzo del proyecto se pensó en utilizar tres sistemas de
seguridad: protección por huella dactilar, contraseña digital mediante
el teclado y una llave física.

Como computadora central de la caja fuerte utilizamos una Arduino debido
a la versatilidad y tamaño reducido de la misma. Además de que permite
modificar su funcionamiento sobre la marcha.

Tras investigar el coste de los módulos disponibles de huellas
dactilares para Arduino, la idea de utilizar este método de seguridad
fue descartada por exceso de coste.

Entonces esperábamos utilizar la llave física y la contraseña digital,
pero por inconvenientes que mencionaremos más adelante, tuvo que
descartarse la llave física.

Cuando finalizamos que sistema utilizar, nos pusimos manos a la obra con
el diseño de la caja fuerte. Para la construcción de la caja primero se
pensó qué materiales utilizar, en un principio se pensó hacerlo de metal
porque tomamos como referencia los diseños existentes en el mercado.
Pero luego de analizar los costos descubrimos que era mejor utilizar
madera compensada. Tras eso se pensó en la forma de unir las paredes de
la misma y llegamos a la conclusión de unirlas con doce ángulos de
metal.

El lugar donde decidimos comprar los materiales fue en la sucursal de
Sodimac por la proximidad del lugar. En este fue comprado las seis
tablas de madera, que se utilizarían para los lados de la caja y se
compró el doble fondo que es una madera más fina que la de los lados.
También los doce ángulos para unir las maderas previamente mencionados.

<p align="center"><img src="/imagenes/tablas.jpeg" width="460"></p>
<p align="center"><b>Figura 1. Seis tablas y la tabla del doble fondo</b></p>

Una vez obtenidos los materiales pasamos a construir la caja fuerte.
Primero fue construido el piso y los tres laterales principales. Dejando
a propósito la puerta y el techo para facilitar el acceso y colocación
de los componentes.

<p align="center"><img src="/imagenes/estructura-media-armada.jpeg" width="460"></p>
<p align="center"><b>Figura 2.  Estructura Inicial</b></p>

En el lapso de dos semanas, investigamos que componentes comprar para
comenzar a programar el proyecto. Fuimos comprando por partes y
avanzando en la programación de ese componente, a pesar de no tener
físicamente el mismo.

Se comenzó utilizando una Arduino Uno para realizar todo el desarrollo,
pero pronto se hizo evidente que el numero de pines seria un problema
para controlar tantos componentes simultáneamente. Por eso se decidió
comprar dos Arduino Mega, una clásica que se utilizaba para realizar
pruebas y otra de tamaño reducido pensada para ser soldada.


<p align="center"><img src="/imagenes/arduino-mega.jpg" width="460"></p>
<p align="center"><b>Figura 3.  Arduino Mega Clásica</b></p>

<p align="center"><img src="/imagenes/arduino-mega-mini.jpg" width="460"></p>
<p align="center"><b>Figura 4.  Arduino Mega Mini</b></p>

Durante la espera de los envíos internacionales, fue diseñada y
ensamblada la placa con la iluminación led que se encargara de mostrar
los intentos disponibles, y si la caja estaba abierta o cerrada.

<p align="center"><img src="/imagenes/ilumicacion-leds.png" width="460"></p>
<p align="center"><b>Figura 5.  Iluminación de ledes</b></p>

Mientras se buscaba un teclado acorde al proyecto, se hizo uno de
prueba, tras la compra del teclado de membrana su implementación a la
caja fue inmediata.

<p align="center"><img src="/imagenes/teclado-casero.png" width="460"></p>
<p align="center"><b>Figura 6.  Teclado de prueba</b></p>

Tras solucionar el asunto de la Arduino, continuamos con modelado de la
caja. Nos enfocamos en el calado de la puerta donde iría la pantalla y
los ledes. Las medidas del calado de la pantalla son de 7.5 x 2.5cm,
luego los orificios de los ledes los hicimos con una mecha de 7mm, el
calado de la puerta lo hicimos con un cincel.

<p align="center"><img src="/imagenes/calado-1.jpeg" width="460"></p>
<p align="center"><b>Figura 7.  Calado de Ledes/Pantalla</b></p>

Aquí es cuando notamos un error que nos llevo a descartar la llave
física, que impedía la colocación de la cerradura y perjudicaba la
estructura de la puerta.

Dentro de las compras tanto locales como internacionales, se encuentra
la pantalla, pensada como el medio principal de interacción que tendría
el usuario con el sistema.

<p align="center"><img src="/imagenes/pantalla.jpg" width="460"></p>
<p align="center"><b>Figura 8.  Pantalla LCD</b></p>

El teclado de membrana previamente mencionado como suplente al teclado
de botones.

<p align="center"><img src="/imagenes/teclado-comprado.png" width="460"></p>
<p align="center"><b>Figura 9.  Teclado de membrana</b></p>

Luego fue comprada la cerradura para comprobar que el orificio de la
cerradura en la puerta coincidiera, luego de llegar a un diseño
satisfactorio, fue implementado el código de la cerradura que seria
controlado por un relé.

<p align="center"><img src="/imagenes/cerradura-electromagnetica.png" width="460"></p>
<p align="center"><b>Figura 10. Cerradura Electromagnetica</b></p>

<p align="center"><img src="/imagenes/rele.jpg" width="460"></p>
<p align="center"><b>Figura 11. Relé</b></p>

Cuando todos los componentes estaban físicamente disponibles, realizamos
todas las pruebas de código y terminamos la puerta, fueron colocados
todos los componentes en la puerta para ser soldados y/o
interconectados.

Una vez realizado el calado en la puerta faltante y la colocación de los
componentes en la misma, procedimos a ensamblarla en la estructura.

Decidimos que la puerta quedaría colocada entre los laterales de la
caja. Para hacer esto, utilizamos dos bisagras, qué estarían colocados a
la derecha de la caja fuerte, una vez colocada la puerta procedimos a
colocar el asa, que mejor se acoplaba al diseño de la caja fuerte.
Colocamos el techo de la caja fuerte del mismo modo que colocamos los
laterales y el piso. Se hizo un calado dónde iría la entrada de
corriente, ubicada en la parte posterior de la caja y agujeros donde
estarían ubicados los parlantes de la alarma, estos últimos fueron
hechos con una mecha de 5mm.

Colocamos la entrada de corriente de 230v interconectada a una fuente
conmuta de 20v, en la salida de esta fue conectado un regulador de
voltaje LM317 para bajar el voltaje a 12v.

<p align="center"><img src="/imagenes/fuente-conmutada.jpeg" width="460"></p>
<p align="center"><b>Figura 12. Fuente Conmutada y Regulador de Voltaje</b></p>

***Falta el amplificador y el rele del mismo***

La caja fuerte fue pintada progresivamente mientras se avanzaba e la
misma. El color escogido fue negro mate ya que notamos que era el color
más frecuente en el mercado de las cajas fuertes, para que luzca más
estético y profesional.

<p align="center"><img src="/imagenes/" width="460"></p>
<p align="center"><b>Figura 13. Caja Fuerte terminada</b></p>

### 2.5 Complicaciones durante en producción
---------------
#### 2.5.1 Complicaciones en la programación

Durante la programación, fue necesario utilizar la EEPROM de manera
obligatoria, cada vez que inicia la caja comprueba diferentes valores
para impedir el uso o saltarse la programación para abrir la puerta.

\
Otra dificultad que ocurrió durante la programación fue impedir todos
los errores que imposibilitarían el inicio o continuación de la misma.
Eso fue realizado mediante distintos modos internos que el programa
accedería, por ejemplo el modo de nuevo pin. Este modo que se accede con
el único propósito de cambiar el pin actual o fijar uno inicial.

Los modos internos utilizados por el programa son los siguientes:

-   **Modo Alarma:** La alarma comienza a sonar y el usuario/empleado de
    la empresa debe colocar el código puk para desactivar la alarma y
    volver al Modo Ingreso de Pin
-   Modo Nuevo Pin: A través del teclado permite ingresar un pin que se
    guardara en la EEPROM como el pin almacenado. El usuario puede
    aceptar el pin que ingreso o volver a ingresar otro.
-   **Modo Ingreso de Pin:** El usuario debe ingresar el pin de seis
    dígitos. Tras confirmar, el sistema compara el pin ingresada con el
    pin almacenado, si la contraseña es correcta el sistema entra en el
    Modo Caja Abierta. Si en cambio, el pin es incorrecto restaría un
    intento y desactivaría un led de intentos. Cuando los intentos son
    iguales a cero el sistema se bloqueara para entrar en el Modo
    Alarma.
-   **Modo Caja Abierta:** Al iniciar este modo toma el tiempo de inicio
    para calcular posteriormente que hayan transcurrido cinco minutos.
    Pasados estos cinco minutos la cerradura automáticamente se
    cerraría. A pesar de esto, el usuario puede cerrar a voluntad la
    cerradura y cambiar el pin
-   Modo Programador: Permite modificar aspectos de la caja a traves de
    comandos especiales. Estos comandos son desactivar/activar la
    alarma, desactivar/activar cerradura, desactivar/activar primer
    inicio.

#### 2.5.2 Complicaciones de ensamblaje

Mientras realizamos la construcción de la caja obtuvimos una serie de
problemas, estos problemas fueron:

-   Al colocar las bisagras en la puerta, esta no se abría
    completamente. Por eso nos vimos obligados a alterar un poco el
    diseño de la misma, la solución que encontramos a este problema fue
    agregarle un complemento al lateral donde iban las bisagras y
    también sé lijo un ángulo de la puerta. Estos cambios son para
    mejorar la apertura de la puerta.

-   Otro de los problemas que tuvimos fue en la parte de la colocación
    de los laterales ya que la madera era compensada y al colocar los
    tornillos no apretaban lo suficiente. Este problema lo solucionamos
    con unos tornillos que se acoplan mejor a la madera compensada y
    también se trató de no quitar los tornillos una vez colocado en la
    madera.
-   El calado de la pantalla tuvo que ser movido unos centímetros hacia
    arriba, porque la pantalla y la iluminación led se solapaban las
    placas e impedía colocarlos correctamente.

Durante la colocación de los componentes tuvimos problemas con la
sección de los cables, estos cables se partieron y que tuvieron que ser
resoldados.

#### 2.5.3 Complicaciones en la soldadura

Se utilizo un estaño de mala calidad durante el comienzo de la
soldadura, con un alto grado de plomo. Esto nos obligo a cambiar por un
estaño de más calidad.

También tuvimos un cortocircuito que daño la pantalla LCD, este fue
producido por cables multifilares mal soldados, algo que nos obligo a
comprar otra y repensar como conectar las soldaduras para que no ocurra
lo mismo.

Al final notamos que una gota de estaño cayo en los pines del ATMEGA
2560 de la Arduino Mega, y tuvo que ser resoldado el chip SMD con mucho
cuidado para evitar cortocircuitar el integrado.

# 3. Comportamiento del sistema

## 3.1 Diagrama de bloques:
<p align="center"><img src="/imagenes/Diagrama.png"></p>

## 3.2 Comportamiento Funcional:
El programa dispone de dos modos principales, el modo usuario donde se
realizara casi todas las operaciones y el modo programador/empresa donde
hacen cambios de pruebas/funcionamientos.

### 3.2.1 Modo usuario:

Al inicio del sistema este comprueba si este es el primer inicio del
mismo. Si la respuesta es positiva, pide un nuevo pin de seis dígitos al
usuario. Luego pide una confirmación de la misma para guardar en la
EEPROM o reingresar otra contraseña distinta. En el caso de tener un pin
ya designado, se deberá ingresar el misma para acceder al interior de la
caja.

El usuario tiene cinco intentos para ingresar correctamente el pin
guardado, donde por cada intento fallido se apagará uno de los ledes de
intentos. En el caso de ocurrir cinco intentos fallidos, se encenderá un
led encendido de color rojo y se activara una alarma para alertar al
usuario de un posible intruso. La alarma seguirá activa hasta que la
empresa o el usuario ingrese el código puk.

En caso de ingresar el pin correcto, se encenderá un led de color verde,
se reinicia el número de intentos disponibles a cinco, y se accionara la
cerradura para tener el acceso a la caja fuerte.

Tras acceder a la caja fuerte, el usuario podrá almacenar o retirar el
contenido del mismo. También podrá cambiar la contraseña actual y/o
cerrar la puerta manualmente. Aun así está habilitado un sistema de
cerrado automático tras cinco minutos

### 3.2.2 Modo programador:

En este modo es accesible mediante a una pin especial que solo tendrá
conocimiento la empresa, en este modo se podrá: Tanto activar o
desactivar la alarma, abrir o cerrar la caja y cambiar la contraseña del
usuario, luego de finalizado estos procedimientos se saldrá del modo
programador para ingresar nuevamente al modo usuario, donde se activarán
la funciones asignadas.

# 4. Descripción de los componentes

## 4.1. Arduino Mega

## 4.2. Teclado
El teclado utilizado es uno de membrana de 12 botones en una
organización de 4 filas x 3 columnas. Es muy utilizado con las placas de
desarrollo Arduino, sensible al tacto por lo cual no se requiere una
gran presión para activar las teclas lo cual lo vuelve muy cómodo, la
ventaja de este teclado es que al tener una conexión flexible puede ser
colocado en cualquier superficie sin problemas.

## 4.3. Parlantes
Se utilizaron dos parlantes de 4Ω en serie, debido a que era lo
que más nos convenía en relación tamaño y potencia. Este dispositivo
esta destinado a la conversión de ondas eléctricas en energía mecánica
y de mecánica en acústica. Es por tanto la puerta por donde sale el
sonido al exterior desde los aparatos que posibilitaron su
amplificación.

## 4.4. Cerradura
Se utilizo esta cerradura por su tamaño reducido y voltaje ya que se
acciona con 12v. Este voltaje es compatible con el amplificador que
utiliza 12v algo conveniente para el proyecto. La cerradura está
compuesto por un solenoide, que es básicamente un electromagneto.

Estos están hechos de una gran bobina de alambre con una armadura (un
lingote de metal) en el medio. Cuando la bobina es energizada, el
lingote es tirado al centro de la bobina. Esto hace que el solenoide sea
capaz de empujar hasta el final de la cerradura.

Normalmente el lingote está expandido por lo tanto no puedes abrir la
puerta porque obstruye el camino. No usa ninguna potencia extra en este
estado. Cuando son aplicados 9-12VDC, el lingote se retrae por lo que no
sobresale más y la puerta puede ser abierta. Los solenoides vienen con
un lingote inclinado como se muestra, pero puedes abrirlo con los dos
tornillos de cabeza Philips y rotarlo 180 grados, por lo que podrán
coincidir con la puerta que quieras usarlos.

## 4.5. Pantalla
Utilizamos esta pantalla por ser muy compatible con la Arduino debido a
las librerías y ejemplos ya existentes. Esta pantalla es de 16x02
caracteres y opera con un voltaje de 5v. Tiene una interfaz paralela de
4 u 8 bits, nosotros utilizamos la segunda interfaz. Su color de texto
es blanco y la luz de fondo es de color azul.

## 4.6. Regulador de Voltaje
Utilizamos un regulador de voltaje porque la fuente es de 20v y
necesitamos reducir a 12v debido a que nuestro circuito funciona a este
voltaje. Para ello utilizamos un LM317, qué permite regular el voltaje
de entrada hacia un máximo de 1.5A y 37V de salida.

## 4.7. Amplificador
Usamos un amplificador de audio de 18w para el funcionamiento de los
parlantes de la alarma, ya que este era necesario para mejorar la
potencia del audio ya que sin el mismo, el sonido era muy bajo. Este
amplificador utiliza un TDA2030 cuyo rango de operación es de 6v a 18v,
y la salida al parlante de 4Ω a 8Ω

## 4.8. Relés
Se utilizo un relé de 5v porque era compatible con el Arduino y permite
cambiar la polaridad de normalmente cerrado (NC) al normalmente abierto
(NA). Los relés son dispositivos electromagnéticos. Funciona como un
interruptor controlado por un circuito eléctrico en el que, por medio de
una bobina y un electro imán, se acciona un juego de uno o varios
contactos que permiten abrir o cerrar otros circuitos eléctricos
independientes.

## 4.9. Iluminación de Ledes


# 5. Cotización del Proyecto
Las estimaciones de costes que tuvimos al comienzo del proyecto eran de
8500 $U, pero tras comprar todo y armarlo, el presupuesto final fue de
7320 $U, porque algunos productos los trajimos desde el extranjero.
  
 Cantidad | Material                           | Precio
--------- | ---------------------------------- | ---------
  1       | Cerradura electromagnética de 12v  | 1300 $U
  1       | Teclado de 4x3 botones             |  130 $U
  2       | Parlantes de 4Ω                    |  GRATIS
  1       | Arduino Mega 2560 Pro Embedded     |  330 $U
  1       | Pantalla LCD 1602A                 |  240 $U
  1       | Placas de prototipo de puntos      |  GRATIS
  1       | Relé de 5v Control, 220AC Salida   |  160 $U
  4       | 10 metros de cables de 0.5mm       |  320 $U
  7       | Tablones de 40cm x 40cm            | 1120 $U
  2       | Bisagras de hierro                 |   80 $U
  12      | Ángulos de Juntura                 |  720 $U
  2       | Aerosoles de Pintura               |  920 $U
  1       | Rollo de Estaño                    | 1600 $U
  1       | Pestillo                           |   80 $U