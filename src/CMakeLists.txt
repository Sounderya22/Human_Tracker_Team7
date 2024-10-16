add_library(Human_Tracker
  main.cpp
)

target_include_directories(Human_Tracker PUBLIC
  # list of directories:
  .
  AcmeBot/include/
  ${OpenCV_INCLUDE_DIRS}
	${EIGEN3_INCLUDE_DIR}
)

target_link_libraries(Human_Tracker PUBLIC ${OpenCV_LIBS} ${EIGEN3_LIBS})

add_subdirectory(AcmeBot)