# Water Quality Monitoring System

A microcontroller-based system for monitoring and categorizing water quality using multiple sensors.

## System Overview

This project implements a water quality monitoring system that uses various sensors to measure key water quality parameters and categorizes the water quality based on predefined thresholds. The system provides real-time feedback through visual indicators (LEDs) and serial communication.

### Key Features

- Continuous monitoring of multiple water quality parameters
- Real-time categorization of water quality as "Good", "Alert", or "Critical"
- Visual feedback through LED indicators
- Detailed logging of sensor readings and quality assessments
- Configurable thresholds for different water quality parameters

## Water Quality Parameters

The system monitors the following water quality parameters:

1. **pH Level**: Measures the acidity or alkalinity of water (scale 0-14)
   - Good: 6.5-8.5
   - Alert: 6.0-6.5 or 8.5-9.0
   - Critical: <6.0 or >9.0

2. **Temperature**: Measures water temperature in Celsius
   - Good: 15-25°C
   - Alert: 10-15°C or 25-30°C
   - Critical: <10°C or >30°C

3. **Turbidity**: Measures the cloudiness of water in NTU (Nephelometric Turbidity Units)
   - Good: ≤5 NTU
   - Alert: 5-10 NTU
   - Critical: >10 NTU

4. **TDS (Total Dissolved Solids)**: Measures the concentration of dissolved substances in water (ppm)
   - Good: ≤300 ppm
   - Alert: 300-500 ppm
   - Critical: >500 ppm

5. **Dissolved Oxygen**: Measures the amount of oxygen dissolved in water (mg/L)
   - Good: ≥6 mg/L
   - Alert: 4-6 mg/L
   - Critical: <4 mg/L

## Hardware Requirements

### Microcontroller
- Arduino Uno/Nano or any AVR-based microcontroller
- Minimum 5 analog input pins
- 3 digital output pins for LED indicators
- UART capability for serial communication

### Sensors

1. **pH Sensor**
   - Recommended: Atlas Scientific pH Sensor or DFRobot pH Sensor
   - Range: 0-14 pH
   - Accuracy: ±0.1 pH
   - Connection: Analog

2. **Temperature Sensor**
   - Recommended: DS18B20 Waterproof Temperature Sensor or LM35
   - Range: -10°C to 85°C
   - Accuracy: ±0.5°C
   - Connection: Analog or Digital (One-Wire for DS18B20)

3. **Turbidity Sensor**
   - Recommended: DFRobot Turbidity Sensor or Gravity Analog Turbidity Sensor
   - Range: 0-1000 NTU
   - Connection: Analog

4. **TDS Sensor**
   - Recommended: DFRobot TDS Sensor or Gravity Analog TDS Sensor
   - Range: 0-1000 ppm
   - Connection: Analog

5. **Dissolved Oxygen Sensor**
   - Recommended: Atlas Scientific Dissolved Oxygen Kit or Gravity Dissolved Oxygen Sensor
   - Range: 0-20 mg/L
   - Connection: Analog

### Other Components
- 3 LEDs (Green, Yellow, Red) for status indication
- Resistors for LEDs (typically 220Ω)
- Breadboard and jumper wires
- Power supply (5V)
- Optional: Enclosure for waterproofing

## Software Implementation

The system software is implemented in C for AVR microcontrollers. The main components are:

1. **Sensor Reading**: Functions to read and convert analog values from sensors
2. **Data Processing**: Algorithms to analyze sensor readings and categorize water quality
3. **Alert System**: Logic to trigger appropriate alerts based on water quality
4. **Communication**: UART-based serial communication for logging and monitoring

### Files
- `water_quality_monitor.c`: Simulation code for testing without hardware
- `water_quality_monitor_embedded.c`: Implementation for actual microcontroller hardware
- `water_quality_config.h`: Configuration parameters and thresholds

## Installation and Setup

### Simulation Mode
To run the simulation without actual hardware:

1. Compile the simulation code:
   ```
   gcc water_quality_monitor.c -o water_quality_monitor
   ```

2. Run the simulation:
   ```
   ./water_quality_monitor
   ```

### Hardware Implementation
To deploy on actual hardware:

1. Connect the sensors and LEDs according to the pin definitions in the code
2. Compile and upload the embedded code using avr-gcc or Arduino IDE
3. Monitor the serial output at 9600 baud rate

## Calibration

For accurate readings, sensors should be calibrated before use:

1. **pH Sensor**: Use standard pH buffer solutions (pH 4, 7, and 10)
2. **TDS Sensor**: Use a standard solution with known TDS value
3. **Turbidity Sensor**: Use distilled water (0 NTU) and a standard turbidity solution
4. **Dissolved Oxygen Sensor**: Calibrate in air (100% saturation) and zero oxygen solution

## Benefits for the Community

### Environmental Monitoring
- Early detection of water pollution
- Monitoring of water sources for safe consumption
- Protection of aquatic ecosystems

### Public Health
- Prevention of waterborne diseases
- Ensuring safe drinking water
- Alerting authorities to potential health hazards

### Educational Value
- Teaching tool for water quality concepts
- Raising awareness about water conservation
- Promoting citizen science initiatives

### Agricultural Applications
- Monitoring irrigation water quality
- Optimizing aquaculture conditions
- Preventing crop damage from poor water quality

## Future Enhancements

1. **Wireless Connectivity**: Add WiFi or LoRa capability for remote monitoring
2. **Data Logging**: Implement SD card storage for long-term data collection
3. **Mobile App**: Develop a companion app for remote monitoring and alerts
4. **Solar Power**: Add solar panels for off-grid operation
5. **Machine Learning**: Implement predictive algorithms for early warning

## License

This project is open source and available under the MIT License.

## Acknowledgments

- Water quality standards based on WHO and EPA guidelines
- Sensor calibration procedures adapted from manufacturer recommendations 
