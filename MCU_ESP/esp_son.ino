#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include<SoftwareSerial.h>

SoftwareSerial espUart(13, 15);  // SRX = D7, STX = D8

// Set these to run example.
#define FIREBASE_HOST "project--db-default-rtdb.europe-west1.firebasedatabase.app"
#define FIREBASE_AUTH "9QcoehXWV1dqR0vqLqFMFO633hhgsnj3iwhOd64o"
#define WIFI_SSID "herkesebenden"
#define WIFI_PASSWORD "erdem123"

const byte numBytes = 21;
byte receivedBytes[numBytes];
byte numReceived = 0;

boolean newData = false;

void setup() {
    Serial.begin(115200);
  //  espUart.begin(115200);
    Serial.println("<Arduino is ready>");

     // connect to wifi.
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
    }
    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());
  
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
    recvBytesWithStartEndMarkers();
    showNewData();

   
}

void recvBytesWithStartEndMarkers() {
    static boolean recvInProgress = false;
    static byte ndx = 0;
    byte startMarker = 0x31;
    byte endMarker = 0x32;
    byte rb;
   

    while (Serial.available() > 0 && newData == false) {
        rb = Serial.read();

        if (recvInProgress == true) {
            if (rb != endMarker) {
                receivedBytes[ndx] = rb;
                ndx++;
                if (ndx >= numBytes) {
                    ndx = numBytes - 1;
                }
            }
            else {
                receivedBytes[ndx] = '\0'; // terminate the string
                recvInProgress = false;
                numReceived = ndx;  // save the number for use when printing
                ndx = 0;
                newData = true;
            }
        }

        else if (rb == startMarker) {
            recvInProgress = true;
        }
    }
}

void showNewData() {
    if (newData == true) {
        Serial.print("This just in (HEX values)... ");
        for (byte n = 0; n < numReceived; n++) {
            Serial.print(receivedBytes[n], HEX);
            Serial.print(' ');

            uint32_t pressure = receivedBytes[4]       | 
                               (receivedBytes[3] << 8) | 
                               (receivedBytes[2] << 16)| 
                               (receivedBytes[1] << 24);


            double lattitude_zoe_m8q =     receivedBytes[8]       |
                                           (receivedBytes[9] << 8) |
                                           (receivedBytes[10] << 16)|
                                           (receivedBytes[11] << 24);

            double longtitude_zoe_m8q =    receivedBytes[12]       |
                                            (receivedBytes[13] << 8) |
                                            (receivedBytes[14] << 16)|
                                            (receivedBytes[15] << 24);

            uint32_t altitude_zoe_m8q  =     receivedBytes[16]       |
                                            (receivedBytes[17] << 8) |
                                            (receivedBytes[18] << 16)|
                                            (receivedBytes[19] << 24);
                                            
            altitude_zoe_m8q = altitude_zoe_m8q / 1000;

            float latitude   = lattitude_zoe_m8q / 10000000;
            float longtitude = longtitude_zoe_m8q / 10000000;
            
            Firebase.setFloat("datas/temperature", receivedBytes[0]);0
            Firebase.setFloat("datas/pressure", pressure);
            Firebase.setFloat("datas/humidity", receivedBytes[5]);
            Firebase.setFloat("datas/altitude",altitude_zoe_m8q);
            Firebase.setFloat("datas/latitude", longtitude);
            Firebase.setFloat("datas/longtitude", latitude);
            Firebase.setFloat("datas/w-cond", receivedBytes[6]);
        }
        Serial.println();
        newData = false;
    }
}
