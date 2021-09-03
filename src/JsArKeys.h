#ifndef __JS_AR_KEYS_H
#define __JS_AR_KEYS_H

class JsArKeys
{
private:
public:
    void begin();
    void pidWrite(uint8_t p, uint8_t i, uint8_t d);
    void loopPeriodWrite(uint8_t period_ms);
    void encodersEnable();
    void maxPowerWrite(uint16_t max_power);
    
    void digitalWrite(uint8_t key_n, uint8_t is_on);
    void powerWrite(uint8_t key_n, uint16_t val);
    void speedWrite(uint8_t key_n, uint16_t val);
    uint16_t powerRead(uint8_t key_n);
    uint16_t positionRead(uint8_t key_n);
    uint16_t speedRead(uint8_t key_n);

    void digitalWriteAll(uint8_t val1,  uint8_t val2,  uint8_t val3,  uint8_t val4);
    void powerWriteAll(uint16_t val1,  uint16_t val2,  uint16_t val3,  uint16_t val4);
    void speedWriteAll(uint16_t val1,  uint16_t val2,  uint16_t val3,  uint16_t val4);
    void positionReadAll(uint16_t & val1, uint16_t & val2, uint16_t & val3, uint16_t & val4);
    void speedReadAll(uint16_t & val1, uint16_t & val2, uint16_t & val3, uint16_t & val4);
};

extern JsArKeys jsarKeys;

#endif
