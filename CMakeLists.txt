cmake_minimum_required(VERSION 2.6)

project (gantelet)

set(EXECUTABLE_OUTPUT_PATH  ${CMAKE_SOURCE_DIR})



FILE(GLOB
	SRCS
	main.cpp
	sources/*.cpp
	sources/Entity/*.cpp
	sources/Ojbects/*.cpp
	sources/GamePhase/*.cpp
	)

FILE(GLOB
	HDRS
	lib/irrklang/include/*
	lib/irrlicht-1.8.4/include/*.hpp
	lib/freeglut/include/GL/*.h
	includes/*.hpp
	includes/GamePhase/*.hpp
	includes/Objects/*.hpp
	includes/PowerUp/*.hpp
	includes/Entity/*.hpp
	)

add_executable(
	gantelet
	${SRCS}
	${HDRS}
	)

	

	include_directories(
	${CMAKE_SOURCE_DIR}/includes
	${CMAKE_SOURCE_DIR}/includes/GamePhase
	${CMAKE_SOURCE_DIR}/includes/Objects
	${CMAKE_SOURCE_DIR}/includes/PowerUp
	${CMAKE_SOURCE_DIR}/includes/Entity
	${CMAKE_SOURCE_DIR}/lib/irrklang/include
	${CMAKE_SOURCE_DIR}/lib/irrlicht-1.8.4/include
	${CMAKE_SOURCE_DIR}/lib/freeglut/include
	)

link_directories(
${CMAKE_SOURCE_DIR}/lib/irrlicht-1.8.4/lib/Win64-VisualStudio
${CMAKE_SOURCE_DIR}/lib/freeglut/lib/x64
${CMAKE_SOURCE_DIR}/lib/irrklang/lib/Winx64-visualStudio
)



target_link_libraries(
	gantelet
	${CMAKE_SOURCE_DIR}/lib/irrlicht-1.8.4/lib/Win64-VisualStudio/Irrlicht.lib
	${CMAKE_SOURCE_DIR}/lib/freeglut/lib/x64/Freeglut.lib
	${CMAKE_SOURCE_DIR}/lib/irrklang/lib/Winx64-visualStudio/irrKlang.lib
	)