#define NUM_COMPONENTS 4
#define MAX_LEVEL 10
#define TIME_IN_BETWEEN 500

const int button[NUM_COMPONENTS] = {2,3,4,5};
const int led[NUM_COMPONENTS] = {6,7,8,9};
const int ledLives[3] = {10,11,12};
const int buzzer = 13;

int sequence[MAX_LEVEL];

void setup() {
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  for (int i = 0; i < NUM_COMPONENTS; i++){
    pinMode(button[i], INPUT);
    pinMode(led[i], OUTPUT);   
    digitalWrite(led[i], LOW);
  }

  for (int i = 0; i < 3; i++) {
    pinMode(ledLives[i], OUTPUT);
    digitalWrite(ledLives[i], LOW);
  }
  noTone(buzzer);
}

void loop() {
  bool didPlayerLose;
  randomSeed(analogRead(0));

  noTone(buzzer);
  
  startSequence();
  //delay(2000);  //2 second delay
  getSequence();
  didPlayerLose = startGame();

  Serial.print("Win or Lose: ");
  Serial.println(didPlayerLose);
  Serial.println();

  if (didPlayerLose == true)
    loseSequence();
  else
    winSequence();
    
  delay(10000);
}

void startSequence(){
  // start sequences goes here
  // LED and sounds 
}

/*
 * Generates a random numbers and stores it in an array -- not truly random
 */
void getSequence() {
  int randNum;
  //Serial.println("sequence:");
  for (int i = 0; i < MAX_LEVEL; i++) {
    randNum = random(4);
    
    while ((randNum == sequence[i-1]) && (sequence[i-1] == sequence[i-2])){   //Loop so that value cannot appear more than 2 times
      randNum = random(4);
    }
     
    sequence[i] = randNum;  
    //Serial.println(sequence[i]);
  }
  //Serial.println("done");
  
  return;
}

bool startGame(){
  int userVal, currentVal = 0, currentLevel = 0, lives = 3;
  bool isGameOver = false, didPlayerLose;

  for (int i = 0; i < 3; i++) {
    digitalWrite(ledLives[i], HIGH);
  }

  while ((isGameOver == false) || (currentLevel < MAX_LEVEL))
  {
    Serial.print("Level: ");
    Serial.println(currentLevel+1);

    currentVal = 0;
    showSequence(currentLevel);
    while (currentVal != currentLevel+1){

      if (lives == 0){
        isGameOver = true;
        didPlayerLose = true;
        currentLevel = MAX_LEVEL;
        break;
      }
      
      Serial.print("Lives: ");
      Serial.println(lives);
      
      userVal = getUserInput();
      if (compareValue(currentVal, userVal) == true){
        currentVal++;
      }
      else{
        lives--;

        switch (lives) {
          case 2:
            digitalWrite(ledLives[0], HIGH);
            digitalWrite(ledLives[1], HIGH);
            digitalWrite(ledLives[2], LOW);
            break;
          case 1:
            digitalWrite(ledLives[0], HIGH);
            digitalWrite(ledLives[1], LOW);
            digitalWrite(ledLives[2], LOW);
            break;
          case 0:
            digitalWrite(ledLives[0], LOW);
            digitalWrite(ledLives[1], LOW);
            digitalWrite(ledLives[2], LOW);
            break;
        }

        delay(1000);
        if (lives > 0) {
          currentVal = 0;
          showSequence(currentLevel);
          //break;
        }
        else{
          isGameOver = true;
          didPlayerLose = true;
          break;
        }
      }
    }

    delay(500);
    
    if (isGameOver == false){
      currentLevel++;
      if (currentLevel >= MAX_LEVEL) {
        didPlayerLose = false; //they beat the game!
        break;
      }
    }
    else
      break;
  }

  return didPlayerLose;
}

/*
 * Displays the generated sequence
 */
void showSequence(int currentLevel) {
  for (int i = 0; i < currentLevel+1; i++){
    digitalWrite(led[sequence[i]], HIGH);

    switch (sequence[i]) {
    case 0: //red
      tone(buzzer, 440);
      break;
    case 1: //yellow
      tone(buzzer, 277);
      break;
    case 2: //blue
      tone(buzzer, 330);
      break;
    case 3: //green
      tone(buzzer, 349);
      break;
    }
    delay(TIME_IN_BETWEEN); 
    
    noTone(buzzer);
    digitalWrite(led[sequence[i]], LOW);
    if (i < currentLevel)
      delay(TIME_IN_BETWEEN); 
  }

  return;
}

//need to put timer here too!
int getUserInput() {
  bool buttonPressed = false;
  int userVal;
  while (!buttonPressed){
    for (int i = 0; i < NUM_COMPONENTS; i++) {
      if (digitalRead(button[i])) {
        while(digitalRead(button[i])){
          digitalWrite(led[i], HIGH);
          switch (i) {
            case 0: //red
              tone(buzzer, 440);
              break;
            case 1: //yellow
              tone(buzzer, 277);
              break;
            case 2: //blue
              tone(buzzer, 330);
              break;
            case 3: //green
              tone(buzzer, 349);
              break;
            }
        }
        noTone(buzzer);
        digitalWrite(led[i], LOW);
        buttonPressed = true;
        userVal = i;
        break;
      }
    }
  }
  return userVal;
}

/*
 * Compares if input value is the same, return true -- current state: turn on all lights if correct
 * If not, return false
 */
bool compareValue(int currentVal, int userVal){
  if (sequence[currentVal] == userVal) {
    return true;
  }
  else
    return false;
}

void loseSequence(){
  Serial.println("lose");
}

void winSequence(){
  Serial.println("win");  
}
