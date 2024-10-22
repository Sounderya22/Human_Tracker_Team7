# Declare the library target first
add_library(AcmeBot SHARED
    AcmeBot.cpp
    Detector.cpp
    Tracker.cpp
)

# set(ACMEBOT_INCLUDE_DIRS PARENT_SCOPE ${CMAKE_CURRENT_SOURCE_DIR}/include) 
set(ACMEBOT_INCLUDE_DIRS "${CMAKE_CURRENT_LIST_DIR}/include" CACHE STRING "AcmeBot Headers Directory")
message(STATUS ${ACMEBOT_INCLUDE_DIRS})

# Specify the include directory
target_include_directories(AcmeBot PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${OpenCV_INCLUDE_DIRS}
)

target_link_libraries(AcmeBot PUBLIC ${OpenCV_LIBS})

