// Configuración inicial: 

//Definición de los pines (2 a 6: LEDS, 7: BOTON, A0: POTENCIADOR)

int ledVerdeVehiculos = 2;
int ledAmarilloVehiculos = 3;
int ledRojoVehiculos = 4;
int ledVerdePeatones = 5;
int ledRojoPeatones = 6;
int botonPeatones = 7;
int potenciometroPin = A0;

// Variables para el manejo del botón y contador de flancos
int contadorPeatones = 0;
int estadoBotonAnterior = LOW;

// Variables para potenciómetro y tiempos ajustables
int valorMinPotenciometro = 0;
int valorMaxPotenciometro = 1023;
long tiempoMinPeatones = 2000;
long tiempoMaxPeatones = 10000;
long tiempoRojoPeatones = 5000;


//Configuración de los pines en modo salida/entrada

void setup(){
    pinMode (ledVerdeVehiculos, OUTPUT);
    pinMode (ledAmarilloVehiculos, OUTPUT);
    pinMode (ledRojoVehiculos, OUTPUT);
    pinMode (ledVerdePeatones, OUTPUT);
    pinMode (ledRojoPeatones, OUTPUT);
    pinMode (botonPeatones, INPUT_PULLUP);
}

//Comunicación serial para debug

Serial.begin(9600);
Serial.println("Semáforo Peatonal Inteligente");

void loop() {
  int estadoBotonActual = digitalRead(botonPeaton);

  // Detección de flancos
  if (estadoBotonActual == HIGH && estadoBotonAnterior == LOW) {
    contadorPeatones++;
      
    Serial.print("Botón presionado. Contador: ");
    Serial.println(contadorPeatones);
  }
  estadoBotonAnterior = estadoBotonActual;

  // Lectura del potenciómetro para ajustar tiempo rojo peatones
  int valorPotenciometro = analogRead(potenciometroPin);
  tiempoRojoPeatones = map(valorPotenciometro, valorMinPotenciometro, valorMaxPotenciometro, tiempoMinPeatones, tiempoMaxPeatones);
}


