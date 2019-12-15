//Pin defintions
const unsigned int R_PIN = 5;
const unsigned int G_PIN = 6;
const unsigned int B_PIN = 3; 
const unsigned int PROX_PIN = A0;

const unsigned int RANGE_LEVEL_COUNT = 5;

/*const unsigned int COLOR_TARGETS[RANGE_LEVEL_COUNT][3] = { {0,255,0},     //Green
                                                           {255,255,0},   //Yellow
                                                           {255, 0, 0},   //Red
                                                           {0, 0, 255},   //Blue
                                                           {255, 0, 255}  //Purple
                                                         };*/

/*const unsigned int COLOR_TARGETS[RANGE_LEVEL_COUNT][3] = { {102, 255, 255},  //Light Blue
                                                           {51, 153, 255},   //
                                                           {0, 102, 204},    //
                                                           {0, 51, 153},     //
                                                           {0, 0, 102}       //Dark Blue
                                                         };*/

const unsigned int COLOR_TARGETS[RANGE_LEVEL_COUNT][3] = { {0, 51, 0},       // Dark Green
                                                           {102, 255, 102},   // Light Green
                                                           {255, 153, 0},    // Orange
                                                           {255, 80, 80},     // Light Red
                                                           {128, 0, 0}       //Dark Red
                                                         };
                                                         
//proximity ranges
const unsigned int RANGE_LEVELS[RANGE_LEVEL_COUNT][2] = {{25,19},
                                                         {18,16},
                                                         {15,14},
                                                         {13,12},
                                                         {11,0}
                                                        };

void setup() {
  Serial.begin(9600);

  //Pin setup
  pinMode(R_PIN, OUTPUT);
  pinMode(G_PIN, OUTPUT);
  pinMode(B_PIN, OUTPUT);
  
  pinMode(PROX_PIN, INPUT);
}

void loop() {
  
  unsigned int currLevel = 0;
  unsigned int calcRed = 0;
  unsigned int calcGreen = 0;
  unsigned int calcBlue = 0; 
  
  // Range from green, yellow, to red depending on proximity of ultra sonic sensor
  unsigned int currRange = analogRead(PROX_PIN);
  if (currRange > RANGE_LEVELS[0][0])
  {
    currRange = RANGE_LEVELS[0][0];
  }
  
  //RGB proximity algorithm
  for (unsigned int i = 0; i < RANGE_LEVEL_COUNT; i++)
  {
    if (currRange <= RANGE_LEVELS[i][0] && currRange >= RANGE_LEVELS[i][1])
    {
      currLevel = i;
      break;
    }
  }
  //simply look at the next level target and map the diff in ranges
  if ((currLevel + 1) < RANGE_LEVEL_COUNT)
  {
    calcRed = map(currRange, RANGE_LEVELS[currLevel][1], RANGE_LEVELS[currLevel][0], COLOR_TARGETS[currLevel+1][0], COLOR_TARGETS[currLevel][0]);
    calcGreen = map(currRange, RANGE_LEVELS[currLevel][1], RANGE_LEVELS[currLevel][0], COLOR_TARGETS[currLevel+1][1], COLOR_TARGETS[currLevel][1]);
    calcBlue = map(currRange, RANGE_LEVELS[currLevel][1], RANGE_LEVELS[currLevel][0], COLOR_TARGETS[currLevel+1][2], COLOR_TARGETS[currLevel][2]);
  }
  else
  {
    calcRed = COLOR_TARGETS[currLevel][0];
    calcGreen = COLOR_TARGETS[currLevel][1];
    calcBlue = COLOR_TARGETS[currLevel][2];
  }

  Serial.print(currLevel);
  Serial.print("\t");
  Serial.print(currRange);
  Serial.print("\t");
  Serial.print(calcRed);
  Serial.print("\t");
  Serial.print(calcGreen);
  Serial.print("\t");
  Serial.print(calcBlue);
  Serial.println();

  analogWrite(R_PIN, calcRed);
  analogWrite(G_PIN, calcGreen);
  analogWrite(B_PIN, calcBlue);
  delay(300);
  
  /*
   * Use the code below to ensure that the LED is wired correctly.
   * If serial text does not match reality then something is wrong
   * 
   */
   
  /*
  Serial.println("Red");
  analogWrite(R_PIN, 255);
  analogWrite(G_PIN, 0);
  analogWrite(B_PIN, 0);

  delay(3000);

  Serial.println("Green");
  analogWrite(R_PIN, 0);
  analogWrite(G_PIN, 255);
  analogWrite(B_PIN, 0);

  delay(3000);

  Serial.println("Blue");
  analogWrite(R_PIN, 0);
  analogWrite(G_PIN, 0);
  analogWrite(B_PIN, 255);

  delay(3000);*/
}
