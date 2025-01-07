#pragma once

#include "six502.h"

class APU : public DEV_six502 {
public:
	APU(const char *name, addr_t from, addr_t to);
	~APU();

private:

};
