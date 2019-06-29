#include <fsdb/fsdb.hpp>

int main() {
	Fsdb db;
	db.init();
	db.insert("key", "value", 5);
	return 0;
}
