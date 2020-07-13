#define NUM_COMPONENTS 4
#define MAX_LEVEL 10

const int button[NUM_COMPONENTS] = {2,3,4,5};
const int led[NUM_COMPONENTS] = {6,7,8,9};

int sequence[MAX_LEVEL];

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < NUM_COMPONENTS; i++){
    pinMode(button[i], INPUT);
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
  }
}

void loop() {
  bool didPlayerLose;
  randomSeed(analogRead(0));
  
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
    delay(1000); 
    digitalWrite(led[sequence[i]], LOW);
    delay(1000); 
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
        }
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
