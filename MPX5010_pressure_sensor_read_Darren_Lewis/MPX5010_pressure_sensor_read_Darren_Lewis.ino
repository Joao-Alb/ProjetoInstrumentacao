/*
  Darren Lewis calculated pressure readings MPX5010 baed on datasheet
  datasheet: https://docs.rs-online.com/9979/0900766b8138443c.pdf
  my website: http://darrenlewismechatronics.co.uk/
*/
const float ADC_mV = 4.8828125;       // convesion multiplier from Arduino ADC value to voltage in mV
const float SensorOffset = 0.0;     // in mV taken from datasheet
const float sensitivity = 4.413;      // in mV/mmH2O taken from datasheet
const float mmh2O_cmH2O = 10;         // divide by this figure to convert mmH2O to cmH2O
const float mmh2O_kpa = 0.00981;      // convesion multiplier from mmH2O to kPa

volatile int countOffset = 0;
volatile float offset = 0;

void setup() {
  Serial.begin(9600);
}

void loop() {
  // ((sensorValue in mV -sensorOffset)/sensitivity in mV/mmH2O)*kPa conversion constant
  //float sensorValue = ((analogRead(A0) * ADC_mV - SensorOffset) / sensitivity * mmh2O_kpa);     // result in kPa
  // float sensorValue = (analogRead(A0) * ADC_mV - SensorOffset) / sensitivity / mmh2O_cmH2O;       // result in cmH2O

  // Serial.print(millis());
  // Serial.println(sensorValue, 2);
  // using serial print format above, you can copy your data from the terminal,
  // paste it into NotePad app, than save as a .CSV file which can be opened in Excel

  int   CountsPressureSensor = 0;
  float PressureRead = 0;

  CountsPressureSensor = analogRead(A0);
  PressureRead = ((float)CountsPressureSensor*10.0)/1024.0;
  if (countOffset<100){
    countOffset++;
    offset+=PressureRead;
    if (countOffset==100){
      offset/=100;
      Serial.print("Offset = ");
      Serial.println(offset);
    }
    delay(100);
  }
  else{

    float resultado = PressureRead - offset;
    Serial.println(resultado);
    delay(100);
  }


}
