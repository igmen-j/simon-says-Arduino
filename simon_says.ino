#define NUM_COMPONENTS 4
#define MAX_LEVEL 10

const int button[NUM_COMPONENTS] = {2,3,4,5};
const int led[NUM_COMPONENTS] = {6,7,8,9};

int currentLevel = 0;
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
  startSequence();
  //delay(2000);  //2 second delay
  getSequence(currentLevel, sequence);
  showSequence(currentLevel, sequence);
  /*
  for (int i = 0; i < NUM_COMPONENTS; i++)
  {
    if (digitalRead(button[i]))
      digitalWrite(led[i], HIGH);
    else
      digitalWrite(led[i], LOW);
  }
  */

}

void startSequence(){
  // start sequences goes here
  // LED and sounds 
}

void getSequence(int currentLevel, int sequence[]) {
  long randNum = random(100);
  randNum %= 4;
  Serial.println(randNum);
  sequence[currentLevel] = randNum;  
}

void showSequence(int currentLevel, int sequence[]) {
  digitalWrite(led[sequence[currentLevel]], HIGH);
  delay(1000); 
     for (int i = 0; i < NUM_COMPONENTS; i++){

    digitalWrite(led[i], LOW);
  }
    delay(1000);
}
