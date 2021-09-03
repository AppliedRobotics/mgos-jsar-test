#include "JsArInterface.h"
#include "JsArKeys.h"
#include "regs.h"

#define MAX_POWER (1023)


JsArKeys jsarKeys;

void JsArKeys::begin()
{
	jsi.set8(DRIVER_MODE, DRIVER_MODE_4_KEYS);
}

void JsArKeys::pidWrite(uint8_t p, uint8_t i, uint8_t d)
{
	jsi.set8(PID_P, p);
	jsi.set8(PID_I, i);
	jsi.set8(PID_D, d);
}

void JsArKeys::loopPeriodWrite(uint8_t period_ms)
{
	if(period_ms < 1) {
		return;
	}
	jsi.set8(CONTROL_PERIOD, period_ms);
}

void JsArKeys::encodersEnable()
{
	jsi.set8(ENCODER_MODE, ENCODER_MODE_SINGLE);
}

void JsArKeys::maxPowerWrite(uint16_t max_power)
{
	if(max_power > 1023) {
		max_power = 1023;
	}

	jsi.set16(MAX_POWER_LIMIT, max_power);
}

void JsArKeys::digitalWrite(uint8_t key_n, uint8_t is_on)
{
	if( !(1 <= key_n && key_n <= 4)) {
		return;
	}

	uint16_t val = is_on? MAX_POWER: 0;
	powerWrite(key_n, val);
}

void JsArKeys::powerWrite(uint8_t key_n, uint16_t val)
{
	if( !(1 <= key_n && key_n <= 4)) {
		return;
	}

	if(val > MAX_POWER) {
		val = MAX_POWER;
	}

	uint8_t addr;
	switch(key_n) {
		case 1: addr = POWER_1; break;
		case 2: addr = POWER_2; break;
		case 3: addr = POWER_3; break;
		case 4: addr = POWER_4; break;
	}

	jsi.set16(addr, val);
}

void JsArKeys::speedWrite(uint8_t key_n, uint16_t val)
{
	if( !(1 <= key_n && key_n <= 4)) {
		return;
	}

	if(jsi.mRegs[MOTOR_CONTROL_MODE] != CONTROL_MODE_SPEED_SINGLE) {
		jsi.set8(MOTOR_CONTROL_MODE, CONTROL_MODE_SPEED_SINGLE);
	}

	uint8_t addr;
	switch (key_n) {
		case 1: addr = GOAL_SPEED_1; break;
		case 2:	addr = GOAL_SPEED_2; break;
		case 3:	addr = GOAL_SPEED_3; break;
		case 4: addr = GOAL_SPEED_4; break;
	}

	jsi.set16(addr, val);
}

uint16_t JsArKeys::powerRead(uint8_t key_n)
{
	if( !(1 <= key_n && key_n <= 4)) {
		return 0;
	}

	uint8_t addr;
	switch(key_n) {
		case 1: addr = POWER_1; break;
		case 2: addr = POWER_2; break;
		case 3: addr = POWER_3; break;
		case 4: addr = POWER_4; break;
	}

	uint16_t data = 0;
	jsi.get16(addr, &data);
	return data;
}

uint16_t JsArKeys::positionRead(uint8_t key_n)
{
	if( !(1 <= key_n && key_n <= 4)) {
		return 0;
	}

	uint8_t addr;
	switch(key_n) {
		case 1: addr = PRESENT_POSITION_1; break;
		case 2: addr = PRESENT_POSITION_2; break;
		case 3: addr = PRESENT_POSITION_3; break;
		case 4: addr = PRESENT_POSITION_4; break;
	}

	uint16_t data = 0;
	jsi.get16(addr, &data);
	return data;	
}

uint16_t JsArKeys::speedRead(uint8_t key_n)
{
	if( !(1 <= key_n && key_n <= 4)) {
		return 0;
	}

	uint8_t addr;
	switch(key_n) {
		case 1: addr = PRESENT_SPEED_1; break;
		case 2: addr = PRESENT_SPEED_2; break;
		case 3: addr = PRESENT_SPEED_3; break;
		case 4: addr = PRESENT_SPEED_4; break;
	}

	uint16_t data = 0;
	jsi.get16(addr, &data);
	return data;		
}

void JsArKeys::digitalWriteAll(uint8_t val1,  uint8_t val2,  uint8_t val3,  uint8_t val4){}
void JsArKeys::powerWriteAll(uint16_t val1,  uint16_t val2,  uint16_t val3,  uint16_t val4){}
void JsArKeys::speedWriteAll(uint16_t val1,  uint16_t val2,  uint16_t val3,  uint16_t val4){}
void JsArKeys::positionReadAll(uint16_t & val1, uint16_t & val2, uint16_t & val3, uint16_t & val4){}
void JsArKeys::speedReadAll(uint16_t & val1, uint16_t & val2, uint16_t & val3, uint16_t & val4){}






















