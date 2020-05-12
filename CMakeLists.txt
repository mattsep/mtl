cmake_minimum_required(VERSION 3.11)

project(mtl
    LANGUAGES CXX
    VERSION 0.1.0
)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    set(MTL_IS_ROOT_PROJECT TRUE)
else()
    set(MTL_IS_ROOT_PROJECT FALSE)
endif()

option(MTL_BUILD_TESTS "Build the MTL test executable" MTL_IS_ROOT_PROJECT)

add_library(mtl INTERFACE)
target_include_directories(mtl INTERFACE include)
target_compile_features(mtl INTERFACE cxx_std_17)
target_link_libraries(mtl INTERFACE ${CONAN_LIBS})

if(MTL_BUILD_TESTS)
    add_executable(mtl-tests tests/main.cpp)
    target_compile_definitions(mtl-tests PRIVATE MTL_BUILD_TESTS)
    target_link_libraries(mtl-tests PRIVATE mtl ${CONAN_LIBS})
    add_custom_target(test ALL COMMAND mtl-tests)
    add_dependencies(test mtl-tests)
endif()