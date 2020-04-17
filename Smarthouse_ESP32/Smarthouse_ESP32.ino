#include <WiFi.h>
#include "FirebaseESP32.h"

#define FIREBASE_HOST "smarthouse-3689b.firebaseio.com"
#define FIREBASE_AUTH "CYMR64SzXKkbF8PBvX5KCTztS49ZgjPNAfxQJxeO"
#define WIFI_SSID "d20c7c"
#define WIFI_PASSWORD "LEABGVL7593"

#define luzSen 34
#define tempSen 32
#define sonidoSen 35
#define proxySen 33

FirebaseData firebaseData, firebaseDataLuz, firebaseDataTemp, firebaseDataSonido, firebaseDataProxy;

void setup() 
{
  Serial.begin(115200);
  Serial.println();
  Serial.println();

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Conectado al Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Conectado con IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);

  pinMode(4,OUTPUT);//LEDS
  pinMode(5,OUTPUT);//SERVO
  pinMode(21,OUTPUT);//RELE
  pinMode(19,OUTPUT);//FAN

}
void loop() 
{
  Firebase.getInt(firebaseData, "/accion");
 
  Firebase.setInt(firebaseDataLuz, "/fotoresistencia", analogRead(luzSen));
  delay(100);
  Firebase.getInt(firebaseDataLuz, "/fotoresistencia");
  Serial.println("Fotoresistencia");
  Serial.println(firebaseDataLuz.intData());

  Firebase.setInt(firebaseDataTemp, "/temperatura", analogRead(tempSen));
  delay(100);
  Firebase.getInt(firebaseDataTemp, "/temperatura");
  Serial.println("Temperatura");
  Serial.println(firebaseDataTemp.intData());

  Firebase.setInt(firebaseDataSonido, "/sonido", analogRead(sonidoSen));
  delay(100);
  Firebase.getInt(firebaseDataSonido, "/sonido");
  Serial.println("Sonido");
  Serial.println(firebaseDataSonido.intData());

  Firebase.setInt(firebaseDataProxy, "/proximidad", digitalRead(proxySen));
  delay(100);
  Firebase.getInt(firebaseDataProxy, "/proximidad");
  Serial.println("Proximidad");
  Serial.println(firebaseDataProxy.intData());

  switch (firebaseData.intData())
  {
    case 41:
      if(firebaseDataLuz.intData()<1000){
        digitalWrite(5,HIGH);
        digitalWrite(4,LOW);
      }else{
        digitalWrite(5,LOW);
        digitalWrite(4,HIGH);
      }
    break;
  
    case 40:
      digitalWrite(5,HIGH);
    break;

    case 11:
      if(firebaseDataProxy.intData()==1){
        digitalWrite(4,HIGH);
      }else{
        digitalWrite(4,LOW);
      }
    break;
  
    case 10:
      digitalWrite(4,HIGH);
    break;

    case 31:
      if(firebaseDataSonido.intData()>80){
        digitalWrite(21,HIGH);
      }else{
        digitalWrite(21,LOW);
      }
    break;
  
    case 30:
      digitalWrite(21,HIGH);
    break;

    case 21:
      if(firebaseDataTemp.intData()>500){
        digitalWrite(19,HIGH);
      }else{
        digitalWrite(19,LOW);
      }
    break;
  
    case 20:
      digitalWrite(19,HIGH);
    break;
  
    case 51:
      digitalWrite(4,LOW);
      digitalWrite(5,LOW);
      digitalWrite(21,LOW);
      digitalWrite(19,LOW);
    break;

    case 50:
      digitalWrite(4,HIGH);
      digitalWrite(5,HIGH);
      digitalWrite(21,HIGH);
      digitalWrite(19,HIGH);
    break;

    case 100:
    if(firebaseDataLuz.intData()<1000){
        digitalWrite(5,HIGH);
        digitalWrite(4,LOW);
      }else{
        digitalWrite(5,LOW);
        digitalWrite(4,HIGH);
      }

    if(firebaseDataProxy.intData()>=1){
        digitalWrite(4,HIGH);
      }else{
        digitalWrite(4,LOW);
      }
    
    if(firebaseDataSonido.intData()>10){
        digitalWrite(21,HIGH);
      }else{
        digitalWrite(21,LOW);
      }

    if(firebaseDataTemp.intData()>500){
        digitalWrite(19,HIGH);
      }else{
        digitalWrite(19,LOW);
      }
  }
  
}
