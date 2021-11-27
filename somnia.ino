
int LED_RED = 9;
int LED_BLUE = 10;
int LED_GREEN = 11;
int LED_DEFAULT = 13;

int looper = 0;
int sleep = 0;
int mode = 3;
// green, red, blue, loop
int rgbTimes[][5] = {
  {4000, 7000, 8000, 0, 10}, // 4-7-8
  {5000, 0, 5000, 0, 8}, // 5-5
  {2000, 0, 4000, 0, 15}, // 2-4
  {4000, 4000, 4000, 4000, 5}, // 4-4-4-4 square
};



// setup
void setup()
{
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_DEFAULT, OUTPUT);
  digitalWrite(LED_DEFAULT, LOW);
}

// loop
void loop()
{
  looper += 1;
  sleep = rgbTimes[mode][4];
  
  if (looper >= sleep) {
    //analogWrite(LED_BLUE, 255/4);
    return;
  }

  
  flash(LED_GREEN, rgbTimes[mode][0]);
  flash(LED_RED, rgbTimes[mode][1]);
  flash(LED_BLUE, rgbTimes[mode][2]);
  flash(LED_RED, rgbTimes[mode][3]);
  
}

// other
void flash(int pin, int ledTime)
{
  if(ledTime < 2000){
    return;
  }
  
  pinMode(pin, OUTPUT);

  int d = 250;

  if(ledTime >= 5000){
    d = 300;
  }
  if(ledTime >= 7000){
      d = 350;
  }
  if(ledTime >= 8000){
      d = 400;
  }

  int a = (ledTime - d) / 2;
  int c = a - 3 * d;

  digitalWrite(pin, HIGH);
  delay(a);
  digitalWrite(pin, LOW);
  delay(d);
  digitalWrite(pin, HIGH);
  delay(c);
  digitalWrite(pin, LOW);
  delay(d);
  digitalWrite(pin, HIGH);
  delay(d);
  digitalWrite(pin, LOW);
  delay(d);
}
