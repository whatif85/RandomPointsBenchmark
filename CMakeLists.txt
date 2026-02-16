cmake_minimum_required(VERSION 3.20)

project(RandomPointsBenchmark LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(RandomPointsBenchmark
               "src/main.cpp"
               "src/Point.h"
               "src/MTGenerator.h" "src/MTGenerator.cpp"
               "src/XorShiftGenerator.h" "src/XorShiftGenerator.cpp"
)

if (MSVC)
    target_compile_options(RandomPointsBenchmark PRIVATE
        $<$<CONFIG:Release>:/O2 /arch:AVX2>
    )
else()
    target_compile_options(RandomPointsBenchmark PRIVATE
        $<$<CONFIG:Release>:-O3 -march=native -flto>
    )
    target_link_options(RandomPointsBenchmark PRIVATE
        $<$<CONFIG:Release>:-flto>
    )
endif()