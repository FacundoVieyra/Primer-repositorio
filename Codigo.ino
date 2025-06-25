// Configuración inicial: 

//Definición de los pines (2 a 6: LEDS, 7: BOTON, A0: POTENCIADOR)

int ledVerdeVehiculos = 2;
int ledAmarilloVehiculos = 3;
int ledRojoVehiculos = 4;
int ledVerdePeatones = 5;
int ledRojoPeatones = 6;
int botonPeaton = 7;
int potenciometroPin = A0;

// Variables para el manejo del botón y contador de flancos
int contadorPeatones = 0;
int estadoBotonAnterior = LOW;

// control por tiempo
long tiempoInicioCambio = 0;
long tiempoAmarillo = 2000; 
long tiempoRojoPeatones = 5000;

// Variables para potenciómetro y tiempos ajustables
int valorMinPotenciometro = 0;
int valorMaxPotenciometro = 1023;
long tiempoMinPeatones = 2000;
long tiempoMaxPeatones = 10000;

// definicion de estados de la maquina de estados
enum Estados {
  ESTADO_VEHICULOS_VERDE,
  ESTADO_VEHICULOS_AMARILLO,
  ESTADO_VEHICULOS_ROJO
};

Estados estadoActual = ESTADO_VEHICULOS_VERDE;


//Configuración de los pines en modo salida/entrada

void setup(){
    pinMode (ledVerdeVehiculos, OUTPUT);
    pinMode (ledAmarilloVehiculos, OUTPUT);
    pinMode (ledRojoVehiculos, OUTPUT);
    pinMode (ledVerdePeatones, OUTPUT);
    pinMode (ledRojoPeatones, OUTPUT);
    // Configuración del pin del boton como entrada 
    pinMode (botonPeaton, INPUT);

//Comunicación serial para debug
    Serial.begin(9600);
    Serial.println("Semáforo Peatonal Inteligente");
}

void loop() {
  int estadoBotonActual = digitalRead(botonPeaton);

  // Detección de flancos
  if (estadoBotonActual == HIGH && estadoBotonAnterior == LOW) {
    contadorPeatones++;
      
    Serial.print("Botón presionado. Contador: ");
    Serial.println(contadorPeatones);

      if (estadoActual == ESTADO_VEHICULOS_VERDE) {
      estadoActual = ESTADO_VEHICULOS_AMARILLO;
      tiempoInicioCambio = millis(); 
    }
  }
  estadoBotonAnterior = estadoBotonActual;

  // Lectura del potenciómetro para ajustar tiempo rojo peatones
  int valorPotenciometro = analogRead(potenciometroPin);
  tiempoRojoPeatones = map(valorPotenciometro, valorMinPotenciometro, valorMaxPotenciometro, tiempoMinPeatones, tiempoMaxPeatones);

 // Control logico por maquina de estados
  switch (estadoActual) {
    case ESTADO_VEHICULOS_VERDE:
      
      digitalWrite(ledVerdeVehiculos, HIGH);
      digitalWrite(ledAmarilloVehiculos, LOW);
      digitalWrite(ledRojoVehiculos, LOW);
      digitalWrite(ledVerdePeatones, LOW);
      digitalWrite(ledRojoPeatones, HIGH);
      break; 

    case ESTADO_VEHICULOS_AMARILLO:
     
      digitalWrite(ledVerdeVehiculos, LOW);
      digitalWrite(ledAmarilloVehiculos, HIGH);
      digitalWrite(ledRojoVehiculos, LOW);
      digitalWrite(ledVerdePeatones, LOW);
      digitalWrite(ledRojoPeatones, HIGH);
      
      if (millis() - tiempoInicioCambio >= tiempoAmarillo) {
        estadoActual = ESTADO_VEHICULOS_ROJO;
        tiempoInicioCambio = millis(); 
      }
      break;

    case ESTADO_VEHICULOS_ROJO:
      
      digitalWrite(ledVerdeVehiculos, LOW);
      digitalWrite(ledAmarilloVehiculos, LOW);
      digitalWrite(ledRojoVehiculos, HIGH);
      digitalWrite(ledVerdePeatones, HIGH);
      digitalWrite(ledRojoPeatones, LOW);
      
      if (millis() - tiempoInicioCambio >= tiempoRojoPeatones) {
        estadoActual = ESTADO_VEHICULOS_VERDE;
        
      }
      break;
  }
delay (10); 
}


