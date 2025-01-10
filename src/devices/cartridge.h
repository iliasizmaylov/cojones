#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <memory>
#include <array>
#include <functional>

#include "six502.h"

#include "mapper.h"

class Cartridge : public DEV_six502 {
private:
	static inline const char* default_name = "Cartridge";
	static inline const addr_t default_addr_from = 0x4020;
	static inline const addr_t default_addr_to = 0xFFFF;

public:
	struct Header {
		char name[4];
		u8 prg_rom_chunks;
		u8 chr_rom_chunks;
		u8 mapper_1;
		u8 mapper_2;
		u8 prg_ram_size;
		u8 tv_system_1;
		u8 tv_system_2;
		char unused[5];
	};

	enum FileType {
		TYPE_0 = 0,
		TYPE_1,
		TYPE_2,

		NR_TYPE,
		TYPE_UNKNOWN = NR_TYPE
	};

	typedef std::function<bool(std::ifstream& ifs,
			const Header &header)>
			filetypefn_t;

	static inline u8 get_mapper_id(const Header& header);

public:
	Cartridge(const char *name, addr_t from, addr_t to);
	Cartridge(const char *name);
	Cartridge();
	~Cartridge();

	bool init_from_file(const std::string& file_name);

	result_t process_read(addr_t addr, databus_t *data);
	result_t process_write(addr_t addr, databus_t data);
	
	bool ppu_read(addr_t addr, databus_t *data);
	bool ppu_write(addr_t addr, databus_t data);

private:
	std::vector<databus_t> progmem;
	std::vector<databus_t> charmem;

	std::array<filetypefn_t, NR_TYPE> filetypefn;

	std::shared_ptr<Mapper> mapper;

	u8 mapper_id;
	u8 nr_prg_banks;
	u8 nr_chr_banks;

	bool is_initialized;

private:
	bool filetypefn_0(std::ifstream& ifs, const Header& header);
	bool filetypefn_1(std::ifstream& ifs, const Header& header);
	bool filetypefn_2(std::ifstream& ifs, const Header& header);

	bool init();
	bool init_filetypefn();
};
