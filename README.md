# TeleCardEmulator
This is an Arduino sketch, in its preliminary stages, meant to allow the testing of smartcard readers found in some payphones.  Although payphones are no longer commonly found, there are many telephone enthusiasts who collect them.  Of particular interest to myself is the Nortel Millennium payphone.  Many of those payphones are equipped with smartcard readers which can be used to pay for telephone calls.  I have put together another repository in relation to the Millennium payphone.

It should be noted that this program will *not* allow free telephone calls to be made as payphones require authenticaton of the card via various encryption keys which will not be discussed.  However, if you have a working payphone at home and would like to tinker with it and test its card reader, this program is what you are looking for.

### Hardware Required
1. Ardiuno Pro Mini (5V 16Mhz)
2. Smartcard-shaped PCB like this one ![alt text](https://raw.githubusercontent.com/armeniki/TeleCardEmulator/main/pics/pcb_card.jpg "Smartcard PCB") 

The wiring is straight forward with 5 connections required from the Arduino to the PCB:
1. 5V
2. GND
3. CLOCK
4. DATA
5. RESET

Please refer to the ISO-7816 standard and enclosed instructions to determine the positions of these pins on the PCB you are using.


## Limitations
At this point, the emulator will only data to allow the payphone terminal to recognise it and display the monetary units available.  Making this work also depends on the type of payphone you are using.  


### Authentication
There is an authentication mechanism which is used to let the payphone know that the card is legitimate and can be used to pay for the call.  This process involves an 8-byte DES key stored in the payphone, which is used to authenticate the card.  In addition, once this is done, the payphone also checks that the card's serial number is within the range of accepted cards.  This is because some telcos use the same DES key to decrypt/authenticate these cards and simlpy restrict their use via card number ranges.  This is something that I have not implemented in this release.


