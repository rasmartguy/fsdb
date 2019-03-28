#include "fsdb.h"

bool Fsdb::init() {
	m_initialized = true;
	return initialized();
}

bool Fsdb::initialized() {
	return m_initialized;
}

