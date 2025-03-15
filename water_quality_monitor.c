/**
 * Water Quality Monitoring System Simulation
 * 
 * This program simulates a microcontroller reading water quality sensors
 * and categorizing water quality based on predefined thresholds.
 */

 #include <stdio.h>
 #include <stdlib.h>
 #include <time.h>
 #include <unistd.h>
 #include "water_quality_config.h"
 
 // Function prototypes
 float read_ph_sensor(void);
 float read_temperature_sensor(void);
 float read_turbidity_sensor(void);
 float read_tds_sensor(void);
 float read_dissolved_oxygen_sensor(void);
 void analyze_water_quality(float ph, float temperature, float turbidity, float tds, float dissolved_oxygen);
 const char* get_quality_category(int quality_level);
 void display_sensor_readings(float ph, float temperature, float turbidity, float tds, float dissolved_oxygen);
 void initialize_system(void);
 
 int main() {
     // Seed the random number generator for simulated sensor readings
     srand(time(NULL));
     
     // Initialize the system
     initialize_system();
     
     // Main monitoring loop
     while (1) {
         // Simulate reading from sensors
         float ph = read_ph_sensor();
         float temperature = read_temperature_sensor();
         float turbidity = read_turbidity_sensor();
         float tds = read_tds_sensor();
         float dissolved_oxygen = read_dissolved_oxygen_sensor();
         
         // Display current sensor readings
         display_sensor_readings(ph, temperature, turbidity, tds, dissolved_oxygen);
         
         // Analyze water quality and trigger alerts if necessary
         analyze_water_quality(ph, temperature, turbidity, tds, dissolved_oxygen);
         
         // Delay between readings (in seconds)
         printf("\nWaiting %d seconds for next reading...\n", READING_INTERVAL);
         printf("------------------------------------------------------\n\n");
         sleep(READING_INTERVAL);
     }
     
     return 0;
 }
 
 void initialize_system(void) {
     printf("------------------------------------------------------\n");
     printf("      WATER QUALITY MONITORING SYSTEM SIMULATION      \n");
     printf("------------------------------------------------------\n");
     printf("Initializing sensors and system components...\n");
     printf("System ready! Beginning continuous monitoring.\n\n");
 }
 
 float read_ph_sensor(void) {
     // Simulate pH reading (typically 0-14, with 7 being neutral)
     // Adding some random variation to simulate real-world fluctuations
     float base_ph = 7.0;  // Neutral pH as base
     float variation = ((float)rand() / RAND_MAX * 2.0 - 1.0) * 2.0;  // Random variation between -2 and +2
     
     return base_ph + variation;
 }
 
 float read_temperature_sensor(void) {
     // Simulate temperature reading (in Celsius)
     // Normal water temperature might be around 15-25°C
     float base_temp = 20.0;
     float variation = ((float)rand() / RAND_MAX * 2.0 - 1.0) * 5.0;  // Random variation between -5 and +5
     
     return base_temp + variation;
 }
 
 float read_turbidity_sensor(void) {
     // Simulate turbidity reading (in NTU - Nephelometric Turbidity Units)
     // Drinking water is typically <1 NTU, while very cloudy water can be >100 NTU
     float base_turbidity = 5.0;
     float variation = ((float)rand() / RAND_MAX) * 20.0;  // Random variation between 0 and 20
     
     return base_turbidity + variation;
 }
 
 float read_tds_sensor(void) {
     // Simulate TDS (Total Dissolved Solids) reading (in ppm - parts per million)
     // Drinking water typically has TDS < 500 ppm
     float base_tds = 200.0;
     float variation = ((float)rand() / RAND_MAX) * 400.0;  // Random variation between 0 and 400
     
     return base_tds + variation;
 }
 
 float read_dissolved_oxygen_sensor(void) {
     // Simulate dissolved oxygen reading (in mg/L)
     // Healthy water typically has DO levels > 6 mg/L
     float base_do = 8.0;
     float variation = ((float)rand() / RAND_MAX * 2.0 - 1.0) * 4.0;  // Random variation between -4 and +4
     
     return base_do + variation;
 }
 
 void display_sensor_readings(float ph, float temperature, float turbidity, float tds, float dissolved_oxygen) {
     printf("Current Sensor Readings:\n");
     printf("pH: %.2f\n", ph);
     printf("Temperature: %.2f °C\n", temperature);
     printf("Turbidity: %.2f NTU\n", turbidity);
     printf("TDS: %.2f ppm\n", tds);
     printf("Dissolved Oxygen: %.2f mg/L\n", dissolved_oxygen);
     printf("\n");
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
     printf("Water Quality Analysis:\n");
     printf("pH: %s\n", get_quality_category(ph_quality));
     printf("Temperature: %s\n", get_quality_category(temp_quality));
     printf("Turbidity: %s\n", get_quality_category(turbidity_quality));
     printf("TDS: %s\n", get_quality_category(tds_quality));
     printf("Dissolved Oxygen: %s\n", get_quality_category(do_quality));
     
     // Determine overall water quality (worst case)
     int overall_quality = ph_quality;
     if (temp_quality > overall_quality) overall_quality = temp_quality;
     if (turbidity_quality > overall_quality) overall_quality = turbidity_quality;
     if (tds_quality > overall_quality) overall_quality = tds_quality;
     if (do_quality > overall_quality) overall_quality = do_quality;
     
     printf("\nOVERALL WATER QUALITY: %s\n", get_quality_category(overall_quality));
     
     // Trigger alert if necessary
     if (overall_quality == QUALITY_ALERT) {
         printf("⚠️ ALERT: Water quality requires attention!\n");
     } else if (overall_quality == QUALITY_CRITICAL) {
         printf("🚨 CRITICAL: Immediate action required! Water quality is unsafe!\n");
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