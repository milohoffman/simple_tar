cmake_minimum_required(VERSION 2.6)

set(PROG_NAME simple_tar)

set(SOURCES archive_transaction.cpp  
		compress.cpp  
		compressor.cpp  
		extract.cpp  
		extractor.cpp  
		main.cpp  
		options.cpp  
		permissions.cpp  
		utils.cpp
	)

find_package(Boost 1.48 REQUIRED COMPONENTS system program_options filesystem)

add_executable(${PROG_NAME} ${SOURCES})
include_directories(${Boost_INCLUDE_DIRS})
target_link_libraries(${PROG_NAME} ${Boost_LIBRARIES})