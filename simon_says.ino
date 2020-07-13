#define NUM_COMPONENTS 4
#define MAX_LEVEL 16

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
  randomSeed(analogRead(0));
}

void loop() {
  bool endCondition;
  
  startSequence();
  //delay(2000);  //2 second delay
  getSequence();
  endCondition = startGame();

  if (endCondition == true)
    loseSequence();
  else
    winSequence();
    
  delay(100000000);
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
  Serial.println("sequence:");
  for (int i = 0; i < MAX_LEVEL; i++) {
    randNum = random(4);
    
    while ((randNum == sequence[i-1]) && (sequence[i-1] == sequence[i-2])){   //Loop so that value cannot appear more than 2 times
      randNum = random(4);
    }
     
    sequence[i] = randNum;  
    Serial.println(sequence[i]);
  }
  Serial.println("done");
  
  return;
}

bool startGame(){
  int userVal, currentVal = 0, currentLevel = 0, lives = 3;
  bool isGameOver = false, endCondition;

  while ((isGameOver == false) || (currentLevel == MAX_LEVEL))
  {
    showSequence(currentLevel);

    Serial.print("Level: ");
    Serial.println(currentLevel+1);
    Serial.print("Lives: ");
    Serial.println(lives);
  
    while (currentVal != currentLevel+1){
      userVal = getUserInput();
      if (compareValue(currentVal, userVal) == true){
        currentVal++;
      }
      else{
        lives--;
        if (lives != 0)
          currentVal = 0;
        else{
          isGameOver = true;
          endCondition = true;
          break;
        }
      }
    }
    
    if (isGameOver == false){
      currentLevel++;
      if (currentLevel == endCondition)
        endCondition == false;
    }
  }

  return endCondition;
}




/*
 * Displays the generated sequence
 */
void showSequence(int currentLevel) {
  for (int i = 0; i < currentLevel+1; i++){
    digitalWrite(led[sequence[i]], HIGH);
    delay(1000); 
    digitalWrite(led[sequence[i]], LOW);
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
    for (int i = 0; i < NUM_COMPONENTS; i++){
      digitalWrite(led[i], HIGH);
    }
    delay(1000); 
    for (int i = 0; i < NUM_COMPONENTS; i++){
    digitalWrite(led[i], LOW);
    }
    return true;
  }
  else
    return false;
}

void loseSequence(){
  
}

void winSequence(){
  
}
