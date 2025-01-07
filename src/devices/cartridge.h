#pragma once

#include <vector>

#include "six502.h"

#include "mapper.h"

class Cartridge : public DEV_six502 {
public:
	Cartridge(const char *name, addr_t from, addr_t to);
	~Cartridge();

private:
	std::vector<databus_t> progmem;
	std::vector<databus_t> charmem;

	std::shared_ptr<Mapper> mapper;
};
