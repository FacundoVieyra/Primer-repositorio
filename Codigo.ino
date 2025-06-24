// Setteo configuración inicial: 
//Definición de los pines (2 a 6: LEDS, 7: BOT, A0: POT)
int ledVerdeVehiculos = 2;
int ledAmarilloVehiculos = 3;
int ledRojoVehiculos = 4;
int ledVerdePeatones = 5;
int ledRojoPeatones = 6;
int botonPeatones = 7;
int potenciometroPin = A0;

//Configuración de los pines en modo salida/entrada-
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

