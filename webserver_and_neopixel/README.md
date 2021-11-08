# Table of Contents

1. [Overview](#overview)
2. [Parts](#parts)
3. [Plan/Design](#plandesign)
4. [Load Some Libraries](#load-some-libraries)
5. [Pictuire](#picture)
6. [Gotchas, Caveats & Tricks](#gotchas-caveats--tricks)

# Overview

A little home sensor project.
 
Fusing:

1. esp32 arduino with wifi.
2. BME280 - simple enviromentmental sensor, temperature, humidity, barometrics pressue.
3. Some code to make it play nice with other data systems.

# Parts

* [ESP32-C3-DevKitC-02](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/hw-reference/esp32c3/user-guide-devkitc-02.html)
* [SparkFun Atmospheric Sensor Breakout - BME280](https://www.sparkfun.com/products/13676)
* Neopixel ( on board on the esp32 board )
* Wires
* prototyping board.

# Plan/Design

* Use serial for diagnositc infomration on setup and error message.
* Get the esp32 board to
- [x] run arduino ( The arduino IDE takes care of this transparently ).
- [x] talk to the I2C BME 280 device.
- [x] talk to the on-board neo pixel
* Get a basic web server setup.
* Write a handler for the /metrics endpoint where the sensor values are exposed. They are exposed in a way that means a prometheus server can collect them at regular intervals and squirrel the data way for other system to query , report, agregate, and graph. In this case I use grafana.

# Load Some Libraries

Use arduino library manager to ensure these libraies are installed.

* Wire + SPI + [ Adafruit_BME280 ] ( https://github.com/adafruit/Adafruit_BME280_Library )
* [ Adafruit_NeoPixel ] ( https://github.com/adafruit/Adafruit_NeoPixel )
* Wifi WifiClient WebServer

# Picture

<img src="esp32_neopixel_bme280.jpg" alt="photograph of the wired up parts" width="400px"/>

# Gotchas, Caveats & Tricks

## Onboard led

With other arduino boards there is a simple "set high = on" led on-board that you can use to given an indication of what's going on on your arduino run time.

With the ESP32-C3-DevKitC-02 the onboard led is infact a neopixel on pin 8 , you can't jsut set it to high to get it to turn on. Instead you use the neopixel library and have to hand it the special pin 8

```
13 const int PIN = 8;
...
21 Adafruit_NeoPixel pixels(1, PIN, NEO_GRB + NEO_KHZ800);
```

In this case the first arugment "1" is the number of pixel as neopixel are often found as a string each individually addressable.
So our "number of pixels" is 1 , and the index for it is zero in the code further down:

```
33 pixels.setPixelColor(0, pixels.Color(254, 0, 0));
```

Very handly IMHO.

##  I2C pins

Various Arduino boards have "default" I2C pins such that if you initialize the wire library with no options it "just works". It's not as clear with the ESP32-C3-DevKitC-02 board. The board was quite new at the time I got this setup and the docs said use pin 21 and 22, that didn't seem to work. So I wired up GPOI0 and GPOI1 and handed the wire.begin ( 0,1 ) that worked. The "official" arduino [wire] ( https://www.arduino.cc/en/reference/wire ) docs don't make it clear that you can set the pin that the arduino "talk" I2C. So that was a bit of a "gotcha".
