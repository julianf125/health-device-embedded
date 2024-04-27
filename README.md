# Embedded Code for Wearable Health Monitor

## Description
The code in this repository was developed in the course of my role as Embedded Systems Lead for my Computer Engineering Capstone Project at UC Santa Barbara. In this project, my team and I were tasked with developing the circuitry and firmware for a wearable health monitor in the form of a smartwatch, as well as an Android application to receive and analyze data collected by the health monitor and upload it to a cloud database. This firmware was written to run on the smartwatch, collecting data from all onboard sensors and transmitting it to our Android application (the implementation of which is found in the health-device-Android repository pinned on my profile).

## Hardware
The microcontroller used in this design is the nRF52840. We selected this SOC due to its compact size and on-board Bluetooth capabilities. In addition to the microcontroller, an assortment of sensors for data cololection are included on the device:
*  **BME688:**  Used to collect local weather conditions in the user's location.
*  **TMP117:**  Measures temperature on contact with an object.
*  **LSM9DS1:**  Inertial Measurement Unit to provide data on movement.
*  **MAX30101:**  LED Sensor for use with PPG.
*  **MAX32664:**  Processing unit for use with MAX30101.
*  **LM393:**  Operational amplifier used with omnidirectional microphone.

## Available Data
The following data is directly collected from the device in real-time:
*  Heart rate
*  Blood oxygen saturation
*  Body temperature
*  Air temperature
*  Relative humidity
*  Barometric pressure
*  Air quality
*  Noise level
*  Motion data
