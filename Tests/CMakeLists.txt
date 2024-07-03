project(IpTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GoogleTest)
add_executable(
  ${PROJECT_NAME}
  tests.cc
)

target_link_libraries(
  ${PROJECT_NAME}
  gtest_main gmock_main gmock  gtest
  ip_data
)
