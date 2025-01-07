#include "memory.h"

Memory::Memory(const char *name, addr_t from, addr_t to)
: NES_MEM_six502(name, from, to)
{

}

Memory::~Memory()
{

}
