//Include Lib for Arduino to Nodemcu
#include <SoftwareSerial.h>
#include <ArduinoJson.h>

//D6 = Rx & D5 = Tx
//SoftwareSerial nodemcu(D6, D5);


void setup() {
  // Initialize Serial port
  Serial.begin(115200);
  //nodemcu.begin(115200);
  while (!Serial) continue;
}

void loop() {
  if (Serial.available()){
    Serial.write(Serial.read());
  }
}
/*
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& data = jsonBuffer.parseObject(nodemcu);

  if (data == JsonObject::invalid()) {
    //Serial.println("Invalid Json Object");
    jsonBuffer.clear();
    return;
  }

  Serial.println("JSON Object Recieved");
  Serial.print("Recieved Humidity:  ");
   dhthumid = data["Humidity"];
  Serial.println(hum);
  Serial.print("Recieved Temperature:  ");
  dhttemp = data["Temperature"];
  Serial.println(temp);
  Serial.println("-----------------------------------------");
}
*/
