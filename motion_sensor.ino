// @Time    : 12/8/18 7:02 PM
// @Author  : Terry LAI
// @Email   : terry.lai@hotmail.com
// @File    : motion_sensor

#include <Ticker.h>

#include <esp_wifi.h>
#include "SSD1306.h"
#include "WiFi.h"
#include <string.h>


#define host_ip // your server ip add
#define port 20000
#define Node 1

#define  c3    7634
#define  d3    6803
#define  e3    6061
#define  f3    5714
#define  g3    5102
#define  a3    4545
#define  b3    4049
#define  c4    3816    // 261 Hz 
#define  d4    3401    // 294 Hz 
#define  e4    3030    // 329 Hz 
#define  f4    2865    // 349 Hz 
#define  g4    2551    // 392 Hz 
#define  a4    2272    // 440 Hz 
#define  a4s   2146
#define  b4    2028    // 493 Hz 
#define  c5    1912    // 523 Hz
#define  d5    1706
#define  d5s   1608
#define  e5    1517
#define  f5    1433
#define  g5    1276
#define  a5    1136
#define  a5s   1073
#define  b5    1012
#define  c6    955

#define  R     0
int speakerOut = 13;



// star wars theme
int melody[] = {  f4,  f4, f4,  f5};//
int beats[]  = {  21,  21, 21,  30 }; 


int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.

// Set overall tempo
long tempo = 10000;
// Set length of my_pp between notes
long my_pp = 1000;
// Loop variable to increase Rest length
int rest_count = 50; //<-BLETCHEROUS HACK; See NOTES

// Initialize core variables
int toneM = 0;
int beat = 0;
long duration  = 0;

// PLAY TONE  ==============================================
// Pulse the speaker to play a tone for a particular duration
void playTone() {
  long elapsed_time = 0;
  if (toneM > 0) { // if this isn't a Rest beat, while the tone has 
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(speakerOut,HIGH);
      delayMicroseconds(toneM / 2);

      // DOWN
      digitalWrite(speakerOut, LOW);
      delayMicroseconds(toneM / 2);

      // Keep track of how long we pulsed
      elapsed_time += (toneM);
    } 
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);  
    }                                
  }                                 
}


#define WIFI // your wifi
#define PWD // your wifi password
const char* ssid     = WIFI;
const char* password = PWD;  

// This is the IP address of the system we will connect to for testing purposes.
const char* host = host_ip;
uint16_t    host_port = port;
WiFiClient client;

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"

Ticker flipper;

#define SDA   4
#define SCL   15
#define RST   16
#define DISPLAY_HEIGHT 128
#define DISPLAY_WIDTH  64
#define V2    1
#define Vext  21

#define len  127
#define wid  63
 
SSD1306  display(0x3c, SDA, SCL, RST);

#include "MPU6050_6Axis_MotionApps20.h"
//#include "MPU6050.h" // not necessary if using MotionApps include file

// class default I2C address is 0x68
// specific I2C addresses may be passed as a parameter here
// AD0 low = 0x68 (default for SparkFun breakout and InvenSense evaluation board)
// AD0 high = 0x69
MPU6050 mpu;
//MPU6050 mpu(0x69); // <-- use for AD0 high

#define strength 1000
#define strength_lr 500



#define INTERRUPT_PIN 2  // use pin 2 on Arduino Uno & most boards
#define LED_PIN 12 // (Arduino is 13, Teensy is 11, Teensy++ is 6)
bool blinkState = false;

// MPU control/status vars
bool dmpReady = false;  // set true if DMP init was successful
bool wifiReady = false;  // set true if DMP init was successful
uint8_t mpuIntStatus;   // holds actual interrupt status byte from MPU
uint8_t devStatus;      // return status after each device operation (0 = success, !0 = error)
uint16_t packetSize;    // expected DMP packet size (default is 42 bytes)
uint16_t fifoCount;     // count of all bytes currently in FIFO
uint8_t fifoBuffer[64]; // FIFO storage buffer

// orientation/motion vars
Quaternion q;           // [w, x, y, z]         quaternion container
VectorInt16 aa;         // [x, y, z]            accel sensor measurements
VectorInt16 aaReal;     // [x, y, z]            gravity-free accel sensor measurements
VectorInt16 aaWorld;    // [x, y, z]            world-frame accel sensor measurements
VectorFloat gravity;    // [x, y, z]            gravity vector
float ypr[3];           // [yaw, pitch, roll]   yaw/pitch/roll container and gravity vector

// ================================================================
// ===               INTERRUPT DETECTION ROUTINE                ===
// ================================================================

volatile bool mpuInterrupt = false;     // indicates whether MPU interrupt pin has gone high
void dmpDataReady() {
    mpuInterrupt = true;
}

void oled_println(const char* str) {
  display.clear();
  display.println(str);
  display.drawLogBuffer(0, 0);
  display.display();
}


void wifi(){
  
  // Setup Wifi.
  byte mac_address[7];
  WiFi.begin(ssid, password);

// Setup OLED display.
  pinMode(Vext, OUTPUT);
  digitalWrite(Vext, LOW);
  delay(50);
  display.init();
  //display.flipScreenVertically();  // Uncomment as needed.
  display.setContrast(255);
  display.setLogBuffer(5, 30);
  display.clear();

  
  oled_println("Connecting to Wifi SSID: ");
  oled_println(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    oled_println(".");
  }
 
  oled_println("\nConnected. IP address: ");
  Serial.println(WiFi.localIP());
  oled_println("Connected to Wifi.");

  delay(1000);
  
   oled_println("Connecting to ");
  oled_println(host);
  
  // Use WiFiClient class to create a TCP connection.
  // Connect to Z's test server.
  while(!client.connect(host, host_port)) {
    Serial.println("Connect failed. Retrying...");
      oled_println("Connect failed. Retrying...");

    delay(3000);
  }
  Serial.println("Connected.");
  oled_println("Connected.");

  while(!wifiReady){
      
    int count = 0;
    char reply_array[3];
    while(count<3)
    {
      while (client.connected() && client.available()) {
      uint8_t val = (uint8_t) client.read();
      reply_array[count] = val;
      count += 1;
      Serial.println(val);

      }
    }
    if( reply_array[0] == 0x11 && reply_array[1] == 0x22 && reply_array[2] == 0x33){
      wifiReady = true;
    }
    
  }

    // Set up a counter to pull from melody[] and beats[]
  for (int i=0; i<MAX_COUNT; i++) {
    toneM = melody[i];
    beat = beats[i];

    duration = beat * tempo; // Set up timing

    playTone(); 
    // A my_pp between notes...
    delayMicroseconds(my_pp);
    if (i==3){
      break;    
    }
  }
  Serial.println("out");

  pinMode(speakerOut, INPUT);
  
  
  digitalWrite(Vext, HIGH);
}

bool check_disconnect(){
      // Make sure the TCP connection is still alive.
    if (client.connected() == 0) {
      Serial.println("\n\nDisconnected. Retrying in 3 seconds...");
      oled_println("Disconnected. Reconnecting...");
      delay(3000);
      return true;
    }
    return false;
}


bool send_flag = false;

#define SEND_SIZE 10
void send_location(bool up,bool down,bool left,bool right){
  if (send_flag){
      uint8_t sned_array[SEND_SIZE];
      memset( sned_array, 0, SEND_SIZE );

      char up_b = up ? 1 : 0;
      char down_b = down ? 1 : 0;
      char left_b = left ? 1 : 0;
      char right_b = right ? 1 : 0;
      
      sned_array[0] = 0xa0;
      sned_array[1] = 0xa1;
      sned_array[2] = up_b;
      sned_array[3] = down_b;
      sned_array[4] = left_b;
      sned_array[5] = right_b;
      sned_array[6] = Node;
      
        for (int i = 0; i < SEND_SIZE; i++) {
          client.write(sned_array[i]);
        }
      send_flag = false;
  }

}

void flip()
{
  send_flag = true;
}
// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {

  pinMode(speakerOut, OUTPUT);


    flipper.attach(0.05, flip);
  
    // join I2C bus (I2Cdev library doesn't do this automatically)
    #if I2CDEV_IMPLEMENTATION == I2CDEV_ARDUINO_WIRE
        Wire.begin(SDA, SCL);
        Wire.setClock(400000); // 400kHz I2C clock. Comment this line if having compilation difficulties
    #elif I2CDEV_IMPLEMENTATION == I2CDEV_BUILTIN_FASTWIRE
        Fastwire::setup(400, true);
    #endif

    // initialize serial communication
    // (115200 chosen because it is required for Teapot Demo output, but it's
    // really up to you depending on your project)
    Serial.begin(9600);
    while (!Serial); // wait for Leonardo enumeration, others continue immediately

    // initialize device
    Serial.println(F("Initializing I2C devices..."));
    mpu.initialize();
    pinMode(INTERRUPT_PIN, INPUT);

    // verify connection
    Serial.println(F("Testing device connections..."));
    Serial.println(mpu.testConnection() ? F("MPU6050 connection successful") : F("MPU6050 connection failed"));

    wifi();
    
    // load and configure the DMP
    Serial.println(F("Initializing DMP..."));
    devStatus = mpu.dmpInitialize();

    // supply your own gyro offsets here, scaled for min sensitivity
    mpu.setXGyroOffset(220);
    mpu.setYGyroOffset(76);
    mpu.setZGyroOffset(-85);
    mpu.setZAccelOffset(1788); // 1688 factory default for my test chip

    // make sure it worked (returns 0 if so)
    if (devStatus == 0) {
        // turn on the DMP, now that it's ready
        Serial.println(F("Enabling DMP..."));
        mpu.setDMPEnabled(true);

        // enable Arduino interrupt detection
        Serial.print(F("Enabling interrupt detection (Arduino external interrupt "));
        Serial.print(digitalPinToInterrupt(INTERRUPT_PIN));
        Serial.println(F(")..."));
        attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), dmpDataReady, RISING);
        mpuIntStatus = mpu.getIntStatus();

        dmpReady = true;

        // get expected DMP packet size for later comparison
        packetSize = mpu.dmpGetFIFOPacketSize();
    } else {
        // ERROR!
        // 1 = initial memory load failed
        // 2 = DMP configuration updates failed
        // (if it's going to break, usually the code will be 1)
        Serial.print(F("DMP Initialization failed (code "));
        Serial.print(devStatus);
        Serial.println(F(")"));
    }

    // configure LED for output
    pinMode(LED_PIN, OUTPUT);
}



// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================


void loop() {

  
    //Serial.println("loop");
    // if programming failed, don't try to do anything
    if (!dmpReady or !wifiReady) return;

    // wait for MPU interrupt or extra packet(s) available
    while (!mpuInterrupt && fifoCount < packetSize) {
        if (mpuInterrupt && fifoCount < packetSize) {
          // try to get out of the infinite loop 
          fifoCount = mpu.getFIFOCount();
        }  
 
    }

    // reset interrupt flag and get INT_STATUS byte
    mpuInterrupt = false;
    mpuIntStatus = mpu.getIntStatus();

    // get current FIFO count
    fifoCount = mpu.getFIFOCount();

    // check for overflow (this should never happen unless our code is too inefficient)
    if ((mpuIntStatus & _BV(MPU6050_INTERRUPT_FIFO_OFLOW_BIT)) || fifoCount >= 1024) {
        // reset so we can continue cleanly
        mpu.resetFIFO();
        fifoCount = mpu.getFIFOCount();
        Serial.println(F("FIFO overflow!"));

    // otherwise, check for DMP data ready interrupt (this should happen frequently)
    } else if (mpuIntStatus & _BV(MPU6050_INTERRUPT_DMP_INT_BIT)) {
        // wait for correct available data length, should be a VERY short wait
        while (fifoCount < packetSize) fifoCount = mpu.getFIFOCount();

        // read a packet from FIFO
        mpu.getFIFOBytes(fifoBuffer, packetSize);
        
        // track FIFO count here in case there is > 1 packet available
        // (this lets us immediately read more without waiting for an interrupt)
        fifoCount -= packetSize;

        // display Euler angles in degrees
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);

        mpu.dmpGetAccel(&aa, fifoBuffer);
        mpu.dmpGetLinearAccel(&aaReal, &aa, &gravity);
        mpu.dmpGetLinearAccelInWorld(&aaWorld, &aaReal, &q);
            
        float roll = ypr[2]* 180/M_PI;
        float pitch = ypr[1]* 180/M_PI;

        float up_greater =  0;
        float up_smaller =  125;
        
        float down_greater =  -120 ;
        float down_smaller =  -40;

        float left_greater =  -120;
        float left_smaller =   -30;

        float right_greater =  60;
        float right_smaller =  120;

        bool up = roll > up_greater && roll < up_smaller ;
        bool down = roll > down_greater && roll < down_smaller ;
        bool left = pitch > left_greater && pitch < left_smaller ;
        bool right = pitch > right_greater && pitch < right_smaller;


        if(up)
        {
           Serial.print("up") ;
        }
        if(down)
        {
           Serial.print("down") ;
        }

        if(left)
        {
           Serial.print("left") ;
        }

        if(right)
        {
           Serial.print("right") ;
        }

        send_location(up,down,left,right);

        // blink LED to indicate activity
        blinkState = !blinkState;
        digitalWrite(LED_PIN, blinkState);
    }
}
