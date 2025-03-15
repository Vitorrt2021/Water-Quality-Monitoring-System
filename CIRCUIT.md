# Circuit Diagram for Water Quality Monitoring System

This document provides instructions for connecting the sensors and components for the water quality monitoring system.

## Component Connections

### Microcontroller (Arduino Uno/Nano)

The system uses an Arduino or similar AVR-based microcontroller with the following connections:

### Power Connections
- VCC: Connect to 5V
- GND: Connect to ground

### Sensor Connections

#### pH Sensor
- VCC: Connect to Arduino 5V
- GND: Connect to Arduino GND
- Signal: Connect to Arduino Analog Pin A0 (defined as PH_SENSOR_PIN in code)

#### Temperature Sensor (LM35)
- VCC: Connect to Arduino 5V
- GND: Connect to Arduino GND
- Signal: Connect to Arduino Analog Pin A1 (defined as TEMPERATURE_SENSOR_PIN in code)

#### Turbidity Sensor
- VCC: Connect to Arduino 5V
- GND: Connect to Arduino GND
- Signal: Connect to Arduino Analog Pin A2 (defined as TURBIDITY_SENSOR_PIN in code)

#### TDS Sensor
- VCC: Connect to Arduino 5V
- GND: Connect to Arduino GND
- Signal: Connect to Arduino Analog Pin A3 (defined as TDS_SENSOR_PIN in code)

#### Dissolved Oxygen Sensor
- VCC: Connect to Arduino 5V
- GND: Connect to Arduino GND
- Signal: Connect to Arduino Analog Pin A4 (defined as DO_SENSOR_PIN in code)

### LED Indicators

#### Green LED (Good Water Quality)
- Anode (+): Connect to Arduino Digital Pin 11 (defined as GREEN_LED_PIN in code) through a 220Ω resistor
- Cathode (-): Connect to Arduino GND

#### Yellow LED (Alert Water Quality)
- Anode (+): Connect to Arduino Digital Pin 10 (defined as YELLOW_LED_PIN in code) through a 220Ω resistor
- Cathode (-): Connect to Arduino GND

#### Red LED (Critical Water Quality)
- Anode (+): Connect to Arduino Digital Pin 9 (defined as RED_LED_PIN in code) through a 220Ω resistor
- Cathode (-): Connect to Arduino GND

## Schematic Representation (ASCII)

```
                                  +---------------------+
                                  |                     |
                                  |    Arduino Uno      |
                                  |                     |
+-------------+                   |                     |
| pH Sensor   |---VCC------------+| 5V                 |
|             |---GND------------+| GND                |
|             |---Signal---------+| A0                 |
+-------------+                   |                     |
                                  |                     |
+-------------+                   |                     |
| Temperature |---VCC------------+| 5V                 |
| Sensor      |---GND------------+| GND                |
|             |---Signal---------+| A1                 |
+-------------+                   |                     |
                                  |                     |
+-------------+                   |                     |
| Turbidity   |---VCC------------+| 5V                 |
| Sensor      |---GND------------+| GND                |
|             |---Signal---------+| A2                 |
+-------------+                   |                     |
                                  |                     |
+-------------+                   |                     |
| TDS Sensor  |---VCC------------+| 5V                 |
|             |---GND------------+| GND                |
|             |---Signal---------+| A3                 |
+-------------+                   |                     |
                                  |                     |
+-------------+                   |                     |
| Dissolved   |---VCC------------+| 5V                 |
| Oxygen      |---GND------------+| GND                |
| Sensor      |---Signal---------+| A4                 |
+-------------+                   |                     |
                                  |                     |
                                  |                     |
                   +--220Ω--+    |                     |
Green LED --------+         +----| D11                |
                                  |                     |
                   +--220Ω--+    |                     |
Yellow LED --------+         +----| D10                |
                                  |                     |
                   +--220Ω--+    |                     |
Red LED -----------+         +----| D9                 |
                                  |                     |
                                  +---------------------+
```

## Notes on Sensor Installation

1. **pH Sensor**: The pH probe should be immersed in water but not touching the bottom or sides of the container. Keep the probe clean and calibrate regularly.

2. **Temperature Sensor**: The waterproof version of DS18B20 can be fully immersed. If using LM35, ensure only the sensing part is in water and the electronics remain dry.

3. **Turbidity Sensor**: Position the sensor so that water flows through the sensing area. Avoid air bubbles which can affect readings.

4. **TDS Sensor**: The probe should be fully immersed in water. Ensure there are no air bubbles on the sensing surface.

5. **Dissolved Oxygen Sensor**: The membrane must be fully submerged but not touching any surfaces. Keep the membrane clean and replace as recommended by the manufacturer.

## Waterproofing Considerations

For outdoor or long-term installations:

1. Place the microcontroller and non-waterproof components in a waterproof enclosure
2. Use waterproof connectors for all sensor cables
3. Apply silicone sealant around cable entry points
4. Consider using conformal coating on circuit boards for additional protection

## Power Considerations

The system can be powered via:

1. USB connection to a computer
2. 9V battery connected to the Arduino's power jack
3. 5V regulated power supply connected to the 5V and GND pins
4. Solar panel with appropriate voltage regulation for off-grid applications 