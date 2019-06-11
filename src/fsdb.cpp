#include <assert.h>
#include <filesystem>
#include "fsdb/fsdb.hpp"

bool Fsdb::init() {
	if (!init_db_directory()) {
	    return false; //< TODO: return error code
	}
    m_initialized = true;
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

bool Fsdb::init_db_directory() {
    if (std::filesystem::exists(m_name)) {
		auto dir_entry = std::filesystem::directory_entry(m_name);
        return dir_entry.is_directory();
    }
    else {
        return std::filesystem::create_directories(m_name);
    }
}

