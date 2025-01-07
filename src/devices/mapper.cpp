#include "mapper.h"

Mapper::Mapper(const uint64_t& new_id)
: id(new_id)
{

}

Mapper000::Mapper000(const uint64_t& new_id)
: Mapper(new_id)
{

}

addr_t Mapper000::map_read(const addr_t& addr)
{
	return addr;
}

addr_t Mapper000::map_write(const addr_t& addr)
{
	return addr;
}
