#include <Arduboy2.h>


Arduboy2 arduboy;

//variable for which moon is on the screen, will change to enum
uint8_t moon = 0;

//Nuitari globals
uint8_t nuiPosn = 2;
const uint8_t nuiMax = 8;
char* nuiPhase[nuiMax] = { "New", "Waxing Crescent", "First Quarter", "Waxing Gibbous", "Full", "Waning Gibbous", "Last Quarter", "Waning Crescent" };
char* nuiSanction[nuiMax] = { "Low", "Waxing", "Waxing", "High", "High", "Waning", "Waning", "Low" };

//Lunitari globals
uint8_t luniPosn = 0;
const uint8_t luniMax = 28;
char* luniPhase[luniMax] = { "New",
                             "Waxing Crescent", "Waxing Crescent", "Waxing Crescent", "Waxing Crescent", "Waxing Crescent", "Waxing Crescent",
                             "First Quarter",
                             "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous",
                             "Full",
                             "Waning Gibbous", "Waning Gibbous", "Waning Gibbous", "Waning Gibbous", "Waning Gibbous", "Waning Gibbous",
                             "Last Quarter",
                             "Waning Crescent", "Waning Crescent", "Waning Crescent", "Waning Crescent", "Waning Crescent", "Waning Crescent" };
char* luniSanction[luniMax] = { "Low", "Low", "Low", "Low",
                                "Waxing", "Waxing", "Waxing", "Waxing", "Waxing", "Waxing", "Waxing",
                                "High", "High", "High", "High", "High", "High", "High",
                                "Waning", "Waning", "Waning", "Waning", "Waning", "Waning", "Waning",
                                "Low", "Low", "Low" };

//Solinari global Variable
uint8_t soliStart[3] = { 16, 28, 4 };
uint8_t soliPosn = 0;
const uint8_t soliMax = 36;
char* soliPhase[soliMax] = { "New",
                             "Waxing Crescent", "Waxing Crescent", "Waxing Crescent", "Waxing Crescent", "Waxing Crescent", "Waxing Crescent", "Waxing Crescent", "Waxing Crescent",
                             "First Quarter",
                             "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous", "Waxing Gibbous",
                             "Full",
                             "Waning Gibbous", "Waning Gibbous", "Waning Gibbous", "Waning Gibbous", "Waning Gibbous", "Waning Gibbous", "Waning Gibbous", "Waning Gibbous",
                             "Last Quarter",
                             "Waning Crescent", "Waning Crescent", "Waning Crescent", "Waning Crescent", "Waning Crescent", "Waning Crescent", "Waning Crescent", "Waning Crescent" };
char* soliSanction[soliMax] = { "Low", "Low", "Low", "Low", "Low",
                                "Waxing", "Waxing", "Waxing", "Waxing", "Waxing", "Waxing", "Waxing", "Waxing", "Waxing",
                                "High", "High", "High", "High", "High", "High", "High", "High", "High",
                                "Waning", "Waning", "Waning", "Waning", "Waning", "Waning", "Waning", "Waning", "Waning",
                                "Low", "Low", "Low", "Low" };

//Day and Year Global Variables
int year = 386;
uint8_t yearPattern = 0;
int day = 0;
int dayMax = 335;

uint8_t month = 1;
uint8_t dayOfMonth = 1;
uint8_t dayOfWeek = 1;

char* days[8] = { "", "Gateway     ", "Bright Eye  ", "Nights Eye  ", "Dead Eye    ", "Dream Dance ", "Winged Trade", "World Tree  " };


void setup() {
  //basic arduboy setup functions
  arduboy.begin();
  arduboy.setFrameRate(30);
}

oes.
void loop() {
  //wait for the next fram
  if (!(arduboy.nextFrame()))
    return;
  //button polling & handeling
  //up & down = change day
  //left & right = change year
  //a button = change moon
  arduboy.pollButtons();
  if (arduboy.justPressed(RIGHT_BUTTON)) {
    year--;
  }

  if (arduboy.justPressed(LEFT_BUTTON)) {
    year++;
  }

  if (arduboy.justPressed(UP_BUTTON)) {
    day++;
  }

  if (arduboy.justPressed(DOWN_BUTTON)) {
    day--;
  }
  if (day > dayMax) {
    day = 0;
    year++;
  }
  if (day < 0) {
    day = dayMax;
    year--;
  }
  if (arduboy.justPressed(A_BUTTON)) {
    moon++;
    if (moon > 2) moon = 0;
  }

  //update calendar & moon data base on button presses
  dateUpdate();
  moonUpdate();


  // draw the screen
  arduboy.clear();
  arduboy.setCursor(0, 0);
  arduboy.println("Krynn Moon Tracker");
  arduboy.print(month);
  arduboy.print("-");
  arduboy.print(dayOfMonth);
  arduboy.print("-");
  arduboy.println(year);
  arduboy.println(days[dayOfWeek]);
  arduboy.println();



  if (moon == 0) {
    arduboy.println("Lunitari");
    arduboy.print("Sanction:");
    arduboy.println(luniSanction[luniPosn]);
    arduboy.print("Phase:");
    arduboy.print(luniPhase[luniPosn]);
  }

  if (moon == 1) {
    arduboy.println("Solinari");
    arduboy.print("Sanction:");
    arduboy.println(soliSanction[soliPosn]);
    arduboy.print("Phase:");
    arduboy.print(soliPhase[soliPosn]);
  }

  if (moon == 2) {
    arduboy.println("Nuitari");
    arduboy.print("Sanction:");
    arduboy.println(nuiSanction[nuiPosn]);
    arduboy.print("Phase:");
    arduboy.print(nuiPhase[nuiPosn]);
  }

  arduboy.display();
}

void dateUpdate() {
  //find the year pattern there is three year cycle
  yearPattern = year % 3;
  
  //use the day variable to find the calendar details
  month = (day / 28) + 1;
  dayOfMonth = (day % 28) + 1;
  dayOfWeek = (dayOfMonth % 7) + 1;

}


void moonUpdate() {
  //find the day of the moon cycle for each moon
  nuiPosn = (day + 2) % nuiMax;
  luniPosn = day % luniMax;
  soliPosn = (day + soliStart[yearPattern]) % soliMax;
}
