#include "ppu.h"

PPU::PPU(const char *name, addr_t from, addr_t to)
: DEV_six502(name, from, to)
{
	using std::placeholders::_1;
	using std::placeholders::_2;

	readfn[rwfn_addr_t::CTRL] = std::bind(&PPU::read_ctrl, this, _1, _2);
	readfn[rwfn_addr_t::MASK] = std::bind(&PPU::read_mask, this, _1, _2);
	readfn[rwfn_addr_t::STATUS] = std::bind(&PPU::read_status, this, _1, _2);
	readfn[rwfn_addr_t::OAMADDR] = std::bind(&PPU::read_oamaddr, this, _1, _2);
	readfn[rwfn_addr_t::OAMDATA] = std::bind(&PPU::read_oamdata, this, _1, _2);
	readfn[rwfn_addr_t::SCROLL] = std::bind(&PPU::read_scroll, this, _1, _2);
	readfn[rwfn_addr_t::PPUADDR] = std::bind(&PPU::read_ppuaddr, this, _1, _2);
	readfn[rwfn_addr_t::PPUDATA] = std::bind(&PPU::read_ppudata, this, _1, _2);

	writefn[rwfn_addr_t::CTRL] = std::bind(&PPU::write_ctrl, this, _1, _2);
	writefn[rwfn_addr_t::MASK] = std::bind(&PPU::write_mask, this, _1, _2);
	writefn[rwfn_addr_t::STATUS] = std::bind(&PPU::write_status, this, _1, _2);
	writefn[rwfn_addr_t::OAMADDR] = std::bind(&PPU::write_oamaddr, this, _1, _2);
	writefn[rwfn_addr_t::OAMDATA] = std::bind(&PPU::write_oamdata, this, _1, _2);
	writefn[rwfn_addr_t::SCROLL] = std::bind(&PPU::write_scroll, this, _1, _2);
	writefn[rwfn_addr_t::PPUADDR] = std::bind(&PPU::write_ppuaddr, this, _1, _2);
	writefn[rwfn_addr_t::PPUDATA] = std::bind(&PPU::write_ppudata, this, _1, _2);
}

PPU::PPU()
: PPU(PPU::default_name, PPU::default_addr_from, PPU::default_addr_to)
{

}

/* ============ MAIN METHODS ============ */

addr_t PPU::mirror(addr_t addr) const
{
	return addr & PPU::addr_mirror_mask;
}

result_t PPU::ppu_read(addr_t addr, databus_t *data)
{
	if (!isin_addr_range(&iorange, addr))
		return SIX502_RET_NO_RW;

	return SIX502_RET_SUCCESS;
}

result_t PPU::ppu_write(addr_t addr, databus_t data)
{
	if (!isin_addr_range(&iorange, addr))
		return SIX502_RET_NO_RW;

	return SIX502_RET_SUCCESS;
}

result_t PPU::process_read(addr_t addr, databus_t *data)
{
	if (!isin_addr_range(&iorange, addr))
		return SIX502_RET_NO_RW;

	addr_t m_addr = mirror(addr);
	return readfn[m_addr](m_addr, data);
}

result_t PPU::process_write(addr_t addr, databus_t data)
{
	if (!isin_addr_range(&iorange, addr))
		return SIX502_RET_NO_RW;

	addr_t m_addr = mirror(addr);
	return writefn[m_addr](m_addr, data);
}

/* ============ READ HANDLERS ============ */

result_t PPU::read_ctrl(addr_t addr, databus_t *data)
{
	return SIX502_RET_SUCCESS;
}

result_t PPU::read_mask(addr_t addr, databus_t *data)
{
	return SIX502_RET_SUCCESS;
}

result_t PPU::read_status(addr_t addr, databus_t *data)
{
	return SIX502_RET_SUCCESS;
}

result_t PPU::read_oamaddr(addr_t addr, databus_t *data)
{
	return SIX502_RET_SUCCESS;
}

result_t PPU::read_oamdata(addr_t addr, databus_t *data)
{
	return SIX502_RET_SUCCESS;
}

result_t PPU::read_scroll(addr_t addr, databus_t *data)
{
	return SIX502_RET_SUCCESS;
}

result_t PPU::read_ppuaddr(addr_t addr, databus_t *data)
{
	return SIX502_RET_SUCCESS;
}

result_t PPU::read_ppudata(addr_t addr, databus_t *data)
{
	return SIX502_RET_SUCCESS;
}

/* ============ WRITE HANDLERS ============ */

result_t PPU::write_ctrl(addr_t addr, databus_t data)
{
	return SIX502_RET_SUCCESS;
}

result_t PPU::write_mask(addr_t addr, databus_t data)
{
	return SIX502_RET_SUCCESS;
}

result_t PPU::write_status(addr_t addr, databus_t data)
{
	return SIX502_RET_SUCCESS;
}

result_t PPU::write_oamaddr(addr_t addr, databus_t data)
{
	return SIX502_RET_SUCCESS;
}

result_t PPU::write_oamdata(addr_t addr, databus_t data)
{
	return SIX502_RET_SUCCESS;
}

result_t PPU::write_scroll(addr_t addr, databus_t data)
{
	return SIX502_RET_SUCCESS;
}

result_t PPU::write_ppuaddr(addr_t addr, databus_t data)
{
	return SIX502_RET_SUCCESS;
}

result_t PPU::write_ppudata(addr_t addr, databus_t data)
{
	return SIX502_RET_SUCCESS;
}

/* ============ OTHER METHODS ============ */

PPU::~PPU()
{

}
