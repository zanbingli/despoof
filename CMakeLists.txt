cmake_minimum_required(VERSION 2.8)
project(despoof CXX)
file(READ version.txt Version)

set(Despoof_includes "${PROJECT_SOURCE_DIR}/include")
set(Argtable2_includes "${PROJECT_SOURCE_DIR}/vendor/argtable2/src")
set(UnitTestCpp_includes "${PROJECT_SOURCE_DIR}/vendor/unittest-cpp/src")
set(Output_directory "${CMAKE_BINARY_DIR}")

include_directories(${Despoof_includes} ${Argtable2_includes})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${Output_directory})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${Output_directory})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${Output_directory})

if(MSVC)
	macro(enable_assertions config)
		string(REPLACE "/D NDEBUG" "" CMAKE_CXX_FLAGS_${config} "${CMAKE_CXX_FLAGS_${config}}")
	endmacro()
	
	enable_assertions(RELEASE)
	enable_assertions(MINSIZEREL)
	enable_assertions(RELWITHDEBINFO)
endif()

macro(configuration_variable_string var)
	if(${var})
		add_definitions("-DDESPOOF_${var}=\"${${var}}\"")
	endif()
endmacro()

configuration_variable_string(DEFAULT_DEBUGGER)
configuration_variable_string(SERVICE_NAME)
configuration_variable_string(SERVICE_DESCRIPTION)
configuration_variable_string(DEFAULT_NET_MODULE)
configuration_variable_string(DEFAULT_LOG_MODULE_ALL)
configuration_variable_string(DEFAULT_LOG_MODULE_NOSVC)
configuration_variable_string(DEFAULT_LOG_MODULE_SVC)

add_definitions(-DUNICODE -D_UNICODE -DDESPOOF_VERSION=\"${Version}\")

add_subdirectory(vendor)

add_subdirectory(common)
add_subdirectory(common-log)
add_subdirectory(common-nw)
add_subdirectory(win32support)
add_subdirectory(log-console)
add_subdirectory(log-file)
add_subdirectory(nw-pcap)
add_subdirectory(despoof)
add_subdirectory(despoof-svctool)

add_subdirectory(test)
