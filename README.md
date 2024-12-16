# Software Requirements Specification (SRS)

## **1. Introduction**

### **1.1 Purpose**
This document defines the requirements for a real-time weather monitoring system. The system simulates weather monitoring using C++ threads and periodic tasks to collect, process, and display data from temperature, humidity, and wind speed sensors.

### **1.2 Scope**
The system will operate in a real-time environment, generating simulated sensor data, processing it to calculate statistics, and displaying the results in the console. It is intended for educational purposes and will demonstrate real-time programming concepts.

---

## **2. System Overview**

### **2.1 Features**
- **Sensor Simulation**: Simulates three sensors (temperature, humidity, wind speed) using threads.
- **Data Collection**: Shared memory is used to store sensor data, with mutexes for thread safety.
- **Data Processing**: Calculates mean, min, and max values for each sensor every 5 seconds.
- **Data Display**: Displays real-time data updates every 2 seconds and statistics every 10 seconds.

### **2.2 Constraints**
- Implemented in C++ with threads and mutexes.
- Timing intervals for data generation, processing, and display must be strictly followed.

---

## **3. Functional Requirements**

### **3.1 Sensor Simulation**
- Each sensor must:
  - Generate random data every 500 ms.
  - Operate within these ranges:
    - Temperature: -30°C to 40°C
    - Humidity: 0% to 100%
    - Wind Speed: 0 m/s to 30 m/s.

### **3.2 Data Collection**
- Use shared memory to store the latest readings from all sensors.
- Protect shared memory with a mutex to ensure thread-safe access.
- Signal when new data is available using flags.

### **3.3 Data Processing**
- Calculate statistics (mean, min, max) every 5 seconds using the last 10 readings from each sensor.

### **3.4 Data Display**
- Display the latest sensor data in the console every 2 seconds.
- Display calculated statistics every 10 seconds.

---

## **4. Non-Functional Requirements**
- **Reliability**: Tasks must meet real-time constraints without race conditions or delays.
- **Maintainability**: The system should be modular and easy to extend with new sensors.
- **Usability**: Console output must be clear and formatted for readability.

---

# Developers To-Do List

## **1. Sensor Simulation**
### Task 1: Sensor Thread Implementation
- **Subtasks**:
  - [ ] Write a thread for each sensor:
    - [ ] Temperature
    - [ ] Humidity
    - [ ] Wind Speed
  - [ ] Use random number generation for sensor readings.
  - [ ] Ensure each sensor generates data every 500 milliseconds.

### Task 2: Data Range Configuration
- **Subtasks**:
  - [ ] Configure the following ranges:
    - Temperature: -30°C to 40°C.
    - Humidity: 0% to 100%.
    - Wind Speed: 0 m/s to 30 m/s.
  - [ ] Test random number generation to ensure realistic outputs.

---

## **2. Data Collection**
### Task 1: Shared Memory Setup
- **Subtasks**:
  - [ ] Define a shared memory structure to store sensor readings.
  - [ ] Include fields for:
    - Latest temperature
    - Latest humidity
    - Latest wind speed

### Task 2: Mutex Protection
- **Subtasks**:
  - [ ] Add a mutex to protect shared memory access.
  - [ ] Implement locking and unlocking mechanisms for thread safety.

### Task 3: Data Availability Signaling
- **Subtasks**:
  - [ ] Implement flags to indicate when new data is available.
  - [ ] Write logic to reset flags after data is processed.

---

## **3. Data Processing**
### Task 1: Statistics Calculation Thread
- **Subtasks**:
  - [ ] Create a separate thread to calculate statistics (mean, min, max) for each sensor.
  - [ ] Implement logic to process the last 10 readings of each sensor.
  - [ ] Schedule the thread to run every 5 seconds.

---

## **4. Data Display**
### Task 1: Real-Time Data Display
- **Subtasks**:
  - [ ] Create a periodic task to display the latest sensor data every 2 seconds.
  - [ ] Format console output for clarity.

### Task 2: Statistics Display
- **Subtasks**:
  - [ ] Create another periodic task to display statistics every 10 seconds.
  - [ ] Format the console to separate current data and statistics clearly.

---

## **5. Optional Tasks (Non-Functional Requirements)**
### Task 1: Code Maintainability
- **Subtasks**:
  - [ ] Modularize code to allow easy addition of new sensors.
  - [ ] Write clear documentation for each module.

### Task 2: System Scalability
- **Subtasks**:
  - [ ] Design data structures to support more sensors.
  - [ ] Ensure the system remains responsive as more threads are added.

