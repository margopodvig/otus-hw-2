cmake_minimum_required(VERSION 3.5)

project(ip_filter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(WITH_GOOGLE_TESTS "Build google tests" ON)

set(SOURCES IpData.cpp)
set(HEADERS IpData.h)
add_library(ip_data ${HEADERS} ${SOURCES})

if(WITH_GOOGLE_TESTS)
    enable_testing()
    add_subdirectory(Tests)
endif()


add_executable(ip_filter main.cpp)
target_link_libraries(ip_filter ip_data)

if(MSVC)
    target_compile_options(ip_data PRIVATE
         /W4)
    target_compile_options(ip_filter  PRIVATE
        /W4)
else()
     target_compile_options(ip_data PRIVATE
          -Wall -Wextra -pedantic -Werror)
      target_compile_options(ip_filter PRIVATE
           -Wall -Wextra -pedantic -Werror)
endif()

include(GNUInstallDirs)
install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)

