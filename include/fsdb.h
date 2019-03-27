#ifndef _RA_DB_H_
#define _RA_DB_H_

class Fsdb {
public:
	Fsdb() : m_initialized(false) {

	}
	~Fsdb() {

	}
	void init();
	bool initialized();
private:
	bool m_initialized;
};

#endif
