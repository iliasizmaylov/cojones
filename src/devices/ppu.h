#pragma once

#include "six502.h"

#include <functional>
#include <array>
#include <memory>

#include "cartridge.h"

class PPU : public DEV_six502 {
public:
	typedef std::function<result_t(addr_t, databus_t *data)> readfn_t;
	typedef std::function<result_t(addr_t, databus_t data)> writefn_t;

	enum rwfn_addr_t {
		CTRL	= 0x0000,
		MASK	= 0x0001,
		STATUS	= 0x0002,
		OAMADDR	= 0x0003,
		OAMDATA	= 0x0004,
		SCROLL	= 0x0005,
		PPUADDR	= 0x0006,
		PPUDATA	= 0x0007,
	};

private:
	static inline const char *default_name = "PPU";
	static inline const addr_t default_addr_from = 0x2000;
	static inline const addr_t default_addr_to = 0x3FFF;
	static inline const addr_t addr_mirror_mask = 0x0007;

	static inline const u8 mem_size = 8;
	static inline const u8 nr_name_tbls = 2;
	static inline const u8 nr_palettes = 32;

private:
	databus_t mem[PPU::mem_size];
	databus_t name_tbl[PPU::nr_name_tbls][MEM_MAX_1KB];
	databus_t palette_tbl[PPU::nr_palettes];

	std::array<readfn_t, PPU::mem_size> readfn;

	result_t read_ctrl(addr_t addr, databus_t *data);
	result_t read_mask(addr_t addr, databus_t *data);
	result_t read_status(addr_t addr, databus_t *data);
	result_t read_oamaddr(addr_t addr, databus_t *data);
	result_t read_oamdata(addr_t addr, databus_t *data);
	result_t read_scroll(addr_t addr, databus_t *data);
	result_t read_ppuaddr(addr_t addr, databus_t *data);
	result_t read_ppudata(addr_t addr, databus_t *data);

	std::array<writefn_t, PPU::mem_size> writefn;

	result_t write_ctrl(addr_t addr, databus_t data);
	result_t write_mask(addr_t addr, databus_t data);
	result_t write_status(addr_t addr, databus_t data);
	result_t write_oamaddr(addr_t addr, databus_t data);
	result_t write_oamdata(addr_t addr, databus_t data);
	result_t write_scroll(addr_t addr, databus_t data);
	result_t write_ppuaddr(addr_t addr, databus_t data);
	result_t write_ppudata(addr_t addr, databus_t data);

	std::shared_ptr<Cartridge> cart;

private:
	addr_t mirror(addr_t addr) const;

public:
	result_t connect_cart(const std::shared_ptr<Cartridge>& cart);
	result_t disconnect_cart();

	result_t process_read(addr_t addr, databus_t *data);
	result_t process_write(addr_t addr, databus_t data);
	
	result_t ppu_read(addr_t addr, databus_t *data);
	result_t ppu_write(addr_t addr, databus_t data);

public:
	PPU();
	PPU(const char *name, addr_t from, addr_t to);
	~PPU();
};
