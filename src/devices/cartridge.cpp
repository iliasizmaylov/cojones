#include "cartridge.h"

bool Cartridge::init_filetypefn()
{
	using std::placeholders::_1;
	using std::placeholders::_2;

	filetypefn[TYPE_0] = std::bind(&Cartridge::filetypefn_0, this, _1, _2);	
	filetypefn[TYPE_1] = std::bind(&Cartridge::filetypefn_1, this, _1, _2);	
	filetypefn[TYPE_2] = std::bind(&Cartridge::filetypefn_2, this, _1, _2);	

	return true;
}

bool Cartridge::init()
{
	mapper_id = 0;
	nr_prg_banks = 0;
	nr_chr_banks = 0;

	init_filetypefn();

	is_initialized = false;
}

Cartridge::Cartridge(const char *name, addr_t from, addr_t to)
: DEV_six502(name, from, to)
{
	init();
}

Cartridge::Cartridge(const char *name)
: Cartridge::Cartridge(name,
		Cartridge::default_addr_from,
		Cartridge::default_addr_to)
{

}

Cartridge::Cartridge()
: Cartridge::Cartridge(Cartridge::default_name,
		Cartridge::default_addr_from,
		Cartridge::default_addr_to)
{

}

Cartridge::~Cartridge()
{

}

inline u8 Cartridge::get_mapper_id(const Cartridge::Header& header)
{
	return ((header.mapper_2 >> 4) << 4) | (header.mapper_1 >> 4);
}

bool Cartridge::filetypefn_0(std::ifstream& ifs, const Cartridge::Header& header)
{
	if (!ifs.is_open())
		return false;
	
	return true;
}

bool Cartridge::filetypefn_1(std::ifstream& ifs, const Cartridge::Header& header)
{
	if (!ifs.is_open())
		return false;

	nr_prg_banks = header.prg_rom_chunks;
	progmem.resize(nr_prg_banks * MEM_MAX_16KB);
	ifs.read((char*) progmem.data(), progmem.size());

	nr_chr_banks = header.chr_rom_chunks;
	charmem.resize(nr_chr_banks * MEM_MAX_8KB);
	ifs.read((char*) charmem.data(), charmem.size());
	
	return true;
}

bool Cartridge::filetypefn_2(std::ifstream& ifs, const Cartridge::Header& header)
{
	if (!ifs.is_open())
		return false;
	
	return true;
}

bool Cartridge::init_from_file(const std::string& file_name)
{
	Cartridge::Header header;

	std::ifstream ifs;
	ifs.open(file_name, std::ifstream::binary);

	if (!ifs.is_open())
		return false;

	/* Read cartridge header */
	ifs.read((char*)&header, sizeof(Cartridge::Header));

	/* If specified bit is set it means that next 512 bytes are just
	 * training information which are (as of yet) useless for the
	 * emulator and thus are skipped altogether
	 */
	if (header.mapper_1 & 0x04)
		ifs.seekg(512, std::ios_base::cur);

	mapper_id = get_mapper_id(header);

	/* TODO: Force set file type to 1 for now */
	u8 file_type = Cartridge::FileType::TYPE_1;

	bool ret = filetypefn[file_type](ifs, header);

	/* TODO: Force load Mapper 000 for testing
	 *       In the future the mapper has to be picked or constructed
	 *       from a mapper factory base on a mapper_id
	 */
	mapper = std::make_shared<Mapper000>(000, nr_prg_banks, nr_chr_banks);

	is_initialized = true;
	ifs.close();
	return ret;
}

result_t Cartridge::process_read(addr_t addr, databus_t *data)
{
	if (!is_initialized)
		return SIX502_RET_NO_RW;

	if (!isin_addr_range(&iorange, addr))
		return SIX502_RET_NO_RW;

	addr_t mapped_addr;
	if (mapper->cpu_map_read(addr, mapped_addr)) {
		*data = progmem[mapped_addr];
		return SIX502_RET_SUCCESS;
	}
	
	return SIX502_RET_NO_RW;
}

result_t Cartridge::process_write(addr_t addr, dabaus_t data)
{
	if (!is_initialized)
		return SIX502_RET_NO_RW;

	if (!isin_addr_range(&iorange, addr))
		return SIX502_RET_NO_RW;

	addr_t mapped_addr;
	if (mapper->cpu_map_write(addr, mapped_addr)) {
		progmem[mapped_addr] = data;
		return SIX502_RET_SUCCESS;
	}

	return SIX502_RET_NO_RW;
}

bool Cartridge::ppu_read(addr_t addr, databus_t *data)
{
	if (!is_initialized)
		return false;

	addr_t mapped_addr;
	if (mapper->ppu_map_read(addr, mapped_addr)) {
		*data = charmem[mapped_addr];
		return true;
	}

	return false;
}

bool Cartridge::ppu_write(addr_t addr, databus_t data)
{
	if (!is_initialized)
		return false;

	addr_t mapped_addr;
	if (mapper->ppu_map_write(addr, mapped_addr)) {
		charmem[mapped_addr] = data;
		return true;
	}

	return false;
}
