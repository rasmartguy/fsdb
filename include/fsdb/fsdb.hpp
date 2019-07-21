#pragma once

#include <string>
#include <filesystem>
#include <string_view>

bool load_buffer_from_file(const char *cFileName, unsigned char **buffer, size_t &fileSz);
bool save_buffer_to_file(const char *cFileName, const char *blob, size_t cBlobSz);

class Fsdb {
public:
	Fsdb();
	Fsdb(const Fsdb&)= delete;
	Fsdb(const Fsdb&&)= delete;
	Fsdb&operator=(const Fsdb&)= delete;
	Fsdb&operator=(const Fsdb&&)= delete;

	~Fsdb();


	bool init();
	bool init(std::string_view name);
	bool deinit();
	bool initialized();
	std::string get_name();
	bool insert(std::string_view key, const char *pdata, size_t data_sz);
	bool obtain(std::string_view key, unsigned char **out_buffer);
	bool del(std::string_view key);
	std::filesystem::path get_db_record_path(std::string_view key);
private:
	bool m_initialized;
	std::string m_name;

	bool init_db_directory();
};

