# Declare the library target first
add_library(AcmeBot
        acmebot.cpp
        detector.cpp
        tracker.cpp
)

# Specify the include directory
target_include_directories(AcmeBot PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

