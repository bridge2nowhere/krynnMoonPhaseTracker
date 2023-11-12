#include <Adafruit_GFX.h>
#include "Adafruit_ThinkInk.h"
#include "EEPROM.h"

//put the fonts in a separate file.
#include "font.h"
//Moon_Phases_32
//Moon_Phases_48
//Redressed_Regular_16
//Redressed_Regular_24


//EEPROM Setup////////////////////////////////
int addr = 0;
#define EEPROM_SIZE 5
long timeCount = 0;
bool updateFlag = false;
//////////////////////////////////////////////


//Eink/////////////////////////////////////////
#define EPD_DC 7
#define EPD_CS 8
#define EPD_BUSY -1
#define SRAM_CS -1
#define EPD_RESET 6
#define EPD_SPI &SPI

ThinkInk_290_Grayscale4_T5 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY,
                                   EPD_SPI);

//////////////////////////////////////////////


//Button Pins/////////////////////////////////////////
#define xl_button 15
#define l_button 14
#define r_button 12
#define xr_button 11
///////////////////////////////////////////////




//Program Mode Mangement///////////////////////
enum class moonMode : uint8_t
{
  Nui, Luni, Soli, Menu
};
moonMode moon = moonMode::Luni;
char* nameOfAddress = "Milord";
///////////////////////////////////////////////


//Calendar Tracker Variables///////////////////////
//Nuitari globals
uint8_t nuiPosn = 2;
bool nuiAlignment = false;
const uint8_t nuiMax = 8;
char* nuiPhase[nuiMax] = { "New", "Waxing Crescent", "First Quarter", "Waxing Gibbous", "Full", "Waning Gibbous", "Last Quarter", "Waning Crescent" };
char* nuiSanction[nuiMax] = { "Low", "Waxing", "Waxing", "High", "High", "Waning", "Waning", "Low" };
char* nuiPhaseLetters[nuiMax] = {"z", "d", "g", "j", "Z", "p", "r", "w"};
//Lunitari globals
uint8_t luniPosn = 0;
bool luniAlignment = false;
const uint8_t luniMax = 28;
char* luniPhase[luniMax] = { "New",
                             "Waxing Crescent", "Waxing Crescent", "Waxing Crescent", "Waxing Crescent", "Waxing Crescent", "Waxing Crescent",
                             "First Quarter",
                             "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous",
                             "Full",
                             "Waning Gibbous", "Waning Gibbous", "Waning Gibbous", "Waning Gibbous", "Waning Gibbous", "Waning Gibbous",
                             "Last Quarter",
                             "Waning Crescent", "Waning Crescent", "Waning Crescent", "Waning Crescent", "Waning Crescent", "Waning Crescent"
                           };
char* luniPhaseLetters[luniMax] = {"z",
                                   "a", "b", "c", "d", "e", "f",
                                   "g",
                                   "h", "i", "i", "j", "k", "l",
                                   "Z",
                                   "m", "n", "p", "q", "r", "s"
                                   "t",
                                   "u", "v", "v", "w", "x", "y"
                                  };


char* luniSanction[luniMax] = { "Low", "Low", "Low", "Low",
                                "Waxing", "Waxing", "Waxing", "Waxing", "Waxing", "Waxing", "Waxing",
                                "High", "High", "High", "High", "High", "High", "High",
                                "Waning", "Waning", "Waning", "Waning", "Waning", "Waning", "Waning",
                                "Low", "Low", "Low"
                              };
//Solinari global Variable
uint8_t soliStart[3] = { 16, 28, 4 };
uint8_t soliPosn = 0;
const uint8_t soliMax = 36;
bool soliAlignment = false;
char* soliPhase[soliMax] = { "New",
                             "Waxing Crescent", "Waxing Crescent", "Waxing Crescent", "Waxing Crescent", "Waxing Crescent", "Waxing Crescent", "Waxing Crescent", "Waxing Crescent",
                             "First Quarter",
                             "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous",
                             "Full",
                             "Waning Gibbous", "Waning Gibbous", "Waning Gibbous", "Waning Gibbous", "Waning Gibbous", "Waning Gibbous", "Waning Gibbous", "Waning Gibbous",
                             "Last Quarter",
                             "Waning Crescent", "Waning Crescent", "Waning Crescent", "Waning Crescent", "Waning Crescent", "Waning Crescent", "Waning Crescent", "Waning Crescent"
                           };
char*soliPhaseLetters[soliMax] = {"z",
                                  "a", "b", "b", "c", "d", "d", "e", "f",
                                  "g",
                                  "h", "i", "i", "j", "j", "k", "k", "l",
                                  "Z",
                                  "m", "n", "o", "p", "q", "q", "r", "s"
                                  "t",
                                  "u", "v", "v", "w", "w", "x", "x", "y"
                                 };

char* soliSanction[soliMax] = { "Low", "Low", "Low", "Low", "Low",
                                "Waxing", "Waxing", "Waxing", "Waxing", "Waxing", "Waxing", "Waxing", "Waxing", "Waxing",
                                "High", "High", "High", "High", "High", "High", "High", "High", "High",
                                "Waning", "Waning", "Waning", "Waning", "Waning", "Waning", "Waning", "Waning", "Waning",
                                "Low", "Low", "Low", "Low"
                              };

//Day and Year Global Variables
int16_t year = 386;
#define initMem 5
#define yearHigh  0
#define yearLow 1
uint8_t yearPattern = 0;
int16_t day = 27;
#define dayHigh 2
#define dayLow 3
int dayMax = 335;

uint8_t month = 1;
uint8_t dayOfMonth = 1;
uint8_t dayOfWeek = 1;

//Set for Aurium Empire, Feel free to change to your calendar. It's 8 days since I'm adding one everywhere else, same with months
char* days[8] = { "", "Solus", "Vendus", "Holus", "Lunus", "Angonus", "Tellus", "Aurus" };
char* months[13] = { "", "Neraran", "Eldaran", "Feloran", "Kathoran", "Gratharan", "Daiduran", "Kaldoran", "Randoran", "Amodan", "Baladan", "Zendoran", "Brectadan"};
//////////////////////////////////////////////





void setup() {
  //setup fnction calls
  pinMode(xl_button, INPUT_PULLUP);
  pinMode(l_button, INPUT_PULLUP);
  pinMode(r_button, INPUT_PULLUP);
  pinMode(xr_button, INPUT_PULLUP);
  display.begin(THINKINK_GRAYSCALE4);

  //Read save EEPROM data if it's been saved
  EEPROM.begin(24);
  if (EEPROM.read(initMem) == 37) {
    year = (EEPROM.read(yearHigh) << 8) + EEPROM.read(yearLow);
    day = (EEPROM.read(dayHigh) << 8) + EEPROM.read(dayLow);
  }
  EEPROM.end();

  //Initial update on calendar and screen
  calUpdate();
  drawScreen();
}
void loop() {
  //check the middle buttons for updating the day
  if (digitalRead(l_button) == LOW) {
    day++;
    if (day > dayMax) {
      day = 0;
      year ++;
    }
    calUpdate();
    drawScreen();
    timeCount = millis();
    updateFlag = true;
  }
  else if (digitalRead(r_button) == LOW) {
    day--;
    if (day < 0) {
      day = dayMax;
      year --;
    }
    calUpdate();
    drawScreen();
    timeCount = millis();
    updateFlag = true;
  }
  //switch between moons when the extreme left button is pressed
  if (digitalRead(xl_button) == LOW) {
    if (moon == moonMode::Soli) moon = moonMode::Luni;
    else if (moon == moonMode::Luni) moon = moonMode::Nui;
    else if (moon == moonMode::Nui) moon = moonMode::Soli;
    calUpdate();
    drawScreen();
  }
  //if the day hasn't been changed in three seconds, update the eeprom.
  if (timeCount + 30000 <= millis() && updateFlag) {
    eepromUpdate();
    updateFlag = false;
  }


}

void calUpdate() {
  //find the year pattern there is three year cycle
  yearPattern = year % 3;

  //use the day variable to find the calendar details
  month = (day / 28) + 1;
  dayOfMonth = (day % 28) + 1;
  dayOfWeek = (dayOfMonth % 7) + 1;

  //update the moon cycles
  nuiPosn = (day + 2) % nuiMax;
  luniPosn = day % luniMax;
  soliPosn = (day + soliStart[yearPattern]) % soliMax;

  //check for alignments
  nuiAlignment = false;
  luniAlignment = false;
  soliAlignment = false;
  if ((nuiSanction[nuiPosn] == soliSanction[soliPosn])) {
    nuiAlignment = true;
    soliAlignment = true;
  }
  if ((nuiSanction[nuiPosn] == luniSanction[luniPosn])) {
    nuiAlignment = true;
    luniAlignment = true;
  }
  if ((soliSanction[soliPosn] == luniSanction[luniPosn])) {
    soliAlignment = true;
    luniAlignment = true;
  }
}


void drawScreen() {
  Serial.println(month);
  Serial.println(months[month]);
  Serial.println(day);

  display.clearBuffer();
  display.drawBitmap(0, 0, epd_bitmap_starChart, 296, 128, EPD_LIGHT);
  display.fillCircle(224, 100, 24, EPD_BLACK);
  display.setTextSize(1);
  display.setFont(&Redressed_Regular_24);
  display.setTextColor(EPD_BLACK);
  display.setCursor(0, 24);
  if (moon == moonMode::Luni) {
    display.print(nameOfAddress);
    display.print(", Lunitari is ");
    if (luniAlignment == true) display.print("aligned ");
    display.print("in ");
    display.setCursor(0, 52);
    display.print(luniSanction[luniPosn]);
    display.print(" Sanction tonight");
    display.setCursor(200, 124);
    display.setFont(&Moon_Phases_48);
    display.setTextColor(EPD_WHITE);
    display.print(luniPhaseLetters[luniPosn]);
  }
  else if (moon == moonMode::Soli) {
    display.print(nameOfAddress);
    display.print(", Solinary is ");
    if (soliAlignment == true) display.print("aligned ");
    display.print("in ");
    display.setCursor(0, 52);
    display.print(soliSanction[soliPosn]);
    display.print(" Sanction tonight");
    display.setCursor(200, 124);
    display.setFont(&Moon_Phases_48);
    display.setTextColor(EPD_WHITE);
    display.print(soliPhaseLetters[soliPosn]);
  }
  else if (moon == moonMode::Nui) {
    display.print(nameOfAddress);
    display.print(", Nuitary is ");
    if (nuiAlignment == true) display.print("aligned ");
    display.print("in ");
    display.setCursor(0, 52);
    display.print(nuiSanction[nuiPosn]);
    display.print(" Sanction tonight");
    display.setCursor(200, 124);
    display.setFont(&Moon_Phases_48);
    display.setTextColor(EPD_WHITE);
    display.print(nuiPhaseLetters[nuiPosn]);
  }
  display.setTextColor(EPD_BLACK);
  display.setFont(&Redressed_Regular_16);
  display.setCursor(0, 92);
  display.print("On this ");
  display.print(days[dayOfWeek]);
  display.print(",");

  display.setCursor(0, 108);
  display.print("the ");
  display.print(dayOfMonth);
  if ((dayOfMonth % 10) == 1) display.print("st of ");
  else if ((dayOfMonth % 10) == 2) display.print("nd of ");
  else if ((dayOfMonth % 10) == 3) display.print("rd of ");
  else display.print("th of ");
  display.print(months[month]);
  display.setCursor(0, 124);
  display.print("in the year ");
  if (year > 0) {
    display.print(year);
    display.print(" AC");
  } else {
    display.print(abs(year));
    display.print(" PC");
  }
  display.display();

}

void eepromUpdate() {
  EEPROM.begin(24);
  EEPROM.write(yearHigh, highByte(year));
  EEPROM.write(yearLow, lowByte(year));
  EEPROM.write(dayHigh, highByte(day));
  EEPROM.write(dayLow, lowByte(day));
  EEPROM.write(initMem, 37);
  EEPROM.commit();
  EEPROM.end();
  Serial.println("Save Complete");
}
