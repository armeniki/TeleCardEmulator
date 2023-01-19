// QuickChange/TeleCard Emulator
// v0.5
// 15 Jan 2023
// Tested on an Arduino Pro Mini 5V 16MHz

#define pin_RESET     3   
#define pin_CLK       2   
#define pin_DATA      5 


//This array is populated with a 16 byte QuickChange or TeleCard number.
byte cardbytes[16] = { 0x99, 0x28, 0x1c, 0x02, 0xa1, 0xb3, 0x8d, 0xf4, 0x00, 0x00, 0x11, 0x77, 0x0f, 0xff, 0xff, 0xff }; //test card data

volatile int indexByte = 0;  //To keep track of current byte being read
volatile int indexBit = 0; //To keep track of current bit being read

volatile bool outputBit = 0; //Currently read bit to be sent out
volatile byte outputByte = 0; //Byte to use for reading its bits

bool status_Reset = 0; //Card's ATR/Reset status
bool flag_Reset = 0; //Used to complete Reset sequence

bool line_CLK;  //Data from reading Clock pin
bool line_RESET; //Data from reading Reset pin


void setup()
{
	Serial.begin(115200);  //Open serial port
	Serial.print("TeleCard Emulator - Started\n"); //Indicate sketch is running

	pinMode(pin_CLK, INPUT_PULLUP); //Set pin modes
	pinMode(pin_RESET, INPUT_PULLUP); // "  "
	pinMode(pin_DATA, OUTPUT); // "  "
	digitalWrite(pin_DATA, 0); //Start with DATA line low
	attachInterrupt(digitalPinToInterrupt(pin_CLK), sendBits, RISING);  //Used to run ISR
}

void loop()
{
	line_CLK = digitalRead(pin_CLK);  //Keep logical level in variable to avoid reading multiple times
	line_RESET = digitalRead(pin_RESET); // "             "             "             "             "


	//This is the very basic card reset routine
	if (line_RESET == 1){
		if (line_CLK == 1){
			flag_Reset = 1;
		}
		if (line_CLK == 0 && flag_Reset == 1){
			ResetCard();
		} //Once the flag is set and CLOCK goes low, call the ResetCard function
	}
}


void ResetCard(){
	Serial.println("Reset Called");
	flag_Reset = 0;
	indexByte = 0;
	indexBit = 0;
	status_Reset = 1;
}


void sendBits()
{
	outputByte = (cardbytes[indexByte]);
	outputBit = bitRead(outputByte, indexBit); //MSB sent out first

	if (outputBit == 1){
		digitalWrite(pin_DATA, 1);
	}
	else
	{
		digitalWrite(pin_DATA, 0);
	}

	indexBit++;  //Increment the bit index for the next use by the bitRead function		

	if (indexBit == 8){  //Once all 8 bits have been read, time to go to the next byte in the array and reset the bit index
		indexByte++;
		indexBit = 0;
	}

	if (indexByte == 16){ //Once all 16 bytes have been read, set the index back to 0
		indexByte = 0;
	}


}

