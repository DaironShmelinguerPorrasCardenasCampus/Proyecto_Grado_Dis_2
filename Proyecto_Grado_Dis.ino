#include <LiquidCrystal_I2C.h>
#include <ESP32Servo.h>

#define BLYNK_TEMPLATE_ID           "TMPLzkV54HY1"
#define BLYNK_DEVICE_NAME           "Quickstart Device"
#define BLYNK_AUTH_TOKEN            "cQD2TgFXvvEY-r0fVGfi0zKEsDIMmjuO"

#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;

char ssid[] = "LOS_URIBE"; //nombre red
char pass[] = "MunecaVal2022"; //contraseña

LiquidCrystal_I2C lcd(0x27, 16, 2);//crear un objeto lcd (DIRECCIÓN pantalla, Tamaño x, Tamño y)
Servo myservo;

int pos = 0;
int pos_Final;
int contador;
int tiempo_act; //tiempo de movimiento
int a = 0;
int b = 0;
int c = 0;


int servoPin = 32; //posición del servo - conexión

BLYNK_WRITE(V0)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V1, value);
  //digitalWrite(19,value);
  a=value;
  Serial.println(value);
}

BLYNK_WRITE(V2)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V3, value);
  //digitalWrite(19,value);
  b=value;
  Serial.println(value);
}

BLYNK_WRITE(V4)
{
  // Set incoming value from pin V0 to a variable
  int value = param.asInt();

  // Update state
  Blynk.virtualWrite(V5, value);
  //digitalWrite(19,value);
  c=value;
  Serial.println(value);
}


void setup() {

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  myservo.setPeriodHertz(50);    // standard 50 hz servo
  myservo.attach(servoPin, 500, 2400); //señal para controlar el servo frecuencia 500 periodo 2400
  
  lcd.begin();   
  lcd.backlight();//Encender la luz de fondo

  pinMode(23,INPUT); //botones
  pinMode(19,INPUT); //botones
  pinMode(18,INPUT); //botones

  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

}

void loop() {
  Blynk.run();

  //Serial.println(digitalRead(23));
  lcd.setCursor (0, 0);//poner el cursor en las coordenadas (x,y)
  lcd.print("  Selec medida  ");//muestra en la pantalla max 20 caracteres
  lcd.setCursor (0, 1);//poner el cursor en las coordenadas (x,y)
  lcd.print("Med1  ");//muestra en la pantalla max 20 caracteres
  lcd.print("Med2  ");
  lcd.print("Med3");

  if(digitalRead(23)|| a==1){
    //pos_Final = 60;
    pos=70;
    tiempo_act=12000;
    lcd.setCursor (0, 0);
    lcd.print("Medida 1        ");
    conteo();
    Vis_Activado();
    a=0;
  }

  if(digitalRead(19)|| b==1){
    //pos_Final = 120;
    pos=150;
    tiempo_act=4000;
    lcd.setCursor (0, 0);
    lcd.print("Medida 2        ");
    conteo();
    Vis_Activado();
    b=0;
  }

  if(digitalRead(18)|| c==1){
    //pos_Final = 180;
    pos=180;
    tiempo_act=8000;
    lcd.setCursor (0, 0);
    lcd.print("Medida 3        ");
    conteo();
    Vis_Activado();
    c=0;
  }
}

void conteo(){
  for (contador=5;contador>0;contador--){
  lcd.setCursor (0, 1); 
  lcd.print("                ");
  lcd.setCursor (0, 1); 
  lcd.print("tiempo ");
  lcd.print(contador);
  delay(1000);
  }
}

//void Mover_Servo(){
//  for (pos = 0; pos <= pos_Final; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myservo.write(pos);    // tell servo to go to position in variable 'pos'
//    delay(15);             // waits 15ms for the servo to reach the position
//  }
//  
//  delay(5000);
//  
//  for (pos = pos_Final; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    myservo.write(pos);    // tell servo to go to position in variable 'pos'
//    delay(15);             // waits 15ms for the servo to reach the position
//  }
//}

void Mover_Servo(){
 myservo.write(pos);
 delay(tiempo_act); 
 myservo.write(90);
 //delay(3000);
}

void Vis_Activado(){
   lcd.setCursor (0, 0);
    lcd.print("Activado        ");
    lcd.setCursor (0, 1);
    lcd.print("                ");
    delay(3000);
    Mover_Servo();
    lcd.setCursor (0, 0);
    lcd.print("                ");
  }
