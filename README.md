# Software Requirements Specification

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

## **3. Developers To-Do List**

### **3.1 Sensor Simulation**
1. **Thread Creation**
   - [ ] Create three threads to simulate the sensors:
     - Temperature
     - Humidity
     - Wind Speed
2. **Data Generation**
   - [ ] Implement random data generation for each sensor using the following ranges:
     - Temperature: -30°C to 40°C
     - Humidity: 0% to 100%
     - Wind Speed: 0 m/s to 30 m/s
   - [ ] Ensure data is generated every 500 milliseconds.

---

### **3.2 Data Collection**
1. **Shared Memory**
   - [ ] Create a shared memory structure to store the latest readings from all sensors.
   - [ ] Protect shared memory access using a mutex.
2. **Signaling**
   - [ ] Implement flags to signal when new data is available for processing.

---

### **3.3 Data Processing**
1. **Statistics Calculation**
   - [ ] Create a separate thread for calculating statistics (mean, min, max) for each sensor.
   - [ ] Retrieve the last 10 readings for each sensor.
   - [ ] Calculate the following statistics every 5 seconds:
     - Mean
     - Minimum
     - Maximum

---

### **3.4 Data Display**
1. **Current Data Display**
   - [ ] Create a periodic task to display the latest sensor data in the console every 2 seconds.
2. **Statistics Display**
   - [ ] Create another periodic task to display calculated statistics every 10 seconds.
3. **Console Formatting**
   - [ ] Ensure console output is clear and easy to read.

---

## **4. Functional Requirements**

### **4.1 Sensor Simulation**
- Each sensor must:
  - Use a dedicated thread.
  - Generate random data every 500 ms.
  - Operate within the specified ranges:
    - Temperature: -30°C to 40°C
    - Humidity: 0% to 100%
    - Wind Speed: 0 m/s to 30 m/s

### **4.2 Data Collection**
- Use shared memory to store the most recent data from all sensors.
- Protect shared memory access using a mutex.
- Signal availability of new data using flags.

### **4.3 Data Processing**
- Calculate statistics (mean, min, max) for each sensor every 5 seconds.
- Use the last 10 readings for calculations.

### **4.4 Data Display**
- Display the latest sensor data every 2 seconds.
- Display calculated statistics every 10 seconds.

---

## **5. Performance Requirements**
- Ensure sensor threads generate data precisely every 500 milliseconds.
- Data processing and display tasks must execute within their specified intervals without delays or race conditions.

---

## **6. Non-Functional Requirements**
1. **Reliability**
   - Ensure tasks meet real-time constraints and deadlines.
2. **Usability**
   - Console output should be clear and easy to interpret.
3. **Maintainability**
   - Code should be modular and well-documented.
4. **Scalability**
   - Design the system to allow the addition of more sensors with minimal changes.

---

## **7. Example Output**
```plaintext
Latest Sensor Data:
Temperature: 15°C
Humidity: 60%
Wind Speed: 10 m/s

Statistics (last 10 readings):
Temperature: Min - 10°C, Max - 20°C, Mean - 15°C
Humidity: Min - 50%, Max - 70%, Mean - 60%
Wind Speed: Min - 8 m/s, Max - 12 m/s, Mean - 10 m/s
