cmake_minimum_required(VERSION 3.5)
project(SecondLab)
add_executable(oop2 main.cpp Position.cpp Position.h)
set_target_properties(oop2 PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED ON
	)
