# Krynn Moon Phase Tracker
This program tracks the three moons of Krynn. Useful for Wizards & Moon Sorcerers (if they can escape the Towers of High Sorcery). 

## eInk Version
![image](https://github.com/bridge2nowhere/krynnMoonPhaseTracker/assets/38335227/5386fad0-193a-4b9e-b983-42c1eb7c27f1)

This version uses an [Adafruit MagTag](https://www.adafruit.com/product/4800), which is a simple way to get a 4-color 2.9" gray-scale eInk Display. 

You can also use one of the options below by changing the SPI pins:
* [Adafruit RP2040 FeatherThinkInk](https://www.adafruit.com/product/5727) or the [eInk Feather Friend](https://www.adafruit.com/product/4446) with a [generic 2.9" gray-scale eInk](https://a.co/d/9ktSN71)
* Or [this board](https://www.amazon.com/Waveshare-2-9inch-Display-Raspberry-Interface/dp/B08VRJ28LF/ref=sr_1_61?crid=N1QD5VYY9WU3&keywords=eink&qid=1699767030&sprefix=eink%2Caps%2C164&sr=8-61) with a RP2040: 

### Usage
* Left and Right center buttons change the day
* Extreme left button switches mooons

## Arduboy Version
![image](https://github.com/bridge2nowhere/krynnMoonPhaseTracker/assets/38335227/bf8900fd-e42d-492e-82ee-8089217cab63)

Years given are all AC, negative years would be PC, but I haven't tested them.

### Useage
* "Up/Down" changes the day
* "Left/Right" changes the year
* "A" changes the moon

### Try it
You can run an emulated version with ProjectABE here: https://felipemanga.github.io/ProjectABE/?url=https://raw.githubusercontent.com/bridge2nowhere/krynnMoonPhaseTracker/main/KrynnMoons.hex

You can also get an Arduboy and run it at the gaming table here: https://www.arduboy.com/

### Future Plans
+ Add Month Names
+ Add a way to switch between the different month names (e.g. Solomnic, Dwarven, Elven)
+ Add Graphics

## Sources
The calendar and phases are following the work of Tobin Melroy which I found at http://dragonlance.d20.cz/clanky/243/2317.html on 4 Sept 23

