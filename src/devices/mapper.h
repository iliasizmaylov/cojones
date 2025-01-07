#pragma once

#include "six502.h"

class Mapper {
public:
	struct Header {
		uint64_t placeholder;
	};

protected:
	Header header;

public:
	const uint64_t id;

public:
	virtual addr_t map_read(addr_t addr) = 0;
	virtual addr_t map_write(addr_t addr) = 0;

public:
	Mapper(const uint64_t& new_id);
	virtual ~Mapper() {};
};

class Mapper000 : public Mapper {
public:
	inline static const std::string name = "Mapper 000";

public:
	addr_t map_read(const addr_t& addr);
	addr_t map_write(const addr_t& addr);

public:
	Mapper000(const uint64_t& new_id);
	~Mapper000() = default;
};
