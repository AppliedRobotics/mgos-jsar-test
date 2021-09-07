#ifndef MGOS_JSAR_H
#define MGOS_JSAR_H

#ifdef __cplusplus
#include "JsAr.h"
#include "JsArKeys.h"
#include "JsArMotors.h"
#else
//typedef struct JsArTag JsAr;
#endif

#ifdef __cplusplus
extern "C" {
#endif


int mgos_jsar_begin(void);

void mgos_jsar_enableEthernet(void);
void mgos_jsar_disableEthernet(void);

void mgos_jsar_enableI2CPins(void);
void mgos_jsar_disableI2CPins(void);

void mgos_jsar_enableCanModule(void);
void mgos_jsar_disableCanModule(void);

void mgos_jsar_disableSpiPins(void);
void mgos_jsar_enableSpiPins3V3Mode(void);
void mgos_jsar_enableSpiPinsFast3V3Mode(void);
void mgos_jsar_enableSpiPins5VMode(void);
void mgos_jsar_enableSpiPinsFast5VMode(void);

void mgos_jsar_disableSDPort(void);
void mgos_jsar_enableSDPort1BitMode(void);
void mgos_jsar_enableSDPort4BitMode(void);
void mgos_jsar_enableSDPortSpiMode(void);

void mgos_jsar_enableMisoPin(void);
void mgos_jsar_disableMisoPin(void);

void mgos_jsar_enableIrTx(void);
void mgos_jsar_disableIrTx(void);

void mgos_jsar_enableIrRx(void);
void mgos_jsar_disableIrRx(void);

void mgos_jsar_writeMinVoltageToStart(double v);
void mgos_jsar_writeMinVoltageToWork(double v);
double mgos_jsar_readVoltage(void);

void mgos_jsar_replacePin36By25AsOUTPUT(void);
void mgos_jsar_replacePin36By25AsDAC(void);
void mgos_jsar_replacePin35By26AsOUTPUT(void);
void mgos_jsar_replacePin35By26AsDAC(void);
void mgos_jsar_replacePin34By27AsOUTPUT(void);
void mgos_jsar_replacePinByExpander(uint8_t pin);

void mgos_jsar_expanderPinMode(uint8_t pin, uint8_t mode);
void mgos_jsar_expanderDigitalWrite(uint8_t pin, uint8_t value);
int mgos_jsar_expanderDigitalRead(uint8_t pin);
void mgos_jsar_expanderAnalogWrite(uint8_t pin, uint16_t value);
int mgos_jsar_expanderAnalogRead(uint8_t pin);
void mgos_jsar_expanderWriteLed(uint8_t is_en);

void mgos_jsar_timMode(uint8_t tim, uint8_t prescaler, uint16_t pulse);

int mgos_jsar_updateFirmware(uint8_t is_en);
void mgos_jsar_lockExpander(uint8_t packet_n);
uint8_t mgos_jsar_unlockExpander(void);


/* Keys  ********************************************************************/
void mgos_jsar_KeysBegin(void);
void mgos_jsar_KeysPidWrite(uint8_t p, uint8_t i, uint8_t d);
void mgos_jsar_KeysLoopPeriodWrite(uint8_t period_ms);
void mgos_jsar_KeysEncodersEnable(void);
void mgos_jsar_KeysMaxPowerWrite(uint16_t max_power);

void mgos_jsar_KeysDigitalWrite(uint8_t key_n, uint8_t is_on);
void mgos_jsar_KeysPowerWrite(uint8_t key_n, uint16_t val);
void mgos_jsar_KeysSpeedWrite(uint8_t key_n, uint16_t val);

uint16_t mgos_jsar_KeysPowerRead(uint8_t key_n);
uint16_t mgos_jsar_KeysPositionRead(uint8_t key_n);
uint16_t mgos_jsar_KeysSpeedRead(uint8_t key_n);


void mgos_jsar_KeysDigitalWriteAll(uint8_t val1,  uint8_t val2,  
                                   uint8_t val3,  uint8_t val4);

void mgos_jsar_KeysPowerWriteAll(uint16_t val1,  uint16_t val2,  
                                 uint16_t val3,  uint16_t val4);

void mgos_jsar_KeysSpeedWriteAll(uint16_t val1,  uint16_t val2, 
                                 uint16_t val3,  uint16_t val4);

void mgos_jsar_KeysPositionReadAll(uint16_t *val1, uint16_t *val2, 
                                   uint16_t *val3, uint16_t *val4);

void mgos_jsar_KeysSpeedReadAll(uint16_t *val1, uint16_t *val2, 
                                uint16_t *val3, uint16_t *val4);

/* Motors *********************************************************************/

void mgos_jsar_MotorsBegin(void);
void mgos_jsar_MotorsPidWrite(uint8_t p, uint8_t i, uint8_t d);
void mgos_jsar_MotorsLoopPeriodWrite(uint8_t period_ms);

void mgos_jsar_MotorsEncoderModeAB(void);
void mgos_jsar_MotorsEncoderModeA(void);
void mgos_jsar_MotorsEncoderModeARising(void);
void mgos_jsar_MotorsMaxPowerWrite(uint16_t max_power);

void mgos_jsar_MotorsPowerWrite(uint8_t motor_n, int16_t val);
void mgos_jsar_MotorsSpeedWrite(uint8_t motor_n, int16_t val);
void mgos_jsar_MotorsPowerWriteAll(int16_t power1, int16_t power2);
void mgos_jsar_MotorsSpeedWriteAll(int16_t speed1, int16_t speed2);

int16_t mgos_jsar_MotorsPowerRead(uint8_t motor_n);
int16_t mgos_jsar_MotorsPositionRead(uint8_t motor_n);
int16_t mgos_jsar_MotorsSpeedRead(uint8_t motor_n);

void mgos_jsar_MotorsPositionReadAll(int16_t *pos1, int16_t *pos2);
void mgos_jsar_MotorsSpeedReadAll(int16_t *speed1, int16_t *speed2);
void mgos_jsar_MotorsPowerReadAll(int16_t *power1, int16_t *power2);
void mgos_jsar_MotorsReadAll(int16_t *position1, int16_t *speed1, 
                             int16_t *position2, int16_t *speed2);


#ifdef __cplusplus
}
#endif  /* __cplusplus */

#endif /* MGOS_JSAR_H */