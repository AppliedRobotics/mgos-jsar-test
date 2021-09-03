#ifndef __JS_AR_MOTORS_H
#define __JS_AR_MOTORS_H

class JsArMotors
{
public:
    void begin();
    void pidWrite(uint8_t p, uint8_t i, uint8_t d);
    void loopPeriodWrite(uint8_t period_ms);
    void encoderModeAB();
    void encoderModeA();
    void encoderModeARising();
    void maxPowerWrite(uint16_t max_power);
    
    void powerWrite(uint8_t motor_n, int16_t val);
    void speedWrite(uint8_t motor_n, int16_t val);
    void powerWriteAll(int16_t power1, int16_t power2);
    void speedWriteAll(int16_t speed1, int16_t speed2);
    
    int16_t powerRead(uint8_t motor_n);
    int16_t positionRead(uint8_t motor_n);
    int16_t speedRead(uint8_t motor_n);
    void positionReadAll(int16_t &position1, int16_t &position2);
    void speedReadAll(int16_t &speed1, int16_t &speed2);
    void powerReadAll(int16_t &power1, int16_t &power2);
    void readAll(int16_t &position1, int16_t &speed1, int16_t &position2, int16_t &speed2);
};

extern JsArMotors jsarMotors;

#endif
