/**
 * Water Quality Monitoring System - Embedded Implementation
 * 
 * This program is designed to run on a microcontroller to read water quality sensors
 * and categorize water quality based on predefined thresholds.
 * 
 * Target hardware: Arduino/AVR microcontroller
 */

 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include <util/delay.h>
 #include <stdio.h>
 #include <stdlib.h>
 #include "water_quality_config.h"
 
 // Pin definitions
 #define PH_SENSOR_PIN          0  // Analog pin A0
 #define TEMPERATURE_SENSOR_PIN 1  // Analog pin A1
 #define TURBIDITY_SENSOR_PIN   2  // Analog pin A2
 #define TDS_SENSOR_PIN         3  // Analog pin A3
 #define DO_SENSOR_PIN          4  // Analog pin A4
 
 #define RED_LED_PIN            9  // Digital pin for red LED (critical)
 #define YELLOW_LED_PIN         10 // Digital pin for yellow LED (alert)
 #define GREEN_LED_PIN          11 // Digital pin for green LED (good)
 
 // Function prototypes
 void initialize_system(void);
 void initialize_adc(void);
 void initialize_uart(void);
 uint16_t read_adc(uint8_t channel);
 float read_ph_sensor(void);
 float read_temperature_sensor(void);
 float read_turbidity_sensor(void);
 float read_tds_sensor(void);
 float read_dissolved_oxygen_sensor(void);
 void analyze_water_quality(float ph, float temperature, float turbidity, float tds, float dissolved_oxygen);
 const char* get_quality_category(int quality_level);
 void display_sensor_readings(float ph, float temperature, float turbidity, float tds, float dissolved_oxygen);
 void set_alert_leds(int quality_level);
 void uart_transmit(unsigned char data);
 void uart_print_string(const char* str);
 void uart_print_float(float value, uint8_t decimal_places);
 
 int main(void) {
     // Initialize the system
     initialize_system();
     
     // Main monitoring loop
     while (1) {
         // Read from sensors
         float ph = read_ph_sensor();
         float temperature = read_temperature_sensor();
         float turbidity = read_turbidity_sensor();
         float tds = read_tds_sensor();
         float dissolved_oxygen = read_dissolved_oxygen_sensor();
         
         // Display current sensor readings via UART
         display_sensor_readings(ph, temperature, turbidity, tds, dissolved_oxygen);
         
         // Analyze water quality and trigger alerts if necessary
         analyze_water_quality(ph, temperature, turbidity, tds, dissolved_oxygen);
         
         // Delay between readings
         uart_print_string("\nWaiting for next reading...\n");
         uart_print_string("------------------------------------------------------\n\n");
         
         // Delay for READING_INTERVAL seconds
         for (uint8_t i = 0; i < READING_INTERVAL; i++) {
             _delay_ms(1000);  // 1 second delay
         }
     }
     
     return 0;  // Never reached
 }
 
 void initialize_system(void) {
     // Set up LED pins as outputs
     DDRB |= (1 << RED_LED_PIN) | (1 << YELLOW_LED_PIN) | (1 << GREEN_LED_PIN);
     
     // Initialize ADC for sensor readings
     initialize_adc();
     
     // Initialize UART for communication
     initialize_uart();
     
     // Enable global interrupts
     sei();
     
     // Send startup message
     uart_print_string("------------------------------------------------------\n");
     uart_print_string("      WATER QUALITY MONITORING SYSTEM INITIALIZED     \n");
     uart_print_string("------------------------------------------------------\n");
     uart_print_string("System ready! Beginning continuous monitoring.\n\n");
 }
 
 void initialize_adc(void) {
     // Set ADC reference voltage to AVCC
     ADMUX = (1 << REFS0);
     
     // Enable ADC and set prescaler to 128 (16MHz/128 = 125kHz)
     ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
 }
 
 void initialize_uart(void) {
     // Set baud rate to 9600 bps for 16MHz clock
     UBRR0H = 0;
     UBRR0L = 103;
     
     // Enable transmitter
     UCSR0B = (1 << TXEN0);
     
     // Set frame format: 8 data bits, 1 stop bit, no parity
     UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
 }
 
 uint16_t read_adc(uint8_t channel) {
     // Select ADC channel
     ADMUX = (ADMUX & 0xF0) | (channel & 0x0F);
     
     // Start conversion
     ADCSRA |= (1 << ADSC);
     
     // Wait for conversion to complete
     while (ADCSRA & (1 << ADSC));
     
     // Return ADC value
     return ADC;
 }
 
 float read_ph_sensor(void) {
     // Read raw ADC value
     uint16_t adc_value = read_adc(PH_SENSOR_PIN);
     
     // Convert ADC value to pH (this conversion depends on the specific sensor)
     // For example, if using a pH sensor with range 0-14 pH mapped to 0-1023 ADC:
     float ph = (float)adc_value * 14.0 / 1023.0;
     
     return ph;
 }
 
 float read_temperature_sensor(void) {
     // Read raw ADC value
     uint16_t adc_value = read_adc(TEMPERATURE_SENSOR_PIN);
     
     // Convert ADC value to temperature (this conversion depends on the specific sensor)
     // For example, if using an LM35 temperature sensor (10mV/°C):
     // 0-1023 ADC maps to 0-5V, and each 10mV is 1°C
     float temperature = (float)adc_value * 5.0 * 100.0 / 1023.0;
     
     return temperature;
 }
 
 float read_turbidity_sensor(void) {
     // Read raw ADC value
     uint16_t adc_value = read_adc(TURBIDITY_SENSOR_PIN);
     
     // Convert ADC value to turbidity (this conversion depends on the specific sensor)
     // For example, if using a turbidity sensor with range 0-100 NTU mapped to 0-1023 ADC:
     float turbidity = (float)adc_value * 100.0 / 1023.0;
     
     return turbidity;
 }
 
 float read_tds_sensor(void) {
     // Read raw ADC value
     uint16_t adc_value = read_adc(TDS_SENSOR_PIN);
     
     // Convert ADC value to TDS (this conversion depends on the specific sensor)
     // For example, if using a TDS sensor with range 0-1000 ppm mapped to 0-1023 ADC:
     float tds = (float)adc_value * 1000.0 / 1023.0;
     
     return tds;
 }
 
 float read_dissolved_oxygen_sensor(void) {
     // Read raw ADC value
     uint16_t adc_value = read_adc(DO_SENSOR_PIN);
     
     // Convert ADC value to dissolved oxygen (this conversion depends on the specific sensor)
     // For example, if using a DO sensor with range 0-20 mg/L mapped to 0-1023 ADC:
     float dissolved_oxygen = (float)adc_value * 20.0 / 1023.0;
     
     return dissolved_oxygen;
 }
 
 void display_sensor_readings(float ph, float temperature, float turbidity, float tds, float dissolved_oxygen) {
     uart_print_string("Current Sensor Readings:\n");
     
     uart_print_string("pH: ");
     uart_print_float(ph, 2);
     uart_print_string("\n");
     
     uart_print_string("Temperature: ");
     uart_print_float(temperature, 2);
     uart_print_string(" °C\n");
     
     uart_print_string("Turbidity: ");
     uart_print_float(turbidity, 2);
     uart_print_string(" NTU\n");
     
     uart_print_string("TDS: ");
     uart_print_float(tds, 2);
     uart_print_string(" ppm\n");
     
     uart_print_string("Dissolved Oxygen: ");
     uart_print_float(dissolved_oxygen, 2);
     uart_print_string(" mg/L\n\n");
 }
 
 void analyze_water_quality(float ph, float temperature, float turbidity, float tds, float dissolved_oxygen) {
     int ph_quality = 0;
     int temp_quality = 0;
     int turbidity_quality = 0;
     int tds_quality = 0;
     int do_quality = 0;
     
     // Analyze pH
     if (ph >= PH_GOOD_MIN && ph <= PH_GOOD_MAX) {
         ph_quality = QUALITY_GOOD;
     } else if ((ph >= PH_ALERT_MIN && ph < PH_GOOD_MIN) || (ph > PH_GOOD_MAX && ph <= PH_ALERT_MAX)) {
         ph_quality = QUALITY_ALERT;
     } else {
         ph_quality = QUALITY_CRITICAL;
     }
     
     // Analyze temperature
     if (temperature >= TEMP_GOOD_MIN && temperature <= TEMP_GOOD_MAX) {
         temp_quality = QUALITY_GOOD;
     } else if ((temperature >= TEMP_ALERT_MIN && temperature < TEMP_GOOD_MIN) || 
                (temperature > TEMP_GOOD_MAX && temperature <= TEMP_ALERT_MAX)) {
         temp_quality = QUALITY_ALERT;
     } else {
         temp_quality = QUALITY_CRITICAL;
     }
     
     // Analyze turbidity
     if (turbidity <= TURBIDITY_GOOD) {
         turbidity_quality = QUALITY_GOOD;
     } else if (turbidity <= TURBIDITY_ALERT) {
         turbidity_quality = QUALITY_ALERT;
     } else {
         turbidity_quality = QUALITY_CRITICAL;
     }
     
     // Analyze TDS
     if (tds <= TDS_GOOD) {
         tds_quality = QUALITY_GOOD;
     } else if (tds <= TDS_ALERT) {
         tds_quality = QUALITY_ALERT;
     } else {
         tds_quality = QUALITY_CRITICAL;
     }
     
     // Analyze dissolved oxygen
     if (dissolved_oxygen >= DO_GOOD) {
         do_quality = QUALITY_GOOD;
     } else if (dissolved_oxygen >= DO_ALERT) {
         do_quality = QUALITY_ALERT;
     } else {
         do_quality = QUALITY_CRITICAL;
     }
     
     // Display quality analysis
     uart_print_string("Water Quality Analysis:\n");
     
     uart_print_string("pH: ");
     uart_print_string(get_quality_category(ph_quality));
     uart_print_string("\n");
     
     uart_print_string("Temperature: ");
     uart_print_string(get_quality_category(temp_quality));
     uart_print_string("\n");
     
     uart_print_string("Turbidity: ");
     uart_print_string(get_quality_category(turbidity_quality));
     uart_print_string("\n");
     
     uart_print_string("TDS: ");
     uart_print_string(get_quality_category(tds_quality));
     uart_print_string("\n");
     
     uart_print_string("Dissolved Oxygen: ");
     uart_print_string(get_quality_category(do_quality));
     uart_print_string("\n");
     
     // Determine overall water quality (worst case)
     int overall_quality = ph_quality;
     if (temp_quality > overall_quality) overall_quality = temp_quality;
     if (turbidity_quality > overall_quality) overall_quality = turbidity_quality;
     if (tds_quality > overall_quality) overall_quality = tds_quality;
     if (do_quality > overall_quality) overall_quality = do_quality;
     
     uart_print_string("\nOVERALL WATER QUALITY: ");
     uart_print_string(get_quality_category(overall_quality));
     uart_print_string("\n");
     
     // Set LEDs based on water quality
     set_alert_leds(overall_quality);
     
     // Trigger alert if necessary
     if (overall_quality == QUALITY_ALERT) {
         uart_print_string("ALERT: Water quality requires attention!\n");
     } else if (overall_quality == QUALITY_CRITICAL) {
         uart_print_string("CRITICAL: Immediate action required! Water quality is unsafe!\n");
     }
 }
 
 const char* get_quality_category(int quality_level) {
     switch (quality_level) {
         case QUALITY_GOOD:
             return "Good";
         case QUALITY_ALERT:
             return "Alert";
         case QUALITY_CRITICAL:
             return "Critical";
         default:
             return "Unknown";
     }
 }
 
 void set_alert_leds(int quality_level) {
     // Turn off all LEDs first
     PORTB &= ~((1 << RED_LED_PIN) | (1 << YELLOW_LED_PIN) | (1 << GREEN_LED_PIN));
     
     // Turn on the appropriate LED based on quality level
     switch (quality_level) {
         case QUALITY_GOOD:
             PORTB |= (1 << GREEN_LED_PIN);
             break;
         case QUALITY_ALERT:
             PORTB |= (1 << YELLOW_LED_PIN);
             break;
         case QUALITY_CRITICAL:
             PORTB |= (1 << RED_LED_PIN);
             break;
     }
 }
 
 void uart_transmit(unsigned char data) {
     // Wait for empty transmit buffer
     while (!(UCSR0A & (1 << UDRE0)));
     
     // Put data into buffer, sends the data
     UDR0 = data;
 }
 
 void uart_print_string(const char* str) {
     // Send each character in the string
     while (*str) {
         uart_transmit(*str++);
     }
 }
 
 void uart_print_float(float value, uint8_t decimal_places) {
     // Handle negative numbers
     if (value < 0) {
         uart_transmit('-');
         value = -value;
     }
     
     // Extract the integer part
     int32_t int_part = (int32_t)value;
     
     // Convert integer part to string and send
     char int_str[10];
     itoa(int_part, int_str, 10);
     uart_print_string(int_str);
     
     // Print decimal point
     uart_transmit('.');
     
     // Extract and print decimal part
     float decimal_part = value - int_part;
     for (uint8_t i = 0; i < decimal_places; i++) {
         decimal_part *= 10;
         uart_transmit('0' + ((int)decimal_part % 10));
     }
 } 