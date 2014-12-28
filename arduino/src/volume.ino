static unsigned int volumeServoZero=45;
static unsigned int volumeServoUp=38;
static unsigned int volumeServoDown=50;
static unsigned int powerServoUnpressed=90;
static unsigned int powerServoPressed=60;
static unsigned int filter_alpha = 5;
static unsigned int redPin=3;
static unsigned int greenPin=6;
static unsigned int bluePin=5;
static unsigned int volumeServoPin = 9;
static unsigned int powerServoPin = 10;
static unsigned int powerToggleCooldown=5000;

#include <Servo.h>

Servo volumeServo, powerServo;

int pingPin = A0;

boolean stereoIsOn=false;
long lastToggleTime=0;

enum interface_states { //default state should be "get_data"
	inactive,
	volume_down,
	volume_up,
	toggle_power
};

interface_states state;

void setup()
{
	Serial.begin(115200);

	powerServo.attach(powerServoPin);
	volumeServo.attach(volumeServoPin);

	volumeServo.write(volumeServoZero);

	pinMode(pingPin, INPUT);
	pinMode(redPin, OUTPUT);
	pinMode(greenPin, OUTPUT);
	pinMode(bluePin, OUTPUT);
}

	unsigned int ping=255;

	//store 3 preceding readings to calculate change over time.
	int lastPing=0;
	int lastLastPing=0;
	int lastLastLastPing=0;
	int sumOfChanges=0;
	static int allowablePingOffset=2;
	unsigned long rolloverTimeout=50; //time it takes between iterations of loading values into the "last ping" integer set
	unsigned long millisAtLastRollover=0;

	boolean allowStateChange=false;

void loop()
{
  //moving average filter:
  ping = (ping * filter_alpha + analogRead(pingPin)) / (filter_alpha+1);
   //ping=analogRead(pingPin);

  //check that change in ping isn't too steep to allow state change.

  //it kind of looks like i am doing the same thing (low pass filtering) twice, but i need to store the last couple of values in order to determine the rate of change.
  if(millis()-rolloverTimeout>millisAtLastRollover)
  {
  	lastLastLastPing=lastLastPing;
  	lastLastPing=lastPing;
  	lastPing=ping;

	sumOfChanges=(lastLastPing-lastLastLastPing)+(lastPing-lastLastPing)+(ping-lastPing);

  	millisAtLastRollover=millis();

  	Serial.print("lastLastLastPing: ");
  	Serial.println(lastLastLastPing);
  	Serial.print("lastLastPing: ");
  	Serial.println(lastLastPing);
  	Serial.print("lastPing: ");
  	Serial.println(lastPing);
  	Serial.print("Sum of changes: ");
  	Serial.println(sumOfChanges);
  	Serial.print("ping: ");
  	Serial.println(ping);
  	Serial.println();
  	Serial.print("Change allowed: ");
  	if(allowStateChange) Serial.println("TOTALLY!");
  	else Serial.println("NOT!");
  }

  /*
  if(sumOfChanges==0) allowStateChange=true;
  else allowStateChange=false;
*/

  if(sumOfChanges>allowablePingOffset) allowStateChange=false;
  else if (sumOfChanges<(-1*allowablePingOffset)) allowStateChange=false;
  else allowStateChange=true;




if (allowStateChange)
{
  if(ping>200) state=inactive;
  else if(ping>140) state=volume_down;
  else if(ping>70) state=volume_up;
  else if(ping>20) state=toggle_power;

}
/*
  Serial.print("ping graph: ");
  for(int i = 0; i<ping/2;i++) Serial.print('-');
  Serial.print("| ");
  Serial.println(ping);
*/



switch(state)
{
	case volume_down:
		setcolour(255,40,0);
		volumeServo.write(volumeServoDown);
		break;

	case volume_up:
		setcolour(0,255,0);
		volumeServo.write(volumeServoUp);
		break;

	case toggle_power:
		setcolour(0,0,255);
		if(millis()-lastToggleTime>powerToggleCooldown)
			{
				onOff();
				lastToggleTime=millis();
			}

		break;
	case inactive:
		volumeServo.write(volumeServoZero);
		if(stereoIsOn) setcolour(255,255,255); //white
		else setcolour(255,0,0); //red
		break;
}

 //standby_light();
  //onOff();
  //delay(1000);
  //volumeServo.write(volumeServoDown);
}


void setcolour(int red,int green,int blue)
{
	analogWrite(redPin,red);
	analogWrite(greenPin,green);
	analogWrite(bluePin,blue);
}

void pulse_colour(int red,int green,int blue,int delaytime)
{
int i;


    for(i=0;i<255;i++)
    {
    	setcolour(map(red, 0, 255, 0, i),map(green, 0, 255, 0, i),map(blue, 0, 255, 0, i));
    	delay(delaytime);
    }

    for(i=255;i>0;i--)
    {
    	setcolour(map(red, 0, 255, 0, i),map(green, 0, 255, 0, i),map(blue, 0, 255, 0, i));
    	delay(delaytime);
    }


    setcolour(0,0,0);
}

void standby_light()
{
	pulse_colour(255,0,0,25);
  	delay(2000);
}

void onOff()
{
stereoIsOn=!stereoIsOn; //invert power state

powerServo.write(powerServoPressed);
delay(150);
powerServo.write(powerServoUnpressed);
}
