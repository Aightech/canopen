#configure_file(config.h.in "${CMAKE_CURRENT_BINARY_DIR}/config.h" @ONLY)

cmake_minimum_required(VERSION 3.0)
set(EXEC_NAME canopen)
set(LIB_NAME ${EXEC_NAME}.0)
project(${EXEC_NAME})

#get the sources and headers
file(GLOB SRCS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "src/*.c")
file(GLOB HEADERS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h" "include/*.hpp")

#add the include libraries directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)


ADD_LIBRARY(${LIB_NAME} STATIC ${SRCS})

#create our exec file
add_executable(${EXEC_NAME} ${SRCS} ${HEADERS})

#link LSL libraries
if(UNIX)
  target_link_libraries (${EXEC_NAME} ${LIB_NAME} )
  ADD_CUSTOM_COMMAND (	TARGET ${EXEC_NAME} POST_BUILD
						#copy the dll files 
						COMMENT "Saving exec in bin/ directory..." VERBATIM
						COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_SOURCE_DIR}/bin/UNIX/${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_VERSION}
						COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_BINARY_DIR}/${EXEC_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/bin/UNIX/${CMAKE_SYSTEM_NAME}_${CMAKE_SYSTEM_VERSION}
						)
endif(UNIX)

