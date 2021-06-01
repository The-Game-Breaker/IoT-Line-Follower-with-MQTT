![](RackMultipart20210601-4-1kw6d5y_html_dd3f474d46c70f69.gif)

1/06/2021

Nathan Laureyn

# IoT Project
# Hardware
## Gebruikte hardware
### Electronica

- Cytron Maker-Line
- HC-SR04
- Joy-IT Esp32 (30pin)
- JK42HS34-1334 nema17 stepper motor
- DRV8825 stepper motor driver
- RGB LED 5mm
- 100uF Capacitor
- Resistors

#### Cytron Maker-Line

![](RackMultipart20210601-4-1kw6d5y_html_6a9bcf01c80f6a5d.jpg)

De Cytron Maker-Line is een ir sensor array voorzien van 5 sensoren die de lijn uitleest. Op basis van deze outputs sturen we de motoren aan. Deze module geeft ook nog wat extra &quot;creature-comforts&quot;, zo is de array gemakkelijk te kalibreren en kan deze &quot;geswitchted&quot; worden tussen een donkere of lichte lijn.
#### HC-SR04

![](RackMultipart20210601-4-1kw6d5y_html_8ae682bc43a1865.png)

De HC-SR04 is een ultrasone sensor. Deze moet ervoor zorgen dat het wagentje nergens tegenaan rijdt. Dit wordt tot stand gebracht met ultrasone echolocatie.

#### Joy-IT Esp32

#### ![](RackMultipart20210601-4-1kw6d5y_html_87042e1e054a947b.png)

Het brein van het project wordt de ESP32 van JOY-IT. Deze zal alle in- en outputs aansturen en data communiceren via wifi.

### nema17 stepper motor

![](RackMultipart20210601-4-1kw6d5y_html_f59dacc554e6251e.jpg)

Deze JK42HS34-1334 NEMA 17 stepper motoren worden gebruikt om het wagentje aan te drijven. Hoewel niet de ideale keuze, bieden ze toch enige flexibiliteit ten opzichte van andere oplossingen.

#### DRV8825 stepper motor driver
#### ![](RackMultipart20210601-4-1kw6d5y_html_9bcb30b5d340ae4f.png)

De DRV8825 wordt gebruikt om de NEMA 17 motoren aan te sturen. Niet alleen biedt deze driver een hogere amperage levering, de microsteps kunnen ook makkelijk worden ingesteld
#### RGB LED 5mm

![](RackMultipart20210601-4-1kw6d5y_html_8c0bb24e140eb531.jpg)

Deze led wordt gebruikt als indicator voor de status van het wagentje.

### Schema, PCB
Het onderstaand schema geeft de beschreven componenten, systematisch weer

![](RackMultipart20210601-4-1kw6d5y_html_677e8a5817ca8857.png) ![](RackMultipart20210601-4-1kw6d5y_html_5589f51cd4bf9820.png)

### Hardware, andere componenten
#### Chassis

![](RackMultipart20210601-4-1kw6d5y_html_e47d017b08f810b6.png)

Het chassis bestaat uit een eigen ontwerp vervaardigd uit plexiglas en 3D geprinte (r)PETG onderdelen. Deze zijn aan elkaar verbonden met M3, M4 en M5 bouten en moeren uit RVS.
#### Wielen

Er zijn 2 wielen voorzien die instaan voor de aandrijving en sturing van het wagentje. Deze komen oorspronkelijk van een RC auto Ook zijn er 2 kogel wieltjes voorzien om het wagentje stabiel te houden.
# Code
## Overview

Programmatie werd geschreven in Visual Studio Code met platformio dit brengt een aantal voordelen qua debuggen en foutcontrole maar brengt ook een aantal challenges met zich me. De code word opgedeeld in verschillende onderdelen.

### Setup: includes, definities, integers, etc

Eerst vinden een sectie met declaraties en setup voor de verschillende onderdelen van het wagentje. Ook vinden we enkele &quot;macro&#39;s&quot; deze worden gebruikt om de code en functies later leesbaarder te houden.
### Functies
Vervolgens vinden we een sectie waarin de functies zijn geschreven. Deze worden later opgevraagd door de verschillende taken of andere functies.
### Taken
Onder de functies vinden we een sectie met &quot;Tasks&quot; Hier worden de functies gedeclareerd die later door de ESP&#39;s FreeRTOS zullen worden opgevraagd.
### Setup en Loop
Tot Slot vinden we de sectie setup, hier worden de pinnen gedeclareerd en geinisialiseert, ook de taken worden hier toegevoegd. De loop functie word in praktijk niet gebruikt in dit geval.
## FreeRTOS
In de programmatie ben ik voor een systeem gegaan met FreeRTOS in de plaats vaneen meer traditioneel systeem. Ik heb hiervoor gekozen omdat het gemakkelijk en efficiënt maakt om te multitasking, het zorgt er ook voor dat in de toekomst uitbreidingen makkelijk mogelijk zijn.

FreeRTOS werkt een beetje als een scheduler enkel is deze ingebouwd in de ESP en vraagt dus geen extra libraries. Tevens bied de RTOS ook een uitgebreid pakket aan opties zo kan je bijvoorbeeld een bepaalde taak aan een bepaalde &quot;core&quot; toewijzen en zo &quot;echte&quot; syncrone taken uitvoeren.
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

In de programmatie test de microcontroller de sensorwaarde voor verschillende cases. Aan de hand van deze waarde word er een &quot;case nummer&quot; gegeven deze kan dan worden opgevraagd door een andere taak in dit geval de motor sturing taak (taskstep).

![](RackMultipart20210601-4-1kw6d5y_html_b8db10d83fbda782.png)

# Tutorial
## Stap 1: Acquiring hardware

De eerste stap om het wagentje te bouwen is natuurlijk alle hardware en elektronica aan te kopen.
## Stap 2: Assemblage

Nadat alle onderdelen zijn aangekomen kunnen we beginne met de assemblage van de wagentjes.
## Stap 3: MQTT and node red

Installeer een MQTT en Node Red server. Hierbij kan gebruik gemaakt worden van een raspberry pi.

Installeer de node-red flow voor de wagensturing.
## Stap 4: Programmatie ESP32

Nu we een MQTT server hebben moeten we de ESP32 programmeren. Vergeet niet voor het programmeren de code aan te passen aan de huidige situatie (wifi ssid, passwoord, etc). Programeer vervolgens ESP.
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

Colors:

#004146 RGB(0,65,70)

#018076 RGB(1,128,118)

#03BFB5 RGB(3,191,181)

#949398 RGB(148,147,152)

#EFF5F9 RGB(239,245,249)

![](RackMultipart20210601-4-1kw6d5y_html_f2e24614f57b2a80.gif)
