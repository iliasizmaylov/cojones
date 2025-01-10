#include "mapper.h"

Mapper::Mapper(const uint64_t& new_id,
		const u8& nr_prg_banks,
		const u8& nr_chr_banks)
: id(new_id)
{
	this->nr_prg_banks = nr_prg_banks;
	this->nr_chr_banks = nr_chr_banks;
}

Mapper000::Mapper000(const uint64_t& new_id,
		const u8& nr_prg_banks,
		const u8& nr_chr_banks)
: Mapper(new_id, nr_prg_banks, nr_chr_banks)
{
	fill_addr_range(&iorange_cpu,
			Mapper000::cpu_addr_from,
			Mapper000::cpu_addr_to);

	fill_addr_range(&iorange_ppu,
			Mapper000::ppu_addr_from,
			Mapper000::ppu_addr_to);
}

Mapper000::~Mapper000()
{

}

bool Mapper000::cpu_map_read(const addr_t& addr, addr_t& mapped_addr)
{
	if (!isin_addr_range(&iorange_cpu, addr))
		return false;

	mapped_addr = addr & (nr_prg_banks > 1 ? 0x7FFF : 0x3FFF);
	return true;
}

bool Mapper000::cpu_map_write(const addr_t& addr, addr_t& mapped_addr)
{
	if (!isin_addr_range(&iorange_cpu, addr))
		return false;

	mapped_addr = addr;
	return true;
}

bool Mapper000::ppu_map_read(const addr_t& addr, addr_t& mapped_addr)
{
	if (!isin_addr_range(&iorange_ppu, addr))
		return false;

	mapped_addr = addr;
	return true;
}

bool Mapper000::ppu_map_write(const addr_t& addr, addr_t& mapped_addr)
{
	return false;
}
