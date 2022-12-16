// modified by AWlabs , kodingan untuk praktikum termodinamika
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h> 
#include <Adafruit_INA219.h> 

#define ONE_WIRE_BUS_1 4
#define ONE_WIRE_BUS_2 6

OneWire oneWire_in(ONE_WIRE_BUS_1);
OneWire oneWire_out(ONE_WIRE_BUS_2);

DallasTemperature sensor_inhouse(&oneWire_in);
DallasTemperature sensor_outhouse(&oneWire_out);

const int INA_addr = 0x40;  // INA219 address
 
Adafruit_INA219 ina219(INA_addr);

const int voltageSensor = A0;

float vOUT = 0.0;
float vIN = 0.0;
float R1 = 30000.0;
float R2 = 7500.0;
int value = 0;
float tegangan = 00;
float arus = 00; // diukur menggunakan MiliAmpere 
float daya = 00; 
 
void setup(void)
{
  Serial.begin(9600);
  Serial.println("CLEARDATA");
  Serial.println("LABEL, Time, Started Time, Date, Suhu_1 C, suhu_2 C, tegangan (Volt), arus (mA), daya (watt)");
  Serial.println("RESETTIMER");
  sensor_inhouse.begin();
  sensor_outhouse.begin();
  ina219.begin();  
}

void loop(void)
{
  //pembacaan sensor suhu 
  sensor_inhouse.requestTemperatures();
  sensor_outhouse.requestTemperatures();
  
  // pembacaan sensor arus dan tegangan (daya)
  tegangan = ina219.getBusVoltage_V(); //command untuk pembacaan tegangan 
  arus = ina219.getCurrent_mA(); //command untuk pembacaan arus 
  daya = tegangan * (arus/1000); //rumus untuk mendapatkan nilai watt 
  
  // pengiriman data ke excel
  Serial.print("DATA, TIME, TIMER, DATE,");
  Serial.print(sensor_inhouse.getTempCByIndex(0));
  Serial.print(" ,");
  Serial.print(sensor_outhouse.getTempCByIndex(0));
  Serial.print(" ,");  
  Serial.print(tegangan); 
  Serial.print(" ,");
  Serial.print(arus);
  Serial.print(" ,");
  Serial.print(daya); 
  Serial.println(" ,");  
  delay(1000);

  delay(300);
}
