cmake_minimum_required(VERSION 3.1)
project(uva_acm)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    job_id_str.cpp)

add_executable(uva_acm ${SOURCE_FILES})

set_target_properties(uva_acm PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")