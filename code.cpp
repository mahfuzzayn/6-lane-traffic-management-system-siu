
// ======================================================
// 6 LANE TRAFFIC LIGHT MANAGEMENT SYSTEM WITH ARDUINO
// Group 5
// ======================================================


// -------------------- PIN DEFINITIONS --------------------

int lane1_greenLED = 2;
int lane1_yellowLED = 3;
int lane1_redLED = 4;

int lane2_greenLED = 5;
int lane2_yellowLED = 6;
int lane2_redLED = 7;

int lane3_greenLED = 8;
int lane3_yellowLED = 9;
int lane3_redLED = 10;

int lane4_greenLED = 11;
int lane4_yellowLED = 12;
int lane4_redLED = 13;

const byte lane5_greenLED = A0;
const byte lane5_yellowLED = A1;
const byte lane5_redLED = A2;

const byte lane6_greenLED = A3;
const byte lane6_yellowLED = A4;
const byte lane6_redLED = A5;


// -------------------- PIN ARRAYS --------------------

int greenPins[] = {
  lane1_greenLED,
  lane2_greenLED,
  lane3_greenLED,
  lane4_greenLED,
  lane5_greenLED,
  lane6_greenLED
};

int yellowPins[] = {
  lane1_yellowLED,
  lane2_yellowLED,
  lane3_yellowLED,
  lane4_yellowLED,
  lane5_yellowLED,
  lane6_yellowLED
};

int redPins[] = {
  lane1_redLED,
  lane2_redLED,
  lane3_redLED,
  lane4_redLED,
  lane5_redLED,
  lane6_redLED
};


// -------------------- LANE PAIR DEFINITIONS --------------------

// Opposite lane pairs
// Array indexes start from 0

const byte lanePairs[3][2] = {
  {0, 3},  // Lane 1 + Lane 4
  {1, 4},  // Lane 2 + Lane 5
  {2, 5}   // Lane 3 + Lane 6
};


// -------------------- TIMING --------------------

const unsigned long STARTUP_RED_TIME = 1000; // 1 sec

const unsigned long GREEN_TIME = 5000;  // 5 sec
const unsigned long YELLOW_TIME = 2000; // 2 sec


// ======================================================
// SET ALL LEDs OFF
// ======================================================

void setAllOff() {

  for (int i = 0; i < 6; i++) {

    digitalWrite(greenPins[i], LOW);
    digitalWrite(yellowPins[i], LOW);
    digitalWrite(redPins[i], LOW);
  }
}


// ======================================================
// SET ALL ROADS TO RED
// ======================================================

void setAllRed() {

  for (int i = 0; i < 6; i++) {

    digitalWrite(greenPins[i], LOW);
    digitalWrite(yellowPins[i], LOW);
    digitalWrite(redPins[i], LOW);

    digitalWrite(redPins[i], HIGH);
  }
}


// ======================================================
// SET SELECTED LANE PAIR TO GREEN
// ======================================================

void setPairGreen(int pairNumber) {

  // Keep all other lanes RED
  setAllRed();

  // Get the two lanes of the selected pair
  int laneA = lanePairs[pairNumber][0];
  int laneB = lanePairs[pairNumber][1];

  // Turn GREEN ON for both lanes
  digitalWrite(redPins[laneA], LOW);
  digitalWrite(redPins[laneB], LOW);

  digitalWrite(greenPins[laneA], HIGH);
  digitalWrite(greenPins[laneB], HIGH);
}


// ======================================================
// SET SELECTED LANE PAIR TO YELLOW
// ======================================================

void setPairYellow(int pairNumber) {

  int laneA = lanePairs[pairNumber][0];
  int laneB = lanePairs[pairNumber][1];

  // Turn GREEN OFF
  digitalWrite(greenPins[laneA], LOW);
  digitalWrite(greenPins[laneB], LOW);

  // Turn YELLOW ON
  digitalWrite(yellowPins[laneA], HIGH);
  digitalWrite(yellowPins[laneB], HIGH);
}


// ======================================================
// SET SELECTED LANE PAIR TO RED
// ======================================================

void setPairRed(int pairNumber) {

  int laneA = lanePairs[pairNumber][0];
  int laneB = lanePairs[pairNumber][1];

  // Turn GREEN and YELLOW OFF
  digitalWrite(greenPins[laneA], LOW);
  digitalWrite(yellowPins[laneA], LOW);

  digitalWrite(greenPins[laneB], LOW);
  digitalWrite(yellowPins[laneB], LOW);

  // Turn RED ON
  digitalWrite(redPins[laneA], HIGH);
  digitalWrite(redPins[laneB], HIGH);
}


// ======================================================
// SETUP
// ======================================================

void setup() {

  // Configure all 18 LED pins as OUTPUT
  for (int i = 0; i < 6; i++) {

    pinMode(greenPins[i], OUTPUT);
    pinMode(yellowPins[i], OUTPUT);
    pinMode(redPins[i], OUTPUT);
  }

  // Initially, all six lanes show RED
  setAllRed();

  // Hold all RED for one second
  delay(STARTUP_RED_TIME);
}


// ======================================================
// MAIN TRAFFIC CONTROL LOOP
// ======================================================

void loop() {

  // Activate lane pairs in sequence
  // Lane 1 + 4 -> Lane 2 + 5 -> Lane 3 + 6

  for (int currentPair = 0; currentPair < 3; currentPair++) {


    // ------------------------------------------
    // STEP 1: SELECTED PAIR GREEN
    // ------------------------------------------

    setPairGreen(currentPair);

    delay(GREEN_TIME);


    // ------------------------------------------
    // STEP 2: SELECTED PAIR YELLOW
    // ------------------------------------------

    setPairYellow(currentPair);

    delay(YELLOW_TIME);


    // ------------------------------------------
    // STEP 3: SELECTED PAIR RED
    // ------------------------------------------

    setPairRed(currentPair);

    // Next pair will activate immediately
  }

  // After Lane 3 + 6, the loop starts again
}
