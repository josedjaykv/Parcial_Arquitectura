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


```c++
char inputBuffer[50];
int bufferIndex = 0;
bool recording = false;
```
Estas líneas declaran variables que se utilizarán para capturar la entrada del usuario. 

`inputBuffer` es un arreglo de caracteres que almacena la entrada del usuario.

`bufferIndex` es un índice que se utiliza para rastrear la posición actual en inputBuffer.

`recording` es una bandera que indica si el programa está actualmente capturando la entrada.

```c++
char convertToGrade(float N) {
    char nota;
     if (N >= 0 && N <= 3) {
        nota = 'A';
    } else if (N > 3 && N <= 4) {
        nota = 'B';
...
}
```
Esta es una función llamada `convertToGrade` que toma un valor numérico `N` como entrada del teclado matricial y devuelve la nota alfanumérica correspondiente. Se utiliza una serie de declaraciones `if` para determinar en qué condicion cae el valor `N` y luego asigna la nota correspondiente a la variable nota que se declaro como un char. Es decir si el usuario ingresa el numero 1 en el teclado matricial esta fumcion devolvera un A y asi sucesivamente se van considerando las siguientes condiciones:

1. Si la nota esta entre 0<=N<=3 devuelve A
2. Si la nota esta entre 3<N<=4 devuelve B
3. Si la nota esta entre 4<N<=5 devuelve C
4. Si la nota esta entre 5<N<=7 devuelve D
5. Si la nota esta entre 7<N<9 devuelve E
6. Si la nota esta entre 9<=N<=10 devuelve F

```c++
void processKey(char key) {
    if (key == '*' && !recording) {
        recording = true; // Iniciar la grabación del número
    } else if (key == '*' && recording) {
         if (bufferIndex > 0) {
            inputBuffer[bufferIndex] = '\0';  // Null-terminate the string
            printf("Numero ingresado: %s\n", inputBuffer);
            
            // Convertir la entrada a un número
            float N = atof(inputBuffer);
            
            if (N >= 0 && N <= 10) {
                char nota = convertToGrade(N);
                printf("Nota alfanumerica: %c\n", nota);
            } else {
                printf("Valor de nota no valido: %s\n", inputBuffer);
            }
            
            bufferIndex = 0;
        }
        recording = false; // Detener la grabación después de la conversión
        
    } else if (recording) {
        inputBuffer[bufferIndex++] = key;
    }
}
```
1. `void processKey(char key) {` : Esta línea define la función `processKey`. Toma un argumento `key`, que representa la tecla presionada del teclado matricial.
2. `if (key == '*' && !recording) {` : Comienza una estructura condicional `if`. Se verifica si la tecla presionada es * y si la grabación no está en curso (es decir, `recording` es `false`).
3. `recording = true;` : Si la condición del primer `if` se cumple, esto significa que se ha presionado * por primera vez para iniciar la grabación del número. Se establece recording en `true` para indicar que ahora estamos grabando una entrada numérica.
4. `} else if (key == '*' && recording) {` : Dentro de la estructura condicional `if`, se verifica si la tecla presionada es * nuevamente y si la grabación ya está en curso. Esto ocurre cuando el usuario presiona * por segunda vez para finalizar la grabación y convertir el número en una nota alfanumérica.
5. `if (bufferIndex > 0) {` : Se verifica si `bufferIndex` es mayor que 0. Esto garantiza que haya algo en `inputBuffer` para convertir antes de continuar. Si `bufferIndex` es 0, significa que no se ha ingresado ningún número y no hay nada que convertir.
6. `inputBuffer[bufferIndex] = '\0';` : Se coloca un carácter nulo `('\0')` al final del contenido en `inputBuffer`. Esto es importante porque `inputBuffer` es un arreglo de caracteres y debe estar null-terminado para que la funcion `atof` funcione correctamente.
7. `printf("Número ingresado: %s\n", inputBuffer);` : Imprime el número ingresado por el usuario en termite. Esto es útil para verificar que se ha capturado correctamente el número.
8. `float N = atof(inputBuffer);` : Utiliza la función `atof` para convertir la cadena en `inputBuffer` en un número decimal de punto flotante (float). `atof` toma la cadena y la interpreta como un número.
9. `if (N >= 0 && N <= 10) {` : Verifica si el número está dentro del rango válido, es decir, entre 0 y 10. Si no está en ese rango, se considera un valor de nota no válido.
10. `char nota = convertToGrade(N);` : Llama a la función `convertToGrade` para convertir el número `N` en una nota alfanumérica y almacena el resultado en la variable `nota`.
11. `printf("Nota alfanumérica: %c\n", nota);` : Imprime la nota alfanumérica calculada en termite.
12. `bufferIndex = 0;` : Reinicia `bufferIndex` a 0 para estar listo para capturar un nuevo número que ingrese el usuario.
13. `recording = false;` : Finalmente, se establece `recording` en `false` para indicar que la grabación ha terminado.
14. `} else if (recording) {` : Esta parte se ejecuta cuando no se presiona *, pero la grabación está en curso.
15. `inputBuffer[bufferIndex++] = key;` : Aquí, la tecla actual (`key`) se agrega al búfer de entrada `inputBuffer`. `bufferIndex` se utiliza como un índice para rastrear la posición actual en el búfer, y después de agregar la tecla, se incrementa para prepararse para la próxima tecla. Esto permite la captura de múltiples dígitos y caracteres para formar un número.

```c++
int main() {
    while (true) {
        for (int i = 0; i < numRows; i++) {
            rowPins[i] = 0;

            for (int j = 0; j < numCols; j++) {
                if (!colPins[j]) {
                    processKey(keyMap[i][j]);
                    ThisThread::sleep_for(500ms);  // Evita lecturas múltiples mientras la tecla está presionada
                }
            }

            rowPins[i] = 1;
        }
    }
}
```
En la función `main`, se ejecuta un bucle infinito. En este bucle, se recorren todas las filas del teclado matricial y se comprueban las columnas para detectar cuándo se presiona una tecla. Cuando se detecta una tecla presionada, se llama a la función `processKey` para manejarla. La pausa de 500 ms evita múltiples lecturas cuando una tecla se mantiene presionada. Luego, se cambian las filas para repetir el proceso en la siguiente fila del teclado matricial.

## Generar colores en un LED RGB

Para generas estos colores usamos la función `void showColors()`

Esta función está diseñada para permitir al usuario seleccionar colores ingresando valores numéricos desde un teclado de membrana y luego mostrar el color correspondiente utilizando LEDs RGB.

`char inputBuffer[32];` Declaramos un arreglo de caracteres llamado `inputBuffer` con capacidad para almacenar hasta 32 caracteres. Este buffer se utiliza para almacenar temporalmente las teclas presionadas por el usuario en el teclado de membrana.

`int bufferIndex = 0;` Inicializamos una variable llamada `bufferIndex` con un valor de 0. Esta variable se utiliza para realizar un seguimiento de la posición actual en el inputBuffer, es decir, la posición donde se debe almacenar el próximo carácter ingresado.

`unsigned int numerosDecimales[3];` Declaramos un arreglo de enteros sin signo llamado numerosDecimales con una longitud de 3 elementos. Este arreglo se utiliza para almacenar los 3 valores numéricos que representan la intesidad de los LEDs RED, GREEN, BLUE ingresados por el usuario desde el teclado de membrana. Por ejemplo si el usuario quiere visualizar el color rojo debe agregar estos valores [255, 0, 0] que se guardarán en el arreglo `numeroDecimales`.

`int numeroActual = 0;` Inicializamos una variable llamada numeroActual con un valor de 0. Esta variable se utiliza para realizar un seguimiento de cuántos valores numéricos se han ingresado hasta el momento. La función espera tres valores numéricos en total.

`while (numeroActual < 3) {` Inicializamos un bucle while que se ejecutará hasta que se ingresen los tres valores numéricos que necesitamos para formar el color.

`for (int i = 0; i < numRows; i++) {` Hacemos un bucle for que recorre las filas de nuestro teclado de membrana.

`rowPins[i] = 0;` Establecemos en bajo (0) el pin correspondiente a la fila actual en el teclado de membrana. Esto asegura que solo se lean las teclas de una fila a la vez.

`for (int j = 0; j < numCols; j++) {` Hacemos otro bucle for que recorre las columnas del teclado de membrana.

`if (!colPins[j]) {` Verificamos si el pin de la columna actual en el teclado de membrana está en bajo (es decir, si una tecla se ha presionado en esa posición).

`char keyPressed = keyMap[i][j];` Obtenemos el carácter asociado a la tecla presionada en la posición actual y lo guardamos en la variable `keyPressed`.

`if (keyPressed == '*') {` Verificamos si la tecla presionada es un asterisco (*), que en nuestro caso se utiliza como una especie de "enter".

`inputBuffer[bufferIndex] = '\0';` Se agrega un carácter nulo al final del inputBuffer para convertirlo en una cadena de caracteres válida.

`sscanf(inputBuffer, "%u", &numerosDecimales[numeroActual]);` Utilizamos la función sscanf para convertir la cadena almacenada en inputBuffer en un valor numérico sin signo, que se almacena en el arreglo `numerosDecimales` en la posición `numeroActual`. 

`printf("Número %d ingresado: %u\n", numeroActual + 1, numerosDecimales[numeroActual]);` Imprimimos el número recien ingresado indicando que número hemos ingresado, por ejemplo: "Número 1 ingresado: 255".

`memset(inputBuffer, 0, sizeof(inputBuffer));` Se borra el contenido del `inputBuffer` para prepararlo para el próximo valor numérico.

`bufferIndex = 0;` Se reinicia el índice del buffer a 0 para empezar a almacenar el próximo carácter desde el principio.

`numeroActual++;` Se incrementa el contador de valores numéricos ingresados.

```c++ 
else {
inputBuffer[bufferIndex] = keyPressed;
bufferIndex++;
}
```

Si la tecla presionada no es un asterisco (*), se agrega al inputBuffer y se incrementa el índice del buffer para la próxima entrada.

`ThisThread::sleep_for(500ms);` Se espera durante 500 milisegundos antes de leer la siguiente columna. Esto evita la lectura múltiple mientras una tecla está presionada.

`rowPins[i] = 1;` Se vuelve a establecer en alto (1) el pin de la fila actual en el teclado de membrana para prepararse para la siguiente iteración del bucle for que recorre las filas.

**Fin del bucle for**

**Fin del bucle while**

```c++
float red = 1 - (float)(numerosDecimales[0] / 255.0f);
float green = 1 - (float)(numerosDecimales[1] / 255.0f);
float blue = 1 - (float)(numerosDecimales[2] / 255.0f);

setRGBColor(red, green, blue);
```

Después de salir del bucle while, se calculan los valores de rojo (red), verde (green) y azul (blue) en función de los valores numéricos ingresados. Estos valores se convierten en flotantes entre 0 y 1, y se utilizan para establecer el color en los LEDs RGB mediante la función `setRGBColor`.

## Función de raices de un polinomio de grado 2 

(Mirar esta funcionalidad bien ejecutada en el siguiente repositorio: https://github.com/DiegoColBdz/Raices-Parcial2023.git)
(Nos falto corregirlo en este repositorio)

```c++
char inputBuffer[50];
int bufferIndex = 0;
bool recording = false;
```
Aqui declaramos variables para manejar la entrada de coeficientes.
`inputBuffer` es un arreglo de caracteres que almacenará la entrada del usuario.
`bufferIndex` es un índice para rastrear la posición actual en `inputBuffer`.
`recording` es una bandera que indica si estamos en modo de grabación de coeficientes.

```c++
    unsigned int coeficientes[3];
    int numeroActual = 0;
```
Creamos un arreglo `coefficients` para almacenar los coeficientes a, b, y c del polinomio de grado 2.
`coefficientIndex` es un índice para rastrear qué coeficiente se está ingresando actualmente.
```c++
void calculateRoots(int a, int b, int c) {
    int discriminant = b * b - 4 * a * c;
    if (discriminant > 0) {
        // Dos raíces enteras
        int root1 = (-b + sqrt(discriminant)) / (2 * a);
        int root2 = (-b - sqrt(discriminant)) / (2 * a);
        printf("Raíces enteras: %d y %d\n", root1, root2);
    } else if (discriminant == 0) {
        // Una raíz real
        int root = -b / (2 * a);
        printf("Raíz entera única: %d\n", root);
    } else {
        // Raíces complejas (no aplicable en este caso)
        printf("El polinomio no tiene raíces enteras.\n");
    }
}
```
Definimos una función `calculateRoots` que toma tres coeficientes enteros `a, b y c` y calcula las raíces del polinomio de grado 2 utilizando la fórmula cuadrática o mejor conocida como formula del estudiante. La función verifica si el discriminante es mayor que 0 (dos raíces reales), igual a 0 (una raíz real) o menor que 0 (raíces complejas), y muestra las raíces en la pantalla.

```c++
void processKey(char key) {
    if (recording) {
        // Verificamos si estamos en modo de grabación
        if (key == '*') {
            // Si el usuario presiona '*', indica que ha terminado de ingresar el coeficiente actual
            inputBuffer[bufferIndex] = '\0';  // Null-terminate the string
            printf("Coeficiente %c: %s\n", 'a' + coefficientIndex, inputBuffer);

            // Analizamos y almacenamos el coeficiente ingresado en la matriz 'coefficients'
            if (sscanf(inputBuffer, "%d", &coefficients[coefficientIndex]) == 1) {
                // La función 'sscanf' analiza el contenido de 'inputBuffer' y extrae un número entero
                coefficientIndex++;
                if (coefficientIndex < 3) {
                    // Si todavía hay coeficientes por ingresar, solicitamos el siguiente
                    printf("Por favor, ingrese el coeficiente %c: ", 'a' + coefficientIndex);
                    bufferIndex = 0;  // Reiniciamos el índice del búfer para el próximo coeficiente
                } else {
                    // Si se han ingresado todos los coeficientes, mostramos un mensaje con los coeficientes
                    printf("Coeficientes ingresados: a=%d, b=%d, c=%d\n", coefficients[0], coefficients[1], coefficients[2]);

                    // Calculamos las raíces llamando a la función 'calculateRoots' con los coeficientes
                    calculateRoots(coefficients[0], coefficients[1], coefficients[2]);

                    coefficientIndex = 0;  // Reiniciamos el índice de coeficiente para futuras entradas
                    recording = false;    // Salimos del modo de grabación
                }
            } else {
                // Si la entrada no es un número válido, mostramos un mensaje de error
                printf("Entrada inválida. Por favor, ingrese un número válido.\n");
                bufferIndex = 0;  // Reiniciamos el índice del búfer para ingresar nuevamente el coeficiente
            }
        } else {
            // Si no se presiona '*', significa que estamos ingresando dígitos del coeficiente actual
            inputBuffer[bufferIndex++] = key;  // Almacenamos el dígito en el búfer
        }
    } else {
        // Si no estamos en modo de grabación y el usuario presiona '*', iniciamos la grabación
        if (key == '*') {
            recording = true;  // Entramos en modo de grabación
            printf("Por favor, ingrese el coeficiente %c: ", 'a' + coefficientIndex);  // Solicitamos el primer coeficiente
            bufferIndex = 0;  // Reiniciamos el índice del búfer para la nueva entrada
        }
    }
}
```
1. La función `processKey` se encarga de manejar las teclas presionadas por el usuario y procesar la entrada de coeficientes.
2. La variable `recording` se utiliza para rastrear si estamos en modo de grabación, es decir, si el usuario está ingresando un coeficiente.
3. Si estamos en modo de grabación `(recording == true)`, la función verifica si se ha presionado la tecla *. Si es así, significa que el usuario ha terminado de ingresar el coeficiente actual y se procede a procesar y almacenar ese coeficiente.
4. Se utiliza `inputBuffer` para almacenar temporalmente la entrada del usuario como una cadena de caracteres. Cuando se presiona *, se agrega un carácter nulo ('\0') al final de la cadena para convertirla en una cadena de caracteres válida.
5. Se utiliza la función `sscanf` para analizar la cadena `inputBuffer` y extraer un número entero. Si la conversión tiene éxito `(retorna 1)`, el coeficiente se almacena en el arreglo `coefficients` en la posición correspondiente (`coefficientIndex`) y se incrementa `coefficientIndex.`
6. Si todavía hay coeficientes por ingresar `(coefficientIndex < 3)`, se solicita al usuario que ingrese el siguiente coeficiente y se reinicia `bufferIndex` para comenzar a recopilar la entrada nuevamente.
7. Si se han ingresado todos los coeficientes `(coefficientIndex == 3)`, se muestra un mensaje con los coeficientes ingresados, se calculan las raíces llamando a `calculateRoots`, se reinicia `coefficientIndex` y se sale del modo de grabación
8. Si la entrada del usuario no es un número válido `(la conversión con sscanf falla)`, se muestra un mensaje de error y se reinicia `bufferIndex` para que el usuario pueda ingresar nuevamente el coeficiente.
9. Si no estamos en modo de grabación `(recording == false)` y el usuario presiona *, comenzamos el proceso de grabación iniciando `recording`, mostrando un mensaje para ingresar el primer coeficiente y reiniciando `bufferIndex` para la nueva entrada.

En sintesis `processKey` maneja la entrada del usuario para que pueda ingresar coeficientes uno por uno, verificar la validez de la entrada y calcular las raíces una vez que todos los coeficientes han sido ingresados correctamente.

```c++
int main() {
    printf("Ingrese los coeficientes del polinomio de grado 2.\n");
    while (true) {
        for (int i = 0; i < numRows; i++) {
            rowPins[i] = 0;
            
            for (int j = 0; j < numCols; j++) {
                if (!colPins[j]) {
                    processKey(keyMap[i][j]);
                    ThisThread::sleep_for(500ms);  // Evita lecturas múltiples mientras la tecla está presionada
                }
            }

            rowPins[i] = 1;
        }
    }
}    
```
En la función principal `main`, inicializamos el programa mostrando un mensaje "Ingrese los coeficientes del polinomio de grado 2". Luego, entramos en un bucle infinito que escanea las teclas del teclado matricial. Para cada fila y columna, llamamos a `processKey` para procesar las teclas presionadas y evitar lecturas múltiples mientras una tecla está presionada.

## Main

```c++
printf("Por favor, elija una opción y presione * para confirmar:\n");
printf("1. Calcular raíces de un polinomio de grado 2\n");
printf("2. Mostrar colores\n");
```

Primero le preguntamos al usaurio 

# Manual de Usuario

## Para la funcion de las notas:
1. Cuando el programa se esté ejecutando, deberías ver que el programa está esperando una entrada del usuario.
2. Presiona la tecla * en el teclado matricial. Esto iniciará la grabación de un número.
3. Luego de presionar *, puedes ingresar un número de 0 a 10 utilizando las teclas numéricas en el teclado matricial. Por ejemplo, si deseas ingresar el número 7, presiona 7, y así sucesivamente.
4. Después de ingresar el número, presiona nuevamente la tecla * para finalizar la grabación del número.
5. El programa tomará el número ingresado, lo convertirá en una nota alfanumérica según los rangos especificados y mostrará la letra correspondiente en la salida estándar.
6. Por ejemplo, si ingresaste el número 7, el programa debería mostrar "Nota alfanumérica: D" en la salida estándar.
7. Puedes repetir el proceso para ingresar y convertir otros números tantas veces como desees.
   nota: Si ingresas un número fuera del rango válido (0 a 10), el programa indicará que el valor de nota no es válido.
## Para la funcion de las raices de un polinomio de grado 2:
1. Cuando inicia el programa, verás el mensaje inicial en la pantalla: "Ingrese los coeficientes del polinomio de grado 2."
2. Presiona el botón *. La pantalla mostrará: "Por favor, ingrese el coeficiente a:"
    Ingresa el valor del coeficiente 'a' como un número entero. Por ejemplo, si 'a' es igual a 2, presiona los botones 2 y luego presiona * para confirmar.
3. Después de ingresar 'a', la pantalla mostrará: "Por favor, ingrese el coeficiente b:"
    Ingresa el valor del coeficiente 'b' de la misma manera que ingresaste 'a'. Por ejemplo, si 'b' es igual a 3, presiona los botones 3 y luego presiona * para confirmar.
4. Luego de ingresar 'b', la pantalla mostrará: "Por favor, ingrese el coeficiente c:"
    Ingresa el valor del coeficiente 'c' de la misma manera que ingresaste 'a' y 'b'. Por ejemplo, si 'c' es igual a 1, presiona los botones 1 y luego presiona * para confirmar.
5. Una vez que ingresaste 'a', 'b' y 'c', el programa mostrará un mensaje en pantalla con los coeficientes que ingresaste. Por ejemplo: "Coeficientes ingresados: a=2, b=3, c=1".
6. Luego de mostrar los coeficientes ingresados, el programa calculará automáticamente las raíces del polinomio de grado 2 utilizando la fórmula cuadrática.

## Observaciones

1. En el programa de la notas es mejor utilizar un `switch` para cada caso de la notas en vez de tener muchos `else if`, que al momento se verlos en codigo son menos amigables y en un `switch` se ve mejor la informacion de los casos a tratar
2. Para la funcionalidad de la raices de un polinomio mirar el siguiente repositorio de Diego Collazos alli tambien se encuentra el readMe: https://github.com/DiegoColBdz/Raices-Parcial2023.git
