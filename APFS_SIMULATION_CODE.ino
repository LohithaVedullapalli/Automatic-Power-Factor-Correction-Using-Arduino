#include <LiquidCrystal.h>
#include <math.h>

/* ================= LCD ================= */
LiquidCrystal lcd(12, 11, 7, 6, 5, 4);

/* ================= INPUTS ================= */
#define VZC     2
#define IZC     3
#define CT_ADC  A0
#define PT_ADC  A1

/* ================= OUTPUTS ================= */
#define PF_OUT  8
#define C1      9
#define C2      10
#define C3      13
#define C4      A2
#define C5      A3
#define C6      A4

/* ================= CALIBRATION ================= */
#define PHASE_OFFSET_US 420
#define V_CAL 0.45
#define I_CAL 0.02

/* ================= VARIABLES ================= */
volatile unsigned long tVolt = 0;
volatile unsigned long tCurr = 0;
volatile unsigned long timeDiff = 0;
volatile bool zcFlag = false;

unsigned long phaseSum = 0;
int phaseCount = 0;

float Vrms = 0, Irms = 0;
float pf = 0.95;
float phaseAngle = 0;

char buf[12];

/* ================= INTERRUPTS ================= */
void voltageZC() {
  tVolt = micros();
}

void currentZC() {
  if (tVolt > 0) {
    tCurr = micros();
    if (tCurr > tVolt) {
      timeDiff = tCurr - tVolt;
      zcFlag = true;
    }
  }
}

/* ================= SETUP ================= */
void setup() {

  lcd.begin(20, 4);

  pinMode(VZC, INPUT_PULLUP);
  pinMode(IZC, INPUT_PULLUP);
  pinMode(CT_ADC, INPUT);
  pinMode(PT_ADC, INPUT);

  pinMode(PF_OUT, OUTPUT);
  pinMode(C1, OUTPUT);
  pinMode(C2, OUTPUT);
  pinMode(C3, OUTPUT);
  pinMode(C4, OUTPUT);
  pinMode(C5, OUTPUT);
  pinMode(C6, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(VZC), voltageZC, RISING);
  attachInterrupt(digitalPinToInterrupt(IZC), currentZC, RISING);

  lcd.setCursor(0,1);
  lcd.print("   APFC SYSTEM   ");
  delay(1500);
  lcd.clear();
}

/* ================= LOOP ================= */
void loop() {

  /* -------- ADC AVERAGING (FAST) -------- */
  long ctSum = 0, ptSum = 0;
  for (int i = 0; i < 10; i++) {
    ctSum += analogRead(CT_ADC);
    ptSum += analogRead(PT_ADC);
  }

  Irms = (ctSum / 10.0) * I_CAL;
  Vrms = (ptSum / 10.0) * V_CAL;

  /* -------- ZERO CROSS AVERAGING (FAST) -------- */
  if (zcFlag && timeDiff > 200 && timeDiff < 9000) {
    phaseSum += timeDiff;
    phaseCount++;
    zcFlag = false;
  }

  if (phaseCount >= 5) {

    float avgTime = phaseSum / (float)phaseCount;
    avgTime -= PHASE_OFFSET_US;
    if (avgTime < 0) avgTime = 0;

    phaseAngle = (avgTime * 180.0) / 10000.0;
    if (phaseAngle > 80) phaseAngle = 80;

    pf = cos(phaseAngle * DEG_TO_RAD);

    phaseSum = 0;
    phaseCount = 0;
  }

  /* -------- POWER CALCULATIONS -------- */
  float VA  = Vrms * Irms;
  float AP  = VA * pf;
  float Q   = VA * sin(acos(pf));

  float upf = pf;
  if (pf < 0.95) upf = 1.0;

  /* -------- CAPACITOR CONTROL -------- */
  digitalWrite(C1, pf < 0.90);
  digitalWrite(C2, pf < 0.85);
  digitalWrite(C3, pf < 0.80);
  digitalWrite(C4, pf < 0.75);
  digitalWrite(C5, pf < 0.72);
  digitalWrite(C6, pf < 0.70);

  digitalWrite(PF_OUT, pf < 0.9);

  /* ================= LCD DISPLAY ================= */

  // Line 1
  lcd.setCursor(0, 0);
  lcd.print("                    ");
  lcd.setCursor(0, 0);
  lcd.print("V:");
  dtostrf(Vrms, 4, 0, buf); lcd.print(buf);
  lcd.print(" I:");
  dtostrf(Irms, 4, 1, buf); lcd.print(buf);

  // Line 2 (FULL PF)
  lcd.setCursor(0, 1);
  lcd.print("                    ");
  lcd.setCursor(0, 1);
  lcd.print("PF:");
  dtostrf(pf, 5, 3, buf); lcd.print(buf);
  lcd.print(" UPF:");
  dtostrf(upf, 5, 3, buf); lcd.print(buf);

  // Line 3
  lcd.setCursor(0, 2);
  lcd.print("                    ");
  lcd.setCursor(0, 2);
  lcd.print("VA:");
  dtostrf(VA, 6, 0, buf); lcd.print(buf);
  lcd.print(" AP:");
  dtostrf(AP, 6, 0, buf); lcd.print(buf);

  // Line 4
  lcd.setCursor(0, 3);
  lcd.print("                    ");
  lcd.setCursor(0, 3);
  if (pf < 0.90)
    lcd.print("Capacitors added");
  else
    lcd.print("Power Factor OK");

  delay(300);   // FAST update
}