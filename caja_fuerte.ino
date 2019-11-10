// ================== Librerias ================== 
//    Keypad.h          - Permite utilizar el teclado de 4x3
//    LiquidCrystal.h   - Permite utilizar la pantalla LCD de 16x2
//    EEPROM.h          - Permite utilizar la EEPROM interna de la arduino mega
// ===============================================

#include <Keypad.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>




// ========== Configuración del teclado ==========
//              ---------------------    
//              | ARDUINO | TECLADO |
//              |---------|---------|
//              |   19    |    1    |
//              |   21    |    2    |
//              |   23    |    3    |
//              |   25    |    4    |
//              |   27    |    5    |
//              |   29    |    6    |
//              |   31    |    7    |
//              ---------------------
// ===============================================

// Se define el tamaño del teclado: 4 filas y 3 columnas
const byte ROWS = 4; const byte COLS = 3;   

// Se define el tipo de dato que el sistema interpretara 
// al presionar la tecla.
char keys[ROWS][COLS] = {                   
    {'1','2','3'},
    {'4','5','6'},
    {'7','8','9'},
    {'N','0','Y'}
};

// Se define en cuales pines se encuentra conectado el teclado
byte rowPins[ROWS] = {19, 21, 23, 25};
byte colPins[COLS] = {27, 29, 31};

// Se pone en marcha el funcionamiento del teclado
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );




// ========= Configuración de la pantalla =========
//              ---------------------    
//              | ARDUINO | PANTALLA |
//              |---------|----------|
//              |   GND   |    VSS   |
//              |   5V    |    VDD   |
//              |         |    VO    |
//              |   33    |    RS    |
//              |   GND   |    RW    |
//              |   35    |    E     |
//              |         |    D0    |
//              |         |    D1    |
//              |         |    D2    |
//              |         |    D3    |
//              |   37    |    D4    |
//              |   39    |    D5    |
//              |   41    |    D6    |
//              |   43    |    D7    |
//              |   5v    |    A     |
//              |   GND   |    K     |
//              ----------------------
// ================================================

// Se establecen los pines que estaran conectados
byte rs = 33, en = 35, d4 = 37, d5 = 39, d6 = 41, d7 = 43;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);




// ============ Configuraciones extras ============
// Se establecen otros pines que seran utilizados 
// ================================================

const byte PIN_LED_1           = 17;
const byte PIN_LED_2           = 15;
const byte PIN_LED_3           = 13;
const byte PIN_LED_4           = 11;
const byte PIN_LED_5           = 9;
const byte PIN_LED_PUERTA      = 7;
const byte PIN_LED_ALARMA      = 5;
const byte PIN_RELE_PUERTA     = 32;
const byte PIN_RELE_ALARMA     = 34;





// ===============VARIABLES GLOBALES===============
// Estas son las variables que se utilizan en todo 
// el codigo, para manejar el flujo del programa.
// ================================================

// Estos variables se utilizan para controlar cuando un
// usuario puede entrar o salir de un modo.
bool controlInicio          = false;
bool controlPinAsignado     = false;
bool controlPinIngresado    = false;
bool controlCajaAbierta     = false;
bool controlAlarma          = false;

// Estas variables se leen de la EEPROM para realizar acciones.
bool opcPrimerInicio        = false;    // Permite acceder al cambio de pin 
bool opcEstadoAlarma        = false;    // Hace sonar la alarma
bool opcEstadoPin           = false;    // Abre la puerta

// Estas son variables en forma de array para almacenar 
// en la memoria RAM los pines
byte pinGuardado[6];
byte pinMemoria[6];

// Estas variables se utilizan para activar el modo programador
// al inicio de la caja fuerte.
int debugcode               = 0;
bool debugmode              = false;

// Estas son direcciones de memoria de la EEPROM. Se utiliza
// para almacenar y/o leer datos persistentes tras reinicios.
const byte dirPrimerInicio     = 0;
const byte dirNumIntentos      = 1;
const byte dirAlarma           = 2;
const byte dirCajaAbierta      = 3;
const byte dirPinGuardado      = 95; 

// Otras variables, se definen globalmente y tienen muchos usos.
byte pinX                   = 0;
byte intentos               = 0;





// =============== Función Inicial ================
// Se ejecuta una sola vez durante el inicio. Se 
// definen la configuración de los pines. Se inicia 
// la pantalla y el puerto serial.
// ================================================

void setup() {   
    // Inicializa el puerto serial para enviar información
    // hacia la computadora.
    Serial.begin(9600);
    while (!Serial) {
        ; 
    }
    
    // Inicializa la pantalla con el tamaño 16x02, limpia el
    // contenido de la misma y activa el parpadeo del cursor.
    // Tras eso muestra el mensaje de inicio.
    lcd.begin(16, 2);
    lcd.clear();
    lcd.blink();
    textoPreInicio();

    // Se establecen los pines extras como salida de datos.
    pinMode(PIN_LED_1,          OUTPUT);
    pinMode(PIN_LED_2,          OUTPUT);
    pinMode(PIN_LED_3,          OUTPUT);
    pinMode(PIN_LED_4,          OUTPUT);
    pinMode(PIN_LED_5,          OUTPUT);
    pinMode(PIN_LED_PUERTA,     OUTPUT);
    pinMode(PIN_LED_ALARMA,     OUTPUT);
    pinMode(PIN_RELE_ALARMA,    OUTPUT);
    pinMode(PIN_RELE_PUERTA,    OUTPUT);
}





// ============== Función Principal ===============
// Se ejecuta indefinidamente tras terminar la 
// funcion inicial. Se encarga de cambiar entre los
// distintos modos del sistema. Lee las direcciones
// de la EEPROM, guarda el dato en las variables
// de opcion y accede a un modo hasta que el valor
// de la variable de control cambie.
// ================================================

void loop() { 

    // Espera al usuario/programador a que comience
    // el programa presionando el boton cero.
    while (controlInicio == false) {
        controlInicio = modoComienzo();
    }
    textoInicio();


    // Carga desde la EEPROM, el numero de intentos
    // disponibles. Ilumina los correspondientes LEDS.
    intentos = EEPROM.read(dirNumIntentos);
    controlLeds(intentos, true);


    // Comprueba si la alarma deberia sonar, de ser asi
    // empieza a sonar la alarma y entra en el modo alarma.
    opcEstadoAlarma = EEPROM.read(dirAlarma);
    if (opcEstadoAlarma == true) {
       Serial.println(F("# Modo > Alarma sonando"));
        textoAlarma();

        controlLeds(7, true);
        digitalWrite(PIN_RELE_ALARMA, HIGH);
        while (controlAlarma == false) {
            controlAlarma = modoAlarma();
        }    
    } else {
        controlLeds(7, false);
        digitalWrite(PIN_RELE_ALARMA, LOW);
    }


    // Comprueba si es el primer inicio de la caja fuerte,
    // de ser asi entra en el modo nuevo pin. En caso contrario,
    // accederia al modo ingreso de pin.
    opcPrimerInicio = EEPROM.read(dirPrimerInicio);
    if (opcPrimerInicio == true) {

        // Muestra por serial y en pantalla el modo
        Serial.println(F("# Modo > Nuevo pin"));
        textoNuevoPin();            
      
        // Accede al modo nuevo pin
        while (controlPinAsignado == false) {
            controlPinAsignado = modoNuevoPin();
        }
   
        limpiarLCD();      

    } else {

        // Muestra por serial y en pantalla el modo
        Serial.println(F("# Modo > Ingreso de pin"));
        textoIngresePin();

        // Accede al modo ingreso de pin
        while (controlPinIngresado == false) {
            controlPinIngresado = modoIngresarPin();
        }
        
        limpiarLCD(); 

    }

    // Comprueba si el pin fue ingresado correctamente tras
    // entrar al modo ingreso de pin, de ser asi entra al 
    // modo de caja abierta.
    if (controlPinIngresado == true) {
        opcEstadoPin = EEPROM.read(dirCajaAbierta);
        if (opcEstadoPin == true) {
            // Muestra por serial y en pantalla el modo
           Serial.println(F("# Modo > Caja Abierta"));
            textoCajaAbierta();

            // Accede al modo caja abierta
            digitalWrite(PIN_RELE_PUERTA, HIGH);
            while (controlCajaAbierta == false) {
                controlCajaAbierta = modoCajaAbierta();
            }
        } else {
            digitalWrite(PIN_RELE_PUERTA, LOW);
        }
    }
}




// ============== Funciones de texto ====================================================
//  Dedicadas al texto e información almacenada:
//  -> textoPreInicio        - Muestra por serial y por LCD el mensaje de introduccion. 
//  -> textoNuevoPin     - Muestra por el LCD el mensaje de nuevo pin.
//  -> textoConfirmarPin - Muestra por el LCD el mensaje de confirmar pin.
//  -> textoIngresePin   - Muestra por el LCD el mensaje de ingrese pin.
//  -> textoAlarma       - Muestra por el LCD el mensaje de ingrese puk.
//  -> leerMemoriaPin    - Muestra por el Serial el pin almacenado en memoria.     
//  -> leerEEPROMPin     - Muestra por el Serial el pin almacenado en la EEPROM.
// ======================================================================================

void textoPreInicio() {  
   Serial.println(F("Bienvenido a la consola de la Caja Fuerte.\n"   )); 
   Serial.println(F("Presione cero para continuar.\n"                ));
    delay(50);

    limpiarLCD(); 
    escribirLCD(0, 0, " Presione cero  ");
    escribirLCD(0, 1, " para continuar ");  
}

void textoInicio() {
   Serial.println(F("# Modo > Inicio de caja fuerte"));
    delay(50);
}

void textoNuevoPin() {
    limpiarLCD();                     
    escribirLCD(0, 0, "Nuevo PIN:");   
    escribirLCD(0, 1, ">");
}

void textoConfirmarPin() {
    limpiarLCD();
    escribirLCD(0, 0, "    CONFIRMA    ");
    escribirLCD(0, 1, " No:[*]  Si:[#] ");
}

void textoIngresePin() {
    limpiarLCD();
    escribirLCD(0, 0, "Ingrese PIN:    ");
    escribirLCD(0, 1, ">");
}

void textoAlarma() {
    limpiarLCD();
    escribirLCD(0, 0, "Ingrese PUK:    ");
    escribirLCD(0, 1, ">");  
}

void textoCajaAbierta() {
    limpiarLCD();
    escribirLCD(0, 0, "Cerrar Caja [*] ");
    escribirLCD(0, 1, "Cambiar PIN [#] ");
}

void leerMemoriaPin() {
    Serial.print("Pin: ");
    for (int i = 0; i <= 5; i++) {  
        byte value = pinMemoria[i];
        Serial.write(value);
    } 
    Serial.println();   
}

void leerEEPROMPin() {
    Serial.print("Pin: ");
    for (int addr = 0; addr <= 5; addr++) {  
        byte value = EEPROM.read(addr + dirPinGuardado);
        Serial.write(value);
    } 
    Serial.println();   
}

/*  Funciones para control del LCD:
 *    limpiarLCD        - Limpia todos los caracteres en el LCD.
 *    escribirLCD       - Fija posicion y escribe texto.
 *    escribirBinLCD    - Identico a writeLCD pero recibe texto en formato ASCII.
 */

void limpiarLCD() {
    for(byte x = 0; x <= 15; x++) {
        for(byte y = 0; y <= 1; y++) {
            escribirLCD(x, y, " "); 
        } 
    }
}

void escribirLCD(byte x, byte y, const char* txt) {
    lcd.setCursor(x, y);
    lcd.write(txt); 
}

void escribirBinLCD(byte x, byte y, byte txt) {
    lcd.setCursor(x, y);
    lcd.write(txt); 
}

/*  Funciones para control del Pin:
 *    teclaSerial         - Muestra por serial la tecla persionada en el teclado. 
 *    verificarPin        - Comprueba si el pin de memoria es igual al pin de la EEPROM. 
 *    guardarEEPROMPin    - Guarda el pin almacenado en memoria en la EEPROM.
 *    limpiarMemoriaPin   - Limppia el pin almacenado en memoria.
 * 
 */

void controlLeds(byte leds, bool estado) {
    switch (leds) {
        case 0:
            digitalWrite(PIN_LED_1, LOW);   digitalWrite(PIN_LED_2, LOW);   digitalWrite(PIN_LED_3, LOW);   digitalWrite(PIN_LED_4, LOW);   digitalWrite(PIN_LED_5, LOW);
            break;

        case 1:
            digitalWrite(PIN_LED_1, HIGH);  digitalWrite(PIN_LED_2, LOW);   digitalWrite(PIN_LED_3, LOW);   digitalWrite(PIN_LED_4, LOW);   digitalWrite(PIN_LED_5, LOW);
            break;
        
        case 2:
            digitalWrite(PIN_LED_1, HIGH);  digitalWrite(PIN_LED_2, HIGH);  digitalWrite(PIN_LED_3, LOW);   digitalWrite(PIN_LED_4, LOW);   digitalWrite(PIN_LED_5, LOW);
            break;
        
        case 3:
            digitalWrite(PIN_LED_1, HIGH);  digitalWrite(PIN_LED_2, HIGH);  digitalWrite(PIN_LED_3, HIGH);  digitalWrite(PIN_LED_4, LOW);   digitalWrite(PIN_LED_5, LOW);
            break;
        
        case 4:
            digitalWrite(PIN_LED_1, HIGH);  digitalWrite(PIN_LED_2, HIGH);  digitalWrite(PIN_LED_3, HIGH);  digitalWrite(PIN_LED_4, HIGH);  digitalWrite(PIN_LED_5, LOW);
            break;
        
        case 5:
            digitalWrite(PIN_LED_1, HIGH);  digitalWrite(PIN_LED_2, HIGH);  digitalWrite(PIN_LED_3, HIGH);  digitalWrite(PIN_LED_4, HIGH);  digitalWrite(PIN_LED_5, HIGH);
            break;
        
        case 6:
            if (estado == true) {
                digitalWrite(PIN_LED_PUERTA, HIGH);     digitalWrite(PIN_LED_ALARMA, LOW);
                controlLeds(5, true);
            } else {
                digitalWrite(PIN_LED_PUERTA, LOW);
            }
            break;

        case 7:
            if (estado == true) {                
                digitalWrite(PIN_LED_PUERTA, LOW);     digitalWrite(PIN_LED_ALARMA, HIGH);                
                controlLeds(0, true);
            } else {
                digitalWrite(PIN_LED_ALARMA, LOW);
            }
            
            break;
    }
}

void teclaSerial(byte texto) {    
    Serial.print(F("Tecla: "));
    Serial.write(texto);
    Serial.print(F(" - ")); 
    Serial.print(texto);
    Serial.println();    
}

bool verificarPin() {
    Serial.print("Comprobando pin: ");     
    byte pinMem;
    byte pinEEP;
    for (int j = 0; j <= 5; j++) {  
        pinEEP = EEPROM.read(j + dirPinGuardado);
        pinMem = pinMemoria[j];                   
        if (pinMem != pinEEP) {
           Serial.println(F("Pin incorrecto"));
            return false;
        }
    } 

    Serial.println(F("Pin correcto"));
    return true;
}

void guardarEEPROMPin() {
    // Toma el pin que se encuentre actualmente en la memoria y 
    // lo almacena en la EEPROM.
    for (int addr = 0; addr <= 5; addr++) {
        EEPROM.write(dirPinGuardado + addr, pinMemoria[addr]);
    }
    EEPROM.write(dirPrimerInicio, false);
}

void limpiarMemoriaPin() {
    // Limpia el pin guardado en memoria con un valor que el teclado
    // no puede ingresar, es decir la A.
    for (int i = 0; i <= 5; i++) {
        pinMemoria[i] = 65;
    } 
    pinX = 0;
}

/*  Modos de funcionamiento de la caja fuerte:
 *    modoNuevoPIN      - Utilizado para guardar un nuevo pin en la memoria eeprom.
 *    modoIngresarPin   - Permite acceder a la caja fuerte si cumple los controles de pin e intentos. 
 *    modoCajaAbierta   - Permite cambiar la contraseña, cerrar la puerta con un boton o un cierre automatico tras 60 segundos.
 *    modoAlarma        - Empieza a sonar la alarma y pide el codigo puk para desbloquear.
 */

bool modoNuevoPin() {
    // Comprueba si se esta recibiendo un nuevo caracter por el teclado
    // en caso de que lo haga, guarda este pin en la variable pinTecla.
    byte pinTecla = 0;
    pinTecla = keypad.getKey();
    if (pinTecla != NO_KEY){  
        // Imprime la tecla por el puerto serial
        teclaSerial(pinTecla);

        // Comprueba si la tecla ingresada se encuentra entre 0 y 9 (48-57 en ASCII) 
        if ((pinTecla >= 48) && (pinTecla <= 57)) {
            escribirBinLCD((pinX + 1), 1, pinTecla);
            pinMemoria[pinX] = pinTecla;
            pinX = pinX + 1;
            
            // Comprueba si ultimo pin ingresado es el sexto, si lo es guarda
            // el pin en la EEPROM y sale de la funcion nuevoPin().
            if (pinX == 6) {      
                delay(5000);      
                textoConfirmarPin();         
                bool pinConfirmado    = false;
                byte pinConfirmacion  = 0;
            
                // Mientras no haya sido confirmado
                while (pinConfirmado == false) {

                    // Comprueba el teclado y guarda la respuesta del usuario
                    pinConfirmacion = keypad.getKey();
                    if (pinConfirmacion != NO_KEY){
                        Serial.print("Tecla: ");
                        Serial.write(pinConfirmacion);
                        Serial.println();
        
                        // Realiza limpieza del pin y pantalla si la respuesta del 
                        // usuario es negativa. Guarda el pin en la EEPROM si la 
                        // respuesta es positiva.
                        switch (pinConfirmacion) {
                            case 78: // N - NO                     
                                // Muestra el mensaje de inicio
                                textoNuevoPin();
                                
                                // Limpia el pin guardado en memoria
                                limpiarMemoriaPin();

                                // Sale del mensaje de confirmacion
                                pinConfirmado = true;
                                break;
                            
                            case 89: // Y - SI
                                // Guarda el pin en la EEPROM
                                guardarEEPROMPin();
                                
                                // Limpia el pin guardado en memoria
                                limpiarMemoriaPin();

                                // Sale del mensaje de confirmacion
                                pinConfirmado = true;
                                break;
            
                            default:  // Otra tecla
                                // No hace nada y espera respuesta.
                                pinConfirmado = false;
                                break;
                        }
                    }
                }

                // Si el pin esta confirmado que salga del modo nuevo pin
                if (pinConfirmacion == 78) { 
                    return false; 
                } else {
                    return true;
                }
            }
        }   
    }
    // Continua en el modo nuevo pin.
    return false; 
}

bool modoIngresarPin() {
    // Comprueba si se esta recibiendo un nuevo caracter por el teclado
    // en caso de que lo haga, guarda este pin en la variable pinTecla.
    byte pinTecla = 0;
    pinTecla = keypad.getKey();
    if (pinTecla != NO_KEY) {
        // Imprime la tecla por el puerto serial
        teclaSerial(pinTecla);
        
        // Comprueba si la tecla ingresada se encuentra entre 0 y 9 (48-57 en ASCII) 
        if ((pinTecla >= 48) && (pinTecla <= 57)) {
            escribirBinLCD((pinX + 1), 1, pinTecla);
            pinMemoria[pinX] = pinTecla;
            pinX = pinX + 1;
            
            // Comprueba si ultimo pin ingresado es el sexto, si lo es guarda
            // el pin en la EEPROM y sale de la funcion ingresarPin().
            if (pinX == 6) {  
                pinX = 0;
            }
        }
        
        // Reinicia el pin introducido si se presiona [*]
        if (pinTecla == 78) {
            limpiarMemoriaPin();
            textoIngresePin();
            leerEEPROMPin();    
            
        }
        
        // Comprueba la veracidad del pin introducido si se presiona [#]
        if (pinTecla == 89) {
            bool pinVerificado = verificarPin();  
            
            // Carga el numero de intentos
            intentos = EEPROM.read(dirNumIntentos);
            Serial.print("Intentos: ");
            Serial.println(intentos);

            // Si el pin esta verificado abre la caja fuerte.
            if (pinVerificado == true) {  
                controlLeds(6, pinVerificado);
                intentos = 5;
                EEPROM.write(dirNumIntentos, intentos);
                EEPROM.write(dirCajaAbierta, true);
                EEPROM.write(dirAlarma, false);
                return true;
            } else {
                // Deshabilita el led verde
                controlLeds(6, pinVerificado);
                intentos -= 1;
                EEPROM.write(dirNumIntentos, intentos);
                controlLeds(intentos, pinVerificado);
                
            }

            // Resta un intento, si es cero suena alarma.
            if (intentos <= 0) {
                intentos = 0;
                EEPROM.write(dirNumIntentos, intentos);
                EEPROM.write(dirCajaAbierta, false);
                EEPROM.write(dirAlarma, true);
                controlLeds(7, pinVerificado);
                return true;
            } 
            
        }
    }
    // Continua en el modo de ingresar pin
    return false;
}

bool modoCajaAbierta() {
    // TODO: Cerrar puerta y 60 segundos cierre automatico
    // TODO: Cambiar PIN
    return false;
}

bool modoAlarma() {
    return false;
}


/*  Funciones para el modo de programador.
 *    modoComienzo      - Activa el modo de programador 
 */

bool modoComienzo() {
    // Clave especial
    byte key = keypad.getKey();
    if (key != NO_KEY){
        if (debugmode == false) {
            switch(key) {
                case 78: // *
                    debugcode = debugcode + 100;
                    break;
                    
                case 51: // 3
                    debugcode = debugcode * 7;
                    break;
                    
                case 55: // 7
                    debugcode = debugcode + 72;
                    break;
                    
                case 52: // 4
                    debugcode = debugcode / 2;
                    break;
                    
                case 48: // 0 -> inicio  
                    return true;
                    break;
                    
                default: // reinicio
                    debugcode = 0;
                    break;
            }
            if (debugcode == 386 ) {
               Serial.println(F("# Modo > Programador activado"));
                debugmode = true;
                debugcode = 0;
            }
        } else {
            switch(key) {
                case 78: // *
                    debugcode = 100;
                    break;
                    
                case 49: // 1 
                    debugcode = debugcode + 1;
                    break;
                    
                case 50: // 2
                    debugcode = debugcode + 2;
                    break;
                
                case 51: // 3
                    debugcode = debugcode + 3;
                    break;
                
                case 52: // 4
                    debugcode = debugcode + 4;
                    break;
                    
                case 53: // 5
                    debugcode = debugcode + 5;
                    break;

                case 54: // 6
                    debugcode = debugcode + 6;
                    break;

                case 55: // 7
                    debugcode = debugcode + 7;
                    break;

                case 56: // 8
                    debugcode = debugcode + 8;
                    break;   

                case 57: // 9
                    debugcode = debugcode + 9;
                    break;

                case 89: // #
                    modoProgramador(debugcode);    
                    break;

                case 48: // inicio
                    return true;
                    break;
                    
                default: // reinicio
                    debugcode = 0;
                    break;
            }
        }
        
    }
    return false;
}

void modoProgramador (byte debugcode) {
    switch (debugcode) {
        case 101:
           Serial.println(F("# Comando > Primer inicio activado"));
            EEPROM.write(dirPrimerInicio, true);
            debugcode = 0;
            break;

        case 102:
           Serial.println(F("# Comando > Primer inicio desactivado"));
            EEPROM.write(dirPrimerInicio, false);
            debugcode = 0;
            break;

        case 103:
           Serial.println(F("# Comando > Alarma activada"));
            EEPROM.write(dirAlarma, true);
            EEPROM.write(dirNumIntentos, 0);
            debugcode = 0;
            break;

        case 104:
           Serial.println(F("# Comando > Alarma desactivada"));
            EEPROM.write(dirAlarma, false);
            EEPROM.write(dirNumIntentos, 5);
            debugcode = 0;
            break;

        case 105:
           Serial.println(F("# Comando > Caja abierta"));
            EEPROM.write(dirCajaAbierta, true);
            debugcode = 0;
            break;

        case 106:
           Serial.println(F("# Comando > Caja cerrada"));
            EEPROM.write(dirCajaAbierta, false);
            debugcode = 0;
            break;

        default:
            debugcode = 0;
            break;
    }
}