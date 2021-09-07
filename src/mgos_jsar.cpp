
#include "mgos_jsar.h"

/* Begin */
int mgos_jsar_begin(void)
{
    return jsar.begin();
}

/* Enable Ethernet */
void mgos_jsar_enableEthernet(void) 
{
    jsar.enableEthernet();
}

/* Disable Ethernet */
void mgos_jsar_disableEthernet(void)
{
    jsar.disableEthernet();
}

/* Enable I2C Pins */
void mgos_jsar_enableI2CPins(void)
{
    jsar.enableI2CPins();
}

/* Disable I2C Pins */
void mgos_jsar_disableI2CPins(void)
{
    jsar.disableI2CPins();
}

void mgos_jsar_enableCanModule(void)
{
    jsar.enableCanModule();
}

void mgos_jsar_disableCanModule(void)
{
    jsar.disableCanModule();
}


void mgos_jsar_disableSpiPins(void)
{
    jsar.disableSpiPins();
}

void mgos_jsar_enableSpiPins3V3Mode(void)
{
    jsar.enableSpiPins3V3Mode();
}

void mgos_jsar_enableSpiPinsFast3V3Mode(void)
{
    jsar.enableSpiPinsFast3V3Mode();
}

void mgos_jsar_enableSpiPins5VMode(void)
{
    jsar.enableSpiPins5VMode();
}

void mgos_jsar_enableSpiPinsFast5VMode(void)
{
    jsar.enableSpiPinsFast5VMode();
}


void mgos_jsar_disableSDPort(void)
{
    jsar.disableSDPort();
}

void mgos_jsar_enableSDPort1BitMode(void)
{
    jsar.enableSDPort1BitMode();
}

void mgos_jsar_enableSDPort4BitMode(void)
{
    jsar.enableSDPort4BitMode();
}

void mgos_jsar_enableSDPortSpiMode(void)
{
    jsar.enableSDPortSpiMode();
}


void mgos_jsar_enableMisoPin(void)
{
    jsar.enableMisoPin();
}

void mgos_jsar_disableMisoPin(void)
{
    jsar.disableMisoPin();
}


void mgos_jsar_enableIrTx(void)
{
    jsar.enableIrTx();
}
void mgos_jsar_disableIrTx(void)
{
    jsar.disableIrTx();
}


void mgos_jsar_enableIrRx(void)
{
    jsar.enableIrRx();
}
void mgos_jsar_disableIrRx(void)
{
    jsar.disableIrRx();
}


void mgos_jsar_writeMinVoltageToStart(double v)
{
    jsar.writeMinVoltageToStart(v);
}

void mgos_jsar_writeMinVoltageToWork(double v)
{
    jsar.writeMinVoltageToWork(v);
}

double mgos_jsar_readVoltage(void)
{
    return jsar.readVoltage();
}


void mgos_jsar_replacePin36By25AsOUTPUT(void)
{
    jsar.replacePin36By25AsOUTPUT();
}

void mgos_jsar_replacePin36By25AsDAC(void)
{
    jsar.replacePin36By25AsDAC();
}

void mgos_jsar_replacePin35By26AsOUTPUT(void)
{
    jsar.replacePin35By26AsOUTPUT();
}

void mgos_jsar_replacePin35By26AsDAC(void)
{
    jsar.replacePin35By26AsDAC();
}

void mgos_jsar_replacePin34By27AsOUTPUT(void)
{
    jsar.replacePin34By27AsOUTPUT();
}

void mgos_jsar_replacePinByExpander(uint8_t pin)
{
    jsar.replacePinByExpander(pin);
}


void mgos_jsar_expanderPinMode(uint8_t pin, uint8_t mode)
{
    jsar.expanderPinMode(pin, mode);
}

void mgos_jsar_expanderDigitalWrite(uint8_t pin, uint8_t value)
{
    jsar.expanderDigitalWrite(pin, value);
}

int mgos_jsar_expanderDigitalRead(uint8_t pin)
{
    return jsar.expanderDigitalRead(pin);
}

void mgos_jsar_expanderAnalogWrite(uint8_t pin, uint16_t value)
{
    jsar.expanderAnalogWrite(pin, value);
}

int mgos_jsar_expanderAnalogRead(uint8_t pin)
{
    return jsar.expanderAnalogRead(pin);
}

void mgos_jsar_expanderWriteLed(uint8_t is_en)
{
    jsar.expanderWriteLed(is_en);
}


void mgos_jsar_timMode(uint8_t tim, uint8_t prescaler, uint16_t pulse)
{
    jsar.timMode(tim, prescaler, pulse);
}


int mgos_jsar_updateFirmware()
{
    return jsar.updateFirmware();
}

void mgos_jsar_lockExpander(uint8_t packet_n)
{
    jsar.lockExpander(packet_n);
}

uint8_t mgos_jsar_unlockExpander(void)
{
    return jsar.unlockExpander();
}

/*Keys ***********************************************************/

/* Begin */
void mgos_jsar_KeysBegin(void)
{
    jsarKeys.begin();
}

/* Pid Write */
void mgos_jsar_KeysPidWrite(uint8_t p, uint8_t i, uint8_t d)
{
    jsarKeys.pidWrite(p, i, d);
}

/* Loop Period Write */
void mgos_jsar_KeysLoopPeriodWrite(uint8_t period_ms)
{
    jsarKeys.loopPeriodWrite(period_ms);
}

/* Encoders Enable */
void mgos_jsar_KeysEncodersEnable(void)
{
    jsarKeys.encodersEnable();
}

/* Max Power Write */
void mgos_jsar_KeysMaxPowerWrite(uint16_t max_power)
{
    jsarKeys.maxPowerWrite(max_power);
}

/* Digital Write */ 
void mgos_jsar_KeysDigitalWrite(uint8_t key_n, uint8_t is_on)
{
    jsarKeys.digitalWrite(key_n, is_on);
}

/* Power Write */
void mgos_jsar_KeysPowerWrite(uint8_t key_n, uint16_t val)
{
    jsarKeys.powerWrite(key_n, val);
}

/* Speed Write */
void mgos_jsar_KeysSpeedWrite(uint8_t key_n, uint16_t val)
{
    jsarKeys.speedWrite(key_n, val);
}

/* Power Read */
uint16_t mgos_jsar_KeysPowerRead(uint8_t key_n)
{
    return jsarKeys.powerRead(key_n);
}

/* Position Read */
uint16_t mgos_jsar_KeysPositionRead(uint8_t key_n)
{
    return jsarKeys.positionRead(key_n);
}

/* Speed Read */
uint16_t mgos_jsar_KeysSpeedRead(uint8_t key_n)
{
    return jsarKeys.speedRead(key_n);
}

/* Digital Write All */
void mgos_jsar_KeysDigitalWriteAll(uint8_t val1,  uint8_t val2,  
                                   uint8_t val3,  uint8_t val4)
{
    jsarKeys.digitalWriteAll(val1,  val2,  val3,  val4);
}

/* Power Write All */
void mgos_jsar_KeysPowerWriteAll(uint16_t val1,  uint16_t val2,  
                                 uint16_t val3,  uint16_t val4)
{
    jsarKeys.powerWriteAll(val1,  val2,  val3,  val4);
}

/* Speed Write All */
void mgos_jsar_KeysSpeedWriteAll(uint16_t val1,  uint16_t val2, 
                                 uint16_t val3,  uint16_t val4)
{
    jsarKeys.speedWriteAll(val1,  val2,  val3,  val4);
}

/* Position Read All */
void mgos_jsar_KeysPositionReadAll(uint16_t *val1, uint16_t *val2, 
                                   uint16_t *val3, uint16_t *val4)
{
    jsarKeys.positionReadAll(val1, val2, val3, val4);
}

/* Speed Read All */
void mgos_jsar_KeysSpeedReadAll(uint16_t *val1, uint16_t *val2, 
                                uint16_t *val3, uint16_t *val4)
{
    jsarKeys.speedReadAll(val1, val2, val3, val4);
}

/* Motors ********************************************************************/

/* Begin */
void mgos_jsar_MotorsBegin(void)
{
    jsarMotors.begin();
}

/* Pid Write */
void mgos_jsar_MotorsPidWrite(uint8_t p, uint8_t i, uint8_t d)
{
    jsarMotors.pidWrite(p, i, d);
}

/* Loop Period Write */
void mgos_jsar_MotorsLoopPeriodWrite(uint8_t period_ms)
{
    jsarMotors.loopPeriodWrite(period_ms);
}

/* Encoder Mode AB */
void mgos_jsar_MotorsEncoderModeAB(void)
{
    jsarMotors.encoderModeAB();
}

/* Encoder ModeA */
void mgos_jsar_MotorsEncoderModeA(void)
{
    jsarMotors.encoderModeA();
}

/* Encoder ModeA Rising */
void mgos_jsar_MotorsEncoderModeARising(void)
{
    jsarMotors.encoderModeARising();
}

/* Max Power Write */
void mgos_jsar_MotorsMaxPowerWrite(uint16_t max_power)
{
    jsarMotors.maxPowerWrite(max_power);
}

/* Power Write */
void mgos_jsar_MotorsPowerWrite(uint8_t motor_n, int16_t val)
{
    jsarMotors.powerWrite(motor_n, val);
}

/* Speed Write */
void mgos_jsar_MotorsSpeedWrite(uint8_t motor_n, int16_t val)
{
    jsarMotors.speedWrite(motor_n, val);
}

/* Power Write All */
void mgos_jsar_MotorsPowerWriteAll(int16_t power1, int16_t power2)
{
    jsarMotors.powerWriteAll(power1, power2);
}

/* Speed Write All */ 
void mgos_jsar_MotorsSpeedWriteAll(int16_t speed1, int16_t speed2)
{
    jsarMotors.speedWriteAll(speed1, speed2);
}

/* Power Read*/
int16_t mgos_jsar_MotorsPowerRead(uint8_t motor_n)
{
    return jsarMotors.powerRead(motor_n);
}

/* Position Read*/
int16_t mgos_jsar_MotorsPositionRead(uint8_t motor_n)
{
    return jsarMotors.positionRead(motor_n);
}

/* SpeedRead */
int16_t mgos_jsar_MotorsSpeedRead(uint8_t motor_n)
{
    return jsarMotors.speedRead(motor_n);
}

/* Position Read All */
void mgos_jsar_MotorsPositionReadAll(int16_t *pos1, int16_t *pos2)
{
    jsarMotors.positionReadAll(pos1, pos2);
}

/* Speed Read All*/
void mgos_jsar_MotorsSpeedReadAll(int16_t *speed1, int16_t *speed2)
{
    jsarMotors.speedReadAll(speed1, speed2);
}

/* Power Read All */
void mgos_jsar_MotorsPowerReadAll(int16_t *power1, int16_t *power2)
{
    jsarMotors.powerReadAll(power1, power2);
}
/* Read All */
void mgos_jsar_MotorsReadAll(int16_t *position1, int16_t *speed1, 
                             int16_t *position2, int16_t *speed2)
{
    jsarMotors.readAll(position1, speed1, position2, speed2);
}