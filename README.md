# TeleCard (SLE4406) Emulator
This is an Arduino sketch, in its preliminary stages, meant to allow the testing of smartcard readers found in some payphones.  Although payphones are no longer commonly found, there are many telephone enthusiasts who collect them.  Of particular interest to myself is the Nortel Millennium payphone.  Many of those payphones are equipped with smartcard readers which can be used to pay for telephone calls.  I have put together another repository in relation to the Millennium payphone.

It should be noted that this program will *not* allow free telephone calls to be made on any payphone.  Each payphone has its own security features which will not be discussed here.  However, if you have a similar working payphone at home and would like to tinker with it and test its card reader, this program is what you are looking for.  It has been tested working on a multipay (type 29) terminal.

### Hardware Required
1. Ardiuno Pro Mini (5V 16Mhz)
2. Smartcard-shaped PCB like this one ![alt text](https://raw.githubusercontent.com/armeniki/TeleCardEmulator/main/pics/pcb_card.jpg "Smartcard PCB") 

The wiring is straight forward with 5 connections required from the Arduino to the PCB:
1. 5V
2. GND
3. CLOCK
4. DATA
5. RESET

Please refer to the ISO-7816 standard and any enclosed instructions to determine the positions of the pins on the PCB you are using.


## Limitations
At this point, the emulator code allows the payphone terminal to recognise it and display the monetary units available.  Once a number is dialled, the terminal will attempt a write operation on the respective bits, however, that is not implemented in this code at the moment.  I will implement a decrementing counter routine as time permits.  


### Authentication
There is an authentication mechanism which is used to let the payphone know that the card is legitimate and can be used to pay for the call.  It is a fairly simple one that is all computed in the payphone terminal itself, mainly through bit shifting.  Once this is done, the payphone also checks that the card's number is within the range of accepted cards.  Please bear in mind that the functionality of this code depends on the type of payphone you are using and several security settings.  
