# ⚡ Automatic Power Factor Correction (APFC) – Proteus Simulation

## 📌 Project Title
**Automatic Power Factor Correction (APFC) using Arduino and Relay-Based Capacitor Switching**

---

## 📝 Short Description
This project demonstrates an **Automatic Power Factor Correction (APFC)** system simulated in **Proteus** using an **Arduino UNO**.  
The system continuously monitors the power factor (simulation-level approximation) and automatically switches capacitor banks through relays to improve the overall power factor.  
The focus of this project is on **control logic, automation, and system behavior**, making it suitable for academic demonstration and learning purposes.

---

## 🛠 Tools Used
- **Proteus 8 Professional** – Circuit design and simulation  
- **Arduino UNO** – Control and decision-making unit  
- **Arduino IDE** – Code development and HEX generation  
- **C / C++ (Arduino)** – Control logic programming  
- **16×2 LCD** – Display of power factor and capacitor status  

---

## ⚙ How It Works (Simple Explanation)
1. The system receives a phase-difference or power-factor–related signal (simulated).
2. The **Arduino UNO** processes this signal and determines whether the power factor is low.
3. Based on predefined thresholds, the Arduino **switches relay-controlled capacitor banks ON or OFF**.
4. Adding capacitors compensates reactive power and improves the power factor.
5. The **LCD displays the current power factor status and active capacitor stages**.
6. The entire behavior is verified through **Proteus simulation**.

> ⚠ Note:  
> This project uses a **simulation-level approximation** of power factor suitable for Proteus-based demonstrations. It emphasizes automation and control logic rather than high-precision power system analysis.

---

## 📂 Repository Contents
- **Proteus_Simulation/** – Complete Proteus project files  
- **Arduino_Code/** – Arduino source code (`.ino`) and compiled HEX file  
- **Circuit_Diagrams/** – Schematic and block diagrams  
- **Results/** – Screenshots of running simulation and LCD output  

---

## 🎯 Applications
- Academic mini / major projects  
- Understanding APFC logic and relay control  
- Embedded systems and automation learning  
- Demonstration of power factor correction concepts  

---


