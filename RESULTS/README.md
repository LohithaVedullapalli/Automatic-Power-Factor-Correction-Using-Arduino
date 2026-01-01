# Simulation Results

This folder contains representative results from the Proteus simulation of the Automatic Power Factor Correction (APFC) system.

## Summary of Results
- The system was tested under one resistive load and multiple RL load conditions.
- Under resistive load conditions, the power factor is close to unity and no capacitor correction is applied.
- Under RL load conditions, the power factor decreases due to reactive power.
- The Arduino-based controller automatically switches relay-controlled capacitor banks to improve the power factor.
- The LCD displays real-time values such as power factor and capacitor status during simulation.

## Included Result Images
- **LCD_Resistive_Load.png**  
  Shows LCD output for a purely resistive load with power factor near unity.

- **LCD_RL_Load_Low_PF.png**  
  Shows LCD output for an RL load condition with low power factor before correction.
  
## Note
Multiple RL load variations were tested during simulation. Representative results are shown here to demonstrate correct APFC operation.

