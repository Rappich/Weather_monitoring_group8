# Weather monitoring project - SRS

## **1. Introduction**

### **1.1 Purpose**
This document specifies the requirements for a real-time weather monitoring system. The system simulates a weather station using C++ threads and periodic tasks to collect, process, and display data from temperature, humidity, and wind speed sensors.

### **1.2 Scope**
The system operates in a real-time environment, generating sensor data, calculating statistics, and displaying results in the console. It is designed for educational purposes.

---

## **2. System Overview**

### **2.1 Features**
- **Sensor Simulation**: Simulates temperature, humidity, and wind speed using threads.
- **Data Collection**: Stores sensor data in shared memory protected by a mutex.
- **Data Processing**: Calculates mean, min, and max statistics every 5 seconds.
- **Data Display**: Shows current data every 2 seconds and statistics every 10 seconds.

### **2.2 Constraints**
- Implemented in C++ using threads and mutexes.
- Must adhere to strict timing intervals for data generation, processing, and display.

---

## **3. Specific Requirements**

### **3.1 Functional Requirements**
#### **3.1.1 Sensor Simulation**
- Simulate three sensors using threads.
- Generate random data every 500 ms within realistic ranges:
  - Temperature: -30°C to 40°C.
  - Humidity: 0% to 100%.
  - Wind Speed: 0 m/s to 30 m/s.

#### **3.1.2 Data Collection**
- Store the latest sensor readings in shared memory protected by a mutex.
- Use flags to indicate new data availability.

#### **3.1.3 Data Processing**
- Calculate mean, min, and max values for each sensor every 5 seconds based on the last 10 readings.

#### **3.1.4 Data Display**
- Display current sensor data every 2 seconds.
- Display calculated statistics every 10 seconds in the console.

### **3.2 Performance Requirements**
- Sensor threads must generate data precisely every 500 ms.
- Data processing and display tasks must adhere to their specified intervals.

---

## **4. Non-Functional Requirements**
- **Reliability**: Ensure all tasks meet real-time constraints without missing deadlines.
- **Usability**: Console output must be clear and easy to interpret.
- **Maintainability**: Code should be modular, well-documented, and allow for the addition of new sensors.

---

## **5. Example Output**
```plaintext
Latest Sensor Data:
Temperature: 15°C
Humidity: 60%
Wind Speed: 10 m/s

Statistics (last 10 readings):
Temperature: Min - 10°C, Max - 20°C, Mean - 15°C
Humidity: Min - 50%, Max - 70%, Mean - 60%
Wind Speed: Min - 8 m/s, Max - 12 m/s, Mean - 10 m/s
