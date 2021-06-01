# IoT Project
# Hardware
## Gebruikte hardware
### Electronica
| Item                            | Discription                                      | Price    | Qty | Extra costs | Total     |
| ------------------------------- | ------------------------------------------------ | -------- | --- | ----------- | --------- |
| Cytron Maker Line               | Simplifying Line Sensor for BeginnersSKU: 19064  |  11,95 € | 1   |             |  11,95 €  |
| Shipping Sensor                 | Shipping elektor                                 |          | 1   |  7,95 €     |  7,95 €   |
| PCB mainboard                   | PCB robot driver board                           |  0,51 €  | 1   |             |  0,51 €   |
| SHIPPING CHARGE                 | SHIPPING                                         |          | 1   |  12,63 €    |  12,63 €  |
| PAYPAL FEE                      | PAYPAL FEE                                       |          | 1   |  0,41 €     |  0,41 €   |
| DRV8825 driver                  | DSD00010 \_Stepstick DRV8825 drive with heatsink |  5,00 €  | 2   |             |  10,00 €  |
| Inbusstelschroef M4x5           | DBM00194 \_Inbusstelschroef M4x5 (10 stuks)      |  2,30 €  | 1   |             |  2,30 €   |
| Verzend- en administratiekosten | Verzend- en administratiekosten 123-3D.nl        |          | 1   |  5,95 €     |  5,95 €   |
| Lipo Battery                    | Yuki Kryptonium 3S 11.1V 30C 5000mAh LiPo 801323 |  45,99 € | 1   |             |  45,99 €  |
| Step-Down Buck Converter        | DEBO DCDC DOWN 4 (mini 360)                      |  2,02 €  | 1   |             |  2,02 €   |
| Dupont kit                      | Dupont connector kit                             |  5,00 €  | 1   |             |  5,00 €   |
| Fuse holder                     | fuse holder                                      |  0,30 €  | 1   |             |  0,30 €   |
| Fuse                            | fuse 2A                                          |  0,20 €  | 1   |             |  0,20 €   |
| RGB led                         | RGB common cathode                               |  1,03 €  | 2   |             |  2,06 €   |
| 3mm led                         | 3mm led red                                      |  0,05 €  | 2   |             |  0,10 €   |
| Resistors                       | resistors various values                         |  0,02 €  | 8   |             |  0,13 €   |
| HC-SR04                         | HC-SR04 Ultrasonic sensor – afstandsmeter        |  3,00 €  | 1   |             |  3,00 €   |
| capacator                       | capacator                                        |  0,11 €  | 2   |             |  0,22 €   |
| 3D print                        | 3d prints materiaal+manafacturing                |  20,00 € | 1   |             |  20,00 €  |
| Lasercut frame                  | laserkcut frame matriaal+manafacturing           |  20,00 € | 1   |             |  20,00 €  |
| Stepper motor                   | JK42HS34-1334                                    |  13,00 € | 2   |             |  26,00 €  |
| Hardware                        | varous nuts and bolts                            |  15,00 € | 1   |             |  15,00 €  |
| Knikkers                        | knikkers                                         |  0,20 €  | 2   |             |  0,40 €   |
|                                 |                                                  |          |     |             |  192,12 € |
#### Cytron Maker-Line

![maker-line-free-view-800x800](https://github.com/The-Game-Breaker/IoT-Line-Follower-with-MQTT/blob/1b5d61187aa5f58dd6a5a0e12d0cc4ccf19bd0ce/Pictures/Electronics/maker-line-free-view-800x800.jpg)



De Cytron Maker-Line is een ir sensor array voorzien van 5 sensoren die de lijn uitlezen. Op basis van deze output sturen we de motoren aan. Deze module geeft ook nog wat extra &quot;creature-comforts&quot;, zo is de array gemakkelijk te kalibreren en kan deze &quot;geswitchted&quot; worden tussen een donkere of lichte lijn.

#### HC-SR04

![](https://github.com/The-Game-Breaker/IoT-Line-Follower-with-MQTT/blob/1b5d61187aa5f58dd6a5a0e12d0cc4ccf19bd0ce/Pictures/Electronics/HC-SR04.png)

De HC-SR04 is een ultrasone sensor. Deze moet ervoor zorgen dat het wagentje nergens tegenaan rijdt. Dit wordt tot stand gebracht met ultrasone echolocatie.

#### Joy-IT Esp32
 ![](https://github.com/The-Game-Breaker/IoT-Line-Follower-with-MQTT/blob/1b5d61187aa5f58dd6a5a0e12d0cc4ccf19bd0ce/Pictures/Electronics/SBC-NodeMCU-ESP32-01.png)

Het brein van het project wordt de ESP32 van JOY-IT. Deze zal alle in- en outputs aansturen en data communiceren via wifi.

### nema17 stepper motor

![](https://github.com/The-Game-Breaker/IoT-Line-Follower-with-MQTT/blob/1b5d61187aa5f58dd6a5a0e12d0cc4ccf19bd0ce/Pictures/Electronics/1128966276.jpg)

Deze JK42HS34-1334 NEMA 17 stepper motoren worden gebruikt om het wagentje aan te drijven. Hoewel niet de ideale keuze, bieden ze toch enige flexibiliteit ten opzichte van andere oplossingen. Een andere factor voor deze keuze was dat ik deze nog had liggen en ik er graag eens mee wilde werken.

#### DRV8825 stepper motor driver

![](https://github.com/The-Game-Breaker/IoT-Line-Follower-with-MQTT/blob/1b5d61187aa5f58dd6a5a0e12d0cc4ccf19bd0ce/Pictures/Electronics/drv8825-stepper-motor-driver-carrier-high-current_2021-May-03_12-38-49PM-000_CustomizedView1389151965.png)

De DRV8825 wordt gebruikt om de NEMA 17 motoren aan te sturen. Niet alleen biedt deze driver een hogere ampère levering, de microsteps kunnen ook makkelijk worden ingesteld

#### RGB LED 5mm

![](https://github.com/The-Game-Breaker/IoT-Line-Follower-with-MQTT/blob/1b5d61187aa5f58dd6a5a0e12d0cc4ccf19bd0ce/Pictures/Electronics/00105-LED_-_RGB_Clear_Common_Cathode-01.jpg)

Deze led wordt gebruikt als indicator voor de status van het wagentje.

Deze statussen zijn:

- Rood: Het wagentje is de lijn kwijt
- Groen: Het wagentje volgt de lijn en geeft aan naar welke kant er wordt gedraaid
- Blauw: Het wagentje stopt voor een obstakel. Dit kan een blokkade of een dwarslijn zijn.

### Schema, PCB
####

Het onderstaand schema geeft de beschreven componenten systematisch weer.

![](https://github.com/The-Game-Breaker/IoT-Line-Follower-with-MQTT/blob/7425e42e2120c3c31c337d58775391b7ac27582b/Pictures/Schematic.png) 
![](https://github.com/The-Game-Breaker/IoT-Line-Follower-with-MQTT/blob/1b5d61187aa5f58dd6a5a0e12d0cc4ccf19bd0ce/Pictures/Electronics/Schematic%20IOT%20Project.png)
### Hardware, andere componenten
#### Chassis

![](https://github.com/The-Game-Breaker/IoT-Line-Follower-with-MQTT/blob/1b5d61187aa5f58dd6a5a0e12d0cc4ccf19bd0ce/Pictures/Frame_2021-May-27_02-28-49PM-000_CustomizedView14686761149.png)

Het chassis bestaat uit een eigen ontwerp vervaardigd uit plexiglas en 3D-geprinte (r)PETG-onderdelen. Deze zijn aan elkaar verbonden met M3, M4 en M5 bouten en moeren uit RVS.
#### Wielen

Er zijn 2 wielen voorzien die instaan voor de aandrijving en sturing van het wagentje. Deze komen oorspronkelijk van een RC-auto. Ook zijn er 2 kogelwieltjes voorzien om het wagentje stabiel te houden.
# Code
## Overview
Programmatie werd geschreven in Visual Studio Code met platformio. Dit geeft een aantal voordelen qua debuggen en foutcontrole maar brengt ook een aantal challenges met zich mee. De code wordt opgedeeld in verschillende onderdelen.

### Setup: includes, definities, integers, etc.

Eerst vinden we een sectie met declaraties en setup voor de verschillende onderdelen van het wagentje. Ook vinden we enkele &quot;macro&#39;s&quot;; deze worden gebruikt om de code en functies later leesbaarder te houden.

### Functies
Vervolgens vinden we een sectie waarin de functies zijn geschreven. Deze worden later opgevraagd door de verschillende taken of andere functies.

### Taken

Onder de functies vinden we een sectie met &quot;Tasks&quot;. Hier worden de functies gedeclareerd die later door de ESP&#39;s FreeRTOS zullen worden opgevraagd.

### Setup en Loop

Tot slot vinden we de sectie setup, hier worden de pinnen gedeclareerd en geïnitialiseerd, ook de taken worden hier toegevoegd. De loop-functie wordt in praktijk niet gebruikt in dit geval.

## FreeRTOS

In de programmatie ben ik voor een systeem gegaan met FreeRTOS in plaats van een meer traditioneel systeem. Ik heb hiervoor gekozen omdat dit het gemakkelijk en efficiënt maakt om te multitasken. Het zorgt er ook voor dat in de toekomst uitbreidingen makkelijk mogelijk zijn.

FreeRTOS werkt een beetje als een scheduler, enkel is deze ingebouwd in de ESP en vraagt dus geen extra libraries. Tevens biedt de RTOS ook een uitgebreid pakket aan opties. Zo kan je bijvoorbeeld een bepaalde taak aan een bepaalde &quot;core&quot; toewijzen en zo &quot;echte&quot; synchrone taken uitvoeren.

## Case system

| Case nr. | Sensors | L | ML | M | MR | R | Dist |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 1 | ExtremeLeft | ON | OFF | OFF | OFF | OFF | OFF |
| 2 | HardLeft | ON | ON | OFF | OFF | OFF | OFF |
| 3 | MediumLeft | OFF | ON | OFF | OFF | OFF | OFF |
| 4 | SoftLeft | OFF | ON | ON | OFF | OFF | OFF |
| 5 | Strait | OFF | OFF | ON | OFF | OFF | OFF |
| 6 | SoftRight | OFF | OFF | ON | ON | OFF | OFF |
| 7 | MediumRight | OFF | OFF | OFF | ON | OFF | OFF |
| 8 | HardRight | OFF | OFF | OFF | ON | ON | OFF |
| 9 | ExtremeRight | OFF | OFF | OFF | OFF | ON | OFF |
| 10 | CrossLine | ON | ON | ON | ON | ON | OFF |
| 11 | LOSTLine | OFF | OFF | OFF | OFF | OFF | OFF |
| 12 | Objectdetect | OFF | OFF | OFF | OFF | OFF | ON |

In de programmatie test de microcontroller de sensorwaarde voor verschillende cases. Aan de hand van deze waarde wordt er een &quot;casenummer&quot; gegeven. Deze kan dan worden opgevraagd door een andere taak, in dit geval de motor sturing taak (taskstep).
![](RackMultipart20210601-4-1wbuym5_html_b8db10d83fbda782.png
## Wifi en MQTT

De ESP is voorzien van een &quot;library&quot; waarmee hij via wifi met een mqtt server kan verbinden. Deze kan zowel &quot;subscriben&quot; als &quot;publishen&quot;. Zo kan hij communiceren met de node red server.
![](https://github.com/The-Game-Breaker/IoT-Line-Follower-with-MQTT/blob/1b5d61187aa5f58dd6a5a0e12d0cc4ccf19bd0ce/Pictures/Schermafbeelding%202021-05-30%20210434.png)
![](https://github.com/The-Game-Breaker/IoT-Line-Follower-with-MQTT/blob/1b5d61187aa5f58dd6a5a0e12d0cc4ccf19bd0ce/Pictures/Schermafbeelding%202021-05-30%20211912.png)
# Tutorial

## Prerequisites

Tijdens de tutorial wordt ervan uitgegaan dat er kennis is van volgende elementen:

- Elektronica
- Mechanica
- ESP32 en software
- MQTT
- Node Red
- Netwerken

## Stap 1: Acquiring hardware

De eerste stap om het wagentje te bouwen is natuurlijk alle hardware en elektronica aan te kopen. Deze onderdelen werden eerder in dit document beschreven onder het deel hardware en zijn ook terug te vinden in de BOM.

## Stap 2: Assemblage

Nadat alle onderdelen zijn aangekomen, kunnen we beginnen met de assemblage van de wagentjes.

### Bodem frame

Bevestig de motor houders, zwenkwieltjes en batterijhouder aan het bodem frame met de bijhorende bouten, moeren en rondellen.

### Midden frame

Bevestig de stapper motoren in de motorhouders. Installeer de &quot;support poles&quot; op de bodemplaat. Installeer ook de bumper met line sensor.

### Boven frame

Installeer het boven frame op de &quot;support poles&quot; en bevestig deze. Installeer vervolgens de mounting bracket voor de afstandssenor.

### PCB

Soldeer alle componenten op de PCB behalve de motorkabels.

### Elektronica bevestigen

Bevestig de servo op het mounting bracket. Neem de afstand sensor en installeer deze op het bovendeel van het mounting bracket en installeer het geheel vervolgens op de servomotor. Bevestig vervolgens de pcb met de bijhorende bouten, moeren en &quot;standoffs&quot; op het boven frame.

### Afmontage Elektronica

Tot slot worden alle kabels getrokken en verbonden met de bijhorende onderdelen volgens onderstaand schema.

![](https://github.com/The-Game-Breaker/IoT-Line-Follower-with-MQTT/blob/7425e42e2120c3c31c337d58775391b7ac27582b/Pictures/Schematic.png)

## Stap 3: MQTT and node red

Installeer een MQTT en Node Red server. Hierbij kan gebruik gemaakt worden van een raspberry pi.

Installeer de node-red flow voor de wagensturing.

## Stap 4: Programmatie ESP32

Nu we een MQTT-server hebben, moeten we de ESP32 programmeren. Vergeet niet voor het programmeren de code aan te passen aan de huidige situatie (wifi ssid, password, etc.). Programmeer vervolgens ESP.

## Stap 5 Aanleggen van het parcours

Het aanleggen van het parcours kan simpelweg worden gedaan door het trekken van een zwarte lijn op lichte grond of witte lijn op donkere grond. Vervolgens kunnen er dwarslijnen voorzien worden om het wagentje te stoppen op de &quot;points of intrest&quot;.

## Stap 6 Tewerkstelling

Tot slot kunnen de wagentjes in werking worden gesteld. Door deze op de lijn te plaatsen en de batterij in te steken.

# Resources

[https://grabcad.com/library/esp-wroom-32-2](https://grabcad.com/library/esp-wroom-32-2)

[https://www.cytron.io/p-maker-line-simplifying-line-sensor-for-beginner](https://www.cytron.io/p-maker-line-simplifying-line-sensor-for-beginner)

[https://www.jkongmotor.com/product/42HS-NEMA17-2Phase-Stepper-Motor-1-8%C2%B0.html](https://www.jkongmotor.com/product/42HS-NEMA17-2Phase-Stepper-Motor-1-8%C2%B0.html)

[https://www.thingiverse.com/thing:4275668/files](https://www.thingiverse.com/thing:4275668/files)

[https://www.makerguides.com/wp-content/uploads/2019/02/DRV8825-Arduino-stepper-motor-wiring-schematic-diagram-pinout\_bb-1024x551.jpg](https://www.makerguides.com/wp-content/uploads/2019/02/DRV8825-Arduino-stepper-motor-wiring-schematic-diagram-pinout_bb-1024x551.jpg)

[https://www.makerguides.com/drv8825-stepper-motor-driver-arduino-tutorial/](https://www.makerguides.com/drv8825-stepper-motor-driver-arduino-tutorial/)

[https://github.com/suzakulab/Eagle-Library-Pololu](https://github.com/suzakulab/Eagle-Library-Pololu)

[https://www.diymodules.org/eagle-show-object?type=dm&amp;file=diy-modules.lbr&amp;device=DC-DC-STEP-DOWN-MP2307](https://www.diymodules.org/eagle-show-object?type=dm&amp;file=diy-modules.lbr&amp;device=DC-DC-STEP-DOWN-MP2307)

[https://www.airspayce.com/mikem/arduino/AccelStepper/index.html](https://www.airspayce.com/mikem/arduino/AccelStepper/index.html)

[https://www.microchip.com/wwwproducts/en/MCP23016](https://www.microchip.com/wwwproducts/en/MCP23016)

[https://www.instructables.com/IO-Expander-for-ESP32-ESP8266-and-Arduino/](https://www.instructables.com/IO-Expander-for-ESP32-ESP8266-and-Arduino/)

[https://github.com/arkhipenko/TaskScheduler](https://github.com/arkhipenko/TaskScheduler)

[https://ozh.github.io/ascii-tables/](https://ozh.github.io/ascii-tables/)

[https://www.studiopieters.nl/esp32-pinout/](https://www.studiopieters.nl/esp32-pinout/)

[https://flows.nodered.org/node/node-red-dashboard](https://flows.nodered.org/node/node-red-dashboard)

#Colors:

##004146 RGB (0,65,70)

##018076 RGB (1,128,118)

##03BFB5 RGB (3,191,181)

##949398 RGB (148,147,152)

##EFF5F9 RGB (239,245,249)
