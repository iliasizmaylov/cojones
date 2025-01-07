#include "cartridge.h"

Cartridge::Cartridge(const char *name, addr_t from, addr_t to)
: DEV_six502(name, from, to)
{

}

Cartridge::~Cartridge()
{

}
