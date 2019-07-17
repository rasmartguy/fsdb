find_path(
		FSDB_INLCUDE_DIR
		NAMES fsdb/fsdb.hpp
		PATHS /usr/local/include /usr/include ${FSDB_DIR}/include
)

message(STATUS "Fsdb dir: ${FSDB_DIR}")

if(FSDB_INCLUDE_DIR)
	find_library(
			FSDB_LIBRARY
			NAMES fsdb
			PATHS
				/usr/local/lib
				/usr/lib
				${FSDB_DIR}/lib
	)
	if(FSDB_LIBRARY)
		set(FSDB_LIBRARY_DIR "")
		get_filename_component(FSDB_LIBRARY_DIRS ${FSDB_LIBRARY} PATH)
		set(FSDB_FOUND ON)
		set(FSDB_INCLUDE_DIRS ${FSDB_INCLUDE_DIR})
		set(FSDB_LIBRARIES ${FSDB_LIBRARY})
	endif()
else()
	message(STATUS "FindFsdb: Could not find fsdb.hpp")
endif()

if(FSDB_FOUND)
	if(NOT FSDB_FIND_QUIETLY)
		message(STATUS "FindFsdb: Found fsdb.h and fsdb-library")
	endif()
else()
	if(FSDB_FIND_REQUIRED)
		message(FATAL_ERROR "FindFsdb: Could not find fsdb.h and/or fsdb-library")
	endif()
endif()

