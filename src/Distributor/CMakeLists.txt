cmake_minimum_required(VERSION 3.14.4)

set(SRC_PATH "./")

project(Distributor)

add_executable(${PROJECT_NAME} 
	${SRC_PATH}/DistributorMain.cpp
	${SRC_PATH}/DistributorClass.cpp
	)