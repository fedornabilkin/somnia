
int LED_RED = 9;
int LED_BLUE = 10;
int LED_GREEN = 11;

int looper = 0;
int sleep = 10;
int modeTime = 19000;
int rgbTimes[] = {4000, 7000, 8000};

// setup
void setup()
{
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(13, OUTPUT);
}

// loop
void loop()
{
  looper += 1;
  
  if (looper >= sleep) {
    flash(13, 4000);
    return;
  }

  
  flash(LED_GREEN, rgbTimes[0]);
  flash(LED_RED, rgbTimes[1]);
  flash(LED_BLUE, rgbTimes[2]);
  
}

// other
void flash(int pin, int ledTime)
{
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
