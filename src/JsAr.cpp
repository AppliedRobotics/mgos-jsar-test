#include "mgos.h"
#include "JsAr.h"
#include "regs.h"
#include "JsArInterface.h"
#include "firmware.h"

#ifdef JSAR_DEBUG
#	define DBG_PRINT(_x_) LOG(LL_INFO, (_x_))
#else
#	define DBG_PRINT(_x_) 
#endif

#define DXL_RESET_MAGIC  	(0x92)
#define CONTROLLER_ID 		(250)
#define BOOT_ID 			(251)

#define INPUT 0x00
#define INPUT_PULLUP 0x02
#define OUTPUT 0x01


typedef enum {
	JsAr_A0 = 0, JsAr_A1, JsAr_A2, JsAr_A3, JsAr_A4, JsAr_A5, JsAr_D2, JsAr_D3, 
	JsAr_D4, JsAr_D5, JsAr_D6, JsAr_D7, JsAr_D8, JsAr_D9, JsAr_D10, JsAr_D11, 
	JsAr_D12, JsAr_D13, JsAr_E1A, JsAr_E1B, JsAr_E2A, JsAr_E2B, JsAr_H1, 
	JsAr_H2, JsAr_H3, JsAr_H4, JsArIO_N
}JsArIO_t;

typedef struct {
	uint8_t mode_reg;
	uint8_t out_reg;
	uint8_t in_reg;
}ExpanderPin_t;


JsAr jsar;

static const ExpanderPin_t expanderPins[JsAr_D12] = { 		//JsArIO_N] = {
	[JsAr_A0] = {A0_MODE, A0_OUTPUT_VAL, A0_PRESENT_VAL},
	[JsAr_A1] = {A1_MODE, A1_OUTPUT_VAL, A1_PRESENT_VAL},
	[JsAr_A2] = {A2_MODE, A2_OUTPUT_VAL, A2_PRESENT_VAL},
	[JsAr_A3] = {A3_MODE, A3_OUTPUT_VAL, A3_PRESENT_VAL},
	[JsAr_A4] = {A4_MODE, A4_OUTPUT_VAL, A4_PRESENT_VAL},
	[JsAr_A5] = {A5_MODE, A5_OUTPUT_VAL, A5_PRESENT_VAL},
	{0, 0, 0},
	[JsAr_D3] = {D3_MODE, D3_OUTPUT_VAL, D3_PRESENT_VAL},
	[JsAr_D4] = {D4_MODE, D4_OUTPUT_VAL, D4_PRESENT_VAL},
	[JsAr_D5] = {D5_MODE, D5_OUTPUT_VAL, D5_PRESENT_VAL},
	[JsAr_D6] = {D6_MODE, D6_OUTPUT_VAL, D6_PRESENT_VAL},
	[JsAr_D7] = {D7_MODE, D7_OUTPUT_VAL, D7_PRESENT_VAL},
	[JsAr_D8] = {D8_MODE, D8_OUTPUT_VAL, D8_PRESENT_VAL},
	[JsAr_D9] = {D9_MODE, D9_OUTPUT_VAL, D9_PRESENT_VAL},
	{0, 0, 0},
	[JsAr_D11] = {D11_MODE, D11_OUTPUT_VAL, D11_PRESENT_VAL}
};

static const ExpanderPin_t *getExpanderPin(uint8_t pin)
{
	switch(pin)	{
		case 36: return expanderPins + JsAr_A0;
		case 39: return expanderPins + JsAr_A1;
		case 34: return expanderPins + JsAr_A2;
		case 35: return expanderPins + JsAr_A3;
		case 32: return expanderPins + JsAr_A4;
		case 33: return expanderPins + JsAr_A5;
		case 23: return expanderPins + JsAr_D3;
		case 19: return expanderPins + JsAr_D4;
		case 18: return expanderPins + JsAr_D5;
		case 21: return expanderPins + JsAr_D6;
		case 22: return expanderPins + JsAr_D7;
		case 2 : return expanderPins + JsAr_D8;
		case 4 : return expanderPins + JsAr_D9;
		case 13: return expanderPins + JsAr_D11;
	}

	return 0;
}

uint8_t getExpanderTim(uint8_t pin)
{
	switch(pin)	{
		case 23: return 2;
		case 19: return 2;
		case 18: return 2;
		case 21: return 3;
		case 22: return 3;
	}
	return 0;
}

/*
static void set8(uint8_t addr, uint8_t val)   {jsi.set8(addr, val);}
static void set16(uint8_t addr, uint16_t val) {jsi.set16(addr, val);}
static uint8_t 	get8(uint8_t addr)	{return jsi.get8(addr);}
static uint16_t get16(uint8_t addr)	{return jsi.get16(addr);}
static uint8_t* regs = jsi.mRegs;
*/

int JsAr::begin(bool isEnableAllPins)
{
	uint8_t pins[] = {18, 23, 21, 19, 22};

	for(uint8_t i = 0; i < sizeof(pins); i++) {
		mgos_gpio_set_mode(pins[i], MGOS_GPIO_MODE_INPUT);
		mgos_gpio_set_pull(pins[i], MGOS_GPIO_PULL_UP);
	}

	delay(100);
	jsi.begin(1000000);
	id = CONTROLLER_ID;

 	if(unlockBootloader() != DYN_STATUS_OK) {
		LOG(LL_INFO, ("JSAR: unlockBootloader FASLE!")); 
		return 1;
	}
	LOG(LL_INFO, ("JSAR: unlock %d - Ok!", id)); 

	uint16_t timeout = 500; 
	do {
		delay(50);
	} while(jsi.ping(BOOT_ID) != DYN_STATUS_OK && --timeout);

	if(timeout == 0) { 
		LOG(LL_INFO, ("BOOT_ID ping FASLE!")); 
		return DYN_STATUS_TIMEOUT;
	}
	LOG(LL_INFO, ("JSAR: ping %d - Ok!", id)); 


	delay(100);

	do {
		jsi.write(BOOT_ID, DXL_LOCK_RESET_REG, (uint8_t)DXL_RESET_MAGIC);
		delay(300);
	} while(jsi.ping(id) != DYN_STATUS_OK);

	LOG(LL_INFO, ("JSAR: started - Ok!"));

	delay(500);

	for(uint8_t i = 0; i < sizeof(pins); i++) {
		mgos_gpio_setup_output(pins[i], 1);
		mgos_gpio_set_mode(pins[i], MGOS_GPIO_MODE_OUTPUT);
	}

	delay(500);

	uint8_t dummy = 0;
	for(uint8_t i = 0; i < 229; i++) {
		jsi.get8(i, &dummy);
	}

	LOG(LL_INFO, ("JSAR: dummy - Ok!"));

	jsi.set8(ETHERNET_ENABLE, (uint8_t)1);
	jsi.set8(ETHERNET_RST, (uint8_t)1);

	LOG(LL_INFO, ("JSAR: ETHERNET_RST - Ok!"));

	jsi.set8(GPIO_PULL_UP_ENABLE, 1);
	LOG(LL_INFO, ("JSAR: PULL UP - Ok!"));


	if(isEnableAllPins) {
		jsi.set8(MISO_OUTPUT_EN, 1);
		jsi.set8(D3_D7_PULL_UP_ENABLE, 1);
		jsi.set8(SPI_MODE, SPI_MODE_5V);
		jsi.set8(I2C_MODE, I2C_MODE_5V);
		disableIrTx();

		for(int i = A0_MODE; i <= D11_MODE; i++) {
			jsi.set8(i, PinMode_ESP);
		}
	}

	LOG(LL_INFO, ("JSAR: set pins - Ok!"));

	for(int i = E1A_MODE; i <= E2B_MODE; i++) {
		jsi.set8(i, PinMode_ST_INPUT);
	}
	
	delay(100);

	for(uint8_t i = 0; i < sizeof(pins); i++) {
		mgos_gpio_set_mode(pins[i], MGOS_GPIO_MODE_INPUT);
		mgos_gpio_set_pull(pins[i], MGOS_GPIO_PULL_NONE);
	}

	return 0;
}

void JsAr::enableEthernet() 
{
	jsi.set8(ETHERNET_ENABLE, 1); 
	jsi.set8(ETHERNET_RST, 0);
}

void JsAr::disableEthernet() 
{
	jsi.set8(ETHERNET_RST, 1); 
	jsi.set8(ETHERNET_ENABLE, 0);
}

void JsAr::enableI2CPins() 			{jsi.set8(I2C_MODE, I2C_MODE_5V);}
void JsAr::disableI2CPins() 		{jsi.set8(I2C_MODE, I2C_MODE_DISABLED);}

void JsAr::enableCanModule() 		{jsi.set8(CAN_ENABLE, 1);}
void JsAr::disableCanModule() 		{jsi.set8(CAN_ENABLE, 0);} 

void JsAr::disableSpiPins() 			{jsi.set8(SPI_MODE, SPI_MODE_DISABLED);} 
void JsAr::enableSpiPins3V3Mode() 		{jsi.set8(SPI_MODE, SPI_MODE_3V3);}
void JsAr::enableSpiPinsFast3V3Mode() 	{jsi.set8(SPI_MODE, SPI_MODE_3V3_DRV);}
void JsAr::enableSpiPins5VMode() 		{jsi.set8(SPI_MODE, SPI_MODE_5V);}
void JsAr::enableSpiPinsFast5VMode() 	{jsi.set8(SPI_MODE, SPI_MODE_5V_DRV);}

void JsAr::disableSDPort() 			{jsi.set8(SD_MODE, SD_MODE_DISABLED);}
void JsAr::enableSDPort1BitMode() 	{jsi.set8(SD_MODE, SD_MODE_1BIT);}
void JsAr::enableSDPort4BitMode() 	{jsi.set8(SD_MODE, SD_MODE_4BIT);}
void JsAr::enableSDPortSpiMode() 	{jsi.set8(SD_MODE, SD_MODE_SPI);}

void JsAr::enableMisoPin() 			{jsi.set8(MISO_OUTPUT_EN, 1);}
void JsAr::disableMisoPin() 		{jsi.set8(MISO_OUTPUT_EN, 0);}

void JsAr::enableIrTx() 			{jsi.set8(IR_TX_ENABLE, 1);}
void JsAr::disableIrTx() 			{jsi.set8(IR_TX_ENABLE, 0);}

void JsAr::enableIrRx() 			{jsi.set8(IR_RX_ENABLE, 1);}
void JsAr::disableIrRx() 			{jsi.set8(IR_RX_ENABLE, 0);}

void JsAr::writeMinVoltageToStart(float v)
{
	jsi.set8(MIN_VOLTAGE_TO_START, (uint8_t)(v*10));
}

void JsAr::writeMinVoltageToWork(float v)	
{
	jsi.set8(MIN_VOLTAGE_LIMIT, (uint8_t)(v*10));
}

float JsAr::readVoltage() 	
{
	uint8_t byte;
	jsi.get8(PRESENT_VOLTAGE, &byte);
	return ((float)byte) / 10;
}

void JsAr::expanderWriteLed(uint8_t is_en) 
{
	jsi.set8(LED, is_en);
}

void JsAr::expanderPinMode(uint8_t pin, uint8_t mode)
{
	const ExpanderPin_t *xpin = getExpanderPin(pin);

	if(!xpin) return;

	switch(mode) {
		case INPUT: 
			jsi.set8(xpin->mode_reg, PinMode_ST_INPUT); 
			break;
		case INPUT_PULLUP: 
			jsi.set8(xpin->mode_reg, PinMode_ST_INPUT_PULLUP); 
			break;
		case OUTPUT: 
			jsi.set8(xpin->mode_reg, PinMode_ST_OUTPUT); 
			break;
	}
}

void JsAr::expanderDigitalWrite(uint8_t pin, uint8_t value)
{
	const ExpanderPin_t *xpin = getExpanderPin(pin);
	if(!xpin) return;

	uint8_t mode = jsi.mRegs[xpin->mode_reg];
	switch(mode) {
		case PinMode_ST_PWM:
			jsi.set8(xpin->mode_reg, PinMode_ST_OUTPUT);
			// fall through
		case PinMode_ST_ADC:
			// fall through
		case PinMode_ST_INPUT:
			// fall through
		case PinMode_ST_INPUT_PULLUP:
			// fall through
		case PinMode_ST_OUTPUT:
			// fall through
		case PinMode_ST_OUTPUT_OPEN_DRAIN:
			jsi.set8(xpin->out_reg, value);
			break;
	}
}

void JsAr::expanderAnalogWrite(uint8_t pin, uint16_t value)
{
	const ExpanderPin_t *xpin = getExpanderPin(pin);
	if(!xpin) return;

	uint8_t mode = jsi.mRegs[xpin->mode_reg];

	switch(mode) {
		case PinMode_ST_OUTPUT:
			// fall through
		case PinMode_ST_OUTPUT_OPEN_DRAIN:
			jsi.set8(xpin->mode_reg, PinMode_ST_PWM);
			// fall through
		case PinMode_ST_INPUT:
			// fall through
		case PinMode_ST_INPUT_PULLUP:
			// fall through
		case PinMode_ST_ADC:
			// fall through
		case PinMode_ST_PWM:
			jsi.set16(xpin->out_reg, value <= 1024? value: 1024);
			break;
	}
}

int JsAr::expanderDigitalRead(uint8_t pin)
{
	const ExpanderPin_t *xpin = getExpanderPin(pin);
	if(!xpin) return 0;


	uint8_t mode = jsi.mRegs[xpin->mode_reg];

	if (mode < PinMode_ST_ADC) return 0;

	if (mode == PinMode_ST_ADC) {
		jsi.set8(xpin->mode_reg, PinMode_ST_INPUT);
	}

	if (mode == PinMode_ST_ADC ||
	    mode == PinMode_ST_INPUT ||
	    mode == PinMode_ST_INPUT_PULLUP) {
		uint8_t data;
		jsi.get8(xpin->in_reg, &data);
		return data;
	}

	return 0;
}

int JsAr::expanderAnalogRead(uint8_t pin)
{
	uint16_t data;
	const ExpanderPin_t *xpin = getExpanderPin(pin);

	if(!xpin) return 0;

	uint8_t mode = jsi.mRegs[xpin->mode_reg];

	if(mode < PinMode_ST_ADC) return 0;

	if(mode != PinMode_ST_ADC) {
		jsi.set8(xpin->mode_reg, PinMode_ST_ADC);
		delay(1);
	}

	jsi.get16(xpin->in_reg, &data);
	return data;
}


void JsAr::timMode(uint8_t tim, uint8_t prescaler, uint16_t pulse)
{
	if(tim == 2) {
		jsi.set8(TIM2_PRESCALER, prescaler);
		jsi.set16(TIM2_PULSE, pulse);
	} else if(tim == 3)	{
		jsi.set8(TIM3_PRESCALER, prescaler);
		jsi.set16(TIM3_PULSE, pulse);
	}
}

void JsAr::replacePinByExpander(uint8_t pin) 
{
	const ExpanderPin_t *xpin = getExpanderPin(pin);

	if(!xpin) return;

	jsi.set8(xpin->mode_reg, PinMode_ST_INPUT);
	return;
}

void JsAr::replacePin36By25AsOUTPUT()	
{
	jsi.set8(getExpanderPin(36)->mode_reg, PinMode_ESP_OUT);
}

void JsAr::replacePin35By26AsOUTPUT()	
{
	jsi.set8(getExpanderPin(35)->mode_reg, PinMode_ESP_OUT);
}

void JsAr::replacePin34By27AsOUTPUT()	
{
	jsi.set8(getExpanderPin(34)->mode_reg, PinMode_ESP_OUT);
}

void JsAr::replacePin36By25AsDAC()	
{
	jsi.set8(getExpanderPin(36)->mode_reg, PinMode_ESP_DAC);
}

void JsAr::replacePin35By26AsDAC()	
{
	jsi.set8(getExpanderPin(35)->mode_reg, PinMode_ESP_DAC);
}

int JsAr::updateFirmware()
{
	jsi.begin(1000000);
	unlockBootloader();

	while(jsi.ping(BOOT_ID) != DYN_STATUS_OK) {}

	const int BLOCK_SIZE = 128;
	const int FIRMWARE_CRC_AND_ERASE_CMD_BLOCK_SIZE = 16;
	//const int FW_VERSION = 1;
	
	//Serial.setTimeout(2000);
	
	if(jsi.write(BOOT_ID, 1, firmwareData, 
		FIRMWARE_CRC_AND_ERASE_CMD_BLOCK_SIZE) != DYN_STATUS_OK) {
		return -1;
	}

	// send firmware
	int fullPacks = (sizeof(firmwareData) 
					- FIRMWARE_CRC_AND_ERASE_CMD_BLOCK_SIZE 
					+ BLOCK_SIZE - 1) / BLOCK_SIZE;
	
	if(fullPacks <= 0) {
		return -2;
	}

	//Serial.println("Writing " + String(fullPacks) + " blocks:");
	LOG(LL_INFO, ("Writing %d  blocks:", fullPacks));

	for(int i = 0; i < fullPacks; i++) {
		//Serial.print("\t" + String(i));
		LOG(LL_INFO, ("\t %d:", i));
		if (!((i + 1) % 16)) {
			//Serial.println();
			LOG(LL_INFO, ("\t"));
		}

		uint8_t addr_and_data_block[BLOCK_SIZE + 1];
		addr_and_data_block[0] = i;
		memcpy(addr_and_data_block + 1, 
			   	firmwareData + FIRMWARE_CRC_AND_ERASE_CMD_BLOCK_SIZE 
															+ i * BLOCK_SIZE,
				BLOCK_SIZE);
		if(jsi.write(BOOT_ID, 0, addr_and_data_block, BLOCK_SIZE + 1)) {
			return -3 - i;
		}
		//delay(200);
	}

	//Serial.println();
	//Serial.setTimeout(10);

	// get old application dynamixel id
	uint8_t app_dxl_id;
	if(jsi.read(BOOT_ID, ID, app_dxl_id) != DYN_STATUS_OK) {
		return -99;
	}

	delay(1000);

	jsi.write(BOOT_ID, DXL_LOCK_RESET_REG, (uint8_t)DXL_RESET_MAGIC);

	delay(1000);

	for(int i = 0; i < 10; i++) {
		delay(300);
		if(jsi.ping(CONTROLLER_ID) == DYN_STATUS_OK) {
			jsi.write(CONTROLLER_ID, LED, 1);
			return 0; //Success!
		}
	}

	return -100;
}

void JsAr::lockExpander(uint8_t packet_n)
{
	if(packet_n == DXL_RESET_MAGIC) {
		packet_n++;
	}

	jsi.write(id, DXL_LOCK_RESET_REG, (uint8_t)packet_n);
	jsi.write(id, DXL_LOCK_RESET_REG, (uint8_t)packet_n);
	jsi.write(id, DXL_LOCK_RESET_REG, (uint8_t)packet_n);
}

DynamixelStatus JsAr::unlockExpander()
{
	return jsi.set8(DXL_LOCK_RESET_REG, 0);
}

DynamixelStatus JsAr::unlockBootloader()
{	
	uint16_t timeout = 500; 

	/* We must sent 10 times for unlock */
	do {
		delay(1);
	} while(jsi.write(BOOT_ID, DXL_LOCK_RESET_REG, (uint8_t)0) != DYN_STATUS_OK  
			&& --timeout);

	if(timeout != 0) { 
		return DYN_STATUS_OK;
	} else { 
		return DYN_STATUS_TIMEOUT;
	}

	return 1;
}

// void JsAr::pinMode(uint8_t pin, uint8_t mode)
// {
// 	const ExpanderPin_t* xpin = getExpanderPin(pin);
// 	if(!xpin)
// 	{
// 		::pinMode(pin, mode);
// 		return;
// 	}

// 	uint8_t old_mode = regs[xpin->mode_reg];
// 	if(old_mode < PinMode_ST_ADC)
// 	{
// 		::pinMode(pin, mode);
// 		return;
// 	}
	
// 	switch(mode)
// 	{
// 		case INPUT: set8(xpin->mode_reg, PinMode_ST_INPUT); break;
// 		case INPUT_PULLUP: set8(xpin->mode_reg, PinMode_ST_INPUT_PULLUP); break;
// 		case OUTPUT: set8(xpin->mode_reg, PinMode_ST_OUTPUT); Serial.println("hello"); break;
// 	}
// }

// void JsAr::digitalWrite(uint8_t pin, uint8_t value)
// {
// 	const ExpanderPin_t* xpin = getExpanderPin(pin);
// 	if(!xpin)
// 	{
// 		::digitalWrite(pin, value);
// 		return;
// 	}

// 	uint8_t mode = regs[xpin->mode_reg];
// 	switch(mode)
// 	{
// 		case PinMode_DISABLED: 
// 		case PinMode_ESP: 
// 			::digitalWrite(pin, value);
// 			break;
// 		case PinMode_ESP_OUT: 
// 			if(pin == 36 || pin == 25)
// 				::digitalWrite(25, value);
// 			else if(pin == 35 || pin == 26)
// 				::digitalWrite(26, value);
// 			break;
// 		case PinMode_ST_PWM:
// 			set8(xpin->mode_reg, PinMode_ST_OUTPUT);
// 		case PinMode_ST_ADC:
// 		case PinMode_ST_INPUT:
// 		case PinMode_ST_INPUT_PULLUP:
// 		case PinMode_ST_OUTPUT:
// 		case PinMode_ST_OUTPUT_OPEN_DRAIN:
// 			set8(xpin->out_reg, value);
// 			break;
// 	}
// }

// void JsAr::analogWrite(uint8_t pin, uint16_t value, uint16_t range)
// {
// 	const ExpanderPin_t* xpin = getExpanderPin(pin);
// 	if(!xpin)
// 		return;
// 	uint8_t mode = regs[xpin->mode_reg];

// 	switch(mode)
// 	{
// 		case PinMode_DISABLED: 
// 		case PinMode_ESP:
// 			break;
// 		case PinMode_ST_OUTPUT:
// 		case PinMode_ST_OUTPUT_OPEN_DRAIN:
// 			set8(xpin->mode_reg, PinMode_ST_PWM);
// 		case PinMode_ST_INPUT:
// 		case PinMode_ST_INPUT_PULLUP:
// 		case PinMode_ST_ADC:
// 		case PinMode_ST_PWM:
// 			if(range)
// 			{
// //				uint8_t tim = getExpanderTim(pin);
// //				uint16_t* tim_pulse = tim == 2? regs + TIM2_PULSE: regs + TIM3_PULSE;
// //				if(tim == 2 && (regs[TIM2_PULSE] != (range & 0xFF) || regs[TIM2_PULSE + 1] != (range >> 8))
// //				{
// //					set16()
// //				}
// 			} 
// 			set16(xpin->out_reg, value <= 1024? value: 1024);
// 			break;
// 	}
// }

//void analogWriteFrequency(uint8_t pin, uint16_t value);

// int JsAr::digitalRead(uint8_t pin)
// {
// 	const ExpanderPin_t* xpin = getExpanderPin(pin);
// 	if(!xpin)
// 		return ::digitalRead(pin);
// 	uint8_t mode = regs[xpin->mode_reg];
// 	if(mode < PinMode_ST_ADC)
// 		return ::digitalRead(pin);
// 	if(mode == PinMode_ST_ADC)
// 		set8(xpin->mode_reg, PinMode_ST_INPUT);
// 	if(mode == PinMode_ST_ADC || mode == PinMode_ST_INPUT || mode == PinMode_ST_INPUT_PULLUP)
// 		return get8(xpin->in_reg);
// 	return 0;
// }

// int JsAr::analogRead(uint8_t pin)
// {
// 	const ExpanderPin_t* xpin = getExpanderPin(pin);
// 	if(!xpin)
// 		return ::analogRead(pin);
// 	uint8_t mode = regs[xpin->mode_reg];
// 	if(mode < PinMode_ST_ADC)
// 		return ::analogRead(pin);
// 	if(mode != PinMode_ST_ADC)
// 	{
// 		set8(xpin->mode_reg, PinMode_ST_ADC);
// 		delay(1);
// 	}
// 	return get16(xpin->in_reg);
// }
/*
void JsAr::disablePin(uint8_t pin)
{
	replacePinByExpander(pin);
}

void JsAr::enablePin(uint8_t pin)
{
	const ExpanderPin_t* xpin = getExpanderPin(pin);
	if(!xpin)
		return;
	set8(xpin->mode_reg, PinMode_ST_INPUT);
	return;
}
*/