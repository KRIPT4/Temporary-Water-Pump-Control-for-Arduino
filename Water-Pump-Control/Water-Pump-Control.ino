#include <Wire.h>         // Wire Built-In by Arduino v1.0.0
#include <Time.h>         // Time by Michael Margolis v1.5.0
#include <TimeLib.h>      // Time by Michael Margolis v1.5.0
#include <TimeAlarms.h>   // TimeAlarms by Michael Margolis v1.5.0
#include <DS3232RTC.h>    // DS3232RTC by Jack Christensen v1.2.4

const int waterPump = 7;  // pin to the Water Pump activated by a Relay.
const int ledAction = 12; // pin Led.

void setup() {
  Serial.begin(9600);
  while (!Serial);              // wait for Arduino Serial Monitor (Arduino Leonardo only)

  pinMode(waterPump, OUTPUT);   // sets the digital pin waterPump as output
  digitalWrite(waterPump, LOW); // sets the digital pin waterPump off
  pinMode(ledAction, OUTPUT);   // sets the digital pin ledAction as output
  digitalWrite(ledAction, LOW); // sets the digital pin ledAction off

  // SYNC the RTC and systime at boot
  setSyncProvider(RTC.get);     // RTC.get() - the function to get the time from an RTC
  if (timeStatus() != timeSet)
    Serial.println("Unable to sync with the RTC");
  else
    Serial.println("RTC has set the system time");

  // create the alarms 
  Alarm.alarmRepeat(22, 30, 0, turnOn);  // 22:30:00hs every day
  Alarm.alarmRepeat(22, 30, 15, turnOff);    // 22:30:15hs every day
}

void loop() {
  digitalClockDisplay();  // update digital clock
  Alarm.delay(1000);      // wait one second between clock display
}

/**
   Callback function that activates the relay on pin waterPump/ledAction (turns on the Water Pump)
*/
void turnOn() {
  Serial.println("Alarm: - turn Water Pump on");
  digitalWrite(waterPump, HIGH); // sets the digital pin waterBomb on
  digitalWrite(ledAction, HIGH); // sets the digital pin ledAction on
}

/**
   Callback function that disables the relay on pin waterPump/ledAction (turns off the Water Pump)
*/
void turnOff() {
  Serial.println("Alarm: - turn Water Pump off");
  digitalWrite(waterPump, LOW); // sets the digital pin waterBomb off
  digitalWrite(ledAction, LOW); // sets the digital pin ledAction off
}

/**
   Functions for printing the clock to the arduino serial monitor
*/
void digitalClockDisplay() {
  // digital clock display of current time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.println();
}

void printDigits(int digits) {
  // utility function for digital clock display: prints colon and leading 0
  Serial.print(":");
  if (digits < 10)
    Serial.print('0');
  Serial.print(digits);
}
