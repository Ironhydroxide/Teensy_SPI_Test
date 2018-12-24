//----------------------------------------------------
//Testing SPI from Teensy 3.6 to NHD 7" cap Touch with FT813
//https://www.mouser.com/datasheet/2/291/NHD-7.0-800480FT-CSXN-CTP-1219227.pdf
// what		-	Teensy 	- 	NHD
// SS/CS	-	10(dig)	-	IDC 6
// MOSI0	-	11(dig)	-	IDC 5
// MISO0	-	12(dig)	-	IDC 4
// SCK0		-	13(dig) -	IDC 3
// PD		-	8(dig)	-	IDC 8 (power down pin, input to display)
// INT		-	15(dig)	-	IDC 7 (interrupt pin, output to Teensy)

//-------------------------------------------------------------------
// Teensy connections
//
#include <SPI.h>  // include the SPI library:

const int slaveSelectPin = 10;//Set pin 10 as slaveSelectPin
const int SPISpeed = 30000000;//set SPI Speed (30mhz for FT813)
#define SPIDATADIRECTION MSBFIRST
#define SPIDATAMODE SPI_MODE1

//setup Speed, endianness, and mode of SPI.
SPISettings FT813(SPISpeed, SPIDATADIRECTION, SPIDATAMODE);

void setup() {
	//setup variables for chip ID
	uint8_t firstByte, secondByte, thirdByte, fourthByte;
	uint32_t IDAddress = 0x0C0003;
	
	// set the slaveSelectPin as an output:
	pinMode (slaveSelectPin, OUTPUT);
	// initialize SPI:
	SPI.begin(); 
	
	//ReadID from FT81X chip  
	/* 
	For SPI memory read transactions, the host sends two zero bits, followed by the 22-bit address. 
	This is followed by a dummy byte. 
	After the dummy byte, the FT81x responds to each host byte with read data bytes.
	*/
	SPI.beginTransaction(FT813);
	digitalWrite (slaveSelectPin, LOW);
	SPI.transfer(IDAddress);//send Address (address is two zero bits followed by 22-bit address)
	SPI.transfer(0x0);//send dummy byte
	firstByte = SPI.transfer(0);//send data irrelevant
	IDAddress = 0x0C0002;//set address to one less.
	
	SPI.transfer(IDAddress);//send Address (address is two zero bits followed by 22-bit address)
	SPI.transfer(0x0);//send dummy byte
	secondByte = SPI.transfer(0);//send data irrelevant
	IDAddress =	0x0C0001;//set address to one less.
	
	SPI.transfer(IDAddress);//send Address (address is two zero bits followed by 22-bit address)
	SPI.transfer(0x0);//send dummy byte
	thirdByte = SPI.transfer(0);//send data irrelevant
	SPI.endTransaction();
	digitalWrite (slaveSelectPin, HIGH);
	
	Serial.print(firstByte, BIN);
	Serial.print(" ");
	Serial.print(secondByte, BIN);
	Serial.print(" ");
	Serial.print(thirdByte, BIN);
	Serial.print(" ");
	Serial.println(fourthByte, BIN);
	
}

void loop() {
  //
}

