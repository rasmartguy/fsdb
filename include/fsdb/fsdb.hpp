#pragma once

#include <string>

class Fsdb {
public:
	Fsdb() : m_initialized(false), m_name("default") {

	}
	~Fsdb() {
        deinit();
	}
	bool init();
	bool deinit();
	bool initialized();
	std::string get_name();
private:
	bool m_initialized;
	std::string m_name;

	bool init_db_directory();
};

