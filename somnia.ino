int LED_RED = PB4;
int LED_BLUE = PB3;
int LED_GREEN = PB5;
int BTN = PB1;

int looper, mode, timeActive, ledState = 0;
uint32_t btnTimer, fixTimer = 0;

// green, red, blue, red, loop
int modes[][5] = {
  {4000, 7000, 8000, 0, 10}, // 4-7-8
  {5000, 0, 5000, 0, 8}, // 5-5
  {2000, 0, 4000, 0, 15}, // 2-4
 {4000, 4000, 4000, 4000, 5}, // 4-4-4-4 square
};
int leds[4] = {LED_GREEN, LED_RED, LED_BLUE, LED_RED};

// setup
void setup()
{
  pinMode(BTN, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
}

// loop
void loop()
{
  bool btnState = digitalRead(BTN);
  int sleep = modes[mode][4];
  
  if (btnState && millis() - btnTimer > 100) {
    flashOut();
    modeChange();
    timeActive = ledState = looper = 0;
    fixTimer = btnTimer = millis();
    return;
  }
  
  if (looper >= sleep) {
    analogWrite(LED_BLUE, 255/10);
    return;
  }
  
  bool ledFlash = LOW;
  int ledActive = leds[ledState];
  timeActive = modes[mode][ledState];

  if(timeActive < 2000){
    ledState += 1;
    return;
  }
  
  int d = (timeActive >= 5000) ? 350 : 250;
  int a = (timeActive - d) / 2;
  int c = a - 3 * d;
  
  uint32_t ledTimer = millis() - fixTimer;
  if (ledTimer >= timeActive) {
    fixTimer = millis();
    ledState += 1;
  } else {
    if ((ledTimer >= a && ledTimer <= a + d) || (ledTimer >= a+d+c && ledTimer <= a + c + d*2)) {
      ledFlash = LOW;
    } else {
      ledFlash = HIGH;
    }
  }
  
  if (ledState > 3) {
    ledState = 0;
    looper += 1;
  }

  digitalWrite(ledActive, ledFlash);
}

// other
void flashOut()
{
  int cnt = sizeof(leds) / sizeof(leds[0]);
  for (int i = 0; i <= cnt; i++) {
    digitalWrite(leds[i], LOW);
  }
}

void modeChange()
{
  mode += 1;
  int cnt = sizeof(modes) / sizeof(modes[0]);
  mode = (mode > cnt-1) ? 0 : mode;
  
  for (int i = 0; i <= mode; i++) {
    digitalWrite(LED_RED, HIGH);
    delay(250);
    digitalWrite(LED_RED, LOW);
    delay(250);
  }
}
