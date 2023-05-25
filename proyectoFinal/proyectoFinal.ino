/*
  Fundación Kinal
  Centro Educativo Técnico Laboral Kinal
  Electrónica
  Grado: Quinto
  Sección: A
  Curso: Taller de Electrónica Digital y Reparación de Computadoras I
  Proyecto: Proyecto Final ( Sistema de acondicionamiento climático de una incubadora
  de huevos).
  Alumnos: Jose Javier Juarez Rivera
         Guillermo Antonio Franco Longo
         Luis Fernando Alvarado Ramirez
  Carné: 2022252
       2022357
       2022219
*/
#include <Servo.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#define RELE1 2
#define VENTILADOR 7
#define PUSH1 6
#define Huevo1 2
#define Huevo2 3
#define Huevo3 4
#define Huevo4 5
#define Huevo5 6
#define a 7
#define b 8
#define c 9
#define d 10
#define e 11
#define f 12
#define g A0
//Se crea el codigo para el caracter de grados
byte F[] = {
  B11100,
  B10100,
  B11100,
  B00000,
  B00000,
  B00000,
  B00000,
  B00000
};

Servo myservo;
OneWire ourWire(8);
DallasTemperature sensor(&ourWire);
//Crear el objeto lcd  dirección  0x3F y 16 columnas x 2 filas
LiquidCrystal_I2C lcd(0x27, 16, 2); //
OneWire ourWire(A1);               //Se establece el pin A1  como bus OneWire
DallasTemperature sensors(&ourWire);

void pines();
int sensortC();



int TempC, value = 0, value1 = 0;
void setup() {
  Serial.begin(9600);
  myservo.attach(4);
  myservo.write(0);
  pines();
  //Definir los 5 pines lo cuales leen si hay un objeto entre el led y la fotoresistencia
  pinMode(Huevo1, INPUT);
  pinMode(Huevo2, INPUT);
  pinMode(Huevo3, INPUT);
  pinMode(Huevo4, INPUT);
  pinMode(Huevo5, INPUT);
  //Definir los 7 segmentos del display como salida
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  Serial.begin(9600);
  // Inicializar el LCD
  lcd.init();
  //Encender la luz de fondo.
  lcd.backlight();
  sensors.begin();   //Se inicia el sensor
  lcd.createChar(0, F);

}
void loop() {
  temperatura();
  sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
  float tempC = sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC
  float tempF = sensors.getTempFByIndex(0); //Se obtiene la temperatura en ºF
  Serial.print("Temperatura");
  Serial.print(tempC);
  Serial.println(" C");
  Serial.print("Temperatura");
  Serial.print(tempF);
  Serial.println(" F");
  delay(100);
  //Leo los 5 pines
  bool lectura1 = digitalRead(Huevo1);
  bool lectura2 = digitalRead(Huevo2);
  bool lectura3 = digitalRead(Huevo3);
  bool lectura4 = digitalRead(Huevo4);
  bool lectura5 = digitalRead(Huevo5);
  Serial.print("Temperatura");
  Serial.print(tempC);
  Serial.println(" C");
  Serial.print("Temperatura");
  Serial.print(tempF);
  Serial.println(" F");
  delay(100);
  //Imprime los grados Farenheit en la primera fila
  lcd.setCursor(0, 0);
  lcd.write(byte(0));//Imprime el caracter de grados en la primera columna y primera fila
  lcd.setCursor(1, 0);
  lcd.print("F");
  lcd.setCursor(2, 0);
  lcd.print("=");
  lcd.setCursor(3, 0);
  lcd.print(tempF);
  //Imprime los grados centigrados en la segunda fila
  lcd.setCursor(0, 1);
  lcd.write(byte(0));
  lcd.setCursor(1, 1);
  lcd.print("C");
  lcd.setCursor(2, 1);
  lcd.print("=");
  lcd.setCursor(3, 1);
  lcd.print(tempC);
  digitalWrite(a, HIGH);
  digitalWrite(b, HIGH);
  digitalWrite(c, HIGH);
  digitalWrite(d, HIGH);
  digitalWrite(e, HIGH);
  digitalWrite(f, HIGH);
  digitalWrite(g, LOW);
  //numero 0 en el display

  //Numero 1 en el display
  if (lectura1 == LOW || lectura2 == LOW || lectura3 == LOW || lectura4 == LOW || lectura5 == LOW)
  {
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, LOW);

  }
  //numero 2 en el display
  if (((((lectura1 == LOW && lectura2 == LOW)) || (lectura1 == LOW && lectura3 == LOW)) || (lectura1 == LOW && lectura4 == LOW)) || (lectura1 == LOW && lectura5 == LOW))
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
  }
  if ((((lectura2 == LOW && lectura3 == LOW)) || (lectura2 == LOW && lectura4 == LOW)) || (lectura2 == LOW && lectura5 == LOW))
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
  }
  if (((lectura3 == LOW && lectura4 == LOW)) || (lectura3 == LOW && lectura5 == LOW))
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
  }
  if ((lectura4 == LOW && lectura5 == LOW))
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, LOW);
    digitalWrite(d, HIGH);
    digitalWrite(e, HIGH);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
  }
  //numero 3 en el display
  if ((((lectura1 == LOW && lectura2 == LOW && lectura3 == LOW)) || (lectura1 == LOW && lectura2 == LOW && lectura4 == LOW)) || (lectura1 == LOW && lectura2 == LOW && lectura5 == LOW))
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
  }
  if (((lectura1 == LOW && lectura3 == LOW && lectura4 == LOW)) || (lectura1 == LOW && lectura3 == LOW && lectura5 == LOW))
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
  }
  if ((lectura1 == LOW && lectura4 == LOW && lectura5 == LOW))
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
  }
  if (((lectura2 == LOW && lectura3 == LOW && lectura4 == LOW)) || (lectura2 == LOW && lectura4 == LOW && lectura5 == LOW))
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
  }
  if ((lectura3 == LOW && lectura2 == LOW && lectura5 == LOW) || (lectura3 == LOW && lectura4 == LOW && lectura5 == LOW))
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, LOW);
    digitalWrite(f, LOW);
    digitalWrite(g, HIGH);
  }
  //numero 4 en el display
  if ((((lectura2 == LOW && lectura5 == LOW && lectura3 == LOW && lectura4 == LOW)) || (lectura1 == LOW && lectura4 == LOW && lectura3 == LOW && lectura5 == LOW)) || (lectura1 == LOW && lectura2 == LOW && lectura4 == LOW && lectura5 == LOW))
  {
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
  }
  if (((lectura1 == LOW && lectura2 == LOW && lectura3 == LOW && lectura5 == LOW)) || (lectura1 == LOW && lectura2 == LOW && lectura3 == LOW && lectura4 == LOW))
  {
    digitalWrite(a, LOW);
    digitalWrite(b, HIGH);
    digitalWrite(c, HIGH);
    digitalWrite(d, LOW);
    digitalWrite(e, LOW);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
  }
  //numero 5 en el display
  if ((lectura1 == LOW && lectura2 == LOW && lectura3 == LOW && lectura4 == LOW && lectura5 == LOW))
  {
    digitalWrite(a, HIGH);
    digitalWrite(b, LOW);
    digitalWrite(c, HIGH);
    digitalWrite(d, HIGH);
    digitalWrite(e, LOW);
    digitalWrite(f, HIGH);
    digitalWrite(g, HIGH);
  }

}
void pines() {
  pinMode(VENTILADOR, OUTPUT);
  pinMode(RELE1, OUTPUT);
  pinMode(PUSH1, INPUT);
  digitalWrite(RELE1, HIGH);
}
int sensortC() {
  sensor.requestTemperatures();   //Se envía el comando para leer la temperatura
  int temp = sensor.getTempCByIndex(0); //Se obtiene la temperatura en ºC
  return temp;
}

void temperatura() {
  TempC = sensortC();
  Serial.println(TempC);

  if (TempC >= 27 && TempC <= 35) {
    digitalWrite(VENTILADOR, HIGH);
    digitalWrite(RELE1, LOW);
    myservo.write(0);
  }

  if (TempC >= 40 && TempC <= 45) {
    digitalWrite(VENTILADOR, LOW);
    digitalWrite(RELE1, HIGH);
    myservo.write(180);

  }
  bool lectura = digitalRead(PUSH1);
  if (lectura == LOW) {
    digitalWrite(VENTILADOR, LOW);
    digitalWrite(RELE1, HIGH);
    myservo.write(180);
  }
}
