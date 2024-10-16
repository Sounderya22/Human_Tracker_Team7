# Declare the library target first
add_library(Human_Tracker_Team7_lib
    AcmeBot.cpp
    Detector.cpp
    Tracker.cpp
)

# Specify the include directory
target_include_directories(Human_Tracker_Team7_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Set C++ standard
target_compile_features(Human_Tracker_Team7_lib PUBLIC cxx_std_11)

# Link OpenCV
target_link_libraries(Human_Tracker_Team7_lib ${OpenCV_LIBS})
