# WI-FI Captive Portal

## Overview

This project is an educational Arduino/ESP Wi-Fi captive portal demo.  
It creates a local Wi-Fi access point and serves a simple web page to connected users.

The purpose of this project is to understand how captive portals, local web servers, DNS redirection, and embedded Wi-Fi devices work.

## Features

- Creates a local Wi-Fi access point
- Runs a basic web server
- Handles DNS redirection for captive portal behavior
- Displays a simple HTML login/success page
- Designed for learning, testing, and demonstration purposes

## Hardware Requirements

- ESP32 board
- USB cable
- Arduino IDE
- Required Arduino libraries depending on the board and code used

## Software Requirements

- Arduino IDE
- ESP32 board package installed
- ESP32 USB-to-serial driver installed, depending on your board:
    - CP2102 / CP2104: Silicon Labs CP210x USB to UART Driver
    - CH340 / CH341: WCH CH340 Driver
- Git / GitHub for version control

## How to Use

1. Clone or download this repository.
2. Open the `.ino` file in Arduino IDE.
3. Select the correct board from **Tools → Board**.
4. Select the correct port from **Tools → Port**.
5. Upload the sketch to the board.
6. Connect to the Wi-Fi network created by the device.
7. Open a browser to test the captive portal page.

## Disclaimer

This project is created for educational and authorized testing purposes only.

Do not use this project to collect real user credentials, impersonate real networks, trick users, or perform unauthorized activity on networks or devices you do not own or have permission to test.

The author is not responsible for any misuse of this project. Users are responsible for following all applicable laws, university policies, and ethical guidelines.

## Ethical Use

Use this project only in a controlled lab environment, personal test network, or classroom demonstration.

Recommended safe uses include:

- Learning how captive portals work
- Testing local web server behavior on ESP boards
- Understanding DNS redirection
- Demonstrating Wi-Fi security awareness

Do not deploy this on public networks or against other people without clear permission.

## License

This project is provided for educational use.  
You may modify and use it responsibly.