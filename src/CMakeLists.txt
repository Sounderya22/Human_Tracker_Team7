add_library(Human_Tracker SHARED
  main.cpp
)

target_include_directories(Human_Tracker PUBLIC
  # list of directories:
  .
  AcmeBot/include/
	${EIGEN3_INCLUDE_DIR}
  ${OpenCV_INCLUDE_DIRS}
)

add_subdirectory(AcmeBot)

target_link_libraries(Human_Tracker PUBLIC AcmeBot ${OpenCV_LIBS} ${EIGEN3_LIBS})
