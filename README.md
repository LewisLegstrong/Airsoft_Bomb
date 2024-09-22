| Microcontroller | ESP-Wroom-32 |
| --------------- | ------------ |

# Airsoft Bomb

## Index

1. [Inspiration](#inspiration)
2. [Supported Targets](#supported-targets)
3. [Airsoft Bomb](#airsoft-bomb)

---

## Inspiration

Watching and knowing a mate of mine was playing Airsoft as a past time activity, and having participated a few times myself, being a CS GO and CS 2 player, I thought of a cool project to create a bomb (Airsoft) and have it as the center of Airsoft events.

I will be capable of joining my CAD and 3D printing experience to programming and build a product from the ground up.

This also offers the opportunity to tackle a project with a certain level of complexity for educational purposes, allowing me to extend my knowledge with embedded systems, multithreading and accurate use of limited resources when coding.

---

## Defining goals and objectives

First things first: this project will use timers, buzzers, buttons and LEDs as the basic to operate, so getting some templates for those to work is mandatory. While doing so, getting tasks to run is also a good point.

---

## Getting Familiar again

From a past experience using the ESP32 as a microcontroller, and creating code for it with ESP-IDF, I know I

![NodeMCU ESP32 pinout](https://www.twinschip.com/image/catalog/Products%20Twins%20Chip%20Store%202020/ESP32%20ESP-WROOM-32%20Development%20Board%20/ESP32%20ESP-WROOM-32%20Development%20Board%20%20-%20Twins%20Chip%20D.jpg)

---

## Pinout

![alt text](image.png)

---

## Notes to self:

With the hardware used, internal pullUp resistors seem to be a struggle, as the output generated on 3 different pins using such resistors results in an unknown behaviour. Using the internall pullDown offers the proper way to work with buttons, in an effeort to avoid using other components in the project. I want to test the issue with a different board of the same model and verify the issue persists.

---

---
