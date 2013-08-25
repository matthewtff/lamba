cmake_minimum_required ( VERSION 2.6 )
project (lamba)

if (${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD" OR ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

	SET (warnings "-Wall -Wextra -Woverloaded-virtual -Werror")

	SET (common_flags "-std=c++0x -fPIC")

	SET (CMAKE_CXX_FLAGS
		"${CMAKE_CXX_FLAGS} ${warnings} ${common_flags}"
	)

	SET (CMAKE_CXX_FLAGS_DEBUG
		"${CMAKE_CXX_FLAGS_DEBUG} ${warnings} ${comon_flags} -g -ggdb"
	)

	SET (CMAKE_CXX_FLAGS_RELEASE
		"${CMAKE_CXX_FLAGS_RELEASE} ${warnings} ${common_flags} -O2"
	)

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	
endif (${CMAKE_SYSTEM_NAME} MATCHES "Linux" OR ${CMAKE_SYSTEM_NAME} MATCHES "FreeBSD" OR ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

include_directories (
	/opt/local/include
)

link_directories (
	/opt/local/lib
)

endif (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/lib)

set (lamba_interpreter_libs
  lamba
)

link_directories (${CMAKE_SOURCE_DIR}/lib)

set ( lamba_src
  src/lamba/tokenizer.cc
  src/lamba/token.cc
)

set ( lamba_interpreter_src
  src/interpreter.cc
)

add_library ( lamba ${lamba_src} )
add_executable ( lambai ${lamba_interpreter_src} )
target_link_libraries ( lambai ${lamba_interpreter_libs} )
