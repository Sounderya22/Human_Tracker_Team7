# Any C++ source files needed to build this target (shell-app).
add_executable(human_tracker
  # list of source cpp files:
  main.cpp
  )

# Any include directories needed to build this target.
# Note: we do not need to specify the include directories for the
# dependent libraries, they are automatically included.
target_include_directories(human_tracker PUBLIC
  # list inclue directories:
  ${CMAKE_SOURCE_DIR}/include
)

# Any dependent libraires needed to build this target.
target_link_libraries(human_tracker PUBLIC -static
  # list of libraries
  Human_Tracker_Team7_lib
  )

  
