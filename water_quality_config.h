/**
 * Water Quality Monitoring System Configuration
 * 
 * This header file defines the thresholds and constants used for
 * water quality monitoring and categorization.
 */

 #ifndef WATER_QUALITY_CONFIG_H
 #define WATER_QUALITY_CONFIG_H
 
 // System configuration
 #define READING_INTERVAL 5  // Time between readings in seconds
 
 // Quality categories
 #define QUALITY_GOOD     0
 #define QUALITY_ALERT    1
 #define QUALITY_CRITICAL 2
 
 // pH thresholds (pH scale 0-14, 7 is neutral)
 #define PH_GOOD_MIN      6.5
 #define PH_GOOD_MAX      8.5
 #define PH_ALERT_MIN     6.0
 #define PH_ALERT_MAX     9.0
 // Anything outside PH_ALERT_MIN to PH_ALERT_MAX is considered critical
 
 // Temperature thresholds (in Celsius)
 #define TEMP_GOOD_MIN    15.0
 #define TEMP_GOOD_MAX    25.0
 #define TEMP_ALERT_MIN   10.0
 #define TEMP_ALERT_MAX   30.0
 // Anything outside TEMP_ALERT_MIN to TEMP_ALERT_MAX is considered critical
 
 // Turbidity thresholds (in NTU - Nephelometric Turbidity Units)
 #define TURBIDITY_GOOD   5.0   // Clear water
 #define TURBIDITY_ALERT  10.0  // Slightly cloudy
 // Anything above TURBIDITY_ALERT is considered critical
 
 // TDS thresholds (Total Dissolved Solids, in ppm - parts per million)
 #define TDS_GOOD         300.0  // Excellent water quality
 #define TDS_ALERT        500.0  // Acceptable water quality
 // Anything above TDS_ALERT is considered critical
 
 // Dissolved Oxygen thresholds (in mg/L)
 #define DO_GOOD          6.0   // Healthy for aquatic life
 #define DO_ALERT         4.0   // Stressful for aquatic life
 // Anything below DO_ALERT is considered critical
 
 #endif /* WATER_QUALITY_CONFIG_H */
 
 
 
 
 