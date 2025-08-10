cmake_minimum_required(VERSION 3.14.4)

set(SRC_PATH "./")

project(Worker)

add_executable(${PROJECT_NAME} 
	${SRC_PATH}/WorkerMain.cpp
	${SRC_PATH}/WorkerClass.cpp
	)

target_link_libraries(${PROJECT_NAME} PRIVATE common)
