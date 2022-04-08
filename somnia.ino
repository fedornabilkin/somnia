#define DEBOUNCE 100
// led
int LED_RED = 9;
int LED_BLUE = 10;
int LED_GREEN = 11;
int LED_DEFAULT = 13;
int BTN = 12;

int a, c, d, ledActive, timeActive, ledState = 0;
bool flag = false;

uint32_t btnTimer, ledTimer, fixTimer = 0;

int looper, sleep, mode = 0;

// green, red, blue, red, loop
int modes[][5] = {
  {4000, 7000, 8000, 0, 10}, // 4-7-8
  {5000, 0, 5000, 0, 8}, // 5-5
  {2000, 0, 4000, 0, 15}, // 2-4
  {4000, 4000, 4000, 4000, 5}, // 4-4-4-4 square
  {2000, 2000, 2000, 2000, 5}, // test
};
int leds[4] = {LED_GREEN, LED_RED, LED_BLUE, LED_RED};


// setup
void setup()
{
  pinMode(BTN, INPUT);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_DEFAULT, OUTPUT);
  digitalWrite(LED_DEFAULT, LOW);
  
  sleep = modes[mode][4];
  
  //test
  Serial.begin(9600);
  Serial.println("setup");
  //test
}

// loop
void loop()
{  
  // читаем значение
  bool btnState = digitalRead(BTN);
  
  if (btnState && !flag && millis() - btnTimer > DEBOUNCE) {
    flag = true;
    btnTimer = millis();
    
    flashOut();
    modeChange();
    clear();
    fixTimer = millis();
    return;
  }
  if (!btnState && flag && millis() - btnTimer > DEBOUNCE) {
    flag = false;
    btnTimer = millis();
  }
  
  if (looper >= sleep) {
    clear();
    analogWrite(LED_BLUE, 255/4);
    return;
  }
  
  //active
  ledActive = leds[ledState];
  timeActive = modes[mode][ledState];
  
  createTiming(timeActive);

  if(timeActive < 2000){
    ledState += 1;
    return;
  }
  
  ledTimer = millis() - fixTimer;
  if (ledTimer >= timeActive) {
    fixTimer = millis();
    
    digitalWrite(ledActive, LOW);
    ledState += 1;
  } else {
    digitalWrite(ledActive, HIGH);
    if (ledTimer >= a && ledTimer <= a + d) {
      digitalWrite(ledActive, LOW);
    }
    if (ledTimer >= a+d+c && ledTimer <= a + c + d*2) {
      digitalWrite(ledActive, LOW);
    }
  }
  
  if (ledState > 3) {
    ledState = 0;
    looper += 1;
  }
  
}

// other
void clear()
{
  ledActive = 0;
  timeActive = 0;
  ledState = 0;
  ledTimer = 0;
  looper = 0;
}

void flashOut()
{
  int cnt = sizeof(leds) / sizeof(leds[0]);
  for (int i = 0; i < cnt; i++) {
    digitalWrite(leds[i], LOW);
  }
}

void modeChange()
{
  mode += 1;
  int cnt = sizeof(modes) / sizeof(modes[0]);
  if (mode > cnt) {
    mode = 0;
  }
  
  sleep = modes[mode][4];
  
  for (int i = 0; i < mode + 1; i++) {
    digitalWrite(LED_DEFAULT, HIGH);
    delay(250);
    digitalWrite(LED_DEFAULT, LOW);
    delay(250);
  }
}

void createTiming(int ledTime)
{
  d = 250;

  if(ledTime >= 5000){
    d = 300;
  }
  if(ledTime >= 7000){
    d = 350;
  }
  if(ledTime >= 8000){
    d = 400;
  }

  a = (ledTime - d) / 2;
  c = a - 3 * d;
}
