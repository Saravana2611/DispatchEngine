cmake_minimum_required(VERSION 3.14.4)

set(SRC_PATH "./src")

project(Distributor)

add_subdirectory(${SRC_PATH}/common)
add_subdirectory(${SRC_PATH}/Distributor)
add_subdirectory(${SRC_PATH}/Workers)