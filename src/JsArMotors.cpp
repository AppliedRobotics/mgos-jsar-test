#include "JsArInterface.h"
#include "JsArMotors.h"
#include "regs.h"

#define MAX_POWER (1023)


JsArMotors jsarMotors;

void JsArMotors::begin()
{
	jsi.set8(DRIVER_MODE, DRIVER_MODE_2_H_BRIDGES);
}

void JsArMotors::pidWrite(uint8_t p, uint8_t i, uint8_t d)
{
	jsi.set8(PID_P, p);
	jsi.set8(PID_I, i);
	jsi.set8(PID_D, d);
}

void JsArMotors::loopPeriodWrite(uint8_t period_ms)
{
	if(period_ms < 1) {
		return;
	}

	jsi.set8(CONTROL_PERIOD, period_ms);
}

void JsArMotors::encoderModeAB()
{
	jsi.set8(ENCODER_MODE, ENCODER_MODE_AB);
}

void JsArMotors::encoderModeA()
{
	jsi.set8(ENCODER_MODE, ENCODER_MODE_A);
}

void JsArMotors::encoderModeARising()
{
	jsi.set8(ENCODER_MODE, ENCODER_MODE_A_RISING);
}

void JsArMotors::maxPowerWrite(uint16_t max_power)
{
	if(max_power > 1023) {
		max_power = 1023;
	}

	jsi.set16(MAX_POWER_LIMIT, max_power);
}

void JsArMotors::powerWrite(uint8_t motor_n, int16_t val)
{
	if(motor_n != 1 && motor_n != 2) {
		return;
	}

	if(val > MAX_POWER) {
		val = MAX_POWER;
	}

	if(val < - MAX_POWER) {
		val = -MAX_POWER;
	}

	uint8_t addr = motor_n == 1? POWER_1: POWER_3;
	jsi.set16(addr, val);
}

void JsArMotors::speedWrite(uint8_t motor_n, int16_t val)
{
	if(motor_n != 1 && motor_n != 2) {
		return;
	}

	if(jsi.mRegs[MOTOR_CONTROL_MODE] != CONTROL_MODE_SPEED) {
		jsi.set8(MOTOR_CONTROL_MODE, CONTROL_MODE_SPEED);
	}

	uint8_t addr = motor_n == 1? GOAL_SPEED_1: GOAL_SPEED_3;
	jsi.set16(addr, val);
}

int16_t JsArMotors::powerRead(uint8_t motor_n)
{
	if(motor_n != 1 && motor_n != 2) {
		return 0;
	}

	uint8_t addr = motor_n == 1? POWER_1: POWER_3;
	
	uint16_t data = 0;
	jsi.get16(addr, &data);
	return data;		
}

int16_t JsArMotors::positionRead(uint8_t motor_n)
{
	if(motor_n != 1 && motor_n != 2) {
		return 0;
	}

	uint8_t addr = motor_n == 1? PRESENT_POSITION_1: PRESENT_POSITION_3;
	
	uint16_t data = 0;
	jsi.get16(addr, &data);
	return data;		
}

int16_t JsArMotors::speedRead(uint8_t motor_n)
{
	if(motor_n != 1 && motor_n != 2) {
		return 0;
	}

	uint8_t addr = motor_n == 1? PRESENT_SPEED_1: PRESENT_SPEED_3;

	uint16_t data = 0;
	jsi.get16(addr, &data);
	return data;		
}

void JsArMotors::powerWriteAll(int16_t power1, int16_t power2)
{
	uint8_t data[4];
	int idx = 0;
	data[idx++] = power1;
	data[idx++] = power1 << 8;
	data[idx++] = power2;
	data[idx++] = power2 << 8;
	jsi.set(POWER_1, idx, data);
}

void JsArMotors::speedWriteAll(int16_t speed1, int16_t speed2)
{
	if(jsi.mRegs[MOTOR_CONTROL_MODE] != CONTROL_MODE_SPEED)
		jsi.set8(MOTOR_CONTROL_MODE	, CONTROL_MODE_SPEED);

	uint8_t data[4];
	int idx = 0;
	data[idx++] = speed1;
	data[idx++] = speed1 << 8;
	data[idx++] = speed2;
	data[idx++] = speed2 << 8;
	jsi.set(GOAL_SPEED_1, idx, data);
}

void JsArMotors::positionReadAll(int16_t *position1, int16_t *position2)
{
	uint8_t data[6];
	jsi.get(PRESENT_POSITION_1, sizeof(data), data);
	*position1 = data[0] | ((uint16_t)data[1] << 8);
	*position2 = data[4] | ((uint16_t)data[5] << 8);
}

void JsArMotors::speedReadAll(int16_t *speed1, int16_t *speed2)
{
	uint8_t data[4];
	jsi.get(PRESENT_SPEED_1, sizeof(data), data);
	*speed1 = data[0] | ((uint16_t)data[1] << 8);
	*speed2 = data[2] | ((uint16_t)data[3] << 8);
}

void JsArMotors::readAll(int16_t *position1, int16_t *speed1, int16_t *position2, int16_t *speed2)
{
	uint8_t data[14];
	jsi.get(PRESENT_POSITION_1, sizeof(data), data);
	*position1 = data[0] | ((uint16_t)data[1] << 8);
	*position2 = data[4] | ((uint16_t)data[5] << 8);
	*speed1 = data[8] | ((uint16_t)data[9] << 8);
	*speed2 = data[12] | ((uint16_t)data[13] << 8);
}

void JsArMotors::powerReadAll(int16_t *power1, int16_t *power2)
{
	uint8_t data[6];
	jsi.get(POWER_1, sizeof(data), data);
	*power1 = data[0] | ((uint16_t)data[1] << 8);
	*power2 = data[4] | ((uint16_t)data[5] << 8);
}






















