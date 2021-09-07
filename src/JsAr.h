#ifndef __JS_AR_H
#define __JS_AR_H

#include "mgos.h"

#define ESP_JS_AR (1)	

class JsAr
{
public:
    JsAr()
    {
        
    };

	int  begin(bool isEnableAllPins = true);

    void enableEthernet();
    void disableEthernet();

    void enableI2CPins();
    void disableI2CPins();

    void enableCanModule();
    void disableCanModule(); 

    void disableSpiPins(); 
    void enableSpiPins3V3Mode();
    void enableSpiPinsFast3V3Mode();
    void enableSpiPins5VMode();
    void enableSpiPinsFast5VMode();

    void disableSDPort();
    void enableSDPort1BitMode();
    void enableSDPort4BitMode();
    void enableSDPortSpiMode();

    void enableMisoPin();
    void disableMisoPin();

    void enableIrTx();
    void disableIrTx();

    void enableIrRx();
    void disableIrRx();

    void writeMinVoltageToStart(float v);
    void writeMinVoltageToWork(float v);
    float readVoltage();

    void replacePin36By25AsOUTPUT();
    void replacePin36By25AsDAC();
    void replacePin35By26AsOUTPUT();
    void replacePin35By26AsDAC();
    void replacePin34By27AsOUTPUT();
    void replacePinByExpander(uint8_t pin);

    void expanderPinMode(uint8_t pin, uint8_t mode);
    void expanderDigitalWrite(uint8_t pin, uint8_t value);
    int  expanderDigitalRead(uint8_t pin);
    void expanderAnalogWrite(uint8_t pin, uint16_t value);
    int  expanderAnalogRead(uint8_t pin);
    void expanderWriteLed(uint8_t is_en);

    void timMode(uint8_t tim, uint8_t prescaler, uint16_t pulse);

    int updateFirmware();
    void lockExpander(uint8_t packet_n);
    uint8_t unlockExpander();

private:

    void delay(uint16_t sleep) { mgos_msleep(sleep); }
    uint8_t id;
    uint8_t unlockBootloader();

};

extern JsAr jsar;

#endif
