add_library(Human_Tracker
  main.cpp
)

target_include_directories(Human_Tracker PUBLIC
  # list of directories:
  .
  AcmeBot/include/
  )


  add_subdirectory(AcmeBot)