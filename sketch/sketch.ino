#define PIN_STEP 3  // Step pin from engine driver.
#define PIN_DIR  2  // Direction pin from engine driver.
#define PIN_RES  A1 // Pin from resistor.

int SPEED = 1; // Current speed.

// "Speeds" list.
int SPEEDS[] = { 
  1,          // Max speed (to left).
  56,   56,   // 16 mm/min speed (to left).
  84,   84,   // 12 mm/min speed (to left).
  112,  112,  // 8  mm/min speed (to left).
  168,  168,  // 6  mm/min speed (to left).
  224,  224,  // 4  mm/min speed (to left).
  336,  336,  // 3  mm/min speed (to left).
  448,  448,  // 2  mm/min speed (to left).
  0,    0,    // Stop.
  -448, -448, // 2  mm/min speed (to right).
  -336, -336, // 3  mm/min speed (to right).
  -224, -224, // 4  mm/min speed (to right).
  -168, -168, // 6  mm/min speed (to right).
  -112, -112, // 8  mm/min speed (to right).
  -84,  -84,  // 12 mm/min speed (to right).
  -56,  -56,  // 16 mm/min speed (to right).
  -1          // Max speed (to right).
};

//Count elements of "Speeds" list.
int SIZE_SPEEDS = (
  sizeof(SPEEDS) / sizeof(int *)
); 

void setup() {
  pinMode(PIN_STEP, OUTPUT); // Initialization Step pin.
  pinMode(PIN_DIR, OUTPUT); // Initialization Dir pin.
  pinMode(PIN_RES, INPUT); // Initialization Resistor pin.
  //Serial.begin(9600); // Initialization Serial (disabled).
}

void loop() {
  // Set current speed.
  SPEED=SPEEDS[
    round(
      analogRead(PIN_RES) / SIZE_SPEEDS
    )
  ];
  
  if(SPEED!=0){
    // Change direction.
    if(SPEED<0){ // To right.
      SPEED=SPEED*-1;
      digitalWrite(PIN_DIR, LOW);
    }else{ // To left.
      digitalWrite(PIN_DIR, HIGH);
    }

    // Step.
    digitalWrite(PIN_STEP, HIGH);
    delay(SPEED);
    digitalWrite(PIN_STEP, LOW);
    delay(SPEED);

    //logs(); // Print logs (disabled).
  }
}

void logs() {
  Serial.print("Speed: ");
  Serial.print(SPEED);
  Serial.print(" | Resistor: ");
  Serial.print(analogRead(PIN_RES));
  Serial.print(" | Current 'Speeds': ");
  Serial.print(
    round(
      analogRead(PIN_RES) / SIZE_SPEEDS
    )
  );
  Serial.print(" | Count 'Speeds': ");
  Serial.println(SIZE_SPEEDS);
}