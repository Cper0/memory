cmake_minimum_required(VERSION 3.12)
project(Memory)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(Memory
	main.cpp
	wave.cpp
)


find_package(Siv3D)
target_link_libraries(Memory PUBLIC Siv3D::Siv3D)
target_compile_features(Memory PRIVATE cxx_std_20)

