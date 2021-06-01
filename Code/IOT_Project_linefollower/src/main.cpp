//==================================================
/*
Written by: Nathan Laureyn
Version:    v0.2
Date:       08/05/2021
Description:
blablabla
 */
//==================================================

#include <Arduino.h>
#include <AccelStepper.h>
#include <WiFi.h>
#include <PubSubClient.h>

//==================================================

//Wifi Setup==================================================
// MQTT client
const char *ssid = "Protected CEX";
const char *password = "geeninternet";

const char *mqttServer = "192.168.137.187";
const int mqttPort = 1883;
const char *mqttUser = "nqtt";
const char *mqttPassword = "nqtt123";
const char *clientID = "LineFollower";

WiFiClient espClient;
PubSubClient client(espClient);

//Topics
const char *linefollower_status_topic = "home/car/carstatus";
const char *linefollower_control_topic = "home/car/control";

//Payloads
char *CarStatus = "Online";
char *PreviousCarStatus = "Offline";

bool Controloverwrite = false;

//Peripherals==================================================
//Sensorsetup--------------------------------------------------
//Linesensor--------------------------------------------------
//Defines/////////////
//Pins
#define SensL 27  //D1
#define SensML 26 //D2
#define SensM 25  //D3
#define SensMR 33 //D4
#define SensR 32  //D5
//Readmacro's
#define ReadSensL digitalRead(SensL)   //D1
#define ReadSensML digitalRead(SensML) //D2
#define ReadSensM digitalRead(SensM)   //D3
#define ReadSensMR digitalRead(SensMR) //D4
#define ReadSensR digitalRead(SensR)   //D5

//Readsensorcases
//Invert
#define invert == //place == for normal operations and != for inverted operation

//Cases

// ╔═════════╦══════════════╦═════╦═════╦═════╦═════╦═════╦══════╗
// ║ Case nr ║  Sensors=>   ║  L  ║ ML  ║  M  ║ MR  ║  R  ║ Dist ║
// ╠═════════╬══════════════╬═════╬═════╬═════╬═════╬═════╬══════╣
// ║       1 ║ ExtremeLeft  ║ ON  ║ OFF ║ OFF ║ OFF ║ OFF ║ OFF  ║
// ║       2 ║ HardLeft     ║ ON  ║ ON  ║ OFF ║ OFF ║ OFF ║ OFF  ║
// ║       3 ║ MediumLeft   ║ OFF ║ ON  ║ OFF ║ OFF ║ OFF ║ OFF  ║
// ║       4 ║ SoftLeft     ║ OFF ║ ON  ║ ON  ║ OFF ║ OFF ║ OFF  ║
// ║       5 ║ Strait       ║ OFF ║ OFF ║ ON  ║ OFF ║ OFF ║ OFF  ║
// ║       6 ║ SoftRight    ║ OFF ║ OFF ║ ON  ║ ON  ║ OFF ║ OFF  ║
// ║       7 ║ MediumRight  ║ OFF ║ OFF ║ OFF ║ ON  ║ OFF ║ OFF  ║
// ║       8 ║ HardRight    ║ OFF ║ OFF ║ OFF ║ ON  ║ ON  ║ OFF  ║
// ║       9 ║ ExtremeRight ║ OFF ║ OFF ║ OFF ║ OFF ║ ON  ║ OFF  ║
// ║      10 ║ CrossLine    ║ ON  ║ ON  ║ ON  ║ ON  ║ ON  ║ OFF  ║
// ║      11 ║ LOSTLine     ║ OFF ║ OFF ║ OFF ║ OFF ║ OFF ║ OFF  ║
// ║      12 ║ Objectdetect ║ OFF ║ OFF ║ OFF ║ OFF ║ OFF ║ ON   ║
// ╚═════════╩══════════════╩═════╩═════╩═════╩═════╩═════╩══════╝

#define ExtremeLeftSens ReadSensL invert HIGH &&ReadSensML invert LOW &&ReadSensM invert LOW &&ReadSensMR invert LOW &&ReadSensR invert LOW

#define HardLeftSens ReadSensL invert HIGH &&ReadSensML invert HIGH &&ReadSensM invert LOW &&ReadSensMR invert LOW &&ReadSensR invert LOW

#define MediumLeftSens ReadSensL invert LOW &&ReadSensML invert HIGH &&ReadSensM invert LOW &&ReadSensMR invert LOW &&ReadSensR invert LOW

#define SoftLeftSens ReadSensL invert LOW &&ReadSensML invert HIGH &&ReadSensM invert HIGH &&ReadSensMR invert LOW &&ReadSensR invert LOW

#define StraitSens ReadSensL invert LOW &&ReadSensML invert LOW &&ReadSensM invert HIGH &&ReadSensMR invert LOW &&ReadSensR invert LOW

#define SoftRightSens ReadSensL invert LOW &&ReadSensML invert LOW &&ReadSensM invert HIGH &&ReadSensMR invert HIGH &&ReadSensR invert LOW

#define MediumRightSens ReadSensL invert LOW &&ReadSensML invert LOW &&ReadSensM invert LOW &&ReadSensMR invert HIGH &&ReadSensR invert LOW

#define HardRightSens ReadSensL invert LOW &&ReadSensML invert LOW &&ReadSensM invert LOW &&ReadSensMR invert HIGH &&ReadSensR invert HIGH

#define ExtremeRightSens ReadSensL invert LOW &&ReadSensML invert LOW &&ReadSensM invert LOW &&ReadSensMR invert LOW &&ReadSensR invert HIGH

#define CrossLineSens ReadSensL invert HIGH &&ReadSensML invert HIGH &&ReadSensM invert HIGH &&ReadSensMR invert HIGH &&ReadSensR invert HIGH

#define LOSTLineSens ReadSensL invert LOW &&ReadSensML invert LOW &&ReadSensM invert LOW &&ReadSensMR invert LOW &&ReadSensR invert LOW

#define Objectdetectsens cm <= TRG_Point

//DistanceSensorsetup--------------------------------------------------
//Defines/////////////
//Pins

#define TRIGGER_PIN 12 //  pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN 13    //  pin tied to echo pin on the ultrasonic sensor.
#define TRG_Point 40   // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
int duration;
int inches;
int cm;

//Buttonsetup--------------------------------------------------
//Defines/////////////
//Pins
#define SkipWaitButton 34 //Pin to be used with skip button

//Led setup--------------------------------------------------

/*
Problem signalisation guide
▪ Green led : No problems
▪ Blue led  : Object detected or crossline
▪ Red led   : Lost line
*/

// Defines some pins the leds will use
#define RGBLrR 15 //D15
#define RGBLgR 16 //D16
#define RGBLbR 17 //D17

#define RGBLrL 2  //D2
#define RGBLgL 14 //D14
#define RGBLbL 18 //D18

#define RGBoff               \
  digitalWrite(RGBLrR, LOW); \
  digitalWrite(RGBLgR, LOW); \
  digitalWrite(RGBLbR, LOW); \
  digitalWrite(RGBLrL, LOW); \
  digitalWrite(RGBLgL, LOW); \
  digitalWrite(RGBLbL, LOW);

//Motorsetup--------------------------------------------------
// Defines some steppers and the pins the motors will use
AccelStepper stepperR(AccelStepper::DRIVER, 23, 19);
AccelStepper stepperL(AccelStepper::DRIVER, 5, 4);
//Speedmacro's
#define StandardSpeed 100                            //sets standard maxspeed
#define StandardAccel 100.0                           //sets standard acceleration
#define StandardLocation currentPosition() - 1000000 //sets standard location

#define ExtremeLeftSpeed StandardSpeed / 1.0000001
#define HardLeftSpeed StandardSpeed / 3
#define MediumLeftSpeed StandardSpeed / 1.5
#define SoftLeftSpeed StandardSpeed / 1.2
#define StraitSpeed StandardSpeed
#define SoftRightSpeed StandardSpeed / 1.2
#define MediumRightSpeed StandardSpeed / 1.5
#define HardRightSpeed StandardSpeed / 3
#define ExtremeRightSpeed StandardSpeed / 1.0000001

#define CrossLineSpeed StandardSpeed - 99.99999
#define LOSTLineSpeed StandardSpeed / 2

int LineStatus;

//Speedcommands
void ExtremeLeft()
{
  stepperR.setMaxSpeed(StandardSpeed);
  stepperL.setMaxSpeed(ExtremeLeftSpeed);
  //stepperR.setAcceleration(StandardAccel);
  //stepperL.setAcceleration(StandardAccel);
  stepperR.moveTo((stepperR.StandardLocation));
  stepperL.moveTo(stepperL.currentPosition());

  RGBoff

      digitalWrite(RGBLgL, HIGH);
  digitalWrite(RGBLgR, LOW);

  //Serial.println("ExtremeLeft");
  CarStatus = "Driving";
}
void HardLeft()
{
  stepperR.setMaxSpeed(StandardSpeed);
  stepperL.setMaxSpeed(HardLeftSpeed);
  //stepperR.setAcceleration(StandardAccel);
  //stepperL.setAcceleration(StandardAccel);
  stepperR.moveTo((stepperR.StandardLocation));
  stepperL.moveTo((stepperL.StandardLocation));

  RGBoff

      digitalWrite(RGBLgL, HIGH);
  digitalWrite(RGBLgR, LOW);

  //Serial.println("HardLeft");
  CarStatus = "Driving";
}
void MediumLeft()
{
  stepperR.setMaxSpeed(StandardSpeed);
  stepperL.setMaxSpeed(MediumLeftSpeed);
  //stepperR.setAcceleration(StandardAccel);
  //stepperL.setAcceleration(StandardAccel);
  stepperR.moveTo((stepperR.StandardLocation));
  stepperL.moveTo((stepperL.StandardLocation));

  RGBoff

      digitalWrite(RGBLgL, HIGH);
  digitalWrite(RGBLgR, LOW);

  //Serial.println("MediumLeft");
  CarStatus = "Driving";
}
void SoftLeft()
{
  stepperR.setMaxSpeed(StandardSpeed);
  stepperL.setMaxSpeed(SoftLeftSpeed);
  //stepperR.setAcceleration(StandardAccel);
  //stepperL.setAcceleration(StandardAccel);
  stepperR.moveTo((stepperR.StandardLocation));
  stepperL.moveTo((stepperL.StandardLocation));

  RGBoff

      digitalWrite(RGBLgL, HIGH);
  digitalWrite(RGBLgR, LOW);

  //Serial.println("SoftLeft");
  CarStatus = "Driving";
}
void Strait()
{
  stepperR.setMaxSpeed(StraitSpeed);
  stepperL.setMaxSpeed(StraitSpeed);
  //stepperR.setAcceleration(StandardAccel);
  //stepperL.setAcceleration(StandardAccel);
  stepperR.moveTo((stepperR.StandardLocation));
  stepperL.moveTo((stepperL.StandardLocation));

  RGBoff

      digitalWrite(RGBLgL, HIGH);
  digitalWrite(RGBLgR, HIGH);

  //Serial.println("Strait");
  CarStatus = "Driving";
}
void SoftRight()
{
  stepperR.setMaxSpeed(SoftRightSpeed);
  stepperL.setMaxSpeed(StandardSpeed);
  //stepperR.setAcceleration(StandardAccel);
  //stepperL.setAcceleration(StandardAccel);
  stepperR.moveTo((stepperR.StandardLocation));
  stepperL.moveTo((stepperL.StandardLocation));

  RGBoff

      digitalWrite(RGBLgL, LOW);
  digitalWrite(RGBLgR, HIGH);

  //Serial.println("SoftRight");
  CarStatus = "Driving";
}
void MediumRight()
{
  stepperR.setMaxSpeed(MediumRightSpeed);
  stepperL.setMaxSpeed(StandardSpeed);
  //stepperR.setAcceleration(StandardAccel);
  //stepperL.setAcceleration(StandardAccel);
  stepperR.moveTo((stepperR.StandardLocation));
  stepperL.moveTo((stepperL.StandardLocation));

  RGBoff

      digitalWrite(RGBLgL, LOW);
  digitalWrite(RGBLgR, HIGH);

  //Serial.println("MediumRight");
  CarStatus = "Driving";
}
void HardRight()
{
  stepperR.setMaxSpeed(HardRightSpeed);
  stepperL.setMaxSpeed(StandardSpeed);
  //stepperR.setAcceleration(StandardAccel);
  //stepperL.setAcceleration(StandardAccel);
  stepperR.moveTo((stepperR.StandardLocation));
  stepperL.moveTo((stepperL.StandardLocation));

  RGBoff

      digitalWrite(RGBLgL, LOW);
  digitalWrite(RGBLgR, HIGH);

  //Serial.println("HardRight");
  CarStatus = "Driving";
}
void ExtremeRight()
{
  stepperR.setMaxSpeed(ExtremeRightSpeed);
  stepperL.setMaxSpeed(StandardSpeed);
  //stepperR.setAcceleration(StandardAccel);
  //stepperL.setAcceleration(StandardAccel);
  stepperR.moveTo(stepperR.currentPosition());
  stepperL.moveTo((stepperL.StandardLocation));

  RGBoff

      digitalWrite(RGBLgL, LOW);
  digitalWrite(RGBLgR, HIGH);

  //Serial.println("ExtremeRight");
  CarStatus = "Driving";
}
void CrossLine()
{
  unsigned long Stoptime = 5000;

  stepperR.setMaxSpeed(CrossLineSpeed);
  stepperL.setMaxSpeed(CrossLineSpeed);
  stepperR.setAcceleration(1000);
  stepperL.setAcceleration(1000);
  stepperR.moveTo(stepperR.currentPosition());
  stepperL.moveTo(stepperL.currentPosition());

  RGBoff

      digitalWrite(RGBLbL, HIGH);
  digitalWrite(RGBLbR, HIGH);
  CarStatus = "Crossline";

  for (int i = 0; i < Stoptime; i++)

  {
    if (digitalRead(SkipWaitButton) == HIGH || Controloverwrite == true)
    {
      i = Stoptime;
      Controloverwrite = false;
    }
    else
    {
      delay(1000);
      i = i + 1000;
    }
    stepperR.setAcceleration(StandardAccel);
    stepperL.setAcceleration(StandardAccel);
  }

  stepperR.setMaxSpeed(StraitSpeed);
  stepperL.setMaxSpeed(StraitSpeed);
  //stepperR.setAcceleration(StandardAccel);
  //stepperL.setAcceleration(StandardAccel);
  stepperR.moveTo((stepperR.StandardLocation));
  stepperL.moveTo((stepperL.StandardLocation));
  delay(500);

  //Serial.println("CrossLine");
}
void LOSTLine()
{
  stepperR.setMaxSpeed(LOSTLineSpeed);
  stepperL.setMaxSpeed(-LOSTLineSpeed);
  stepperR.setAcceleration(1000);
  stepperL.setAcceleration(1000);
  stepperR.moveTo((stepperR.StandardLocation));
  stepperL.moveTo(-(stepperL.StandardLocation));

  RGBoff

      digitalWrite(RGBLrL, HIGH);
  digitalWrite(RGBLrR, HIGH);

  //Serial.println("LOSTLine");
  CarStatus = "Lostline";
}
void Objectdetect()
{
  stepperR.setMaxSpeed(StandardSpeed);
  stepperL.setMaxSpeed(StandardSpeed);
  //stepperR.setAcceleration(StandardAccel);
  //stepperL.setAcceleration(StandardAccel);
  stepperR.moveTo(stepperR.currentPosition());
  stepperL.moveTo(stepperL.currentPosition());
  RGBoff

      digitalWrite(RGBLbL, HIGH);
  digitalWrite(RGBLbR, HIGH);

  //Serial.println("Objectdetect");
  CarStatus = "Objectdetect";
}

void callback(char *topic, byte *payload, unsigned int length)
{

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message:");

  String messageTemp;
  for (int i = 0; i < length; i++)
  {
    Serial.print((char)payload[i]);
    messageTemp += (char)payload[i];
  }
  Serial.println();

  // Feel free to add more if statements to control more GPIOs with MQTT

  // If a message is received on the topic esp32/output, you check if the message is either "on" or "off".
  // Changes the output state according to the message

  Serial.print("Changing output to ");
  if (messageTemp == "Driveoverwrite")
  {
    Controloverwrite = true;
    Serial.println("-----------------------");
  }

  Serial.println();
  Serial.println("-----------------------");
}

//Tasks==================================================
void taskstep(void *parameters)
{
  for (;;)
  {
    switch (LineStatus)
    {
    case 1:
      ExtremeLeft();
      //Serial.println("	ExtremeLeft	");
      break;
    case 2:
      HardLeft();
      //Serial.println("	HardLeft	");
      break;
    case 3:
      MediumLeft();
      //Serial.println("	MediumLeft	");
      break;
    case 4:
      SoftLeft();
      //Serial.println("	SoftLeft	");
      break;
    case 5:
      Strait();
      //Serial.println("	Strait	");
      break;
    case 6:
      SoftRight();
      //Serial.println("	SoftRight	");
      break;
    case 7:
      MediumRight();
      //Serial.println("	MediumRight	");
      break;
    case 8:
      HardRight();
      //Serial.println("	HardRight	");
      break;
    case 9:
      ExtremeRight();
      //Serial.println("	ExtremeRight	");
      break;
    case 10:
      CrossLine();
      //Serial.println("	CrossLine	");
      break;
    case 11:
      LOSTLine();
      //Serial.println("	LOSTLine	");
      break;
    case 12:
      Objectdetect();
      //Serial.println("	Objectdetect	");
      break;

    default:
      break;
    }

    //Serial.println("steptask");
    vTaskDelay(20 / portTICK_PERIOD_MS);
  }
}

void SensLine(void *parameters)
{

  for (;;)
  {

    if (ExtremeLeftSens)
    {
      LineStatus = 1;
      //Serial.println("	ExtremeLeft	");
    }
    else if (HardLeftSens)
    {
      LineStatus = 2;
      //Serial.println("	HardLeft	");
    }
    else if (MediumLeftSens)
    {
      LineStatus = 3;
      //Serial.println("	MediumLeft	");
    }
    else if (SoftLeftSens)
    {
      LineStatus = 4;
      //Serial.println("	SoftLeft	");
    }
    else if (StraitSens)
    {
      LineStatus = 5;
      //Serial.println("	Strait	");
    }
    else if (SoftRightSens)
    {
      LineStatus = 6;
      //Serial.println("	SoftRight	");
    }
    else if (MediumRightSens)
    {
      LineStatus = 7;
      //Serial.println("	MediumRight	");
    }
    else if (HardRightSens)
    {
      LineStatus = 8;
      //Serial.println("	HardRight	");
    }
    else if (ExtremeRightSens)
    {
      LineStatus = 9;
      //Serial.println("	ExtremeRight	");
    }
    else if (CrossLineSens)
    {
      LineStatus = 10;
      //Serial.println("	CrossLine	");
    }
    else if (LOSTLineSens)
    {
      LineStatus = 11;
      //Serial.println("	LOSTLine	");
    }
    if (Objectdetectsens)
    {
      LineStatus = 12;
      //Serial.println("	Objectdetectsens	");
    }
    //Serial.println("SensLine");
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}

void SensDistance(void *parameters)
{

  for (;;)
  {

    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    digitalWrite(TRIGGER_PIN, LOW);
    delayMicroseconds(5);
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);

    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(ECHO_PIN, INPUT);
    duration = pulseIn(ECHO_PIN, HIGH);

    // Convert the time into a distance
    cm = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
    inches = (duration / 2) / 74; // Divide by 74 or multiply by 0.0135

    /* 
   Serial.print(inches);
    Serial.print("in, ");
    Serial.print(cm);
    Serial.print("cm");
    Serial.println();
    */

    vTaskDelay(200 / portTICK_PERIOD_MS);
  }
}

void MQTTPublish(void *parameters)
{

  for (;;)
  {
    if (CarStatus != PreviousCarStatus)
    {
      client.publish(linefollower_status_topic, CarStatus);
      Serial.println(linefollower_status_topic);
      Serial.println(CarStatus);
      PreviousCarStatus = CarStatus;
    }
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
void MQTTClient(void *parameters)
{

  for (;;)
  {
    client.loop();
    vTaskDelay(10 / portTICK_PERIOD_MS);
  }
}
void setup()
{

  Serial.begin(115200); // initialize the //Serial port:

  WiFi.begin(ssid, password);

  //set up wifi connection=================================================
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
  client.setServer(mqttServer, mqttPort);

  // connect to broker
  while (!client.connected())
  {
    Serial.println("Connecting to MQTT...");
    if (client.connect("ESP32Client", mqttUser, mqttPassword))
    {
      Serial.println("connected");
    }
    else
    {
      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  //set a callback function for when data is received from broker
  client.setCallback(callback);
  // subscribe to topic
  client.subscribe("home/car/control");

  //pinsetup==================================================
  //linesensor
  pinMode(SensL, INPUT);
  pinMode(SensML, INPUT);
  pinMode(SensM, INPUT);
  pinMode(SensMR, INPUT);
  pinMode(SensR, INPUT);

  //distancesensor
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  //button
  pinMode(SkipWaitButton, INPUT_PULLUP);

  //led
  //RGB R
  pinMode(RGBLrR, OUTPUT); //D15
  pinMode(RGBLgR, OUTPUT); //D16
  pinMode(RGBLbR, OUTPUT); //D17

  //RGB L
  pinMode(RGBLrL, OUTPUT); //D2
  pinMode(RGBLgL, OUTPUT); //D14
  pinMode(RGBLbL, OUTPUT); //D18

  pinMode(LED_BUILTIN, OUTPUT);

  digitalWrite(LED_BUILTIN, HIGH);
  delay(500);
  digitalWrite(LED_BUILTIN, LOW);

  xTaskCreate(
      taskstep,   /* Task function. */
      "taskstep", /* name of task. */
      10000,      /* Stack size of task */
      NULL,       /* parameter of the task */
      1,          /* priority of the task */
      NULL);      /* Task handle to keep track of created task */

  xTaskCreate(
      SensLine,   /* Task function. */
      "SensLine", /* name of task. */
      10000,      /* Stack size of task */
      NULL,       /* parameter of the task */
      1,          /* priority of the task */
      NULL);      /* Task handle to keep track of created task */

  xTaskCreate(
      SensDistance, /* Task function. */
      "SensLine",   /* name of task. */
      10000,        /* Stack size of task */
      NULL,         /* parameter of the task */
      1,            /* priority of the task */
      NULL);        /* Task handle to keep track of created task */
  xTaskCreate(
      MQTTPublish,   /* Task function. */
      "MQTTPublish", /* name of task. */
      10000,         /* Stack size of task */
      NULL,          /* parameter of the task */
      1,             /* priority of the task */
      NULL);         /* Task handle to keep track of created task */
  xTaskCreate(
      MQTTClient,   /* Task function. */
      "MQTTClient", /* name of task. */
      10000,        /* Stack size of task */
      NULL,         /* parameter of the task */
      1,            /* priority of the task */
      NULL);        /* Task handle to keep track of created task */
  //stepperR.setMaxSpeed(StandardSpeed);
  stepperR.setAcceleration(StandardAccel);
  stepperR.moveTo((stepperR.StandardLocation));

  stepperL.setAcceleration(StandardAccel);
  stepperL.moveTo((stepperL.StandardLocation));
}

void loop()
{
  stepperR.run();
  stepperL.run();
}