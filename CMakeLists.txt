cmake_minimum_required(VERSION 3.20)

project(YieldCurve VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(
    YieldCurveLib
    src/curve_point.cpp
    src/yield_curve.cpp
)

target_include_directories(YieldCurveLib PUBLIC include)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(
    YieldCurveTests
    tests/curve_point_test.cpp
    tests/yield_curve_test.cpp

)

target_link_libraries(
    YieldCurveTests
    PRIVATE
        YieldCurveLib
        GTest::gtest_main
)

enable_testing()

add_test(YieldCurveTests YieldCurveTests)