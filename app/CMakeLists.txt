# Any C++ source files needed to build this target (shell-app).
add_executable(track
        # list of source cpp files:
        main.cpp
        #        test.cpp
)

# Any include directories needed to build this target.
# Note: we do not need to specify the include directories for the
# dependent libraries, they are automatically included.
target_include_directories(track PUBLIC
        # list include directories:
        ${CMAKE_SOURCE_DIR}/src/AcmeVision/include
        ${ACMEBOT_INCLUDE_DIRS}
        ${OpenCV_INCLUDE_DIRS}
)

# Any dependent libraires needed to build this target.
target_link_libraries(track PUBLIC
        # list of libraries
        # Human_Tracker_Team7_lib
        readerwriterqueue
        AcmeVisionLib
        ${OpenCV_LIBS} ${EIGEN3_LIBS}
)
