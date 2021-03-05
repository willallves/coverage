cmake_minimum_required(VERSION 3.13)

project(cmake-coverage VERSION 0.0.1)
 
include_directories(${PROJECT_SOURCE_DIR}/include)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -g -O0")

# Locate GTest
find_package(GTest REQUIRED)

add_library(maior SHARED src/main.cpp)
add_library(sqrt SHARED src/sqrt.cpp)

# Enable tests
option(ENABLE_TESTS "Enable unit testing" ON)

if (ENABLE_TESTS)
    enable_testing()
    add_subdirectory(tests)

    # Add build target to generate Coverage Test Report to all compiled object files
    find_program(GCOV gcov)
    find_program(LCOV lcov)
    find_program(GENHTML genhtml)
    if(NOT GCOV)
        message(FATAL_ERROR "gcov not found!")
    endif()
    if(NOT LCOV)
        message(FATAL_ERROR "lcov not found!")
    endif()
    if(NOT GENHTML)
        message(FATAL_ERROR "genhtml not found!")
    endif()

    add_custom_target(gcov
        COMMAND mkdir -p Coverage
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

    add_custom_command(TARGET gcov POST_BUILD
        COMMAND find ${CMAKE_BINARY_DIR} -type f -name *test.cpp.o -exec ${GCOV} {} "\;"
        COMMAND echo "Command gcov - Coverage reports generated."
        COMMAND echo "You can find them on ${CMAKE_BINARY_DIR}/Coverage"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Coverage
        COMMENT "Command gcov - Coverage Reports Generated"
    )

    add_custom_target(lcov
        COMMAND mkdir -p Coverage/Reports
        COMMAND echo "Command lcov - Coverage reports generated."
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    )

    add_custom_command(TARGET lcov POST_BUILD

        COMMAND find .. -type f -name *test.cpp.gcda -exec rm -r {} "\;"
        COMMAND find .. -type f -name *test.cpp.gcno -exec rm -r {} "\;"
        
        COMMAND ${LCOV} --directory .. --capture -o lcov.info
        COMMAND ${LCOV} --remove lcov.info -o lcov.info '/usr/*'
        
        COMMAND echo "lcov.info generated."
        COMMAND ${GENHTML} lcov.info --output-directory ${CMAKE_BINARY_DIR}/Coverage/Reports 
        COMMAND echo "Command lcov - Coverage reports generated."
        COMMAND echo "You can find them on ${CMAKE_BINARY_DIR}/Coverage/Reports"
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/Coverage
        COMMENT "Command lcov - Coverage Reports Generated"
    )

    # Add 'Coverage' folder into clean target
    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES Coverage)
endif(ENABLE_TESTS)
