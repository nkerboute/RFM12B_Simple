//Simple RFM12B wireless demo - transimtter - no ack
//Glyn Hudson openenergymonitor.org GNU GPL V3 7/7/11
//Credit to JCW from Jeelabs.org for RFM12 
#define RF69_COMPAT 0  // define this to use the RF69 driver i.s.o. RF12
#include <JeeLib.h>  //from jeelabs.org

#define myNodeID 10          //node ID of tx (range 0-30)
#define network     210      //network group (can be in the range 1-250).
#define RF_freq RF12_433MHZ     //Freq of RF12B can be RF12_433MHZ, RF12_868MHZ or RF12_915MHZ. Match freq to module


typedef struct { int power1, power2, power3, battery; } PayloadTX;      // create structure - a neat way of packaging data for RF comms
PayloadTX emontx;  

const int LED = 6;                                             //emonTx V3
void setup() {
  rf12_initialize(myNodeID,RF_freq,network);   //Initialize RFM12 with settings defined above  
Serial.begin(9600);
Serial.println("RFM12B Transmitter - Simple demo");

 Serial.print("Node: "); 
 Serial.print(myNodeID); 
 Serial.print(" Freq: "); 
 if (RF_freq == RF12_433MHZ) Serial.print("433Mhz");
 if (RF_freq == RF12_868MHZ) Serial.print("868Mhz");
 if (RF_freq == RF12_915MHZ) Serial.print("915Mhz"); 
 Serial.print(" Network: "); 
 Serial.println(network);

pinMode(LED, OUTPUT);

}

void loop() {
  emontx.power1=emontx.power1+1;
  emontx.power2=emontx.power2+2;
  emontx.power3=emontx.power3+3;
  emontx.battery=emontx.battery+4;
    
    rf12_sendNow(0, &emontx, sizeof emontx);                    
    rf12_sendWait(2);
    
  Serial.print("power1: "); Serial.println(emontx.power1); 
  Serial.print("power2: "); Serial.println(emontx.power2); 
  Serial.print("power3: "); Serial.println(emontx.power3); 
  Serial.print("battery: "); Serial.println(emontx.battery); 
  Serial.println("  "); 
  
  digitalWrite(LED, HIGH); delay(500); digitalWrite(LED, LOW);   
  delay(2000);
}
