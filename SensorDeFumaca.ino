#define tempo 10
#include <SPI.h>
#include <Ethernet.h>

EthernetServer server = EthernetServer(1000);

int frequencia = 0;
int Pinofalante = 8;

int smokeA0 = A5;
// Your threshold value
int sensorThres = 450;

void setup() {
  pinMode(Pinofalante,OUTPUT);
  pinMode(smokeA0, INPUT);
  Serial.begin(9600);
  
  uint8_t mac[6] = {0x00,0x01,0x02,0x03,0x04,0x05};
  IPAddress myIP(192,168,0,6);

  Serial.println("Iniciando...");

  Ethernet.begin(mac,myIP);

  server.begin();
    
  Serial.println("Rodando!!!");
}

void loop() {
          EthernetClient client = server.available();
    if (client.connected())
  {
                Serial.println("Cliente conectado!");
          if (client.available()){

                        char c = client.read();
                        Serial.println(c);                      
                        if(c == '1'){
                          int analogSensor = analogRead(smokeA0);

                          Serial.print("Pin A0: ");
                          Serial.print(analogSensor);
  
                               if (analogSensor > sensorThres)
                                {
                                Serial.println(" Tá pegando fogo!!!!");
                                client.println("666");
                                alarme();
                                }
                                else
                                {
                                Serial.println("Tudo OK");
                                client.println("333");
                                }
                                
                          }
                        
                        
    }
  }
  client.stop();
  delay(1000);

  
  
}


void alarme(){
   for (frequencia = 150; frequencia < 1800; frequencia += 1) 
  {
    tone(Pinofalante, frequencia, tempo); 
    delay(1);
  }
  for (frequencia = 1800; frequencia > 150; frequencia -= 1) 
  {
    tone(Pinofalante, frequencia, tempo); 
    delay(1);
  }
}


