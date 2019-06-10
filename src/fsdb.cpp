#include "fsdb/fsdb.hpp"

bool Fsdb::init() {
	m_initialized = true;
	m_name = "default.db";
	return initialized();
}

bool Fsdb::initialized() {
	return m_initialized;
}

bool Fsdb::deinit() {
    return true;
}

std::string Fsdb::get_name() {
    return m_name;
}
