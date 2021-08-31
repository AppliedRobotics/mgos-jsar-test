#ifndef __JS_AR_INTERFACE_H
#define __JS_AR_INTERFACE_H

#include "DxlMaster.h"
#include "regs.h"

#define STM8_ID	(250)

class JsArInterface : public HardwareDynamixelInterface
{
public:
    JsArInterface(uint8_t aUART_no) : HardwareDynamixelInterface(aUART_no), 
		mId(STM8_ID)
	{};

	DynamixelStatus set8(uint8_t addr, uint8_t val);
	DynamixelStatus set16(uint8_t addr, uint16_t val);
	DynamixelStatus get8(uint8_t addr, uint8_t *data);
	DynamixelStatus get16(uint8_t addr, uint16_t *data);
    DynamixelStatus set(uint8_t addr, uint8_t size, uint8_t *data);
    DynamixelStatus get(uint8_t addr, uint8_t size, uint8_t *data);

	uint8_t mId;
	int mLast_error;
	uint8_t mRegs[255];

};

extern JsArInterface jsi;

#endif
