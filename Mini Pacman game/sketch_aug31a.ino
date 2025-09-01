long t = 0;
long t2 = 0;
int debounce_delay = 250;
int pin[] = {2, 3, 4, 5};
char space = ' ';
String distance = "";
char dir;
const int lines_default = 26;
int lines_up = 7;
int lines_down = 7;

void direzione();
void pacman();

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 4; i++){
    pinMode(pin[i], INPUT_PULLUP);
  }
}

void loop() {
  direzione();
  if((millis() - t2) >= 500){
    pacman();
    t2 = millis();
  }
}

void direzione(){  // it storages the direction of the pacman
  const char pac[] = {'^', '<', 'v', '>'};  // defines how the pacman can be
  for(int i = 0; i < 4; i++){                   // controls if the
    if(digitalRead(pin[i]) == LOW){              // direction changes 
      if((millis() - t) >= debounce_delay){  // debounce for the buttons
        dir = pac[i];  // storages the direction
        t = millis();
      }
    }  
  }
}

void pacman(){  // it upgrades the pacman's position and prints the pacman
  bool basso = false;
  switch(dir){
    case '>':  // if the direction is right, it addes spaces to move the pacman right
      if(distance.length() < 60){
        distance.concat(space);
      }
      break;
    case '<':  // if the direction is left, it removes spaces to move the pacman left
      distance.remove(1,1);
      break;
    case 'v':  // if the direction is down, it addes lines to move the pacman down
        lines_up++;
        lines_down--;
        break;
    case '^':  // if the direction is up, it sobtracts lines to move the pacman up
      if(lines_up != 0){
        lines_up--;
        lines_down++;
      }
      break;
  }
  for(int i = 1; i <= lines_default; i++){  //creates the empty lines to upgrade the field
    Serial.println();
  }
  for(int j = 1; j <= lines_up; j++){
    Serial.println();
  }
  Serial.print(distance); //shows the distance of the pacman
  Serial.print(dir);      //shows the pacman
  for(int y = 1; y <= lines_down; y++){
    Serial.println();
  }
}