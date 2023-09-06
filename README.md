# Parcial de Arquitectura de HardWare
Por Diego Collazos y José David Jayk Vanegas


## Algunas funciones y declaraciones



### Declaramos las variables ledR, ledG y ledB
```c++
PwmOut ledR(LED1);
PwmOut ledG(LED2);
PwmOut ledB(LED3);
```

`PwmOut ledR(LED1);`

Esta línea declara una variable llamada ledR de tipo PwmOut, que se utiliza para controlar la intensidad luminosa (brillo) de un LED. Está configurada para controlar el LED físico conectado al pin LED1 en una placa de desarrollo. La clase PwmOut se utiliza comúnmente para controlar LEDs y otros dispositivos que requieren un control preciso de la intensidad luminosa mediante modulación por anchura de pulso (PWM).

Lo mismo se hace con ledG y ledB


### Definimos la función setRGBColor

```c++
void setRGBColor(float red, float green, float blue) {
    ledR = red;
    ledG = green;
    ledB = blue;
}
```

Definimos una función llamada setRGBColor que toma tres argumentos de tipo float: red, green y blue. Esta función se utiliza para establecer el color de los LEDs RGB controlados por ledR, ledG y ledB. La función toma los valores de intensidad luminosa para los componentes rojo, verde y azul, respectivamente, y los asigna a las variables ledR, ledG y ledB utilizando PWM para controlar el brillo de cada componente del LED RGB.

### Matriz bidimensional para representar el teclado de membrana

```c++
const int numRows = 4;
const int numCols = 4;

char keyMap[numRows][numCols] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}
};
```

Definimos una matriz bidimensional de caracteres llamada keyMap que representa la disposición del teclado de membrana de 4 filas por 4 columnas. Lo definimos como 4x4 por si en el futuro disponemos de un teclado 4x4, esto no afecta el funcionamiento del programa.

### Pines de entrada y salida

Definimos dos arreglos de objetos que interactúan con los pines de entrada y salida digital de nuestra tarjeta de desarrollo.

```c++
DigitalOut rowPins[numRows] = {DigitalOut(D2), DigitalOut(D3), DigitalOut(D4), DigitalOut(D5)};
DigitalIn colPins[numCols] = {DigitalIn(D6), DigitalIn(D7), DigitalIn(D8), DigitalIn(D9)};
```
 
`DigitalOut` es una clase que se utiliza para controlar pines de salida digital en nuestra tarjeta de desarrollo.

`{DigitalOut(D2), DigitalOut(D3), DigitalOut(D4), DigitalOut(D5)}` nicializa el arreglo rowPins con cuatro objetos DigitalOut, cada uno asociado a un pin específico de la tarjeta de desarrollo (en este caso, los pines D2, D3, D4 y D5).

`DigitalIn` es una clase que se utiliza para leer el estado de pines de entrada digital en una tarjeta de desarrollo.

`{DigitalIn(D6), DigitalIn(D7), DigitalIn(D8), DigitalIn(D9)}` inicializa el arreglo colPins con cuatro objetos DigitalIn, cada uno asociado a un pin específico de la tarjeta de desarrollo (en este caso, los pines D6, D7, D8 y D9). 

## Función de notas alfanuméricas

