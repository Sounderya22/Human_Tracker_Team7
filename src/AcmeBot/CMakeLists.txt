# Declare the library target first
add_library(AcmeBot
    AcmeBot.cpp
    Detector.cpp
    Tracker.cpp
)

# Specify the include directory
target_include_directories(AcmeBot PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

