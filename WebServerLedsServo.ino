#include <Servo.h>

Servo myservo; 
#include <Wire.h>
#include <UnoWiFiDevEd.h>

void setup() {
    myservo.attach(6);
    Wifi.begin();
    Wifi.println("Web Server is up");
    pinMode(13,OUTPUT); //Establecemos los pines como salidas
    pinMode(12,OUTPUT);
    pinMode(11,OUTPUT);
    pinMode(10,OUTPUT);
    pinMode(9,OUTPUT);
    pinMode(8,OUTPUT);
    pinMode(7,OUTPUT);
    pinMode(5,OUTPUT);
    pinMode(4,OUTPUT);
}
void loop() {
  //Si el Arduino Wifi está disponible comienza en funcionamiento
    while(Wifi.available()){
      process(Wifi);
    }
  delay(50);
}

void process(WifiData client) {
//Lee el comando
  String command = client.readStringUntil('/');
  if (command == "webserver") {
    WebServer(client);
  }
  if (command == "digital") {
    digitalCommand(client);
  }
}
void WebServer(WifiData client) {
  //Da los comandos necesarios para la visualización del servidor web 
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println();
  client.println("<html>");
  client.println("<head> </head>");
  client.print("<body>");
  client.print("Click<input type=button onClick=\"var w=window.open('/arduino/digital/13/1','_parent');w.close();\"value='VAMOS'>pin13 ON<br>");
  client.print("Click<input type=button onClick=\"var w=window.open('/arduino/digital/13/0','_parent');w.close();\"value='VENIMOS'>pin13 OFF<br>");
  client.print("Click<input type=button onClick=\"var w=window.open('/arduino/digital/13/2','_parent');w.close();\"value='CENTRO'>pin13 PARPADEO<br>");
  client.print("</body>");
  client.println("</html>");
  client.print(DELIMITER);
}
void digitalCommand(WifiData client) {
  int pin, value = 0;
    pin = client.parseInt();
 //Leyendo el número junto al / a fin de tomar un funcionamiento distinto en cada caso por haber presionado distintos motores
  if (client.read() == '/') {
    value = client.parseInt();
    if(value==1){
      //Se encienden los leds de izquierda a derecha uno a uno y finalmente el motor da una vuelta
     digitalWrite(pin, value);
     digitalWrite(13, value);
     delay(150);
     digitalWrite(12, value);
     delay(150);
     digitalWrite(11, value);
     delay(150);
     digitalWrite(10, value);
     delay(150);
     digitalWrite(9, value);
     delay(150);
     digitalWrite(8, value);
     delay(150);
     digitalWrite(7, value);
     delay(150);
     digitalWrite(5, value);
     delay(150);
     digitalWrite(4, value);
     delay(150);
      myservo.write(180);
      
    }else if(value==0){
      //Se apagan los leds de derecha a izquierda uno a uno después de que el motor haya dado una vuelta
     digitalWrite(4, value);
     delay(150);
     myservo.write(10);
     digitalWrite(5, value);
     delay(150);
     digitalWrite(7, value);
     delay(150);
     digitalWrite(8, value);
     delay(150);
     digitalWrite(9, value);
     delay(150);
     digitalWrite(10, value);
     delay(150);
     digitalWrite(11, value);
     delay(150);
     digitalWrite(12, value);
     delay(150);
     digitalWrite(13, value);
     delay(150);
     }else if(value==2){
    // Los leds se encienden uno a uno desde afuera hacia adentro, simultáneamente los del mismo color y finalmente el motor gira en tiempos de ida y vuelta
    digitalWrite(13, 1);
    digitalWrite(7, 1);
    delay(200);
    digitalWrite(13, 0);
    delay(200);
    digitalWrite(7, 0);
    delay(200);
    digitalWrite(12,1);
    digitalWrite(8, 1);
    delay(200);
    
    digitalWrite(12,0);
    delay(250);
    digitalWrite(8,0);
    delay(250);
    digitalWrite(11,1);
    digitalWrite(9, 1);
    delay(250);
    digitalWrite(11,0);
    delay(250);
    digitalWrite(9, 0);
    delay(250);
    digitalWrite(10,1);
    delay(250);
    digitalWrite(10,0);
    delay(250);
    digitalWrite(5, 1);
    digitalWrite(4, 1);
    delay(250);
    for(int i=0;i<=180;i=i+20){
      myservo.write(i);
      delay(50);
    }
    for(int i=180;i>=0;i=i-20){
      myservo.write(i);
      delay(50);
    }
    }
  }

  //Mensaje de aviso de finalización del programa
  client.println("Status: 200 OK\n");
  client.print(F("Pin D"));
  client.print(pin);
  client.print(F(" set to "));
  client.print(value);
  client.print(EOL);
}
