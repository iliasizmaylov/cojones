#pragma once

#include "six502.h"

class Memory : public NES_MEM_six502 {
public:
	Memory(const char *name, addr_t from, addr_t to);
	~Memory();

private:

};
