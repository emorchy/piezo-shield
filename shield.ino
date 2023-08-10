#include <Arduino.h>
#include <TM1637Display.h>
using namespace std;
#define CLK 2
#define DIO 3
#define THRESHOLD 60 //sensitivity of shield depending on force of candy/object (0-255)
#define ATTEMPTS 1 //number of attempts before averaging values (1 for speed (i.e rapid simulateous projectiles), more for reliability (turn down threshold))
#define DELAY 25 //prevents multiple counts for the same projectile. Low: speedy, high chance of multi-counting. High: chance of missing projectile, low chance of multi-counting

const int knockSensors[5] = {A0, A1, A2, A3, A4}; //change as needed for number of sensors
const int pinKey = 9; //push-button
unsigned long resetTime = 0;
unsigned long downTime = 0;
bool clicked = false;
TM1637Display display(CLK, DIO);

void key(){ //used to prevent sleep in project boost converter.
  unsigned long newTime = millis();
  if (newTime - resetTime > 20000){ //pulse on button every 20s
    if (!clicked){
      pinMode(pinKey, OUTPUT);
      digitalWrite(pinKey, LOW);
      clicked = true;
      downTime = millis();
    } else {
      if (millis() - downTime > 100){
        pinMode(pinKey, INPUT);
        resetTime = newTime;
        clicked = false;
      }
    }
  }
}

class BuzzersData {
  public:
    int attempts;
    int sensorCount;
    float** singleAttempt;
    
    float** initialize(){ //returns 2D float array: attempts x number of sensors
      float** arr = new float*[attempts];
        for (int i = 0; i < attempts; i++) {
          arr[i] = new float[sensorCount];
        }
      return arr;
    }

    void interface_sensors(float **buzzer_data, int index){ //writes to array
      for (int i=0; i < sensorCount; i++){
        buzzer_data[index][i] = analogRead(knockSensors[i]); //read sensor data into given attempt array
      }
    }

    float** getdata(){ //read all sensors "attempts" number of times
      for (int i=0; i < attempts; i++){
        interface_sensors(singleAttempt, i);
      }
      return singleAttempt; //returns float buffer of attempts x sensors
    }

    float* average(){ //does nothing if ATTEMPTS = 1 because there is only one data point per sensor
      for (int i=0; i < attempts - 1; i++){ //combines all sensor data rows into first row
        for (int j=0; j < sensorCount; j++){
          singleAttempt[0][j] += singleAttempt[i+1][j]; //places sum of all data in first attempt array
        }
      }
      for (int i=0; i < sensorCount; i++){
        singleAttempt[0][i] /= attempts; //divides each sensor sum by the number of attempts
      }
      return singleAttempt[0];
    }
  private:
};

BuzzersData bd; //initialize class
int counter = 0;

void setup() {
   //Serial.begin(9600); //uncomment for debugging
   bd.attempts = ATTEMPTS; //ATTEMPT per averaging
   bd.sensorCount = sizeof(knockSensors) / 2; //buffer size (int is 2 bytes)
   bd.singleAttempt = bd.initialize(); //creates empty attempt buffer
   display.setBrightness(0x01); //sets brightness of led screen (0-7)
   display.showNumberDec(counter, true);
}

void loop() {
  key(); //remove if not using https://www.amazon.com/MakerFocus-Discharge-Integrated-Charging-Protection/dp/B07PZT3ZW2
  float **singleAttempt = bd.getdata(); //fills attempt buffer with data
  float* averageArr = bd.average(); //averages attempt buffer
  //Serial.print("Average sensor data: ");
  for (int i=0; i < bd.sensorCount; i++){ //checks if each sensor data is above threshold
    //Serial.print(averageArr[i]);
    //Serial.print(" ");
    if (averageArr[i] > THRESHOLD){
      counter++; //increase counter for every sensor above threshold
      display.showNumberDec(counter, true);
      delay(DELAY); //prevents multiple increases for the same projectile. Low decrease
      break;
    }
  }
  //Serial.println();
}
