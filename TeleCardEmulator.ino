// QuickChange/TeleCard Emulator
// v1.1
// (C) 2023 armeniki
// https://github.com/armeniki/TeleCardEmulator/
// 25 Jan 2023
// Tested on an Arduino Pro Mini 5V 16MHz

//#define DEBUG  //Running with DEBUG may adversely affect data speeds

#define pin_RESET     3   
#define pin_CLK       2   
#define pin_DATA      5 

//This array is populated with a 16 byte QuickChange or TeleCard number.
//NB: Your terminal may or may not recognise this card number and depends on the entries in your terminal's card tables.
byte cardbytes[16] = { 0x99, 0x28, 0x1c, 0x02, 0xa1, 0xb3, 0x8d, 0xf4, 0x00, 0x00, 0x11, 0x77, 0x0f, 0xff, 0xff, 0xff };
byte cardbits[128];

byte indexByte = 0;  //To keep track of current byte being read
uint8_t indexBit = 0; //To keep track of current bit being read
bool flagReset = 0; //Used to complete Reset sequence
bool line_CLK;  //Data from reading Clock pin
bool line_RESET; //Data from reading Reset pin
uint8_t addressBit = 0;


void setup()
{
#ifdef DEBUG
	Serial.begin(115200);  //Open serial port
	Serial.print("TeleCard Emulator - Started\n"); //Indicate sketch is running
#endif DEBUG
	pinMode(pin_CLK, INPUT_PULLUP); //Set pin modes
	pinMode(pin_RESET, INPUT_PULLUP); // "  "
	pinMode(pin_DATA, OUTPUT); // "  "
	digitalWrite(pin_DATA, 1); //Data line stays high normally
	attachInterrupt(digitalPinToInterrupt(2), processBit, FALLING);
	cardBytesToBits();


}
void loop()
{

	line_CLK = bitRead(PIND, PIND2);
	line_RESET = bitRead(PIND, PIND3);

	//Check if reset is requested
	if (line_RESET == 1 && line_CLK == 0){
		flagReset = 1; //We set a flag to clear
	}
	if (line_RESET == 0 && line_CLK == 0 && flagReset){
		flagReset = 0;
		resetCard();
	}


}

void processBit(){

	if (line_RESET == 0){ //DATA does not go out during RESET high
		addressBit++;
		if (cardbits[addressBit] == 1){
			PORTD |= _BV(PB5); //write port HIGH
		}
		if (cardbits[addressBit] == 0){
			PORTD &= ~_BV(PB5); //write port LOW


		}
	}

	if (line_RESET == 1){
		cardbits[addressBit] = digitalRead(pin_DATA);
	
	}

}

void resetCard(){
#ifdef DEBUG
	Serial.println("Reset Called");
#endif
	digitalWrite(pin_DATA, 1);
	flagReset = 0;
	indexByte = 0;
	indexBit = 0;
	addressBit = 0;

}
void cardBytesToBits(){

	//Store card bytes into bit array for easy management
	char string[100];
	indexBit = 7;
	int c = 0;
	int i = 0;

	for (i = 0; i < 128; i++)
	{

		cardbits[i] = bitRead(cardbytes[c], indexBit);

#ifdef DEBUG
		snprintf(string, sizeof(string), "Card byte: 0x%02X, Index bit: %u, Counter: %u, Bit Setting: %u\n", cardbytes[c], indexBit, i, cardbits[i]);
		Serial.print(string);
#endif


		if (indexBit == 0x00){
			indexBit = 8;
			c++;
		}
		indexBit--;


	}

}