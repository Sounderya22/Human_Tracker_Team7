# Any C++ source files needed to build this target.
add_executable(humanBot_test
        # list of source cpp files:
        main.cpp
        test.cpp
)

# Any include directories needed to build this target.
# Note: we do not need to specify the include directories for the
# dependent libraries, they are automatically included.
target_include_directories(humanBot_test PUBLIC
        # list of include directories:
        ./
        ${CMAKE_SOURCE_DIR}/src/AcmeVision/include/
)

# Any dependent libraires needed to build this target.
target_link_libraries(humanBot_test PUBLIC
        # list of libraries:
        gtest
        gmock
        spdlog::spdlog
        AcmeVisionLib
)

# Enable CMake’s test runner to discover the tests included in the
# binary, using the GoogleTest CMake module.
gtest_discover_tests(humanBot_test)
