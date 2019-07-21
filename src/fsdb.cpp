#include <assert.h>
#include <filesystem>
#include "fsdb/fsdb.hpp"

bool load_buffer_from_file(const char *cFileName, unsigned char **buffer, size_t &fileSz) {
	std::filesystem::path file_path {cFileName};
	auto full_path = std::filesystem::canonical(file_path).string();
	if(FILE *f = fopen(full_path.c_str(), "rb")) {
		fseek(f,0,SEEK_END);
		fileSz = (unsigned int)ftell(f);
		if(!fileSz) {
			// File have zero-size
			fclose(f);
			return false;
		}
		fseek(f, 0, SEEK_SET);
		try {
			auto result = new unsigned char[fileSz];
			auto cFileRead = fread(result, 1, fileSz, f);
			if(cFileRead == fileSz) {
				// Bytes read: cFileRead
				fclose(f);
				*buffer = result;
				return true;
			} else {
				// File read error
				delete[] result;
				fclose(f);
				return false;
			}
		}
		catch(...) {
			// Buffer allocation error
			fclose(f);
			return false;
		}
	}
	else {
		// File not found
		return false;
	}
}

bool save_buffer_to_file(const char *cFileName,
                         const char *blob,
                         const size_t cBlobSz) {
    bool result = false;
    if (FILE *f = fopen(cFileName, "w+b")) {
        if(fwrite(blob, 1, cBlobSz, f) == cBlobSz) {
            result = true;
            // File write success
        }
        else {
            // File write error
        }
        fclose(f);
		}
    else {
        // file open error
    }
    return result;
}

Fsdb::Fsdb() : m_initialized(false), m_name("default") {

}
Fsdb::~Fsdb(){
	deinit();
}

bool Fsdb::init() {
	if (!init_db_directory()) {
	    return false; //< TODO: return error code
	}
    m_initialized = true;
	return initialized();
}

bool Fsdb::init(std::string_view name) {
	m_name = name;
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
    m_initialized = false;
    return true;
}

std::string Fsdb::get_name() {
    return m_name;
}

bool Fsdb::init_db_directory() {
	auto p = std::filesystem::path(m_name);
    if (std::filesystem::exists(p)) {
    	auto is_dir = std::filesystem::is_directory(p);
    	return is_dir;
    }
    else {
    	try {
    		std::filesystem::create_directories(p);
    	}
    	catch (...) {
    		return false;
    	}
		return true;
    }
}

std::filesystem::path Fsdb::get_db_record_path(std::string_view key) {
    std::filesystem::path key_path(m_name);
    return key_path.append(key.substr(0, 2)).append(key);
}

bool Fsdb::insert(std::string_view key, const char *pdata, const size_t data_sz) {
    if (!initialized()) return false;
    auto key_path = get_db_record_path(key);
    //if (std::filesystem::exists(key_path)) {
    //    return false;
    //}
    std::filesystem::create_directories(key_path.parent_path());
	return save_buffer_to_file(key_path.string().c_str(), pdata, data_sz);
}

bool Fsdb::obtain(std::string_view key, unsigned char **out_buffer) {
	if (!initialized()) return false;
	auto key_path = get_db_record_path(key);
	if(!std::filesystem::exists(key_path)) {
		return false;
	}
	size_t sz = 0;
	return load_buffer_from_file(key_path.c_str(), out_buffer, sz);
}

bool Fsdb::del(std::string_view key) {
	auto key_path = get_db_record_path(key);
	return std::filesystem::remove(key_path);
}
