#pragma once

#include "six502.h"

class Mapper {
public:
	struct Header {
		uint64_t placeholder;
	};

protected:
	u8 nr_prg_banks;
	u8 nr_chr_banks;

	Header header;

	addr_range_t iorange_cpu;
	addr_range_t iorange_ppu;

public:
	const uint64_t id;

public:
	virtual bool cpu_map_read(const addr_t& addr, addr_t& mapped_addr) = 0;
	virtual bool cpu_map_write(const addr_t& addr, addr_t& mapped_addr) = 0;
	virtual bool ppu_map_read(const addr_t& addr, addr_t& mapped_addr) = 0;
	virtual bool ppu_map_write(const addr_t& addr, addr_t& mapped_addr) = 0;

public:
	Mapper(const uint64_t& new_id,
			const u8& nr_prg_banks,
			const u8& nr_chr_banks);

	virtual ~Mapper() {};
};

class Mapper000 : public Mapper {
public:
	inline static const std::string name = "Mapper 000";

	inline static const addr_t cpu_addr_from = 0x8000;
	inline static const addr_t cpu_addr_to = 0xFFFF;
	
	inline static const addr_t ppu_addr_from = 0x0000;
	inline static const addr_t ppu_addr_to = 0x1FFF;

public:
	bool cpu_map_read(const addr_t& addr, addr_t& mapped_addr);
	bool cpu_map_write(const addr_t& addr, addr_t& mapped_addr);
	bool ppu_map_read(const addr_t& addr, addr_t& mapped_addr);
	bool ppu_map_write(const addr_t& addr, addr_t& mapped_addr);

public:
	Mapper000(const uint64_t& new_id,
			const u8& nr_prg_banks,
			const u8& nr_chr_banks);

	~Mapper000();
};
