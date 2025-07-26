# Fridge Door Temperature Monitor – Arduino Project
This project logs temperature and time data whenever a fridge door is opened and closed. It helps identify how long the fridge is left open and the impact on internal temperature.

What It Does
    • Records the time and temperature when the fridge door is opened
    • Records the time and temperature when the door is closed
    • Saves the data to a CSV file on an SD card
    
Hardware Used
    • Arduino Uno
    • DS3231 Real-Time Clock (RTC) module (used for both timekeeping and temperature sensing)
    • Photoresistor (used to detect light levels and determine door state)
    • SD card module
    
Data Format
The .csv file stores entries in the following format:
Open Time, Open Temp, Close Time, Close Temp, 

Example:
2025-07-24 17:45:12, 4.5, 2025-07-24 17:45:45, 5.3

Video Walkthrough
You can watch a full demonstration of the project here:
YouTube Video
Future Improvements
    • Add wireless communication (e.g., Wi-Fi or Bluetooth) to measure outside temperature when the door is open
    • Make a SQL database to analyse the data
      
