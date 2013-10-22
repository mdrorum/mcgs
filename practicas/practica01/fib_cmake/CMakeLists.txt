#Versión del Cmake mínima requerida
cmake_minimum_required(VERSION 2.8.9)

#Nombre el proyecto
project(fib)

#Definición del compilador gcc
add_definitions(-std=c99)

FIND_PACKAGE(Doxygen)

	IF (DOXYGEN_FOUND)

	SET(DOXYGEN_INPUT "Doxyfile")
	SET(DOXYGEN_OUTPUT "./doc")

	ADD_CUSTOM_COMMAND(
		OUTPUT ${DOXYGEN_OUTPUT}
		COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
		COMMAND ${CMAKE_COMMAND} -E echo "Done."
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		DEPENDS ${DOXYGEN_INPUT}
		)

	ADD_CUSTOM_TARGET(apidoc ALL DEPENDS ${DOXYGEN_OUTPUT})

	ADD_CUSTOM_TARGET(apidoc_forced
		COMMAND ${CMAKE_COMMAND} -E echo_append "Building API Documentation..."
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_INPUT}
		COMMAND ${CMAKE_COMMAND} -E echo "Done."
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

	ENDIF (DOXYGEN_FOUND)

#Indica el nombre del ejecutable y el codigo a usar
add_executable(fib fib.cpp)
